#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

#define ROOM_WIDTH 12
#define HME_POS 1
#define BWL_POS (ROOM_WIDTH - 2)
#define CAT_NAME "고먐미"

int turn = 1;
int intimacy = 2;   // 집사와의 관계 (0~4)
int mood = 3;       // 야옹이 기분 (0~3)
int cp = 0;         // cp (상점에서 사용)
int soup_c = 0;     // 수프 개수
int cat_pos = HME_POS; // 고양이 위치
int prev_pos = HME_POS; // 고양이 이전 위치

int main(void) {
    srand((unsigned int)time(NULL));


    printf("**** 야옹이와 수프 ****\n\n");
    printf("@@@ 여기에 ASCII art 그리기 @@@\n\n");
    printf("       /\\_/\\\n");
    printf(" /\\   / o o \\\n");
    printf("//\\\\  \\~(*)~/\n");
    printf("`  \\/    ^ /\n");
    printf("  |  \\|| ||\n");
    printf("  \\  '|| ||\n");
    printf("   \\ )()-())\n");

    printf("고양이 이름은 '%s'입니다.\n\n", CAT_NAME);

    Sleep(3000);

    while (1) {
        clear_screen();
        printf("==================== Turn %d ====================\n", turn);

        // 1. 상태 출력
        print_status();

    }

	return 0;
}

// 상태 출력
void print_status() {
    printf("==================== 현재 상태 ====================\n");
    printf("현재까지 만든 수프: %d개\n", soup_c);
    printf("CP: %d 포인트\n", cp);
    printf("%s의 기분(0~3): %d\n", CAT_NAME, mood);
    switch (mood) {
    case 0: printf("기분이 매우 나쁩니다.\n"); break;
    case 1: printf("심심해합니다.\n"); break;
    case 2: printf("식빵을 굽습니다.\n"); break;
    case 3: printf("골골송을 부릅니다.\n"); break;
    }
    printf("집사와의 관계(0~4): %d\n", intimacy);
    switch (intimacy) {
    case 0: printf("곁에 오는 것조차 싫어합니다.\n"); break;
    case 1: printf("간식 자판기 취급입니다.\n"); break;
    case 2: printf("그럭저럭 쓸 만한 집사입니다.\n"); break;
    case 3: printf("훌륭한 집사로 인정 받고 있습니다.\n"); break;
    case 4: printf("집사 껌딱지입니다.\n"); break;
    }
    printf("==================================================\n\n");
    Sleep(1000);
}

// 화면 지우기
void clear_screen() {
    system("cls");
}