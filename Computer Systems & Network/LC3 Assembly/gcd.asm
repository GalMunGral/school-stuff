.orig x3000
  ld r6, stack
  ld r0, a
  ld r1, b
  add r6, r6, -2
  str r0, r6, 0   ; pass in a
  str r1, r6, 1   ; pass in b
  jsr gcd
  ldr r0, r6, 0
  add r6, r6, 3
  st r0, answer
  halt

a
  .fill 20
b
  .fill 16
answer
  .blkw 1
stack
  .fill xf000

gcd
  add r6, r6, -3
  str r7, r6, 1
  str r5, r6, 0
  add r5, r6, -1
  ldr r0, r5, 4   ; load a
  ldr r1, r5, 5   ; load b
  udiv
  add r1, r1, 0   ; check if r1 == 0
  brnp skip
  ldr r0, r5, 5   ; load b
  br return

skip
  add r6, r6, -2
  ldr r0, r5, 5   ; load b
  str r0, r6, 0   ; pass in b
  str r1, r6, 1
  jsr gcd
  ldr r0, r6, 0
  add r6, r6, 3
  br return

return
  str r0, r5, 3
  ldr r7, r5, 2
  add r6, r5, 0
  ldr r5, r5, 1
  add r6, r6, 3
  ret

.end
