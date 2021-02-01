/*
Cho 1 danh sách các từ chỉ gồm các ký tự a-z. Yêu cầu đếm số lượng các từ có tiền tố là 1 string cho trước
Input sẽ như sau:
1	// Số lượng testcase
12 6	// N=12: số lượng word, Q=6: số lượng query (số lần cần đếm số từ có chung prefix).
bulldog		// 12 dòng tiếp theo là 12 từ
dog
dogged
doggedly
doggerel
dogma
dogmatic
dogmatism
dogs
catastroph
catastroph
doctor
cat		// 6 dòng tiếp là 6 prefix tương ứng cho 6 query
dog
dogg
do
doctrinography
dogge
Output: với mỗi query, in ra số từ có chung prefix đã cho:
#1 2 8 3 9 0 3
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>

#define ALPHABET_SIZE 26
#define null NULL
#define MAX_LENGTH 1000

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

using namespace std;

int n, q;

int getStringLength(char* str) {
	int len = 0;

	// *str++; = trỏ tới ô nhớ tiếp theo
	while (*str++) len++;

	return len;
}

// trie node 
struct TrieNode {
	TrieNode* children[ALPHABET_SIZE];
	int cnt;
};

TrieNode* root;
TrieNode pool[1000000];
int cntPool;

TrieNode* createNewNode() {
	TrieNode* pNode = &pool[cntPool++];

	pNode->cnt = 1;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = null;

	return pNode;
}

void insert(char* key) {
	int length = getStringLength(key);
	int index;

	TrieNode* curr = root;

	// lặp tới khi hết chuỗi (tới khi gặp ký tự '\0')
	for (int i = 0; i < length; i++) {
		index = key[i] - 'a';

		if (curr->children[index] == null) {  // if (!curr->children[index])
			curr->children[index] = createNewNode();
		}
		else {
			curr->children[index]->cnt++;
		}

		curr = curr->children[index];
	}
}

int searchPrefix(char* key) {
	int length = getStringLength(key);
	int index;

	TrieNode* curr = root;

	// lặp tới khi hết chuỗi (tới khi gặp ký tự '\0')
	for (int i = 0; i < length; i++) {
		index = key[i] - 'a';

		if (curr->children[index] == null)
			return 0;

		curr = curr->children[index];
	}

	return curr->cnt;
}

char str[MAX_LENGTH];

void input() {
	// init
	cntPool = 0;
	root = createNewNode();

	cin >> n >> q;

	for (int i = 0; i < n; i++)
	{
		cin >> str;
		insert(str);
	}

	for (int i = 0; i < q; i++)
	{
		cin >> str;
		cout << searchPrefix(str) << " ";
	}
	cout << endl;
}

int main() {
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cout << "#" << tc << " ";
		input();
	}
}