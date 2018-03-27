/*
Bao ve nong trang
Nông trang có rất nhiều ngọn đồi núi, để bảo vệ nông trang nông dân John muốn đặt 
người canh gác trên các ngọn đồi này.

Anh ta băn khoăn không biết sẽ cần bao nhiêu người canh gác nếu như anh ta muốn 
đặt 1 người canh gác trên đỉnh của mỗi đồi. Anh ta có bản đồ của nông trang là 
một ma trận gồm N (1 < N <= 700) hàng và M (1 < M <= 700) cột. Mỗi phần tử của 
ma trận là độ cao H_ij so với mặt nước biển (0 <= H_ij <= 10,000) của ô (i, j). 
Hãy giúp anh ta xác định số lượng đỉnh đồi trên bản đồ.

Đỉnh đồi là 1 hoặc nhiều ô nằm kề nhau của ma trận có cùng độ cao được bao quanh 
bởi cạnh của bản đồ hoặc bởi các ô có độ cao nhỏ hơn. Hai ô gọi là kề nhau nếu 
độ chênh lệch giữa tọa độ X không quá 1 và chênh lệch tọa độ Y không quá 1.

[Input]
* Dòng 1: Số lượng mẫu
* Dòng 2: Hai số nguyên cách nhau bởi dấu cách: N và M
* Dòng 3: N+1: Dòng i+1 mô tả hàng i của ma trận với M số nguyên cách nhau bởi dấu cách: H_ij

[Output]
* Dòng 1: Một số nguyên duy nhất là số lượng đỉnh đồi.

[Sample]
[Input]
3

8 7

4 3 2 2 1 0 1

3 3 3 2 1 0 1

2 2 2 2 1 0 0

2 1 1 1 1 0 0

1 1 0 0 0 1 0

0 0 0 1 1 1 0

0 1 2 2 1 1 0

0 1 1 1 2 1 0

8 7

4 3 2 2 1 1 1

3 3 3 2 1 0 1

2 2 2 2 1 0 0

2 1 1 1 1 0 0

1 1 0 0 0 1 0

0 0 0 1 1 1 0

0 1 2 2 1 1 0

0 1 1 1 2 1 0

8 7

4 3 2 2 1 1 1

3 3 3 2 1 0 1

2 2 2 2 1 0 0

2 1 1 2 1 0 0

1 1 2 2 0 1 0

0 0 0 2 1 1 0

0 1 2 2 1 1 0

0 1 1 1 2 1 0

 
[Output]
#1 3
#2 2
#3 1

*/

#include <iostream>
#include <stdio.h>

#define MAX 701

using namespace std;

int T;
int n, m;
int a[MAX][MAX];	//a là input của bản đồ, cũng là chiều cao của từng ô đất
int visited[MAX][MAX];
int moveX[] = {0,0,-1,1,-1,-1,1,1};
int moveY[] = {-1,1,0,0,-1,1,-1,1};
int numOfHill;

struct Point {
	int x,y;
};

//bài này thực chất dùng stack, vì queue trong bài này toàn deQueue từ phía rear
Point myQueue[1000000];
int front, rear;
void initQueue() {
	front = rear = -1;
}

void enQueue(int a, int b) {
	Point p;
	p.x = a; p.y = b;
	rear++;
	myQueue[rear] = p;
}

Point deQueue() {
	front++;
	Point temp = myQueue[front];
	if(front==rear) front=rear=-1;
	return temp;
}

Point deQueueFromRear() {
	Point temp = myQueue[rear];
	rear--;
	if(front==rear) front=rear=-1;
	return temp;
}

Point getFront() {
	return myQueue[front];
}

Point getRear() {
	return myQueue[rear];
}

bool isQueueEmpty() {
	return front==-1 && rear==-1;
}

void printQueue() {
	printf("print queue\n");
	for(int i=front+1; i<=rear; i++) {
		Point p = myQueue[i];
		printf("%d,%d  ",p.x, p.y);
	}
}

void input() {
	cin >> n >> m;
	numOfHill = 0;

	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			cin >> a[i][j];
			visited[i][j] = 0;
		}
	}
}

bool checkExistCell(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > m) return false;
	return true;
}

void baoVeNongTrang() {
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(visited[i][j] == 1) continue;

			visited[i][j] = 1;
			initQueue();
			
			//cho điểm đang xét vào queue
			enQueue(i, j);
			
			//giả sử điểm đang xét là đỉnh đồi
			bool isHill = true;

			while(!isQueueEmpty()) {
				Point pRear = deQueueFromRear();

				//xét 8 hàng xóm xq điểm rear
				for(int k=0; k<8; k++) {
					int xNeigh = pRear.x + moveX[k];
					int yNeigh = pRear.y + moveY[k];
					
					if(!checkExistCell(xNeigh, yNeigh)) continue;

					//nếu đỉnh hàng xóm này chưa thăm thì check như sau:
					if(visited[xNeigh][yNeigh] == 0 && a[xNeigh][yNeigh] == a[pRear.x][pRear.y]) {
						enQueue(xNeigh, yNeigh);
						visited[xNeigh][yNeigh] = 1;
					}
					
					//dù đỉnh hàng xóm này chưa thăm hay đã thăm rồi thì vẫn phải check như sau:
					if(a[xNeigh][yNeigh] > a[pRear.x][pRear.y]) {
						isHill = false;
					}
				}
			}

			if(isHill) {
				numOfHill++;
			}
		}
	}
}

int main() {
	freopen("BaoVeNongTrang_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		baoVeNongTrang();
		cout << "#" << tc << " ";
		cout << numOfHill << endl;
	}
}