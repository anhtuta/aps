/*
Ice Cave - level 3
You play a computer game. Your character stands on some level 
of a multilevel ice cave. In order to move on forward, you need 
to descend one level lower and the only way to do this is to fall 
through the ice.

The level of the cave where you are is a rectangular square grid 
of n rows and m columns. Each cell consists either from intact 
or from cracked ice. From each cell you can move to cells that 
are side-adjacent with yours (due to some limitations of the game 
engine you cannot make jumps on the same place, i.e. jump from a 
cell to itself). If you move to the cell with cracked ice, then 
your character falls down through it and if you move to the cell 
with intact ice, then the ice on this cell becomes cracked.

Let's number the rows with integers from 0 to n-1 from top to 
bottom and the columns with integers from 0 to m-1 from left to 
right. Let's denote a cell on the intersection of the (r-1)-th 
row and the    (c-1)-th column.

You are staying in the cell (r1, c1) and this cell is cracked 
because you've just fallen here from a higher level. You need 
to fall down through the cell (r2, c2) since the exit to the 
next level is there. Can you do this?

  

[Input]

The first line contains two integers, n and m (1 ≤ n, m ≤ 500) — 
the number of rows and columns in the cave description. Then, r1 
and c1 (0≤ r1 < n, 0 ≤ c1 < m) — your initial coordinates. It is 
guaranteed that the description of the cave contains character '0' 
in cell (r1, c1), that is, the ice on the starting cell is initially 
cracked. The next two integers r2 and c2 (0 ≤ r2 < n, 0 ≤ c2 < m) — the 
coordinates of the cell through which you need to fall. The 
final cell may coincide with the starting one.

Each of the next n lines describes the initial state of the level 
of the cave, each line consists of m characters "1" (that is, 
intact ice) and "X" (cracked ice).

The next line contains two integers, r1 and c1 (0≤ r1 < n, 0 ≤ c1 < m) — your initial coordinates. 
It is guaranteed that the description of the cave contains 
character '0' in cell (r1, c1), that is, the ice on the starting 
cell is initially cracked.

The next line contains two integers r2 and c2 (0 ≤ r2 ≤<n, 0 ≤ c2 < m) — the coordinates 
of the cell through which you need to fall. The final cell may coincide with the starting one.

 

[Output]

If you can reach the destination, print 'YES', otherwise print 'NO'.

 

[Sample]

[Input]

2

4 6 0 5 1 1 	//bản đồ có 4 hàng, 6 cột. người chơi ở vị trí bắt đầu = (0,5). đích = (1,1)

0 1 1 1 0 0

1 1 1 0 0 1

1 0 1 1 0 1

1 1 1 1 1 1

5 4 4 2 0 0

1 0 1 1

1 1 1 0

0 1 0 1

1 1 1 1

1 0 0 1

[Output]

YES

NO


0: cracked ice: băng mềm
1: intact ice: băng cứng
vị trí ban đầu luôn là băng mềm. nếu người chơi đi tới vị trí băng cứng thì sau đó
vị trí đó sẽ chuyển thành băng mềm. Nếu người chơi đi tới vị trí băng mềm
thì sẽ rơi mà thua cuộc, trừ trường hợp vị trí đó là đích
Nhiệm vụ: kiểm tra xem người chơi có đi tới đích và rơi xuống đc ko.
nếu ô đích là 1 thì khi tới đích, người chơi phải nhảy sang ô khác, sau đó quay
lại để còn rơi xuống. Nếu ô đích = 0 thì khi tới đích là xong luôn!

*/
#include <iostream>
#include <stdio.h>

#define MAX 501

using namespace std;

int T;
int n,m;
int a[MAX][MAX];
int visited[MAX][MAX];
int r1,c1,r2,c2;
int moveY[] = {0,0,-1,1};
int moveX[] = {-1,1,0,0};

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
void enQueue(int i, int j) {
	Point p;
	p.x = i; p.y = j;
	rear++;
	myQueue[rear] = p;
}
Point deQueue() {
	front++;
	Point p = myQueue[front];
	if(front==rear) front=rear=-1;
	return p;
}
bool isQueueEmpty() {
	return front==-1 && rear==-1;
}

void input() {
	cin >> n >> m >>r1>>c1>>r2>>c2;
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			cin>>a[i][j];
			visited[i][j] = 0;
		}
	}
}

bool checkExistCell(int x, int y) {
	if(x < 0 || x >= n || y < 0 || y >= m) return false;	//out of bound exception!
	if(x==r2 && y==c2) return true;
	if(a[x][y] == 0) return false;		//cracked ice, can't go here
	if(visited[x][y] != 0) return false;	//this cell is visited, can't go here again
	return true;
}

void printVisited() {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			printf("%2d ", visited[i][j]);
		}
		xuongDong();
	}
	xuongDong();
}

//BFS tại điểm bắt đầu (r1, c1), tới điểm đích (r2,c2) thì stop
bool iceCave() {
	initQueue();
	visited[r1][c1] = 1;
	enQueue(r1, c1);
	int xNeigh, yNeigh;

	while(!isQueueEmpty()) {
		Point p = deQueue();
		if(p.x == r2 && p.y == c2) break;

		for(int i=0; i<4; i++) {
			xNeigh = p.x + moveX[i];
			yNeigh = p.y + moveY[i];

			if(checkExistCell(xNeigh, yNeigh)) {
				visited[xNeigh][yNeigh] = visited[p.x][p.y] + 1;
				enQueue(xNeigh, yNeigh);
			}
		}
	}

	//printVisited();

	if(visited[r2][c2] == 0) return false;
	
	if(a[r2][c2] == 0) {
		for(int i=0; i<4; i++) {
			xNeigh = r2 + moveX[i];
			yNeigh = c2 + moveY[i];

			//Nếu ô đích là ô 0, và xung quanh nó có 1 ô A mà
			//tồn tại đường đi từ điểm xuất phát đến ô A thì return true
			if(xNeigh >= 0 && xNeigh < n && yNeigh >= 0 && yNeigh < m &&
				visited[xNeigh][yNeigh] != 0) {
					return true;
			}
		}
		return false;
	} else {
		//nếu ô đích là 1 thì phải tồn tại ít nhất 2 ô quanh nó = 1
		int soLuongCellXungQuanhBangMot = 0;
		for(int i=0; i<4; i++) {
			xNeigh = r2 + moveX[i];
			yNeigh = c2 + moveY[i];

			if(xNeigh >= 0 && xNeigh < n && yNeigh >= 0 && yNeigh < m &&
				a[xNeigh][yNeigh] == 1) soLuongCellXungQuanhBangMot++;

			if(soLuongCellXungQuanhBangMot >= 2) {
				return true;
			}
		}
		return false;
	}
	return false;
}

int main() {
	freopen("IceCave_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		if(iceCave())
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}