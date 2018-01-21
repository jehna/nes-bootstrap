.export musicData

.segment "CHARS"
; ⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇ Add your imported sprite files here
  .incbin "sprites/alphabet.chr"

.segment "RODATA"
musicData:
  .include "sounds/TestMusic.s"
