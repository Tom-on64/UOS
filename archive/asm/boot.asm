org 0x7c00
bits 16

%define ENDL 0x0a, 0x0d
mov [diskNum], dl

start:
    ; Setup the stack
    mov bp, 0x7c00
    mov sp, bp

    mov bx, msg
    call puts

    ; INT 0x13:
    ;   al - Amount of sectors to read
    ;   ch - Cylinder number
    ;   dh - Head number
    ;   cl - Sector number 
    ;   dl - Drive number 
    ;   es:bx - Load pointer

    mov ah, 2
    mov al, 1 ; 1 Sector (512B)
    mov ch, 0 ; Cylinder 1
    mov dh, 0 ; Head 1
    mov cl, 2 ; Sector 2
    mov dl, [diskNum] ; Drive number
    push ax ; Save ax
    mov ax, 0 ; Can't modify es directly
    mov es, ax
    mov bx, 0x7e00 ; es * 16 + bx | 0 * 16 + 0x7e00 = 0x7e00
    pop ax 
    int 0x13 
;success:
    mov ah, 0x0e
    mov al, [0x7e00]
    int 0x10

    hlt

;
; Prints a string to the screen
; Args:
;   bx - String pointer
;
puts:
    push ax
    mov ah, 0x0e
.loop: 
    mov al, [bx]
    or al, al
    jz .done
    int 0x10
    inc bx
    jmp .loop
.done: 
    pop ax
    ret

;
; Reads a user input string terminated by a newline
; Args:
;   bx - Pointer to buffer
; Returns: Read string into the buffer
;
reads:
    push ax
    mov al, 0
.loop:
    cmp al, 0x0d
    je .done
    mov ah, 0
    int 0x16
    mov ah, 0x0e
    int 0x10
    mov [bx], al
    inc bx
    jmp .loop
.done:
    mov ah, 0x0e
    mov al, [newline]
    int 0x10
    mov al, 0
    dec bx
    mov [bx], al
    pop ax
    ret

; Data
msg: db "Hey!", ENDL, 0
data: times 16 db 0

; Sys
newline: db ENDL
diskNum: db 0

times 510-($-$$) db 0
dw 0xAA55

times 512 db 'A'