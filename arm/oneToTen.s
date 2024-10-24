.global main      // main 함수를 글로벌 심볼로 선언
.text             // 코드 섹션 시작

main:  
    stp x29, x30, [sp, -16]!  // 스택에 x29와 x30 저장 후, 스택 포인터 조정
    mov x29, sp               // 프레임 포인터 설정

    mov x19, 1                // x19에 1 저장 (초기값)
loop:
    mov x1, x19               // 출력할 정수를 x1에 저장
    ldr x0, =format_string    // 포맷 문자열 주소를 x0에 로드
    bl printf                 // printf 호출

    add x19, x19, 1           // x19를 1 증가
    cmp x19, 11               // x19와 11을 비교 (10까지 출력)
    bne loop                  // 11이 아니면 loop로 분기

    ldp x29, x30, [sp], 16    // 스택에서 레지스터 복원
    mov x0, xzr               // x0에 0 저장 (반환값)
    ret                       // 함수 종료

.data                         // 데이터 섹션 시작
format_string: .asciz "%d\n"  // 정수 출력용 포맷 문자열
