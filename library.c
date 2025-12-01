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
	next->reserch = 1;
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

	temp = core->head;
	while (temp != NULL)
	{
		if (strcmp(temp->bname, answer) == 0)
		{
			if (temp->many <= 0)
			{
				printf("해당 책은 현재 모두 대출 중입니다.\n");
				return;
			}
			temp->many -= 1;

			next = (info*)malloc(sizeof(info));
			strcpy(next->bname, temp->bname);
			strcpy(next->genre, temp->genre);
			next->page = temp->page;
			next->many = 1;     
			next->price = temp->price;
			next->reserch = 1;
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
			return;
		}
	}
	if (!found)
		printf("해당 인물은 없습니다\n");
}

int search_b(First* core, char* answer)
{
	char choice[30];
	info* temp;
	int check = 0;
	temp = core->head;

	if (temp == NULL)
	{
		printf("아직 도서관 내 도서가 없습니다");
		return 0;
	}

	int count = 1;

	while (temp != NULL)
	{
		if (temp->reserch == 1)
		{
			char* found_title = strstr(temp->bname, answer);
			char* found_genre = strstr(temp->genre, answer);

			if (found_title != NULL || found_genre != NULL)
			{
				check = 1;
				printf("\n[%d 번째 도서]\n", count);
				printf("----------------------------------------\n");
				printf(" 제목        : %s\n", temp->bname);
				printf(" 들어온 권수 : %d 권\n", temp->many);
				printf(" 가격        : %d 원\n", temp->price);
				printf(" 장르        : %s\n", temp->genre);
				printf(" 페이지 수   : %d 페이지\n", temp->page);
				printf("----------------------------------------\n");
				count++;
			}
			else
			{
				temp->reserch = 0;
			}
		}

		temp = temp->link;
	}

	if (check == 0)
	{
		printf("해당 정보의 책은 없습니다\n");
		return 0;
	}

	printf("재검색을 하시겠습니까?(예, 아니오)\n");
	printf("> ");
	scanf("%s", choice);
	clearline();

	while (1)
	{
		if (strcmp(choice, "예") == 0)
		{
			printf("세부적으로 검색할 키워드를 입력하세요\n");
			printf("> ");
			scanf("%s", answer);
			clearline();

			return search_b(core, answer);
		}
		else if (strcmp(choice, "아니오") == 0)
		{
			temp = core->head;
			while (temp != NULL)
			{
				temp->reserch = 1;
				temp = temp->link;
			}
			return 0;
		}
		else
		{
			printf("다시 입력해주세요\n> ");
			scanf("%s", choice);
			clearline();
		}
	}
}

int sort(First* core)
{
	if (core->head == NULL || core->head->link == NULL)
		return 0;

	info* dummy = (info*)malloc(sizeof(info));
	dummy->link = core->head;

	info* prev;
	info* curr;
	info* next;
	int swapped = 1;

	while (swapped)
	{
		swapped = 0;
		prev = dummy;
		curr = dummy->link;

		while (curr->link != NULL)
		{
			next = curr->link;

			if (strcmp(curr->bname, next->bname) > 0)
			{
				curr->link = next->link;
				next->link = curr;
				prev->link = next;

				swapped = 1;
				prev = next;
			}
			else
			{
				prev = curr;
				curr = curr->link;
			}
		}
	}

	// 머리 교체
	core->head = dummy->link;
	free(dummy);
	return 1;
}

void returning(char* bookname, char* username, First* core, users** user, int usernum)
{
	users* targetUser = NULL;

	for (int i = 0; i < usernum; i++)
	{
		if (strcmp(user[i]->name, username) == 0)
		{
			targetUser = user[i];
			break;
		}
	}

	if (targetUser == NULL)
	{
		printf("해당 인물을 찾을 수 없습니다.\n");
		return;
	}

	info* prev = NULL;
	info* cur = targetUser->head;

	while (cur != NULL)
	{
		if (strcmp(cur->bname, bookname) == 0)
		{
			if (prev == NULL)
			{
				targetUser->head = cur->link;
			}
			else
			{
				prev->link = cur->link;
			}

			free(cur);

			info* lib = core->head;
			while (lib != NULL)
			{
				if (strcmp(lib->bname, bookname) == 0)
				{
					lib->many += 1;
					break;
				}
				lib = lib->link;
			}

			printf("%s님이 %s을(를) 반납했습니다.\n", username, bookname);
			return;
		}

		prev = cur;
		cur = cur->link;
	}

	printf("해당 회원은 이 책을 빌린 기록이 없습니다.\n");
}

int Starting(First* core, users** user)
{
	info* b1 = (info*)malloc(sizeof(info));
	strcpy(b1->bname, "해리포터1");
	strcpy(b1->genre, "판타지");
	b1->many = 3;
	b1->price = 15000;
	b1->page = 350;
	b1->reserch = 1;
	b1->link = NULL;
	core->head = b1;

	info* b2 = (info*)malloc(sizeof(info));
	strcpy(b2->bname, "해리포터2");
	strcpy(b2->genre, "판타지");
	b2->many = 2;
	b2->price = 15000;
	b2->page = 380;
	b2->reserch = 1;
	b2->link = NULL;
	b1->link = b2;

	info* b3 = (info*)malloc(sizeof(info));
	strcpy(b3->bname, "해리포터3");
	strcpy(b3->genre, "판타지");
	b3->many = 4;
	b3->price = 16000;
	b3->page = 420;
	b3->reserch = 1;
	b3->link = NULL;
	b2->link = b3;

	info* b4 = (info*)malloc(sizeof(info));
	strcpy(b4->bname, "해리포터연대기");
	strcpy(b4->genre, "판타지");
	b4->many = 1;
	b4->price = 20000;
	b4->page = 500;
	b4->reserch = 1;
	b4->link = NULL;
	b3->link = b4;

	info* b5 = (info*)malloc(sizeof(info));
	strcpy(b5->bname, "해리포터마법책");
	strcpy(b5->genre, "판타지");
	b5->many = 5;
	b5->price = 12000;
	b5->page = 300;
	b5->reserch = 1;
	b5->link = NULL;
	b4->link = b5;

	core->length = 5;

	user[0] = assign("홍석");
	user[1] = assign("민수");
	user[2] = assign("지훈");

	info* h1 = (info*)malloc(sizeof(info));
	*h1 = *b1;
	h1->many = 1;
	h1->link = NULL;
	user[0]->head = h1;
	b1->many--;

	info* h2 = (info*)malloc(sizeof(info));
	*h2 = *b2;
	h2->many = 1;
	h2->link = NULL;
	h1->link = h2;
	b2->many--;

	info* m1 = (info*)malloc(sizeof(info));
	*m1 = *b5;
	m1->many = 1;
	m1->link = NULL;
	user[1]->head = m1;
	b5->many--;

	info* j1 = (info*)malloc(sizeof(info));
	*j1 = *b3;
	j1->many = 1;
	j1->link = NULL;
	user[2]->head = j1;
	b3->many--;

	info* j2 = (info*)malloc(sizeof(info));
	*j2 = *b4;
	j2->many = 1;
	j2->link = NULL;
	j1->link = j2;
	b4->many--;

	return 3;
}