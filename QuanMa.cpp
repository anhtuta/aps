/*
Quân mã

Trong một bàn cờ NxM.
Tìm số lần đi tối thiểu để quân mã ăn hết quân địch.
Quân mã có thể di chuyển xung quanh theo 8 hướng .

Input : 
dòng đầu tiên là số lương test case
Dòng 2 là kích thước của bàn cờ
Tiếp theo là bàn cờ :
3 là vị trí xuất phát của quân mã
1 là vị trí quân địch
0 là vị trí trống.
Quân mã có thể di chuyển trên tất cả các vị trí trên bàn cờ (0,1,3).

Output:
In ra số lần di chuyển nhỏ nhất để quân mã ăn hết quân địch.

Sample input:
2
10 10
1 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0
0 1 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 3 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 1
5 7
0 0 0 0 0 0 0
0 3 0 0 0 0 0
0 0 0 1 0 0 0
0 0 0 0 0 1 0
0 0 0 1 0 0 0

output:
Case #1
12
Case #2
3

Cách làm: coi quân mã và các kẻ địch, mỗi thằng là 1 node. Đầu tiên 
tìm khoảng cách giữa 2 node bất kỳ, tìm tất cả nhé. VD: có 6 node 
thì cần tìm 15 khoảng cách. Sau khi tìm xong, ta sẽ quay lui để tìm
thứ tự ăn quân địch của con mã dựa vào khoảng cách vừa tìm đó.
 */
#include <iostream>
#include <stdio.h>

#define MAX 201
#define INF 999999

using namespace std;

/*
Đầu tiên BFS từ tất cả các điểm để tìm khoảng cách giữa 2 điểm bất kỳ.
Sau đó quay lui để tìm đường đi ngắn nhất
*/
struct Point {
	int x, y;
};

int T;
int n,m;
int a[MAX][MAX];	//dữ liệu bàn cờ
int visited[MAX][MAX];
int edges[MAX][MAX];	//Lưu độ dài giữa 2 quân địch bất kỳ, theo danh sách kề.
//chú ý: chiều dài và rộng của mảng edges là như nhau, và edges[3][2] là khoảng cách
//ngắn nhất giữa 2 quân địch 3 và 2. quân địch 3 có tọa độ do ta tự quy ước
//có thể để quân địch đầu tiên chính là vị trí con mã xuất phát: edges[1][...]
//vậy edges[1][k] = khoảng cách từ mã tới quân địch k
//nếu số lượng đỉnh là k thì kích thước mảng này = k(k+1)/2

Point vertices[MAX];		//Các đỉnh của đồ thị. mỗi đỉnh chính là các ô có quân địch hoặc con mã
//mặc định: vertexs[1] = vị trí con mã lúc đầu
//vậy: chiều dài edges[3][4] là độ dài cạnh nối 2 đỉnh 3 và 4. tọa độ các đỉnh 3,4 là vertices[3] và vertices[4]

int moveX[] = {-1,-2,-2,-1,1,2, 2, 1};
int moveY[] = {-2,-1, 1, 2,2,1,-1,-2};	//các vị trí xq của con mã
int numOfEnemies;
int kq;		//tổng số bước đi cần tìm
int currCost, minCost;

int mark[MAX];	//mảng đánh dấu quân địch đã ăn, dùng trong quay lui
int res[MAX];	//mảng kq thứ tự ăn quân địch, dùng trong quay lui

struct Point myQueue[100000];
int front,rear;
void initQueue() {
	front = rear = -1;
}
void enQueue(int x1, int y1) {
	Point p;
	p.x = x1; p.y = y1;
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

void xuongDong() {
	cout<<endl;
}

void initVisited() {
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			visited[i][j] = -1;
		}
	}
}

void input() {
	cin >> n >> m;
	numOfEnemies = 0;
	currCost = 0;
	minCost = INF;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			cin >> a[i][j];
			if(a[i][j] == 1) {
				numOfEnemies++;
				Point p;
				p.x = i; p.y = j;
				vertices[numOfEnemies + 1] = p;		//quân địch đầu tiên sẽ có chỉ số = 2
			} else if(a[i][j] == 3) {
				Point p;
				p.x = i; p.y = j;
				vertices[1] = p;	//đỉnh đầu tiên là vị trí bắt đầu của con mã
			}
		}
	}
	initVisited();
}

void printVisited() {
	printf("Print visited...\n");
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			printf("%d ", visited[i][j]);
		}
		xuongDong();
	}
	xuongDong();
}

bool checkValidCell(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > m) return false;
	if(visited[x][y]!=-1) return false;
	return true;
}

//BFS từ đỉnh (x,y)
void BFS(int x, int y) {
	int xNeigh, yNeigh;
	initQueue();
	enQueue(x,y);
	initVisited();
	visited[x][y] = 0;		//(x,y) chính là điểm bắt đầu

	while(!isQueueEmpty()) {
		Point p = deQueue();

		for(int i=0; i<8; i++) {
			xNeigh = p.x + moveX[i];
			yNeigh = p.y + moveY[i];

			if(checkValidCell(xNeigh, yNeigh)) {
				visited[xNeigh][yNeigh] = visited[p.x][p.y] + 1;
				enQueue(xNeigh, yNeigh);
			}
		}
	}
}

//cho con mã đi ăn quân địch thứ k. Chú ý: quân địch bắt đầu từ chỉ số 2, vì chỉ
//số 1 là vị trí con mã lúc bắt đầu rồi
//chú ý: số lượng quân cờ = numOfEnemies + 1, trong đó có 1 quân mã và numOfEnemies quân địch
void backtrack(int k) {
	if (k > numOfEnemies + 1) {
		if (minCost > currCost) minCost = currCost;
		return;
	}
	for (int i = 2; i <= numOfEnemies + 1; i++) {
		if (mark[i] == 0) {
			res[k] = i;
			mark[i] = 1;
			currCost += edges[res[k - 1]][res[k]];
			backtrack(k + 1);
			currCost -= edges[res[k - 1]][res[k]];
			res[k] = 0;
			mark[i] = 0;
		}
	}
}
void horseEatsAllEmemies() {
	for (int i = 1; i <= numOfEnemies + 1; i++) {
		BFS(vertices[i].x, vertices[i].y);
		for (int j = 1; j <= numOfEnemies; j++) {
			if (i != j) {
				edges[i][j] = edges[j][i] = visited[vertices[j].x][vertices[j].y];
				//cạnh i,j nối đỉnh i và j. do ta BFS từ đỉnh i nên độ dài cạnh này
				//chính là thời gian thăm đỉnh j = visited[j.x][j.y]
			}
		}
	}

	res[1] = 1;		//điểm đầu tiên là điểm 1
	mark[1] = 1;	//đánh dấu điểm 1 đã đc thăm
 	backtrack(2);	//bắt đầu tìm điểm thứ 2
}

void printEdgesFromVertex(int v) {
	for (int i = 1; i <= numOfEnemies + 1; i++) {
		if (i != v) printf("(%d, %d) = %d\n", v, i, edges[v][i]);
	}
}

void printAllEdges() {
	for (int i = 1; i <= numOfEnemies + 1; i++) {
		for (int j = 1; j <= numOfEnemies + 1; j++)
			if (i != j) printf("(%d, %d) = %d\n", i, j, edges[i][j]);
		xuongDong();
	}
	xuongDong();
}



int main() {
	freopen("QuanMa_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		horseEatsAllEmemies();
		//printAllEdges();
		cout << "Case #" << tc << endl;
		cout << minCost << endl;
	}
}
