.orig x3000
  ld r6, stack

  ;; test

  halt

; ======================== PARSE_INT ========================
parse_int
  add r6, r6, -3
  str r7, r6, 1
  str r5, r6, 0
  add r5, r6, -1
  add r6, r6, -2
  and r1, r1, 0
  str r1, r6, 1   ; result = 0
  str r1, r6, 0   ; ishex = 0
  getc
  out
  ld r1, x
  not r1, r1
  add r1, r1, 1   ; -'x'
  add r1, r1, r0  ; r0 - 'x'
  brnp pi_loop
  and r2, r2, 0
  add r2, r2, 1
  str r2, r6, 0   ; ishex = 1
  getc
  out

pi_loop
  and r3, r3, 0   ; init parsed
  ldr r1, r6, 0   ; load ishex
  brnp pi_skip1
  ldr r2, r6, 1   ; load result
  add r6, r6, -2 
  str r2, r6, 0   ; pass in result
  str r0, r6, 1
  ld r1, parse_decimal_addr
  jsrr r1         ; parsedecimal(result, r0)
  br pi_skip2

pi_skip1
  ldr r2, r6, 1   ; load result
  add r6, r6, -2 
  str r2, r6, 0   ; pass in result
  str r0, r6, 1
  ld r1, parse_hex_addr
  jsrr r1         ; parsehex(result, r0)

pi_skip2
  ldr r1, r6, 0   ; load parse
  add r6, r6, 3
  add r2, r1, 1   ; parsed + 1
  brnp pi_skip3
  ldr r1, r6, 1   ; load result
  str r1, r5, 3
  ldr r7, r5, 2
  add r6, r5, 0
  ldr r5, r5, 1
  add r6, r6, 3
  ret

pi_skip3
  str r1, r6, 1   ; result = parsed
  getc
  out
  br pi_loop
  

parse_decimal_addr
  .fill x5000     ; the address of the parsedecimal function
parse_hex_addr
  .fill x6000     ; the address of the parsehex function
x 
  .fill x0078

.end


; =========================== MULT ==========================
.orig x4000
mult
  add r6, r6, -3
  str r7, r6, 1
  str r5, r6, 0
  add r5, r6, -1
  and r0, r0, 0   ; initialize result
  ldr r1, r5, 4   ; load a
  ldr r2, r5, 5   ; load b

m_loop 
  brnz m_return
  add r0, r0, r1  ; result += a
  add r2, r2, -1  ; b--
  br m_loop

m_return 
  str r0, r5, 3
  str r7, r5, 2
  add r6, r5, 0 
  ldr r5, r5, 1
  add r6, r6, 3 
  ret

.end


; ====================== PARSE_DECIMAL ======================
.orig x5000
parse_decimal
  add r6, r6, -3
  str r7, r6, 1
  str r5, r6, 0
  add r5, r6, -1
  ldr r1, r5, 4     ; load acc
  ldr r2, r5, 5     ; load c
  ld r3, pd_zero    ;'0'
  not r3, r3 
  add r3, r3, 1     ; -'0'
  add r3, r3, r2    ; c - '0' 
  brn if
  ld r3, pd_nine    ; '9'
  not r3, r3 
  add r3, r3, 1     ; -'9'
  add r3, r3, r2    ; c - '9'
  brnz pd_skip  

if 
  and r1, r1, 0
  add r1, r1, -1
  br pd_return 

pd_skip
  add r6, r6, -2
  str r1, r6, 0   ; pass in acc
  and r3, r3, 0 
  add r3, r3, 10
  str r3, r6, 1
  ld r0, pd_mult_addr
  jsrr r0         ; mult(acc, 10)
  ldr r0, r6, 0   ; load m
  add r6, r6, 3
  ldr r1, r5, 5   ; load c
  ld r2, pd_zero  ; '0'
  not r2, r2
  add r2, r2, 1   ; -'0' 
  add r1, r1, r2  ; c -'0'
  add r1, r1, r0  ; m + c - '0'
  
pd_return
  str r1, r5, 3
  ldr r7, r5, 2
  add r6, r5, 0 
  ldr r5, r5, 1
  add r6, r6, 3
  ret

pd_mult_addr
  .fill x4000     ; the address of the mult function
pd_zero
  .fill x0030
pd_nine
  .fill x0039
  
.end


; ======================== PARSE_HEX ========================
.orig x6000
parse_hex
  add r6, r6, -3
  str r7, r6, 1
  str r5, r6, 0
  add r5, r6, -1
  ldr r0, r5, 4       ; load acc
  and r1, r1, 0       ; clear r1
  add r1, r1, x000f   ; 15
  add r1, r1, 1       ; 16
  add r6, r6, -2 
  str r0, r6, 0       ; pass in acc
  str r1, r6, 1       ; pass in 16
  ld r2, ph_mult_addr 
  jsrr r2             ; mult(acc,16)
  ldr r0, r6, 0       ; m
  add r6, r6, 3       ; restore r6
  ldr r1, r5, 5       ; load c
  ld r2, ph_zero      ; '0'
  not r2, r2 
  add r2, r2, 1       ; -'0'
  add r2, r2, r1      ; c - '0'
  brn ph_skip1
  ld r2, ph_nine      ; '9'
  not r2, r2
  add r2, r2, 1       ; -'9'
  add r2, r2, r1      ; c -'9'
  brp ph_skip1
  ld r2, ph_zero      ; '0'
  not r2, r2 
  add r2, r2, 1       ; -'0'
  add r2, r2, r1      ; c - '0'
  add r3, r0, r2      ; m + c -'0'
  br ph_return

ph_skip1
  ld r2, a            ; 'a'
  not r2, r2
  add r2, r2, 1       ; - 'a'
  add r2, r2, r1      ; c - 'a'
  brn ph_skip2
  ld r2, f            ; 'f'
  not r2, r2 
  add r2, r2, 1       ; -'f'
  add r2, r2, r1      ; c - 'f'
  brp ph_skip2
  ld r2, a            ; 'a' 
  not r2, r2 
  add r2, r2, 1       ; -'a'
  add r2, r2, r1      ; c - 'a'
  add r3, r0, r2      ; m + c -'a'
  add r3, r3, 10      ; m + c - 'a' + 10
  br ph_return
  
ph_skip2
  and r3, r3, 0
  add r3, r3, -1 

ph_return
  str r3, r5, 3
  ldr r7, r5, 2
  add r6, r5, 0
  ldr r5, r5, 1
  add r6, r6, 3
  ret 

ph_mult_addr
  .fill x4000         ; the address of the mult function
ph_zero
  .fill x0030
ph_nine
  .fill x0039
a
  .fill x0041
f
  .fill x0046
ph_

.end
