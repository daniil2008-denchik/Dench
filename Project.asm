extern SDL_Init 
extern SDL_CreateWindow 
extern SDL_CreateRenderer 
extern SDL_DestroyRenderer 
extern SDL_DestroyWindow 
extern SDL_Quit 
extern SDL_PollEvent 
extern SDL_GetTicks 
extern SDL_Delay 
extern SDL_SetRenderDrawColor 
extern SDL_RenderClear 
extern SDL_RenderDrawLine 
extern SDL_RenderPresent 
extern SDL_GetError 
extern printf 
extern exit 
 
 
; SDL2 constants 
SDL_INIT_VIDEO      equ 0x00000020 
SDL_WINDOWPOS_CENTERED equ 0x2FFF0000 
SDL_RENDERER_ACCELERATED equ 0x00000002 
SDL_RENDERER_PRESENTVSYNC equ 0x00000004 
 
; Event types 
SDL_QUIT            equ 0x100 
SDL_KEYDOWN         equ 0x300 
SDLK_ESCAPE         equ 27 
 
 
SCREEN_WIDTH        equ 800 
SCREEN_HEIGHT       equ 600 
BALL_RADIUS         equ 20 
FPS                 equ 60 
FRAME_DELAY         equ 1000 / FPS 
 
; Цвета (R, G, B, A) 
COLOR_BLACK         equ 0x000000FF  ; ARGB: чёрный 
COLOR_WHITE         equ 0xFFFFFFFF  ; ARGB: белый 
 
 
section .data 
     
    window_title    db "Ball Simulation in Assembly", 0 
     
     
    err_sdl_init    db "SDL_Init failed: %s", 10, 0 
    err_window      db "SDL_CreateWindow failed: %s", 10, 0 
    err_renderer    db "SDL_CreateRenderer failed: %s", 10, 0 
     
     
    gravity         dq 0.15 
    boost           dq 1.08 
    max_speed       dq 30.0 
    radius          dq 20.0 
    screen_width    dq 800.0 
    screen_height   dq 600.0 
    zero            dq 0.0 
    one             dq 1.0 
    minus_one       dq -1.0 
 
 
section .bss 
     
    window          resq 1      ; SDL_Window* 
    renderer        resq 1      ; SDL_Renderer* 
     
    ;  
    ball_x          resq 1      ;  
    ball_y          resq 1      ;  
    ball_vx         resq 1      ;  
    ball_vy         resq 1      ;  
     
    ; Для событий 
    event           resb 56     ;  
     
    ; Для контроля FPS 
    frame_start     resd 1      ;  
    frame_time      resd 1      ;  
     
     
    running         resb  
 
 
%macro check_result 2 
    test    eax, eax 
    jnz     %1 
    %2 
%endmacro 
 
 
%macro fld_const 1 
    fld     qword [%1] 
%endmacro 
 
 
section .text 
    global main 
 
 
main: 
    push    rbp 
    mov     rbp, rsp 
    sub     rsp, 32          
     
    mov     ecx, SDL_INIT_VIDEO 
    call    SDL_Init 
    test    eax, eax 
    jnz     .sdl_init_failed 
     
     
    mov     rcx, window_title 
    mov     edx, SDL_WINDOWPOS_CENTERED 
    mov     r8d, SDL_WINDOWPOS_CENTERED 
    mov     r9d, SCREEN_WIDTH 
    push    SCREEN_HEIGHT 
    push    0               ;  
    sub     rsp, 32         ;  
    call    SDL_CreateWindow 
    add     rsp, 48         ; 
     
    test    rax, rax 
    jz      .window_failed 
    mov     [window], rax 
     
     
    mov     rcx, rax        ; window 
    mov     edx, -1         ; auto select driver 
    mov     r8d, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC 
    call    SDL_CreateRenderer 
     
    test    rax, rax 
    jz      .renderer_failed 
    mov     [renderer], rax 
     
 
    call    init_ball 
     
     
    mov     byte [running], 1 
     
.main_loop: 
    cmp     byte [running], 0 
    je      .exit_program 
     
     
    call    SDL_GetTicks 
    mov     [frame_start], eax 
     
     
    call    handle_events 
     
     
    call    update_ball 
     
 
    call    render_frame 
     
     
    call    sdl_delay_frame 
     
    jmp     .main_loop 
 
.exit_program: 
     
    mov     rcx, [renderer] 
    call    SDL_DestroyRenderer 
     
    mov     rcx, [window] 
    call    SDL_DestroyWindow 
     
    call    SDL_Quit 
     
    xor     eax, eax        ; return 0 
    jmp     .done 
 
 
.sdl_init_failed: 
    call    print_sdl_error 
    mov     ecx, 1 
    call    exit 
 
.window_failed: 
    call    print_sdl_error 
    call    SDL_Quit
