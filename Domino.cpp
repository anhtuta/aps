/*
Bài domino*/
/* xem đề và cách giải ở đây:
http://codesoeasy.weebly.com/home/vonny-vonny-and-her-dominos

SAU ĐÂY LÀ LỜI GIẢI SAI CỦA Anhtu

*/
#include <iostream>
#include <stdio.h>

#define MAX 101

using namespace std;

int T;
int n, m;
int a[8][9];	//cái board có kích thước 7*8
int moveX[] = {0,1};
int moveY[] = {1,0};
int mark[8][9];			//đánh dấu ô (x,y) đã thăm hay chưa
int markDomino[7][7];	//đánh dấu domino (a,b) đã lấy chưa
int cnt;

void input() {
	cnt = 0;
	for(int i = 1; i <= 7; i++) {
		for(int j = 1; j <= 8; j++) {
			cin >> a[i][j];
		}
	}
}

void printMark() {
	printf("print mark\n");
	for(int i = 1; i <= 7; i++) {
		for(int j = 1; j <= 8; j++) {
			cout << mark[i][j] << " ";
		}
		cout<<endl;
	}cout<<endl;
	for(int i = 0; i < 7; i++) {
		for(int j = 0; j < 7; j++) {
			cout << markDomino[i][j] << " ";
		}
		cout<<endl;
	}
}

bool checkIfDominoValid(int x1, int y1, int x2, int y2) {
	//if(x1 < 1 || x1 > 7 || y1 < 1 || y1 > 8 ||
		if(x2 < 1 || x2 > 7 || y2 < 1 || y2 > 8) return false;

	if(mark[x1][y1] != 0 || mark[x2][y2] != 0) return false;
	if(markDomino[a[x1][y1]][a[x2][y2]] != 0 || 
		markDomino[a[x2][y2]][a[x1][y1]] != 0) return false;
	return true;
}

void domino(int k) {
	//printMark();
	//printf("k = %d\n", k);
	if(k > 55) {
		cnt++;
		printf("cnt = %d\n", cnt);
		return;
	}

	int r = k/8+1;
	int c = k%8+1;
	//printf("r = %d, c = %d\n",r,c);

	if(mark[r][c] != 0) {
		domino(k+1);
		return;
	}

	//Tại mỗi 1 ô k (ô (r,c)), ta xét 2 ô cạnh nó, đó là 2 ô bên phải và ở dưới,
	//để thể hợp thành 1 domino. KO CẦN XÉT 2 Ô PHÍA TRÊN VÀ BÊN TRÁI, vì
	//ta duyệt từ trái sang nên chắc chắn các ô đó đã đc duyệt rồi
	bool isBackTrack = false;
	for(int i=0; i<=1; i++) {
		int secondSquareX = r + moveX[i];
		int secondSquareY = c + moveY[i];

		//bây giờ 2 ô (r,c) và (secondSquareX, secondSquareY) có thể
		//hợp thành 1 domino. Ta cần check xem domino đó có valid ko

		if(checkIfDominoValid(r,c,secondSquareX,secondSquareY)) {
			int firstDomino = a[r][c];
			int secondDomino = a[secondSquareX][secondSquareY];

			mark[r][c] = 1;
			mark[secondSquareX][secondSquareY] = 1;
			markDomino[firstDomino][secondDomino] = 1;
			markDomino[secondDomino][firstDomino] = 1;

			isBackTrack = true;
			domino(k+1);

			mark[r][c] = 0;
			mark[secondSquareX][secondSquareY] = 0;
			markDomino[firstDomino][secondDomino] = 0;
			markDomino[secondDomino][firstDomino] = 0;
		}
	}
	if(!isBackTrack) 
		domino(k+1);
}

int main() {
	freopen("dominos.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		domino(0);
		cout << "Case #" << tc << endl;
		cout << cnt << endl;
		
	}
}