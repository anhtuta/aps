/*
Pink and Blue
Xenny was a teacher and he had N students. The N children were sitting in a room. 
Each child was wearing a white T-shirt, with a unique number from the range 1 to N 
written on it. T-Shirts of pink and blue color were to be distributed among the 
students by Xenny. This made the students very happy.

Xenny felt that a random distribution of T-Shirts would be very 
uninteresting. So, he decided to keep an interesting condition:

Every student would get a T-Shirt that is of a different color 
than his/her friends. That is, if X and Y are friends and X has a 
Pink T-Shirt, then Y should compulsorily have a Blue T-Shirt, and vice-versa.

Also, Xenny had a belief that Boys should wear blue T-Shirts and 
Girls should wear pink T-Shirts. If a boy was given a pink T-Shirt 
or a girl was given a Blue T-Shirt, he called it an inversion.

So, Xenny wanted to distribute T-Shirts in the above-mentioned interesting 
manner and also wanted to minimize "inversions". Help him solve the task.

Note: There are no disjoint groups of friends in the room. That is, 
2 distinct groups with finite number of students do not exist, but 
exactly 1 group of students exists in the given situation.

 

Input
The first line is the number of test cases T.

First line of each test case contains 2 space-separated integers - N 
and M - number of students and number of friendships present respectively.

Second line consists of N space-separated characters, where ith 
character denotes the gender of the ith student. B: Boy, G: Girl.

M lines follow. Each line consists of 2 space-separated integers, 
u and v, showing that u is a friend of v and vice-versa.

 

Output
If Xenny could distribute the T-Shirts in the desired way, print the 
minimum number of inversions required.
Else, print -1.

 

Constraints
1 ≤ N ≤ 105
1 ≤ M ≤ 105
1 ≤ u, v ≤ N

Colors of T-Shirt are represented by uppercase characters 'B' and 'G'

 

Sample

 

Input

3

3 2

B G B

1 2

1 3

6 9

B B B G G G

3 5

2 6

4 2

6 3

3 1

3 4

6 1

5 1

1 4

6 5

G G G B G G

6 3

1 3

2 3

4 3

5 3

 

Output 

1

-1

2
*/

/*
Chú ý: bài này input quá dài và quá lớn: file input gồm hơn 300 nghìn dòng,
có test case có 34000 đỉnh và 85000 cạnh, nên lưu = mảng ko đủ bộ nhớ
*/

//lời giải sau dùng mảng, nhưng bộ nhớ ko đủ nên chỉ đc 80đ
#include <iostream>

#define MAX 50001
#define MAX_OF_FRIENDS 1000
#define PINK 0
#define BLUE 1
#define INF 999999

using namespace std;

int T;
int n, m;
int top;
char gender[MAX];	//giới tính của các học sinh (hs)
int color[MAX];	//màu áo của các hs
int a[MAX][MAX_OF_FRIENDS];	//mối quan hệ giữa các hs
int currInversion, minInversion;
int myQueue[100000];
int front, rear;
void initQueue() {
	front = rear = -1;
}
void enQueue(int data) {
	rear++;
	myQueue[rear] = data;
}
int deQueue() {
	front++;
	int temp = myQueue[front];
	if (front == rear) front = rear = -1;
	return temp;
}
bool isQueueEmpty() {
	return front == -1 && rear == -1;
}

void printColor() {
	for (int i = 1; i <= n; i++) {
		if (color[i] == PINK) cout << "pink ";
		else if (color[i] == BLUE) cout << "blue ";
		else
			cout << color[i] << " ";
	}
	cout << endl;
}

void input() {
	cin >> n >> m;
	currInversion = 0, minInversion = INF;
	char c;
	for (int i = 1; i <= n; i++) {
		cin >> c;
		gender[i] = c;
		color[i] = -1;
		a[i][0] = 0;	//khởi tạo hs thứ i có số lượng bạn bè = 0
	}

	int u, v;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v;
		a[u][0]++; a[u][a[u][0]] = v;
		a[v][0]++; a[v][a[v][0]] = u;
	}

	//printColor();
}

void resetColor() {
	for (int i = 1; i <= n; i++)
	{
		color[i] = -1;
	}
}

bool pinkAndBlue() {
	for (int i = 0; i <= 1; i++)
	{
		resetColor();
		currInversion = 0;
		color[1] = i;	//gán màu cho hs đầu tiên
		initQueue();
		enQueue(1);		//cho học sinh đầu tiên vào queue
		int neigh;

		while (!isQueueEmpty()) {
			//lấy hs hiện tại trong queue ra
			int currHs = deQueue();

			//xét các bạn bè của currHs và tô màu cho nó
			for (int j = 1; j <= a[currHs][0]; j++) {
				neigh = a[currHs][j];
				//printf("currHs = %d, neigh = %d\n", currHs, neigh);
				if (color[neigh] == -1) {
					color[neigh] = 1 - color[currHs];
					enQueue(neigh);
				}
				else if (color[neigh] == color[currHs]) return false;
			}
		}

		for (int k = 1; k <= n; k++)
		{
			if (color[k] == PINK && gender[k] == 'B') currInversion++;
			else if (color[k] == BLUE && gender[k] == 'G') currInversion++;
		}
		if (minInversion > currInversion) minInversion = currInversion;
	}
	return true;
}

int main() {
	//FILE *stream; freopen_s(&stream, "PinkAndBlue_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		input();
		if (pinkAndBlue())
			cout << minInversion << endl;
		else cout << "-1" << endl;
		//printColor();
	}
}


//lời giải sau dùng linkedlist nên đc 100đ
//Xem file PinkAndBlue.cpp
