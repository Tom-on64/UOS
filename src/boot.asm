[org 0x7c00]
[bits 16]

mov [BOOT_DISK], dl     ; Save the disk number

start:
    mov ah, 0x0e
    mov al, 'A'
    int 0x13

    ; Setup the stack
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov bp, 0x8000
    mov sp, bp

    mov ah, 0
    mov al, 3
    int 0x10            ; Text mode + clear screen

    mov bx, KERNEL_LOC
    mov dh, 20          ; !!! If something breaks, this is probably too small :/ !!!

    mov ah, 2           ; Sector to start at
    mov al, dh          ; Number of sectors to read
    mov ch, 0           ; Cylinder number
    mov dh, 0           ; Head number
    mov cl, 2           ; Sector number
    mov dl, [BOOT_DISK] ; Drive number
    int 0x13            ; TODO: Error management

    cli
    lgdt [GDT_Descriptor]
    ; Change last bit of cr0 to 1
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    ; Far jump to code
    jmp CODE_SEG:start_protected_mode
    hlt

[bits 32]
start_protected_mode:
    mov ax, DATA_SEG    ; Setup segment registers and stack
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp

    jmp KERNEL_LOC      ; Jump to kernel 
    hlt

; General Descriptor Table
GDT_Start:
    null_descriptor:
        dd 0 ; four null bytes
        dd 0 ; four null bytes
    code_descriptor:
        dw 0xffff ; First bits of limit
        dw 0 ; 16 bits +
        db 0 ; + 8 bits = 24 bits
        db 0b10011010 ; p, p, t, type flags
        db 0b11001111 ; Other flags + limit (last 4 bits)
        db 0 ; base (last 8 bits)
    data_descriptor:
        dw 0xffff ; First bits of limit
        dw 0 ; 16 bits +
        db 0 ; + 8 bits = 24 bits
        db 0b10010010 ; p, p, t, type flags
        db 0b11001111 ; Other flags + limit (last 4 bits)
        db 0 ; base (last 8 bits)
GDT_End:

GDT_Descriptor:
    dw GDT_End - GDT_Start - 1  ; Size
    dd GDT_Start                ; Start

CODE_SEG equ code_descriptor - GDT_Start
DATA_SEG equ data_descriptor - GDT_Start
KERNEL_LOC equ 0x1000
BOOT_DISK: db 0

times 510-($-$$) db 0
dw 0xaa55 ; Magic number :)
