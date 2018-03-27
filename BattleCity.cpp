/*
Battle City
Many of us had played the game "Battle city" in our childhood, and some 
people (like me) even often play it on computer now. 

What we are discussing is a simple edition of this game. Given a map that
consists of empty spaces, rivers, steel walls and brick walls only. Your 
task is to get a bonus as soon as possible suppose that no enemies will 
disturb you (See the following picture). 

 



﻿

 

Your tank can't move through rivers or walls, but it can destroy brick walls 
by shooting. A brick wall will be turned into empty spaces when you hit 
it, however, if your shot hit a steel wall, there will be no damage to the 
wall. In each of your turns, you can choose to move to a neighboring 
(4 directions, not 8) empty space, or shoot in one of the four directions 
without a move. The shot will go ahead in that direction, until it go out 
of the map or hit a wall. If the shot hits a brick wall, the wall will 
disappear (i.e., in this turn). Well, given the description of a map, 
the positions of your tank and the target, how many turns will you take 
at least to arrive there?  

Input

﻿ There can be more than one test case in the input. The first line has T, 
the number of test cases. 
Then the totally T test cases are provided in the following lines (T<=10). 
The first line of each test case contains two integers M and N (2 <= M, N< = 300).
Each of the following M lines contains N uppercase letters, each of which is 
one of 'Y' (you), 'T' (target), 'S' (steel wall), 'B' (brick wall), 'R' (river) 
and 'E' (empty space). Both 'Y' and 'T' appear only once. 

Output

For each test case, please output the turns you take at least in a separate 
line. If you can't arrive at the target, output "-1" instead.


Sample
Input
1
3 4
YBEB
EERE
SSTE
 
Output
Case #1
8
*/

/*
Đề bài: cho bản đồ giống trò chơi bắn tank, trên bản, mỗi ô là
1 trong 6 loại: vị trí của bạn (YOU), đích (TARGET), tường thép, tường gạch, sông
và empty space. Chỉ có 1 vị trí của bạn và 1 vị trí đích.
mỗi lần đi xe tank chỉ đi 1 bước từ ô này sang ô khác với chi phí = 1.
nếu gặp tường gạch thì nó mất 1 chi phí để bắn, sau đó 1 chi phí để đi tới.
tank ko thể đi qua sông hoặc tường thép.

tính số bước đi ngắn nhất từ vị trí bắt đầu tới đích.

sample input:
1		//số test case
3 4		//kích thước của bản đồ (m=3, n=4, tương ứng là số hàng và cột) (2<=m,n<=300)
YBEB	//hàng đầu tiên của bản đồ. ý nghĩa các kí hiệu: xem #define ở dưới
EERE
SSTE

Cách làm: loang từ 1 ô ra 4 hướng, kiểu BFS
*/

#include <iostream>
#include <stdio.h>

#define MAX 302

#define YOU 'Y'
#define TARGET 'T'
#define STEEL_WALL 'S'
#define BRICK_WALL 'B'
#define RIVER 'R'
#define EMPTY_SPACE 'E'

using namespace std;

int T;
int n, m;
char a[MAX][MAX];
int startX, startY, endX, endY;
int moveX[] = {0,0,-1,1};
int moveY[] = {-1,1,0,0};	//4 hướng đi lần lượt là: trái, phải, lên, xuống
int turn[MAX][MAX];		//chi phí (số lượt) để đi đến từng ô

struct Point {
	int x,y;
};

Point myQueue[1000000];
int front, rear;
void initQueue() {
	front = rear = -1;
}

void enQueue(Point p) {
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

void input() {
	cin >> m >> n;	//m = số hàng, n = số cột

	for(int i=1; i<=m; i++) {
		for(int j=1; j<=n; j++) {
			cin >> a[i][j];
			turn[i][j] = -1;
			if(a[i][j] == YOU) {
				startX = i; startY = j;
			} else if(a[i][j] == TARGET) {
				endX = i; endY = j;
			}
		}
	}
}

bool checkExistCell(int x, int y) {
	//printf("checking...: x = %d, y = %d\n", x, y);
	if(x < 1 || x > m || y < 1 || y > n) return false;
	//if(turn[x][y] != -1) return false;		//ô này đã đc thăm rồi, nhưng vẫn phải thăm lại để update turn
	if(a[x][y] == STEEL_WALL || a[x][y] == RIVER) return false;
	return true;
}

void printTurn() {
	cout << "print turn...\n";
	for(int i=1; i<=m; i++) {
		for(int j=1; j<=n; j++) {
			printf("%2d ", turn[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

int min(int a, int b) {
	return a<b?a:b;
}

void battleCity() {
	Point startPosition;
	startPosition.x = startX;
	startPosition.y = startY;
	enQueue(startPosition);
	turn[startX][startY] = 0;
	int nextX, nextY;
	//printf("startX = %d, startY = %d, endX = %d, endY = %d\n", startX, startY, endX, endY);

	while(!isQueueEmpty()) {
		Point currPos = deQueue();	//current position
		int currX, currY, nextX, nextY;
		currX = currPos.x;
		currY = currPos.y;
		//if(currX == endX && currY == endY) {
		if(a[currX][currY] == TARGET) {
			//KHÔNG ĐƯỢC BREAK, VÌ CẦN DUYỆT TIẾP ĐỂ TÌM ĐƯỜNG ĐI TỐI ƯU
			//PHẢI DUYỆT TỚI KHI QUEUE RỖNG MỚI STOP
			//cout << "kq = " << turn[currX][currY] << endl;
			//break;
		}
		
		//printTurn();

		//loang ra 4 hướng xung quanh
		for(int i=0; i<4; i++) {
			nextX = currX + moveX[i];
			nextY = currY + moveY[i];
			if(checkExistCell(nextX, nextY)) {
				if(a[nextX][nextY] == BRICK_WALL && 
						(turn[nextX][nextY] == -1 || turn[nextX][nextY] > (turn[currX][currY] + 2))) {
					turn[nextX][nextY] = turn[currX][currY] + 2;
					Point p2;
					p2.x = nextX; p2.y = nextY;
					enQueue(p2);
				} else if((a[nextX][nextY] == EMPTY_SPACE || a[nextX][nextY] == TARGET) && 
						(turn[nextX][nextY] == -1 || turn[nextX][nextY] > (turn[currX][currY] + 1))) {
					turn[nextX][nextY] = turn[currX][currY] + 1;
					Point p2;
					p2.x = nextX; p2.y = nextY;
					enQueue(p2);
				}
			}
		}
	}
}

int main() {
	freopen("BattleCity_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		initQueue();
		battleCity();
		cout << "Case #" << tc << endl;
		if(turn[endX][endY] != -1) {
			cout << turn[endX][endY] << endl;
		} else {
			//ko tìm đc đường tới đích
			cout << "-1\n";
		}
		//printTurn();
	}
}

/*
output:
8
-1
5
5
13
29
-1
-1
228
598

*/