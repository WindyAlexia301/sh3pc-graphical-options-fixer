SILENT HILL 3 - SAVE "REAL-TIME SHADOW" & "LENS FLARE QUALITY"
=============================================================

WHAT THIS DOES
--------------
Silent Hill 3 (PC) stores these two graphics options in:

    savedata\disp.ini

    shadow           -> "Real-Time Shadow"     (1 = ON,  0 = OFF)
    lensflare_ztest  -> "Lens Flare Quality"   (1 = Detail, 0 = Fast)

On this port those options can reset every time you launch the game.
"Launch SH3 (Save Graphics).bat" fixes that: it writes your chosen
values into disp.ini right before the game starts, so they stick.


HOW TO USE
----------
1. Just run "Launch SH3 (Save Graphics).bat" instead of the game's
   normal shortcut. It applies your settings and then starts the game.

2. Both settings are already set to maximum quality (1 and 1) and have
   also been written into disp.ini directly.


CHANGING THE VALUES
-------------------
Open "Launch SH3 (Save Graphics).bat" in Notepad and edit these lines
near the top:

    set "SHADOW=1"
    set "LENSFLARE=1"

    1 = ON  / Detail  (higher quality)
    0 = OFF / Fast    (better performance)

Save the file, then run it again.


NOTES
-----
- Your resolution, gamma and other display settings are left untouched.
- If the game keeps overwriting the values even with the launcher, you
  can make the file read-only as a last resort:
  right-click savedata\disp.ini > Properties > tick "Read-only".
  (Only do this if the in-game display menu still works for you.)
