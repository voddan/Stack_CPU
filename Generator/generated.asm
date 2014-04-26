; 64-bit "Hello World!" in Linux NASM
global main 

extern dump_obj 
extern init_obj
extern del_obj

extern obj;
extern head;

;extern Obj_execute;

section .text
main:
	; sys_write(stdout, message, length)
	mov    rax, 1        ; sys_write
	mov    rdi, 1        ; stdout
	mov    rsi, message_start
	mov    rdx, message_start_len
	syscall
	;;;;;;;;;;;;;;;;;;;;;;;;
	
	call init_obj
	;call head.dump_obj
	call del_obj
	
	;;;;;;;;;;;;;;;;;;;;;;;
	; sys_write(stdout, message, length)
	
	mov    rax, 1        ; sys_write
	mov    rdi, 1        ; stdout
	mov    rsi, message_finish
	mov    rdx, message_finish_len
	syscall
	
	; sys_exit(return_code)
	
	mov    rax, 60        ; sys_exit
	mov    rdi, 0        ; return 0 (success)
	syscall
 
section .data
message_start:		db 'started..' ,0x0A
message_start_len 	equ $-message_start

message_finish:		db 'finished..',0x0A
message_finish_len 	equ $-message_finish
 
