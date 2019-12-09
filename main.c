#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RBtree.h"
#include "ADJlist.h";

int reserve_check_number; //RBtree �迭�� ������ ��

void group_20_aircraft_print();
void squre_box_print1();
void squre_box_print2();
void squre_box_print3();
void random_reserve(RBtree t);
int main() {
	RBtree t = RBtree_create();
	group_20_aircraft_print(); //air print
	random_City_Position(city);
	random_reserve(t);
	make_ADJlist();
	int choose_number;
	printf("***********************************************************************************************************************\n");

	while (1) {

		printf("***********************************\n");
		printf("    �ش��ϴ� ���ڸ� �Է��ϼ���!\n");
		printf(" \n    ***  �������� ���� : 1 ***\n");
		printf(" \n    ***  ���� ��ȸ : 2  *** \n");
		printf(" \n    ***  ���� ��� : 3  *** \n");
		printf(" \n    ***  ����� ���� : 4  *** \n");
		printf(" \n    ***  ����   : -1  *** \n\n");
		printf("***********************************\n");

		printf("  -> ");
		scanf("%d", &choose_number);
		printf("\n\n");
		//	while (1) {


		if (choose_number == 1) {

			int reserve_number;
			int temp_date_check = 0;
			squre_box_print1();
			printf("\n -> ");
			scanf("  %s", reservation[reserve_check_number].source, 20);
			PrintList(reservation[reserve_check_number].source[0]);

			squre_box_print2();
			printf("\n -> ");
			scanf("%s", reservation[reserve_check_number].destination, 20);

			squre_box_print3();

			printf("\n -> ");
			scanf("%d", &temp_date_check);
			if (temp_date_check > 31) {
				while (1) {
					printf("��¥�� �ٽ� �Է��ϼ���!\n");
					scanf("%d", &temp_date_check);
					if (temp_date_check <= 31) break;
				}
			}
			else
				reservation[reserve_check_number].date = temp_date_check;

			//make_route(reservation[reserve_check_number].source, reservation[reserve_check_number].destination, reservation[reserve_check_number].date);
			//printf("��� : \n");
			printf(" \n -> ���� �Ͻðڽ��ϱ�? \n");
			printf(" 1  : �� \n");
			printf(" 2  : �ƴϿ�\n");

			printf("\n -> ");
			scanf("%d", &reserve_number);
			printf("\n");

			if (reserve_number == 1) {

				printf("�̸� : ");
				scanf("%s", reservation[reserve_check_number].name, 10);
				printf("��");  //ù��° ��
				for (int i = 0; i < 28; i++) printf("��");
				printf("��\n");
				printf("�� ");//�ι�° ��
				printf(" ������ �Ϸ��Ͽ����ϴ�.");
				printf("    �� \n");
				printf("��");
				printf("  ���� ��ȣ��  %d��  �Դϴ�.", reserve_check_number);
				printf(" �� \n");
				printf("��");  //���� ° ��
				for (int i = 0; i < 28; i++) printf("��");
				printf("��\n\n");
				reservation[reserve_check_number].reservation_number = reserve_check_number;

				array_RBTree[reserve_check_number] = reserve_check_number;
				RBtree_insert(t, (void*)array_RBTree[reserve_check_number], compare_int);
				reserve_check_number++;

			}
		}
		else if (choose_number == 2) {
			int check = 0;
			printf("���� ��ȣ�� �Է��ϼ��� -> ");
			scanf("%d", &check);
			printf("\n\n");
			if (RBtree_search_node(t->root, check) != NULL) {
				printf("��");  //ù��° ��
				for (int i = 0; i < 20; i++) printf("��");
				printf("��\n");
				printf("��"); //�ι�° ��
				printf(" ���� ��ȣ : %d", reservation[check].reservation_number);
				if (reservation[check].reservation_number >= 10)
					printf("     �� \n");
				else
					printf("      �� \n");
				printf("�� ");
				printf("�� �̸� : %s", reservation[check].name);
				for (int i = 0; i < 20 - (13 + strlen(reservation[check].name)); i++) 	printf(" ");
				printf("�� \n");
				printf("�� ");
				printf("�����    : %s", reservation[check].source);

				for (int i = 0; i < 20 - (13 + strlen(reservation[check].source)); i++) 	printf(" ");
				printf("�� \n");
				printf("�� ");
				printf("������    : %s", reservation[check].destination);
				for (int i = 0; i < 20 - (13 + strlen(reservation[check].destination)); i++) 	printf(" ");
				printf("�� \n");
				printf("�� ");
				printf("��߳�¥  : %d", reservation[check].date);
				if (reservation[check].date >= 10)
					printf("     �� \n");
				else
					printf("      �� \n");
				printf("��");  //���� ° ��
				for (int i = 0; i < 20; i++) printf("��");
				printf("��\n\n");

			}

			else if (RBtree_search_node(t->root, check) == NULL) {
				printf("��");  //ù��° ��
				for (int i = 0; i < 28; i++) printf("��");
				printf("��\n");
				printf("�� ");
				printf("��ȸ���� �ʴ� ��ȣ �Դϴ�!");
				printf(" �� \n");
				printf("��");  //���� ° ��
				for (int i = 0; i < 28; i++) printf("��");
				printf("��\n\n");
			}
			//	break;
		}
		else if (choose_number == 3) {
			int check;
			printf("���� ��ȣ�� �Է��ϼ��� -> ");
			scanf("%d", &check);
			printf("\n\n");
			if (RBtree_search_node(t->root, check) != NULL) {
				RBtree_delete(t, (void*)check, compare_int);
				printf("��");  //ù��° ��
				for (int i = 0; i < 25; i++) printf("��");
				printf("��\n");
				printf("�� ");
				printf("������ ��ҵǾ����ϴ�!");
				printf("  �� \n");
				printf("��");  //���� ° ��
				for (int i = 0; i < 25; i++) printf("��");
				printf("��\n\n");
			}
			else printf("��ȸ���� �ʴ� ��ȣ �Դϴ�.\n\n");
			//break;
		}
		else if (choose_number == 4) {
			char airport;
			int flight_day = 0;
			printf("��");  //ù��° ��
			for (int i = 0; i < 44; i++) printf("��");
			printf("��\n");
			printf("�� ");
			printf("���� ������ ���� ���� ���ø� �Է����ּ���");
			printf("  �� \n");
			printf("��");  //���� ° ��
			for (int i = 0; i < 44; i++) printf("��");
			printf("��\n\n");
			printf("-> ");
			scanf("%s", &airport);
			printf("\n");
			squre_box_print3();
			printf("��");  //ù��° ��
			for (int i = 0; i < 44; i++) printf("��");
			printf("��\n");
			printf("�� ");
			printf("���� ������ ���� ���� ��¥�� �Է����ּ���");
			printf("  �� \n");
			printf("��");  //���� ° ��
			for (int i = 0; i < 44; i++) printf("��");
			printf("��\n\n");
			printf("-> ");
			scanf("%d", &flight_day);
			printf("\n");
			PrintListTime(airport, flight_day);

		}

		else  if (choose_number != -1 && choose_number > 3) {
			printf("�ٽ� �Է����ּ��� !\n\n\n ");
		}
		if (choose_number == -1) {
			printf("��ȸ�� �����մϴ�!\n");
			exit(1);
		}
		///	}	
			//if (choose_number == -1) break;
	}

	return 0;

}

void group_20_aircraft_print() {

	printf("               _                              _           ___   ___          _            _                  \n");
	printf("              | |                            | |         |__ \\ / _ \\        (_)          | |                 \n");
	printf(" __      _____| | ___ ___  _ __ ___   ___    | |_ ___       ) | | | |   __ _ _ _ __ _ __ | | __ _ _ __   ___ \n");
	printf(" \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\   | __/ _ \\     / /| | | |  / _` | | '__| '_ \\| |/ _` | '_ \\ / _ \\ \n");
	printf("  \\ V  V /  __/ | (_| (_) | | | | | |  __/   | || (_) |   / /_| |_| | | (_| | | |  | |_) | | (_| | | | |  __/\n");
	printf("   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|    \\__\\___/   |____|\\___/   \\__,_|_|_|  | .__/|_|\\__,_|_| |_|\\___|\n");
	printf("                                                                                   | |                       \n");
	printf("                                                                                   |_|                       ");

	printf("\n                                ___\n");
	printf("                                \\\\ \\ \n");
	printf("                                 \\\\ `\\ \n");
	printf("              ___                 \\\\  \\ \n");
	printf("             |    \\                \\\\  `\\ \n");
	printf("             |_____\\                \\    \\ \n");
	printf("             |______\\                \\    `\\\n");
	printf("             |       \\                \\     \\ \n");
	printf("             |      __\\__---------------------------------._. \n");
	printf("           __|---~~~__o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_[][\\__ \n");
	printf("          |___                         /~      )                \\__ \n");
	printf("              ~~~---..._______________/      ,/_________________/ \n");
	printf("                                     /      / \n");
	printf("                                    /     ,/ \n");
	printf("                                   /     / \n");
	printf("                                  /    ,/ \n");
	printf("                                 /    /\n");
	printf("                                //  ,/\n");
	printf("                               //  /\n");
	printf("                              // ,/\n");
	printf("                             //_/\n");
	printf("                    _  _\n");
	printf("                   ( `   )_\n");
	printf("                  (    )    `)\n");
	printf("                (_   (_ .  _) _)\n");
	printf("                                     _\n");
	printf("                                    (  )\n");
	printf("     _ .                         ( `  ) . )\n");
	printf("   (  _ )_                      (_, _(  ,_)_)\n");
	printf(" (_  _(_ ,)\n");
}
void squre_box_print1() {
	printf("��");  //ù��° ��
	for (int i = 0; i < 10; i++) printf("��");
	printf("��\n");
	printf("��"); //�ι�° ��
	printf("  �����  ");
	printf("�� \n");
	printf("��");  //���� ° ��
	for (int i = 0; i < 10; i++) printf("��");
	printf("��\n");
}
void squre_box_print2() {
	printf("��");  //ù��° ��
	for (int i = 0; i < 10; i++) printf("��");
	printf("��\n");
	printf("��"); //�ι�° ��
	printf("  ������  ");
	printf("�� \n");
	printf("��");  //���� ° ��
	for (int i = 0; i < 10; i++) printf("��");
	printf("��\n");
}
void squre_box_print3() {
	printf("��");  //ù��° ��
	for (int i = 0; i < 12; i++) printf("��");
	printf("��\n");
	printf("��"); //�ι�° ��
	printf("  ��� ��¥ ");
	printf("�� \n");
	printf("��");  //���� ° ��
	for (int i = 0; i < 12; i++) printf("��");
	printf("��\n");


	int i = 0;
	int start = 0;
	const char* wname[7] = { "��","��","ȭ","��","��","��","��" };

	printf("                   << 2019�� 12��>>\n");//�� ���
	printf("======================================================\n");
	for (i = 0; i < 7; i++)//���� ���
	{
		printf("%7s", wname[i]);//���� 7�� ����
	}
	printf("\n");

	for (i = 0; i < start; i++)//ù �� �����ϱ��� ���� ���
	{
		printf("%7s", " ");//���� 7�� ����
	}
	for (i = 0; i < 31; i++)//�� ���
	{
		printf("%7d", i + 1);//���� 7�� ����
		start++;
		if (start == 7)//������ 7�̸�
		{
			start = 0;//0���� ����
			printf("\n");//���� ���
		}
	}
	printf("\n======================================================\n");
}
void random_reserve(RBtree t) {
	char* cusname = (char*)malloc(sizeof(char) * 10);
	char alpha = 'a';
	for (int i = 0; i < 500; i++) {
		int namelen = rand() % 7 + 1;
		int start = rand() % 26;
		int arrive = rand() % 26;
		int sdate = rand() % 26;
		for (int j = 0; j < namelen; j++) {
			alpha = rand() % 26 + 'a';
			cusname[j] = alpha;

		}
		cusname[namelen] = '\0';
		strcpy(reservation[reserve_check_number].name, cusname);
		reservation[reserve_check_number].source[0] = (char)(start + 'a');
		reservation[reserve_check_number].destination[0] = (char)(arrive + 'a');
		reservation[reserve_check_number].date = sdate + 1;
		reservation[reserve_check_number].reservation_number = reserve_check_number;
		array_RBTree[reserve_check_number] = reserve_check_number;
		RBtree_insert(t, (void*)array_RBTree[reserve_check_number], compare_int);
		reserve_check_number++;
	}
}