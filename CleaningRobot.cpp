
/*
bài robot 

Giống với bài này: http://codesoeasy.weebly.com/home/cleanrbt-cleaning-robot
Khác ở chỗ: có thêm chướng ngại vật

Sau đây là lời giải SAI của Anhtu
ý tưởng giải: ta cho robot tìm rác ở vị trí gần nó nhất để nhặt, sau đó
lại tìm rác nào ở gần nó nhất và nhặt tiếp... nhặt tới khi nào hết

nhận xét: cách trên KHÔNG THỂ là cách đi tối ưu, xem hình vẽ để hiểu rõ hơn

Cách giải đúng: cần tìm tất cả các khoảng cách từ robot đến từng rác, và khoảng
cách giữa 2 rác với nhau. VD: có 4 rác và 1 robot, vậy cần tìm 10 khoảng cách
(cần tìm khoảng cách giữa 2 vật bất kỳ). Cách tìm này dùng BFS cho từng điểm rác
và cho vị trí robot. Sau đó ta dùng quay lui để xác định đường đi tối ưu
Ý tưởng là vậy, nhưng chưa có time implement!
*/

#include <iostream>
#include <stdio.h>

#define MAX 101

using namespace std;

int T;
int n, m;
int a[MAX][MAX];
int numOfTrash;
int moveX[] = {0,0,-1,1};
int moveY[] = {1,-1,0,0};

struct tile {
	int x,y;
};

struct tile myQueue[1000000];
int front, rear;
int mark[MAX][MAX];

int startOfRobotX, startOfRobotY;

void initMark() {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			mark[i][j] = 0;
		}
	}
}

void printMark() {
	cout << "printMark\n";
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cout << mark[i][j] << " ";
		}
		cout<<endl;
	}
}

/*============ Queue ===============*/
void initQueue() {
	front = rear = -1;
}

bool isQueueEmpty() {
	return front==-1 && rear==-1;
}

void enQueue(struct tile value) {
	rear++;
	myQueue[rear] = value;
}

struct tile deQueue() {
	/*if(isQueueEmpty()) {
		cout << "Queue is empty! can't pop something\n";
		return;
	}*/
	front++;
	struct tile temp = myQueue[front];
	if(front == rear) {
		//đã lấy hết các phần tử trong queue
		front = rear = -1;
	}
	return temp;
}

void destroyQueue() {
	front = rear = -1;
}
/*============ end of Queue ===============*/

void input() {
	cin >> n >> m;
	numOfTrash = 0;
	initQueue();

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> a[i][j];
			if(a[i][j] == 1) numOfTrash++;
			if(a[i][j] == 3) {
				startOfRobotX = i;
				startOfRobotY = j;
			}
		}
	}
}

//check xem ô này có thể đi đc tới hay ko
//(nghĩa là check xem nó có phải là chướng ngại vật ko)
bool isThisTileSafe(int x, int y) {
	if(x == startOfRobotX && y == startOfRobotY) return false;
	//printf("startOfRobotX = %d, startOfRobotY = %d\n", startOfRobotX, startOfRobotY);
	//printf("isThisTileSafe: x = %d, y = %d\n",x,y);
	if(x < 1 || x > n || y < 1 || y > m) return false;
	return a[x][y]!=2 && mark[x][y]==0;
}

int robot() {
	int kq = 0;
	
	//với mỗi lần duyệt, tìm vị trí của rác gần nhất
	while(numOfTrash != 0) {
		//init
		destroyQueue();
		initMark();

		struct tile rb;
		rb.x = startOfRobotX;
		rb.y = startOfRobotY;
		enQueue(rb);

		a[startOfRobotX][startOfRobotY] = 0;
		//mark[startOfRobotX][startOfRobotY] = -1;

		bool isTrashTaken = false;

		while(!isQueueEmpty()) {
			//printMark();
			//printf("front = %d, rear = %d\n", front, rear);
			struct tile t = deQueue();
			int currX = t.x;
			int currY = t.y;
			//cout << "is queue empty: "<<isQueueEmpty()<<endl;

			if(a[currX][currY] == 1) {
				cout<<"found trash at (" << currX << ", " << currY << ")\n";
				printMark();
				isTrashTaken = true;
				startOfRobotX = currX;
				startOfRobotY = currY;
				kq += mark[currX][currY];
				printf("kq = %d, numOfTrash = %d\n", kq, numOfTrash);
				break;
			}

			int nextX, nextY;
			for(int i=0; i<4; i++) {
				nextX = currX + moveX[i];
				nextY = currY + moveY[i];

				//nếu ô này có thể đi tới thì cho nó vào queue
				if(isThisTileSafe(nextX, nextY)) {
					//cout<<"vao day\n";
					struct tile tempTile;
					tempTile.x = nextX;
					tempTile.y = nextY;
					enQueue(tempTile);
					mark[nextX][nextY] = mark[currX][currY] + 1;
					//printMark();
					//if(rear == 1000000) printf("queue is almost full!\n");
				}
			}
		}
		if(!isTrashTaken) {
			//printf("trash %d isn't taken\n", numOfTrash);
			return -1;
		}
		numOfTrash--;
	}
	//cout << "return kq = "<<kq<<endl;
	return kq;
}

int main() {
	freopen("CleaningRobot.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		//robot();
		cout << "Case #" << tc << endl;
		cout << robot() << endl;
		
	}
}
