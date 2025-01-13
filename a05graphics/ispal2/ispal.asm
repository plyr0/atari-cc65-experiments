; http://atariki.krap.pl/index.php/Programowanie:_Jak_wykry%C4%87_system_TV

.global _ispal

VCOUNT = $D40B

_ispal: ldx VCOUNT
        bpl _ispal  ; 0-127
sync2:  txa         ; keep last vcount in the A
        ldx VCOUNT
        bmi sync2   ; do while 128-255(bit 7 set, negative number); zero ends
        rts
      
; return max vcount to cc65/llvm-mos through accumulator
