/*
Checking cube
Given a integer N. Find number of possible ways to represent N as a 
sum of at most five cubes.
Cho 1 số nguyên N, tìm só cách biểu diễn N thành tổng của
5 số lập phương

Input
First line contains N.
1<=N<=125000.

Output
Output the result

Sample Input
4
1
64
905
15436

Output
#1 1
#2 2
#3 0
#4 12

Giải thích:
+ Cách 1: 64 = 27 + 27 + 8 + 1 + 1
+ Cách 2: 64 = 64 + 0  + 0 + 0 + 0

Bài này quay lui, chú ý: cách chọn số sau luôn >= số trước
*/
#include <iostream>
#include <stdio.h>

#define MAX 6

using namespace std;

int T;
int n;
int answer, sum;
int value[MAX];

void xuongDong() {
	cout<<endl;
}

void input() {
	cin >> n;
	answer = 0;
	sum = 0;
}

void printValue() {
	for(int i=1; i<=5; i++) {
		cout << value[i] << " ";
	}
	xuongDong();
}

//check xem số i^3 có cho vào vị trí thứ k đc hay ko
bool thuocTapUCV(int i, int k) {
	//số đằng sau phải lớn hơn hoặc bằng số đằng trước
	if(k==1) return true;
	if(value[k-1] > i*i*i) return false;
	return true;
}

int currIndex;
//cho khối thích hợp vào vị trí k
//khối ở đây là 1 số lập phương, VD: 0,1,8,27,64,125
void checkingCube(int k) {
	if(k > 5) {		//tối đa 5 số thôi!
		if(sum == n) {
			answer++;
			//printValue();
		}
		return;
	}

	for(int i = currIndex; i <= 50; i++) {
		if(thuocTapUCV(i, k)) {
			sum += i*i*i;
			value[k] = i*i*i;
			currIndex = i;
			if(sum <= n) checkingCube(k+1);
			sum -= i*i*i;
		}
	}
}

int main() {
	freopen("CheckingCube_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		sum = 0;
		currIndex = 0;
		checkingCube(1);
		cout << "#" << tc << " " << answer << endl;
	}
}

/*
input: xem file CheckingCube_input.txt

output:
#1 39
#2 18
#3 1
#4 12
#5 1
#6 2
#7 4
#8 8
#9 15
#10 4
#11 13
#12 8
#13 9
#14 13
#15 31
#16 24
#17 2
#18 9
#19 4
#20 10
#21 7
#22 10
#23 14
#24 8
#25 21
#26 34
#27 3
#28 17
#29 13
#30 1
#31 2
#32 3
#33 6
#34 36
#35 1
#36 16
#37 8
#38 2
#39 11
#40 7
#41 26
#42 19
#43 11
#44 23
#45 27
#46 2
#47 19
#48 2
#49 16
#50 4

*/