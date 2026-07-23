%macro VECTOR 1
global isr%1
isr%1:
    %if (%1 == 8 || (%1 >= 10 && %1 <= 14) || %1 == 17 || %1 == 21 || %1 == 29 || %1 == 30)
        push %1
        jmp isr_common
    %else
        push 0
        push %1
        jmp isr_common
    %endif
%endmacro

%include "src/sys/vectors.s"

extern idt_handler

isr_common:
    pushad
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    cld

    mov eax, esp
    and esp, 0xFFFFFFF0
    push eax

    call idt_handler

    mov esp, [esp]

    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 8
    iret
