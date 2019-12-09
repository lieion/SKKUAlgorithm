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

	while (1) {

		printf("***********************************\n");
		printf("    해당하는 숫자를 입력하세요!\n");
		printf(" \n    ***  여행지를 선택 : 1 ***\n");
		printf(" \n    ***  예약 조회 : 2  *** \n");
		printf(" \n    ***  예약 취소 : 3  *** \n");
		printf(" \n    ***  비행기 정보 : 4  *** \n");
		printf(" \n    ***  종료   : -1  *** \n\n");
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
					printf("날짜를 다시 입력하세요!\n");
					scanf("%d", &temp_date_check);
					if (temp_date_check <= 31) break;
				}
			}
			else
				reservation[reserve_check_number].date = temp_date_check;

			//make_route(reservation[reserve_check_number].source, reservation[reserve_check_number].destination, reservation[reserve_check_number].date);
			//printf("경로 : \n");
			printf(" \n -> 예약 하시겠습니까? \n");
			printf(" 1  : 예 \n");
			printf(" 2  : 아니오\n");

			printf("\n -> ");
			scanf("%d", &reserve_number);
			printf("\n");

			if (reserve_number == 1) {

				printf("이름 : ");
				scanf("%s", reservation[reserve_check_number].name, 10);
				printf("┏");  //첫번째 줄
				for (int i = 0; i < 28; i++) printf("━");
				printf("┓\n");
				printf("┃ ");//두번째 줄
				printf(" 예약을 완료하였습니다.");
				printf("    ┃ \n");
				printf("┃");
				printf("  예약 번호는  %d번  입니다.", reserve_check_number);
				printf(" ┃ \n");
				printf("┗");  //세번 째 줄
				for (int i = 0; i < 28; i++) printf("━");
				printf("┛\n\n");
				reservation[reserve_check_number].reservation_number = reserve_check_number;

				array_RBTree[reserve_check_number] = reserve_check_number;
				RBtree_insert(t, (void*)array_RBTree[reserve_check_number], compare_int);
				reserve_check_number++;

			}
		}
		else if (choose_number == 2) {
			int check = 0;
			printf("예약 번호를 입력하세요 -> ");
			scanf("%d", &check);
			printf("\n\n");
			if (RBtree_search_node(t->root, check) != NULL) {
				printf("┏");  //첫번째 줄
				for (int i = 0; i < 20; i++) printf("━");
				printf("┓\n");
				printf("┃"); //두번째 줄
				printf(" 예약 번호 : %d", reservation[check].reservation_number);
				if (reservation[check].reservation_number >= 10)
					printf("     ┃ \n");
				else
					printf("      ┃ \n");
				printf("┃ ");
				printf("고객 이름 : %s", reservation[check].name);
				for (int i = 0; i < 20 - (13 + strlen(reservation[check].name)); i++) 	printf(" ");
				printf("┃ \n");
				printf("┃ ");
				printf("출발지    : %s", reservation[check].source);

				for (int i = 0; i < 20 - (13 + strlen(reservation[check].source)); i++) 	printf(" ");
				printf("┃ \n");
				printf("┃ ");
				printf("도착지    : %s", reservation[check].destination);
				for (int i = 0; i < 20 - (13 + strlen(reservation[check].destination)); i++) 	printf(" ");
				printf("┃ \n");
				printf("┃ ");
				printf("출발날짜  : %d", reservation[check].date);
				if (reservation[check].date >= 10)
					printf("     ┃ \n");
				else
					printf("      ┃ \n");
				printf("┗");  //세번 째 줄
				for (int i = 0; i < 20; i++) printf("━");
				printf("┛\n\n");

			}

			else if (RBtree_search_node(t->root, check) == NULL) {
				printf("┏");  //첫번째 줄
				for (int i = 0; i < 28; i++) printf("━");
				printf("┓\n");
				printf("┃ ");
				printf("조회되지 않는 번호 입니다!");
				printf(" ┃ \n");
				printf("┗");  //세번 째 줄
				for (int i = 0; i < 28; i++) printf("━");
				printf("┛\n\n");
			}
			//	break;
		}
		else if (choose_number == 3) {
			int check;
			printf("예약 번호를 입력하세요 -> ");
			scanf("%d", &check);
			printf("\n\n");
			if (RBtree_search_node(t->root, check) != NULL) {
				RBtree_delete(t, (void*)check, compare_int);
				printf("┏");  //첫번째 줄
				for (int i = 0; i < 25; i++) printf("━");
				printf("┓\n");
				printf("┃ ");
				printf("예약이 취소되었습니다!");
				printf("  ┃ \n");
				printf("┗");  //세번 째 줄
				for (int i = 0; i < 25; i++) printf("━");
				printf("┛\n\n");
			}
			else printf("조회되지 않는 번호 입니다.\n\n");
			//break;
		}
		else if (choose_number == 4) {
			char airport;
			int flight_day = 0;
			printf("┏");  //첫번째 줄
			for (int i = 0; i < 44; i++) printf("━");
			printf("┓\n");
			printf("┃ ");
			printf("비행 정보를 보고 싶은 도시를 입력해주세요");
			printf("  ┃ \n");
			printf("┗");  //세번 째 줄
			for (int i = 0; i < 44; i++) printf("━");
			printf("┛\n\n");
			printf("-> ");
			scanf("%s", &airport);
			printf("\n");
			squre_box_print3();
			printf("┏");  //첫번째 줄
			for (int i = 0; i < 44; i++) printf("━");
			printf("┓\n");
			printf("┃ ");
			printf("비행 정보를 보고 싶은 날짜를 입력해주세요");
			printf("  ┃ \n");
			printf("┗");  //세번 째 줄
			for (int i = 0; i < 44; i++) printf("━");
			printf("┛\n\n");
			printf("-> ");
			scanf("%d", &flight_day);
			printf("\n");
			PrintListTime(airport, flight_day);

		}

		else  if (choose_number != -1 && choose_number > 3) {
			printf("다시 입력해주세요 !\n\n\n ");
		}
		if (choose_number == -1) {
			printf("조회를 종료합니다!\n");
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
	printf("┏");  //첫번째 줄
	for (int i = 0; i < 10; i++) printf("━");
	printf("┓\n");
	printf("┃"); //두번째 줄
	printf("  출발지  ");
	printf("┃ \n");
	printf("┗");  //세번 째 줄
	for (int i = 0; i < 10; i++) printf("━");
	printf("┛\n");
}
void squre_box_print2() {
	printf("┏");  //첫번째 줄
	for (int i = 0; i < 10; i++) printf("━");
	printf("┓\n");
	printf("┃"); //두번째 줄
	printf("  도착지  ");
	printf("┃ \n");
	printf("┗");  //세번 째 줄
	for (int i = 0; i < 10; i++) printf("━");
	printf("┛\n");
}
void squre_box_print3() {
	printf("┏");  //첫번째 줄
	for (int i = 0; i < 12; i++) printf("━");
	printf("┓\n");
	printf("┃"); //두번째 줄
	printf("  출발 날짜 ");
	printf("┃ \n");
	printf("┗");  //세번 째 줄
	for (int i = 0; i < 12; i++) printf("━");
	printf("┛\n");


	int i = 0;
	int start = 0;
	const char* wname[7] = { "일","월","화","수","목","금","토" };

	printf("                   << 2019년 12월>>\n");//달 출력
	printf("======================================================\n");
	for (i = 0; i < 7; i++)//요일 출력
	{
		printf("%7s", wname[i]);//폭을 7로 설정
	}
	printf("\n");

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
			printf("\n");//개행 출력
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