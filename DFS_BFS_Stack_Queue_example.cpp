/*
Demo DFS, BFS, stack, queue (implement bằng mảng)
input:
Dòng đầu tiên là 2 số n,e: số đỉnh và số cạnh của đồ thị
e dòng tiếp theo: từng cạnh của đồ thị, mỗi cạnh gồm 2 đỉnh

sample input:
7 8		//số đỉnh, số cạnh
1 2		//các cạnh của đồ thị
1 3
2 4
2 5
3 7
4 6
5 6
6 7

*/
#include <iostream>
#include <stdio.h>

#define MAX 1001
#define INF 9999999

using namespace std;

int T;
int n, e;
int a[MAX][MAX];	//lưu danh sách kề của đồ thị
int myQueue[MAX];
int front, rear;
int myStack[MAX];
int top;
//top: luôn trỏ tới vị trí phần tử trên cùng của stack
//front: trỏ tới TRƯỚC phần từ phía đầu của queue
//rear: trỏ tới phần tử phía cuối của queue (phần tử vừa thêm vào)
//lấy ra phía front, thêm vào phía rear

int mark[MAX];

void init() {
	for(int i = 0; i <= n; i++) {
		mark[i] = 0;
		for(int j = 0; j <= n; j++) a[i][j] = 0;
	}
}

void initMark() {
	for(int i = 0; i <= n; i++) {
		mark[i] = 0;
	}
}

void input() {
	cin >> n >> e;	//e = số lượng cạnh của đồ thị
	init();

	int u,v;
	//đọc từng cạnh của đồ thị
	for(int i = 1; i <= e; i++) {
		cin >> u >> v;
		a[u][0]++;
		a[v][0]++;
		a[u][a[u][0]] = v;
		a[v][a[v][0]] = u;
	}

	/*for(int i = 1; i <= n; i++) {
		printf("Node %d, cac dinh ke voi no: ", i);
		for(int j = 1; j <= a[i][0]; j++) {
			printf("%d ", a[i][j]);
		}
		cout<<endl;
	}
	cout<<endl;*/
}

/*============ my queue ===============*/
void initQueue() {
	front = rear = -1;
}

void enQueue(int value) {
	rear++;
	myQueue[rear] = value;
}

int deQueue() {
	front++;
	int temp = myQueue[front];
	if(front == rear) front = rear = -1;
	return temp;
}

bool isQueueEmpty() {
	return front==-1 && rear==-1;
}
/*============ end of my queue ===============*/

/*============ my stack ===============*/
void initStack() {
	top = -1;
}

bool isStackEmpty() {
	return top==-1;
}

void push(int data) {
	top++;
	myStack[top] = data;
}

int pop() {
	if(isStackEmpty()) {
		printf("Stack is empty, can't pop!\n");
		return -1;
	}

	int temp = myStack[top];
	top--;
	return temp;
}
/*============ end of my stack ===============*/

void DFS(int k) {
	mark[k] = 1;
	printf("%d ", k);
	for(int i=1; i<=a[k][0]; i++) {
		if(mark[a[k][i]] == 0) DFS(a[k][i]);
	}
}

void printMark() {
	cout<<"print mark\n";
	for(int i=1; i<=n; i++) printf("%d ", mark[i]);
	cout<<endl;
}

void printQueue() {
	cout<<"print queue\n";
	for(int i = front+1; i <= rear; i++) {
		cout<<myQueue[i]<<" ";
	}
	cout<<endl;
}

//k = node bắt đầu BFS
void BFS(int k) {
	mark[k] = 1;
	enQueue(k);
	cout << k << " ";

	while(!isQueueEmpty()) {
		int node = deQueue();

		//Xét các hàng xóm của node
		for(int i = 1; i <= a[node][0]; i++) {
			int v = a[node][i];
			if(mark[v] == 0) {
				mark[v] = 1;
				enQueue(v);
				cout << v << " ";
			}
		}
	}
}

int main() {
	freopen("DemoDFSBFS.txt", "r", stdin);
	input();
	DFS(1);
	cout<<endl;

	initMark();
	BFS(1);
}
