/*
Painting - MỘT BÀI CƠ BẢN DÙNG BACKTRACKING

The design team at SAMSUNG Electronics considers an innovative 
design for a new product.

The left figure is the basic diagram and the design team tries 
to distinguish each area marked by letter of the alphabet with four colors.

When proceeding with this, the design team pursues perfection 
by researching the combinations of all colors and chooses one of them.

However, they have trouble because they do not know the total 
number of cases of the color combinations.

Due to this difficulty, you convert the basic diagram on the 
left to the graph in the center and then you solve the problem 
by converting it to the adjacency matrix on the right.

The number of cases is 264.

What is the method used to solve this?  (Time Limit : 2 seconds)

[Input]
The adjacency matrix about a basic diagram is entered.
On the first line, the number of the test cases (1<=T <= 10) is given.
On the first line of each test case, the size of the matrix n 
(1<=n <= 30, n is the positive number).
From the second line, the values of matrix are entered by being 
distinguished as one blank or other.


[Output]

 

For each test case, you should print "Case #T" in the first 
line where T means the case number. 
In the second line, print out the total number of cases to 
paint and distinguish them with four colors for each area.

input:
4
4

0 0 0 1

0 0 0 1

0 0 0 1

1 1 1 0

5

0 1 1 1 0

1 0 0 1 1

1 0 0 1 0

1 1 1 0 1

0 1 0 1 0

7

0 1 0 0 1 0 1

1 0 1 0 1 0 0

0 1 0 1 1 0 0

0 0 1 0 1 1 0

1 1 1 1 0 1 1

0 0 0 1 1 0 1

1 0 0 0 1 1 0
15
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 1 0 1 1 0 0 1 1 0 0 1 1 
0 0 0 0 1 0 1 1 0 0 0 0 0 1 0 
0 1 0 0 1 1 0 1 0 1 0 1 0 1 1 
0 0 1 1 0 1 1 0 0 1 1 1 1 1 1 
0 1 0 1 1 0 0 1 0 0 1 1 1 0 0 
0 1 1 0 1 0 0 0 0 1 1 1 0 0 0 
0 0 1 1 0 1 0 0 0 1 0 0 0 1 1 
0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 
0 1 0 1 1 0 1 1 0 0 1 0 0 1 0 
0 1 0 0 1 1 1 0 1 1 0 0 0 0 0 
0 0 0 1 1 1 1 0 0 0 0 0 1 0 0 
0 0 0 0 1 1 0 0 0 0 0 1 0 0 1 
0 1 1 1 1 0 0 1 0 1 0 0 0 0 1 
0 1 0 1 1 0 0 1 0 0 0 0 1 1 0 
 
output:
Case #1
108
Case #2
96
Case #3
264
Case #4
864

*/
/*
Bài này là bài tô màu đồ thị, input là 1 matrix kề của đồ thị. yêu cầu tính số cách có thể
tô các đỉnh của đồ thị = 4 màu sao cho ko có 2 đỉnh kề == màu nhau
*/
#include<iostream>
#include<stdio.h>

#define MAX 31
#define NUM_OF_COLOR 4

using namespace std;

int T;
int n;
int a[MAX][MAX];
int color[MAX];
int numOfCasesToPaint;

void input() {
	cin >> n;
	numOfCasesToPaint = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
}

//check xem màu i có thể tô cho đỉnh k hay ko
bool thuocTapUCV(int i, int k) {
	for(int j = 1; j <= n; j++) {
		if(a[k][j] == 1) {
			if(color[j] == i) return false;
		}
	}
	return true;
}

//tìm màu để tô cho đỉnh k
void paiting(int k) {
	if(k == n+1) {
		numOfCasesToPaint++;
		return;
	}

	for(int i = 1; i <= NUM_OF_COLOR; i++) {
		if(thuocTapUCV(i, k)) {
			color[k] = i;
			paiting(k+1);
			color[k] = 0;
		}
	}
}

int main() {
	freopen("Painting.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		paiting(1);
		cout << "Case #" << tc << endl;
		cout << numOfCasesToPaint << endl;
	}
}
