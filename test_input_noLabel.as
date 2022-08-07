add r2,STR
macro m1
inc K
mov S1.2 ,r3
endmacro
; comment
macro m2
inc H
mov S1.2 ,r3
endmacro
prn #-5
sub r1, r4
m1
bne LOOP
m2
m1
m2