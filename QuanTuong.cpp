/*
Quân tượng
Xét bàn cờ vuông kích thước n×n. Các dòng được đánh số từ 1 đến n, 
từ dưới lên trên. Các cột được đánh số từ 1 đến n từ trái qua phải.

Ô nằm trên giao của dòng i và cột j được gọi là ô (i,j). Trên bàn 
cờ có m (0 ≤ m ≤ n) quân cờ. Với m > 0, quân cờ thứ i ở ô (ri, ci), 
i = 1,2,..., m. Không có hai quân cờ nào ở trên cùng một ô. Trong số 
các ô còn lại của bàn cờ, tại ô (p, q) có một quân tượng. Mỗi một 
nước đi, từ vị trí đang đứng quân tượng chỉ có thể di chuyển đến 
được những ô trên cùng đường chéo với nó mà trên đường đi không phải 
qua các ô đã có quân

Cần phải đưa quân tượng từ ô xuất phát (p, q) về ô đích (s,t).

Cho kích thước bàn cờ n, số quân cờ hiện có trên bàn cờ m và vị 
trí của chúng, ô xuất phát và ô đích của quân tượng. Hãy xác định 
số nước đi ít nhất cần thực hiện để đưa quân tượng về ô đích hoặc 
đưa ra số -1 nếu điều này không thể thực hiện được.

Constraints

N = 1~200

Input
Dòng đầu tiên chứa số testcase. Mỗi testcase có cấu trúc như sau:
Dòng thứ nhất chứa 6 số nguyên n, m, p, q, s, t.
Nếu m > 0 thì mỗi dòng thứ i trong m dòng tiếp theo chứa một 
cặp số nguyên ri , ci xác định vị trí quân thứ i.
Hai số liên tiếp trên cùng một dòng được ghi cách nhau ít nhất 
một dấu cách.

Output
Với mỗi test case in ra 1 dòng duy nhất là số nước đi tìm được.

Sample

Input 
2
5 5 5 5 5 3
1 2
1 5
2 2
4 2
4 3
8 3 7 2 1 4
5 4
3 4
4 7

Output
2
3

Cách làm: bài này giống bài fast robot: ta BFS từ vị trí con tượng,
tại 1 điểm, cứ đi thẳng tới khi gặp mép bàn hoặc gặp quân cờ khác thì
dừng, chứ ko phải BFS chỉ xét 4 hàng xóm xq (tại 1 điểm đi theo 4 hướng,
đi hết bàn hoặc gặp quân cờ khác thì thôi)
*/
#include <iostream>
#include <stdio.h>

#define MAX 201

using namespace std;

int T;
int n, m, p, q, s, t;
int a[MAX][MAX];
int visited[MAX][MAX];
int moveX[] = {-1,-1,1,1};
int moveY[] = {-1,1,-1,1};

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

void input() {
	cin >> n>>m>>p>>q>>s>>t;
	p = n-p+1;
	s = n-s+1;

	//init
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			a[i][j] = 0;
			visited[i][j] = 0;
		}
	}

	int x,y;
	for(int i=1; i<=m; i++) {
		cin >> x >> y;
		x = n - x + 1;
		a[x][y] = 1;
	}

	/*for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			cout << a[i][j] << " ";
		}
		xuongDong();
	}
	xuongDong();
	cout << "finish print a[]\n";*/
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

bool checkExistCell(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > n) return false;	//out of bound
	if(a[x][y] == 1) return false;	//this place has a chess standing
	///if(visited[x][y]!=0) return false;
	return true;
}

//bishop = quân tượng
void bishop() {
	initQueue();
	enQueue(p,q);	//cho vị trí xuất phát của con tượng vào queue
	int xNeigh, yNeigh, xCurr, yCurr;
	visited[p][q] = 1;

	while(!isQueueEmpty()) {
		//cout << "while 1...\n\n\n";
		Point pRear = deQueue();
		if(pRear.x == s && pRear.y == t) break;

		for(int i=0; i<4; i++) {
			xCurr = pRear.x;
			yCurr = pRear.y;

			while(1) {
				//cout << "while 2...\n";
				xNeigh = xCurr + moveX[i];
				yNeigh = yCurr + moveY[i];
				//printf("xNeigh = %d, yNeigh = %d\n", xNeigh, yNeigh);

				if(!checkExistCell(xNeigh, yNeigh)) break;
				
				if(visited[xNeigh][yNeigh] == 0) {
					visited[xNeigh][yNeigh] = visited[pRear.x][pRear.y] + 1;
					enQueue(xNeigh, yNeigh);
				}
				
				//Nếu visited[xNeigh][yNeigh] != 0 nghĩa là ô này đã thăm rồi, và
				//visited[xNeigh][yNeigh] chính là giá trị ngắn nhất đi từ vị trí
				//bắt đầu tới ô này. Do đó ko cần nhét nó vào queue nữa
				xCurr = xNeigh; yCurr = yNeigh;
			}
		}

	}

}

int main() {
	freopen("QuanTuong_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		bishop();
		cout << visited[s][t] - 1 << endl;
		//printVisited();
	}
}

/*
input: xem file QuanTuong_input.txt

output:
2
4
2
2
9
8
6
2
3
4
4
5
4
3
2

*/