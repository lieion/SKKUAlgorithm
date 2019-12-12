#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "RBtree.h"
#include "ADJlist.h"

int reserve_check_number; //RBtree �迭�� ������ ��

void group_20_aircraft_print();

void squre_box_print();
void random_reserve(RBtree t);
void source_name(); //����� ���
void destination_name();// ������ ��� 
void source_date(); //��� ��¥ ���
void seat_print(RBtree t, char start, char dest); //�¼� ���� ���
int seatCheck(RBtree t, char start, char dest, int str, int num);

int main() {
	srand(time(NULL));
	RBtree t = RBtree_create();
	group_20_aircraft_print(); //air print
	random_City_Position(city);
	random_reserve(t);
	make_ADJlist();
	int choose_number;

	printf("***********************************************************************************************************************\n");

	printf("\t\t\t\t\tRed-Black tree height : %d \n", RBtree_height(t->root));
	printf("\t\t\t\t\tRed-Black tree  count node : %d\n ", count_node(t->root));

	while (1) {
		printf("\t\t\t\t\t***********************************\n");
		printf("\t\t\t\t\t    �ش��ϴ� ���ڸ� �Է��ϼ���!\n");
		printf("\n\t\t\t\t\t    ***  �������� ���� : 1 ***\n");
		printf("\n\t\t\t\t\t     ***  ���� ��ȸ : 2  *** \n");
		printf("\n\t\t\t\t\t     ***  ���� ��� : 3  *** \n");
		printf("\n\t\t\t\t\t     ***  ����   : -1  *** \n\n");
		printf("\n\t\t\t\t\t***********************************\n");

		int  flag;
		do {
			flag = 0;
			printf("\t\t\t\t\t  -> ");

			if (!scanf("\t\t\t\t\t %d", &choose_number)) {
				printf("\t\t\t\t\t���ڰ� �ƴմϴ�. \n\n");
				flag = 1;
				while (getchar() != '\n');
			}
		} while (flag);

		if (choose_number == 1) {

			int reserve_number;
			int temp_date_check = 0;
			char airport;
			char arrive;
			int flight_day = 0;

			for (int j = 0; j < 2; j++) {
				if (j == 0) {
					//���� ���� ��� 
					source_name();  //����� 
					printf("\t\t\t\t\t-> ");
					scanf("  %c", &reservation[reserve_check_number].source);
					if (!isalpha(reservation[reserve_check_number].source)) {
						while (1) {
							printf("\t\t\t\t\t���ڷ� �Է����ּ���! \n");
							printf("\t\t\t\t\t-> ");
							scanf("  %c", &reservation[reserve_check_number].source);
							if (isalpha(reservation[reserve_check_number].source))
								break;
						}
					}
					airport = reservation[reserve_check_number].source;
					printf("\n");

					squre_box_print(); //��� ��¥ box
					source_date();


					int  flag0;
					do {
						flag0 = 0;
						printf("\t\t\t\t\t  -> ");

						if (!scanf("\t\t\t\t\t%d", &temp_date_check)) {
							printf("\t\t\t\t\t���ڰ� �ƴմϴ�. \n\n");
							flag0 = 1;
							while (getchar() != '\n');
						}
					} while (flag0);

					if (temp_date_check > 31 || temp_date_check < 0) {
						while (1) {
							printf("\t\t\t\t\t��¥�� �ٽ� �Է��ϼ���!\n");

							int  flag5;
							do {
								flag5 = 0;
								printf("\t\t\t\t\t  -> ");

								if (!scanf("\t\t\t\t\t%d", &temp_date_check)) {

									printf("\t\t\t\t\t���ڰ� �ƴմϴ�. \n\n");
									flag5 = 1;
									while (getchar() != '\n');
								}
							} while (flag5);

							if (temp_date_check <= 31 && temp_date_check > 0) break;
						}

					}


					else {
						reservation[reserve_check_number].date = temp_date_check;
						flight_day = reservation[reserve_check_number].date;

						PrintListTime(airport, flight_day);
					}

				}

				else {
					destination_name();  //������ 
					PrintList(airport);
					printf("\t\t\t\t\t-> ");
					scanf(" %c", &reservation[reserve_check_number].destination);
					if (!isalpha(reservation[reserve_check_number].destination)) {
						while (1) {
							printf("\t\t\t\t\t���ڷ� �Է����ּ���!\n ");
							printf("\t\t\t\t\t-> ");
							scanf("  %c", &reservation[reserve_check_number].destination);
							if (isalpha(reservation[reserve_check_number].destination))
								break;
						}
					}
					arrive = reservation[reserve_check_number].destination;
					printf("\n");

				}
			}
			//make_route(reservation[reserve_check_number].source, reservation[reserve_check_number].destination, reservation[reserve_check_number].date);
			//printf("��� : \n");

			seat_print(t, airport, arrive);
			printf(" \n\t\t\t\t\t -> �¼��� �������ּ���! \n\n");
			printf("\t\t\t\t\t -> ");
			scanf(" %s", &reservation[reserve_check_number].seat);
			if (!isalpha(reservation[reserve_check_number].seat[0])) {
				while (1) {
					printf(" \n\t\t\t\t\t -> ���� �¼��Դϴ�! \n\n");
					printf("\t\t\t\t\t -> ");
					scanf(" %s", &reservation[reserve_check_number].seat);
					if (isalpha(reservation[reserve_check_number].seat[0])) {
						if (!(reservation[reserve_check_number].seat[0] >= 'A' && reservation[reserve_check_number].seat[0] <= 'J')) {
							while (1) {
								printf(" \n\t\t\t\t\t -> ���� �¼��Դϴ�! \n\n");
								printf("\t\t\t\t\t -> ");
								scanf(" %s", &reservation[reserve_check_number].seat);
								if (reservation[reserve_check_number].seat[0] >= 'A' && reservation[reserve_check_number].seat[0] <= 'J') {
									break;
								}
							}
						}
					}
				}
			}
			else if (!(reservation[reserve_check_number].seat[0] >= 'A' && reservation[reserve_check_number].seat[0] <= 'J')) {
				while (1) {
					printf(" \n\t\t\t\t\t -> ���� �¼��Դϴ�! \n\n");
					printf("\t\t\t\t\t -> ");
					scanf(" %s", &reservation[reserve_check_number].seat);
					if (reservation[reserve_check_number].seat[0] >= 'A' && reservation[reserve_check_number].seat[0] <= 'J')
						break;
				}

				printf("\t\t\t\t\t -> ");
				char seat[3];
				scanf(" %s", &reservation[reserve_check_number].seat);
				strcpy(seat, reservation[reserve_check_number].seat);

				if (seatCheck(t, airport, arrive, seat[0] - 'A', seat[1] - '0')) {
					do {
						printf("\n\t\t\t\t\t�¼��� �ٽ� �Է��ϼ���!\n");
						printf("\n\t\t\t\t\t-> ");
						scanf(" %s", &reservation[reserve_check_number].seat);
						strcpy(seat, reservation[reserve_check_number].seat);
					} while (seatCheck(t, airport, arrive, seat[0] - 'A', seat[1] - '0'));
				}

				printf("\n");
				printf(" \n\t\t\t\t\t -> ���Ͻô� �¼� ����� �������ּ���! \n");
				printf(" \n\t\t\t\t\t 1 : prestige class  ( ����  :  $3100 ) \n\n");
				printf(" \n\t\t\t\t\t 2 : business class ( ���� :  $1100 )\n\n");
				printf(" \n\t\t\t\t\t 3 : economy class ( ���� :  $700 )\n\n");
				printf("\t\t\t\t\t -> ");
				scanf(" %d", &reservation[reserve_check_number].seat_level);
				if (reservation[reserve_check_number].seat_level < 0 || reservation[reserve_check_number].seat_level >3) {
					while (1) {
						printf("\t\t\t\t\t �߸��Է��Ͽ����ϴ�!\n ");
						printf("\t\t\t\t\t -> ");
						scanf(" %d", &reservation[reserve_check_number].seat_level);
						if (reservation[reserve_check_number].seat_level > 0 && reservation[reserve_check_number].seat_level <= 3)
							break;
					}
				}

				printf(" \n\t\t\t\t\t -> ���� �Ͻðڽ��ϱ�? \n");

				printf("\t\t\t\t\t 1  : �� \n");
				printf("\t\t\t\t\t 2  : �ƴϿ�\n\n");

				int  flag1;
				do {
					flag1 = 0;
					printf("\t\t\t\t\t  -> ");

					if (!scanf("\t\t\t\t\t%d", &reserve_number)) {
						printf("\t\t\t\t\t���ڰ� �ƴմϴ�. \n\n");
						flag1 = 1;
						while (getchar() != '\n');
					}
				} while (flag1);

				if (reserve_number == 1) {

					printf("\t\t\t\t\t�̸� : ");
					scanf("%s", reservation[reserve_check_number].name, 10);
					printf("\t\t\t\t\t��");  //ù��° ��
					for (int i = 0; i < 30; i++) printf("��");
					printf("��\n");
					printf("\t\t\t\t\t�� ");//�ι�° ��
					printf(" ������ �Ϸ��Ͽ����ϴ�.");
					printf("      �� \n");
					printf("\t\t\t\t\t��");
					printf("  ���� ��ȣ��  %d��  �Դϴ�.", reserve_check_number);
					if (reserve_check_number >= 10 && reserve_check_number < 100)
						printf("     �� \n");
					else if (reserve_check_number >= 100)
						printf(" �� \n");
					else
						printf(" �� \n");

					printf("\t\t\t\t\t��");  //���� ° ��
					for (int i = 0; i < 30; i++) printf("��");
					printf("��\n\n");
					reservation[reserve_check_number].reservation_number = reserve_check_number;

					array_RBTree[reserve_check_number] = reserve_check_number;
					RBtree_insert(t, (void*)array_RBTree[reserve_check_number], compare_int);
					reserve_check_number++;
					printf("\t\t\t\t\tRed-Black tree height : %d \n", RBtree_height(t->root));
					printf("\t\t\t\t\tRed-Black tree  count node : %d\n ", count_node(t->root));

				}
			}
		}
			else if (choose_number == 2) {
				int check = 0;
				printf("\t\t\t\t\t���� ��ȣ�� �Է��ϼ��� -> ");

				int  flag2;
				do {
					flag2 = 0;

					if (!scanf("\t\t\t\t\t%d", &check)) {
						printf("\t\t\t\t\t���ڰ� �ƴմϴ�. \n\n");
						flag2 = 1;
						while (getchar() != '\n');
					}
				} while (flag2);

				if (RBtree_search_node(t->root, check) != NULL) {
					printf("\t\t\t\t\t��");  //ù��° ��
					for (int i = 0; i < 28; i++) printf("��");
					printf("��\n");
					printf("\t\t\t\t\t��"); //�ι�° ��
					printf(" ���� ��ȣ : %d", reservation[check].reservation_number);
					if (reservation[check].reservation_number >= 10 && reservation[check].reservation_number < 100)
						printf("             �� \n");
					else if (reservation[check].reservation_number >= 100)
						printf("            �� \n");
					else
						printf("               �� \n");
					printf("\t\t\t\t\t�� ");
					printf("�� �̸� : %s", reservation[check].name);
					for (int i = 0; i < 28 - (13 + strlen(reservation[check].name)); i++) 	printf(" ");
					printf("�� \n");

					printf("\t\t\t\t\t�� ");
					printf("�����    : %c", reservation[check].source);
					printf("	             �� \n");

					printf("\t\t\t\t\t�� ");
					printf("������    : %c", reservation[check].destination);
					printf("	             �� \n");

					printf("\t\t\t\t\t�� ");
					printf("��߳�¥  : %d", reservation[check].date);
					if (reservation[check].date >= 10)
						printf("             �� \n");
					else
						printf("              �� \n");
					printf("\t\t\t\t\t�� ");
					printf("�¼� ��ȣ : %s", reservation[check].seat);
					printf("             �� \n");
					printf("\t\t\t\t\t�� ");
					printf("�¼� ��� : ");
					if (reservation[check].seat_level == 1) {
						printf("prestige class");
						printf(" �� \n");
					}
					else if (reservation[check].seat_level == 2) {
						printf("business class");
						printf(" �� \n");
					}
					else {
						printf("economy class");
						printf("  �� \n");
					}
					printf("\t\t\t\t\t�� ");
					int pathnum = shortest_path(reservation[check].source, reservation[check].destination, reservation[check].date);
					printf("����ð�  : %d ", pathnum);
					if (reservation[check].date >= 10)
						printf("            �� \n");
					else if (reservation[check].date < 10)
						printf("             �� \n");
					printf("\t\t\t\t\t��");  //���� ° ��
					for (int i = 0; i < 28; i++) printf("��");
					printf("��\n\n");
					if (pathnum >= 1000) {
						printf("\n\n\t\t\t\t\t-*-WARNING/ �ùٸ��� ���� �����Դϴ�!!!(��� ����)-*-\n\n");
						continue;
					}
					print_path(reservation[check].source, reservation[check].destination);
					print_time(reservation[check].date);


				}

				else if (RBtree_search_node(t->root, check) == NULL) {
					printf("\t\t\t\t\t��");  //ù��° ��
					for (int i = 0; i < 28; i++) printf("��");
					printf("��\n");
					printf("\t\t\t\t\t�� ");
					printf("��ȸ���� �ʴ� ��ȣ �Դϴ�!");
					printf(" �� \n");
					printf("\t\t\t\t\t��");  //���� ° ��
					for (int i = 0; i < 28; i++) printf("��");
					printf("��\n\n");
				}
				//	break;
			}
			else if (choose_number == 3) {
				int check;
				printf("\t\t\t\t\t���� ��ȣ�� �Է��ϼ��� -> ");

				int  flag3;
				do {
					flag3 = 0;

					if (!scanf("%d", &check)) {
						printf("\t\t\t\t\t���ڰ� �ƴմϴ�. \n\n");
						flag3 = 1;
						while (getchar() != '\n');
					}
				} while (flag3);

				if (RBtree_search_node(t->root, check) != NULL) {
					RBtree_delete(t, (void*)check, compare_int);
					printf("\t\t\t\t\t��");  //ù��° ��
					for (int i = 0; i < 25; i++) printf("��");
					printf("��\n");
					printf("\t\t\t\t\t�� ");
					printf("������ ��ҵǾ����ϴ�!");
					printf("  �� \n");
					printf("\t\t\t\t\t��");  //���� ° ��
					for (int i = 0; i < 25; i++) printf("��");
					printf("��\n\n");
					printf("\t\t\t\t\tRed-Black tree height : %d \n", RBtree_height(t->root));
					printf("\t\t\t\t\tRed-Black tree  count node : %d\n ", count_node(t->root));
				}
				else printf("\t\t\t\t\t��ȸ���� �ʴ� ��ȣ �Դϴ�.\n\n");

			}

			else  if (choose_number != -1 && choose_number > 4) {
				printf("\t\t\t\t\t�ٽ� �Է����ּ��� !\n\n\n ");
			}
			if (choose_number == -1) {
				printf("\t\t\t\t\t��ȸ�� �����մϴ�!\n");
				printf("\t\t\t\t\tRed-Black tree height : %d \n", RBtree_height(t->root));
				printf("\t\t\t\t\tRed-Black tree  count node : %d \n\n", count_node(t->root));
				exit(1);
			}

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

void squre_box_print() {
	printf("\t\t\t\t\t��");  //ù��° ��
	for (int i = 0; i < 12; i++) printf("��");
	printf("��\n");
	printf("\t\t\t\t\t��"); //�ι�° ��
	printf("  ��� ��¥ ");
	printf("�� \n");
	printf("\t\t\t\t\t��");  //���� ° ��
	for (int i = 0; i < 12; i++) printf("��");
	printf("��\n");

	int i = 0;
	int start = 0;
	const char* wname[7] = { "��","��","ȭ","��","��","��","��" };

	printf("\t\t\t\t\t                   << 2019�� 12��>>\n");//�� ���
	printf("\t\t\t\t\t======================================================\n");
	printf("\t\t\t\t\t");
	for (i = 0; i < 7; i++)//���� ���
	{
		printf("%7s", wname[i]);//���� 7�� ����
	}
	printf("\n\t\t\t\t\t");
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
			printf("\n\t\t\t\t\t");//���� ���
		}
	}
	printf("\n\t\t\t\t\t======================================================\n");
}

void source_date() {
	printf("\t\t\t\t\t��");  //ù��° ��
	for (int i = 0; i < 30; i++) printf("��");
	printf("��\n");
	printf("\t\t\t\t\t�� ");
	printf("  ��� ��¥�� �Է����ּ���!");
	printf("  �� \n");
	printf("\t\t\t\t\t��");  //���� ° ��
	for (int i = 0; i < 30; i++) printf("��");
	printf("��\n\n");
}

void source_name() {
	printf("\t\t\t\t\t��");  //ù��° ��
	for (int i = 0; i < 44; i++) printf("��");
	printf("��\n");
	printf("\t\t\t\t\t�� ");
	printf("��� ��  ���ø� �Է����ּ���!");
	printf("              �� \n");
	printf("\t\t\t\t\t�� ");
	printf("'a'���� 'z'���̿��� ������ �ּ���!");
	printf("         �� \n");
	printf("\t\t\t\t\t��");  //���� ° ��
	for (int i = 0; i < 44; i++) printf("��");
	printf("��\n\n");
}

void destination_name() {
	printf("\t\t\t\t\t��");  //ù��° ��
	for (int i = 0; i < 44; i++) printf("��");
	printf("��\n");
	printf("\t\t\t\t\t�� ");
	printf("       ���� ��  ���ø� �Է����ּ���!");
	printf("       �� \n");
	printf("\t\t\t\t\t��");  //���� ° ��
	for (int i = 0; i < 44; i++) printf("��");
	printf("��\n\n");
}

void random_reserve(RBtree t) {
	char* cusname = (char*)malloc(sizeof(char) * 10);
	char* cuspos = (char*)malloc(sizeof(char) * 3);
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
		for (int j = 0; j < 2; j++) {
			if (j == 0)
				cuspos[j] = rand() % 10 + 'A';
			else
				cuspos[j] = rand() % 7 + '0';
		}
		cuspos[2] = '\0';
		strcpy(reservation[reserve_check_number].name, cusname);
		strcpy(reservation[reserve_check_number].seat, cuspos);
		reservation[reserve_check_number].source = (char)(start + 'a');
		reservation[reserve_check_number].destination = (char)(arrive + 'a');
		reservation[reserve_check_number].date = sdate + 1;
		reservation[reserve_check_number].reservation_number = reserve_check_number;
		array_RBTree[reserve_check_number] = reserve_check_number;
		RBtree_insert(t, (void*)array_RBTree[reserve_check_number], compare_int);
		reserve_check_number++;
	}
}

void seat_print(RBtree t, char start, char dest) {
	printf("\t\t\t\t\t\t    �¼� ����\n");
	printf("\t\t\t\t\t   ��");  //ù��° ��
	for (int i = 0; i < 25; i++) printf("��");
	printf("��\n");
	printf("\t\t\t\t\t   ��   0 1   2 3 4   5 6     ��\n");
	for (int i = 0; i < 10; i++) {
		printf("\t\t\t\t\t   ");
		printf("��   ");
		for (int j = 0; j < 7; j++) {
			if (j % 10 == 2 || j % 10 == 5)
				printf("�� ");
			if (!seatCheck(t, start, dest, 9 - i, j)) {
				printf("o ");
			}
			else {
				printf("x ");
			}
		}
		printf(" %c", 'J' - i);
		printf("  ��");
		printf("\n");
	}
	printf("\t\t\t\t\t   ��");  //������ ��
	for (int i = 0; i < 25; i++) printf("��");
	printf("��\n");
}

int seatCheck(RBtree t, char start, char dest, int str, int num) {
	for (int i = 0; i <= reserve_check_number; i++) {
		if ((reservation[i].source == start) && (reservation[i].destination == dest)) {
			if ((reservation[i].seat[0] - 'A' == str) && (reservation[i].seat[1] - '0' == num)) {
				return 1;
			}
		}
	}
	return 0;
}
