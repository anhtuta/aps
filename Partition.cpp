/*
Partition 1
This time, Samsung Electronics, in a new building was built on the Umyeon Dong.
Wireless division also was assigned to the spacious.
The total space for Wireless division is fixed and the space for each group is fixed.
Now we should assign partitions for each group.

The time for assigning partition is proportional to size of space.
For example, if the size of space is 1000, it spends time of 1000 to partition it
(It spends same time if we partition it as 300+700 or 500+500.)
The total time depends on the order of partitioning.
For example, in case the size of total space is 800, and each size for groups is 100, 200, and 500.
If partitioning 100+700 first, partitioning 200+500 later, then the total time is 800+700=1500
But, if partitioning 500+300 first, partitioning 100+200 later, then the total time is 800+300=1100


Write program to print the minimum time to partition for all groups.

[Input]
There can be more than one test case in the input.
The first line has T, the number of test cases.
Then the totally T test cases are provided in the following lines.
In each test case, the first line has an integer N(1 ≤ N ≤ 1000); the number of group.
The next line enumerates N integers each separated by a blank; each integer means 
the size of space(S) for each group. (10≤S≤5000)

[Output]
For each test case, you should print your answer in two line.

[Sample]

Input
3
3
500 100 200
4
30 40 10 20
13
13 21 34 55 89 144 233 377 610 987 1597 2584 4181

Output

Case #1
1100
Case #2
190
Case #3
28316

*/
/*
Bài này hiểu như sau:
cho các nhóm và kích thước tương ứng, ghép tất cả thành 1 nhóm sau cho chi phí ghép nhỏ nhất.
chi phí ghép 2 nhóm có kích thước a và b là a+b
VD: 3 nhóm 100, 200, 500 ghép thành 1 nhóm 800 thì chi phí là: 1100
(ghép 100 với 200, chi phí 300. sau đó ghép 300 với 800 thì chi phí là 1100)

Giải thuật: tham lam
cách làm: sắp xếp dãy từ nhỏ -> lớn, gộp 2 dãy nhỏ nhất thành 1 số và lại tiếp
tục làm tới khi hết dãy
*/

#include<iostream>
#include<stdio.h>

#define NUM_OF_TESTCASES = 2
#define MAX 501

using namespace std;

int T;
int n;
int total;
int cost;
int *a;		// array of spaces

void input() {
	cin >> n;
	a = new int[n+1];
	cost = 0;
	total = 0;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		total += a[i];
	}
}

void swapSpaces(int i, int j) {
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

//Sắp xếp mảng a theo thứ tự tăng dần từ vị trí start đến hết,
//dùng thuật toán selectionSort
void sortSpaces(int start) {
	for(int i = start; i < n; i++) {
		//Tìm phần tử nhỏ nhất trong dãy m[i..n] và đưa nó về đầu của dãy đó
		//chú ý: trong mỗi vòng lặp thì đầu dãy luôn là thằng m[i]
		int minIndex = i;
		int min = a[minIndex];

		for(int j = i+1; j <= n; j++) {
			if(a[j] < min) {
				minIndex = j;
				min = a[j];
			}
		}
		//printf("i = %d, minIndex = %d\n", i, minIndex);
		if(minIndex != i) swapSpaces(i, minIndex);
	}
}

void partition(int k) {
	if(k == n) return;

	//lấy 2 số nhỏ nhất trong dãy a gộp lại (đó là 2 số đầu a[k] và a[k+1]),
	//kq gán cho số a[k+1]
	a[k+1] = a[k] + a[k+1];

	//tăng giá lên
	cost += a[k+1];

	//sắp xếp lại dãy vừa tạo và lại partition tiếp, 
	//tới khi dãy còn 1 phần tử
	sortSpaces(k+1);
	partition(k+1);
}

int main() {
	//freopen("Partition.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		sortSpaces(1);
		partition(1);
		cout << "Case #" << tc << endl << cost << endl;
	}

}

