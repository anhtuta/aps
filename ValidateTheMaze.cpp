/*
Validate the maze
There are many algorithms to generate maze. After generating the 
maze we’ve to validate whether it’s a valid maze or not. A valid 
maze has exactly one entry point and exactly one exit point
(exactly 2 openings in the edges) and there must be atleast one
path from the entry point to exit point.
Given a maze, just find whether the maze is "valid" or "invalid".

Input
The first line consists of an integer t, the number of test cases. 
Then for each test case, the first line consists of two integers 
m and n, the number of rows and columns in the maze. Then contains 
the description of the matrix M of order mxn. M[i][j] = # represents
a wall and M[i][j] = '.' represents a space.

Output
For each test case find whether the maze is "valid" or "invalid".

Constraints
1 <= t< = 10000
1 <= m< = 20
1 <= n< = 20

Sample
Input
6
4 4

####

#...

#.##

#.##

5 5

#.###

#..##

##..#

#.#.#

###.#

1 1

.

5 1

#

#

.

.

#

2 2

#.

.#

3 4

#..#

#.##

#.##

 

Output

valid

valid

invalid

valid

invalid

invalid

Cách làm: khi đọc data, check xem có bao nhiêu cổng, nếu số cổng != 2
thì return invalid luôn. Nếu có đúng 2 cổng thì BFS từ 1 cổng, nếu tới
đc cổng khi thì return valid
Có thể DFS, nhưng BFS có vẻ nhanh hơn
*/
#include <iostream>
#include <stdio.h>

#define MAX 21

using namespace std;

int T;
int m, n;
char a[MAX][MAX];
int startX,startY,endX,endY;	//tọa độ 2 cổng của mê cung
int visited[MAX][MAX];
int numOfGate;
int moveX[] = {0,0,-1,1};
int moveY[] = {-1,1,0,0};

void xuongDong() {
	cout<<endl;
}
struct Point {
	int x,y;
};
Point myQueue[100000];
int front, rear;
void initQueue() {
	front=rear=-1;
}
void enQueue(int startX, int startY) {
	Point p;
	p.x = startX; p.y = startY;
	rear++;
	myQueue[rear] = p;
}
Point deQueue() {
	front++;
	Point temp = myQueue[front];
	if(front == rear) front=rear=-1;
	return temp;
}

bool input() {
	cin >> m >> n;
	numOfGate = 0;
	bool isValid = true;

	for(int i=1; i<=m; i++) {
		for(int j=1; j<=n; j++) {
			cin >> a[i][j];
			if((i==1 || i==m || j==1 || j==n) && a[i][j]=='.') {
				numOfGate++;
				if(numOfGate > 2) isValid = false;
				else if(numOfGate == 1) {
					startX = i; startY = j;
				} else {
					endX = i; endY = j;
				}
			}
			visited[i][j] = 0;
		}
	}

	if(!isValid) return false;
	if(numOfGate < 2) return false;
	return true;
}
bool isQueueEmpty() {
	return front==-1 && rear==-1;
}

bool checkValidCell(int x, int y) {
	if(x < 1 || x > m || y < 1 || y > n) return false;
	if(a[x][y] == '#') return false;
	if(visited[x][y] != 0) return false;
	return true;
}

//BFS từ cổng (startX,startY), để xem nó có đi ra đc cổng (endX,endY) hay ko 
bool validateTheMaze() {
	initQueue();
	enQueue(startX, startY);
	visited[startX][startY] = 1;
	int xNeigh, yNeigh;

	while(!isQueueEmpty()) {
		Point p = deQueue();

		for(int i = 0; i < 4; i++) {
			xNeigh = p.x + moveX[i];
			yNeigh = p.y + moveY[i];

			if(checkValidCell(xNeigh, yNeigh)) {
				visited[xNeigh][yNeigh] = 1;
				enQueue(xNeigh, yNeigh);
			}
		}
	}

	return visited[endX][endY]==1;
}

int main() {
	freopen("ValidateTheMaze_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		if(input()) {
			if(validateTheMaze())
				cout << "valid" << endl;
			else
				cout << "invalid" << endl;
		} else {
			cout << "invalid" << endl;
		}
	}
}

/*
input: xem file ValidateTheMaze_input.txt

output:
valid
valid
invalid
valid
invalid
invalid
valid
valid
valid
invalid
invalid
valid
invalid
invalid
valid
invalid
valid
valid
invalid
valid

*/