mov
  mov #-5 ,r3
mov #-5 ,r3
MAIN: mov S1.1 ,LENGTH
 add r2,STR
 LOOP: jmp END
 macro m1
 inc K
 mov S1.2 ,#3
 endmacro
 mov r1 ,S1.2
prn #-5
sub r1, r4
m1
bne LOOP
mov K ,r3
 mov #-5 ,K
END: hlt
.extern LOOP
STR: .string "abcdef"
LENGTH: .data 6,-9,15
K: .data 22
.struct 8, "ab"
S1: .struct 8, "ab" 
