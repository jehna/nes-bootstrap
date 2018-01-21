; This file only acts as a bridge between the Famitone 2 tracker and the C code.

.export _synchronizeMusicToFrame, _initMusic, _playSong, _stopSong
.import musicData, _famitoneVariablePointer

; Settings:
.define FT_BASE_ADR     $0400	; page in the RAM used for FT2 variables, should be $xx00
.define FT_DPCM_OFF     $c000	; $c000..$ffc0, 64-byte steps
.define FT_SFX_STREAMS  4     ; number of sound effects played at once, 1..4
.define FT_DPCM_ENABLE  0     ; undefine to exclude all DMC code
.define FT_SFX_ENABLE   0     ; undefine to exclude all sound effects code
.define FT_THREAD       1     ; undefine if you are calling sound effects from the same thread as the sound update call
.define FT_PAL_SUPPORT  1     ; undefine to exclude PAL support
.define FT_NTSC_SUPPORT 1     ; undefine to exclude NTSC support

.segment "ZEROPAGE"
FT_TEMP: .res 3	              ; reserve 3 bytes in zeropage used by the library as a scratchpad
.segment "CODE"

.include "../../lib/famitone2.s"

_synchronizeMusicToFrame:
  JMP FamiToneUpdate
  RTS

_initMusic:
  LDA 0
  LDX #<musicData ; low byte
  LDY #>musicData ; high byte
  JMP FamiToneInit
  RTS

_playSong:
  JMP FamiToneMusicPlay
  RTS

_stopSong:
  JMP FamiToneMusicStop
  RTS