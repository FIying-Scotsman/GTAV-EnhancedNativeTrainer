#!/usr/bin/env python3
"""
Recovers ent.db after downgrading ENT to a build older than the one that added the "savedAt"
column (DB schema version 18, the "Sort By: Date Saved" feature) - running an older build
against a database a newer build already touched fails with an error like:

    table ENT_SAVED_VEHICLES has 44 columns but 43 values were supplied

...because the older build's save code doesn't know the newer column exists and always supplies
a fixed number of values. This removes that column again from every table it was added to, and
rolls the database's stored schema version back down so a future upgrade re-adds it correctly.

Only needed if you're deliberately running an older ENT build against a database a newer build
already touched. If that's not a hard requirement, updating to the latest ENT build instead
avoids the problem entirely and is the simpler fix.

A backup of the original file is made alongside it (ent.db.bak) before any change is written.

Usage:
    python downgrade_savedat_column.py path\\to\\ent.db
"""

import argparse
import shutil
import sqlite3
import sys

# Tables the "savedAt" column (DB schema version 18) was added to - see handle_version() in
# EnhancedNativeTrainer/src/storage/database.cpp for the authoritative list.
SAVEDAT_TABLES = [
    "ENT_SAVED_VEHICLES",
    "ENT_SAVED_VEH_COLOURS",
    "ENT_SAVED_SKINS",
    "ENT_SAVED_BOD_SKINS",
    "ENT_SAVED_WEAPON",
    "ENT_PROP_SETS",
]
COLUMN_TO_REMOVE = "savedAt"
ROLLBACK_TO_VERSION = 17


def table_has_column(conn, table, column):
    cur = conn.execute(f"PRAGMA table_info({table})")
    return any(row[1] == column for row in cur.fetchall())


def column_definition(row):
    # PRAGMA table_info row shape: (cid, name, type, notnull, dflt_value, pk)
    _, name, coltype, notnull, default, pk = row
    parts = [name, coltype or ""]
    if pk:
        parts.append("PRIMARY KEY AUTOINCREMENT" if (coltype or "").upper() == "INTEGER" else "PRIMARY KEY")
    if notnull:
        parts.append("NOT NULL")
    if default is not None:
        parts.append(f"DEFAULT {default}")
    return " ".join(p for p in parts if p)


def drop_column(conn, table, column):
    # Rebuilds the table without `column`, rather than SQLite's native ALTER TABLE DROP COLUMN,
    # since that needs SQLite 3.35+ and this reads through whatever sqlite3 Python happens to
    # bundle - this approach works on any version. Only covers plain column definitions (type/
    # not-null/default/single-column primary key) - none of SAVEDAT_TABLES has a UNIQUE
    # constraint or composite key to preserve, but a table added here later might.
    columns = conn.execute(f"PRAGMA table_info({table})").fetchall()
    keep = [c for c in columns if c[1] != column]

    col_defs = ", ".join(column_definition(c) for c in keep)
    col_names = ", ".join(c[1] for c in keep)
    tmp_table = f"{table}__tmp"

    conn.execute(f"CREATE TABLE {tmp_table} ({col_defs})")
    conn.execute(f"INSERT INTO {tmp_table} ({col_names}) SELECT {col_names} FROM {table}")
    conn.execute(f"DROP TABLE {table}")
    conn.execute(f"ALTER TABLE {tmp_table} RENAME TO {table}")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("db_path", help="Path to ent.db")
    args = parser.parse_args()

    backup_path = args.db_path + ".bak"
    shutil.copy2(args.db_path, backup_path)
    print(f"Backed up {args.db_path} to {backup_path}")

    conn = sqlite3.connect(args.db_path)
    # Rebuilding one table at a time via drop+rename can trip transient FK checks mid-way even
    # though the end state is fine - off for the duration of this script only. ENT itself turns
    # this back on every time it opens the database, so this doesn't weaken anything long-term.
    conn.execute("PRAGMA foreign_keys = OFF")

    try:
        changed = False
        for table in SAVEDAT_TABLES:
            if table_has_column(conn, table, COLUMN_TO_REMOVE):
                print(f"Removing {COLUMN_TO_REMOVE} from {table}...")
                drop_column(conn, table, COLUMN_TO_REMOVE)
                changed = True
            else:
                print(f"{table} has no {COLUMN_TO_REMOVE} column, skipping")

        if changed:
            conn.execute(
                "INSERT OR REPLACE INTO ENT_DB_MANIFEST (MANIFEST_KEY, MANIFEST_VALUE) VALUES ('VERSION', ?)",
                (str(ROLLBACK_TO_VERSION),),
            )
            print(f"Set the stored DB version back to {ROLLBACK_TO_VERSION}")
        else:
            print("Nothing to do - database already matches the older schema")

        conn.commit()
        print("Done. If anything looks wrong, restore from the backup at:", backup_path)
    except Exception:
        conn.rollback()
        print("Something went wrong - no changes were saved, your original file is untouched.", file=sys.stderr)
        raise
    finally:
        conn.close()


if __name__ == "__main__":
    main()
