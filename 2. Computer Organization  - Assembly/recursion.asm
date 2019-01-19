.orig x3000
  ld r6, stack
  ld r0, curr_head  ; put head address on stack
  add r6, r6, -1
  str r0, r6, 0
  jsr reverse_sum   ; call reversesum 
  ldr r0, r6, 0     ; load return value
  add r6, r6, 2     ; clear stack
  st r0, sum        ; store sum
  halt

curr_head
  .fill head1
sum
  .blkw 1
stack
  .fill xf000


reverse_sum
  add r6, r6, -3
  str r7, r6, 1
  str r5, r6, 0
  add r5, r6, -1
  add r6, r6, -1    ; local variable sum

  ldr r0, r5, 4     ; load ptr
  brnp skip1
  and r0, r0, 0     ; 0
  br return

skip1
  ldr r1, r0, 1     ; next = mem[ptr +1]
  add r6, r6, -1
  str r1, r6, 0
  jsr reverse_sum
  ldr r2, r6, 0     ; load sum
  add r6, r6, 2
  ldr r0, r5, 4     ; load ptr
  ldr r3, r0, 0     ; mem[ptr]
  add r2, r2, r3    ; sum += mem[ptr]
  str r2, r6, 0     ; store sum
  add r6, r6, -1
  str r2, r6, 0;
  ld r0, print_addr
  jsrr r0           ; print(sum)
  add r6, r6, 2
  ldr r0, r6, 0     ; load sum
  br return

return 
  str r0, r5, 3
  ldr r7, r5, 2
  add r6, r5, 0
  ldr r5, r5, 1
  add r6, r6, 3
  ret

print_addr
  .fill print

.end


; the linked-list nodes

.orig x4000
head1 
  .fill 5
  .fill x4004
.end

.orig x4004
  .fill 3
  .fill x4008
.end

.orig x4008
  .fill 2
  .fill x400c
.end

.orig x400c
  .fill 9
  .fill x4010
.end

.orig x4010
  .fill 0
  .fill x4014
.end

.orig x4014
  .fill 3
  .fill x0
.end

.orig x4040

head2
  .fill 10
  .fill 
  .end
