/**
 * NES definitions. By Groepaz/Hitmem.
 */

// FIXME: optimize zeropage usage

#define SCREEN_PTR      *((unsigned char *)0x62)           // 2
#define CRAM_PTR        *((unsigned char *)0x64)           // 2
#define CHARCOLOR       *((unsigned char *)0x66)
#define BGCOLOR         *((unsigned char *)0x67)
#define RVS             *((unsigned char *)0x68)
#define CURS_X          *((unsigned char *)0x69)
#define CURS_Y          *((unsigned char *)0x6a)

#define tickcount       *((unsigned char *)0x6b)           // 2

#define VBLANK_FLAG     *((unsigned char *)0x70)

#define ringbuff        *((unsigned char *)0x0200)
#define ringwrite       *((unsigned char *)0x71)
#define ringread        *((unsigned char *)0x72)
#define ringcount       *((unsigned char *)0x73)

#define ppuhi           *((unsigned char *)0x74)
#define ppulo           *((unsigned char *)0x75)
#define ppuval          *((unsigned char *)0x76)

#define screenrows      (30-1)
#define charsperline    32
#define xsize           charsperline

// PPU defines

#define PPU_CTRL        *((unsigned char *)0x2000)
#define PPU_MASK        *((unsigned char *)0x2001)
#define PPU_STATUS      *((unsigned char *)0x2002)
#define PPU_SPR_ADDR    *((unsigned char *)0x2003)
#define PPU_SPR_IO      *((unsigned char *)0x2004)
#define PPU_SCROLL      *((unsigned char *)0x2005)
#define PPU_ADDR        *((unsigned char *)0x2006)
#define PPU_VRAM_IO     *((unsigned char *)0x2007)

// APU defines

#define APU_PULSE1CTRL  *((unsigned char *)0x4000)         // Pulse #1 Control Register (W)
#define APU_PULSE1RAMP  *((unsigned char *)0x4001)         // Pulse #1 Ramp Control Register (W)
#define APU_PULSE1FTUNE *((unsigned char *)0x4002)         // Pulse #1 Fine Tune (FT) Register (W)
#define APU_PULSE1CTUNE *((unsigned char *)0x4003)         // Pulse #1 Coarse Tune (CT) Register (W)
#define APU_PULSE2CTRL  *((unsigned char *)0x4004)         // Pulse #2 Control Register (W)
#define APU_PULSE2RAMP  *((unsigned char *)0x4005)         // Pulse #2 Ramp Control Register (W)
#define APU_PULSE2FTUNE *((unsigned char *)0x4006)         // Pulse #2 Fine Tune Register (W)
#define APU_PULSE2STUNE *((unsigned char *)0x4007)         // Pulse #2 Coarse Tune Register (W)
#define APU_TRICTRL1    *((unsigned char *)0x4008)         // Triangle Control Register #1 (W)
#define APU_TRICTRL2    *((unsigned char *)0x4009)         // Triangle Control Register #2 (?)
#define APU_TRIFREQ1    *((unsigned char *)0x400A)         // Triangle Frequency Register #1 (W)
#define APU_TRIFREQ2    *((unsigned char *)0x400B)         // Triangle Frequency Register #2 (W)
#define APU_NOISECTRL   *((unsigned char *)0x400C)         // Noise Control Register #1 (W)
// #define APU_ *((unsigned char *)0x400D)  // Unused (???)
#define APU_NOISEFREQ1  *((unsigned char *)0x400E)         // Noise Frequency Register #1 (W)
#define APU_NOISEFREQ2  *((unsigned char *)0x400F)         // Noise Frequency Register #2 (W)
#define APU_MODCTRL     *((unsigned char *)0x4010)         // Delta Modulation Control Register (W)
#define APU_MODDA       *((unsigned char *)0x4011)         // Delta Modulation D/A Register (W)
#define APU_MODADDR     *((unsigned char *)0x4012)         // Delta Modulation Address Register (W)
#define APU_MODLEN      *((unsigned char *)0x4013)         // Delta Modulation Data Length Register (W)
#define APU_SPR_DMA     *((unsigned char *)0x4014)         // Sprite DMA Register (W)
#define APU_CHANCTRL    *((unsigned char *)0x4015)         // Sound/Vertical Clock Signal Register (R)
#define APU_PAD1        *((unsigned char *)0x4016)         // Joypad #1 (RW)
#define APU_PAD2        *((unsigned char *)0x4017)         // Joypad #2/SOFTCLK (RW)


#define CH_HLINE        11
#define CH_VLINE        14
#define CH_ULCORNER     176
#define CH_URCORNER     174
#define CH_LLCORNER     173
#define CH_LRCORNER     189
#define CH_TTEE         178
#define CH_RTEE         179
#define CH_BTEE         177
#define CH_LTEE         171
#define CH_CROSS        123
#define CH_CURS_UP      145
#define CH_CURS_DOWN    17
#define CH_CURS_LEFT    157
#define CH_CURS_RIGHT   29
#define CH_PI           126
#define CH_DEL          20
#define CH_INS          148
#define CH_ENTER        10
#define CH_STOP         3
#define CH_ESC          27


/**
 * PPU_CTRL flags
 * http://wiki.nesdev.com/w/index.php/PPU_registers#PPUCTRL
 */

#define PPU_CTRL_FLAG_NAMETABLE_ADDRESS_2000            0x0
#define PPU_CTRL_FLAG_NAMETABLE_ADDRESS_2400            0x1
#define PPU_CTRL_FLAG_NAMETABLE_ADDRESS_2800            0x2
#define PPU_CTRL_FLAG_NAMETABLE_ADDRESS_2C00            0x3
#define PPU_CTRL_FLAG_VRAM_ADDRESS_INCREMENT_HORIZONTAL 0x0 << 2
#define PPU_CTRL_FLAG_VRAM_ADDRESS_INCREMENT_VERTICAL   0x1 << 2
#define PPU_CTRL_FLAG_SPRITE_TABLE_ADDRESS_0000         0x0 << 3
#define PPU_CTRL_FLAG_SPRITE_TABLE_ADDRESS_1000         0x1 << 3
#define PPU_CTRL_FLAG_BG_TABLE_ADDRESS_0000             0x0 << 4
#define PPU_CTRL_FLAG_BG_TABLE_ADDRESS_1000             0x1 << 4
#define PPU_CTRL_FLAG_SPRITE_SIZE_8x8                   0x0 << 5
#define PPU_CTRL_FLAG_SPRITE_SIZE_8x16                  0x1 << 5
#define PPU_CTRL_FLAG_MASTER                            0x0 << 6 // PPU master/slave select: Read backdrop from EXT pins
#define PPU_CTRL_FLAG_SLAVE                             0x1 << 6 // PPU master/slave select: Output color on EXT pins
#define PPU_CTRL_FLAG_GENERATE_NMI_AT_VBI               0x1 << 7 // Generate non-maskable interrupt at the start of the vertical blanking interval (0: off; 1: on)

/**
 * PPU_MASK flags
 * http://wiki.nesdev.com/w/index.php/PPU_registers#Mask_.28.242001.29_.3E_write
 */

#define PPU_MASK_FLAG_NORMAL_COLOR          0x0
#define PPU_MASK_FLAG_GRAYSCALE             0x1
#define PPU_MASK_FLAG_HIDE_LEFT_8PX_BG      0x0 << 1
#define PPU_MASK_FLAG_SHOW_LEFT_8PX_BG      0x1 << 1
#define PPU_MASK_FLAG_HIDE_LEFT_8PX_SPRITES 0x0 << 2
#define PPU_MASK_FLAG_SHOW_LEFT_8PX_SPRITES 0x1 << 2
#define PPU_MASK_FLAG_HIDE_BG               0x0 << 3
#define PPU_MASK_FLAG_SHOW_BG               0x1 << 3
#define PPU_MASK_FLAG_HIDE_SPRITES          0x0 << 4
#define PPU_MASK_FLAG_SHOW_SPRITES          0x1 << 4
#define PPU_MASK_FLAG_EMPHASIZE_RED         0x1 << 5
#define PPU_MASK_FLAG_EMPHASIZE_GREEN       0x1 << 6
#define PPU_MASK_FLAG_EMPHASIZE_BLUE        0x1 << 7
#define PPU_MASK_FLAG_SHOW_ALL              PPU_MASK_FLAG_SHOW_LEFT_8PX_BG | PPU_MASK_FLAG_SHOW_LEFT_8PX_SPRITES | PPU_MASK_FLAG_SHOW_BG | PPU_MASK_FLAG_SHOW_SPRITES
#define PPU_MASK_FLAG_SCREEN_OFF            0x0

// Helper macros for setting two values to pointer
#define SET_TWO_VALUES_TO_POINTER(POINTER, VALUE1, VALUE2) POINTER = VALUE1; POINTER = VALUE2
#define SET_16BIT_VALUE_TO_POINTER(POINTER, VALUE) SET_TWO_VALUES_TO_POINTER (POINTER, (VALUE & 0xFF00) >> 8, VALUE & 0xFF)
#define SET_PPU_ADDR(VALUE) SET_16BIT_VALUE_TO_POINTER (PPU_ADDR, VALUE)
#define SET_PPU_ADDR_VALUE(ADDRESS, VALUE) SET_PPU_ADDR(ADDRESS); PPU_VRAM_IO = VALUE
#define SET_PPU_SCROLL(X_VALUE, Y_VALUE) SET_TWO_VALUES_TO_POINTER (PPU_SCROLL, X_VALUE, Y_VALUE)

/**
 * PPU Memory map addresses
 * http://wiki.nesdev.com/w/index.php/PPU_memory_map
 */
#define PPU_ADDR_PATTERN_TABLE_0      0x0000
#define PPU_ADDR_PATTERN_TABLE_1      0x1000
#define PPU_ADDR_NAMETABLE_0          0x2000
#define PPU_ADDR_NAMETABLE_1          0x2400
#define PPU_ADDR_NAMETABLE_2          0x2800
#define PPU_ADDR_NAMETABLE_3          0x2C00
#define PPU_ADDR_MIRRORS_OF_2000_2EFF 0x3000
#define PPU_ADDR_MIRRORS_OF_3F00_3F1F 0x3F20

/**
 * PPU Palette addresses:
 * http://wiki.nesdev.com/w/index.php/PPU_palettes
 */
#define PPU_ADDR_PALETTE_UNIVERSAL_BACKGROUND_COLOR 0x3F00
#define PPU_ADDR_PALETTE_BACKGROUND_0               0x3F01
#define PPU_ADDR_PALETTE_BACKGROUND_1               0x3F05
#define PPU_ADDR_PALETTE_BACKGROUND_2               0x3F09
#define PPU_ADDR_PALETTE_BACKGROUND_3               0x3F0D
#define PPU_ADDR_PALETTE_SPRITE_0                   0x3F11
#define PPU_ADDR_PALETTE_SPRITE_1                   0x3F15
#define PPU_ADDR_PALETTE_SPRITE_2                   0x3F19
#define PPU_ADDR_PALETTE_SPRITE_3                   0x3F1D

#define PALETTE_COLOR_BLACK      0x0F
#define PALETTE_COLOR_DARK_GRAY  0x00
#define PALETTE_COLOR_LIGHT_GRAY 0x10
#define PALETTE_COLOR_WHITE      0x20
#define PALETTE_COLOR_BLUE       0x12
#define PALETTE_COLOR_FUCHIA     0x14
#define PALETTE_COLOR_RED        0x16
#define PALETTE_COLOR_ORANGE     0x17
#define PALETTE_COLOR_OLIVE      0x18
#define PALETTE_COLOR_GREEN      0x1A
#define PALETTE_COLOR_CYAN       0x1C
#define PALETTE_COLOR_NAVY       0x02
#define PALETTE_COLOR_MAROON     0x06
#define PALETTE_COLOR_BLUE       0x12
#define PALETTE_COLOR_PURPLE     0x14
#define PALETTE_COLOR_BROWN      0x17
#define PALETTE_COLOR_OLIVE      0x18
#define PALETTE_COLOR_GREEN      0x1A
#define PALETTE_COLOR_AQUA       0x1C
#define PALETTE_COLOR_MAGENTA    0x24
#define PALETTE_COLOR_LIME       0x2A
#define PALETTE_COLOR_TEAL       0x2C

/**
 * Assembly macros for readability
 */
#define RETURN_FROM_INTERRUPT() asm("RTI");
#define DISABLE_IRQ_INTERRUPT() asm("SEI");
#define DISABLE_DECIMAL_MODE() asm("CLD");

#define DOS_END_OF_FILE 0x1A
#define NES_FILE_HEADER(PRG_ROM_SIZE_KB, CHR_ROM_SIZE_KB) \
  'N', 'E', 'S', DOS_END_OF_FILE, \
  PRG_ROM_SIZE_KB / 16, \
  CHR_ROM_SIZE_KB / 8
  // TODO: The full iNES file format header:
  // https://wiki.nesdev.com/w/index.php/INES#iNES_file_format

/**
 * Sprite flags
 */
#define SPRITE_FLAG_USE_PALETTE_1     0
#define SPRITE_FLAG_USE_PALETTE_2     1
#define SPRITE_FLAG_USE_PALETTE_3     2
#define SPRITE_FLAG_USE_PALETTE_4     3
#define SPRITE_FLAG_BEHIND_BACKGROUND 1 << 5
#define SPRITE_FLAG_FLIP_HORIZONTALLY 1 << 6
#define SPRITE_FLAG_FLIP_VERTICALLY   1 << 7