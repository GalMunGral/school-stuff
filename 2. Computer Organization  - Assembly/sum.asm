.orig x3000

  ld r1, x
  ld r2, y
  add r3, r1, r2
  lea r0, hello
  puts
  add r0, r3, 15
  add r0, r0, 15
  add r0, r0, 15
  add r0, r0, 3   ; convert the sum into ascii code.
  out
  halt

hello
  .stringz "the sum is: "
x 
  .fill 2
y 
  .fill 3

.end
