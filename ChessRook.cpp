/*
Chess rook
In chess, the rook is a piece that can move any number of squares 
vertically or horizontally.

In this problem we will consider small chess boards (at most 4 ×4) 
that can also contain walls through which rooks cannot move.

The goal is to place as many rooks on a board as possible so that 
no two can capture each other.

A configuration of rooks is legal provided that no two rooks are 
on the same horizontal row or vertical column unless there is at 
least one wall separating them.

The following image shows five pictures of the same board. The first 
picture is the empty board, the second and third pictures show legal 
configurations, and the fourth and fifth pictures show illegal configurations.

For this board, the maximum number of rooks in a legal configuration 
is 5; the second picture shows one way to do it, but there are several other ways.

 

Your task is to write a program that, given a description of a board, 
calculates the maximum number of rooks that can be placed on the board 
in a legal configuration.

Input

First line of input is number of test cases. Each test case contains 
a board description.

Each board description begins with a line containing a positive integer 
N that is the size of the board; N will be at most 4.

The next N lines each describe one row of the board, with a ‘.’ indicating 
an open space and an uppercase ‘X’ indicating a wall. There are no spaces 
in the input file.

Output

For each test case, output one line containing the maximum number of rooks 
that can be placed on the board in a legal configuration.

Note that first output line of each test case should be Case #tn, 
where tn is the test case number.

Sample input

5

4

.X..

....

XX..

....

2

XX

.X

3

.X.

X.X

.X.

3

...

.XX

.XX

4

....

....

....

....

Sample output

Case #1

5

Case #2

1

Case #3

5

Case #4

2

Case #5

4
*/
/*
Cách làm: 
ở mỗi hàng, ở mỗi ô ta thử đặt con xe xem có đc ko
	nếu đặt đc thì duyệt sang phải xem có đặt đc con xe nữa ko
	sau đó nhảy tới hàng tiếp theo để duyệt (dù có đặt đc con xe thứ 2 hay ko, vẫn nhảy)
sau đó nhảy tới hàng tiếp theo để duyệt (dù có đặt đc con xe thứ 1 hay ko, vẫn nhảy)
(phải nhảy 2 lần nhé)

*/

/*============ LỜI CẢM ƠN ============*/
/* Lời giải này tham khảo từ tác giả Huy Tran, ai muốn làm quen với
 * Huy xin vui lòng vào đây mà nhìn mặt nó:
 * https://www.facebook.com/huycucpro.vip
 **/

#include<iostream>
#include<stdio.h>

#define MAX 5
#define BOARD_SIZE_wtf 4

using namespace std;

int T;
int n;
char a[MAX][MAX];
int mark[MAX][MAX];
int maxRooks;
int countRooks;

void input() {
	cin >> n;
	maxRooks = 0;
	countRooks = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> a[i][j];
			mark[i][j] = 0;
		}
	}
}

//check bên trái vị trí (r,c) để xem
//có thể đặt con xe vào vị trí (r,c) đc ko
bool checkLeft(int r, int c) {
	if(c == 1) return true;	//con xe ở vị trí đầu tiên của hàng r
	
	for(int i = c-1; i >= 1; i--) {
		if(a[r][i] == 'X') return true;
		if(mark[r][i] == 1) return false;	//nếu đi từ vị trí hiện tại sang trái mà gặp con xe khác thì return false
	}
	return true;
}

//vì ta đi từ trái sang nên có thể ko cần check bên phải
//bởi vì bên phải chắc chắn chưa có con xe nào
bool checkRight(int r, int c) {
	/*if(c == n) return true;
	for(int i = c+1; i <= n; i++) {
		if(a[r][i] == 'X') return true;
		if(mark[r][i] == 1) return false;
	}*/
	return true;
}

bool checkUp(int r, int c) {
	if(r == 1) return true;
	for(int i = r-1; i >= 1; i--) {
		if(a[i][c] == 'X') return true;
		if(mark[i][c] == 1) return false;
	}
	return true;
}

bool checkDown(int r, int c) {
	if(r == n) return true;
	for(int i = r+1; i <= n; i++) {
		if(a[i][c] == 'X') return true;
		if(mark[i][c] == 1) return false;
	}
	return true;
}

//check xem con xe ở vị trí (row, col) có hợp lệ ko
bool checkValid(int row, int col) {
	if(checkLeft(row, col) && checkRight(row, col) && 
		checkUp(row, col) && checkDown(row, col) &&
		 a[row][col] != 'X') return true;
	return false;
}

void printMark() {
	cout << "print mark\n";
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cout<<mark[i][j]<<" ";
		}
		cout<<endl;
	}
	printf("countRooks %d, maxRooks = %d\n", countRooks, maxRooks);
}

void chessRook3(int row) {
	//Nếu row > số lượng hàng thì return
	if(row == n+1) {
		if(countRooks > maxRooks) maxRooks = countRooks;
		return;
	}

	bool isBackTrack = false;
	for(int i = 1; i <= n; i++) {	//xét từng cột trong hàng row để chọn vị trí đặt con xe đầu tiên
		//cout << "i = "<<i<<", row = " << row << endl;
		//printMark();
		if(checkValid(row, i)) {
			isBackTrack = true;
			//(1)
			countRooks++;
			mark[row][i] = 1;

			bool isBackTrack2 = false;
			//nếu (row,i) là 1 trong 2 vị trí đầu cuối cùng của hàng
			//row thì ko thể thêm con xe nào nữa, chuyển sang hàng tiếp
			if(i == n-1 || i==n) {
				chessRook3(row+1);
			} else {
				//ngược lại thì có thể có cơ hội thêm đc con xe nữa
				//ở trên hàng này. Ta phải tìm nó
				for(int j = i+1; j <= n; j++) {
					if(checkValid(row, j)) {
						isBackTrack2 = true;
						//(2)
						countRooks++;
						mark[row][j] = 1;

						chessRook3(row + 1);

						//khôi phục ở (2), do ở trên đã set nó giá trị khác
						countRooks--;
						mark[row][j] = 0;
					}
				}
			}

			//Nếu ko tìm đc vị trí đặt con xe thứ 2 thì vẫn phải nhảy tới
			//hàng tiếp theo
			if(!isBackTrack2) chessRook3(row+1);

			//khôi phục ở (1), do ở trên đã set nó giá trị khác
			countRooks--;
			mark[row][i] = 0;
		}
	}

	//Nếu hàng này ko thể tìm đc vị trí nào để đặt con xe
	//thì vẫn phải check hàng tiếp theo
	if(!isBackTrack) chessRook3(row+1);
}


int main() {
	freopen("ChessRook.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		chessRook3(1);
		cout << "Case #" << tc << endl;
		cout << maxRooks << endl;
	}
}

