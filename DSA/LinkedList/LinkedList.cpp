#include <iostream>
#include <stdio.h>

using namespace std;

struct Node {
	int data;
	struct Node* next;
};

// danh sách liên kết
struct Node* head;

// kích thước của ds liên kết
int listSize;

void initList() {
	head = NULL;
	listSize = 0;
}

// insert data vào đầu list
void insertFirst(int data) {
	Node* t = new Node();
	t->data = data;

	listSize++;

	if (head == NULL) {
		head = t;
		head->next = NULL;
	}
	else {
		t->next = head;
		head = t;
	}
}

// nếu dùng curr thay cho head: TẠI SAO SAI:
//void insertFirst(int data) {
//	Node *t = new Node();
//	t->data = data;
//	Node *curr;
//	curr = head;
//
//	listSize++;
//
//	if(curr == NULL) {
//		curr = t;	// SAI CHỖ NÀY! VÌ GÁN curr = t ko ảnh hưởng đến head
//		curr->next = NULL;
//	} else {
//		t->next = curr;
//		curr = t;	// SAI CHỖ NÀY! VÌ GÁN curr = t ko ảnh hưởng đến head
//	}
//}

void insertAt(int position, int data) {
	if (position < 0 || position > listSize) return;
	if (position == 0) {
		insertFirst(data);
		return;
	}

	Node* t = new Node();
	t->data = data;

	listSize++;

	Node* prevNode, * currNode;
	prevNode = NULL, currNode = head;
	int currPos = 0;

	while (currPos != position) {
		prevNode = currNode;
		currNode = currNode->next;
		currPos++;
	}

	prevNode->next = t;
	t->next = currNode;		//nếu insert vào cuối list thì currNode = NULL
}

void appendList(int data) {
	insertAt(listSize, data);
}

void printList() {
	Node* t = head;

	if (t == NULL) {
		printf("empty ");
		return;
	}

	while (t != NULL) {
		printf("%d ", t->data);
		t = t->next;
	}
}

int getListSize() {
	return listSize;
}

void removeFirst() {
	if (head == NULL) return;

	listSize--;

	Node* temp = head;
	head = head->next;

	delete temp;
}


// xóa phần tử thứ position (position >= 0). Nếu position vượt quá vị trí của phần tử cuối cùng thì không làm gì. 
// chú ý: vị trí phần tử cuối cùng = listSize-1
void removeAt(int position) {
	if (position >= listSize || position < 0) return;
	if (position == 0) {
		removeFirst();
		return;
	}

	listSize--;

	Node* prevNode, * currNode;
	prevNode = NULL, currNode = head;
	int currPos = 0;

	while (currPos != position) {
		prevNode = currNode;
		currNode = currNode->next;
		currPos++;
	}

	// bây giờ remove currNode là xong
	// Nếu remove phần tử cuối cùng thì currNode->next = NULL,
	// do đó vẫn đúng!
	prevNode->next = currNode->next;

	// cần giải phóng node cần xóa, vì C/C++ ko tự động giải phóng
	delete currNode;
}

void removeLast() {
	removeAt(listSize - 1);
}

void demo() {
	Node* curr = head;
	curr = curr->next->next;

	Node* t = new Node;
	t->data = 1234;
	t->next = NULL;

	// thay đổi dslk
	curr->next = t;
}

void demo2() {
	Node* curr = head;
	curr = curr->next->next;

	Node* t = new Node;
	t->data = 1234;
	t->next = NULL;

	// dslk ko bị thay đổi
	curr = t;
}


int main() {
	initList();

	appendList(2);
	appendList(4);
	appendList(12);
	printList(); cout << endl;

	insertFirst(3);
	printList(); cout << endl;

	insertFirst(1);
	insertFirst(22);
	insertFirst(5);
	insertFirst(9);
	insertFirst(13);
	printList(); cout << endl;
	printf("Size = %d\n", getListSize());

	demo2();
	cout << "After demo\n";
	printList(); cout << endl;
	printf("Size = %d\n", getListSize());


	cout << "Insert '3' into position 2\n";
	insertAt(2, 3);
	printList(); cout << endl;

	insertAt(5, 101);
	printList(); cout << endl;

	insertAt(500, 21);
	printList(); cout << endl;

	cout << "Insert '7' into position 0\n";
	insertAt(0, 7);
	printList(); cout << endl;

	insertAt(-1, 17);
	printList(); cout << endl;

	printf("Size = %d\n", getListSize());

	cout << "removing first...\n";
	removeFirst();
	removeFirst();
	removeFirst();
	printList(); cout << endl;
	printf("Size = %d\n", getListSize());

	cout << "removing at position = 2\n";
	removeAt(2);
	printList(); cout << endl;

	cout << "removing at position = 1111\n";
	removeAt(1111);
	printList(); cout << endl;

	cout << "removing at last position\n";
	removeAt(getListSize() - 1);
	printList(); cout << endl;

	cout << "removing at 2nd last position\n";
	removeAt(getListSize() - 2);
	printList(); cout << endl;

	cout << "removing first\n";
	removeAt(0);
	printList(); cout << endl;

	cout << "removing first\n";
	removeFirst();
	printList(); cout << endl;

	cout << "removing first\n";
	removeFirst();
	printList(); cout << endl;

	cout << "removing first\n";
	removeFirst();
	printList(); cout << endl;

	cout << "removing first\n";
	removeFirst();
	printList(); cout << endl;

	cout << "removing first\n";
	removeFirst();
	printList(); cout << endl;
}