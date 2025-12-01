typedef struct INFO
{
	char bname[100];
	int many;
	int price;
	char genre[20];
	int page;
	int reserch;
	struct INFO * link;
}info;

typedef struct
{
	info* head;
	int length;
}First;

typedef struct User
{
	char name[30];
	info * head;
}users;

void clearline();
First* initList();
void addbook(First* core, char* name, int a, int b, char* bgenre, int c);
void display(First* core);
void addbook_num(First* core, char*, int a);
users* assign(char* answer);
void booking(char * answer, char * answer2, First*core, users**user, int usernum);
void search_u(users** user, int usernum, char * answer);
int search_b(First* core, char* answer);
int sort(First* core);
void returning(char* bookname, char* username, First* core, users** user, int usernum);
int Starting(First* core, users** user);