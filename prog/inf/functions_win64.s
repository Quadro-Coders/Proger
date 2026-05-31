	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 0
	.file	"functions.c"
	.def	increment;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	increment                       # -- Begin function increment
	.p2align	4
increment:                              # @increment
.seh_proc increment
# %bb.0:
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	movq	%rcx, (%rsp)
	movq	(%rsp), %rax
	movl	(%rax), %ecx
	addl	$1, %ecx
	movl	%ecx, (%rax)
	.seh_startepilogue
	popq	%rax
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	decrement;
	.scl	2;
	.type	32;
	.endef
	.globl	decrement                       # -- Begin function decrement
	.p2align	4
decrement:                              # @decrement
.seh_proc decrement
# %bb.0:
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	movq	%rcx, (%rsp)
	movq	(%rsp), %rax
	movl	(%rax), %ecx
	addl	$-1, %ecx
	movl	%ecx, (%rax)
	.seh_startepilogue
	popq	%rax
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	main                            # -- Begin function main
	.p2align	4
main:                                   # @main
.seh_proc main
# %bb.0:
	pushq	%rbp
	.seh_pushreg %rbp
	subq	$48, %rsp
	.seh_stackalloc 48
	leaq	48(%rsp), %rbp
	.seh_setframe %rbp, 48
	.seh_endprologue
	callq	__main
	movl	$0, -4(%rbp)
	movl	$10, -8(%rbp)
	movl	-8(%rbp), %edx
	leaq	.L.str(%rip), %rcx
	callq	printf
	leaq	-8(%rbp), %rcx
	callq	increment
	movl	-8(%rbp), %edx
	leaq	.L.str.1(%rip), %rcx
	callq	printf
	leaq	-8(%rbp), %rcx
	callq	decrement
	movl	-8(%rbp), %edx
	leaq	.L.str.2(%rip), %rcx
	callq	printf
	xorl	%eax, %eax
	.seh_startepilogue
	addq	$48, %rsp
	popq	%rbp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
.L.str:                                 # @.str
	.asciz	"\320\230\321\201\321\205\320\276\320\264\320\275\320\276\320\265 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265: %d\n"

.L.str.1:                               # @.str.1
	.asciz	"\320\237\320\276\321\201\320\273\320\265 increment: %d\n"

.L.str.2:                               # @.str.2
	.asciz	"\320\237\320\276\321\201\320\273\320\265 decrement: %d\n"

	.section	.debug$S,"dr"
	.p2align	2, 0x0
	.long	4                               # Debug section magic
	.long	241
	.long	.Ltmp1-.Ltmp0                   # Subsection size
.Ltmp0:
	.short	.Ltmp3-.Ltmp2                   # Record length
.Ltmp2:
	.short	4353                            # Record kind: S_OBJNAME
	.long	0                               # Signature
	.byte	0                               # Object name
	.p2align	2, 0x0
.Ltmp3:
	.short	.Ltmp5-.Ltmp4                   # Record length
.Ltmp4:
	.short	4412                            # Record kind: S_COMPILE3
	.long	0                               # Flags and language
	.short	208                             # CPUType
	.short	21                              # Frontend version
	.short	1
	.short	6
	.short	0
	.short	21016                           # Backend version
	.short	0
	.short	0
	.short	0
	.asciz	"clang version 21.1.6 (https://github.com/llvm/llvm-project.git a832a5222e489298337fbb5876f8dcaf072c5cca)" # Null-terminated compiler version string
	.p2align	2, 0x0
.Ltmp5:
.Ltmp1:
	.p2align	2, 0x0
	.addrsig
	.addrsig_sym increment
	.addrsig_sym decrement
	.addrsig_sym printf
