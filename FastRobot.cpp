/*
Fast robot
Mr. Noh is responsible for enhancing the movement of a robot faster. 
Now, Mr. Noh is thinking like this: The speed of the robot decreases when it changes its direction. 
Therefore, it requires a study of the acceleration in direction changes. 
However, the better method than that is to use the route with the minimum number of direction changes when it moves from point A to point B.


Because of that, he studies a maze. 
When the maze information is given, he tries to create a program to move it from the starting point to the arriving point based on the minimized direction changes.


Let’s find out the minimum direction changes possible from the starting point to the arriving point when the maze information is given.


Time limit : 1 sec (Java : 2 sec)


[Input]
There can be more than one test case in the input file. The first line has T, the number of test cases. 
Then the totally T test cases are provided in the following lines (T ≤ 10 )
In each test case, The width and height of the maze are given as N & M separately at the first row. (1 ≤ N, M ≤ 200)
The horizontal coordinate and vertical coordinate of the starting point, and the horizontal coordinate and vertical coordinate of the arriving point are given separately in order at the second row. 
Information of the maze is given from the third row the number (N). At this time, the path indicates 0; the wall indicates 1. There is no blank each other.


[Output]
In case of being reachable from the starting point to the arriving point, generate the minimum direction change frequency between two points. 
If not, generate "-1"

[I/O Example]

Input

2
7 7
1 2 7 5
1111111
0000011
1011001
1011100
1011110
1000000
1111111
7 7
1 2 7 6
1111111
0000001
1011000
1011100
1011110
1000000
1111111


Output

3

2
*/

/*
bài này chú ý: cái mê cung đọc như thường
N, M, tọa đọ điểm đầu và cuối phải đọc ngược thứ tự:
cin >> m >> n;	//n = số hàng, m = số cột
cin >> startY >> startX >> endY >> endX;

Cách làm: tại mỗi ô, ta loang ra 4 phía, loang tới khi gặp tường hoặc quá kích
thước của mê cung thì dừng (nghĩa là tại mỗi ô, ta đi 1 mạch tới hết đường, tới khi gặp
tường hoặc hết đường thì duyệt sang ô tiếp theo)
Chú ý: nếu tại 1 ô, loang ra 4 hướng mà gặp 1 ô đã thăm rồi thì ta cứ đi qua
ô đó chứ ko đc break (nhưng ko cho ô đó vào queue)
*/

#include <iostream>
#include <stdio.h>

#define MAX 201
#define WALL '1'


using namespace std;

int T;
int n, m;
char a[MAX][MAX];
int startX, startY, endX, endY;
int moveY[] = {0,0,-1,1};
int moveX[] = {-1,1,0,0};	//4 hướng đi lần lượt là: trái, phải, lên, xuống
int cost[MAX][MAX];		//chi phí để đi đến từng ô

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
	cin >> m >> n;	//n = số hàng, m = số cột
	cin >> startY >> startX >> endY >> endX;

	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			cin >> a[i][j];
			cost[i][j] = -1;
		}
	}
}

bool checkValidCell(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > m) return false;
	if(a[x][y] == WALL) return false;
	return true;
}

void printCost() {
	cout << "print cost...\n";
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			printf("%2d ", cost[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

bool checkIfAllCellsVisited() {
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(cost[i][j] == -1) return false;
		}
	}
	return true;
}

void fastRobot() {
	Point startPosition;
	startPosition.x = startX;
	startPosition.y = startY;
	enQueue(startPosition);
	cost[startX][startY] = 0;
	int nextX, nextY;

	while(!isQueueEmpty()) {
		Point currPos = deQueue();	//current position
		int currX, currY;
		
		//loang ra 4 hướng xung quanh, loang cho tới khi gặp tường
		//hoặc quá kích thước của mê cung thì dừng, chứ ko phải
		//loang từng ô
		for(int i=0; i<4; i++) {
			currX = currPos.x;
			currY = currPos.y;
			while(1) {
				nextX = currX + moveX[i];
				nextY = currY + moveY[i];

				if(!checkValidCell(nextX, nextY)) break;

				if(cost[nextX][nextY] == -1) {
					cost[nextX][nextY] = cost[currPos.x][currPos.y] + 1;
					Point p2;
					p2.x = nextX; p2.y = nextY;
					enQueue(p2);
				} else {
					//Nếu gặp ô mà cost[nextX][nextY] != -1 thì chứng tỏ
					//ô này đã được thăm rồi. ta vẫn tiếp tục đi tiếp chứ ko đc break.
					//chỉ có điều là ko cho ô này vào queue
					//Do đó trong này ko làm j cả
				}
				currX = nextX; currY = nextY;
			}
		}

	}
}

int main() {
	freopen("FastRobot_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		fastRobot();
		if(cost[endX][endY] != -1) {
			cout << cost[endX][endY]-1 << endl;
		} else {
			//ko tìm đc đường tới đích
			cout << "-1\n";
		}
		//printCost();
	}
}
/*
output:
4
8
7
10
265
3
1
2
-1
10

*/