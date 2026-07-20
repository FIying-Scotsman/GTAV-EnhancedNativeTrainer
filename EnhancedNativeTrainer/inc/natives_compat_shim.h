#pragma once

// Backward-compatibility shim for the natives.h migration.
// Every declaration here forwards an OLD namespace/name/signature to its
// NEW equivalent in natives.h, resolved by matching the native's hash (the
// stable game identifier) - this file exists purely so the natives.h swap
// is behavior-preserving on day one. Call sites are migrated off this file
// incrementally, namespace by namespace; once a namespace has zero
// remaining references anywhere in src/, delete its block below.
//
// As of Phase 2 completion, every call site in src/ has been migrated to
// call natives.h's current namespace/name directly, so this file is empty.
// Left in place (and still included from natives.h) as scaffolding in case
// a future natives.h regeneration reintroduces renamed/resignatured natives
// and needs the same shim pattern again.

#include "natives.h"
