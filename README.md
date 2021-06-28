TES3MP
======

Copyright (c) 2008-2021, OpenMW Team  
Copyright (c) 2016-2020, David Cernat & Stanislav Zhukov

[![Build Status](https://travis-ci.org/TES3MP/openmw-tes3mp.svg?branch=0.7.0)](https://travis-ci.org/TES3MP/openmw-tes3mp)

TES3MP is a project adding multiplayer functionality to [OpenMW](https://github.com/OpenMW/openmw), an open-source game engine that supports playing "The Elder Scrolls III: Morrowind" by Bethesda Softworks.

* TES3MP version: 0.7.1
* OpenMW version: 0.48.0
* License: GPLv3 (see [LICENSE](https://gitlab.com/OpenMW/openmw/-/raw/master/LICENSE) for more information)
* IRC: #openmw on irc.libera.chat

Font Licenses:
* DejaVuLGCSansMono.ttf: custom (see [files/mygui/DejaVuFontLicense.txt](https://gitlab.com/OpenMW/openmw/-/raw/master/files/mygui/DejaVuFontLicense.txt) for more information)

Project status
--------------

[Version changelog](https://github.com/TES3MP/openmw-tes3mp/blob/master/tes3mp-changelog.md)

As of version 0.7.x, TES3MP is fully playable, providing very extensive player, NPC, world and quest synchronization, as well as state saving and loading, all of which are highly customizable via [serverside Lua scripts](https://github.com/TES3MP/CoreScripts).

Remaining gameplay problems mostly relate to AI and the synchronization of clientside script variables.

Donations
---------------

You can benefit the project by donating on Patreon to our two developers, [David Cernat](https://www.patreon.com/davidcernat) and [Koncord](https://www.patreon.com/Koncord), as well as by supporting [OpenMW](https://openmw.org).

Contributing
---------------

Helping us with documentation, bug hunting and video showcases is always greatly appreciated.

For code contributions, it's best to start out with modestly sized fixes and features and work your way up. There are so many different possible implementations of more major features – many of which would cause undesirable code or vision conflicts with OpenMW – that those should be talked over in advance with the existing developers before effort is spent on them.

Feel free to contact the [team members](https://github.com/TES3MP/openmw-tes3mp/blob/master/tes3mp-credits.md) for any questions you might have.

Getting started
---------------

* [Quickstart guide](https://github.com/TES3MP/openmw-tes3mp/wiki/Quickstart-guide)
* [Steam group](https://steamcommunity.com/groups/mwmulti) and its [detailed FAQ](https://steamcommunity.com/groups/mwmulti/discussions/1/353916184342480541/)
* [TES3MP section on OpenMW forums](https://forum.openmw.org/viewforum.php?f=45)
* [Discord server](https://discord.gg/ECJk293)
* [Subreddit](https://www.reddit.com/r/tes3mp)
* [Known issues and bug reports](https://github.com/TES3MP/openmw-tes3mp/issues)

The data path
-------------

The data path tells OpenMW where to find your Morrowind files. If you run the launcher, OpenMW should be able to pick up the location of these files on its own, if both Morrowind and OpenMW are installed properly (installing Morrowind under WINE is considered a proper install).

Command line options
--------------------

    Syntax: openmw <options>
    Allowed options:
      --help                                print help message
      --version                             print version information and quit
      --data arg (=data)                    set data directories (later directories
                                            have higher priority)
      --data-local arg                      set local data directory (highest
                                            priority)
      --fallback-archive arg (=fallback-archive)
                                            set fallback BSA archives (later
                                            archives have higher priority)
      --resources arg (=resources)          set resources directory
      --start arg                           set initial cell
      --content arg                         content file(s): esm/esp, or
                                            omwgame/omwaddon
      --no-sound [=arg(=1)] (=0)            disable all sounds
      --script-verbose [=arg(=1)] (=0)      verbose script output
      --script-all [=arg(=1)] (=0)          compile all scripts (excluding dialogue
                                            scripts) at startup
      --script-all-dialogue [=arg(=1)] (=0) compile all dialogue scripts at startup
      --script-console [=arg(=1)] (=0)      enable console-only script
                                            functionality
      --script-run arg                      select a file containing a list of
                                            console commands that is executed on
                                            startup
      --script-warn [=arg(=1)] (=1)         handling of warnings when compiling
                                            scripts
                                            0 - ignore warning
                                            1 - show warning but consider script as
                                            correctly compiled anyway
                                            2 - treat warnings as errors
      --script-blacklist arg                ignore the specified script (if the use
                                            of the blacklist is enabled)
      --script-blacklist-use [=arg(=1)] (=1)
                                            enable script blacklisting
      --load-savegame arg                   load a save game file on game startup
                                            (specify an absolute filename or a
                                            filename relative to the current
                                            working directory)
      --skip-menu [=arg(=1)] (=0)           skip main menu on game startup
      --new-game [=arg(=1)] (=0)            run new game sequence (ignored if
                                            skip-menu=0)
      --fs-strict [=arg(=1)] (=0)           strict file system handling (no case
                                            folding)
      --encoding arg (=win1252)             Character encoding used in OpenMW game
                                            messages:

                                            win1250 - Central and Eastern European
                                            such as Polish, Czech, Slovak,
                                            Hungarian, Slovene, Bosnian, Croatian,
                                            Serbian (Latin script), Romanian and
                                            Albanian languages

                                            win1251 - Cyrillic alphabet such as
                                            Russian, Bulgarian, Serbian Cyrillic
                                            and other languages

                                            win1252 - Western European (Latin)
                                            alphabet, used by default
      --fallback arg                        fallback values
      --no-grab                             Don't grab mouse cursor
      --export-fonts [=arg(=1)] (=0)        Export Morrowind .fnt fonts to PNG
                                            image and XML file in current directory
      --activate-dist arg (=-1)             activation distance override
      --random-seed arg (=<impl defined>)   seed value for random number generator
