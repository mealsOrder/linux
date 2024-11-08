.global main
.text
.data
    fizz_string:     .asciz "Fizz\n"
    buzz_string:     .asciz "Buzz\n"
    fizzbuzz_string: .asciz "FizzBuzz\n"

main:
    stp x29, x30, [sp, -16]!  
    mov x29, sp

    mov x19, 1  

loop:
    mov x0, x19    // 출력할 숫자를 x0에 저장
    mov x1, xzr    // 초기화: Fizz/Buzz 여부 확인용 플래그

    // 3의 배수 검사
    mov x2, x19
    mov x3, 3
    udiv x4, x2, x3
    msub x5, x4, x3, x2
    cbnz x5, check_buzz

    adrp x0, fizz_string    // fizz_string의 페이지 주소 로드
    add x0, x0, :lo12:fizz_string
    mov x1, 1

check_buzz:
    // 5의 배수 검사
    mov x2, x19
    mov x3, 5
    udiv x4, x2, x3
    msub x5, x4, x3, x2
    cbnz x5, print_result

    adrp x0, buzz_string    // buzz_string의 페이지 주소 로드
    add x0, x0, :lo12:buzz_string
    cmp x1, 1
    bne print_result

    adrp x0, fizzbuzz_string
    add x0, x0, :lo12:fizzbuzz_string

print_result:
    bl printf

    add x19, x19, 1
    cmp x19, 101
    bne loop

    ldp x29, x30, [sp], 16
    mov x0, xzr
    ret


