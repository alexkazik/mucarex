Launcher
========

The Launcher is the menu on the Vectrex which allows you to start games.


Usage
-----

Use the Joystick to switch between categories by pressing left/right and
entries by up/down.

With a press of an outer button (1 or 4) you select an entry, in case of
the main menu it will launch the game.

By pressing an inner button (2 or 3) you switch between the main and sub
menu.


Main Menu
---------

The list of categories and entries is stored in an directory on the
flash. Use vextrecpack to change the entries (see
Docs/User/vectrexpack.md).


Sub Menu
--------

The submenu consists of some pages:

### Game

View some information about the selected game. Including the current
high score and how many data is stored.

### Config

When the high score module is installed (see Docs/User/High-Score.md)
you can here:

* Make the game the selected game on power-up
* En-/Disable high score saving
* Delete the current high score
* Select the launch method for this game (see Settings)
* Delete the custom data

### Settings

Define on how all games should be launched:

* Slow: The original BIOS routines
* Fast: Show the cartridge screen only 1/3rd of the time and don't play music
* Instant: Launch it immediately

### Storage

View some information about the high score module, if installed.
Including used, deleted and free space in the high score/data area on
the flash.

### Credits

View the credits - you have to scroll by yourself ;-)
