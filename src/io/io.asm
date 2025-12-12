section .asm

/*Hardware port I/O boundary*/
global insb
global insw
global outb
global outw

insb:    /*Input byte from I/O port*/
    push ebp
    mov ebp, esp

    xor eax, eax
    mov edx, [ebp+8]
    in al, dx

    pop ebp
    ret

insw:    /*Input word from I/O port*/
    push ebp
    mov ebp, esp

    xor eax, eax
    mov edx, [ebp+8]
    in ax, dx

    pop ebp
    ret

outb:    /*Output byte from I/O port*/
    push ebp
    mov ebp, esp

    mov eax, [ebp+8]
    mov edx, [ebp+12]
    out dx, al

    pop ebp
    ret

outw:    /*Output word from I/O port*/
    push ebp
    mov ebp, esp

    mov eax, [ebp+12]
    mov edx, [ebp+8]
    out dx, ax

    pop ebp
    ret
