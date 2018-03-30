/*
Crazy King
King Peter lives in kingdom A, and his daughter in kingdom B. 
King received a letter telling that her daughter gave birth to a 
child. King is incredibly curious to see his grandchild! Unfortunately 
that’s not gonna be that easy. 
Kingdoms A and B are separated by a forest. There are lots of 
enemies in the forest, and King is not that curious to see them. 
If they attack king on his way to kingdom B, then he will never ever 
see his grandchild and daughter again because of lethal consequences.

Security Council of the King disposes information about location of 
the enemies, which makes the things easier for king. For some unknown 
reason a forest is MxN chessboard. (N is the number of rows, and M is 
the number of columns). N,M <=100 are positive integers.

Enemies of the King can ride horses as showed in the picture. 
Usually horses ride (or jump) that way in Chess. Unfortunately 
king can’t take an airplane from point A to point B because it 
is not invented yet. So he moves the same way as chess-king does 


King can’t move to a square X, if a horse of the enemy is on 
that square. While the king is moving horses are not, but if 
at least one horse can reach square X in one move, then king 
can't move to that square (except for the case when square X 
is either kingdom A or B).

You are the chief of Electronic Intelligence department of kingdom A 
(by the way the computers are already invented). And you’re asked to 
find the length of the shortest route L from kingdom A to B, as king 
can’t wait any longer.

Input

The first line of input contains the number of tests T <=100. 
The first line of each test contains 2 numbers M and N. Then M 
lines follow each containing N symbols from the set 
S = { ‘.’, ‘Z’, ‘A’, ‘B’}. ‘.’ means that square is not occupied. 
‘Z’ - horse occupies that square. ‘A’ - kingdom A, ‘B’ - kingdom B. 
Each test contains exactly one kingdom A and B.

Output

Find number L for each test and print line L if King can reach 
kingdom B. Replace L with corresponding number. If King can’t 
safely reach the kingdom B print line -1.

Sample

Input
1 		//số lượng testcase
6 8		//m=6, n=8. bàn cờ kích thước n*m
.A....	//bắt đầu nhập data của bàn cờ
......
B.....
......
......
.Z....
.Z.Z..
..Z.Z.

Output
2

có 2 vương quốc A và B, vua ở vương quốc A, cần đi tới B,
ngựa của địch ở các vị trí Z. nếu vua đi phải vị trí này hoặc 
các vị trí mà ngựa có thể mai phục (vị trí mà ngựa có thể
nhảy tới đó = 1 nước, nhảy giống trong cờ vua) thì vua sẽ chết

in ra số bước đi ít nhất của vua, nếu ko tới đc in ra -1
(vua đi giống quân tướng trong cờ vua)
*/

#include <iostream>
#include <stdio.h>

#define MAX 201

using namespace std;

int T;
int n, m;	//n = số hàng, m = số cột
char a[MAX][MAX];
int visited[MAX][MAX];
int horseMoveX[] = {-1,-2,-2,-1,1,2, 2, 1};
int horseMoveY[] = {-2,-1, 1, 2,2,1,-1,-2};
int kingMoveX[] = {0,0,-1,1,-1,-1,1,1};
int kingMoveY[] = {-1,1,0,0,-1,1,-1,1};
int A_x, A_y, B_x, B_y;		//tọa độ của vương quốc A và B

void xuongDong() {
	cout<<endl;
}

struct Point {
	int x,y;
};
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
bool isQueueEmpty() {
	return front==-1 && rear==-1;
}

bool checkExistCell(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > m) return false;	//out of bound
	return true;
}

bool isDangerousPlace(int x, int y) {
	return a[x][y] == 'Z' || a[x][y] == 'X';
}

void input() {
	//CHÚ Ý: ĐỀ BÀI YÊU CẦU NHẬP m TRƯỚC
	cin >> m >> n;
	int xNeigh, yNeigh;
	
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			cin >> a[i][j];
			visited[i][j] = 0;
			if(a[i][j] == 'A') {A_x = i; A_y = j;}
			if(a[i][j] == 'B') {B_x = i; B_y = j;}
		}
	}
	
	//init enemy: Do nhà vua ko đi đc tới các ô có quân mã (các ô mà a[][] = 'Z')
	//và 8 ô xung quanh mà ô 'Z' có thể đi tới, nên ta thiết lập 8 ô xq đó có
	//giá trị a[][] = 'X' luôn.
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(a[i][j] == 'Z') {
				for(int k=0; k<8; k++) {
					xNeigh = i + horseMoveX[k];
					yNeigh = j + horseMoveY[k];
					if(checkExistCell(xNeigh, yNeigh)) {
						if(a[xNeigh][yNeigh] == '.') {
							a[xNeigh][yNeigh] = 'X';
						}
					}
				}
			}
		}
	}

	/*for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			cout << a[i][j] << " ";
		}
		xuongDong();
	}
	xuongDong();
	cout << "finish print a[]\n";*/
	//printf("start = (%d, %d), end = (%d, %d)\n", A_x, A_y, B_x, B_y);
}

void printVisited() {
	printf("print visited....\n");
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			printf("%d ",visited[i][j]);
		}
		xuongDong();
	}
	xuongDong();
}

void crazyKing() {
	initQueue();
	enQueue(A_x, A_y);
	visited[A_x][A_y] = 1;
	int xNeigh, yNeigh;

	while(!isQueueEmpty()) {
		Point pRear = deQueue();
		if(pRear.x == B_x && pRear.y == B_y) break;

		//cho nhà vua lan ra 8 hướng
		for(int i=0; i<8; i++) {
			xNeigh = pRear.x + kingMoveX[i];
			yNeigh = pRear.y + kingMoveY[i];

			if(checkExistCell(xNeigh, yNeigh) && !isDangerousPlace(xNeigh, yNeigh) && visited[xNeigh][yNeigh] == 0) {
				visited[xNeigh][yNeigh] = visited[pRear.x][pRear.y] + 1;
				enQueue(xNeigh, yNeigh);
			}
		}
		//printVisited();
	}
}

int main() {
	freopen("CrazyKing_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		crazyKing();
		cout << visited[B_x][B_y] - 1 << endl;
		//printVisited();
	}
}

/*
input: xem file CrazyKing_input.txt

output:

1
4
1
2
3
2
2
2
-1
-1
-1
-1
-1
-1
-1
-1
-1
-1
-1
-1

*/