.orig x3000

  ld r6, stack
  ld r0, n
  add r6, r6, -1
  str r0, r6, 0   ; pass in n 
  jsr collatz
  ldr r0, r6, 0
  add r6, r6, 2
  st r0, answer 
  halt

n      
  .fill 8
answer  
  .fill 0
stack   
  .fill xf000


collatz
  add r6, r6, -3
  str r7, r6, 1
  str r5, r6, 0
  add r5, r6, -1
  ldr r0, r5, 4   ; n
  add r0, r0, -1  ; n - 1
  brnp skip1
  and r0, r0, 0
  br return

skip1
  ldr r0, r5, 4   ; n
  and r1, r1, 0
  add r1, r1, 2 
  udiv
  add r1, r1, 0
  brnp skip2
  add r6, r6, -1
  str r0, r6, 0 
  jsr collatz
  ldr r0, r6, 0   ; load c
  add r6, r6, 2 
  add r0, r0 ,1   ; c + 1
  br return

skip2 
  ldr r1, r5, 4   ; load n
  and r0, r0, 0
  add r0, r0, r1  ; n
  add r0, r0, r1  ; 2n
  add r0, r0, r1  ; 3n
  add r0, r0, 1   ; m = n * 3 + 1
  add r6, r6, -1
  str r0, r6, 0   ; pass in m
  jsr collatz
  ldr r0, r6, 0   ; load c
  add r6, r6, 2
  add r0, r0, 1   ; c + 1

return
  str r0, r5, 3
  ldr r7, r5, 2
  add r6, r5, 0
  ldr r5, r5, 1
  add r6, r6, 3
  ret

.end
