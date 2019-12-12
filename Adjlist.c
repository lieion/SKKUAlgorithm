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
	int ttm = 0;
	NODE* cur, * Newnode;
	Newnode = (NODE*)malloc(sizeof(NODE));
	Newnode->length = (int)sqrt((pow(city[tstart].pos_x - city[tdest].pos_x, 2) + pow(city[tstart].pos_y - city[tdest].pos_y, 2)), 2);
	//Newnode->length = ;
	Newnode->next = NULL;
	Newnode->data = dest;
	for (int i = 0; i < 31; i++) {
		ttm = rand() % 24; // 무작위 시간 
		Newnode->tm[i] = ttm;
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

void PrintList(char start) {
	printf("\t\t\t\t\t갈 수 있는 여행지: ");
	memset(visited, 0, sizeof(visited));
	checkDestination(start - 'a');
	for (int i = 0; i < 26; i++) {
		if (i == start - 'a')
			continue;
		if (visited[i] == 1)
			printf("%c ", i + 'a');
	}
	printf("\n\n");
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
	printf("┓\n"); -
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

void checkDestination(int start) {
	visited[start] = 1;
	NODE* temp = Adjlist[start].head->next;

	while (temp != NULL) {
		if (visited[temp->data - 'a'] == 0) {
			checkDestination(temp->data - 'a');
		}
		temp = temp->next;
	}
}

int shortest_path_time(char start, char arrive, int date) {
	int graduated[30];
	int dist[30];
	int prev = 0;
	//printf("%c\n", start);
	for (int i = 0; i < 30; i++) {
		graduated[i] = 0;
		dist[i] = 1000000;
	}
	int current = start - 'a';
	dist[current] = 0;
	NODE* cur;
	while (1) {
		int min = 0;
		int swit = 0;
		int count = 0;
		prev = dist[current];
		//printf("??:%d   %d\n", dist[current], dist[0]);
		for (int i = 0; i < 26; i++) {
			if (graduated[i] == 0 && swit == 0) {
				min = i;
				swit = 1;
			}
			else {
				if (swit == 1 && graduated[i] == 0 && dist[min] > dist[i]) min = i;
			}
			if (graduated[i] == 1) count++;
		}
		//printf("%d\n", min);
		if (count == 26)break;
		//sprintf("min: %d\n", min);
		current = min;
		prev = dist[current];
		//printf("min: %d   %d\n", min, prev);
		//최소값을 current로 만든다. 그리고 그 값을 prev로 저장 
		cur = Adjlist[current].head->next;
		while (!cur == NULL) {
			prev = dist[current];
			int stime = cur->tm[date];
			int runing = ceil((cur->length) / 500);// 비행기로 이동시간 ,,	
			//printf("<%c -> %c>\n", current + 'a', cur->data);
			//printf("%c %d| ", cur->data, runing);
			//printf("a)))))prev: %d dist: %d   %d\n", prev, dist[(cur->data)-'a'], graduated[cur->data - 'a']);
			prev += runing;
			if (prev > 1000000) {
				dist[cur->data - 'a'] = prev - 1000000;
				prev = prev - 1000000;
			}
			else if (dist[cur->data - 'a'] >= 1000000) dist[cur->data - 'a'] = prev;
			else if (dist[cur->data - 'a'] > prev) {
				//printf("here!\n");
				dist[cur->data - 'a'] = prev;
				//printf("inputed : %c -> %d\n", cur->data, prev);
			}
			//printf("b)))))prev: %d dist: %d   %d\n", prev, dist[(cur->data) - 'a'], graduated[cur->data - 'a']);
			cur = cur->next;
			//printf("%d\n", dist[10]);
		}

		graduated[current] = 1;
	}
	/*
	for (int i = 0; i < 26; i++) {
		printf("%c | %d\n", i+'a', dist[i]);
	}
	*/

	return dist[arrive - 'a'];
}
/*
int shortest_path(char start, char arrive, int date) {
	int graduated[30];
	int dist[30];
	int prev=0;
	//printf("%c\n", start);
	for (int i = 0; i < 30; i++) {
		graduated[i] = 0;
		way[i] = 1000;
		dist[i] = 1000000;
	}
	int current = start - 'a';
	dist[current] = 0;
	NODE* cur;
	while (1) {
		int min = 0;
		int swit = 0;
		int count = 0;
		prev = dist[current];
		//printf("??:%d   %d\n", dist[current], dist[0]);
		for (int i = 0; i < 26; i++) {
			if (graduated[i] == 0 && swit == 0) {
				min = i;
				swit = 1;

			}
			else {
				if (swit == 1 && graduated[i] == 0 && dist[min] > dist[i]) {
					min = i;
				}
			}

			if(graduated[i]==1) count++;
		}

		//printf("%d\n", min);
		if (count == 26)break;
		//sprintf("min: %d\n", min);
		current = min;

		prev = dist[current];
		//printf("min: %d   %d\n", min, prev);
		//최소값을 current로 만든다. 그리고 그 값을 prev로 저장
		cur = Adjlist[current].head->next;
		while (!cur == NULL) {
			prev = dist[current];
			int stime = cur->tm[date];
			int runing = ceil((cur->length) / 500);// 비행기로 이동시간 ,,
			//printf("<%c -> %c>\n", current + 'a', cur->data);
			//printf("%c %d| ", cur->data, runing);
			//printf("a)))))prev: %d dist: %d   %d\n", prev, dist[(cur->data)-'a'], graduated[cur->data - 'a']);
			prev += runing;
			if (prev > 1000000) {
				dist[cur->data - 'a'] = prev - 1000000;
				dist[cur->data - 'a'] = prev;
				prev = prev - 1000000;
			}
			else if (dist[cur->data - 'a'] >= 1000000) {
				way[cur->data-'a'] = current;
				dist[cur->data - 'a'] = prev;
			}
			else if (dist[cur->data-'a'] > prev) {
				//printf("here!\n");
				dist[cur->data-'a'] = prev;
				//printf("inputed : %c -> %d\n", cur->data, prev);
			}
			//printf("b)))))prev: %d dist: %d   %d\n", prev, dist[(cur->data) - 'a'], graduated[cur->data - 'a']);
			cur = cur->next;
			//printf("%d\n", dist[10]);
		}

		graduated[current] = 1;
	}

	for (int i = 0; i < 26; i++) {
		printf("%c | %d\n", i+'a', dist[i]);
	}


	return dist[arrive - 'a'];
}
*/
int shortest_path(char start, char arrive, int date) {
	int graduated[30];
	int dist[30];
	NODE* cur;
	for (int i = 0; i < 30; i++) {
		graduated[i] = 0;
		travel[i] = 1000;
		dist[i] = 1000;
	}
	dist[start - 'a'] = 0;
	dist[26] = 1000;
	int count = 0;

	while (1) {
		int min = 26;

		for (int i = 0; i < 26; i++) {
			if (graduated[i] == 0 && dist[min] > dist[i]) {
				min = i;
			}

			//printf("%d ? %d\n", dist[min], dist[i]);
		}
		if (min == 26) break;
		//printf("%d min: %c\n", ++count ,min + 'a');
		graduated[min] = 1;
		cur = Adjlist[min].head->next;
		/* 길이 배열 중 최솟값 찾기 */

		while (!cur == NULL) {
			if (graduated[cur->data - 'a'] == 0) {
				int runing = ceil((cur->length) / 500);// 비행기로 이동시간 ,,	
				if (dist[cur->data - 'a'] > (dist[min] + runing)) {
					dist[cur->data - 'a'] = (dist[min] + runing);
					travel[cur->data - 'a'] = min;
				}
			}
			cur = cur->next;
		}

	}
	/*
	for (int i = 0; i < 26; i++) {
		printf("%c | %d\n", i + 'a', dist[i]);
	}
	*/
	return dist[arrive - 'a'];
}



void print_path(char start, char arrive) {
	//printf("here\n");
	/*
	for (int i = 0; i < 26; i++) {
		printf("%c | %c \n", i + 'a', travel[i] + 'a');
	}
	*/
	int count = 0;
	int des = arrive - 'a';
	while (1) {
		trav[count++] = des;
		//printf("here!\n");
		if (des == start - 'a') break;
		des = travel[des];
	}
	//printf("count: %d", count);
	printf("\t\t\t\t\t 경유 경로: ");
	len = count - 1;
	for (int i = count - 1; i >= 0; i--) {
		if (i == 0) printf("%c ", trav[i] + 'a');
		else printf("%c -> ", trav[i] + 'a');
	}
	printf("\n\n");
	return 0;
}

void print_time(int date) {
	int sdat=0, edat=0, sclock=0, eclock=0;
	int dat = date;
	//printf("len: %d\n", len);
	int spend_time = 0;
	int clock = 0;
	int his = 0;
	int temp = 0;
	int temp_sp = 0;
	for (int i = len; i >= 1; i--) {
		
		NODE* cur;
		printf("\n\t\t\t\t\t>>%c 공항\n\n", trav[i] + 'a');
		cur = Adjlist[trav[i]].head->next;
		while (cur != NULL) {
			//printf("here!\n");
			if ((cur->data) - 'a' == trav[i - 1]) {
				temp_sp = ceil((double)(cur->length) / 500);
				
				if (clock + temp_sp >= 24) {
					++dat;
					clock = clock + temp_sp - clock;
				}
				if (cur->tm[dat] < clock) dat++;
				temp = cur->tm[dat];
		
				his = 1;
				break;
			}
			cur = cur->next;
		}
		if (his == 1) {
			clock = temp;
		
			printf("\t\t\t\t\t12월 %d일 %d시 정각 출발\n", dat, clock);
			if (i == len) {
				sdat = dat;
				sclock = clock;
			
			}
			clock += temp_sp;
			spend_time += temp_sp;
			his = 0;
		}
		else {
			if (temp <= clock) {
				dat++;
				spend_time += temp + 24 - clock;
				
			
			}
			else {
				
				spend_time += temp - clock;
			}
			clock = temp;
			clock + temp_sp;


		}
		if (clock >= 24) {
			dat++;
			clock = clock - 24;
			
		}
		printf("\t\t\t\t\t12월 %d일 %d시 정각 도착\n", dat, clock);

	}
	printf("\n\n\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n\n");
	printf("\t\t\t\t\t%c 출발: 12월 %d일 %d시\n\n", trav[len] + 'a', sdat, sclock);
	printf("\t\t\t\t\t%c 도착: 12월 %d일 %d시\n\n", trav[0] + 'a', dat, clock);
	printf("\t\t\t\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n\n");
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
		insertNode(start, dest, times);

	}
}

