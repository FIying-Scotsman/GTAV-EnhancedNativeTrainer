# Tools

Small standalone scripts for fixing things that don't belong in the trainer itself. None of these
are used by the trainer - they're run separately, by hand, only when needed.

## downgrade_savedat_column.py

**What this is for:** if you've gone back to an older ENT build after using a newer one, and
saving anything (a vehicle, a skin, etc.) now fails with an error like:

```
table ENT_SAVED_VEHICLES has 44 columns but 43 values were supplied
```

...this script fixes that. See `KNOWN_ISSUES.md` for why it happens. If you can update to the
latest ENT build instead of staying on an older one, do that instead - it's simpler and you won't
need this script at all.

### Step-by-step guide

You'll need Python installed to run this - a one-time setup if you don't already have it.

**1. Check if you already have Python.**

Press the Windows key, type `cmd`, and press Enter to open Command Prompt. Type:

```
python --version
```

and press Enter. If you see something like `Python 3.12.4`, you already have Python - skip to
step 3.

If instead you see an error, or it opens the Microsoft Store, you don't have it yet - continue to
step 2.

**2. Install Python.**

- Go to [python.org/downloads](https://www.python.org/downloads/) and click the big "Download
  Python" button - it'll offer you the latest version for Windows automatically.
- Run the installer you downloaded.
- **On the very first screen, tick the checkbox at the bottom that says "Add python.exe to
  PATH"** before clicking "Install Now". This step matters - if you skip it, typing `python` in
  Command Prompt won't work and you'll need to reinstall to fix it.
- Let the installer finish, then close it.
- Open a **new** Command Prompt window (close any that were already open first) and run
  `python --version` again to confirm it now shows a version number.

**3. Find your `ent.db` file.**

Press Windows key + R, type the following, and press Enter:

```
%APPDATA%\GTAV Enhanced Native Trainer
```

This opens the folder containing `ent.db` - that's the file you'll point the script at. Note the
full path shown in the folder's address bar (or just remember it's
`%APPDATA%\GTAV Enhanced Native Trainer\ent.db`).

**4. Get this script onto your computer.**

If you don't already have a copy of this repository, download just this file:
[`downgrade_savedat_column.py`](downgrade_savedat_column.py) (right-click the "Raw" button on
GitHub and choose "Save link as..."), and save it somewhere easy to find, like your Desktop.

**5. Run it.**

In your Command Prompt window, type `cd ` (with a trailing space), then drag the folder
where you saved the script into the Command Prompt window - this fills in the path for you -
then press Enter. Then run:

```
python downgrade_savedat_column.py "%APPDATA%\GTAV Enhanced Native Trainer\ent.db"
```

(You can also drag `ent.db` itself into the Command Prompt window instead of typing the path, the
same way you did with the folder above.)

**6. Check the output.**

You should see messages like `Backed up ... to ent.db.bak`, `Removing savedAt from
ENT_SAVED_VEHICLES...`, and finally `Done.`. That's it - your older ENT build should now be able
to save again.

If anything looks wrong afterward, a backup was made automatically as `ent.db.bak` right next to
your original file - delete the changed `ent.db` and rename `ent.db.bak` back to `ent.db` to
undo everything the script did.
