/*
Demo Hash data structure
Giả sử cho ds sinh viên, cần lưu lại và tìm kiếm theo username
=> ta sẽ hash theo username
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>

#define HASH_TABLE_SIZE 100007
#define POOL_SIZE 1000000
#define null NULL
#define MAX_NAME_LENGTH 50

using namespace std;

unsigned int myHash(char* name) {
	unsigned int h = 7;
	int i = 0;
	int c;

	while (name[i] != 0) {
		c = name[i] - 'a';
		h = ((h << 5) + h + c) % HASH_TABLE_SIZE;
		i++;
	}

	return h;
}

void copyString(char* from, char* to) {
	int i = 0;
	while (from[i] != 0) {
		to[i] = from[i];
		i++;
	}
	to[i] = 0;
}

int compareString(char* str1, char* str2) {
	int flag = 0, i = 0;

	while (flag != 0) {
		if (str1[i] > str2[i]) flag = 1;
		else if (str1[i] < str2[i]) flag = -1;

		if (str1[i] == 0) break;

		i++;
	}

	return flag;
}

struct Node {
	// lưu username
	char fieldValue[MAX_NAME_LENGTH];

	// lưu vị trí bản ghi trong Table
	int id;

	Node* next;
};
Node* head[HASH_TABLE_SIZE];
Node pool[POOL_SIZE];
int cntPool;

struct Table {
	char username[MAX_NAME_LENGTH];
	int mssv;
	char school[MAX_NAME_LENGTH];
};
Table table[1000];
int auto_increment;

void initHash() {
	cntPool = auto_increment = 0;
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		head[i] = null;
	}
}

/*
Việc insert này ko check xem trong hash đã tồn tại phần tử
username hay chưa. Do đó trước khi insert cần check ở chỗ khác
(Có thể dùng hàm searchFromHash(username) trước, nếu search được
thì ko insert nữa)
*/
void insertToHash(char username[MAX_NAME_LENGTH], int indexOfRealData) {
	int h = myHash(username);

	Node* t = &pool[cntPool++];
	copyString(username, t->fieldValue);
	t->id = indexOfRealData;

	if (head[h] == null) {
		head[h] = t;
		t->next = null;
	}
	else {
		t->next = head[h];
		head[h] = t;
	}
}

int searchFromHash(char username[MAX_NAME_LENGTH]) {
	int h = myHash(username);
	Node* curr = head[h];

	while (curr != null) {
		if (compareString(curr->fieldValue, username) == 0) {
			return curr->id;
		}
		curr = curr->next;
	}

	return -1;
}

int main() {
	freopen("input.txt", "r", stdin);
	initHash();

	int n;
	char username[MAX_NAME_LENGTH];
	int mssv;
	char school[MAX_NAME_LENGTH];

	// init data
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s %d %s", username, &mssv, school);
		//printf("%s %d %s\n", username, mssv, school);
		Table t;
		copyString(username, t.username);
		t.mssv = mssv;
		copyString(school, t.school);
		table[auto_increment] = t;

		insertToHash(username, auto_increment);
		auto_increment++;
	}

	// now let test our hash by searching
	char searchName1[10] = "charlotte";
	char searchName2[10] = "anhtuta";
	int id1 = searchFromHash(searchName1);
	int id2 = searchFromHash(searchName2);
	printf("id1 = %d, id2 = %d\n", id1, id2);
	if (id1 >= 0) {
		printf("%s: %d, %s\n", searchName1, table[id1].mssv, table[id1].school);
	}

	return 51195;	// it's my birthday :)
}