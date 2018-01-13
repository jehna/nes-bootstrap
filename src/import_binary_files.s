; Startup code for cc65/ca65
.export __STARTUP__:absolute=1

.segment "CHARS"
; ⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇⬇ Add your imported sprite files here
  .incbin "sprites/alphabet.chr"