/*
Little Elephants
The Little Elephant and his friends from the Zoo were returning from the 
party. But suddenly they were stopped by the policeman Big Hippo, who 
wanted to make an alcohol test for elephants.

There were N elephants ordered from the left to the right in a row and 
numbered from 0 to N-1.Let R[i] to be the result of breathalyzer test 
of i-th elephant.

Considering current laws in the Zoo, elephants would be arrested if there 
exist K consecutive elephants among them for which at least M of these K 
elephants have the maximal test result among these K elephants.

Using poor math notations we can alternatively define this as follows. 
The elephants would be arrested if there exists i from 0 to N-K, inclusive, 
such that for at least M different values of j from i to i+K-1,inclusive, 
we have R[j] = max{R[i], R[i+1], ..., R[i+K-1]}.

The Big Hippo is very old and the Little Elephant can change some of the results. 
In a single operation he can add 1 to the result of any elephant. 
But for each of the elephants he can apply this operation at most once.

What is the minimum number of operations that the Little Elephant needs 
to apply, such that the sequence of results, after all operations will 
be applied, let elephants to avoid the arrest? If it is impossible to 
avoid the arrest applying any number of operations, output -1.

 

Input

The first line of the input contains an integer T denoting the number 
of test cases. The description of T test cases follows. The first line 
of each test case contains three space-separated integers N,K, M. The 
second line contains N space-separated integers R[0],R[1], ..., R[N-1] 
denoting the test results of the elephants.

Output

For each test case, output a single line containing the minimum number 
of operations needed to avoid the arrest.

Constraints

1 ≤ T ≤ 10

1 ≤ M ≤ K ≤ N ≤ 17

1 ≤ R[i] ≤ 17

Example
Input:
4

5 3 2

1 3 1 2 1

5 3 3

7 7 7 7 7

5 3 3

7 7 7 8 8

4 3 1

1 3 1 2

 

Output:

#1 0

#2 1

#3 1

#4 -1

cho n con voi, nếu trong k con voi liên tiếp nhau, có m con có nồng độ
cồn = nhau và = max thì tất cả các con voi sẽ bị bắt (max = nồng độ cồn
lớn nhất trong k con voi liên tiếp đó)
nhiệm vụ: thêm 1 hoặc ko thêm vào nồng độ cồn của các con voi sao cho
tất cả các con voi ko bị bắt, in ra số lượng thêm ít nhất
nếu ko có solution nào thì in ra -1

VD:
5 3 3
7 7 7 8 8

có các nhóm 3 con voi: 777, 778, 788
nhóm 777 có 3 ( = m) con có nồng độ = max, cần sửa nhóm này,
có thể sửa thành: 787, 877,...
vậy chi phí sửa là 1

VD2:
5 3 2
1 3 1 2 1

k = 3, ta duyệt tất cả các nhóm có 3 con voi:
131, 312, 121.
ko có nhóm nào có 2 con trở lên mà nồng độ cồn = nhau và = max
do vậy đám voi này ko bị bắt
*/
#include <iostream>
#include <stdio.h>

#define MAX 18
#define INF 9999999

using namespace std;

int T;
int n,k,m;
//n=số lượng voi
//k=số lượng voi trong nhóm
//m=số lượng voi đạt max thì toàn bộ sẽ bị bắt
int r[MAX];
int visited[MAX];
int numOfOperation;
int minNumOfOperation;

void xuongDong() {
	cout<<endl;
}

struct Point {
	int x,y;
};

Point myQueue[1000000];
int front, rear;
void initQueue() {
	front = rear = -1;
}
void enQueue(int i, int j) {
	Point p;
	p.x = i; p.y = j;
	rear++;
	myQueue[rear] = p;
}
Point deQueue() {
	front++;
	Point p = myQueue[front];
	if(front==rear) front=rear=-1;
	return p;
}
bool isQueueEmpty() {
	return front==-1 && rear==-1;
}

void input() {
	cin >> n >> k >> m;
	for(int i=0; i<n; i++) {
		cin >> r[i];
	}
	numOfOperation = 0;
	minNumOfOperation = INF;
}

void printR() {
	for(int i=1; i<=n; i++) {
		cout << r[i] << " ";
	}
	cout<<endl;
}

//chỉnh sửa nồng độ cồn của con voi thứ a,
//hoặc ko chỉnh sửa (tăng lên 1 hoặc ko tăng)
void stupidElephants(int a) {
	if(a > n-1) {
		//printR();
		for(int i=0; i<n-k+1; i++) {
			//tính số con voi có chỉ nồng độ cồn = max trong nhóm k con voi
			int maxOfGroup = r[i];
			int numOfMax = 1;
			for(int j=i+1; j<i+k; j++) {
				if(maxOfGroup < r[j]) {
					maxOfGroup = r[j];
					numOfMax = 1;
				} else if(maxOfGroup == r[j]) {
					numOfMax++;
				}
			}

			if(numOfMax >= m) return;
		}

		//Nếu chạy tới đây thì số lượng con voi có độ cồn = max sẽ < m
		if(minNumOfOperation > numOfOperation) minNumOfOperation = numOfOperation;
		return;
	}

	for(int i=0; i<=1; i++) {
		r[a] += i;
		if(i==1) numOfOperation++;
		stupidElephants(a+1);
		r[a] -= i;
		if(i==1) numOfOperation--;
	}
}

int main() {
	freopen("LittleElephants_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		stupidElephants(1);
		if(minNumOfOperation != INF) 
			cout << "#" << tc << " " << minNumOfOperation << endl;
		else
			cout << "#" << tc << " " << "-1" << endl;

	}
}