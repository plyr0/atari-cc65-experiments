.global _waitvblank

CLOCK = $14

_waitvblank:
    lda CLOCK
wvb:
    cmp CLOCK
    beq wvb
    rts
