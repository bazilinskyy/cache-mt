	.file	"hr_timer.c"
	.text
.Ltext0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"clock gettime"
	.text
	.p2align 4,,15
	.globl	get_time_ns
	.type	get_time_ns, @function
get_time_ns:
.LFB31:
	.file 1 "hr_timer.c"
	.loc 1 34 0
	.cfi_startproc
.LVL0:
	subq	$8, %rsp
.LCFI0:
	.cfi_def_cfa_offset 16
	.loc 1 34 0
	movq	%rdi, %rsi
	.loc 1 36 0
	movl	$1, %edi
.LVL1:
	call	clock_gettime
.LVL2:
	cmpl	$-1, %eax
	.loc 1 40 0
	movl	$1, %edx
	.loc 1 36 0
	je	.L6
	.loc 1 41 0
	movl	%edx, %eax
	addq	$8, %rsp
.LCFI1:
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L6:
.LCFI2:
	.cfi_restore_state
	.loc 1 37 0
	movl	$.LC0, %edi
	call	perror
.LVL3:
	.loc 1 38 0
	xorl	%edx, %edx
	.loc 1 41 0
	addq	$8, %rsp
.LCFI3:
	.cfi_def_cfa_offset 8
	movl	%edx, %eax
	ret
	.cfi_endproc
.LFE31:
	.size	get_time_ns, .-get_time_ns
	.section	.rodata.str1.1
.LC1:
	.string	"clock getres"
	.text
	.p2align 4,,15
	.globl	get_time_res
	.type	get_time_res, @function
get_time_res:
.LFB32:
	.loc 1 44 0
	.cfi_startproc
.LVL4:
	subq	$8, %rsp
.LCFI4:
	.cfi_def_cfa_offset 16
	.loc 1 44 0
	movq	%rdi, %rsi
	.loc 1 46 0
	movl	$1, %edi
.LVL5:
	call	clock_getres
.LVL6:
	cmpl	$-1, %eax
	.loc 1 50 0
	movl	$1, %edx
	.loc 1 46 0
	je	.L11
	.loc 1 54 0
	movl	%edx, %eax
	addq	$8, %rsp
.LCFI5:
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L11:
.LCFI6:
	.cfi_restore_state
	.loc 1 47 0
	movl	$.LC1, %edi
	call	perror
.LVL7:
	.loc 1 48 0
	xorl	%edx, %edx
	.loc 1 54 0
	addq	$8, %rsp
.LCFI7:
	.cfi_def_cfa_offset 8
	movl	%edx, %eax
	ret
	.cfi_endproc
.LFE32:
	.size	get_time_res, .-get_time_res
	.p2align 4,,15
	.globl	calculate_time_ns
	.type	calculate_time_ns, @function
calculate_time_ns:
.LFB33:
	.loc 1 57 0
	.cfi_startproc
.LVL8:
	.loc 1 60 0
	movq	%rcx, %rax
	.loc 1 64 0
	subq	%rdi, %rdx
.LVL9:
	.loc 1 60 0
	subq	%rsi, %rax
	js	.L15
.LVL10:
	.loc 1 68 0
	imulq	$1000000000, %rdx, %rdx
.LVL11:
	addq	%rdx, %rax
.LVL12:
	.loc 1 69 0
	ret
.LVL13:
	.p2align 4,,10
	.p2align 3
.L15:
	.loc 1 61 0
	subq	$1, %rdx
.LVL14:
	.loc 1 62 0
	leaq	1000000000(%rcx), %rax
	.loc 1 68 0
	imulq	$1000000000, %rdx, %rdx
.LVL15:
	.loc 1 62 0
	subq	%rsi, %rax
.LVL16:
	.loc 1 68 0
	addq	%rdx, %rax
.LVL17:
	.loc 1 69 0
	ret
	.cfi_endproc
.LFE33:
	.size	calculate_time_ns, .-calculate_time_ns
	.p2align 4,,15
	.globl	average_time
	.type	average_time, @function
average_time:
.LFB34:
	.loc 1 72 0
	.cfi_startproc
.LVL18:
	.loc 1 74 0
	xorl	%eax, %eax
	.loc 1 73 0
	cmpl	$0, %esi
	je	.L17
.LVL19:
	.loc 1 78 0 discriminator 1
	jle	.L28
	.loc 1 72 0
	movq	%rdi, %r8
	movq	%rdi, %rdx
	salq	$60, %r8
	shrq	$63, %r8
	cmpl	%r8d, %esi
	cmovb	%esi, %r8d
	cmpl	$7, %esi
	cmovbe	%esi, %r8d
	testl	%r8d, %r8d
	je	.L29
	xorl	%ecx, %ecx
.LVL20:
	.p2align 4,,10
	.p2align 3
.L21:
	.loc 1 78 0
	addl	$1, %ecx
	.loc 1 79 0
	addq	(%rdx), %rax
.LVL21:
	addq	$8, %rdx
	cmpl	%r8d, %ecx
	jb	.L21
	cmpl	%r8d, %esi
	je	.L18
.LVL22:
.L20:
	movl	%esi, %r11d
	movl	%r8d, %edx
	subl	%r8d, %r11d
	movl	%r11d, %r9d
	shrl	%r9d
	movl	%r9d, %r10d
	addl	%r10d, %r10d
	je	.L23
	.loc 1 72 0
	pxor	%xmm0, %xmm0
	leaq	(%rdi,%rdx,8), %r8
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L24:
	addl	$1, %edx
	.loc 1 79 0 discriminator 2
	paddq	(%r8), %xmm0
	addq	$16, %r8
	cmpl	%r9d, %edx
	jb	.L24
	movdqa	%xmm0, %xmm1
	addl	%r10d, %ecx
	psrldq	$8, %xmm1
	paddq	%xmm1, %xmm0
	movq	%xmm0, -16(%rsp)
	addq	-16(%rsp), %rax
	cmpl	%r10d, %r11d
	je	.L18
.L23:
	.loc 1 72 0
	movslq	%ecx, %rdx
	leaq	(%rdi,%rdx,8), %rdx
	.p2align 4,,10
	.p2align 3
.L26:
	.loc 1 78 0
	addl	$1, %ecx
	.loc 1 79 0
	addq	(%rdx), %rax
.LVL23:
	addq	$8, %rdx
	.loc 1 78 0
	cmpl	%ecx, %esi
	jg	.L26
.LVL24:
.L18:
	.loc 1 81 0
	movslq	%esi, %rsi
	xorl	%edx, %edx
	divq	%rsi
.LVL25:
.L17:
	.loc 1 82 0
	rep
	ret
.LVL26:
.L28:
	.loc 1 78 0
	xorl	%eax, %eax
	jmp	.L18
.LVL27:
.L29:
	.loc 1 72 0
	xorl	%eax, %eax
	xorl	%ecx, %ecx
	jmp	.L20
	.cfi_endproc
.LFE34:
	.size	average_time, .-average_time
	.p2align 4,,15
	.globl	rdtsc_old
	.type	rdtsc_old, @function
rdtsc_old:
.LFB35:
	.loc 1 88 0
	.cfi_startproc
.LVL28:
	.loc 1 91 0
	testl	%edi, %edi
	.loc 1 88 0
	pushq	%rbx
.LCFI8:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	.loc 1 91 0
	jne	.L41
	.loc 1 94 0
#APP
# 94 "hr_timer.c" 1
	rdtsc
# 0 "" 2
.LVL29:
	.loc 1 96 0
#NO_APP
	salq	$32, %rdx
.LVL30:
	orq	%rax, %rdx
.LVL31:
	.loc 1 98 0
	movq	%rdx, %rax
.LVL32:
	popq	%rbx
.LCFI9:
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.LVL33:
	.p2align 4,,10
	.p2align 3
.L41:
.LCFI10:
	.cfi_restore_state
	.loc 1 92 0
#APP
# 92 "hr_timer.c" 1
	CPUID
rdtsc
# 0 "" 2
.LVL34:
	.loc 1 96 0
#NO_APP
	salq	$32, %rdx
.LVL35:
	orq	%rax, %rdx
.LVL36:
	.loc 1 98 0
	movq	%rdx, %rax
.LVL37:
	popq	%rbx
.LCFI11:
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE35:
	.size	rdtsc_old, .-rdtsc_old
	.p2align 4,,15
	.globl	rdtsc
	.type	rdtsc, @function
rdtsc:
.LFB36:
	.loc 1 101 0
	.cfi_startproc
	pushq	%rbx
.LCFI12:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	.loc 1 114 0
#APP
# 114 "hr_timer.c" 1
	CPUID
	RDTSC
	mov %edx, %esi
	mov %eax, %edi
	
# 0 "" 2
.LVL38:
	.loc 1 122 0
#NO_APP
	popq	%rbx
.LCFI13:
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE36:
	.size	rdtsc, .-rdtsc
	.section	.rodata.str1.1
.LC2:
	.string	"TIME. Time: %ld %ld %ld."
.LC3:
	.string	" Diff: %llu %llu\n"
	.text
	.p2align 4,,15
	.globl	test_clock_gettime
	.type	test_clock_gettime, @function
test_clock_gettime:
.LFB37:
	.loc 1 126 0
	.cfi_startproc
	subq	$56, %rsp
.LCFI14:
	.cfi_def_cfa_offset 64
.LVL39:
.LBB34:
.LBB35:
	.loc 1 36 0
	movl	$1, %edi
	movq	%rsp, %rsi
	call	clock_gettime
.LVL40:
	cmpl	$-1, %eax
	je	.L76
.L45:
.LVL41:
.LBE35:
.LBE34:
.LBB37:
.LBB38:
	leaq	16(%rsp), %rsi
.LVL42:
	movl	$1, %edi
	call	clock_gettime
.LVL43:
	cmpl	$-1, %eax
	je	.L77
.L46:
.LVL44:
.LBE38:
.LBE37:
.LBB40:
.LBB41:
	leaq	32(%rsp), %rsi
.LVL45:
	movl	$1, %edi
	call	clock_gettime
.LVL46:
	cmpl	$-1, %eax
	je	.L72
	.p2align 4,,10
	.p2align 3
.L70:
.LVL47:
	movq	24(%rsp), %rcx
	movq	8(%rsp), %rdx
.LVL48:
	movq	16(%rsp), %rax
.LVL49:
.LBE41:
.LBE40:
.LBB42:
.LBB43:
	.loc 1 64 0 discriminator 1
	subq	(%rsp), %rax
.LVL50:
	.loc 1 60 0 discriminator 1
	movq	%rcx, %rsi
	subq	%rdx, %rsi
	js	.L78
.L51:
.LVL51:
	.loc 1 68 0
	imulq	$1000000000, %rax, %rax
.LVL52:
	addq	%rax, %rsi
.LVL53:
.LBE43:
.LBE42:
	.loc 1 132 0
	testq	%rsi, %rsi
	jne	.L58
.LVL54:
.LBB45:
.LBB46:
	.loc 1 36 0
	leaq	16(%rsp), %rsi
.LVL55:
	movl	$1, %edi
	call	clock_gettime
.LVL56:
	cmpl	$-1, %eax
	jne	.L70
.LVL57:
.L72:
	.loc 1 37 0
	movl	$.LC0, %edi
	call	perror
.LVL58:
	jmp	.L70
.LVL59:
	.p2align 4,,10
	.p2align 3
.L81:
.LBE46:
.LBE45:
.LBB47:
.LBB48:
	.loc 1 61 0
	subq	$1, %rsi
.LVL60:
	.loc 1 62 0
	leaq	1000000000(%rdx), %rcx
	.loc 1 68 0
	imulq	$1000000000, %rsi, %rsi
.LVL61:
	.loc 1 62 0
	subq	%rax, %rcx
.LVL62:
	.loc 1 68 0
	addq	%rsi, %rcx
.LVL63:
.LBE48:
.LBE47:
	.loc 1 136 0
	testq	%rcx, %rcx
	jne	.L79
.LVL64:
.L58:
.LBB50:
.LBB51:
	.loc 1 36 0
	leaq	32(%rsp), %rsi
.LVL65:
	movl	$1, %edi
	call	clock_gettime
.LVL66:
	cmpl	$-1, %eax
	je	.L80
.L69:
	movq	32(%rsp), %r8
	movq	40(%rsp), %rdx
	movq	16(%rsp), %rdi
.LVL67:
	movq	24(%rsp), %rax
.LVL68:
.LBE51:
.LBE50:
.LBB53:
.LBB49:
	.loc 1 64 0 discriminator 1
	movq	%r8, %rsi
	.loc 1 60 0 discriminator 1
	movq	%rdx, %rcx
	.loc 1 64 0 discriminator 1
	subq	%rdi, %rsi
	.loc 1 60 0 discriminator 1
	subq	%rax, %rcx
	js	.L81
.LVL69:
	.loc 1 68 0
	imulq	$1000000000, %rsi, %rsi
.LVL70:
	addq	%rsi, %rcx
.LVL71:
.LBE49:
.LBE53:
	.loc 1 136 0
	testq	%rcx, %rcx
	je	.L58
.LVL72:
.L79:
	.loc 1 142 0
	imulq	$1000000000, %r8, %r8
.LVL73:
	.loc 1 141 0
	imulq	$1000000000, %rdi, %rdi
.LVL74:
	.loc 1 140 0
	leaq	(%r8,%rdx), %rcx
	leaq	(%rax,%rdi), %rdx
.LVL75:
	movq	(%rsp), %rax
.LVL76:
	movl	$.LC2, %edi
	imulq	$1000000000, %rax, %rsi
	xorl	%eax, %eax
	addq	8(%rsp), %rsi
	call	printf
.LVL77:
	movq	40(%rsp), %rsi
	movq	16(%rsp), %r8
.LVL78:
	movq	24(%rsp), %rax
.LVL79:
	movq	32(%rsp), %rcx
.LVL80:
.LBB54:
.LBB55:
	.loc 1 60 0
	movq	%rsi, %rdx
	.loc 1 64 0
	subq	%r8, %rcx
.LVL81:
	.loc 1 60 0
	subq	%rax, %rdx
	js	.L82
.L60:
.LVL82:
	.loc 1 68 0
	imulq	$1000000000, %rcx, %rcx
.LVL83:
	movq	8(%rsp), %rdi
.LVL84:
.LBE55:
.LBE54:
.LBB58:
.LBB59:
	.loc 1 60 0
	movq	%rax, %rsi
.LVL85:
	.loc 1 64 0
	subq	(%rsp), %r8
.LVL86:
.LBE59:
.LBE58:
.LBB63:
.LBB56:
	.loc 1 68 0
	addq	%rcx, %rdx
.LVL87:
.LBE56:
.LBE63:
.LBB64:
.LBB60:
	.loc 1 60 0
	subq	%rdi, %rsi
	js	.L83
.L62:
.LVL88:
	.loc 1 68 0
	imulq	$1000000000, %r8, %r8
.LVL89:
.LBE60:
.LBE64:
	.loc 1 143 0
	movl	$.LC3, %edi
.LVL90:
	xorl	%eax, %eax
.LVL91:
.LBB65:
.LBB61:
	.loc 1 68 0
	addq	%r8, %rsi
.LVL92:
.LBE61:
.LBE65:
	.loc 1 143 0
	call	printf
.LVL93:
	.loc 1 144 0
	addq	$56, %rsp
.LCFI15:
	.cfi_remember_state
	.cfi_def_cfa_offset 8
.LVL94:
	ret
.LVL95:
	.p2align 4,,10
	.p2align 3
.L78:
.LCFI16:
	.cfi_restore_state
.LBB66:
.LBB44:
	.loc 1 62 0
	leaq	1000000000(%rcx), %rsi
	.loc 1 61 0
	subq	$1, %rax
.LVL96:
	.loc 1 62 0
	subq	%rdx, %rsi
.LVL97:
	jmp	.L51
.LVL98:
	.p2align 4,,10
	.p2align 3
.L80:
.LBE44:
.LBE66:
.LBB67:
.LBB52:
	.loc 1 37 0
	movl	$.LC0, %edi
	call	perror
.LVL99:
	jmp	.L69
.LVL100:
	.p2align 4,,10
	.p2align 3
.L82:
.LBE52:
.LBE67:
.LBB68:
.LBB57:
	.loc 1 62 0
	leaq	1000000000(%rsi), %rdx
	.loc 1 61 0
	subq	$1, %rcx
.LVL101:
	.loc 1 62 0
	subq	%rax, %rdx
.LVL102:
	jmp	.L60
.LVL103:
	.p2align 4,,10
	.p2align 3
.L77:
.LBE57:
.LBE68:
.LBB69:
.LBB39:
	.loc 1 37 0
	movl	$.LC0, %edi
	call	perror
.LVL104:
	jmp	.L46
.LVL105:
	.p2align 4,,10
	.p2align 3
.L76:
.LBE39:
.LBE69:
.LBB70:
.LBB36:
	movl	$.LC0, %edi
	call	perror
.LVL106:
	.p2align 4,,3
	jmp	.L45
.LVL107:
	.p2align 4,,10
	.p2align 3
.L83:
.LBE36:
.LBE70:
.LBB71:
.LBB62:
	.loc 1 62 0
	leaq	1000000000(%rax), %rsi
	.loc 1 61 0
	subq	$1, %r8
.LVL108:
	.loc 1 62 0
	subq	%rdi, %rsi
.LVL109:
	jmp	.L62
.LBE62:
.LBE71:
	.cfi_endproc
.LFE37:
	.size	test_clock_gettime, .-test_clock_gettime
	.section	.rodata.str1.1
.LC4:
	.string	"RESOLUTION. time: %ld\n"
	.text
	.p2align 4,,15
	.globl	test_clock_getres
	.type	test_clock_getres, @function
test_clock_getres:
.LFB38:
	.loc 1 147 0
	.cfi_startproc
	subq	$24, %rsp
.LCFI17:
	.cfi_def_cfa_offset 32
.LVL110:
.LBB74:
.LBB75:
	.loc 1 46 0
	movl	$1, %edi
	movq	%rsp, %rsi
	call	clock_getres
.LVL111:
	cmpl	$-1, %eax
	je	.L87
.L85:
.LBE75:
.LBE74:
	.loc 1 151 0
	movq	(%rsp), %rdx
	.loc 1 150 0
	movl	$.LC4, %edi
	xorl	%eax, %eax
	.loc 1 151 0
	imulq	$1000000000, %rdx, %rsi
	.loc 1 150 0
	addq	8(%rsp), %rsi
	call	printf
.LVL112:
	.loc 1 152 0
	addq	$24, %rsp
.LCFI18:
	.cfi_remember_state
	.cfi_def_cfa_offset 8
.LVL113:
	ret
.LVL114:
	.p2align 4,,10
	.p2align 3
.L87:
.LCFI19:
	.cfi_restore_state
.LBB77:
.LBB76:
	.loc 1 47 0
	movl	$.LC1, %edi
	call	perror
.LVL115:
	jmp	.L85
.LBE76:
.LBE77:
	.cfi_endproc
.LFE38:
	.size	test_clock_getres, .-test_clock_getres
	.section	.rodata.str1.1
.LC5:
	.string	"TEST OF RDTSC with CPUID"
.LC6:
	.string	"%llu [%llu]\n"
.LC7:
	.string	"Total=%llu\n"
.LC8:
	.string	"\nTEST OF RDTSC without CPUID"
	.text
	.p2align 4,,15
	.globl	test_rdtsc
	.type	test_rdtsc, @function
test_rdtsc:
.LFB39:
	.loc 1 155 0
	.cfi_startproc
	pushq	%r15
.LCFI20:
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	.loc 1 157 0
	movl	$.LC5, %edi
	.loc 1 155 0
	pushq	%r14
.LCFI21:
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
.LCFI22:
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
.LCFI23:
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
.LCFI24:
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
.LCFI25:
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$264, %rsp
.LCFI26:
	.cfi_def_cfa_offset 320
	.loc 1 155 0
	leaq	256(%rsp), %r12
	movq	%rsp, %rbp
	.loc 1 157 0
	call	puts
.LVL116:
	.loc 1 155 0
	movq	%rsp, %rsi
.LVL117:
	.p2align 4,,10
	.p2align 3
.L89:
.LBB78:
.LBB79:
	.loc 1 92 0
#APP
# 92 "hr_timer.c" 1
	CPUID
rdtsc
# 0 "" 2
.LVL118:
	.loc 1 96 0
#NO_APP
	salq	$32, %rdx
.LVL119:
	orq	%rax, %rdx
.LVL120:
	movq	%rdx, (%rsi)
	addq	$8, %rsi
.LBE79:
.LBE78:
	.loc 1 161 0
	cmpq	%r12, %rsi
	jne	.L89
	.loc 1 164 0
	movq	(%rsp), %r15
.LVL121:
	leaq	8(%rsp), %r13
	movq	%r13, %rbx
	movq	%r15, %rax
.LVL122:
	.p2align 4,,10
	.p2align 3
.L90:
	.loc 1 166 0 discriminator 2
	movq	(%rbx), %r14
	movl	$.LC6, %edi
	addq	$8, %rbx
	movq	%r14, %rdx
	movq	%r14, %rsi
	subq	%rax, %rdx
	xorl	%eax, %eax
.LVL123:
	call	printf
.LVL124:
	.loc 1 165 0 discriminator 2
	cmpq	%r12, %rbx
	.loc 1 167 0 discriminator 2
	movq	%r14, %rax
	.loc 1 165 0 discriminator 2
	jne	.L90
	.loc 1 170 0
	movq	248(%rsp), %rsi
	movl	$.LC7, %edi
	xorl	%eax, %eax
	subq	%r15, %rsi
	call	printf
.LVL125:
	.loc 1 173 0
	movl	$.LC8, %edi
	call	puts
.LVL126:
	.p2align 4,,10
	.p2align 3
.L91:
.LBB80:
.LBB81:
	.loc 1 94 0
#APP
# 94 "hr_timer.c" 1
	rdtsc
# 0 "" 2
.LVL127:
	.loc 1 96 0
#NO_APP
	salq	$32, %rdx
.LVL128:
	orq	%rax, %rdx
.LVL129:
	movq	%rdx, 0(%rbp)
	addq	$8, %rbp
.LBE81:
.LBE80:
	.loc 1 175 0
	cmpq	%r12, %rbp
	jne	.L91
	.loc 1 178 0
	movq	(%rsp), %rbp
.LVL130:
	movq	%rbp, %rax
.LVL131:
	.p2align 4,,10
	.p2align 3
.L92:
	.loc 1 180 0 discriminator 2
	movq	0(%r13), %rbx
	movl	$.LC6, %edi
	addq	$8, %r13
	movq	%rbx, %rdx
	movq	%rbx, %rsi
	subq	%rax, %rdx
	xorl	%eax, %eax
.LVL132:
	call	printf
.LVL133:
	.loc 1 179 0 discriminator 2
	cmpq	%r12, %r13
	.loc 1 181 0 discriminator 2
	movq	%rbx, %rax
	.loc 1 179 0 discriminator 2
	jne	.L92
	.loc 1 184 0
	movq	248(%rsp), %rsi
	.loc 1 185 0
	addq	$264, %rsp
.LCFI27:
	.cfi_def_cfa_offset 56
	.loc 1 184 0
	movl	$.LC7, %edi
	.loc 1 185 0
	popq	%rbx
.LCFI28:
	.cfi_def_cfa_offset 48
.LVL134:
	.loc 1 184 0
	xorl	%eax, %eax
.LVL135:
	subq	%rbp, %rsi
	.loc 1 185 0
	popq	%rbp
.LCFI29:
	.cfi_def_cfa_offset 40
	popq	%r12
.LCFI30:
	.cfi_def_cfa_offset 32
	popq	%r13
.LCFI31:
	.cfi_def_cfa_offset 24
	popq	%r14
.LCFI32:
	.cfi_def_cfa_offset 16
	popq	%r15
.LCFI33:
	.cfi_def_cfa_offset 8
	.loc 1 184 0
	jmp	printf
.LVL136:
	.cfi_endproc
.LFE39:
	.size	test_rdtsc, .-test_rdtsc
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-linux-gnu/4.7/include/stddef.h"
	.file 3 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.file 4 "/usr/include/libio.h"
	.file 5 "/usr/include/time.h"
	.file 6 "/usr/include/stdint.h"
	.file 7 "/usr/include/stdio.h"
	.file 8 "<built-in>"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xbed
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF84
	.byte	0x1
	.long	.LASF85
	.long	.LASF86
	.quad	.Ltext0
	.quad	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF7
	.byte	0x2
	.byte	0xd5
	.long	0x38
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x2
	.long	.LASF8
	.byte	0x3
	.byte	0x8d
	.long	0x69
	.uleb128 0x2
	.long	.LASF9
	.byte	0x3
	.byte	0x8e
	.long	0x69
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF10
	.uleb128 0x2
	.long	.LASF11
	.byte	0x3
	.byte	0x95
	.long	0x69
	.uleb128 0x2
	.long	.LASF12
	.byte	0x3
	.byte	0x9e
	.long	0x62
	.uleb128 0x5
	.byte	0x8
	.uleb128 0x6
	.byte	0x8
	.long	0xab
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF13
	.uleb128 0x7
	.long	.LASF43
	.byte	0xd8
	.byte	0x4
	.value	0x10f
	.long	0x27f
	.uleb128 0x8
	.long	.LASF14
	.byte	0x4
	.value	0x110
	.long	0x62
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF15
	.byte	0x4
	.value	0x115
	.long	0xa5
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x8
	.long	.LASF16
	.byte	0x4
	.value	0x116
	.long	0xa5
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x8
	.long	.LASF17
	.byte	0x4
	.value	0x117
	.long	0xa5
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x8
	.long	.LASF18
	.byte	0x4
	.value	0x118
	.long	0xa5
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x8
	.long	.LASF19
	.byte	0x4
	.value	0x119
	.long	0xa5
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x8
	.long	.LASF20
	.byte	0x4
	.value	0x11a
	.long	0xa5
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0x8
	.long	.LASF21
	.byte	0x4
	.value	0x11b
	.long	0xa5
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0x8
	.long	.LASF22
	.byte	0x4
	.value	0x11c
	.long	0xa5
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0x8
	.long	.LASF23
	.byte	0x4
	.value	0x11e
	.long	0xa5
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0x8
	.long	.LASF24
	.byte	0x4
	.value	0x11f
	.long	0xa5
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0x8
	.long	.LASF25
	.byte	0x4
	.value	0x120
	.long	0xa5
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0x8
	.long	.LASF26
	.byte	0x4
	.value	0x122
	.long	0x2bd
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0x8
	.long	.LASF27
	.byte	0x4
	.value	0x124
	.long	0x2c3
	.byte	0x2
	.byte	0x23
	.uleb128 0x68
	.uleb128 0x8
	.long	.LASF28
	.byte	0x4
	.value	0x126
	.long	0x62
	.byte	0x2
	.byte	0x23
	.uleb128 0x70
	.uleb128 0x8
	.long	.LASF29
	.byte	0x4
	.value	0x12a
	.long	0x62
	.byte	0x2
	.byte	0x23
	.uleb128 0x74
	.uleb128 0x8
	.long	.LASF30
	.byte	0x4
	.value	0x12c
	.long	0x70
	.byte	0x2
	.byte	0x23
	.uleb128 0x78
	.uleb128 0x8
	.long	.LASF31
	.byte	0x4
	.value	0x130
	.long	0x46
	.byte	0x3
	.byte	0x23
	.uleb128 0x80
	.uleb128 0x8
	.long	.LASF32
	.byte	0x4
	.value	0x131
	.long	0x54
	.byte	0x3
	.byte	0x23
	.uleb128 0x82
	.uleb128 0x8
	.long	.LASF33
	.byte	0x4
	.value	0x132
	.long	0x2c9
	.byte	0x3
	.byte	0x23
	.uleb128 0x83
	.uleb128 0x8
	.long	.LASF34
	.byte	0x4
	.value	0x136
	.long	0x2d9
	.byte	0x3
	.byte	0x23
	.uleb128 0x88
	.uleb128 0x8
	.long	.LASF35
	.byte	0x4
	.value	0x13f
	.long	0x7b
	.byte	0x3
	.byte	0x23
	.uleb128 0x90
	.uleb128 0x8
	.long	.LASF36
	.byte	0x4
	.value	0x148
	.long	0xa3
	.byte	0x3
	.byte	0x23
	.uleb128 0x98
	.uleb128 0x8
	.long	.LASF37
	.byte	0x4
	.value	0x149
	.long	0xa3
	.byte	0x3
	.byte	0x23
	.uleb128 0xa0
	.uleb128 0x8
	.long	.LASF38
	.byte	0x4
	.value	0x14a
	.long	0xa3
	.byte	0x3
	.byte	0x23
	.uleb128 0xa8
	.uleb128 0x8
	.long	.LASF39
	.byte	0x4
	.value	0x14b
	.long	0xa3
	.byte	0x3
	.byte	0x23
	.uleb128 0xb0
	.uleb128 0x8
	.long	.LASF40
	.byte	0x4
	.value	0x14c
	.long	0x2d
	.byte	0x3
	.byte	0x23
	.uleb128 0xb8
	.uleb128 0x8
	.long	.LASF41
	.byte	0x4
	.value	0x14e
	.long	0x62
	.byte	0x3
	.byte	0x23
	.uleb128 0xc0
	.uleb128 0x8
	.long	.LASF42
	.byte	0x4
	.value	0x150
	.long	0x2df
	.byte	0x3
	.byte	0x23
	.uleb128 0xc4
	.byte	0
	.uleb128 0x9
	.long	.LASF87
	.byte	0x4
	.byte	0xb4
	.uleb128 0xa
	.long	.LASF44
	.byte	0x18
	.byte	0x4
	.byte	0xba
	.long	0x2bd
	.uleb128 0xb
	.long	.LASF45
	.byte	0x4
	.byte	0xbb
	.long	0x2bd
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xb
	.long	.LASF46
	.byte	0x4
	.byte	0xbc
	.long	0x2c3
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xb
	.long	.LASF47
	.byte	0x4
	.byte	0xc0
	.long	0x62
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x286
	.uleb128 0x6
	.byte	0x8
	.long	0xb2
	.uleb128 0xc
	.long	0xab
	.long	0x2d9
	.uleb128 0xd
	.long	0x86
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x27f
	.uleb128 0xc
	.long	0xab
	.long	0x2ef
	.uleb128 0xd
	.long	0x86
	.byte	0x13
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x2f5
	.uleb128 0xe
	.long	0xab
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF48
	.uleb128 0x2
	.long	.LASF49
	.byte	0x5
	.byte	0x5c
	.long	0x98
	.uleb128 0xa
	.long	.LASF50
	.byte	0x10
	.byte	0x5
	.byte	0x78
	.long	0x335
	.uleb128 0xb
	.long	.LASF51
	.byte	0x5
	.byte	0x7a
	.long	0x8d
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xb
	.long	.LASF52
	.byte	0x5
	.byte	0x7b
	.long	0x69
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF53
	.uleb128 0x3
	.byte	0x4
	.byte	0x4
	.long	.LASF54
	.uleb128 0x3
	.byte	0x8
	.byte	0x4
	.long	.LASF55
	.uleb128 0x2
	.long	.LASF56
	.byte	0x6
	.byte	0x34
	.long	0x4d
	.uleb128 0x2
	.long	.LASF57
	.byte	0x6
	.byte	0x38
	.long	0x38
	.uleb128 0xf
	.byte	0x1
	.long	.LASF59
	.byte	0x1
	.byte	0x39
	.byte	0x1
	.long	0x335
	.byte	0x1
	.long	0x394
	.uleb128 0x10
	.long	.LASF58
	.byte	0x1
	.byte	0x39
	.long	0x30c
	.uleb128 0x11
	.string	"end"
	.byte	0x1
	.byte	0x39
	.long	0x30c
	.uleb128 0x12
	.long	.LASF62
	.byte	0x1
	.byte	0x3b
	.long	0x30c
	.byte	0
	.uleb128 0xf
	.byte	0x1
	.long	.LASF60
	.byte	0x1
	.byte	0x58
	.byte	0x1
	.long	0x335
	.byte	0x1
	.long	0x3cf
	.uleb128 0x10
	.long	.LASF61
	.byte	0x1
	.byte	0x58
	.long	0x62
	.uleb128 0x13
	.string	"a"
	.byte	0x1
	.byte	0x59
	.long	0x38
	.uleb128 0x13
	.string	"b"
	.byte	0x1
	.byte	0x59
	.long	0x38
	.uleb128 0x12
	.long	.LASF62
	.byte	0x1
	.byte	0x5a
	.long	0x335
	.byte	0
	.uleb128 0xf
	.byte	0x1
	.long	.LASF63
	.byte	0x1
	.byte	0x22
	.byte	0x1
	.long	0x62
	.byte	0x1
	.long	0x3ed
	.uleb128 0x10
	.long	.LASF64
	.byte	0x1
	.byte	0x22
	.long	0x3ed
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x30c
	.uleb128 0x14
	.long	0x3cf
	.quad	.LFB31
	.quad	.LFE31
	.long	.LLST0
	.byte	0x1
	.long	0x454
	.uleb128 0x15
	.long	0x3e1
	.long	.LLST1
	.uleb128 0x16
	.quad	.LVL2
	.long	0xb6d
	.long	0x438
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x1
	.byte	0x31
	.uleb128 0x17
	.byte	0x1
	.byte	0x54
	.byte	0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x55
	.byte	0
	.uleb128 0x18
	.quad	.LVL3
	.long	0xb8b
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC0
	.byte	0
	.byte	0
	.uleb128 0xf
	.byte	0x1
	.long	.LASF65
	.byte	0x1
	.byte	0x2c
	.byte	0x1
	.long	0x62
	.byte	0x1
	.long	0x472
	.uleb128 0x10
	.long	.LASF64
	.byte	0x1
	.byte	0x2c
	.long	0x3ed
	.byte	0
	.uleb128 0x14
	.long	0x454
	.quad	.LFB32
	.quad	.LFE32
	.long	.LLST2
	.byte	0x1
	.long	0x4d3
	.uleb128 0x15
	.long	0x466
	.long	.LLST3
	.uleb128 0x16
	.quad	.LVL6
	.long	0xba0
	.long	0x4b7
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x1
	.byte	0x31
	.uleb128 0x17
	.byte	0x1
	.byte	0x54
	.byte	0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x55
	.byte	0
	.uleb128 0x18
	.quad	.LVL7
	.long	0xb8b
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC1
	.byte	0
	.byte	0
	.uleb128 0x19
	.long	0x360
	.quad	.LFB33
	.quad	.LFE33
	.byte	0x2
	.byte	0x77
	.sleb128 8
	.byte	0x1
	.long	0x50f
	.uleb128 0x1a
	.long	0x372
	.byte	0x6
	.byte	0x55
	.byte	0x93
	.uleb128 0x8
	.byte	0x54
	.byte	0x93
	.uleb128 0x8
	.uleb128 0x15
	.long	0x37d
	.long	.LLST4
	.uleb128 0x1b
	.long	0x388
	.long	.LLST5
	.byte	0
	.uleb128 0x1c
	.byte	0x1
	.long	.LASF88
	.byte	0x1
	.byte	0x48
	.byte	0x1
	.long	0x335
	.quad	.LFB34
	.quad	.LFE34
	.byte	0x2
	.byte	0x77
	.sleb128 8
	.byte	0x1
	.long	0x56f
	.uleb128 0x1d
	.long	.LASF66
	.byte	0x1
	.byte	0x48
	.long	0x56f
	.long	.LLST6
	.uleb128 0x1d
	.long	.LASF67
	.byte	0x1
	.byte	0x48
	.long	0x62
	.long	.LLST7
	.uleb128 0x1e
	.string	"i"
	.byte	0x1
	.byte	0x4c
	.long	0x62
	.long	.LLST8
	.uleb128 0x1f
	.long	.LASF68
	.byte	0x1
	.byte	0x4d
	.long	0x335
	.long	.LLST9
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x335
	.uleb128 0x14
	.long	0x394
	.quad	.LFB35
	.quad	.LFE35
	.long	.LLST10
	.byte	0x1
	.long	0x5b6
	.uleb128 0x1a
	.long	0x3a6
	.byte	0x1
	.byte	0x55
	.uleb128 0x1b
	.long	0x3b1
	.long	.LLST11
	.uleb128 0x1b
	.long	0x3ba
	.long	.LLST12
	.uleb128 0x1b
	.long	0x3c3
	.long	.LLST13
	.byte	0
	.uleb128 0x20
	.byte	0x1
	.long	.LASF69
	.byte	0x1
	.byte	0x65
	.long	0x355
	.quad	.LFB36
	.quad	.LFE36
	.long	.LLST14
	.byte	0x1
	.long	0x5f0
	.uleb128 0x13
	.string	"lo"
	.byte	0x1
	.byte	0x66
	.long	0x34a
	.uleb128 0x13
	.string	"hi"
	.byte	0x1
	.byte	0x66
	.long	0x34a
	.byte	0
	.uleb128 0x21
	.byte	0x1
	.long	.LASF70
	.byte	0x1
	.byte	0x7e
	.byte	0x1
	.quad	.LFB37
	.quad	.LFE37
	.long	.LLST15
	.byte	0x1
	.long	0x8f1
	.uleb128 0x22
	.long	.LASF71
	.byte	0x1
	.byte	0x7f
	.long	0x30c
	.byte	0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x22
	.long	.LASF72
	.byte	0x1
	.byte	0x7f
	.long	0x30c
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x22
	.long	.LASF73
	.byte	0x1
	.byte	0x7f
	.long	0x30c
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x23
	.long	0x3cf
	.quad	.LBB34
	.long	.Ldebug_ranges0+0
	.byte	0x1
	.byte	0x80
	.long	0x695
	.uleb128 0x15
	.long	0x3e1
	.long	.LLST16
	.uleb128 0x16
	.quad	.LVL40
	.long	0xb6d
	.long	0x679
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x1
	.byte	0x31
	.uleb128 0x17
	.byte	0x1
	.byte	0x54
	.byte	0x2
	.byte	0x77
	.sleb128 0
	.byte	0
	.uleb128 0x18
	.quad	.LVL106
	.long	0xb8b
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC0
	.byte	0
	.byte	0
	.uleb128 0x23
	.long	0x3cf
	.quad	.LBB37
	.long	.Ldebug_ranges0+0x30
	.byte	0x1
	.byte	0x81
	.long	0x6ee
	.uleb128 0x15
	.long	0x3e1
	.long	.LLST17
	.uleb128 0x16
	.quad	.LVL43
	.long	0xb6d
	.long	0x6d2
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x1
	.byte	0x31
	.uleb128 0x17
	.byte	0x1
	.byte	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x18
	.quad	.LVL104
	.long	0xb8b
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC0
	.byte	0
	.byte	0
	.uleb128 0x24
	.long	0x3cf
	.quad	.LBB40
	.quad	.LBE40
	.byte	0x1
	.byte	0x82
	.long	0x72c
	.uleb128 0x15
	.long	0x3e1
	.long	.LLST18
	.uleb128 0x18
	.quad	.LVL46
	.long	0xb6d
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x1
	.byte	0x31
	.uleb128 0x17
	.byte	0x1
	.byte	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.byte	0
	.uleb128 0x23
	.long	0x360
	.quad	.LBB42
	.long	.Ldebug_ranges0+0x60
	.byte	0x1
	.byte	0x84
	.long	0x761
	.uleb128 0x15
	.long	0x37d
	.long	.LLST19
	.uleb128 0x15
	.long	0x372
	.long	.LLST20
	.uleb128 0x25
	.long	.Ldebug_ranges0+0x90
	.uleb128 0x26
	.long	0x388
	.byte	0
	.byte	0
	.uleb128 0x24
	.long	0x3cf
	.quad	.LBB45
	.quad	.LBE45
	.byte	0x1
	.byte	0x85
	.long	0x7be
	.uleb128 0x15
	.long	0x3e1
	.long	.LLST21
	.uleb128 0x16
	.quad	.LVL56
	.long	0xb6d
	.long	0x7a2
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x1
	.byte	0x31
	.uleb128 0x17
	.byte	0x1
	.byte	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x18
	.quad	.LVL58
	.long	0xb8b
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC0
	.byte	0
	.byte	0
	.uleb128 0x23
	.long	0x360
	.quad	.LBB47
	.long	.Ldebug_ranges0+0xc0
	.byte	0x1
	.byte	0x88
	.long	0x7f3
	.uleb128 0x15
	.long	0x37d
	.long	.LLST22
	.uleb128 0x15
	.long	0x372
	.long	.LLST23
	.uleb128 0x25
	.long	.Ldebug_ranges0+0xf0
	.uleb128 0x26
	.long	0x388
	.byte	0
	.byte	0
	.uleb128 0x23
	.long	0x3cf
	.quad	.LBB50
	.long	.Ldebug_ranges0+0x120
	.byte	0x1
	.byte	0x89
	.long	0x84c
	.uleb128 0x15
	.long	0x3e1
	.long	.LLST24
	.uleb128 0x16
	.quad	.LVL66
	.long	0xb6d
	.long	0x830
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x1
	.byte	0x31
	.uleb128 0x17
	.byte	0x1
	.byte	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x18
	.quad	.LVL99
	.long	0xb8b
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC0
	.byte	0
	.byte	0
	.uleb128 0x23
	.long	0x360
	.quad	.LBB54
	.long	.Ldebug_ranges0+0x150
	.byte	0x1
	.byte	0x8f
	.long	0x881
	.uleb128 0x15
	.long	0x37d
	.long	.LLST25
	.uleb128 0x15
	.long	0x372
	.long	.LLST26
	.uleb128 0x25
	.long	.Ldebug_ranges0+0x190
	.uleb128 0x26
	.long	0x388
	.byte	0
	.byte	0
	.uleb128 0x23
	.long	0x360
	.quad	.LBB58
	.long	.Ldebug_ranges0+0x1d0
	.byte	0x1
	.byte	0x8f
	.long	0x8b6
	.uleb128 0x15
	.long	0x37d
	.long	.LLST27
	.uleb128 0x15
	.long	0x372
	.long	.LLST28
	.uleb128 0x25
	.long	.Ldebug_ranges0+0x220
	.uleb128 0x26
	.long	0x388
	.byte	0
	.byte	0
	.uleb128 0x16
	.quad	.LVL77
	.long	0xbbe
	.long	0x8d5
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC2
	.byte	0
	.uleb128 0x18
	.quad	.LVL93
	.long	0xbbe
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC3
	.byte	0
	.byte	0
	.uleb128 0x21
	.byte	0x1
	.long	.LASF74
	.byte	0x1
	.byte	0x93
	.byte	0x1
	.quad	.LFB38
	.quad	.LFE38
	.long	.LLST29
	.byte	0x1
	.long	0x996
	.uleb128 0x22
	.long	.LASF75
	.byte	0x1
	.byte	0x94
	.long	0x30c
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x23
	.long	0x454
	.quad	.LBB74
	.long	.Ldebug_ranges0+0x270
	.byte	0x1
	.byte	0x95
	.long	0x97a
	.uleb128 0x15
	.long	0x466
	.long	.LLST30
	.uleb128 0x16
	.quad	.LVL111
	.long	0xba0
	.long	0x95e
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x1
	.byte	0x31
	.uleb128 0x17
	.byte	0x1
	.byte	0x54
	.byte	0x2
	.byte	0x77
	.sleb128 0
	.byte	0
	.uleb128 0x18
	.quad	.LVL115
	.long	0xb8b
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC1
	.byte	0
	.byte	0
	.uleb128 0x18
	.quad	.LVL112
	.long	0xbbe
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC4
	.byte	0
	.byte	0
	.uleb128 0x21
	.byte	0x1
	.long	.LASF76
	.byte	0x1
	.byte	0x9b
	.byte	0x1
	.quad	.LFB39
	.quad	.LFE39
	.long	.LLST31
	.byte	0x1
	.long	0xb43
	.uleb128 0x27
	.string	"t"
	.byte	0x1
	.byte	0x9f
	.long	0xb43
	.byte	0x3
	.byte	0x91
	.sleb128 -320
	.uleb128 0x1f
	.long	.LASF77
	.byte	0x1
	.byte	0x9f
	.long	0x335
	.long	.LLST32
	.uleb128 0x1e
	.string	"i"
	.byte	0x1
	.byte	0xa0
	.long	0x62
	.long	.LLST33
	.uleb128 0x24
	.long	0x394
	.quad	.LBB78
	.quad	.LBE78
	.byte	0x1
	.byte	0xa2
	.long	0xa30
	.uleb128 0x28
	.long	0x3a6
	.byte	0x1
	.uleb128 0x29
	.quad	.LBB79
	.quad	.LBE79
	.uleb128 0x1b
	.long	0x3b1
	.long	.LLST34
	.uleb128 0x1b
	.long	0x3ba
	.long	.LLST35
	.uleb128 0x1b
	.long	0x3c3
	.long	.LLST36
	.byte	0
	.byte	0
	.uleb128 0x24
	.long	0x394
	.quad	.LBB80
	.quad	.LBE80
	.byte	0x1
	.byte	0xb0
	.long	0xa7f
	.uleb128 0x28
	.long	0x3a6
	.byte	0
	.uleb128 0x29
	.quad	.LBB81
	.quad	.LBE81
	.uleb128 0x1b
	.long	0x3b1
	.long	.LLST37
	.uleb128 0x1b
	.long	0x3ba
	.long	.LLST38
	.uleb128 0x1b
	.long	0x3c3
	.long	.LLST39
	.byte	0
	.byte	0
	.uleb128 0x16
	.quad	.LVL116
	.long	0xbd8
	.long	0xa9e
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC5
	.byte	0
	.uleb128 0x16
	.quad	.LVL124
	.long	0xbbe
	.long	0xac3
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC6
	.uleb128 0x17
	.byte	0x1
	.byte	0x54
	.byte	0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.uleb128 0x16
	.quad	.LVL125
	.long	0xbbe
	.long	0xae2
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC7
	.byte	0
	.uleb128 0x16
	.quad	.LVL126
	.long	0xbd8
	.long	0xb01
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC8
	.byte	0
	.uleb128 0x16
	.quad	.LVL133
	.long	0xbbe
	.long	0xb26
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC6
	.uleb128 0x17
	.byte	0x1
	.byte	0x54
	.byte	0x2
	.byte	0x73
	.sleb128 0
	.byte	0
	.uleb128 0x2a
	.quad	.LVL136
	.byte	0x1
	.long	0xbbe
	.uleb128 0x17
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.byte	0x3
	.quad	.LC7
	.byte	0
	.byte	0
	.uleb128 0xc
	.long	0x335
	.long	0xb53
	.uleb128 0xd
	.long	0x86
	.byte	0x1f
	.byte	0
	.uleb128 0x2b
	.long	.LASF78
	.byte	0x7
	.byte	0xa5
	.long	0x2c3
	.byte	0x1
	.byte	0x1
	.uleb128 0x2b
	.long	.LASF79
	.byte	0x7
	.byte	0xa6
	.long	0x2c3
	.byte	0x1
	.byte	0x1
	.uleb128 0x2c
	.byte	0x1
	.long	.LASF80
	.byte	0x5
	.value	0x150
	.byte	0x1
	.long	0x62
	.byte	0x1
	.long	0xb8b
	.uleb128 0x2d
	.long	0x301
	.uleb128 0x2d
	.long	0x3ed
	.byte	0
	.uleb128 0x2e
	.byte	0x1
	.long	.LASF89
	.byte	0x7
	.value	0x347
	.byte	0x1
	.byte	0x1
	.long	0xba0
	.uleb128 0x2d
	.long	0x2ef
	.byte	0
	.uleb128 0x2c
	.byte	0x1
	.long	.LASF81
	.byte	0x5
	.value	0x14d
	.byte	0x1
	.long	0x62
	.byte	0x1
	.long	0xbbe
	.uleb128 0x2d
	.long	0x301
	.uleb128 0x2d
	.long	0x3ed
	.byte	0
	.uleb128 0x2c
	.byte	0x1
	.long	.LASF82
	.byte	0x7
	.value	0x167
	.byte	0x1
	.long	0x62
	.byte	0x1
	.long	0xbd8
	.uleb128 0x2d
	.long	0x2ef
	.uleb128 0x2f
	.byte	0
	.uleb128 0x30
	.byte	0x1
	.long	.LASF83
	.byte	0x8
	.byte	0
	.long	.LASF90
	.byte	0x1
	.long	0x62
	.byte	0x1
	.uleb128 0x2d
	.long	0x2ef
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x2115
	.uleb128 0xc
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.quad	.LFB31-.Ltext0
	.quad	.LCFI0-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI0-.Ltext0
	.quad	.LCFI1-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI1-.Ltext0
	.quad	.LCFI2-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI2-.Ltext0
	.quad	.LCFI3-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI3-.Ltext0
	.quad	.LFE31-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST1:
	.quad	.LVL0-.Ltext0
	.quad	.LVL1-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL1-.Ltext0
	.quad	.LVL2-1-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	.LVL2-1-.Ltext0
	.quad	.LFE31-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x55
	.byte	0x9f
	.quad	0
	.quad	0
.LLST2:
	.quad	.LFB32-.Ltext0
	.quad	.LCFI4-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI4-.Ltext0
	.quad	.LCFI5-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI5-.Ltext0
	.quad	.LCFI6-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI6-.Ltext0
	.quad	.LCFI7-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI7-.Ltext0
	.quad	.LFE32-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST3:
	.quad	.LVL4-.Ltext0
	.quad	.LVL5-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL5-.Ltext0
	.quad	.LVL6-1-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	.LVL6-1-.Ltext0
	.quad	.LFE32-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x55
	.byte	0x9f
	.quad	0
	.quad	0
.LLST4:
	.quad	.LVL8-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x6
	.byte	0x51
	.byte	0x93
	.uleb128 0x8
	.byte	0x52
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL9-.Ltext0
	.quad	.LFE33-.Ltext0
	.value	0x5
	.byte	0x93
	.uleb128 0x8
	.byte	0x52
	.byte	0x93
	.uleb128 0x8
	.quad	0
	.quad	0
.LLST5:
	.quad	.LVL10-.Ltext0
	.quad	.LVL11-.Ltext0
	.value	0x6
	.byte	0x51
	.byte	0x93
	.uleb128 0x8
	.byte	0x50
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL11-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x5
	.byte	0x93
	.uleb128 0x8
	.byte	0x50
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-.Ltext0
	.value	0xa
	.byte	0x93
	.uleb128 0x8
	.byte	0x72
	.sleb128 0
	.byte	0x74
	.sleb128 0
	.byte	0x1c
	.byte	0x9f
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL14-.Ltext0
	.quad	.LVL15-.Ltext0
	.value	0x5
	.byte	0x51
	.byte	0x93
	.uleb128 0x8
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL16-.Ltext0
	.quad	.LVL17-.Ltext0
	.value	0x5
	.byte	0x93
	.uleb128 0x8
	.byte	0x50
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL17-.Ltext0
	.quad	.LFE33-.Ltext0
	.value	0x10
	.byte	0x93
	.uleb128 0x8
	.byte	0x72
	.sleb128 0
	.byte	0x74
	.sleb128 0
	.byte	0x1c
	.byte	0x23
	.uleb128 0x3b9aca00
	.byte	0x9f
	.byte	0x93
	.uleb128 0x8
	.quad	0
	.quad	0
.LLST6:
	.quad	.LVL18-.Ltext0
	.quad	.LVL27-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL27-.Ltext0
	.quad	.LFE34-.Ltext0
	.value	0x1
	.byte	0x51
	.quad	0
	.quad	0
.LLST7:
	.quad	.LVL18-.Ltext0
	.quad	.LVL25-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	.LVL25-.Ltext0
	.quad	.LVL26-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x54
	.byte	0x9f
	.quad	.LVL26-.Ltext0
	.quad	.LFE34-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	0
	.quad	0
.LLST8:
	.quad	.LVL19-.Ltext0
	.quad	.LVL20-.Ltext0
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.quad	.LVL21-.Ltext0
	.quad	.LVL22-.Ltext0
	.value	0x1
	.byte	0x52
	.quad	.LVL23-.Ltext0
	.quad	.LVL24-.Ltext0
	.value	0x1
	.byte	0x52
	.quad	.LVL26-.Ltext0
	.quad	.LFE34-.Ltext0
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.quad	0
	.quad	0
.LLST9:
	.quad	.LVL19-.Ltext0
	.quad	.LVL20-.Ltext0
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.quad	.LVL21-.Ltext0
	.quad	.LVL22-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL23-.Ltext0
	.quad	.LVL24-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL26-.Ltext0
	.quad	.LFE34-.Ltext0
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.quad	0
	.quad	0
.LLST10:
	.quad	.LFB35-.Ltext0
	.quad	.LCFI8-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI8-.Ltext0
	.quad	.LCFI9-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI9-.Ltext0
	.quad	.LCFI10-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI10-.Ltext0
	.quad	.LCFI11-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI11-.Ltext0
	.quad	.LFE35-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST11:
	.quad	.LVL29-.Ltext0
	.quad	.LVL32-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL34-.Ltext0
	.quad	.LVL37-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	0
	.quad	0
.LLST12:
	.quad	.LVL29-.Ltext0
	.quad	.LVL30-.Ltext0
	.value	0x1
	.byte	0x51
	.quad	.LVL34-.Ltext0
	.quad	.LVL35-.Ltext0
	.value	0x1
	.byte	0x51
	.quad	0
	.quad	0
.LLST13:
	.quad	.LVL29-.Ltext0
	.quad	.LVL30-.Ltext0
	.value	0x9
	.byte	0x71
	.sleb128 0
	.byte	0x8
	.byte	0x20
	.byte	0x24
	.byte	0x70
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.quad	.LVL31-.Ltext0
	.quad	.LVL33-.Ltext0
	.value	0x1
	.byte	0x51
	.quad	.LVL34-.Ltext0
	.quad	.LVL35-.Ltext0
	.value	0x9
	.byte	0x71
	.sleb128 0
	.byte	0x8
	.byte	0x20
	.byte	0x24
	.byte	0x70
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.quad	.LVL36-.Ltext0
	.quad	.LFE35-.Ltext0
	.value	0x1
	.byte	0x51
	.quad	0
	.quad	0
.LLST14:
	.quad	.LFB36-.Ltext0
	.quad	.LCFI12-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI12-.Ltext0
	.quad	.LCFI13-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI13-.Ltext0
	.quad	.LFE36-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST15:
	.quad	.LFB37-.Ltext0
	.quad	.LCFI14-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI14-.Ltext0
	.quad	.LCFI15-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 64
	.quad	.LCFI15-.Ltext0
	.quad	.LCFI16-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI16-.Ltext0
	.quad	.LFE37-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 64
	.quad	0
	.quad	0
.LLST16:
	.quad	.LVL39-.Ltext0
	.quad	.LVL94-.Ltext0
	.value	0x1
	.byte	0x57
	.quad	.LVL94-.Ltext0
	.quad	.LVL95-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -64
	.byte	0x9f
	.quad	.LVL95-.Ltext0
	.quad	.LFE37-.Ltext0
	.value	0x1
	.byte	0x57
	.quad	0
	.quad	0
.LLST17:
	.quad	.LVL41-.Ltext0
	.quad	.LVL42-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -48
	.byte	0x9f
	.quad	.LVL42-.Ltext0
	.quad	.LVL43-1-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	.LVL43-1-.Ltext0
	.quad	.LVL55-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -48
	.byte	0x9f
	.quad	.LVL55-.Ltext0
	.quad	.LVL56-1-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	.LVL56-1-.Ltext0
	.quad	.LVL105-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -48
	.byte	0x9f
	.quad	.LVL107-.Ltext0
	.quad	.LFE37-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -48
	.byte	0x9f
	.quad	0
	.quad	0
.LLST18:
	.quad	.LVL44-.Ltext0
	.quad	.LVL45-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x9f
	.quad	.LVL45-.Ltext0
	.quad	.LVL46-1-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	.LVL46-1-.Ltext0
	.quad	.LVL65-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x9f
	.quad	.LVL65-.Ltext0
	.quad	.LVL66-1-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	.LVL66-1-.Ltext0
	.quad	.LVL103-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x9f
	.quad	.LVL107-.Ltext0
	.quad	.LFE37-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x9f
	.quad	0
	.quad	0
.LLST19:
	.quad	.LVL49-.Ltext0
	.quad	.LVL50-.Ltext0
	.value	0x6
	.byte	0x50
	.byte	0x93
	.uleb128 0x8
	.byte	0x52
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL50-.Ltext0
	.quad	.LVL55-.Ltext0
	.value	0x7
	.byte	0x91
	.sleb128 -48
	.byte	0x93
	.uleb128 0x8
	.byte	0x52
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL55-.Ltext0
	.quad	.LVL56-1-.Ltext0
	.value	0x7
	.byte	0x74
	.sleb128 0
	.byte	0x93
	.uleb128 0x8
	.byte	0x52
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL95-.Ltext0
	.quad	.LVL98-.Ltext0
	.value	0x7
	.byte	0x91
	.sleb128 -48
	.byte	0x93
	.uleb128 0x8
	.byte	0x52
	.byte	0x93
	.uleb128 0x8
	.quad	0
	.quad	0
.LLST20:
	.quad	.LVL47-.Ltext0
	.quad	.LVL48-.Ltext0
	.value	0x6
	.byte	0x77
	.sleb128 0
	.byte	0x93
	.uleb128 0x8
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL48-.Ltext0
	.quad	.LVL56-1-.Ltext0
	.value	0x7
	.byte	0x77
	.sleb128 0
	.byte	0x93
	.uleb128 0x8
	.byte	0x51
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL95-.Ltext0
	.quad	.LVL98-.Ltext0
	.value	0x7
	.byte	0x77
	.sleb128 0
	.byte	0x93
	.uleb128 0x8
	.byte	0x51
	.byte	0x93
	.uleb128 0x8
	.quad	0
	.quad	0
.LLST21:
	.quad	.LVL54-.Ltext0
	.quad	.LVL55-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -48
	.byte	0x9f
	.quad	.LVL55-.Ltext0
	.quad	.LVL56-1-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	.LVL56-1-.Ltext0
	.quad	.LVL57-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -48
	.byte	0x9f
	.quad	0
	.quad	0
.LLST22:
	.quad	.LVL59-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x6
	.byte	0x58
	.byte	0x93
	.uleb128 0x8
	.byte	0x51
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL68-.Ltext0
	.quad	.LVL73-.Ltext0
	.value	0x6
	.byte	0x58
	.byte	0x93
	.uleb128 0x8
	.byte	0x51
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL73-.Ltext0
	.quad	.LVL75-.Ltext0
	.value	0x7
	.byte	0x91
	.sleb128 -32
	.byte	0x93
	.uleb128 0x8
	.byte	0x51
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL75-.Ltext0
	.quad	.LVL77-1-.Ltext0
	.value	0x8
	.byte	0x91
	.sleb128 -32
	.byte	0x93
	.uleb128 0x8
	.byte	0x91
	.sleb128 -24
	.byte	0x93
	.uleb128 0x8
	.quad	0
	.quad	0
.LLST23:
	.quad	.LVL59-.Ltext0
	.quad	.LVL64-.Ltext0
	.value	0x6
	.byte	0x55
	.byte	0x93
	.uleb128 0x8
	.byte	0x50
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL67-.Ltext0
	.quad	.LVL68-.Ltext0
	.value	0x5
	.byte	0x55
	.byte	0x93
	.uleb128 0x8
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL68-.Ltext0
	.quad	.LVL74-.Ltext0
	.value	0x6
	.byte	0x55
	.byte	0x93
	.uleb128 0x8
	.byte	0x50
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL74-.Ltext0
	.quad	.LVL76-.Ltext0
	.value	0x7
	.byte	0x91
	.sleb128 -48
	.byte	0x93
	.uleb128 0x8
	.byte	0x50
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL76-.Ltext0
	.quad	.LVL77-1-.Ltext0
	.value	0x8
	.byte	0x91
	.sleb128 -48
	.byte	0x93
	.uleb128 0x8
	.byte	0x91
	.sleb128 -40
	.byte	0x93
	.uleb128 0x8
	.quad	0
	.quad	0
.LLST24:
	.quad	.LVL59-.Ltext0
	.quad	.LVL65-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x9f
	.quad	.LVL65-.Ltext0
	.quad	.LVL66-1-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	.LVL66-1-.Ltext0
	.quad	.LVL95-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x9f
	.quad	.LVL98-.Ltext0
	.quad	.LVL103-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x9f
	.quad	.LVL107-.Ltext0
	.quad	.LFE37-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x9f
	.quad	0
	.quad	0
.LLST25:
	.quad	.LVL80-.Ltext0
	.quad	.LVL81-.Ltext0
	.value	0x6
	.byte	0x52
	.byte	0x93
	.uleb128 0x8
	.byte	0x54
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL81-.Ltext0
	.quad	.LVL85-.Ltext0
	.value	0x7
	.byte	0x91
	.sleb128 -32
	.byte	0x93
	.uleb128 0x8
	.byte	0x54
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL85-.Ltext0
	.quad	.LVL93-1-.Ltext0
	.value	0x8
	.byte	0x91
	.sleb128 -32
	.byte	0x93
	.uleb128 0x8
	.byte	0x91
	.sleb128 -24
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL100-.Ltext0
	.quad	.LVL103-.Ltext0
	.value	0x7
	.byte	0x91
	.sleb128 -32
	.byte	0x93
	.uleb128 0x8
	.byte	0x54
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL107-.Ltext0
	.quad	.LFE37-.Ltext0
	.value	0x8
	.byte	0x91
	.sleb128 -32
	.byte	0x93
	.uleb128 0x8
	.byte	0x91
	.sleb128 -24
	.byte	0x93
	.uleb128 0x8
	.quad	0
	.quad	0
.LLST26:
	.quad	.LVL78-.Ltext0
	.quad	.LVL79-.Ltext0
	.value	0x5
	.byte	0x58
	.byte	0x93
	.uleb128 0x8
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL79-.Ltext0
	.quad	.LVL86-.Ltext0
	.value	0x6
	.byte	0x58
	.byte	0x93
	.uleb128 0x8
	.byte	0x50
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL86-.Ltext0
	.quad	.LVL91-.Ltext0
	.value	0x7
	.byte	0x91
	.sleb128 -48
	.byte	0x93
	.uleb128 0x8
	.byte	0x50
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL91-.Ltext0
	.quad	.LVL93-1-.Ltext0
	.value	0x8
	.byte	0x91
	.sleb128 -48
	.byte	0x93
	.uleb128 0x8
	.byte	0x91
	.sleb128 -40
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL100-.Ltext0
	.quad	.LVL103-.Ltext0
	.value	0x6
	.byte	0x58
	.byte	0x93
	.uleb128 0x8
	.byte	0x50
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL107-.Ltext0
	.quad	.LFE37-.Ltext0
	.value	0x7
	.byte	0x91
	.sleb128 -48
	.byte	0x93
	.uleb128 0x8
	.byte	0x50
	.byte	0x93
	.uleb128 0x8
	.quad	0
	.quad	0
.LLST27:
	.quad	.LVL84-.Ltext0
	.quad	.LVL86-.Ltext0
	.value	0x6
	.byte	0x58
	.byte	0x93
	.uleb128 0x8
	.byte	0x50
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL86-.Ltext0
	.quad	.LVL91-.Ltext0
	.value	0x7
	.byte	0x91
	.sleb128 -48
	.byte	0x93
	.uleb128 0x8
	.byte	0x50
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL91-.Ltext0
	.quad	.LVL93-1-.Ltext0
	.value	0x8
	.byte	0x91
	.sleb128 -48
	.byte	0x93
	.uleb128 0x8
	.byte	0x91
	.sleb128 -40
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL107-.Ltext0
	.quad	.LFE37-.Ltext0
	.value	0x7
	.byte	0x91
	.sleb128 -48
	.byte	0x93
	.uleb128 0x8
	.byte	0x50
	.byte	0x93
	.uleb128 0x8
	.quad	0
	.quad	0
.LLST28:
	.quad	.LVL82-.Ltext0
	.quad	.LVL84-.Ltext0
	.value	0x6
	.byte	0x77
	.sleb128 0
	.byte	0x93
	.uleb128 0x8
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL84-.Ltext0
	.quad	.LVL90-.Ltext0
	.value	0x7
	.byte	0x77
	.sleb128 0
	.byte	0x93
	.uleb128 0x8
	.byte	0x55
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL90-.Ltext0
	.quad	.LVL93-1-.Ltext0
	.value	0x8
	.byte	0x77
	.sleb128 0
	.byte	0x93
	.uleb128 0x8
	.byte	0x91
	.sleb128 -56
	.byte	0x93
	.uleb128 0x8
	.quad	.LVL107-.Ltext0
	.quad	.LFE37-.Ltext0
	.value	0x7
	.byte	0x77
	.sleb128 0
	.byte	0x93
	.uleb128 0x8
	.byte	0x55
	.byte	0x93
	.uleb128 0x8
	.quad	0
	.quad	0
.LLST29:
	.quad	.LFB38-.Ltext0
	.quad	.LCFI17-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI17-.Ltext0
	.quad	.LCFI18-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI18-.Ltext0
	.quad	.LCFI19-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI19-.Ltext0
	.quad	.LFE38-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	0
	.quad	0
.LLST30:
	.quad	.LVL110-.Ltext0
	.quad	.LVL113-.Ltext0
	.value	0x1
	.byte	0x57
	.quad	.LVL113-.Ltext0
	.quad	.LVL114-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x9f
	.quad	.LVL114-.Ltext0
	.quad	.LFE38-.Ltext0
	.value	0x1
	.byte	0x57
	.quad	0
	.quad	0
.LLST31:
	.quad	.LFB39-.Ltext0
	.quad	.LCFI20-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI20-.Ltext0
	.quad	.LCFI21-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI21-.Ltext0
	.quad	.LCFI22-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI22-.Ltext0
	.quad	.LCFI23-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI23-.Ltext0
	.quad	.LCFI24-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI24-.Ltext0
	.quad	.LCFI25-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI25-.Ltext0
	.quad	.LCFI26-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI26-.Ltext0
	.quad	.LCFI27-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 320
	.quad	.LCFI27-.Ltext0
	.quad	.LCFI28-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 56
	.quad	.LCFI28-.Ltext0
	.quad	.LCFI29-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI29-.Ltext0
	.quad	.LCFI30-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI30-.Ltext0
	.quad	.LCFI31-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI31-.Ltext0
	.quad	.LCFI32-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI32-.Ltext0
	.quad	.LCFI33-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI33-.Ltext0
	.quad	.LFE39-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
.LLST32:
	.quad	.LVL121-.Ltext0
	.quad	.LVL122-.Ltext0
	.value	0x1
	.byte	0x5f
	.quad	.LVL122-.Ltext0
	.quad	.LVL123-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL124-.Ltext0
	.quad	.LVL130-.Ltext0
	.value	0x1
	.byte	0x5e
	.quad	.LVL130-.Ltext0
	.quad	.LVL131-.Ltext0
	.value	0x1
	.byte	0x56
	.quad	.LVL131-.Ltext0
	.quad	.LVL132-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL133-.Ltext0
	.quad	.LVL134-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	.LVL134-.Ltext0
	.quad	.LVL135-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	0
	.quad	0
.LLST33:
	.quad	.LVL116-.Ltext0
	.quad	.LVL117-.Ltext0
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.quad	.LVL121-.Ltext0
	.quad	.LVL122-.Ltext0
	.value	0x2
	.byte	0x31
	.byte	0x9f
	.quad	.LVL130-.Ltext0
	.quad	.LVL131-.Ltext0
	.value	0x2
	.byte	0x31
	.byte	0x9f
	.quad	0
	.quad	0
.LLST34:
	.quad	.LVL118-.Ltext0
	.quad	.LVL122-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	0
	.quad	0
.LLST35:
	.quad	.LVL118-.Ltext0
	.quad	.LVL119-.Ltext0
	.value	0x1
	.byte	0x51
	.quad	0
	.quad	0
.LLST36:
	.quad	.LVL118-.Ltext0
	.quad	.LVL119-.Ltext0
	.value	0x9
	.byte	0x71
	.sleb128 0
	.byte	0x8
	.byte	0x20
	.byte	0x24
	.byte	0x70
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.quad	.LVL120-.Ltext0
	.quad	.LVL122-.Ltext0
	.value	0x1
	.byte	0x51
	.quad	0
	.quad	0
.LLST37:
	.quad	.LVL127-.Ltext0
	.quad	.LVL131-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	0
	.quad	0
.LLST38:
	.quad	.LVL127-.Ltext0
	.quad	.LVL128-.Ltext0
	.value	0x1
	.byte	0x51
	.quad	0
	.quad	0
.LLST39:
	.quad	.LVL127-.Ltext0
	.quad	.LVL128-.Ltext0
	.value	0x9
	.byte	0x71
	.sleb128 0
	.byte	0x8
	.byte	0x20
	.byte	0x24
	.byte	0x70
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.quad	.LVL129-.Ltext0
	.quad	.LVL131-.Ltext0
	.value	0x1
	.byte	0x51
	.quad	0
	.quad	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.quad	.LBB34-.Ltext0
	.quad	.LBE34-.Ltext0
	.quad	.LBB70-.Ltext0
	.quad	.LBE70-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB37-.Ltext0
	.quad	.LBE37-.Ltext0
	.quad	.LBB69-.Ltext0
	.quad	.LBE69-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB42-.Ltext0
	.quad	.LBE42-.Ltext0
	.quad	.LBB66-.Ltext0
	.quad	.LBE66-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB43-.Ltext0
	.quad	.LBE43-.Ltext0
	.quad	.LBB44-.Ltext0
	.quad	.LBE44-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB47-.Ltext0
	.quad	.LBE47-.Ltext0
	.quad	.LBB53-.Ltext0
	.quad	.LBE53-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB48-.Ltext0
	.quad	.LBE48-.Ltext0
	.quad	.LBB49-.Ltext0
	.quad	.LBE49-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB50-.Ltext0
	.quad	.LBE50-.Ltext0
	.quad	.LBB67-.Ltext0
	.quad	.LBE67-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB54-.Ltext0
	.quad	.LBE54-.Ltext0
	.quad	.LBB63-.Ltext0
	.quad	.LBE63-.Ltext0
	.quad	.LBB68-.Ltext0
	.quad	.LBE68-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB55-.Ltext0
	.quad	.LBE55-.Ltext0
	.quad	.LBB56-.Ltext0
	.quad	.LBE56-.Ltext0
	.quad	.LBB57-.Ltext0
	.quad	.LBE57-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB58-.Ltext0
	.quad	.LBE58-.Ltext0
	.quad	.LBB64-.Ltext0
	.quad	.LBE64-.Ltext0
	.quad	.LBB65-.Ltext0
	.quad	.LBE65-.Ltext0
	.quad	.LBB71-.Ltext0
	.quad	.LBE71-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB59-.Ltext0
	.quad	.LBE59-.Ltext0
	.quad	.LBB60-.Ltext0
	.quad	.LBE60-.Ltext0
	.quad	.LBB61-.Ltext0
	.quad	.LBE61-.Ltext0
	.quad	.LBB62-.Ltext0
	.quad	.LBE62-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB74-.Ltext0
	.quad	.LBE74-.Ltext0
	.quad	.LBB77-.Ltext0
	.quad	.LBE77-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF52:
	.string	"tv_nsec"
.LASF63:
	.string	"get_time_ns"
.LASF74:
	.string	"test_clock_getres"
.LASF32:
	.string	"_vtable_offset"
.LASF51:
	.string	"tv_sec"
.LASF25:
	.string	"_IO_save_end"
.LASF20:
	.string	"_IO_write_end"
.LASF62:
	.string	"temp"
.LASF5:
	.string	"short int"
.LASF7:
	.string	"size_t"
.LASF10:
	.string	"sizetype"
.LASF69:
	.string	"rdtsc"
.LASF35:
	.string	"_offset"
.LASF30:
	.string	"_old_offset"
.LASF68:
	.string	"avTime"
.LASF14:
	.string	"_flags"
.LASF21:
	.string	"_IO_buf_base"
.LASF61:
	.string	"CPUID"
.LASF81:
	.string	"clock_getres"
.LASF26:
	.string	"_markers"
.LASF16:
	.string	"_IO_read_end"
.LASF54:
	.string	"float"
.LASF49:
	.string	"clockid_t"
.LASF71:
	.string	"start1"
.LASF76:
	.string	"test_rdtsc"
.LASF73:
	.string	"start3"
.LASF48:
	.string	"long long int"
.LASF86:
	.string	"/home/dmsc1301/experiments/test/src"
.LASF85:
	.string	"hr_timer.c"
.LASF34:
	.string	"_lock"
.LASF6:
	.string	"long int"
.LASF82:
	.string	"printf"
.LASF75:
	.string	"startres1"
.LASF31:
	.string	"_cur_column"
.LASF89:
	.string	"perror"
.LASF47:
	.string	"_pos"
.LASF70:
	.string	"test_clock_gettime"
.LASF46:
	.string	"_sbuf"
.LASF43:
	.string	"_IO_FILE"
.LASF1:
	.string	"unsigned char"
.LASF4:
	.string	"signed char"
.LASF57:
	.string	"uint64_t"
.LASF53:
	.string	"long long unsigned int"
.LASF56:
	.string	"uint32_t"
.LASF72:
	.string	"start2"
.LASF3:
	.string	"unsigned int"
.LASF44:
	.string	"_IO_marker"
.LASF33:
	.string	"_shortbuf"
.LASF80:
	.string	"clock_gettime"
.LASF84:
	.string	"GNU C 4.7.2"
.LASF9:
	.string	"__off64_t"
.LASF90:
	.string	"puts"
.LASF18:
	.string	"_IO_write_base"
.LASF42:
	.string	"_unused2"
.LASF15:
	.string	"_IO_read_ptr"
.LASF58:
	.string	"start"
.LASF22:
	.string	"_IO_buf_end"
.LASF13:
	.string	"char"
.LASF67:
	.string	"timesRun"
.LASF88:
	.string	"average_time"
.LASF36:
	.string	"__pad1"
.LASF37:
	.string	"__pad2"
.LASF38:
	.string	"__pad3"
.LASF39:
	.string	"__pad4"
.LASF40:
	.string	"__pad5"
.LASF45:
	.string	"_next"
.LASF59:
	.string	"calculate_time_ns"
.LASF2:
	.string	"short unsigned int"
.LASF0:
	.string	"long unsigned int"
.LASF19:
	.string	"_IO_write_ptr"
.LASF55:
	.string	"double"
.LASF11:
	.string	"__time_t"
.LASF8:
	.string	"__off_t"
.LASF27:
	.string	"_chain"
.LASF64:
	.string	"timeStruct"
.LASF12:
	.string	"__clockid_t"
.LASF24:
	.string	"_IO_backup_base"
.LASF78:
	.string	"stdin"
.LASF29:
	.string	"_flags2"
.LASF41:
	.string	"_mode"
.LASF17:
	.string	"_IO_read_base"
.LASF50:
	.string	"timespec"
.LASF66:
	.string	"time"
.LASF23:
	.string	"_IO_save_base"
.LASF83:
	.string	"__builtin_puts"
.LASF65:
	.string	"get_time_res"
.LASF28:
	.string	"_fileno"
.LASF77:
	.string	"prev"
.LASF60:
	.string	"rdtsc_old"
.LASF79:
	.string	"stdout"
.LASF87:
	.string	"_IO_lock_t"
	.ident	"GCC: (Debian 4.7.2-5) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
