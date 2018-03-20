/*
Turn Over Game
﻿As in , there is a 4×4 sized table. In a grid of the table, there are white or black stones. When you choose a position of stone randomly, the stone and four stones adjacent to the up, down, left and right sides of the stone will turn to the opposite color like turning a white stone to a black & a black stone to a white. Let’s suppose this process as a calculation.﻿﻿


Using such a calculation, you want to change all the stones on the table into all whites or all blacks. Find out the minimum operation count at this time. 

Time limit: 1 second (java: 2 seconds)

[Input]
Several test cases can be included in the inputs. T, the number of cases is given in the first row of the inputs. After that, the test cases as many as T (T ≤ 30) are given in a row. 
Table info is given without blank over four rows per each test case. Colors are indicated like white for ‘w’ and black for ‘b’.

[Output]
Output the minimum operation count to change all colors as white or black on the first row per each test case. If not possible, output "impossible" .

[I/O Example]
Input
2
bwwb
bbwb
bwwb
bwww
bwbw
wwww
bbwb
bwwb

Output
Case #1 

4 

Case #2
impossible
*/
/*
Đây là bài bàn cờ đen trắng:
bàn cờ 4*4, mỗi ô có 1 màu đen hoặc trắng
nếu đổi màu 1 ô thì 4 ô xung quanh nó cũng sẽ phải đổi màu.
tính số lần đổi màu ít nhất để cả 16 ô đều cùng 1 màu

Bài này dùng quay lui, ở mỗi ô xét 2 trường hợp:
- Nếu ko đổi màu ô đó thì xét tiếp tới ô tiếp theo
- Nếu đổi màu ô đó thì đổi màu 4 ô xung quanh và xét tiếp tới ô tiếp theo
*/


#include <iostream>
#include <stdio.h>

#define MAX 20001
#define INF 9999999

using namespace std;

int T;
int n;
char a[5][5];
char mark[5][5];

int currCount;
int minCount;

int moveX[] = {1, 0, -1, 0};
int moveY[] = {0, -1, 0, 1};

void input() {
	currCount = 0;
	minCount = INF;
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 4; j++) {
			cin >> a[i][j];
			mark[i][j] = a[i][j];
		}
	}
}

bool checkIfAllHaveSameColor() {
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 4; j++) {
			if(mark[i][j] != mark[1][1]) return false;
		}
	}
	return true;
}

void changeColor4Squares(int r, int c) {
	for(int i = 0; i < 4; i++) {
		int newR = r + moveX[i];
		int newC = c + moveY[i];
		if(newR >= 1 && newR <= 4 && newC >= 1 && newC <= 4) {
			if(mark[newR][newC] == 'b') mark[newR][newC] = 'w';
			else mark[newR][newC] = 'b';
		}
	}
}

void printMark() {
	cout<<"print mark\n";
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 4; j++) {
			cout << mark[i][j] << " ";
		}
		cout<<endl;
	}
	if(checkIfAllHaveSameColor()) {
		printf("minCoun = %d, currCount = %d\n", minCount, currCount);
	}
}

//duyệt ô thứ k xem nên cho nó màu j
void turnOverGame(int k) {
	if(checkIfAllHaveSameColor()) {
		if(currCount < minCount) minCount = currCount;
		return;
	}

	if(k > 15) {
		return;
	}

	int r = k/4+1;
	int c = k%4+1;

	for(int i = 0; i <= 1; i++) {
		if(i == 0) {
			//ko thay đổi màu của ô k này
			turnOverGame(k+1);
		} else {
			currCount++;
			
			//đổi màu ô k này,
			if(mark[r][c] == 'b') mark[r][c] = 'w';
			else mark[r][c] = 'b';

			//và đổi màu các ô xung quanh nó
			changeColor4Squares(r,c);

			turnOverGame(k+1);

			//quay lui lại
			currCount--;
			if(mark[r][c] == 'b') mark[r][c] = 'w';
			else mark[r][c] = 'b';

			//và đổi màu các ô xung quanh nó
			changeColor4Squares(r,c);
		}
	}
}

int main() {
	freopen("TurnOverGame.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		turnOverGame(0);
		cout << "Case #" << tc << endl;
		if(minCount != INF)
			cout << minCount << endl;
		else cout << "impossible\n";
	}
}

