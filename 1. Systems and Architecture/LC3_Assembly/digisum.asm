.orig x3000
  ld r6, stack
  ld r0, n
  add r6, r6, -1
  str r0, r6, 0
  jsr digisum
  ldr r0, r6, 0
  add r6, r6, 2
  st r0, answer
  halt

stack
  .fill xf000
n
  .fill 45
answer
  .blkw 1

digisum
  add r6, r6, -3
  str r7, r6, 1
  str r5, r6, 0
  add r5, r6, -1
  add r6, r6, -2 
  ldr r0, r5, 4   ; load n
  and r1, r1, 0
  add r1, r1, 10
  trap x80
  str r0, r6, 1   ; div
  str r1, r6, 0   ; mod
  ldr r3, r5, 4   ; check if n == 0
  brz skip
  add r6, r6, -1
  str r0, r6, 0
  jsr digisum
  ldr r0, r6, 0
  add r6, r6, 2
  ldr r1, r6, 0   ; load mod
  add r3, r1, r0  ; mod + digisum(div)
  str r3, r5, 3
  ldr r7, r5, 2
  add r6, r5, 0
  ldr r5, r5, 1
  add r6, r6, 3
  ret 

skip
  and r3, r3, 0
  str r3, r5, 3
  ldr r7, r5, 2
  add r6, r5, 0
  ldr r5, r5, 1
  add r6, r6, 3
  ret
  
.end
