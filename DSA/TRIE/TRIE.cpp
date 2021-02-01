/*
Giả sử có 1 danh sách các sinh viên với thông tin: username, mssv, school. Tạo TRIE để search theo username, và đưa ra thông tin các sinh viên có username là 1 prefix nào đó
Input:
20  // N=20: số lượng sinh viên. 20 dòng tiếp theo là 20 sinh viên theo format: "username mssv school"
anthony 20132322 FTU
akira 20112323 TLU
binhnt 20141010 FPT
tuta 20134509 HUST
tuzaku 22001919 HANU
tungnt 20112341 FPT
willsmith 20131001 HUST
jordan 20143292 FTU
john 20133929 FPT
challote 20121921 NEU
linhbka 20121212 HUTECH
lubu 20102120 HUST
liliana 20110220 HANU
alexandra 20110221 HANU
trungnt 20123029 SAMSUNG
nguvanngoc 20110101 NEU
tamara 20201019 TLU
terri 21011129 FPT
lionel 20110011 HUST
huyga 20122121 HUTECH

Bài toán:
- Tìm sinh viên theo username (1)
- Đếm số lượng username có chung prefix nào đó (2)

Note: với bài toán (1), ta có thể dùng Hashtable để lưu với key=username, value=info của sinh viên
Nhưng với bài toán (2) thì dùng hash khó có thể đếm được! Giải pháp là dùng TRIE (cây từ điển)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>

#define ALPHABET_SIZE 26

#define POOL_SIZE 1000000
#define null NULL

using namespace std;

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

int charToIndex(char c) { return c - 'a'; }

struct TrieNode {
	int cnt;	// đếm số phần tử có chung prefix
	int id;		// trỏ tới id trong bảng data thật, nếu = -1 thì ko trỏ tới gì
	TrieNode* children[ALPHABET_SIZE];
};

TrieNode* root;
TrieNode pool[POOL_SIZE];
int cntPool;

TrieNode* createNewNode() {
	TrieNode* node = &pool[cntPool++];
	node->cnt = 1;
	node->id = -1;
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		node->children[i] = null;
	}
	return node;
}

struct Table {
	char username[50];
	int mssv;
	char school[50];
};
Table table[1000];
int auto_increment;

void initTRIE() {
	cntPool = auto_increment = 0;
	root = createNewNode();
}

void insertToTRIE(char username[50], int indexOfRealData) {
	TrieNode* curr = root;
	int index, i = 0;

	while (username[i] != 0) {
		index = charToIndex(username[i]);
		if (curr->children[index] == null) {
			curr->children[index] = createNewNode();
		}
		else {
			curr->children[index]->cnt++;
		}

		curr = curr->children[index];
		i++;
	}
	curr->id = indexOfRealData;
}

int searchFromTRIE(char username[50]) {
	TrieNode* curr = root;
	int index, i = 0;

	while (username[i] != 0) {
		index = charToIndex(username[i]);
		if (curr->children[index] == null) return -1;

		curr = curr->children[index];
		i++;
	}

	return curr->id;
}

int cntPrefix(char prefix[50]) {
	TrieNode* curr = root;
	int index, i = 0;

	while (prefix[i] != 0) {
		index = charToIndex(prefix[i]);
		if (curr->children[index] == null) return 0;

		curr = curr->children[index];
		i++;
	}

	return curr->cnt;
}

int main() {
	freopen("input.txt", "r", stdin);
	initTRIE();

	int n;
	char username[50];
	int mssv;
	char school[50];

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

		insertToTRIE(username, auto_increment);
		auto_increment++;
	}

	// now let test our hash by searching
	int id1 = searchFromTRIE((char*)"tuzaku");
	int id2 = searchFromTRIE((char*)"anhtuta");
	printf("id1 = %d, id2 = %d\n", id1, id2);
	if (id1 >= 0) {
		printf("id1 info: %s, %d, %s\n", table[id1].username, table[id1].mssv, table[id1].school);
	}
	if (id2 >= 0) {
		printf("id2 info: %s, %d, %s\n", table[id2].username, table[id2].mssv, table[id2].school);
	}

	// count prefix
	int pre1 = cntPrefix((char*)"li");
	int pre2 = cntPrefix((char*)"tu");
	int pre3 = cntPrefix((char*)"anhtuta");
	printf("pre1 = %d, pre2 = %d, pre3 = %d\n", pre1, pre2, pre3);
}