    .data
str_num:    .asciz "%d\n"
str_fizz:   .asciz "Fizz\n"
str_buzz:   .asciz "Buzz\n"
str_fizzbuzz: .asciz "FizzBuzz\n"

    .global main
    .text

main:
    stp x29, x30, [sp, -16]!    // 스택에 x29, x30 저장
    mov x29, sp                 // 프레임 포인터 설정
    mov x19, 1                  // x19를 1로 초기화 (카운터)

loop:
    cmp x19, 100                // x19가 100보다 큰지 비교
    bgt end_loop                // 100보다 크면 종료

    // 15로 나누어 떨어지는지 확인 (FizzBuzz)
    mov w0, w19                 // w19의 값을 w0에 복사
    mov w1, 15
    bl mod_check
    cbz w0, print_fizzbuzz      // 결과가 0이면 FizzBuzz 출력

    // 3으로 나누어 떨어지는지 확인 (Fizz)
    mov w0, w19
    mov w1, 3
    bl mod_check
    cbz w0, print_fizz          // 결과가 0이면 Fizz 출력

    // 5로 나누어 떨어지는지 확인 (Buzz)
    mov w0, w19
    mov w1, 5
    bl mod_check
    cbz w0, print_buzz          // 결과가 0이면 Buzz 출력

    // 그 외에는 숫자 출력
    ldr x0, =str_num
    mov x1, x19
    bl printf
    b increment_counter         // 다음 숫자로 이동

print_fizzbuzz:
    ldr x0, =str_fizzbuzz
    bl printf
    b increment_counter

print_fizz:
    ldr x0, =str_fizz
    bl printf
    b increment_counter

print_buzz:
    ldr x0, =str_buzz
    bl printf

increment_counter:
    add x19, x19, 1             // 카운터 증가
    b loop                      // 루프 재실행

end_loop:
    ldp x29, x30, [sp], 16      // 스택에서 레지스터 복원
    mov x0, xzr                 // x0에 0 저장 (반환값)
    ret                         // 반환

// 나머지 계산 함수 (mod_check)
// w0: 피제수, w1: 제수
mod_check:
    udiv w2, w0, w1             // w0 / w1의 몫 계산
    msub w0, w2, w1, w0         // w0 - (w2 * w1) 계산 (나머지)
    ret
