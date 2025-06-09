#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

#define ROOM_WIDTH 12
#define HME_POS 1
#define BWL_POS (ROOM_WIDTH - 2)
#define CAT_NAME "��ι�"

int turn = 1;
int intimacy = 2;   // ������� ���� (0~4)
int mood = 3;       // �߿��� ��� (0~3)
int cp = 0;         // cp (�������� ���)
int soup_c = 0;     // ���� ����
int cat_pos = HME_POS; // ����� ��ġ
int prev_pos = HME_POS; // ����� ���� ��ġ

// ���̱ⱸ �� �峭��
bool has_scratcher = false;
bool has_cat_tower = false;
bool has_toy_mouse = false;
bool has_laser_pointer = false;

// ���̱ⱸ ��ġ
int scratcher_pos = -1;
int cat_tower_pos = -1;


int main(void) {
    srand((unsigned int)time(NULL));


    printf("**** �߿��̿� ���� ****\n\n");
    printf("@@@ ���⿡ ASCII art �׸��� @@@\n\n");
    printf("       /\\_/\\\n");
    printf(" /\\   / o o \\\n");
    printf("//\\\\  \\~(*)~/\n");
    printf("`  \\/    ^ /\n");
    printf("  |  \\|| ||\n");
    printf("  \\  '|| ||\n");
    printf("   \\ )()-())\n");

    printf("����� �̸��� '%s'�Դϴ�.\n\n", CAT_NAME);

    Sleep(3000);

    // ���� ��
    while (1) {
        clear_screen();
        printf("==================== Turn %d ====================\n", turn);

        // ���� ���
        print_status();

        // ��� ��ȭ (ù �� ����)
        if (turn > 1) {
            handle_mood_change();
        }
        // �̵�
        handle_movement();

		// �ൿ
        handle_action();

        // ��׸���
        draw_room();

		// ��ȣ�ۿ�
        handle_interaction();

		// CP ����
        produce_cp();

        // 9. ����
        enter_shop();
    }

	return 0;
}

// ���� ���
void print_status() {
    printf("==================== ���� ���� ====================\n");
    printf("������� ���� ����: %d��\n", soup_c);
    printf("CP: %d ����Ʈ\n", cp);
    printf("%s�� ���(0~3): %d\n", CAT_NAME, mood);
    switch (mood) {
    case 0: printf("����� �ſ� ���޴ϴ�.\n"); break;
    case 1: printf("�ɽ����մϴ�.\n"); break;
    case 2: printf("�Ļ��� �����ϴ�.\n"); break;
    case 3: printf("������ �θ��ϴ�.\n"); break;
    }
    printf("������� ����(0~4): %d\n", intimacy);
    switch (intimacy) {
    case 0: printf("�翡 ���� ������ �Ⱦ��մϴ�.\n"); break;
    case 1: printf("���� ���Ǳ� ����Դϴ�.\n"); break;
    case 2: printf("�׷����� �� ���� �����Դϴ�.\n"); break;
    case 3: printf("�Ǹ��� ����� ���� �ް� �ֽ��ϴ�.\n"); break;
    case 4: printf("���� �������Դϴ�.\n"); break;
    }
    printf("==================================================\n\n");
    Sleep(1000);
}

// ��� ��ȭ
void handle_mood_change() {

    int dice = rand() % 6 + 1;
    printf("�ֻ����� �����ϴ�. �Ǹ���... %d��(��) ���Խ��ϴ�.\n", dice);

    if (dice <= 6 - intimacy) {
        printf("�ƹ� ���� ���� ����� �������ϴ�. ����̴ϱ�?\n");
        printf("%s�� ����� �������ϴ�: %d -> %d\n", CAT_NAME, mood, mood > 0 ? mood - 1 : 0);
        if (mood > 0) mood--;
    }
    else {
        printf("����� �״���Դϴ�.\n");
    }
    printf("\n");
    Sleep(1500);
}

// �� �׸���
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

// �̵�
void handle_movement() {
    prev_pos = cat_pos;

    switch (mood) {
    case 0: // ������
        if (cat_pos > HME_POS) {
            cat_pos--;
            printf("����� �ſ� ���� %s��(��) ������ ���մϴ�.\n", CAT_NAME);
        }
        else {
            printf("%s��(��) ���� �ӹ��� �ֽ��ϴ�.\n", CAT_NAME);
        }
        break;
    case 1: // ���̱ⱸ��
        if (!has_scratcher && !has_cat_tower) {
            printf("��Ÿ��� ��� ����� �ſ� �������ϴ�.\n");
            if (mood > 0) mood--;
        }
        else {
            int target_pos = -1;
            // �ΰ� �� ������ �� ����� ������
            if (has_scratcher && has_cat_tower) {
                target_pos = abs(cat_pos - scratcher_pos) <= abs(cat_pos - cat_tower_pos) ? scratcher_pos : cat_tower_pos;
            }
            else if (has_scratcher) {
                target_pos = scratcher_pos;
            }
            else { // ĹŸ���� ���� ��
                target_pos = cat_tower_pos;
            }

            const char* toy_name = (target_pos == scratcher_pos) ? "��ũ��ó" : "ĹŸ��";
            printf("%s��(��) �ɽ��ؼ� %s ������ �̵��մϴ�.\n", CAT_NAME, toy_name);

            if (cat_pos < target_pos) cat_pos++;
            else if (cat_pos > target_pos) cat_pos--;
        }
        break;
    case 2: // ���ڸ�
        printf("%s��(��) ��� ���� �Ļ��� ���� �ֽ��ϴ�.\n", CAT_NAME);
        break;
    case 3: // �����
        if (cat_pos < BWL_POS) {
            cat_pos++;
            printf("%s��(��) ������ �θ��� ������ ���鷯 ���ϴ�.\n", CAT_NAME);
        }
        else {
            printf("%s��(��) ���� �տ� �ӹ��� �ֽ��ϴ�.\n", CAT_NAME);
        }
        break;
    }
    printf("\n");
    Sleep(1500);
}

// �ൿ
void handle_action() {
    if (prev_pos == cat_pos) {
        if (cat_pos == HME_POS) {
            printf("%s��(��) ������ �� ���� ���� ����� �������ϴ�.\n", CAT_NAME);
            if (mood < 3) mood++;
        }
        return;
    }

    bool action_taken = false;
    if (cat_pos == BWL_POS) {
        int soup_type = rand() % 3;
        const char* soup_name;
        switch (soup_type) {
        case 0: soup_name = "����"; break;
        case 1: soup_name = "�����"; break;
        default: soup_name = "����ݸ�"; break;
        }
        printf("%s�� %s ������ ��������ϴ�!\n", CAT_NAME, soup_name);
        soup_c++;
        action_taken = true;
    }
    else if (has_scratcher && cat_pos == scratcher_pos) {
        printf("%s��(��) ��ũ��ó�� �ܰ� ��ҽ��ϴ�.\n", CAT_NAME);
        if (mood < 3) {
            printf("����� ���� ���������ϴ�: %d -> %d\n", mood, mood + 1);
            mood++;
        }
        else {
            printf("����� �ְ��Դϴ�!\n");
        }
        action_taken = true;
    }
    else if (has_cat_tower && cat_pos == cat_tower_pos) {
        printf("%s��(��) ĹŸ���� �پ�ٴմϴ�.\n", CAT_NAME);
        int prev_mood = mood;
        mood += 2;
        if (mood > 3) mood = 3;
        printf("����� ���� ���������ϴ�: %d -> %d\n", prev_mood, mood);
        action_taken = true;
    }

    if (!action_taken) {
        printf("%s��(��) Ư���� �ൿ�� ���� �ʾҽ��ϴ�.\n", CAT_NAME);
    }
    printf("\n");
    Sleep(1500);
}

// ��ȣ �ۿ�
void handle_interaction() {
    int choice = -1;
    int max_choice = 1;

    printf("� ��ȣ�ۿ��� �Ͻðڽ��ϱ�?\n");
    printf("0. �ƹ��͵� ���� ����\n");
    printf("1. �ܾ� �ֱ�\n");

    int toy_mouse_num = -1, laser_pointer_num = -1;
    if (has_toy_mouse) {
        max_choice++;
        toy_mouse_num = max_choice;
        printf("%d. �峭�� ��� ��� �ֱ�\n", toy_mouse_num);
    }
    if (has_laser_pointer) {
        max_choice++;
        laser_pointer_num = max_choice;
        printf("%d. ������ �����ͷ� ��� �ֱ�\n", laser_pointer_num);
    }

    while (1) {
        printf(">> ");
        scanf_s("%d", &choice);
        if (choice >= 0 && choice <= max_choice) {
            break;
        }
        printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
    }

    int dice = rand() % 6 + 1;
    printf("�ֻ����� �����ϴ�. �Ǹ���... %d��(��) ���Խ��ϴ�!\n", dice);

    if (choice == 0) {
        printf("�ƹ��͵� ���� �ʽ��ϴ�.\n");
        printf("%s�� ����� ���������ϴ�: %d -> %d\n", CAT_NAME, mood, mood > 0 ? mood - 1 : 0);
        if (mood > 0) mood--;
        if (dice <= 5) {
            printf("������� ���谡 �������ϴ�.\n");
            if (intimacy > 0) intimacy--;
        }
    }
    else if (choice == 1) {
        printf("%s�� ���� �ܾ��־����ϴ�.\n", CAT_NAME);
        printf("%s�� ����� �״���Դϴ�: %d\n", CAT_NAME, mood);
        if (dice >= 5) {
            printf("������� ���谡 �������ϴ�.\n");
            if (intimacy < 4) intimacy++;
        }
    }
    else if (has_toy_mouse && choice == toy_mouse_num) {
        printf("�峭�� ��� %s�� ����־����ϴ�.\n", CAT_NAME);
        int prev_mood = mood;
        if (mood < 3) mood++;
        printf("%s�� ����� ���� ���������ϴ�: %d -> %d\n", CAT_NAME, prev_mood, mood);
        if (dice >= 4) {
            printf("������� ���谡 �������ϴ�.\n");
            if (intimacy < 4) intimacy++;
        }
    }
    else if (has_laser_pointer && choice == laser_pointer_num) {
        printf("������ �����ͷ� %s�� �ų��� ����־����ϴ�.\n", CAT_NAME);
        int prev_mood = mood;
        mood += 2;
        if (mood > 3) mood = 3;
        printf("%s�� ����� �� ���������ϴ�: %d -> %d\n", CAT_NAME, prev_mood, mood);
        if (dice >= 2) {
            printf("������� ���谡 �������ϴ�.\n");
            if (intimacy < 4) intimacy++;
        }
    }

    printf("\n");
    Sleep(2000);
}

// CP ����
void produce_cp() {
    int cp_gain = (mood > 1 ? mood - 1 : 0) + intimacy;

    printf("%s�� ���(0~3): %d\n", CAT_NAME, mood);
    printf("������� ģ�е�(0~4): %d\n", intimacy);

    if (cp_gain > 0) {
        printf("%s�� ��а� ģ�е��� ���� CP�� %d ����Ʈ ����Ǿ����ϴ�.\n", CAT_NAME, cp_gain);
        cp += cp_gain;
    }
    else {
        printf("CP�� ������� �ʾҽ��ϴ�.\n");
    }
    printf("���� CP: %d ����Ʈ\n\n", cp);
    Sleep(2000);
}



// ����
void enter_shop() {
    int choice = -1;
    printf("--- ���� ---\n");
    printf("������ �湮�Ͻðڽ��ϱ�? (1. ��, 0. �ƴϿ�)\n>> ");
    scanf_s("%d", &choice);

    if (choice != 1) {
        printf("������ ���ɴϴ�.\n");
        return;
    }

    while (1) {
        clear_screen();
        printf("--- ���� ---\n");
        printf("���� CP: %d\n\n", cp);
        printf("� ������ �����Ͻðڽ��ϱ�?\n");
        printf("0. �ƹ��͵� ���� �ʴ´�.\n");
        printf("1. �峭�� ��: 1 CP %s\n", has_toy_mouse ? "(ǰ��)" : "");
        printf("2. ������ ������: 2 CP %s\n", has_laser_pointer ? "(ǰ��)" : "");
        printf("3. ��ũ��ó: 4 CP %s\n", has_scratcher ? "(ǰ��)" : "");
        printf("4. Ĺ Ÿ��: 6 CP %s\n", has_cat_tower ? "(ǰ��)" : "");

        printf(">> ");
        scanf_s("%d", &choice);

        if (choice == 0) {
            break;
        }

        switch (choice) {
        case 1:
            if (has_toy_mouse) printf("�峭�� �㸦 �̹� �����߽��ϴ�.\n");
            else if (cp >= 1) {
                cp -= 1; has_toy_mouse = true;
                printf("�峭�� �㸦 �����߽��ϴ�. ���� CP %d ����Ʈ\n", cp);
            }
            else printf("CP�� �����մϴ�.\n");
            break;
        case 2:
            if (has_laser_pointer) printf("������ �����͸� �̹� �����߽��ϴ�.\n");
            else if (cp >= 2) {
                cp -= 2; has_laser_pointer = true;
                printf("������ �����͸� �����߽��ϴ�. ���� CP %d ����Ʈ\n", cp);
            }
            else printf("CP�� �����մϴ�.\n");
            break;
        case 3:
            if (has_scratcher) printf("��ũ��ó�� �̹� �����߽��ϴ�.\n");
            else if (cp >= 4) {
                cp -= 4; has_scratcher = true;
                scratcher_pos = get_empty_furniture_pos();
                printf("��ũ��ó�� �����߽��ϴ�. ���� %d ��ġ�� ��ġ�˴ϴ�. ���� CP %d ����Ʈ\n", scratcher_pos, cp);
            }
            else printf("CP�� �����մϴ�.\n");
            break;
        case 4:
            if (has_cat_tower) printf("Ĺ Ÿ���� �̹� �����߽��ϴ�.\n");
            else if (cp >= 6) {
                cp -= 6; has_cat_tower = true;
                cat_tower_pos = get_empty_furniture_pos();
                printf("Ĺ Ÿ���� �����߽��ϴ�. ���� %d ��ġ�� ��ġ�˴ϴ�. ���� CP %d ����Ʈ\n", cat_tower_pos, cp);
            }
            else printf("CP�� �����մϴ�.\n");
            break;
        default:
            printf("������ ��� ���Դϴ�. �ٽ� �Է����ּ���.\n");
        }
        Sleep(2000);
    }
}
// ���̱ⱸ ���� �� ������ ��ġ ����
int get_empty_furniture_pos() {
    int pos;
    while (1) {
        pos = rand() % (BWL_POS - HME_POS - 2) + (HME_POS + 2);
        if (pos != scratcher_pos && pos != cat_tower_pos) {
            return pos;
        }
    }
}




// ȭ�� �����
void clear_screen() {
    system("cls");
}