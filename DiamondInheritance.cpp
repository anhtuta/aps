/*
Diamond
You are asked to help diagnose class diagrams to identify instances of 
diamond inheritance. The following example class diagram illustrates 
the property of diamond inheritance. There are four classes: A, B, C and D. An arrow pointing from X to Y indicates that class X inherits from class Y.

<< Xem hình DiamondInheritance.png >>

In this class diagram, D inherits from both B and C, B inherits from A,
and C also inherits from A. An inheritance path from X to Y is defined 
as a sequence of classes X, C1, C2, C3, ..., Cn, Y where X inherits from 
C1, Ci inherits from Ci + 1 for 1 ≤ i ≤ n - 1, and Cn inherits from Y. 
There are two inheritance paths from D to A in the example above. The 
first path is D, B, A and the second path is D, C, A.

A class diagram is said to contain a diamond inheritance if there exists
a pair of classes X and Y such that there are at least two different
inheritance paths from X to Y. The above class diagram is a classic
example of diamond inheritance. Your task is to determine whether or 
not a given class diagram contains a diamond inheritance.

Input

The first line of the input gives the number of test cases, T. T test 
cases follow, each specifies a class diagram. The first line of each 
test case gives the number of classes in this diagram, N. The classes
are numbered from 1 to N. N lines follow. The ith line starts with a
non-negative integer Mi indicating the number of classes that class i
inherits from. This is followed by Mi distinct positive integers each 
from 1 to N representing those classes. You may assume that:

If there is an inheritance path from X to Y then there is no inheritance 
path from Y to X.

A class will never inherit from itself.

Output

For each diagram, output one line containing "Case #x: y", where x is 
the case number (starting from 1) and y is "Yes" if the class diagram 
contains a diamond inheritance, "No" otherwise.

Limits

1 ≤ T ≤ 50.
0 ≤ Mi ≤ 10.

Small dataset

1 ≤ N ≤ 50.

Large dataset

1 ≤ N ≤ 1,000.

Sample

Input   

3
3
1 2
1 3
0
5
2 2 3
1 4
1 5
1 5
0
3
2 2 3
1 3
0 

Output

Case #1 
No
Case #2 
Yes
Case #3 
Yes


bài này tìm trong 1 tập các lới, có tồn tại kế thừa hình thoi hay ko
Cách làm: BFS từ từng điểm, nếu thăm 1 điểm khác 2 lần thì tồn tại
*/

#include <iostream>
#include <stdio.h>

#define MAX 1001

using namespace std;

int T;
int n;
int a[MAX][11];		//1 class kề thừa tối đa từ 10 class cha
int visited[MAX];

void xuongDong() {
	cout<<endl;
}

int myQueue[1000000];
int front, rear;
void initQueue() {
	front = rear = -1;
}
void enQueue(int a) {
	rear++;
	myQueue[rear] = a;
}
int deQueue() {
	front++;
	int temp = myQueue[front];
	if(front==rear) front=rear=-1;
	return temp;
}
bool isQueueEmpty() {
	return front==-1 && rear==-1;
}

void input() {
	cin >> n;

	//init
	for(int i=1; i<=n; i++) {
		visited[i] = 0;
		for(int j=0; j<=10; j++) {
			a[i][j] = 0;
		}
	}

	int nunOfFather, father;
	for(int i=1; i<=n; i++) {
		cin >> a[i][0];
		for(int j=1; j<=a[i][0]; j++) {
			cin >> a[i][j];
		}
	}
}

void initVisited() {
	for(int i=1; i<=n; i++) {
		visited[i] = 0;
	}
}

void printVisited() {
	printf("print visited....\n");
	for(int i=1; i<=n; i++) {
		printf("%d ",visited[i]);
	}
	xuongDong();
}

//BFS từ đỉnh k để kiểm tra xem có kế thừa kim cương từ đỉnh k hay ko 
bool BFS(int k) {
	if(a[k][0] < 2) return false;	//nếu đỉnh này ko kế thừa từ 2 cha trở lên thì return false

	initQueue();
	initVisited();
	enQueue(k);
	visited[k] = 1;
	int neigh;

	while(!isQueueEmpty()) {
		int p = deQueue();

		//xét các hàng xóm của p
		for(int i=1; i<=a[p][0]; i++) {
			//a[p][i] là hàng xóm của p
			neigh = a[p][i];

			//Nếu đỉnh neigh đã thăm rồi, nghĩa là trước đó đã tìm đc
			//1 đường đi từ k tới neigh, bây giờ lại đi được tới neigh nữa
			//chứng tỏ đây là 1 kế thừa hình kim cương. return true!
			if(visited[neigh]==1) return true;
			else {
				visited[neigh] = 1;
				enQueue(neigh);
			}
		}
	}
	return false;
}

bool diamondInheritance() {
	for(int i=1; i<=n; i++) {
		if(BFS(i)) return true;
	}
	return false;
}

int main() {
	freopen("DiamondInheritance_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		cout << "Case #" << tc << endl;
		if(diamondInheritance()) cout << "Yes\n";
		else cout << "No\n";
	}
}

/*
input: xem file DiamondInheritance_input.txt

output:
Case #1
No
Case #2
Yes
Case #3
Yes
Case #4
No
Case #5
No
Case #6
Yes
Case #7
No
Case #8
Yes
Case #9
Yes
Case #10
Yes
Case #11
No
Case #12
Yes
Case #13
Yes
Case #14
No
Case #15
No
Case #16
Yes
Case #17
No
Case #18
Yes
Case #19
Yes
Case #20
Yes
Case #21
Yes
Case #22
Yes
Case #23
Yes
Case #24
Yes
Case #25
Yes
Case #26
Yes
Case #27
Yes
Case #28
Yes
Case #29
Yes
Case #30
Yes
Case #31
Yes
Case #32
Yes
Case #33
No
Case #34
Yes
Case #35
No
Case #36
No
Case #37
Yes
Case #38
Yes
Case #39
No
Case #40
Yes
Case #41
No
Case #42
Yes
Case #43
No
Case #44
No
Case #45
No
Case #46
No
Case #47
No
Case #48
No
Case #49
No
Case #50
No

*/