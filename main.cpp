#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <time.h>

typedef struct city {
	char name;
	int pos_x;
	int pos_y;
} City;

typedef struct node {
	struct node* next;
	int data;
}NODE;

int pathCheck(char random_path[100][3], int num) {
	for (int i = 0; i < num; i++) {
		if ((random_path[i][0] == random_path[num][0] && random_path[i][1] == random_path[num][1]) || (random_path[i][0] == random_path[num][1] && random_path[i][1] == random_path[num][0])) {
			return 1;
		}
	}
	return 0;
}
int main(void){
  srand(time(NULL));
	NODE* head[26];
	char random_path[100][3];
	
	for (int i = 0; i < 100; i++) {
		random_path[i][0] = (rand() % 26) + 'a';
		random_path[i][1] = (rand() % 26) + 'a';
		if ((random_path[i][0] == random_path[i][1]) || pathCheck(random_path, i)){
			i--;
			continue;
		}
	}
  return 0;
}
