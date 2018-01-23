.text
.global printx

.extern putchar

printx:

push {ip, lr}		@ Push reg in ordet to end program and end w/ pop


	mov r4, r0		@ copy r0 (given int) to r4

    mov r8, #0      @ store 0 in r8, r8 will be our counter for reverse stack printing

	cmp r4, #0		@ Check if r0 (given int) is = 0
	beq zeroskip	@ If = 0 no work needed so go to end

loop:

	@
	@ Perform division and modulus
    @  -loop / 16
    @  -keep looping with curVal % 16
    @  -repeat until != 0
    @  NOTE: Char address size!!!!
	@

	mov	r3, r4, asr #31			@ r3 <- ( r4[given int] >> 31)  NOTE: ASR uses 2's comp, sign saved
	add	ip, r4, #15				@ ip <- r4[given int] + 15

	mov	r2, r3, lsr #28			@ r2 <- r3[given int shifted right 31 bits] >> 28  NOTE: LSR clears vacated bits
	add	r3, r4, r2				@ r3 <- r4[given int] + r2[given int shifted right 31+28 bits]

    cmp	r4, #0					@ compare r4 and 0 (is the given int == 0?)
    movlt	r4, ip				@ r4 <- ip[given int + 15] NOTE: ONLY IF GIVEN INT (R4) IS LESS THAN 0
	and	r3, r3, #15             @ r3 <- r3[r4 + r2] & 15  NOTE: compares added registers == 15 ? 1 : 0
                                @ NOTE: boolean to determine continuation of looping later on

                                @ NOTE: now r3 is boolean (0 or 1) for modulous operation


	sub	r3, r3, r2              @ r3 <- r3[boolean val] - r2[given int >> 31+28]

    @ NOTE: REMEMBER CHAR SIZE BELOW!!! ASR #4
	movs r4, r4, asr #4         @ r4 <- r4 >> 4 NOTE: finished modulus operation, preped for CHAR conversion

    mov r0, r3                  @ r0 <- r3 NOTE: copying r4 to r0 to prep for printing w/ putchar

    @
    @ Add offset so it can print as proper ASCII char value
    @  +48 for number  +55 for letters
    @

    cmp r0, #10                 @ compare r0[our current val] with 10
    bge skip                    @ if r0 >= 10 go to 'skip' since its a letter
    add r0, r3, #48             @ if we are here, its a number so ADD 48 for ascii code
    b afterskip                 @ go to afterskip label

skip:

    add r0, r3, #55             @ add 55 to get proper ascii code from letter

afterskip:

    push {r0}       @ push r0 (our current char) onto stack

    add r8, r8, #1  @ increment our counter

	cmp r4, #0		@ Check if r0 (our running int) is = 0
	bne loop		@ keep looping if r0 != 0


printstack:
    pop {r0}            @ pop leftmost char from stack into r0 for printing in proper order
    bl putchar          @ call putchar function externally
    sub r8, r8, #1      @ decrement our counter (r8)
    cmp r8, #0          @ is our counter == 0?
    bne printstack      @ Keep looping if its not 0

	b end			@ otherwise, go to end (skip zeroskip)

zeroskip: 
	
    mov r0, #48     @ directly put 48 (ASCII code for '0') in r0
	bl putchar      @ print 0, for our special case

end:

pop {ip, pc}			@ end program and return

.data


	
