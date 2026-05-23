 ПРЫГАЮЩИЙ ШАРИК (упрощённо) 

section .data
    pos     dd  0.0
    vel     dd  2.5
    grav    dd  0.3
    bounce  dd  -0.9
    ground  dd  15
    speed   dd  40
    score   dd  0
    newline db  10
    ball    db  '       O', 0
    score_msg db '  Score: ', 0

section .text
    global _start

_start:
loop:
    call    clear_screen
    
    ; Проверка клавиши (упрощённо)
    call    check_key
    cmp     al, 'q'
    je      exit
    
    ; Рисование шарика
    call    draw_ball
    
    ; Физика
    movss   xmm0, [vel]
    addss   xmm0, [grav]     ; vel += gravity
    movss   [vel], xmm0
    
    movss   xmm0, [pos]
    addss   xmm0, [vel]      ; pos += vel
    movss   [pos], xmm0
    
    ; Проверка пола
    movss   xmm0, [pos]
    movss   xmm1, [ground]
    comiss  xmm0, xmm1
    jb      check_ceiling
    
    ; Отскок от пола
    movss   xmm0, [ground]
    movss   [pos], xmm0
    movss   xmm0, [vel]
    mulss   xmm0, [bounce]
    movss   [vel], xmm0
    inc     dword [score]
    jmp     delay

check_ceiling:
    ; Проверка потолка
    xorps   xmm1, xmm1
    comiss  xmm0, xmm1
    jae     delay
    
    ; Отскок от потолка
    xorps   xmm0, xmm0
    movss   [pos], xmm0
    movss   xmm0, [vel]
    abs     xmm0, xmm0
    mulss   xmm0, [bounce]
    movss   [vel], xmm0

delay:
    ; Задержка
    mov     eax, [speed]
    call    sleep_ms
    
    jmp     loop

exit:
    call    clear_screen
    ; Вывод финального счёта
    ; ...
    mov     eax, 60         ; sys_exit
    xor     edi, edi
    syscall

clear_screen:
    ; Очистка экрана
    mov     eax, 4          ; sys_write
    mov     edi, 1          ; stdout
    mov     esi, CSI        ; "\033[2J\033[H"
    mov     edx, 8
    syscall
    ret

draw_ball:
    ; Рисование пустых строк + шарика
    ; ... (сложная логика с циклами)
    ret
