/*
[level 3]
Picking up Jewels

There is a maze that has one entrance and one exit. 
Jewels are placed in passages of the maze. 
You want to pick up the jewels after getting into the maze 
through the entrance and before getting out of it through the exit. 
You want to get as many jewels as possible, but you don’t
want to take the same passage you used once.

When locations of a maze and jewels are given, 
find out the greatest number of jewels you can get without 
taking the same passage twice, and the path taken in this case.

Time limit : 1 sec (Java : 2 sec)

[Input]
There can be more than one test case in the input file. The 
first line has T, the number of test cases. 
Then the totally T test cases are provided in the following 
lines (T ≤ 10 )

In each test case, 
In the first line, the size of the maze N (1 ≤ N ≤ 10) 
is given. The maze is N×N square-shaped. 
From the second line through N lines, information of the 
maze is given. 
“0” means a passage, “1” means a wall, and “2” means a location 
of a jewel. 
The entrance is located on the upper-most left passage and the
exit is located on the lower-most right passage. 
There is no case where the path from the entrance to the exit 
doesn’t exist.

[Output]
Output the greatest number of jewels that can be picked up.

*/

/*
Bài này level 3 nên khá dễ:
Cho 1 mê cung, trong đó có các jewel nằm trên đường đi. lối vào
ở ô (1,1), lối ra ở ô (n, n)
Nhiệm vụ: đi vào mê cung, lấy số lượng jewel nhiều nhất sau đó đi ra
nhưng mỗi con đường (mỗi ô) chỉ đc đi qua 1 lần
đi đường dài ko quan trọng, quan trọng là số lượng jewel lấy đc
*/

#include <iostream>
#include <stdio.h>

#define MAX 11
#define WALL 1
#define JEWEL 2

using namespace std;

int T;
int n;
int a[MAX][MAX];
int visited[MAX][MAX];
int currJewel, maxJewel;
int moveX[] = {0,0,-1,1};
int moveY[] = {-1,1,0,0};

void input() {
	cin >> n;
	currJewel = maxJewel = 0;

	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			cin >> a[i][j];
			visited[i][j] = 0;
		}
	}
}

bool checkExistCell(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > n) return false;
	if(visited[x][y] != 0) return false;
	if(a[x][y] == WALL) return false;
	return true;
}

//quay lui
void pickUpJewels(int x, int y) {
	if(x == n && y == n) {
		if(maxJewel < currJewel) maxJewel = currJewel;
		return;
	}

	int nextX, nextY;
	for(int i = 0; i < 4; i++) {
		nextX = x + moveX[i];
		nextY = y + moveY[i];
		
		if(checkExistCell(nextX, nextY)) {
			visited[nextX][nextY] = 1;
			if(a[nextX][nextY] == JEWEL) currJewel++;
			
			pickUpJewels(nextX, nextY);
			
			visited[nextX][nextY] = 0;
			if(a[nextX][nextY] == JEWEL) currJewel--;
		}
	}
}

int main() {
	freopen("PickingUpJewels_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		visited[1][1] = 1;
		pickUpJewels(1,1);
		cout << maxJewel << endl;
	}
}
/*
input: xem file PickingUpJewels_input.txt
output:
8
6
17
7
11
17
15
17
15
17
*/
