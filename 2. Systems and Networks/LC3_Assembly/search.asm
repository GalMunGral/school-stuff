.orig x3000
  and r0, r0, 0   ; counter
  and r1, r1, 0   ; result
  ld r2, array    ; pointer
  ld r3, number 
  not r3, r3
  add r3, r3, 1   ; -number 
  ld r4, length 
  not r4, r4  
  add r4, r4, 1   ; -length

loop
  add r5, r0, r4  ; counter - length
  brzp quit
  ldr r5, r2, 0   ; array[counter]
  add r5, r5, r3  ; array[counter] - number
  brz found
  add r0, r0, 1   ; counter++
  add r2, r2, 1   ; pointer++
  brnzp loop

found
  add r1, r1, 1   ; set result to 1

quit
  st  r1, result
  halt

array
  .fill x6000
length
  .fill 20
number
  .fill 15
result
  .fill 0
  
.end

.orig x6000
.fill 1
.fill 2
.fill 733
.fill 44
.fill 9
.fill 7
.fill 12
.fill 80
.fill 3
.fill 64
.fill 21
.fill 10
.fill 90
.fill 7
.fill 15
.fill 12
.fill 377
.fill 65
.fill 7
.fill 42
.end
