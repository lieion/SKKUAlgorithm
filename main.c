#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "RBtree.h"
#include "ADJlist.h"

int reserve_check_number; //RBtree 배열에 저장할 값

void group_20_aircraft_print();

void squre_box_print();
void random_reserve(RBtree t);
void source_name(); //출발지 출력
void destination_name();// 도착지 출력 
void source_date(); //출발 날짜 출력
void seat_print(RBtree t, char start, char dest); //좌석 정보 출력
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
		printf("\t\t\t\t\t    해당하는 숫자를 입력하세요!\n");
		printf("\n\t\t\t\t\t    ***  여행지를 선택 : 1 ***\n");
		printf("\n\t\t\t\t\t     ***  예약 조회 : 2  *** \n");
		printf("\n\t\t\t\t\t     ***  예약 취소 : 3  *** \n");
		printf("\n\t\t\t\t\t     ***  종료   : -1  *** \n\n");
		printf("\n\t\t\t\t\t***********************************\n");

		int  flag;
		do {
			flag = 0;
			printf("\t\t\t\t\t  -> ");

			if (!scanf("\t\t\t\t\t %d", &choose_number)) {
				printf("\t\t\t\t\t숫자가 아닙니다. \n\n");
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
					//비행 정보 출력 
					source_name();  //출발지 
					printf("\t\t\t\t\t-> ");
					scanf("  %c", &reservation[reserve_check_number].source);
					if (!isalpha(reservation[reserve_check_number].source)) {
						while (1) {
							printf("\t\t\t\t\t문자로 입력해주세요! \n");
							printf("\t\t\t\t\t-> ");
							scanf("  %c", &reservation[reserve_check_number].source);
							if (isalpha(reservation[reserve_check_number].source))
								break;
						}
					}
					airport = reservation[reserve_check_number].source;
					printf("\n");

					squre_box_print(); //출발 날짜 box
					source_date();


					int  flag0;
					do {
						flag0 = 0;
						printf("\t\t\t\t\t  -> ");

						if (!scanf("\t\t\t\t\t%d", &temp_date_check)) {
							printf("\t\t\t\t\t숫자가 아닙니다. \n\n");
							flag0 = 1;
							while (getchar() != '\n');
						}
					} while (flag0);

					if (temp_date_check > 31 || temp_date_check < 0) {
						while (1) {
							printf("\t\t\t\t\t날짜를 다시 입력하세요!\n");

							int  flag5;
							do {
								flag5 = 0;
								printf("\t\t\t\t\t  -> ");

								if (!scanf("\t\t\t\t\t%d", &temp_date_check)) {

									printf("\t\t\t\t\t숫자가 아닙니다. \n\n");
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
					destination_name();  //도착지 
					PrintList(airport);
					printf("\t\t\t\t\t-> ");
					scanf(" %c", &reservation[reserve_check_number].destination);
					if (!isalpha(reservation[reserve_check_number].destination)) {
						while (1) {
							printf("\t\t\t\t\t문자로 입력해주세요!\n ");
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
			//printf("경로 : \n");

			seat_print(t, airport, arrive);
			printf(" \n\t\t\t\t\t -> 좌석을 선택해주세요! \n\n");
			printf("\t\t\t\t\t -> ");
			char seat[3];
			scanf(" %s", &reservation[reserve_check_number].seat);
			strcpy(seat, reservation[reserve_check_number].seat);

			if(!(!seatCheck(t, airport, arrive, seat[0] - 'A', seat[1] - '0') && ((seat[0] >= 'A' && seat[0] <= 'J') && (seat[1] >= '0' && seat[1] <= '6')))){
				do {
					printf("\n\t\t\t\t\t 좌석을 다시 입력하세요!\n");
					printf("\n\t\t\t\t\t-> ");
					scanf(" %s", &reservation[reserve_check_number].seat);
					strcpy(seat, reservation[reserve_check_number].seat);
				} while (!(!seatCheck(t, airport, arrive, seat[0] - 'A', seat[1] - '0') && ((seat[0] >= 'A' && seat[0] <= 'J') && (seat[1] >= '0' && seat[1] <= '6'))));
			}

			printf("\n");
			printf(" \n\t\t\t\t\t -> 원하시는 좌석 등급을 선택해주세요! \n");
			printf(" \n\t\t\t\t\t 1 : prestige class  ( 가격  :  $3100 ) \n\n");
			printf(" \n\t\t\t\t\t 2 : business class ( 가격 :  $1100 )\n\n");
			printf(" \n\t\t\t\t\t 3 : economy class ( 가격 :  $700 )\n\n");
			printf("\t\t\t\t\t -> ");
			scanf(" %d", &reservation[reserve_check_number].seat_level);
			if (reservation[reserve_check_number].seat_level < 0 || reservation[reserve_check_number].seat_level >3) {
				while (1) {
					printf("\t\t\t\t\t 잘못입력하였습니다!\n ");
					printf("\t\t\t\t\t -> ");
					scanf(" %d", &reservation[reserve_check_number].seat_level);
					if (reservation[reserve_check_number].seat_level > 0 && reservation[reserve_check_number].seat_level <= 3)
						break;
				}
			}

			printf(" \n\t\t\t\t\t -> 예약 하시겠습니까? \n");

			printf("\t\t\t\t\t 1  : 예 \n");
			printf("\t\t\t\t\t 2  : 아니오\n\n");

			int  flag1;
			do {
				flag1 = 0;
				printf("\t\t\t\t\t  -> ");

				if (!scanf("\t\t\t\t\t%d", &reserve_number)) {
					printf("\t\t\t\t\t숫자가 아닙니다. \n\n");
					flag1 = 1;
					while (getchar() != '\n');
				}
			} while (flag1);

			if (reserve_number == 1) {

				printf("\t\t\t\t\t이름 : ");
				scanf("%s", reservation[reserve_check_number].name, 10);
				printf("\t\t\t\t\t┏");  //첫번째 줄
				for (int i = 0; i < 30; i++) printf("━");
				printf("┓\n");
				printf("\t\t\t\t\t┃ ");//두번째 줄
				printf(" 예약을 완료하였습니다.");
				printf("      ┃ \n");
				printf("\t\t\t\t\t┃");
				printf("  예약 번호는  %d번  입니다.", reserve_check_number);
				if (reserve_check_number >= 10 && reserve_check_number < 100)
					printf("     ┃ \n");
				else if (reserve_check_number >= 100)
					printf(" ┃ \n");
				else
					printf(" ┃ \n");

				printf("\t\t\t\t\t┗");  //세번 째 줄
				for (int i = 0; i < 30; i++) printf("━");
				printf("┛\n\n");
				reservation[reserve_check_number].reservation_number = reserve_check_number;

				array_RBTree[reserve_check_number] = reserve_check_number;
				RBtree_insert(t, (void*)array_RBTree[reserve_check_number], compare_int);
				reserve_check_number++;
				printf("\t\t\t\t\tRed-Black tree height : %d \n", RBtree_height(t->root));
				printf("\t\t\t\t\tRed-Black tree  count node : %d\n ", count_node(t->root));

			}
		}
		else if (choose_number == 2) {
			int check = 0;
			printf("\t\t\t\t\t예약 번호를 입력하세요 -> ");

			int  flag2;
			do {
				flag2 = 0;

				if (!scanf("\t\t\t\t\t%d", &check)) {
					printf("\t\t\t\t\t숫자가 아닙니다. \n\n");
					flag2 = 1;
					while (getchar() != '\n');
				}
			} while (flag2);

			if (RBtree_search_node(t->root, check) != NULL) {
				printf("\t\t\t\t\t┏");  //첫번째 줄
				for (int i = 0; i < 28; i++) printf("━");
				printf("┓\n");
				printf("\t\t\t\t\t┃"); //두번째 줄
				printf(" 예약 번호 : %d", reservation[check].reservation_number);
				if (reservation[check].reservation_number >= 10 && reservation[check].reservation_number < 100)
					printf("             ┃ \n");
				else if (reservation[check].reservation_number >= 100)
					printf("            ┃ \n");
				else
					printf("               ┃ \n");
				printf("\t\t\t\t\t┃ ");
				printf("고객 이름 : %s", reservation[check].name);
				for (int i = 0; i < 28 - (13 + strlen(reservation[check].name)); i++) 	printf(" ");
				printf("┃ \n");

				printf("\t\t\t\t\t┃ ");
				printf("출발지    : %c", reservation[check].source);
				printf("	             ┃ \n");

				printf("\t\t\t\t\t┃ ");
				printf("도착지    : %c", reservation[check].destination);
				printf("	             ┃ \n");

				printf("\t\t\t\t\t┃ ");
				printf("출발날짜  : %d", reservation[check].date);
				if (reservation[check].date >= 10)
					printf("             ┃ \n");
				else
					printf("              ┃ \n");
				printf("\t\t\t\t\t┃ ");
				printf("좌석 번호 : %s", reservation[check].seat);
				printf("             ┃ \n");
				printf("\t\t\t\t\t┃ ");
				printf("좌석 등급 : ");
				if (reservation[check].seat_level == 1) {
					printf("prestige class");
					printf(" ┃ \n");
				}
				else if (reservation[check].seat_level == 2) {
					printf("business class");
					printf(" ┃ \n");
				}
				else {
					printf("economy class");
					printf("  ┃ \n");
				}
				printf("\t\t\t\t\t┃ ");
				int pathnum = shortest_path(reservation[check].source, reservation[check].destination, reservation[check].date);
				printf("비행시간  : %d ", pathnum);
				if (reservation[check].date >= 10)
					printf("            ┃ \n");
				else if (reservation[check].date < 10)
					printf("             ┃ \n");
				printf("\t\t\t\t\t┗");  //세번 째 줄
				for (int i = 0; i < 28; i++) printf("━");
				printf("┛\n\n");
				if (pathnum >= 1000) {
					printf("\n\n\t\t\t\t\t-*-WARNING/ 올바르지 않은 예약입니다!!!(경로 없음)-*-\n\n");
					continue;
				}
				print_path(reservation[check].source, reservation[check].destination);
				print_time(reservation[check].date);


			}

			else if (RBtree_search_node(t->root, check) == NULL) {
				printf("\t\t\t\t\t┏");  //첫번째 줄
				for (int i = 0; i < 28; i++) printf("━");
				printf("┓\n");
				printf("\t\t\t\t\t┃ ");
				printf("조회되지 않는 번호 입니다!");
				printf(" ┃ \n");
				printf("\t\t\t\t\t┗");  //세번 째 줄
				for (int i = 0; i < 28; i++) printf("━");
				printf("┛\n\n");
			}
			//	break;
		}
		else if (choose_number == 3) {
			int check;
			printf("\t\t\t\t\t예약 번호를 입력하세요 -> ");

			int  flag3;
			do {
				flag3 = 0;

				if (!scanf("%d", &check)) {
					printf("\t\t\t\t\t숫자가 아닙니다. \n\n");
					flag3 = 1;
					while (getchar() != '\n');
				}
			} while (flag3);

			if (RBtree_search_node(t->root, check) != NULL) {
				RBtree_delete(t, (void*)check, compare_int);
				printf("\t\t\t\t\t┏");  //첫번째 줄
				for (int i = 0; i < 25; i++) printf("━");
				printf("┓\n");
				printf("\t\t\t\t\t┃ ");
				printf("예약이 취소되었습니다!");
				printf("  ┃ \n");
				printf("\t\t\t\t\t┗");  //세번 째 줄
				for (int i = 0; i < 25; i++) printf("━");
				printf("┛\n\n");
				printf("\t\t\t\t\tRed-Black tree height : %d \n", RBtree_height(t->root));
				printf("\t\t\t\t\tRed-Black tree  count node : %d\n ", count_node(t->root));
			}
			else printf("\t\t\t\t\t조회되지 않는 번호 입니다.\n\n");

		}

		else  if (choose_number != -1 && choose_number > 4) {
			printf("\t\t\t\t\t다시 입력해주세요 !\n\n\n ");
		}
		if (choose_number == -1) {
			printf("\t\t\t\t\t조회를 종료합니다!\n");
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
	printf("\t\t\t\t\t┏");  //첫번째 줄
	for (int i = 0; i < 12; i++) printf("━");
	printf("┓\n");
	printf("\t\t\t\t\t┃"); //두번째 줄
	printf("  출발 날짜 ");
	printf("┃ \n");
	printf("\t\t\t\t\t┗");  //세번 째 줄
	for (int i = 0; i < 12; i++) printf("━");
	printf("┛\n");

	int i = 0;
	int start = 0;
	const char* wname[7] = { "일","월","화","수","목","금","토" };

	printf("\t\t\t\t\t                   << 2019년 12월>>\n");//달 출력
	printf("\t\t\t\t\t======================================================\n");
	printf("\t\t\t\t\t");
	for (i = 0; i < 7; i++)//요일 출력
	{
		printf("%7s", wname[i]);//폭을 7로 설정
	}
	printf("\n\t\t\t\t\t");
	for (i = 0; i < start; i++)//첫 주 시작일까지 공백 출력
	{
		printf("%7s", " ");//폭을 7로 설정
	}
	for (i = 0; i < 31; i++)//일 출력
	{
		printf("%7d", i + 1);//폭을 7로 설정
		start++;
		if (start == 7)//요일이 7이면
		{
			start = 0;//0으로 변경
			printf("\n\t\t\t\t\t");//개행 출력
		}
	}
	printf("\n\t\t\t\t\t======================================================\n");
}

void source_date() {
	printf("\t\t\t\t\t┏");  //첫번째 줄
	for (int i = 0; i < 30; i++) printf("━");
	printf("┓\n");
	printf("\t\t\t\t\t┃ ");
	printf("  출발 날짜를 입력해주세요!");
	printf("  ┃ \n");
	printf("\t\t\t\t\t┗");  //세번 째 줄
	for (int i = 0; i < 30; i++) printf("━");
	printf("┛\n\n");
}

void source_name() {
	printf("\t\t\t\t\t┏");  //첫번째 줄
	for (int i = 0; i < 44; i++) printf("━");
	printf("┓\n");
	printf("\t\t\t\t\t┃ ");
	printf("출발 할  도시를 입력해주세요!");
	printf("              ┃ \n");
	printf("\t\t\t\t\t┃ ");
	printf("'a'부터 'z'사이에서 선택해 주세요!");
	printf("         ┃ \n");
	printf("\t\t\t\t\t┗");  //세번 째 줄
	for (int i = 0; i < 44; i++) printf("━");
	printf("┛\n\n");
}

void destination_name() {
	printf("\t\t\t\t\t┏");  //첫번째 줄
	for (int i = 0; i < 44; i++) printf("━");
	printf("┓\n");
	printf("\t\t\t\t\t┃ ");
	printf("       도착 할  도시를 입력해주세요!");
	printf("       ┃ \n");
	printf("\t\t\t\t\t┗");  //세번 째 줄
	for (int i = 0; i < 44; i++) printf("━");
	printf("┛\n\n");
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
	printf("\t\t\t\t\t\t    좌석 정보\n");
	printf("\t\t\t\t\t   ┏");  //첫번째 줄
	for (int i = 0; i < 25; i++) printf("━");
	printf("┓\n");
	printf("\t\t\t\t\t   ┃   0 1   2 3 4   5 6     ┃\n");
	for (int i = 0; i < 10; i++) {
		printf("\t\t\t\t\t   ");
		printf("┃   ");
		for (int j = 0; j < 7; j++) {
			if (j % 10 == 2 || j % 10 == 5)
				printf("┃ ");
			if (!seatCheck(t, start, dest, 9 - i, j)) {
				printf("o ");
			}
			else {
				printf("x ");
			}
		}
		printf(" %c", 'J' - i);
		printf("  ┃");
		printf("\n");
	}
	printf("\t\t\t\t\t   ┗");  //마지막 줄
	for (int i = 0; i < 25; i++) printf("━");
	printf("┛\n");
}

int seatCheck(RBtree t, char start, char dest, int str, int num) {
	for (int i = 0; i < reserve_check_number; i++) {
		if ((reservation[i].source == start) && (reservation[i].destination == dest)) {
			if ((reservation[i].seat[0] - 'A' == str) && (reservation[i].seat[1] - '0' == num)) {
				return 1;
			}
		}
	}
	return 0;
}
