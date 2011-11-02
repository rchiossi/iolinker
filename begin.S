.text
.align 4
.globl _ld_start
	.type _ld_start,@function	
_ld_start:
	mov %esp, %eax
	pushl %esp

	pushl %eax
	call __linker_init

	popl %esp
	jmp *%eax

	