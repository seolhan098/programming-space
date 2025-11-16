#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "library.h"

int main()
{
    printf("\n==========================================\n");
    printf("    평화로운 도서관 관리 시스템 \n");
    printf("==========================================\n");
    printf("원하시는 기능을 입력하세요\n\n");
    printf("------------------------------------------\n> ");

    char answer[50];
    char answer2[50];
    int book;
    int price;
    char genre[30];
    int page;
    First* core;
    users* user[30];
    int usernum = 0;
    core = initList();

    while (1)
    {
        printf("[ 메뉴 목록 ]\n");
        printf("  - 회원 가입\n");
        printf("  - 회원 정보\n");
        printf("  - 도서 추가\n");
        printf("  - 권수 추가\n");
        printf("  - 도서 검색\n");
        printf("  - 도서 정렬\n");
        printf("  - 도서 대출\n");
        printf("  - 도서 반납\n");
        printf("  - 도서 보기\n");
        printf("  - 나가기\n");
        printf("------------------------------------------\n> ");
        fgets(answer, sizeof(answer), stdin);
        answer[strcspn(answer, "\n")] = '\0';

        if (strcmp(answer, "회원 가입") == 0)
        {
            printf("회원 가입할 이름을 입력해주세요\n");
            printf("> ");
            scanf("%s", answer);
            clearline();  // 버퍼에 남은 \n 제거
            user[usernum] = assign(answer);
            usernum++;
        }
        else if (strcmp(answer, "회원 정보") == 0)
        {
            printf("검색할 회원의 이름을 입력하세요\n");
            printf("> ");
            scanf("%s", answer);
            clearline();
            search_u(user, usernum, answer);
            clearline();
        }
        else if (strcmp(answer, "도서 추가") == 0)
        {
            printf("해당 책의 대한 정보를 입력해주세요.\n(이름, 들어온 권수, 가격, 장르, 페이지 수 순)\n");
            printf("> ");
            scanf("%s %d %d %s %d", answer, &book, &price, genre, &page);
            addbook(core, answer, book, price, genre, page);
            clearline();
        }
        else if (strcmp(answer, "권수 추가") == 0)
        {
            printf("책의 이름과 추가할 권수를 적어주세요.\n(이름, 권수)\n");
            printf("> ");
            scanf("%s %d", answer, &book);
            addbook_num(core, answer, book);
            clearline();
        }
        else if (strcmp(answer, "도서 검색") == 0)
        {

        }
        else if (strcmp(answer, "도서 정렬") == 0)
        {

        }
        else if (strcmp(answer, "도서 대출") == 0)
        {
            printf("빌릴 책의 이름과 빌리실 분의 이름을 입력해주세요.\n");
            printf("> ");
            scanf("%s %s", answer, answer2);
            booking(answer, answer2, core, user, usernum);
            clearline();
        }
        else if (strcmp(answer, "도서 반납") == 0)
        {
            
        }
        else if (strcmp(answer, "도서 보기") == 0)
        {
            display(core);
        }
        else if (strcmp(answer, "나가기") == 0)
        {
            break;
            printf("시스템 종료");
        }
        else 
        {
            printf("해당 기능은 없습니다\n");
        }
    }

    return 0;
}