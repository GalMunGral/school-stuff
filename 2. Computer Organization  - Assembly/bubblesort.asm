.orig x3000
  and r0, r0, 0   ; init counter
  ld  r1, length 
  not r1, r1  
  add r1, r1, 1

loop0
  ld r2, array    ; init pointer
  add r2, r2, 1
  add r3, r1, r0
  brzp quit0
  and r4, r4, 0   ; reset flag
  add r4, r4, 1
  and r5, r5, 0   ; reset counter 
  add r5, r5, 1

loop1
  add r3, r5, r1
  add r3, r3, r0  ; i-(length-k)
  brzp quit1
  ldr r6, r2, 0   ; array[i]
  ldr r7, r2, -1  ; array[i-1]
  not r3, r7
  add r3, r3, 1
  add r3, r3, r6  ; array[i] - array[i-1]
  brzp skip
  str r7, r2, 0   ; swap
  str r6, r2, -1 
  and r4, r4, 0   ; clear flag

skip
  add r2, r2, 1   ; pointer++
  add r5, r5, 1   ; counter++
  brnzp loop1

quit1
  add r4, r4, 0   ; check flag
  brp loop0 
  add r0, r0, 1   ; counter++
  brnzp loop0

quit0
  halt

array
  .fill x6000

length
  .fill 12

.end

.orig x6000
  .fill 28
  .fill -50
  .fill 7
  .fill 2
  .fill 42
  .fill 4
  .fill 15
  .fill -8
  .fill 34
  .fill 101
  .fill -5
  .fill 250
.end
