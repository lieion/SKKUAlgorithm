#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>

class City {
public:
	char name;
	int pos_x;
	int pos_y;
};

class Node {
public:	
	Node* next;
	City city;
};

// Adjacency list 그래프 구현에 필요
class ADJList {
public:
	Node* head;

	ADJList() {
		head = NULL;
	}

	void insertNode(City city) {
		Node* temp = new Node();
		temp->city = city;
		temp->next = head;
		head = temp;
	}
};

int pathCheck(char random_path[100][3], int num) {
	for (int i = 0; i < num; i++) {
		if ((random_path[i][0] == random_path[num][0] && random_path[i][1] == random_path[num][1]) || (random_path[i][0] == random_path[num][1] && random_path[i][1] == random_path[num][0])) {
			return 1;
		}
	}
	return 0;
}

int main() {
	srand(time(NULL));
	ADJList* adjlist = new ADJList[26];
	char random_path[100][3];
	
	City city[26];
	for (int i = 0; i < 26; i++) {
		city[i].name = i + 'a';
		city[i].pos_x = rand() % 6000 - 3000;
		city[i].pos_y = rand() % 6000 - 3000;
	}

	for (int i = 0; i < 100; i++) {
		random_path[i][0] = (rand() % 26) + 'a';
		random_path[i][1] = (rand() % 26) + 'a';
		if ((random_path[i][0] == random_path[i][1]) || pathCheck(random_path, i)){
			i--;
			continue;
		}
	}

	for (int i = 0; i < 100; i++) {
		char start = random_path[i][0];
		char dest = random_path[i][1];

		adjlist[i].insertNode(city[start - 'a']);
		adjlist[i].insertNode(city[dest - 'a']);
	}
}
