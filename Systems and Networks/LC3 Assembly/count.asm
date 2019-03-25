.orig x3000

  ld r0, table    ; pointer
  and r1, r1, 0
  and r2, r2, 0   ; i

loop1
  add r7, r2, -10 ; check if i < 10
  brzp quit1
  str r1, r0, 0   ; table[i] = 0
  add r2, r2, 1   ; i++
  add r0, r0, 1   ; pointer++
  br loop1

quit1
  ld r0, array
  ld r1, length
  not r1, r1
  add r1, r1, 1   ; -length
  and r2, r2, 0   ; i
  and r3, r3, 0
  ld r4, table

loop2 
  add r7, r2, r1  ; i - length
  brzp quit2
  ldr r3, r0, 0   ; load array[i]
  add r5, r4, r3  ; &table[index]
  ldr r6, r5, 0   ; load table[index]
  add r6, r6, 1   ; table[index]++
  str r6, r5, 0   ; store table[index]
  add r2, r2, 1   ; i++
  add r0, r0, 1   ; pointer++
  br loop2

quit2
  halt

array
  .fill x6000
length
  .fill 20
table
  .fill x7000
.end

.orig x6000
.fill 1
.fill 2
.fill 3
.fill 4
.fill 5
.fill 6
.fill 7
.fill 8
.fill 9
.fill 0
.fill 1
.fill 2
.fill 4
.fill 4
.fill 5
.fill 6
.fill 7
.fill 8
.fill 9
.fill 0
.end

.orig x7000
.blkw 10
.end
