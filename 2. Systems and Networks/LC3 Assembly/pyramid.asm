.orig x3000

  and r0, r0, 0
  ld r1, levels   
  and r2, r2, 0
  add r2, r2, 1   ; current = 1
  not r3, r2  
  add r3, r3, 1   ; -current
  add r3, r3, r1  ; init spaces
  and r4, r4, 0
  add r4, r4, 1   ; stars = 1
  and r5, r5, 0   ; init counter

loop0
  not r6, r1 
  add r6, r6, 1   ; -level
  add r6, r6, r2  ; current - level
  brp quit0

loop1
  not r6, r3  
  add r6, r6, 1   ; -spaces
  add r6, r6, r5  ; counter - spaces
  brzp quit1
  ld r0, space 
  out             ; print " "
  add r5, r5, 1   ; counter++
  brnzp loop1 

quit1
  and r5, r5, 0   ; clear counter
  add r3, r3, -1  ; space--;

loop2
  not r6, r4  
  add r6, r6, 1   ; -stars
  add r6, r6, r5  ; counter-stars
  brzp quit2
  ld r0, astrsk 
  out             ; print "*"
  add r5, r5, 1   ; counter++
  brnzp loop2

quit2
  lea r0, newln
  puts            ; print "\n"
  and r5, r5, 0   ; clear counter
  add r4, r4, 2   ; stars += 2
  add r2, r2, 1   ; current++
  brnzp loop0

quit0
  halt

levels
  .fill 10
astrsk
  .fill x002a
space
  .fill x0020
newln
  .stringz "\n"
  
.end
