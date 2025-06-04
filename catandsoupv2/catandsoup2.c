#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define ROOM_WIDTH 5
#define HME_POS 1
#define BWL_POS (ROOM_WIDTH - 2)

int main(void) {
    srand((unsigned int)time(NULL));

    int intimacy = 2; // ����
    int soup_c = 0; // ������ ����
    int cat_w = HME_POS; // ����� ��ġ
    int prev_w = HME_POS; // ������� ���� ��ġ
    int choice = 0;

    printf("**** �߿��̿� ���� ****\n\n");
    printf("@@@ ���⿡ ASCII art �׸��� @@@\n\n");
    printf("       /\\_/\\\n");
    printf(" /\\   / o o \\\n");
    printf("//\\\\  \\~(*)~/\n");
    printf("`  \\/    ^ /\n");
    printf("  |  \\|| ||\n");
    printf("  \\  '|| ||\n");
    printf("   \\ )()-())\n");

    printf("����� �̸��� '��ι�'�Դϴ�.\n");

    Sleep(1000);
    system("cls");

    while (1) {
        printf("==================== ���� ���� ===================\n");
        printf("������� ���� ����: %d��\n", soup_c);
        printf("������� ����(0~4): %d\n", intimacy);
        switch (intimacy) {
        case 0: printf("�翡 ���� ������ �Ⱦ��մϴ�.\n");
            break;
        case 1: printf("���� ���Ǳ� ����Դϴ�.\n");
            break;
        case 2: printf("�׷����� �� ���� �����Դϴ�.\n");
            break;
        case 3: printf("�Ǹ��� ����� ���� �ް� �ֽ��ϴ�.\n");
            break;
        case 4: printf("���� �������Դϴ�.\n");
            break;
        }
        printf("==================================================\n\n");

        prev_w = cat_w;
        int move_dice = rand() % 6 + 1;
        printf("\n��ι� �̵�: ����� ģ���Ҽ��� ���� ������ �� Ȯ���� �������ϴ�.\n");
        printf("�ֻ��� ���� %d �̻��̸� ���� ������ �̵��մϴ�.\n", 6 - intimacy);
        printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
        printf("%d��(��) ���Խ��ϴ�!\n", move_dice);

        if (move_dice >= (6 - intimacy)) {
            if (cat_w < BWL_POS) cat_w++;
            printf("���� ������ �����Դϴ�.\n");
        }
        else {
            if (cat_w > HME_POS) cat_w--;
            printf("�� ������ �����Դϴ�.\n");
        }

        if (cat_w == HME_POS) {
            printf("��ι̴� �ڽ��� ������ ������� �����ϴ�.\n");
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

        printf("\n� ��ȣ�ۿ��� �Ͻðڽ��ϱ�?  0. �ƹ��͵� ���� ����  1. �ܾ� �ֱ�\n");

        do {
            printf(">>");
            scanf_s("%d", &choice);
        } while (choice != 0 && choice != 1);
        Sleep(500);

        int dice = rand() % 6 + 1;
        if (choice == 0) {
            printf("�ƹ��͵� ���� �ʽ��ϴ�.\n");
            printf("4/6�� Ȯ���� ģ�е��� �������ϴ�.\n");
            printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
            printf("%d��(��) ���Խ��ϴ�!\n", dice);
            if (dice <= 4) {
                if (intimacy > 0) intimacy--;
                printf("ģ�е��� �������ϴ�.");
            }
            else {
                printf("������ ģ�е��� �������� �ʾҽ��ϴ�.");
            }
            printf("\n���� ģ�е�: %d\n", intimacy);
        }
        else if (choice == 1) {
            printf("��ι��� ���� �ܾ��־����ϴ�.\n");
            printf("2/6�� Ȯ���� ģ�е��� �������ϴ�.\n");
            printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
            printf("%d��(��) ���Խ��ϴ�!\n", dice);
            if (dice >= 5) {
                if (intimacy < 4) intimacy++;
                printf("ģ�е��� �������ϴ�.");
            }
            else {
                printf("ģ�е��� �״���Դϴ�.");
            }
            printf("\n���� ģ�е�: %d\n", intimacy);
        }

        Sleep(500);

        if (cat_w == BWL_POS) {
            int soup_type = rand() % 3;
            switch (soup_type) {
            case 0: printf("��ι̰� ���� ������ ��������ϴ�!\n");
                break;
            case 1: printf("��ι̰� ����� ������ ��������ϴ�!\n");
                break;
            case 2: printf("��ι̰� ����ݸ� ������ ��������ϴ�!\n");
                break;
            }
            soup_c++;
        }


        Sleep(2500);
        system("cls");
    }
}