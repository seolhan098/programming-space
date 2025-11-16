#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"

First* initList() {
	First* core;
	core = (First*)malloc(sizeof(First));
	core->head = NULL;
	core->length = 0;
	return core;
}

void clearline()
{
	while (getchar() != '\n');
}

void addbook(First* core, char* name, int a, int b, char* bgenre, int c) {
	info* next, * temp;
	next = (info*)malloc(sizeof(info));
	strcpy(next->bname, name);
	next->many = a;
	next->price = b;
	strcpy(next->genre, bgenre);
	next->page = c;
	next->reserch = 0;
	next->link = NULL;
	if (core->head == NULL)
	{
		core->head = next;
	}
	else
	{
		temp = core->head;
		while (temp->link != NULL)
		{
			temp = temp->link;
		}
		temp->link = next;
	}
	printf("\n========================================\n");
	printf("새 도서가 추가되었습니다!\n");
	printf("----------------------------------------\n");
	printf(" 제목        : %s\n", next->bname);
	printf(" 들어온 권수 : %d 권\n", next->many);
	printf(" 가격        : %d 원\n", next->price);
	printf(" 장르        : %s\n", next->genre);
	printf(" 페이지 수   : %d 페이지\n", next->page);
	printf("========================================\n\n");
}

void display(First* core)
{
	info* list = core->head;
	int count = 1;

	if (list == NULL)
	{
		printf("\n---  도서 목록이 비어 있습니다. ---\n\n");
		return;
	}

	printf("\n==========  도서 목록 보기  ==========\n");

	while (list != NULL)
	{
		printf("\n[%d 번째 도서]\n", count);
		printf("----------------------------------------\n");
		printf(" 제목        : %s\n", list->bname);
		printf(" 들어온 권수 : %d 권\n", list->many);
		printf(" 가격        : %d 원\n", list->price);
		printf(" 장르        : %s\n", list->genre);
		printf(" 페이지 수   : %d 페이지\n", list->page);
		printf("----------------------------------------\n");

		count++;
		list = list->link;
	}

	printf("==========================================\n\n");
}
void addbook_num(First* core, char* name, int a)
{
	info* temp;
	temp = core->head;
	if (temp == NULL)
	{
		printf("\n---  해당 이름의 책은 없습니다. ---\n\n");
		return;
	}
	while (temp != NULL)
	{
		if (strcmp(temp->bname, name) == 0)
		{
			temp->many = temp->many + a;
			printf("==========================================\n\n");
			return;
		}
		temp = temp->link;
	}
	printf("\n---  해당 이름의 책은 없습니다. ---\n\n");
	printf("==========================================\n\n");
}

users* assign(char* answer)
{
	users* user;
	user = (users*)malloc(sizeof(users));
	strcpy(user->name, answer);
	user->head = NULL;
	return user;
}

void booking(char* answer, char* answer2, First* core, users** user, int usernum)
{
	info* temp, * next;
	users* targetUser = NULL;

	// 회원 찾기
	for (int i = 0; i < usernum; i++)
	{
		if (strcmp(user[i]->name, answer2) == 0)
		{
			targetUser = user[i];
			break;
		}
	}
	if (targetUser == NULL)
	{
		printf("해당 인물을 찾아볼 수 없습니다\n");
		return;
	}

	// 책 찾기
	temp = core->head;
	while (temp != NULL)
	{
		if (strcmp(temp->bname, answer) == 0)
		{
			next = (info*)malloc(sizeof(info));
			strcpy(next->bname, temp->bname);
			strcpy(next->genre, temp->genre);
			next->page = temp->page;
			next->link = NULL;

			if (targetUser->head == NULL)
			{
				targetUser->head = next;
			}
			else
			{
				info* p = targetUser->head;
				while (p->link != NULL)
					p = p->link;
				p->link = next;
			}

			printf("%s님이 %s을(를) 대출했습니다.\n", answer2, answer);
			return; 
		}
		temp = temp->link;
	}

	printf("해당 책을 찾을 수 없습니다\n");
}

void search_u(users** user, int usernum, char* answer)
{
	int found = 0;
	for (int i = 0; i < usernum; i++)
	{
		if (strcmp(user[i]->name, answer) == 0)
		{
			found = 1;
			info* list = user[i]->head;
			printf("회원 이름: %s\n", user[i]->name);
			if (list == NULL)
			{
				printf("--- 대출한 책이 없습니다 ---\n\n");
				return;
			}

			int count = 1;
			printf("대출한 책 목록:\n");
			while (list != NULL)
			{
				printf("[%d] %s\n", count, list->bname);
				list = list->link;
				count++;
			}
		}
	}
	if (!found)
		printf("해당 인물은 없습니다\n");
}