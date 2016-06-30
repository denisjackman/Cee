# Game
======
This holds the code and notes for a rough game idea I have.
I will do this in C++. Using Travis CI and Coverall as tools to run the project. Maybe trello too.

# Badges
========
* Game      : ![Game Status](https://img.shields.io/badge/game-progressing-yellow.svg)
* Coveralls : [![Coverage Status](https://coveralls.io/repos/github/denisjackman/game/badge.svg?branch=master)](https://coveralls.io/github/denisjackman/game?branch=master)
* Travis CI : [![Build Status](https://travis-ci.org/denisjackman/game.svg?branch=master)](https://travis-ci.org/denisjackman/game)
* Coverity  : <a href="https://scan.coverity.com/projects/denisjackman-game"><img alt="Coverity Scan Build Status"src="https://scan.coverity.com/projects/9143/badge.svg"/></a>

## Version History 
|Date |Author|Version|Reason|
|----------|-------------|-----|--------------------------------------|
|2016-05-12|Denis Jackman|01.00|Original Version |
|2016-05-17|Denis Jackman|02.00|Converted to CPP only project |
|2016-05-18|Denis Jackman|02.01|Added SDL libraries and Slack notification |
|2016-05-20|Denis Jackman|02.02|Added ccppunit libraries and coverall |
|2016-05-27|Denis Jackman|02.03|Added numerous functions to the library |
|2016-06-07|Denis Jackman|02.04|Added more detail to the reference mark down pages |
|2016-06-14|Denis Jackman|02.05|Added in Coverity and kings game |

## TODO
* Start coding part 8 of the tutorials 
* Overlay the Maze array with rooms (create a function to do so )
* Make sure the Maze is sane (all rooms connect to each other)
* Add Maze furniture (Doors, Stairs (up and down)) or do we treat these as objects
* Display the Maze in the game
* Let the Character walk around the maze
* How do levels work
* Add monsters
* Add fighting
* Add treasure drops
* Add other objects
* Look at NetHack code - http://git.code.sf.net/p/nethack/NetHack - (maybe fork it )
* Look at Angbad code  - https://github.com/angband/angband/tree/AngbandBase - (maybe fork it )
* fix -  --- Starting ---
Unable to create texture from files/texture.png! SDL Error: Invalid renderer
Failed to load texture image!
Game failed to load media !


## Links
* [Game Programming](http://gameprogrammingpatterns.com/)
* [Genetic Algorithims](http://www.ai-junkie.com/ga/intro/gat1.html)
* [GIT Tutorials](https://www.atlassian.com/git/tutorials/what-is-version-control)
* [Rogue Like Tutorial](http://www.kathekonta.com/rlguide/)
* [Rogue Like Tutorial](https://solarianprogrammer.com/2012/07/12/roguelike-game-cpp-11-part-0/)
* [Source to look at](https://github.com/sol-prog/roguelike)
* [Roguelike DEV](http://www.roguebasin.com/index.php?title=Roguelike_Dev_FAQ)
* [Roguelike in 15 steps](http://www.roguebasin.com/index.php?title=How_to_Write_a_Roguelike_in_15_Steps)
* [Map](http://www.roguebasin.com/index.php?title=Grid_Based_Dungeon_Generator)
* [Angband](http://rephial.org/)
* [Anmgband Source](https://github.com/angband/angband/tree/AngbandBase)
* [NetHack](http://www.nethack.org/)
* [Cataclysm DDA](https://github.com/CleverRaven/Cataclysm-DDA)
* [0AD](https://gitlab.com/0ad)
* [Moria](http://beej.us/moria/)

## Games Reference 
* [Lists](http://roll1d12.blogspot.co.uk/)
* [Lists](http://drumsofwar.wikia.com/wiki/Drums_of_War_Wiki)
* [Dungeon Building](http://roguelikedeveloper.blogspot.co.uk/2007/11/unangband-dungeon-generation-part-one.html)
* [Rooms](http://journal.stuffwithstuff.com/2014/12/21/rooms-and-mazes/)
* [Maps](https://endevagames.wordpress.com/2015/05/29/randomly-generated-maps/)
* [Maps](http://divingintodart.blogspot.co.uk/2015/01/procedural-generation-part-one-making.html)

## Forums/Groups 
* [Temple of the Roguelike](http://forums.roguetemple.com/index.php)
* [Angband Forum](http://angband.oook.cz/forum/index.php)

### Tools 
* [Github](https://github.com/)
* [Gitlab](https://gitlab.com/)
* [Trello](https://trello.com/b/pCvSF4QZ/games-project)
* [Freedcamp](https://freedcamp.com/dashboard)
* [Travis CI](https://travis-ci.org/profile/denisjackman)
* [Coverall](https://coveralls.io/repos)
* [Linux Journey](https://linuxjourney.com)
* [Binary converter](http://www.unit-conversion.info/texttools/convert-text-to-binary/)
* [Coverity](https://scan.coverity.com/projects/denisjackman-game)
* [Shields IO](http://shields.io/)
* [Open Dash](https://open.cdash.org)
* [Bit Bucket](https://bitbucket.org)
* [TileEd](http://www.mapeditor.org/)
* [tinyxml2](http://www.grinninglizard.com/tinyxml2/index.html)
* [tonyxml](http://www.grinninglizard.com/tinyxml/)
* [json](https://github.com/nlohmann/json)

### C++ Links
* [SDL Library](https://www.libsdl.org/index.php)
* [Codeblocks IDE](http://www.codeblocks.org/)
* [MiniGW](http://www.mingw.org/)
* [SDL Tutorials](http://lazyfoo.net/SDL_tutorials/)
* [SDL Tutorials](http://www.sdltutorials.com/)
* [SDL Tutorials](http://www.willusher.io/pages/sdl2/)
* [SDL Tutorials](http://gamedevgeek.com/tutorials/getting-started-with-sdl/)
* [more SDL Tutorials](http://www.sdltutorials.com/)
* [SDL and Codeblocks](http://wiki.codeblocks.org/index.php/Using_SDL_with_Code::Blocks)
* [Aaron's Games Programming(SDL)](http://aaroncox.net/tutorials/2dtutorials/index.html)
* [SDL 1.2 to 2.0 porting](http://blog.stuff-o-matic.com/post/2013/09/15/ASGP-s-Android-Port-Part-II%3A-from-SDL-1.2-to-SDL-2.)
* [SDL 1.2 to 2.0 Migration](https://wiki.libsdl.org/MigrationGuide)
* [SDL 1.2 to 2.0 Migration](http://www.cs.umb.edu/~bazz/cms/index.php?id=sdl-sdl2-migration-experience)
* [More SDL Tutorials](http://www.willusher.io/pages/sdl2/)
* [SDL-1.2:Sprite SDL](http://gamedevgeek.com/tutorials/moving-sprites-with-sdl/)
* [SDL-1.2:Animated Sprites](http://gamedevgeek.com/tutorials/animating-sprites-with-sdl/)
* [OPENGL and SDL](http://headerphile.com/)
* [SDL TTF](http://www.sdltutorials.com/sdl-ttf)

## Books 
* Game Programming in C++ 
* Focus on SDL
* Programming Linux Games
* Beginning C++ Game Programming
* C++ For Game Programmers.
* Design Patterns 

## Branches 
* new-feature-test (from the work machine)

## Licence 
<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
