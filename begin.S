.text
.align 4
.globl __linker_init
.globl _start
	.type _start,@function	
_start:
	mov %esp, %eax
	pushl %esp

	pushl %eax
	call __linker_init

	popl %esp
	jmp *%eax

	