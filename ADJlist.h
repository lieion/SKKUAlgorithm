#ifndef ADJlist_H
#define ADJlist_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#pragma warning (disable : 4996)
typedef enum { false, true } bool;
typedef struct city {
	char name;
	int pos_x;
	int pos_y;
} City;

typedef struct node {
	struct node* next;
	int data;
	int tm[31];
	int length;
}NODE;

typedef struct link
{
	NODE* head;
	int len;
} LinkedList;

City city[26];

int visited[26];
int travel[30];
int trav[30];
int len;
LinkedList Adjlist[50];

int pathCheck(char random_path[100][3], int num);
void random_City_Position(City* city);
void insertNode(char start, char dest, int times);
void init_Node();
void PrintList(char start);
void PrintListTime(char city_name, int date_num);
void checkDestination(int start);
int shortest_path(char start, char arrive, int date);
void print_path(char start, char arrive);
void print_time(int date);
void make_ADJlist();












#endif
