# prototype-apoc

# Intro
This game is called apoc and is about shooting monsters.

# Video
Check out a video of this game here.

# Screenshots
Check out some photos of this game below.

# Description
Apoc is a 2D-shooter where a player is a flower that must avoid being eaten by monsters. The flower can move and shoot the monsters in order to survive. The objective is to see how long the player (flower) can survive without being eaten by the monsters.

# Contents
This goes over the folders/files in the repository.

- assets: contains the font, sprite, sound, and music materials used

- demo: contains a video about this game

- packages: contains basic sfml build files

- screenshots: contains photos about this game

- src: files that build the game

# Setup
We are assuming that the user knows some basic aspects of SFML and g++.

1.  Download SFML and g++ and make sure both versions match. Otherwise, download the recommended g++ from the SFML Downloads page.

2.  Download the entire repository files

3.  Open the repository in your local text editor or IDE. You may need to set the path of ```dir=packages``` so that your workspace automatically searches the subdirectories of that directory recursively. In VS Code, it can be manually set upon "Quick Fixing".

4.  Switch into the ```dir=src``` and run ```make``` in your terminal of choice.

5.  Run the game using ```./apoc```.

# Controls
__Menu__

```W,S``` or ```Up, Down Arrows```: scrolls menu options

```Enter```: selects the menu option

<br>

__In-Game Controls__

```W,A,S,D``` or ```Up,Left,Right,Down Arrows```: movement for the flower.

```Mouse: Left Click```: flower shoots

```p```: to pause game, ```o```: to unpause game

```i```: to show crosshair, ```u```: to hide crosshair

```y```: to restart game, ```m```: to go back to the menu

```Enter```: to go back to the menu if game over

```esc``` or ```Click [x symbol] of program```: closes the program

# Limitations
These are some features that have not been implemented yet.

__Menu__

- Mouse hover/select menu options
- Title art/custom font
- Background image
- Stats tracked over sessions
- Settings tab: sound, crosshair type/color, fps cap, resolution, or window size. 

<br>

__In-Game__
- Background image
- Sprite animation
- Game over music should happen after player has ran out of health rather than pressing enter.
- Enemy bots with health and/or ability to shoot.
- Special enemy bots, size of projectiles, size of enemy bots.
- Health regen system

# Bugs/Issues
- Pausing then unpausing may cause enemies to become invincible for a few seconds. It is best to avoid pausing overall during deeper progressions.

# Resources
These goes over the external assets and tools used.

__Tools__

- Written in c++ using VS Code

- g++ version 13.1.0 and SFML 2.6.1

- Saved through Git and hosted through GitHub

<br>

__Assets__

- [SFML Setup](https://www.sfml-dev.org/tutorials/2.6/)

- [Player: Fire Flower](https://www.pinterest.com/pin/pixel-fireflower-pin--469429961159390499/)

- [Enemy: Crab Space Invader](https://www.pngkey.com/maxpic/u2w7w7a9y3u2e6e6/)

- [Sound Effects](https://opengameart.org/content/retro-shooter-sound-effects)

- [Main Menu and In-Game Music](https://retro.sx/music/934)