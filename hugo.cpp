/*
Hugo
Có thử thách dành cho Hugo như sau: Hugo được thả vào 1 khu rừng 
có rất nhiều kim cương, tuy nhiên đồng thời lúc đó có các đám cháy 
xuất hiện. Các đám cháy này sẽ lây lan ra các khu vực lân cận theo 
bốn hướng sau 1 giờ. Tuy nhiên trong khu rừng có một số hồ nhỏ, và 
lửa không thể cháy lan trên hồ.

Thời gian để Hugo di chuyển giữa các khu đất là 1 giờ, qua khu hồ là 
2 giờ. Hãy giúp Hugo thoát khỏi khu rừng cùng với số lượng kim cương 
lớn nhất có thể và đảm bảo Hugo không bị lửa thiêu.

Lưu ý khu rừng chỉ tồn tại một số lượng nhất định lối thoát, tại danh 
giới của khu rừng, và Hugo không bao giờ quay lại khu vực mình đã đi qua.

<< XEM ẢNH Ở FILE hugo.png (cùng thư mục này) >>

Input
Dòng đầu là số lượng test case T (T <= 50).
Dòng đầu của mỗi test case là 4 số N, M, SR, SC tương ứng là số hàng, 
số cột của khu rừng và tọa độ hàng, cột mà Hugo đang đứng. ( 4 <= N, M <= 15).
3 dòng tiếp theo, bắt đầu của mỗi dòng tương ứng là số lượng K các 
đám cháy hiện có, các hồ và các lối thoát, 2K số tiếp theo trên dòng 
là tọa độ tương ứng. N dòng tiếp theo sẽ là bản đồ mô tả số lượng kim 
cương D tại mỗi khu vực trong khu rừng. (0 <= D <= 1000)

Output
In mỗi test case trên 2 dòng, dòng đầu tiên là "Case #x", với x là 
số thứ tự của test case.
Dòng tiếp theo là số lượng kim cương lớn nhất mà Hugo có thể thu được, 
nếu Hugo không thể thoát ra khỏi khu rừng, in ra -1.
Sample

Input
5 <- Số lượng test case
4 4 1 2 <- Test case 1, khu rừng có kích thước 4x4, Hugo đang ở ô (1, 2)
2 1 1 4 1 <- 2 Khu vực bắt đầu cháy ở (1, 1) và (4, 1)
4 1 3 2 1 3 3 3 4 <- 4 Khu vực là hồ ở (1, 3), (2, 1), (3, 3) và (3, 4)
2 2 4 3 4 <- 2 lối thoát ở ô (2, 4) và (3, 4)
0 0 10 20 <- Số lượng kim cương hàng 1
9 3 2 5 <- Số lượng kim cương hàng 2
0 0 0 0 <- Số lượng kim cương hàng 3
0 10 0 100 <- Số lượng kim cương hàng 4
...

Output
Case #1
10  <- Số lượng kim cương lớn nhất mà Hugo có thể thu được
Case #2
45
Case #3
250
Case #4
643
Case #5
328

*/
/*
	CORRECT ANSWER: cách giải
	Ban đầu ta cần BFS fire để tìm thời gian lửa loang đến tất cả các ô
	sau đó dùng hàm quay lui để cho hugo đi nhặt kim cương:
	Hugo(x, y, diamond, time) {
		//x,y = tọa độ hiện tại của hugo
		//diamond = số kim cương hugo đang có ở ô (x,y)
		//time = thời gian thoát khỏi ô này
	}
*/
#include <iostream>
#include <stdio.h>

#define MAX 16

#define HUGO 1
#define FIRE 2
#define LAKE 3
#define DIAMOND 4
#define EXIT 5

using namespace std;

int T;
int n, m;
int hugo[MAX][MAX];		//đánh dấu vị trí mà hugo đã thăm
int fire[MAX][MAX];
int lake[MAX][MAX];
int diamond[MAX][MAX];
int exitway[MAX][MAX];
bool isHugoEscape;

int moveX[] = {0,0,-1,1};
int moveY[] = {-1,1,0,0};	//move: left, right, up, down

int maxDiamonds;
int SR, SC;

struct myPoint {
	int x,y;
};

struct myPoint myQueue[400];
int front, rear;


/*=========== my queue =============*/
void initQueue() {
	front = rear = -1;
}

bool isQueueEmpty() {
	return front==-1 && rear==-1;
}

void enQueue(myPoint data) {
	rear++;
	myQueue[rear] = data;
}

myPoint deQueue() {
	front++;
	struct myPoint temp = myQueue[front];
	if(front == rear) front = rear = -1;
	return temp;
}
/*=========== end of my queue =============*/

void input() {
	cin >> n >> m >> SR >> SC;

	maxDiamonds = 0;
	isHugoEscape = false;

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			hugo[i][j] = 0;
			fire[i][j] = 0;
			lake[i][j] = 0;
			diamond[i][j] = 0;
			exitway[i][j] = 0;
		}
	}

	hugo[SR][SC] = 1;

	int numOfFires, numOfLakes, numOfExits, x, y;
	cin >> numOfFires;
	for(int i = 1; i <= numOfFires; i++) {
		cin >> x >> y;
		fire[x][y] = 1;
	}
	cin >> numOfLakes;
	for(int i = 1; i <= numOfLakes; i++) {
		cin >> x >> y;
		lake[x][y] = 1;
	}
	cin >> numOfExits;
	for(int i = 1; i <= numOfExits; i++) {
		cin >> x >> y;
		exitway[x][y] = 1;
	}

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> diamond[i][j];
		}
	}
}

//check xem lửa có lan đc vào tọa độ (x,y) hay ko
bool checkFire(int x, int y) {
	//printf("checkFire: x = %d, y = %d\n", x, y);
	if(x < 1 || x > n || y < 1 || y > m) return false;
	if(lake[x][y] == 1) return false;
	if(fire[x][y] != 0) return false;

	return true;
}

//BFS fire để tìm thời gian lửa lan tới tất cả các ô
void BFS_Fire() {
	initQueue();
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(fire[i][j] == 1) {
				myPoint p1;
				p1.x = i;
				p1.y = j;
				enQueue(p1);
			}
		}
	}

	while(!isQueueEmpty()) {
		myPoint p2 = deQueue();

		//xét các hàng xóm của p2
		for(int i = 0; i < 4; i++) {
			int xNext = p2.x + moveX[i];
			int yNext = p2.y + moveY[i];
			if(checkFire(xNext, yNext)) {
				//nếu lửa chưa lan tới ô (xNext, yNext)
				//thì nhét ô đó vào queue
				fire[xNext][yNext] = fire[p2.x][p2.y] + 1;
				myPoint p3;
				p3.x = xNext; p3.y = yNext;
				enQueue(p3);
			}
		}
	}
}

//check xem hugo có đi đc vào tọa độ (x,y) hay ko
bool checkHugo(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > m) return false;
	if(hugo[x][y] == 1) return false;
	return true;
}

//x,y = current position, dm = current amount of diamond
//time = current time
void hugoStealDiamond(int x, int y, int dm, int time) {
	if(time >= fire[x][y] && fire[x][y] != 0) return;	//hugo ko thể vào ô này, vì sẽ bị thiêu

	if(exitway[x][y] == 1) {
		//update số lượng kim cương, nhưng KHÔNG return, vì
		//có thể hugo sẽ nhảy sang ô khác chứ ko thoát khỏi rừng luôn
		isHugoEscape = true;	//đã tìm đc lời giải
		if(maxDiamonds < dm) maxDiamonds = dm;
	}

	//tìm vị trí tiếp theo của hugo
	for(int i=0; i<4; i++) {
		int xNext = x + moveX[i];
		int yNext = y + moveY[i];
		if(checkHugo(xNext, yNext)) {
			if(lake[x][y]==1) {
				//Nếu ô hiện tại là hồ thì tốn 2 time
				hugo[xNext][yNext] = 1;
				hugoStealDiamond(xNext, yNext, dm + diamond[xNext][yNext], time+2);
				hugo[xNext][yNext] = 0;
			} else {
				hugo[xNext][yNext] = 1;
				hugoStealDiamond(xNext, yNext, dm + diamond[xNext][yNext], time+1);
				hugo[xNext][yNext] = 0;
			}
		}
	}
}

int main() {
	freopen("Hugo_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		BFS_Fire();
		hugo[SR][SC] = 1;		//đánh dấu hugo đã đi qua ô này rồi, vì đây là ô start
		hugoStealDiamond(SR, SC, diamond[SR][SC], 1);
		//Do khi bắt đầu thì các ô chứa lửa có giá trị = 1 (time = 1)
		//nên thời gian khởi tạo của hugo cũng phải = 1

		cout << "Case #" << tc << endl;
		if(isHugoEscape)
			cout << maxDiamonds << endl;
		else cout << "-1\n";
	}
}
