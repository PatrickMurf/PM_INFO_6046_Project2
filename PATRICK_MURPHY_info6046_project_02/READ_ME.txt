=== Build/Run:
-> To build & run the project, run the .sln file, and click "Local Windows Debugger".


=== Controls:
The controls should be fairly intuitive...Mainly because the program displays them, & can remind you at any time.  Regardless, here's a quick rundown & explanation for what isn't as easily explained.

-> The help menu shows up when the project is first loaded; and can be brought up again with 'P'.  It will explain your controls to you.
-> 'O' will show you the current settings for volume, pitch, & pan.  ...Though requires a sound to be currently in progress.

-> Number keys 1 through 4 will play a sound.  You can only have one sound playing at a time.
-> 'Q' will toggle if the sound is played/paused.  (Requires a sound currently active.)
-> 'W' will immediately end a sound from playing.  (Requires a sound currently active.)

-> 'Z' and 'X' control the volume.  You cannot change these without an active sound.
-> 'C' and 'V' control the pitch.  You cannot change these without an active sound.
-> 'B' and 'N' control the pan.  You cannot change these without an active sound.
-> Finally, 'M' will restore to defaults.


=== Play bar:
The play bar will show you how far through a sound you are.  It will display similar to this:

===0------  |  Playback: 1088 / 1764.0

-> The '=' represent the audio you've already heard.
-> The 'O' represents your current position in the audio.
-> The '-' represents the audio you haven't heard.
-> The two numbers after "Playback" show you a numerical representation of your progress.  They represent your current position, and the total length of the audio, respectively.

*Note: I have encountered a glitch where after making an input while paused, the playbar broke and wouldn't show up again.  I don't know what the issue was, and wasn't able to replicate/repeat it.  If this happens, you can fix it by closing out the program, and re-running it.