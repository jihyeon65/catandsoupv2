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

    while (1) {
        clear_screen();
        printf("==================== Turn %d ====================\n", turn);

        // 1. ���� ���
        print_status();

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

// ȭ�� �����
void clear_screen() {
    system("cls");
}