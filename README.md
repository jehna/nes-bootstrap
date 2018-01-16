![NES Bootstrap logo skeleton](https://github.com/jehna/nes-bootstrap/blob/master/logo.png?raw=true)

# NES Programming Bootstrap Project
> Everything to start coding NES games with C

This is a "batteries included" bootstrap project so you can start coding NES in
C. Just read the README and start hacking!

## Getting started

You need to [install CC65
compiler](http://cc65.github.io/cc65/getting-started.html) to your machine. This
compiler is used to compile the C code into NES game.

After you have CC65 installed, just run:

```shell
./compile
```

This will compile all the source files into `game.nes` file that you can open in
your favorite emulator.

## Developing

This project has quite handy development tools that make developing NES games a
lot easier:

- Automatic building via Nodemon file watcher
- JavaScript-based [JSNES](https://github.com/bfirsh/jsnes) emulator that runs
  in browser

### Installing developer tools

You need Node.js installed, because some developer tools (like file watching,
and the web server) are running on top of Node. To install the dev tools, just
run:

```shell
npm install
```

This will download and install all needed development tools for this project.

### Running developer tools

To run the developer tools, just run:

```shell
npm run start
```

This will start the file watcher, web server (that serves the JSNES-based
emulator) and compiles the project automatically.

## Features

Using this project you will be able to:
* Start developing NES games with (close to) zero knowledge of NES
* Have working code for moving sprites, drawing backgrounds and handling user
  input from the first minute
* See updates in seconds via the browser-based emulator
* Use words instead of hex-codes (NO magic numbers!)

This project has been constructed from different how-to's and sample codes.

The "heart" of the project is file called `nes.h`, which is originally converted
from the CC65 project's [nes.inc assembly
file](https://github.com/cc65/cc65/blob/master/asminc/nes.inc) to C, but it has
been filled and modified to include all necessary magic number definitions from
the NES architecture.

## Nice helpers and globals

When you start crafting your own game, just open `main.c` and start hacking.
There are a few convenience functions/macros/variables available for you when
you start hacking more:

#### Sprites
Type: `Sprite[]`  
Import from: `nes/sprite.h`

This is a global array of `Sprite` structs that holds the information of all 64
sprites you can have at your screen at the same time.

Each sprite can be modified at any point (even outside vblank), and they are
copied to Picture Processing Unit automatically once per frame.

Example:
```c
Sprites[0].xPos = 0x80; // Moves sprite in index 0 horizontally to center
```

#### Input
Type: `{ struct ControllerInput player1, struct ControllerInput player2 }`  
Import from: `nes/controller.c`

This reads input from the controllers automatically. You can check the struct
for if the player's controller was pressed during that frame.

Example:
```c
if (Input.player1.A) {
  jump();
}
```

#### SET_16BIT_VALUE_TO_POINTER ( pointer, value )
Type: `macro`  
Import from: `nes.h`

With this helper macro you can set one 16-bit value to a register that only
accepts 8-bit values (like [Picture Processing Unit
Address](https://wiki.nesdev.com/w/index.php/PPU_registers#Address_.28.242006.29_.3E.3E_write_x2)).

Example:
```c
SET_16BIT_VALUE_TO_POINTER(PPU_ADDR, 0x1234)

/**
 * Outputs:
 *  lda     #$12
 *  sta     $4016
 *  lda     #$34
 *  sta     $4016
 */
```

#### SET_PPU_SCROLL ( x, y )
Type: `macro`  
Import from: `nes.h`

Sets Picture Processing Unit's scroll in one function.

Example:
```c
SET_PPU_SCROLL(0,0)

/**
 * Outputs:
 *  lda     #$00
 *  sta     $2006
 *  sta     $2006
 *
 * (omits the unnecessary extra LDA)
 */
```

#### PALETTE_COLOR_ [color]
Type: `constant`  
Import from: `nes.h`

All available colors of the standard palette are available as constants.

Example:
```c
// Sets universal background to black
SET_PPU_ADDR_VALUE(PPU_ADDR_PALETTE_UNIVERSAL_BACKGROUND_COLOR, PALETTE_COLOR_BLACK);
```

## Contributing

If you'd like to contribute, please fork the repository and use a feature
branch. Pull requests are warmly welcome.

This project was initially created for [Global Game
Jam](https://globalgamejam.org/) 2018. It might not be updated a lot after the
jam is over, but I hope some others will also find it useful in the future!

## Licensing

The code in this project is licensed under MIT license.
