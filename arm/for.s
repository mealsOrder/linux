    .data
str: .asciz "i : %d\n"
    .global main
    .text
main:
    stp x29, x30, [sp, -16]!
    mov x19, 1

1:
    cmp x19, 10
    bgt 2f
    ldr x0, =str
    mov x1, x19
    bl printf
    add x19, x19, 1
    b 1b

2:
    ldp x29, x30, [sp], 16    // 스택에서 레지스터 복원
    mov x0, xzr               // x0에 0 저장 (반환값)
    ret
