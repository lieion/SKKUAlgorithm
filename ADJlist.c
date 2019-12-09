#include "RBtree.h"
#include "ADJlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>


int pathCheck(char random_path[100][3], int num) {
	for (int i = 0; i < num; i++) {
		if ((random_path[i][0] == random_path[num][0] && random_path[i][1] == random_path[num][1]) || (random_path[i][0] == random_path[num][1] && random_path[i][1] == random_path[num][0])) {
			return 1;
		}
	}
	return 0;
}

void random_City_Position(City* city) {
	
	
	for (int i = 0; i < 26; i++) {
		city[i].name = i + 'a';
		city[i].pos_x = rand() % 6000 - 3000;
		city[i].pos_y = rand() % 6000 - 3000;
	}
}
void insertNode(char start, char dest, int times) {
	int tstart = start - 'a';
	int tdest = dest - 'a';
	int ttm=0;
	NODE* cur, * Newnode;
	Newnode = (NODE*)malloc(sizeof(NODE));
	Newnode->length=(int)sqrt(pow(city[tstart].pos_x - city[dest].pos_x, 2) + pow(city[tstart].pos_y - city[dest].pos_y, 2));
	//Newnode->length = ;
	Newnode->next = NULL;
	Newnode->data = dest;
	for (int i = 0; i < 31; i++) {
		ttm=rand() % 24; // 무작위 시간 
		Newnode->tm[i]= ttm;
	}
	
	cur = Adjlist[tstart].head->next;
	if ((Adjlist[tstart].len == 0)) {
		Newnode->next = cur;
		Adjlist[tstart].head->next = Newnode;
		Adjlist[tstart].len++;
	}
	else if (cur->data > Newnode->data) {
		Newnode->next = cur;
		Adjlist[tstart].head->next = Newnode;
		Adjlist[tstart].len++;
	}
	else {
		while (1) {

			if (cur->next == NULL) {
				cur->next = Newnode;
				Adjlist[tstart].len++;
				break;
			}
			else if (Newnode->data < cur->next->data) {
				Newnode->next = cur->next;
				cur->next = Newnode;
				Adjlist[tstart].len++;
				break;
			}
			else {
				cur = cur->next;
			}
		}
	}
}

void init_Node() {
	
	for (int i = 0; i < 26; i++) {
		Adjlist[i].head = (NODE*)malloc(sizeof(NODE));
		Adjlist[i].head->next = NULL;
		Adjlist[i].len = 0;
	}
}
void PrintList(int i) {
	printf("%c\n", i);
	i = i - 'a';
	NODE* cur;
	int dec;
	printf("갈 수 있는 여행지: ");
	cur = Adjlist[i].head->next;
	while (!cur == NULL) {
		printf("%c ", cur->data);
		cur = cur->next;

	}
	printf("\n");
}

void PrintListTime(char city_name, int date_num) {
	int i = (int)(city_name - 'a');
	int k = 0;
	if (date_num > 10) k = 24;
	else k = 23;
	NODE* cur;
	int dec;
	printf("\t\t\t\t\t┏");  //첫번째 줄
	for (int i = 0; i < k; i++) printf("━");
	printf("┓\n");
	printf("\t\t\t\t\t┃ ");
	printf("<%c공항 %d일의 시간표>", city_name, date_num);
	printf("  ┃ \n");
	printf("\t\t\t\t\t┗");  //세번 째 줄
	for (int i = 0; i < k; i++) printf("━");
	printf("┛\n\n");
	
	cur = Adjlist[i].head->next;
	while (!cur == NULL) {
		printf("\t\t\t\t\t> %c -> %c %d시\n", city_name, cur->data, cur->tm[date_num]);
		cur = cur->next;
	}
	printf("\n");
}


int shortest_path(int start, int arrive, int date) {
	int used_city[26]; // 쓴 도시 저장
	int saver[26]; // 최대 최소 저장
	int savertime[26]; // 24시 기준 시간 저장
	int min=0;
	int min_time=0;
	for (int i=0; i < 26; i++) {
		used_city[i] = 0;
		saver[i] = 0;
		savertime[i] = 0;
	}
	int used_number = 1;
	NODE* cur;
	int i = start;
	while (1) {
		cur = Adjlist[i].head->next;
		while (!cur == NULL) {
			if (i!=start) {

			}
			int stime = cur->tm[date];
			int runing = ceil((cur->length)/500);// 비행기로 이동시간 
			saver[cur->data] = runing;
			if (start == i) savertime[cur->data] = stime + runing; // 처음이면 그냥 시간에 넣는다 
			else savertime[cur->data] += runing; // 아니면 말고;
			cur = cur->next;
		}
		used_city[i] = 1;
		min = 0;
		min_time = 0;
		for (int i = 0; i < 26; i++) {
			if (saver[min] > saver[i]) min = i;
		}
		i = min;
		
	}
	return -1;
	
}

void make_ADJlist() {
	srand(time(NULL));
	init_Node();
	char random_path[100][3];

	for (int i = 0; i < 100; i++) {
		random_path[i][0] = (rand() % 26) + 'a'; // 0은 출발
		random_path[i][1] = (rand() % 26) + 'a'; // 1은 도착
		random_path[i][2] = (rand() % 24); //출발 시간
		if ((random_path[i][0] == random_path[i][1]) || pathCheck(random_path, i)) {
			i--;
			continue;
		}
	}

	for (int i = 0; i < 100; i++) {
		char start = random_path[i][0];
		char dest = random_path[i][1];
		int times = random_path[i][2];
		insertNode(start,dest, times);
		
	}
}

