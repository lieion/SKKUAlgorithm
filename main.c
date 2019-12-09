#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RBtree.h"
#include "ADJlist.h";

int reserve_check_number; //RBtree 배열에 저장할 값

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

	printf("\t\t\t\t\tRed-Black tree height : %d \n", RBtree_height(t->root));
	printf("\t\t\t\t\tRed-Black tree  count node : %d\n ", count_node(t->root));
	
	while (1) {

		printf("\t\t\t\t\t***********************************\n");
		printf("\t\t\t\t\t    해당하는 숫자를 입력하세요!\n");
		printf("\n\t\t\t\t\t    ***  여행지를 선택 : 1 ***\n");
		printf("\n\t\t\t\t\t     ***  예약 조회 : 2  *** \n");
		printf("\n\t\t\t\t\t     ***  예약 취소 : 3  *** \n");
		printf("\n\t\t\t\t\t     ***  비행기 정보 : 4  *** \n");
		printf("\n\t\t\t\t\t     ***  종료   : -1  *** \n\n");
		printf("\n\t\t\t\t\t***********************************\n");

		int  flag;
		do {
			flag = 0;
			printf("\t\t\t\t\t  -> ");

			if (!scanf("%d", &choose_number)) {
				printf("\t\t\t\t\t숫자가 아닙니다. \n\n");
				flag = 1;
				while (getchar() != '\n');
			}
		} while (flag);

		if (choose_number == 1) {

			int reserve_number;
			int temp_date_check = 0;
			squre_box_print1();
			printf("\n\t\t\t\t\t -> ");
			scanf("  %s", reservation[reserve_check_number].source, 20);

			squre_box_print2();
			printf("\n\t\t\t\t\t -> ");
			scanf("%s", reservation[reserve_check_number].destination, 20);

			squre_box_print3();

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
			if (temp_date_check > 31) {
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
					if (temp_date_check <= 31) break;
				}
			}
			else
				reservation[reserve_check_number].date = temp_date_check;

			//make_route(reservation[reserve_check_number].source, reservation[reserve_check_number].destination, reservation[reserve_check_number].date);
			//printf("경로 : \n");
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
				for (int i = 0; i < 20; i++) printf("━");
				printf("┓\n");
				printf("\t\t\t\t\t┃"); //두번째 줄
				printf(" 예약 번호 : %d", reservation[check].reservation_number);
				if (reservation[check].reservation_number >= 10 && reservation[check].reservation_number < 100)
					printf("     ┃ \n");
				else if (reservation[check].reservation_number >= 100)
					printf("    ┃ \n");
				else
					printf("      ┃ \n");
				printf("\t\t\t\t\t┃ ");
				printf("고객 이름 : %s", reservation[check].name);
				for (int i = 0; i < 20 - (13 + strlen(reservation[check].name)); i++) 	printf(" ");
				printf("┃ \n");
				printf("\t\t\t\t\t┃ ");
				printf("출발지    : %s", reservation[check].source);

				for (int i = 0; i < 20 - (13 + strlen(reservation[check].source)); i++) 	printf(" ");
				printf("┃ \n");
				printf("\t\t\t\t\t┃ ");
				printf("도착지    : %s", reservation[check].destination);
				for (int i = 0; i < 20 - (13 + strlen(reservation[check].destination)); i++) 	printf(" ");
				printf("┃ \n");
				printf("\t\t\t\t\t┃ ");
				printf("출발날짜  : %d", reservation[check].date);
				if (reservation[check].date >= 10)
					printf("     ┃ \n");
				else
					printf("      ┃ \n");
				printf("\t\t\t\t\t┗");  //세번 째 줄
				for (int i = 0; i < 20; i++) printf("━");
				printf("┛\n\n");

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
		}
		else printf("\t\t\t\t\t조회되지 않는 번호 입니다.\n\n");
		
		}
		else if (choose_number == 4) {
			char airport;
			int flight_day = 0;
			printf("\t\t\t\t\t┏");  //첫번째 줄
			for (int i = 0; i < 44; i++) printf("━");
			printf("┓\n");
			printf("\t\t\t\t\t┃ ");
			printf("비행 정보를 보고 싶은 도시를 입력해주세요");
			printf("  ┃ \n");
			printf("\t\t\t\t\t┗");  //세번 째 줄
			for (int i = 0; i < 44; i++) printf("━");
			printf("┛\n\n");
			printf("\t\t\t\t\t-> ");
			scanf("%s", &airport);
			printf("\n");
			squre_box_print3();
			printf("\t\t\t\t\t┏");  //첫번째 줄
			for (int i = 0; i < 44; i++) printf("━");
			printf("┓\n");
			printf("\t\t\t\t\t┃ ");
			printf("비행 정보를 보고 싶은 날짜를 입력해주세요");
			printf("  ┃ \n");
			printf("\t\t\t\t\t┗");  //세번 째 줄
			for (int i = 0; i < 44; i++) printf("━");
			printf("┛\n\n");
			printf("\t\t\t\t\t-> ");
			scanf("%d", &flight_day);
			printf("\n");
			PrintListTime(airport, flight_day);

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
void squre_box_print1() {
	printf("\t\t\t\t\t┏");  //첫번째 줄
	for (int i = 0; i < 10; i++) printf("━");
	printf("┓\n");
	printf("\t\t\t\t\t┃"); //두번째 줄
	printf("  출발지  ");
	printf("┃ \n");
	printf("\t\t\t\t\t┗");  //세번 째 줄
	for (int i = 0; i < 10; i++) printf("━");
	printf("┛\n");
}
void squre_box_print2() {
	printf("\t\t\t\t\t┏");  //첫번째 줄
	for (int i = 0; i < 10; i++) printf("━");
	printf("┓\n");
	printf("\t\t\t\t\t┃"); //두번째 줄
	printf("  도착지  ");
	printf("┃ \n");
	printf("\t\t\t\t\t┗");  //세번 째 줄
	for (int i = 0; i < 10; i++) printf("━");
	printf("┛\n");
}
void squre_box_print3() {
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
