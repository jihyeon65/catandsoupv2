#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define ROOM_WIDTH 5
#define HME_POS 1
#define BWL_POS (ROOM_WIDTH - 2)

int main(void) {
    srand((unsigned int)time(NULL));

    int intimacy = 2; // 관계
    int soup_c = 0; // 수프의 개수
    int cat_w = HME_POS; // 고양이 위치
    int prev_w = HME_POS; // 고양이의 이전 위치
    int choice = 0;

    printf("**** 야옹이와 수프 ****\n\n");
    printf("@@@ 여기에 ASCII art 그리기 @@@\n\n");
    printf("       /\\_/\\\n");
    printf(" /\\   / o o \\\n");
    printf("//\\\\  \\~(*)~/\n");
    printf("`  \\/    ^ /\n");
    printf("  |  \\|| ||\n");
    printf("  \\  '|| ||\n");
    printf("   \\ )()-())\n");

    printf("고양이 이름은 '고먐미'입니다.\n");

    Sleep(1000);
    system("cls");

    while (1) {
        printf("==================== 현재 상태 ===================\n");
        printf("현재까지 만든 수프: %d개\n", soup_c);
        printf("집사와의 관계(0~4): %d\n", intimacy);
        switch (intimacy) {
        case 0: printf("곁에 오는 것조차 싫어합니다.\n");
            break;
        case 1: printf("간식 자판기 취급입니다.\n");
            break;
        case 2: printf("그럭저럭 쓸 만한 집사입니다.\n");
            break;
        case 3: printf("훌륭한 집사로 인정 받고 있습니다.\n");
            break;
        case 4: printf("집사 껌딱지입니다.\n");
            break;
        }
        printf("==================================================\n\n");

        prev_w = cat_w;
        int move_dice = rand() % 6 + 1;
        printf("\n고먐미 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n");
        printf("주사위 눈이 %d 이상이면 냄비 쪽으로 이동합니다.\n", 6 - intimacy);
        printf("주사위를 굴립니다. 또르륵...\n");
        printf("%d이(가) 나왔습니다!\n", move_dice);

        if (move_dice >= (6 - intimacy)) {
            if (cat_w < BWL_POS) cat_w++;
            printf("냄비 쪽으로 움직입니다.\n");
        }
        else {
            if (cat_w > HME_POS) cat_w--;
            printf("집 쪽으로 움직입니다.\n");
        }

        if (cat_w == HME_POS) {
            printf("고먐미는 자신의 집에서 편안함을 느낍니다.\n");
        }

        Sleep(500);


        for (int i = 0; i < ROOM_WIDTH; i++)
            printf("#");

        printf("\n");

        for (int i = 0; i < ROOM_WIDTH; i++) {
            if (i == ROOM_WIDTH - 1 || i == 0)
                printf("#");
            else if (i == 1)
                printf("H");
            else if (i == ROOM_WIDTH - 2)
                printf("B");
            else
                printf(" ");
        }

        printf("\n");

        for (int i = 0; i < ROOM_WIDTH; i++) {
            if (i == ROOM_WIDTH - 1 || i == 0)
                printf("#");
            else if (i == cat_w)
                printf("C");
            else if (i == prev_w)
                printf(".");
            else
                printf(" ");
        }

        printf("\n");

        for (int i = 0; i < ROOM_WIDTH; i++)
            printf("#");

        printf("\n어떤 상호작용을 하시겠습니까?  0. 아무것도 하지 않음  1. 긁어 주기\n");

        do {
            printf(">>");
            scanf_s("%d", &choice);
        } while (choice != 0 && choice != 1);
        Sleep(500);

        int dice = rand() % 6 + 1;
        if (choice == 0) {
            printf("아무것도 하지 않습니다.\n");
            printf("4/6의 확률로 친밀도가 떨어집니다.\n");
            printf("주사위를 굴립니다. 또르륵...\n");
            printf("%d이(가) 나왔습니다!\n", dice);
            if (dice <= 4) {
                if (intimacy > 0) intimacy--;
                printf("친밀도가 떨어집니다.");
            }
            else {
                printf("다행히 친밀도가 떨어지지 않았습니다.");
            }
            printf("\n현재 친밀도: %d\n", intimacy);
        }
        else if (choice == 1) {
            printf("고먐미의 턱을 긁어주었습니다.\n");
            printf("2/6의 확률로 친밀도가 높아집니다.\n");
            printf("주사위를 굴립니다. 또르륵...\n");
            printf("%d이(가) 나왔습니다!\n", dice);
            if (dice >= 5) {
                if (intimacy < 4) intimacy++;
                printf("친밀도가 높아집니다.");
            }
            else {
                printf("친밀도는 그대로입니다.");
            }
            printf("\n현재 친밀도: %d\n", intimacy);
        }

        Sleep(500);

        if (cat_w == BWL_POS) {
            int soup_type = rand() % 3;
            switch (soup_type) {
            case 0: printf("고먐미가 감자 수프를 만들었습니다!\n");
                break;
            case 1: printf("고먐미가 양송이 수프를 만들었습니다!\n");
                break;
            case 2: printf("고먐미가 브로콜리 수프를 만들었습니다!\n");
                break;
            }
            soup_c++;
        }


        Sleep(2500);
        system("cls");
    }
}