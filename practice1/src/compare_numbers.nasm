section .text
global compare_numbers

compare_numbers:
    ; Inputs:
    ;   [ebp + 8]  = First number
    ;   [ebp + 12] = Second number
    ; Output:
    ;   EAX = Greater number

    mov eax, [ebp + 8]       ; Move the first number to EAX
    cmp eax, [ebp + 12]      ; Compare EAX with the second number
    jg  greater             ; Jump to 'greater' if EAX is greater than the second number
    mov eax, [ebp + 12]      ; Move the second number to EAX if it is greater
    ret

greater:
    ret

