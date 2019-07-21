.orig x3000
  and r0, r0, 0   ; quotient = 0
  and r1, r1, 0   ; remainder = 0
  ld r2, b
  brz skip        ; check if b == 0
  not r2, r2  
  add r2, r2, 1   ; -b
  ld r1, a        ; remainder = a

loop
  add r3, r1, r2  ; a - b
  brn output  
  add r0, r0, 1   ; quotient++
  add r1, r1, r2  ; a -= b
  brnzp loop

skip
  add r0, r0, -1

output
  st  r0, quotient
  st  r1, remainder
  halt

a
  .fill 1
b 
  .fill 2
quotient
  .fill 2
remainder
  .fill 2
  
.end
