	.file	"test.c"
	.local	experiment_id
	.comm	experiment_id,4,4
	.section	.rodata
	.align 8
.LC0:
	.string	"Missing arguments. Usage: %s test_id\n"
.LC1:
	.string	"%d"
	.align 8
.LC2:
	.string	"ERROR; return code from pthread_create() is %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	cmpl	$2, -20(%rbp)
	je	.L2
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$1, %edi
	call	exit
.L2:
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$experiment_id, %edx
	movl	$.LC1, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sscanf
	call	test_rdtsc
	call	set_highest_process_priority
	leaq	-8(%rbp), %rax
	movl	$0, %ecx
	movl	$pthread_main, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create
	movl	%eax, -12(%rbp)
	cmpl	$0, -12(%rbp)
	je	.L3
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$-1, %edi
	call	exit
.L3:
	movq	-8(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC3:
	.string	"Error with allocating space for the array"
.LC4:
	.string	"%s%s"
.LC5:
	.string	"/proc/interrupts"
.LC6:
	.string	"/stat"
.LC7:
	.string	"/status"
.LC8:
	.string	"LOC:"
.LC9:
	.string	"INT SUM %llu\n"
.LC10:
	.string	"voluntary_ctxt_switches:"
	.align 8
.LC11:
	.string	"PFMIN. TEST: %ld. EXP: %d DIFF: %llu LIMIT: %d\n"
	.align 8
.LC12:
	.string	"PFMAJ. TEST: %ld. EXP: %d DIFF: %llu LIMIT: %d\n"
	.align 8
.LC13:
	.string	"CS. TEST: %ld. EXP: %d DIFF: %llu LIMIT: %d\n"
	.align 8
.LC14:
	.string	"INT. TEST: %ld. EXP: %d DIFF: %llu LIMIT: %d\n"
.LC16:
	.string	"\n%d. RESULTS Clean - %d:\n"
.LC17:
	.string	"%d. %lu - %llu\n"
.LC18:
	.string	"\n%d. RESULTS Dirty - %d:\n"
	.text
	.globl	pthread_main
	.type	pthread_main, @function
pthread_main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$824, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -824(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movl	$0, -808(%rbp)
	movl	$0, %edi
	call	pin_thread_to_core
	movl	$0, -804(%rbp)
	movl	$0, -804(%rbp)
	jmp	.L6
.L31:
	movl	$1920, %edi
	call	malloc
	movq	%rax, -768(%rbp)
	cmpq	$0, -768(%rbp)
	jne	.L7
	movl	$.LC3, %edi
	call	puts
	movl	$1, %edi
	call	exit
.L7:
	movl	$1920, %edi
	call	malloc
	movq	%rax, -760(%rbp)
	cmpq	$0, -760(%rbp)
	jne	.L8
	movl	$.LC3, %edi
	call	puts
	movl	$1, %edi
	call	exit
.L8:
	movl	$0, -800(%rbp)
	movq	$1, -784(%rbp)
	jmp	.L9
.L26:
	addl	$1, -800(%rbp)
	movl	$80, %edi
	call	malloc
	movq	%rax, -752(%rbp)
	cmpq	$0, -768(%rbp)
	jne	.L10
	movl	$.LC3, %edi
	call	puts
	movl	$1, %edi
	call	exit
.L10:
	movl	$80, %edi
	call	malloc
	movq	%rax, -744(%rbp)
	cmpq	$0, -768(%rbp)
	jne	.L11
	movl	$.LC3, %edi
	call	puts
	movl	$1, %edi
	call	exit
.L11:
	movl	$0, %edi
	call	experiment_1
	call	warm_strings_with_files
	movl	$0, -796(%rbp)
	movl	$0, -792(%rbp)
	movl	$0, -796(%rbp)
	jmp	.L12
.L25:
	movq	$0, -736(%rbp)
	movq	$0, -728(%rbp)
	movq	$0, -720(%rbp)
	movq	$0, -712(%rbp)
	movq	$0, -704(%rbp)
	movq	$0, -696(%rbp)
	movq	$0, -688(%rbp)
	movq	$0, -680(%rbp)
	call	getpid
	movl	%eax, -788(%rbp)
	movabsq	$52104118038575, %rdx
	movq	%rdx, -352(%rbp)
	leaq	-344(%rbp), %rdx
	movl	$0, %eax
	movl	$11, %ecx
	movq	%rdx, %rdi
	rep stosq
	movq	%rdi, %rdx
	movl	%eax, (%rdx)
	addq	$4, %rdx
	movl	-788(%rbp), %edx
	leaq	-464(%rbp), %rax
	movl	%edx, %ecx
	movl	$.LC1, %edx
	movl	$100, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf
	leaq	-464(%rbp), %rcx
	leaq	-352(%rbp), %rdx
	leaq	-576(%rbp), %rax
	movq	%rcx, %r8
	movq	%rdx, %rcx
	movl	$.LC4, %edx
	movl	$100, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf
	movl	$.LC5, %edi
	call	file_to_string
	movq	%rax, -672(%rbp)
	leaq	-576(%rbp), %rdx
	leaq	-240(%rbp), %rax
	movl	$.LC6, %r8d
	movq	%rdx, %rcx
	movl	$.LC4, %edx
	movl	$100, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf
	leaq	-240(%rbp), %rax
	movq	%rax, %rdi
	call	file_to_string
	movq	%rax, -664(%rbp)
	leaq	-576(%rbp), %rdx
	leaq	-128(%rbp), %rax
	movl	$.LC7, %r8d
	movq	%rdx, %rcx
	movl	$.LC4, %edx
	movl	$100, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	file_to_string
	movq	%rax, -656(%rbp)
	leaq	-624(%rbp), %rax
	movq	%rax, %rdi
	call	get_time_ns
	leaq	-608(%rbp), %rax
	movq	%rax, %rdi
	call	get_time_ns
	jmp	.L13
.L15:
	leaq	-608(%rbp), %rax
	movq	%rax, %rdi
	call	get_time_ns
.L13:
	movq	-608(%rbp), %rdx
	movq	-624(%rbp), %rax
	cmpq	%rax, %rdx
	jne	.L14
	movq	-616(%rbp), %rdx
	movq	-600(%rbp), %rax
	cmpq	%rax, %rdx
	je	.L15
.L14:
	movl	experiment_id(%rip), %eax
	cmpl	$1, %eax
	jne	.L16
	movq	-784(%rbp), %rax
	movl	%eax, %edi
	call	experiment_1
.L16:
	leaq	-592(%rbp), %rax
	movq	%rax, %rdi
	call	get_time_ns
	movl	$1, %edx
	movl	$.LC8, %esi
	movl	$.LC5, %edi
	call	search_in_file
	movq	%rax, -728(%rbp)
	movl	$0, %eax
	call	get_interrupts_sum
	movl	%eax, %esi
	movl	$.LC9, %edi
	movl	$0, %eax
	call	printf
	movl	$1, %edi
	call	get_page_fault
	movq	%rax, -712(%rbp)
	movl	$2, %edi
	call	get_page_fault
	movq	%rax, -696(%rbp)
	leaq	-128(%rbp), %rax
	movl	$1, %edx
	movl	$.LC10, %esi
	movq	%rax, %rdi
	call	search_in_file
	movq	%rax, -680(%rbp)
	movq	-672(%rbp), %rax
	movl	$1, %edx
	movl	$.LC8, %esi
	movq	%rax, %rdi
	call	search_in_string
	movq	%rax, -736(%rbp)
	movq	-664(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	get_page_fault_from_string
	movq	%rax, -720(%rbp)
	movq	-664(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	get_page_fault_from_string
	movq	%rax, -704(%rbp)
	movq	-656(%rbp), %rax
	movl	$1, %edx
	movl	$.LC10, %esi
	movq	%rax, %rdi
	call	search_in_string
	movq	%rax, -688(%rbp)
	movq	-592(%rbp), %rdx
	movq	-584(%rbp), %rcx
	movq	-608(%rbp), %rsi
	movq	-600(%rbp), %rax
	movq	%rsi, %rdi
	movq	%rax, %rsi
	call	calculate_time_ns
	movq	%rax, -648(%rbp)
	movl	-796(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-744(%rbp), %rax
	addq	%rax, %rdx
	movq	-648(%rbp), %rax
	movq	%rax, (%rdx)
	movq	-784(%rbp), %rax
	movq	%rax, -640(%rbp)
	movq	-784(%rbp), %rax
	imulq	$100000, %rax, %rax
	movq	%rax, -632(%rbp)
	movq	-648(%rbp), %rax
	cmpq	-640(%rbp), %rax
	jb	.L34
	movq	-648(%rbp), %rax
	cmpq	-632(%rbp), %rax
	ja	.L34
.L18:
	movq	-720(%rbp), %rax
	movq	-712(%rbp), %rdx
	movq	%rdx, %rcx
	subq	%rax, %rcx
	movq	%rcx, %rax
	cmpq	$6, %rax
	jbe	.L20
	movq	-720(%rbp), %rax
	movq	-712(%rbp), %rdx
	movq	%rdx, %rcx
	subq	%rax, %rcx
	movl	-796(%rbp), %edx
	movq	-784(%rbp), %rax
	movl	$6, %r8d
	movq	%rax, %rsi
	movl	$.LC11, %edi
	movl	$0, %eax
	call	printf
	jmp	.L24
.L20:
	movq	-696(%rbp), %rax
	cmpq	-704(%rbp), %rax
	je	.L21
	movq	-704(%rbp), %rax
	movq	-696(%rbp), %rdx
	movq	%rdx, %rcx
	subq	%rax, %rcx
	movl	-796(%rbp), %edx
	movq	-784(%rbp), %rax
	movl	$0, %r8d
	movq	%rax, %rsi
	movl	$.LC12, %edi
	movl	$0, %eax
	call	printf
	jmp	.L24
.L21:
	movq	-680(%rbp), %rax
	cmpq	-688(%rbp), %rax
	je	.L22
	movq	-688(%rbp), %rax
	movq	-680(%rbp), %rdx
	movq	%rdx, %rcx
	subq	%rax, %rcx
	movl	-796(%rbp), %edx
	movq	-784(%rbp), %rax
	movl	$0, %r8d
	movq	%rax, %rsi
	movl	$.LC13, %edi
	movl	$0, %eax
	call	printf
	jmp	.L24
.L22:
	movq	-736(%rbp), %rax
	movq	-728(%rbp), %rdx
	movq	%rdx, %rdi
	subq	%rax, %rdi
	movq	%rdi, %rax
	cmpq	$5, %rax
	jbe	.L23
	movq	-736(%rbp), %rax
	movq	-728(%rbp), %rdx
	movq	%rdx, %rcx
	subq	%rax, %rcx
	movl	-796(%rbp), %edx
	movq	-784(%rbp), %rax
	movl	$5, %r8d
	movq	%rax, %rsi
	movl	$.LC14, %edi
	movl	$0, %eax
	call	printf
	jmp	.L24
.L23:
	movl	-792(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-752(%rbp), %rax
	addq	%rax, %rdx
	movq	-648(%rbp), %rax
	movq	%rax, (%rdx)
	addl	$1, -792(%rbp)
	jmp	.L24
.L34:
	nop
.L24:
	addl	$1, -796(%rbp)
.L12:
	cmpl	$9, -796(%rbp)
	jle	.L25
	movl	-808(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-768(%rbp), %rax
	leaq	(%rdx,%rax), %rbx
	movl	-792(%rbp), %edx
	movq	-752(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	average_time
	movq	%rax, (%rbx)
	movl	-808(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-760(%rbp), %rax
	leaq	(%rdx,%rax), %rbx
	movq	-744(%rbp), %rax
	movl	$10, %esi
	movq	%rax, %rdi
	call	average_time
	movq	%rax, (%rbx)
	addl	$1, -808(%rbp)
	movq	-752(%rbp), %rax
	movq	%rax, %rdi
	call	free
	movq	-744(%rbp), %rax
	movq	%rax, %rdi
	call	free
	movq	-784(%rbp), %rax
	movq	%rax, %rdi
	call	calculate_n
	movq	%rax, -784(%rbp)
.L9:
	cvtsi2sdq	-784(%rbp), %xmm0
	movsd	.LC15(%rip), %xmm1
	ucomisd	%xmm0, %xmm1
	ja	.L26
	movl	-800(%rbp), %edx
	movl	-804(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC16, %edi
	movl	$0, %eax
	call	printf
	movq	$1, -776(%rbp)
	movl	$1, -808(%rbp)
	jmp	.L27
.L28:
	movl	-808(%rbp), %eax
	cltq
	subq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	-768(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-776(%rbp), %rax
	leaq	0(,%rax,8), %rsi
	movl	-808(%rbp), %eax
	movq	%rdx, %rcx
	movq	%rsi, %rdx
	movl	%eax, %esi
	movl	$.LC17, %edi
	movl	$0, %eax
	call	printf
	movq	-776(%rbp), %rax
	movq	%rax, %rdi
	call	calculate_n
	movq	%rax, -776(%rbp)
	addl	$1, -808(%rbp)
.L27:
	movl	-808(%rbp), %eax
	cmpl	-800(%rbp), %eax
	jle	.L28
	movq	$1, -776(%rbp)
	movl	-800(%rbp), %edx
	movl	-804(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC18, %edi
	movl	$0, %eax
	call	printf
	movl	$1, -808(%rbp)
	jmp	.L29
.L30:
	movl	-808(%rbp), %eax
	cltq
	subq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	-760(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-776(%rbp), %rax
	leaq	0(,%rax,8), %rsi
	movl	-808(%rbp), %eax
	movq	%rdx, %rcx
	movq	%rsi, %rdx
	movl	%eax, %esi
	movl	$.LC17, %edi
	movl	$0, %eax
	call	printf
	movq	-776(%rbp), %rax
	movq	%rax, %rdi
	call	calculate_n
	movq	%rax, -776(%rbp)
	addl	$1, -808(%rbp)
.L29:
	movl	-808(%rbp), %eax
	cmpl	-800(%rbp), %eax
	jle	.L30
	movl	-800(%rbp), %ecx
	movl	-804(%rbp), %edx
	movq	-768(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	write_to_csv
	movl	-800(%rbp), %ecx
	movl	-804(%rbp), %edx
	movq	-760(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	write_to_csv
	movq	-760(%rbp), %rax
	movq	%rax, %rdi
	call	free
	movq	-768(%rbp), %rax
	movq	%rax, %rdi
	call	free
	addl	$1, -804(%rbp)
.L6:
	cmpl	$2, -804(%rbp)
	jle	.L31
	movl	$1, %eax
	movq	-24(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L33
	call	__stack_chk_fail
.L33:
	addq	$824, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	pthread_main, .-pthread_main
	.globl	pin_thread_to_core
	.type	pin_thread_to_core, @function
pin_thread_to_core:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$184, %rsp
	.cfi_offset 3, -24
	movl	%edi, -180(%rbp)
	movl	$84, %edi
	call	sysconf
	movl	%eax, -164(%rbp)
	cmpl	$0, -180(%rbp)
	js	.L36
	movl	-180(%rbp), %eax
	cmpl	-164(%rbp), %eax
	jl	.L37
.L36:
	movl	$22, %eax
	jmp	.L41
.L37:
	leaq	-144(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %eax
	movl	$16, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	movl	-180(%rbp), %eax
	cltq
	movq	%rax, -160(%rbp)
	cmpq	$1023, -160(%rbp)
	ja	.L40
	movq	-160(%rbp), %rax
	shrq	$6, %rax
	movq	-144(%rbp,%rax,8), %rdx
	movq	-160(%rbp), %rcx
	andl	$63, %ecx
	movl	$1, %esi
	movq	%rsi, %rbx
	salq	%cl, %rbx
	movq	%rbx, %rcx
	orq	%rcx, %rdx
	movq	%rdx, -144(%rbp,%rax,8)
.L40:
	call	pthread_self
	movq	%rax, -152(%rbp)
	leaq	-144(%rbp), %rdx
	movq	-152(%rbp), %rax
	movl	$128, %esi
	movq	%rax, %rdi
	call	pthread_setaffinity_np
.L41:
	addq	$184, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	pin_thread_to_core, .-pin_thread_to_core
	.globl	set_highest_process_priority
	.type	set_highest_process_priority, @function
set_highest_process_priority:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$-20, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	setpriority
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	set_highest_process_priority, .-set_highest_process_priority
	.section	.rodata
	.align 8
.LC15:
	.long	0
	.long	1097859072
	.ident	"GCC: (Ubuntu/Linaro 4.7.3-1ubuntu1) 4.7.3"
	.section	.note.GNU-stack,"",@progbits
