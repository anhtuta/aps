/*
Grid Acid
A rectangular grid has N x M size.  Each cell is either made of a special 
metal(type A) or made of stone (type B).

If acid is poured on a cell of grid, it can either melt it(for type A: 
special metal cell) and spread further or do not pass through it(for type B: stone cell).

The cell made with special metal (type A) can melt with acid in 1 
second and thus allow acid to spread further.

The cell made with stone (type B) does not react with acid and hence 
neither melt nor allow acid to pass through it.

There is a third type of a cell that is empty (type C), but has a 
boundary (all 4 sides) covered with a protective metal.

If all 4 sides of it (type C: empty cell) come into contact with 
acid at any given time, then in that case boundary of it (all 4 sides)
melt and allow acid to pass through it. In that case it (type C:  empty cell) 
get filled with acid.

There is only one and only one such cell in a given grid.

 

Acid is poured on one of the cell of grid, the cell being 
made of special metal that can melt with acid.

It is guaranteed that acid will be poured on only one cell 
made up of special metal (type A), not on the stone (type B) 
or the empty cell(type C).

Acid is poured continuously until all the grid cells (except stone - type B) 
melt completely.

You have to tell when the empty cell with special protective 
boundary will get filled with acid and when whole grid will 
get filled with acid (except the cells made up of stones).

It takes 1sec for acid to dissolve special metal cell and after 
that it can spread to its 4 orthogonal neighbors (Left, Right, Up, Down).

Input:

First entry is number of test cases; rest is each test case input.
For each test case first row contains N and M as two integers 
separated by a space.
Next row contains the location of cell (row and column number 
separated by space) where acid will be poured continuously until 
whole grid (except stone cells) melt.
Next N rows contain M integer values each containing the cell type.

Cell type value is of 3 types:
    -  0 : cell is stone (type B)
    -  1:  cell is made special metal (type A)
    -  2:  cell is special empty cell, having a special boundary (type C)
Note:  There is always one and only one cell of type C (value 2) in a given grid.

Output:
Output should contain 2 lines for each test case.
1st line:   Case#
2nd line:   Count1  Count2
    Where:
            Count1:  time in seconds when special empty cell (type C) will get filled.
            Count2:  time in seconds when whole grid will get filled with water (note: 
            stone cell cannot be filled with acid).
Note:
1.  Count2 will be -1if all cells of the grid (except stone cells) 
cannot be dissolved.  Whole grid dissolving term means that all 
cells except stone get filled with Acid.
2.  Count1 will be -1if empty cell cannot be filled. If empty cell 
cannot be filled the #1 is also applicable, i.e. then Count2 = -1.
3.  Once acid enters special cell, it accumulates there for 1 second.
After that the acid starts leaking to neighboring (left, right, up, down) cells.
4.  The terms “dissolve”, “melt”, “leaking” are used to express similar 
meaning that the cell starts leaking the acid to its neighbor 
cells (left, right, up, down).
5. Acid is poured continuously so once a cell starts leaking acid, 
it may spread further to other cells in further course of time.
6.  The maximum number of rows or columns of grid is 3000.

*/
/*
input:
9       ---->Number of test cases.
4 5    -------> N=4: number of rows,   M= 5: number of columns
2 4       ----->  Location of cell(row  col) where acid is poured
1 0 1 0 1   ------>  Grid 1st row with M cell entries
1 0 1 1 1     ----> Acid is  poured on 4thcell of this (2nd) row.
1 1 2 1 1      -----> Rows contains empty cell (type C: value: 2)
1 0 1 0 1         -------> Last row of the grid with cell M values

3 3    ------> 2ndtest case starts, N=3, M=3
1 2 
1 1 0 
1 2 1
0 1 1

3 3
1 1
1 1 1
1 2 1
0 1 1

3 3
3 3
1 1 1
1 2 1
0 1 1

4 4
2 3
0 0 1 0
0 1 1 1
1 1 2 1
1 0 1 1

3 3
1 3
0 1 1
1 2 1
1 1 1

4 5
1 3
1 0 1 0 1
1 0 1 1 1
1 1 1 2 1
1 0 0 1 1

4 5
3 5
1 0 1 0 1
1 0 1 1 1
1 1 1 2 1
1 0 0 1 1

4 5
2 4
1 0 1 0 1
1 1 1 1 1
1 1 2 1 1
1 0 1 1 1

output:
Case #1
-1 -1
Case #2
-1 -1
Case #3
6 6
Case #4
6 6
Case #5
5 5
Case #6
6 6
Case #7
7 7
Case #8
5 9
Case #9
4 6
*/

/*
bài này hiểu như sau:
1 cái lưới, có 3 loại ô: type A,B,C (xem ảnh)
loại A: acid đi vào sẽ tan chảy trong 1 giây, sau đó acid loang tới ô tiếp theo
(acid lan tới ô A thì làm tan nó và tiếp tục đi)
loại B: acid ko thể đi vào
loại C: khi 4 ô xung quanh nó có acid thì nó mới bị acid lan vào và tan chảy (dissolve)

Hiển nhiên: nếu ô loại C ở rìa mép của lưới hoặc ở cạnh 1 ô loại B thì
chắc chắn nó ko thể bị tan chảy

Nhiệm vụ của bạn là tìm thời gian ô loại C bị tan chảy (count1) và thời gian để
toàn bộ lưới bị tan chảy (count2).
hiển nhiên count1 = -1 thì count2 = -1

Cách làm:
BFS để cho acid loang hết grid.:
	Nếu gặp ô nào là METAL thì loang bình thường
	Nếu gặp ô nào là STONE thì KHÔNG loang
	Nếu gặp ô nào là EMOTY_CELL thì phải check xem xung quanh nó là 4 ô có acid hay ko
	
chú ý: Sau khi BFS xong, nếu còn 1 ô METAL chưa được thăm thì cho count2 = -1
Nếu count1 = -1 thì chắc chắn count2 = -1
	
*/
#include <iostream>
#include <stdio.h>

#define MAX 3001
#define STONE 0
#define METAL 1
#define EMPTY_CELL 2


using namespace std;

struct myPoint {
	int x,y;

	myPoint() {}

	myPoint(int a, int b) {
		x=a; y=b;
	}
};

/*============= my queue =========*/
struct myPoint myQueue[1000000];
int front, rear;

void initQueue() {
	front = rear = -1;
}

bool isEmpty() {
	return front==-1 && rear==-1;
}

void enQueue(myPoint data) {
	rear++;
	myQueue[rear] = data;
}

myPoint deQueue() {
	if(isEmpty()) cout << "queue is empty! can't deQueue\n";	
	front++;
	myPoint temp = myQueue[front];
	if(front == rear) front = rear = -1;
	return temp;
}
/*============= end of my queue =========*/

int T;
int n,m;	//N = number of rows, M = number of columns
int grid[MAX][MAX];		//lưới đầu vào, có 1 trong 3 giá trị: 0,1,2
int mark[MAX][MAX];		//đánh dấu xem ô đó đã tràn acid tới chưa, mark[k1][k2] = 5 nghĩa là thời gian tràn acid tới ô k1k2 = 5 giây
int moveX[] = {0,0,-1,1};
int moveY[] = {-1,1,0,0};	//acid lan theo 4 hướng: left, right, up, down
int count1, count2;

int pouringAcidX, pouringAcidY;	//Location of cell(row  col) where acid is poured
int emptyCellX, emptyCellY;		//localion of empty cell

void input() {
	count1 = count2 = -1;
	cin >> n >> m;
	cin >> pouringAcidX >> pouringAcidY;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			mark[i][j] = 0;
			cin >> grid[i][j];
			if(grid[i][j] == EMPTY_CELL) {
				emptyCellX = i;
				emptyCellY = j;
			}
		}
	}
}

void printMark() {
	cout <<"print mark" << endl;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(grid[i][j]==EMPTY_CELL)	cout << "C ";
			else if(grid[i][j]==STONE) cout << "* ";
			else cout << mark[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//nếu empty cell (loại C) mà ở rìa hoặc ở cạnh STONE thì ko thể đổ đầy acid
bool checkIfEmptyCellIsInBoundary() {
	for(int i=0; i<4; i++) {
		int x = emptyCellX + moveX[i];
		int y = emptyCellY + moveY[i];
		if(x < 1 || x > n || y < 1 || y > m) return true;
		if(grid[x][y] == STONE) return true;
	}
	return false;
}

//check xem cell(x,y) có tồn tại hay ko, và đã đc thăm chưa
bool checkCell(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > m) return false;
	if(mark[x][y] != 0) return false;
	return true;
}

bool checkIfEmptyCellBeingAroundByFourAcidCells() {
	int x,y;
	for(int i=0; i<4; i++) {
		x = emptyCellX + moveX[i];
		y = emptyCellY + moveY[i];
		if(mark[x][y] == 0) return false;
	}
	return true;
}

//BFS grid từ ô đổ acid
void BFS_grid() {
	mark[pouringAcidX][pouringAcidY] = 1;
	myPoint p1(pouringAcidX, pouringAcidY);
	enQueue(p1);

	while(!isEmpty()) {
		//printMark();
		//lấy 1 thằng khỏi queue
		myPoint p2 = deQueue();

		//xét các hàng xóm của p2 (trên, dưới, trái, phải)
		for(int i = 0; i < 4; i++) {
			//printf("i = %d\n", i);
			int xNeigh = p2.x + moveX[i];
			int yNeigh = p2.y + moveY[i];
			//printf("xNeigh = %d, yNeigh = %d\n", xNeigh, yNeigh);
			if(checkCell(xNeigh, yNeigh)) {
				if(grid[xNeigh][yNeigh] == EMPTY_CELL) {	//nếu ô này là loại C
					if(checkIfEmptyCellBeingAroundByFourAcidCells()) {
						mark[xNeigh][yNeigh] = mark[p2.x][p2.y];	//đánh dấu đã thăm ô này, chú ý: KHÔNG cộng thêm 1: mark[xNeigh][yNeigh] = mark[p2.x][p2.y]+1
						count1 = mark[xNeigh][yNeigh];
						myPoint p3;
						p3.x = xNeigh; p3.y = yNeigh;
						enQueue(p3);	 //nhét vào queue
					}
				} else if(grid[xNeigh][yNeigh] == METAL) {	//nếu ô này là kim loại
					mark[xNeigh][yNeigh] = mark[p2.x][p2.y] + 1;	//đánh dấu đã thăm ô này
					myPoint p3;
					p3.x = xNeigh; p3.y = yNeigh;
					enQueue(p3);	 //nhét vào queue
				} else {
					//nếu ô này là STONE: ĐÉO LÀM GÌ, ĐÉO LAN ACID VÀO
				}
			}
		}
	}

	//sau khi bfs thì tính kq
	if(count1 == -1) return;
	else {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				//CẦN CHÚ Ý CHECK NHƯ SAU
				//Nếu có 1 ô KHÔNG PHẢI LÀ STONE sau khi BFS mà chưa được duyệt thì count2 = -1
				if(mark[i][j] == 0 && grid[i][j] != STONE) {
					count2 = -1;
					return;
				}
				if(count2 < mark[i][j]) count2 = mark[i][j];
			}
		}
	}

	//printMark();
}

int main() {
	freopen("GridAcid_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		cout << "Case #" << tc << endl;
		if(checkIfEmptyCellIsInBoundary()) cout << "-1 -1" << endl;
		else {
			BFS_grid();
			cout << count1 << " " << count2 << endl;
		}
	}
}
