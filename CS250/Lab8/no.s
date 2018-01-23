	.arch armv6
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"printx.c"
	.text
	.align	2
	.global	hexString
	.type	hexString, %function
hexString:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #100
	bl	malloc
	cmp	r4, #0
	ldmeqfd	sp!, {r4, pc}
	mov	r1, r0
.L3:
	mov	r3, r4, asr #31
	add	ip, r4, #15
	mov	r2, r3, lsr #28
	cmp	r4, #0
	add	r3, r4, r2
	movlt	r4, ip
	and	r3, r3, #15
	rsb	r3, r2, r3
	movs	r4, r4, asr #4
	strb	r3, [r1, #1]!
	bne	.L3
	ldmfd	sp!, {r4, pc}
	.size	hexString, .-hexString
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r0, #0
	bx	lr
	.size	main, .-main
	.ident	"GCC: (Raspbian 4.9.2-10) 4.9.2"
	.section	.note.GNU-stack,"",%progbits
