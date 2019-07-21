.orig x3000
  ld r0, num 
  not r0, r0
  add r0, r0, 1
  and r1, r1, 0   ; i
  and r2, r2, 0   ; sum
  ld r3, num      ; n

loop
  add r4, r1, r0  ; i - n
  brzp quit
  add r2, r2, r3  ; sum += n
  add r3, r3, -1  ; n--
  add r1, r1, 1   ; i++
  brnzp loop 

quit
  st r2, num  
  halt

num
  .fill #5
  
.end
