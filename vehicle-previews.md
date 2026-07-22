# Vehicle preview images

The vehicle spawner shows a preview image next to each vehicle in the list. Most of these
come bundled with the trainer, but you can add your own or replace an existing one without
touching any code - just drop a PNG file in the right place with the right name.

## Where to put them

`Enhanced Native Trainer\previews\` next to `EnhancedNativeTrainer.asi` (i.e. inside your
game's install folder) - the same location and file format on both Legacy and Enhanced.

## Naming a file

The filename (without `.png`) has to match the vehicle's internal model name, not its display
name - e.g. the "Bravado Gauntlet Hellfire" you see in the spawner is internally called
`gauntlet4`, so its file is `gauntlet4.png`, not `hellfire.png` or `gauntlet_hellfire.png`.

The easiest way to find a vehicle's internal model name is to spawn it once and check
`Enhanced Native Trainer\ent - log.txt` - every spawn logs a line like:

```
Attempting to spawn Bravado Gauntlet Hellfire (gauntlet4) with hash: 1934384720
```

The name in parentheses is exactly what the file needs to be called.

## Image format

256x128 pixels, PNG. That's a 2:1 aspect ratio - every image the trainer ships with is sized
this way, and the preview widget expects it (a different aspect ratio will just look stretched
or letterboxed, not broken, but 256x128 is what to aim for).

## Priority order

For a given vehicle, the trainer looks for a preview in this order, using whichever it finds
first:

1. An exact-matching PNG in `Enhanced Native Trainer\previews\` (i.e. what this page is about).
2. A built-in entry for that exact vehicle (most vanilla and DLC vehicles already have one).
3. The closest thing it can find automatically - either a same-family PNG (e.g. `sentinel.png`
   used for `sentinel4` if there's no `sentinel4.png` of its own) or a same-family built-in
   entry, on the reasoning that a related vehicle's picture beats no picture at all.

A PNG you add always wins over a built-in entry for that same vehicle, so you can override any
of the bundled previews just by adding a file with the matching name - no need to remove or
edit anything else first.

## One thing to know about replacing an image mid-session

Once the trainer's looked for a particular vehicle's preview once in a running session (found
or not), it remembers the result for the rest of that session. If you add or replace a PNG for
a vehicle you've already viewed in the spawner this session, you won't see the change until you
restart the trainer (or the game).
