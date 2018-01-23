	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	leaq	L_.str(%rip), %rdi
	movl	$0, -4(%rbp)
	movl	$2, -16(%rbp)
	movb	$0, %al
	callq	_printf
	leaq	L_.str.1(%rip), %rdi
	leaq	-8(%rbp), %rsi
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_scanf
	leaq	L_.str.2(%rip), %rdi
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.1(%rip), %rdi
	leaq	-12(%rbp), %rsi
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_scanf
	movl	-8(%rbp), %ecx
	cmpl	-12(%rbp), %ecx
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	jle	LBB0_2
## BB#1:
	movl	$1, -16(%rbp)
	jmp	LBB0_5
LBB0_2:
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jge	LBB0_4
## BB#3:
	movl	$0, -16(%rbp)
LBB0_4:
	jmp	LBB0_5
LBB0_5:
	cmpl	$1, -16(%rbp)
	jne	LBB0_7
## BB#6:
	leaq	L_.str.3(%rip), %rdi
	movl	-8(%rbp), %esi
	movl	-12(%rbp), %edx
	movl	-8(%rbp), %eax
	subl	-12(%rbp), %eax
	movl	%eax, %ecx
	movb	$0, %al
	callq	_printf
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	jmp	LBB0_11
LBB0_7:
	cmpl	$0, -16(%rbp)
	jne	LBB0_9
## BB#8:
	leaq	L_.str.3(%rip), %rdi
	movl	-12(%rbp), %esi
	movl	-8(%rbp), %edx
	movl	-12(%rbp), %eax
	subl	-8(%rbp), %eax
	movl	%eax, %ecx
	movb	$0, %al
	callq	_printf
	movl	%eax, -40(%rbp)         ## 4-byte Spill
	jmp	LBB0_10
LBB0_9:
	leaq	L_.str.4(%rip), %rdi
	movl	-12(%rbp), %esi
	movl	-8(%rbp), %edx
	movb	$0, %al
	callq	_printf
	movl	%eax, -44(%rbp)         ## 4-byte Spill
LBB0_10:
	jmp	LBB0_11
LBB0_11:
	movl	-4(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Enter the first number: "

L_.str.1:                               ## @.str.1
	.asciz	"%d"

L_.str.2:                               ## @.str.2
	.asciz	"Enter the second number: "

L_.str.3:                               ## @.str.3
	.asciz	"%d is strictly greater than %d by %d.\n"

L_.str.4:                               ## @.str.4
	.asciz	"%d and %d are equal.\n"


.subsections_via_symbols
