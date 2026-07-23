org 0x7C00

xor ax, ax
mov ds, ax
mov ss, ax
mov sp, 0x7C00

mov ah, 0
mov al, 3
int 10h

; enable a20 gate
mov ax, 0x2401
int 15h
jc err

; check for a20 gate
call check_a20

lba_packet:
        db 0x10   ; packet size
        db 0x00   ; reserved
        dw 120     ; sectors
        dw 0x0000 ; offset
        dw 0x1000 ; segment
        dq 1      ; start

mov si, lba_packet
mov ah, 0x42
int 13h
jc err

lgdt [gdt_descriptor]

cli
mov eax, cr0
or eax, 1
mov cr0, eax
jmp 0x08:protected_mode

[bits 32]
protected_mode:
        mov ax, 0x10
        mov ds, ax
        mov ss, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov esp, 0x80000

        jmp 0x10000
.hlt:
        jmp .hlt

; physical a20 check
check_a20:
        ; 0x0000:0x0000 = 0xAA
        xor ax, ax
        mov ds, ax
        mov bx, ax
        mov al, 0xAA
        mov [bx], al

        ; 0xFFFF:0x0010 = 0xBB
        mov ax, 0xFFFF
        mov ds, ax
        mov bx, 0x0010
        mov al, 0xBB
        mov [bx], al

        ; check if 0x0000 was rewritten
        xor ax, ax
        mov ds, ax
        mov bx, ax
        mov al, [bx]
        cmp al, 0xBB

        je err
        ret

; error shit
err:
        mov ah, 0 ; if everything goes wrong, it sets
        mov al, 0 ; the shitty text mode
        int 10h
        hlt
        jmp err

gdt_start:
        ; null descriptor
        dd 0,0

gdt_r0_code:
        dw 0xFFFF      ; limit (bits 0 - 15)
        dw 0x0000      ; base  (bits 0 - 15)
        db 0x00        ; base  (bit 16 - 23)
        db 0b10011010  ; access byte (present, ring0, code r/x)
        db 0b11001111  ; g=1, d=1, l=0, avl=0
        db 0x00        ; base  (bit 24 - 31)

gdt_r0_data:
        dw 0xFFFF      ; limit (bits 0 - 15)
        dw 0x0000      ; base  (bits 0 - 15)
        db 0x00        ; base  (bit 16 - 23)
        db 0b10010010  ; acces byte (present, ring0, data, r/w)
        db 0b11001111  ; g=1, d=1, l=0, avl=0
        db 0x00

gdt_r3_code:
        dw 0xFFFF      ; limit (bits 0 - 15)
        dw 0x0000      ; base  (bits 0 - 15)
        db 0x00        ; base  (bit 16 - 23)
        db 0b11111010  ; access byte (present, ring3, code r/x)
        db 0b11001111  ; g=1, d=1, l=0, avl=0
        db 0x00

gdt_r3_data:
        dw 0xFFFF      ; limit (bits 0 - 15)
        dw 0x0000      ; base  (bits 0 - 15)
        db 0x00        ; base  (bit 16 - 23)
        db 0b11110010  ; acces byte (present, ring3, data, r/w)
        db 0b11001111  ; g=1, d=1, l=0, avl=0
        db 0x00

gdt_end:
gdt_descriptor:
        dw gdt_end - gdt_start - 1
        dd gdt_start

times 510 - ($ - $$) db 0
dw 0xAA55
