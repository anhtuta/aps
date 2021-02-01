/*
Bài này giống bài WordPrefix: giả sử có 1 danh bạ điện thoại gồm các sđt có lenght đều = 10, đếm số các sđt có chung prefix cho trước
Input:
5	// N = 5: số lượng number. 5 dòng tiếp theo là N số có độ dài 10 ký tự mỗi số
9740948824
9617115276
7423221685
9618927954
9623341138
5	// Q = 5: số lượng query. 5 dòng tiếp theo là Q query
9
961
964
96
7423221685
Sample Output:
Case #1
4
Case #2
2
Case #3
0
Case #4
3
Case #5
1
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>

#define ALPHABET_SIZE 10
#define null NULL

using namespace std;

int n, q, T;

struct TrieNode {
	TrieNode* children[ALPHABET_SIZE];
	int cnt;
};

TrieNode* root;
TrieNode pool[1400000];
int cntPool;

TrieNode* createNewNode() {
	TrieNode* pNode = &pool[cntPool++];

	pNode->cnt = 1;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = null;

	return pNode;
}

void initTrie() {
	cntPool = 0;
	root = createNewNode();
}

int getStringLength(char* str) {
	int len = 0;
	while (*str++) len++;
	return len;
}

void insert(char* key) {
	int length = getStringLength(key);
	int index;

	TrieNode* curr = root;

	for (int i = 0; i < length; i++)
	{
		index = key[i] - '0';

		if (curr->children[index] == null) {
			curr->children[index] = createNewNode();
		}
		else {
			curr->children[index]->cnt++;
		}

		curr = curr->children[index];
	}
}

int countPrefixMatching(char* str) {
	TrieNode* curr = root;
	int len = getStringLength(str);
	int index;

	for (int i = 0; i < len; i++)
	{
		index = str[i] - '0';
		if (curr->children[index] == null) return 0;
		curr = curr->children[index];
	}

	return curr->cnt;
}

char str[20];

void input() {
	initTrie();

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> str;
		insert(str);
	}

	cin >> q;
	for (int i = 1; i <= q; i++)
	{
		cin >> str;
		cout << "Case #" << i << endl;
		cout << countPrefixMatching(str) << endl;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	input();
}