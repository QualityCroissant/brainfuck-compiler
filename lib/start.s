section .data
	array db 30000 dup 0
	pointer dq array

section .text
	global _start

%macro increment 0
	mov rsi, [pointer]
	inc byte [rsi]
%endmacro

%macro decrement 0
	mov rsi, [pointer]
	dec byte [rsi]
%endmacro

%macro increment_pointer 0
	inc qword [pointer]
%endmacro

%macro decrement_pointer 0
	dec qword [pointer]
%endmacro

%macro start_block 1
.block%1%+:
	mov rsi, [pointer]
	movzx rsi, byte [rsi]
	test rsi, rsi
	jz .end_block%1
%endmacro

%macro end_block 1
	jmp .block%1
.end_block%1%+:
%endmacro

%macro output 0
	mov rdi, 1
	mov rsi, [pointer]
	mov rdx, 1

	mov rax, 1
	syscall
%endmacro

%macro input 0
	mov rdi, 0
	mov rsi, [pointer]
	mov rdx, 1

	mov rax, 0
	syscall
%endmacro

_start:


