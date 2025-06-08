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

// 놀이기구 및 장난감
bool has_scratcher = false;
bool has_cat_tower = false;
bool has_toy_mouse = false;
bool has_laser_pointer = false;

// 놀이기구 위치
int scratcher_pos = -1;
int cat_tower_pos = -1;


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

    // 게임 턴
    while (1) {
        clear_screen();
        printf("==================== Turn %d ====================\n", turn);

        // 상태 출력
        print_status();

        // 기분 변화 (첫 턴 제외)
        if (turn > 1) {
            handle_mood_change();
        }
        // 이동
        handle_movement();

		// 행동
        handle_action();

        // 방그리기
        draw_room();

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

// 기분 변화
void handle_mood_change() {
    printf("--- 기분 변화 ---\n");
    int dice = rand() % 6 + 1;
    printf("주사위를 굴립니다. 또르륵... %d이(가) 나왔습니다.\n", dice);

    if (dice <= 6 - intimacy) {
        printf("아무 이유 없이 기분이 나빠집니다. 고양이니까?\n");
        printf("%s의 기분이 나빠집니다: %d -> %d\n", CAT_NAME, mood, mood > 0 ? mood - 1 : 0);
        if (mood > 0) mood--;
    }
    else {
        printf("기분은 그대로입니다.\n");
    }
    printf("\n");
    Sleep(1500);
}

// 방 그리기
void draw_room() {
    char furniture_line[ROOM_WIDTH + 1];
    char cat_line[ROOM_WIDTH + 1];

    for (int i = 0; i < ROOM_WIDTH; i++) {
        furniture_line[i] = ' ';
        cat_line[i] = ' ';
    }
    furniture_line[ROOM_WIDTH] = '\0';
    cat_line[ROOM_WIDTH] = '\0';

    furniture_line[0] = '#';
    furniture_line[ROOM_WIDTH - 1] = '#';
    furniture_line[HME_POS] = 'H';
    furniture_line[BWL_POS] = 'B';
    if (has_scratcher) furniture_line[scratcher_pos] = 'S';
    if (has_cat_tower) furniture_line[cat_tower_pos] = 'T';

    cat_line[0] = '#';
    cat_line[ROOM_WIDTH - 1] = '#';
    if (cat_pos != prev_pos) {
        cat_line[prev_pos] = '.';
    }
    cat_line[cat_pos] = 'C';

    printf("\n");
    for (int i = 0; i < ROOM_WIDTH; i++) printf("#");
    printf("\n");
    printf("%s\n", furniture_line);
    printf("%s\n", cat_line);
    for (int i = 0; i < ROOM_WIDTH; i++) printf("#");
    printf("\n\n");
    Sleep(500);
}

// 이동
void handle_movement() {
    prev_pos = cat_pos;
    printf("--- %s의 이동 ---\n", CAT_NAME);

    switch (mood) {
    case 0: // 집으로
        if (cat_pos > HME_POS) {
            cat_pos--;
            printf("기분이 매우 나쁜 %s은(는) 집으로 향합니다.\n", CAT_NAME);
        }
        else {
            printf("%s은(는) 집에 머물러 있습니다.\n", CAT_NAME);
        }
        break;
    case 1: // 놀이기구로
        if (!has_scratcher && !has_cat_tower) {
            printf("놀거리가 없어서 기분이 매우 나빠집니다.\n");
            if (mood > 0) mood--;
        }
        else {
            int target_pos = -1;
            // 두개 다 있으면 더 가까운 곳으로
            if (has_scratcher && has_cat_tower) {
                target_pos = abs(cat_pos - scratcher_pos) <= abs(cat_pos - cat_tower_pos) ? scratcher_pos : cat_tower_pos;
            }
            else if (has_scratcher) {
                target_pos = scratcher_pos;
            }
            else { // 캣타워만 있을 때
                target_pos = cat_tower_pos;
            }

            const char* toy_name = (target_pos == scratcher_pos) ? "스크래처" : "캣타워";
            printf("%s은(는) 심심해서 %s 쪽으로 이동합니다.\n", CAT_NAME, toy_name);

            if (cat_pos < target_pos) cat_pos++;
            else if (cat_pos > target_pos) cat_pos--;
        }
        break;
    case 2: // 제자리
        printf("%s은(는) 기분 좋게 식빵을 굽고 있습니다.\n", CAT_NAME);
        break;
    case 3: // 냄비로
        if (cat_pos < BWL_POS) {
            cat_pos++;
            printf("%s은(는) 골골송을 부르며 수프를 만들러 갑니다.\n", CAT_NAME);
        }
        else {
            printf("%s은(는) 냄비 앞에 머물러 있습니다.\n", CAT_NAME);
        }
        break;
    }
    printf("\n");
    Sleep(1500);
}

// 행동
void handle_action() {
    if (prev_pos == cat_pos) {
        if (cat_pos == HME_POS) {
            printf("%s은(는) 집에서 한 턴을 쉬어 기분이 좋아집니다.\n", CAT_NAME);
            if (mood < 3) mood++;
        }
        return;
    }

    printf("--- %s의 행동 ---\n", CAT_NAME);
    bool action_taken = false;
    if (cat_pos == BWL_POS) {
        int soup_type = rand() % 3;
        const char* soup_name;
        switch (soup_type) {
        case 0: soup_name = "감자"; break;
        case 1: soup_name = "양송이"; break;
        default: soup_name = "브로콜리"; break;
        }
        printf("%s가 %s 수프를 만들었습니다!\n", CAT_NAME, soup_name);
        soup_c++;
        action_taken = true;
    }
    else if (has_scratcher && cat_pos == scratcher_pos) {
        printf("%s은(는) 스크래처를 긁고 놀았습니다.\n", CAT_NAME);
        if (mood < 3) {
            printf("기분이 조금 좋아졌습니다: %d -> %d\n", mood, mood + 1);
            mood++;
        }
        else {
            printf("기분이 최고입니다!\n");
        }
        action_taken = true;
    }
    else if (has_cat_tower && cat_pos == cat_tower_pos) {
        printf("%s은(는) 캣타워를 뛰어다닙니다.\n", CAT_NAME);
        int prev_mood = mood;
        mood += 2;
        if (mood > 3) mood = 3;
        printf("기분이 제법 좋아졌습니다: %d -> %d\n", prev_mood, mood);
        action_taken = true;
    }

    if (!action_taken) {
        printf("%s은(는) 특별한 행동을 하지 않았습니다.\n", CAT_NAME);
    }
    printf("\n");
    Sleep(1500);
}

// 화면 지우기
void clear_screen() {
    system("cls");
}