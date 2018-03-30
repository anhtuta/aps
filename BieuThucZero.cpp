/*
Biểu thức Zero
Cho một số tự nhiên N ≤ 9. Giữa các số từ 1 đến N hãy thêm 
vào các dấu + và - sao cho kết quả thu được bằng 0. Hãy viết 
chương trình tìm tất cả các khả năng có thể.

[Input]
Dòng đầu tiên là T số testcase. T dòng tiếp theo là các 
số tự nhiên N <= 9.

[Output]

Mỗi test case in ra “# ” theo sau là số lượng kết quả tìm 
được mỗi test case. 

[Sample] 
[Input]

1
7

[Output]
#1 6

Giải thích
1-2-3-4-5+6+7=0
1-2+3+4-5+6-7=0
1-23-45+67=0
1-23+4+5+6+7=0
1+2-3-4+5+6-7=0
1+2-3+4-5-6+7=0

*/
#include <iostream>
#include <stdio.h>

#define MAX 11
#define PLUS 0
#define MINUS 1
#define KHONG_THEM_DAU 2	//Ko thêm dấu gì

using namespace std;

int T;
int n;
int answer, sum;
int operation[MAX];

void xuongDong() {
	cout<<endl;
}

void input() {
	cin >> n;
	answer = 0;
	sum = 1;
}

void printOperation() {
	printf("print operation\n");
	for(int i = 2; i <= n; i++) {
		printf("%d ", operation[i]);
	}
	xuongDong();
}

bool checkDebug() {
	return operation[2] == 1 && operation[3]==2 && operation[4]==1 && operation[5]==2 && operation[6]==0 && operation[7]==2;
}

void bieuThucZero(int k) {
	if(k > n) {
		//tính tổng. Có thể tách riêng phần này ra thành 1 hàm cho dễ đọc
		sum = 1;
		for(int i = 2; i <= n; i++) {
			/*if(i==3 && checkDebug()) 
				cout << "start debug. please set a breakpoint here if you want...\n";*/
			if(operation[i] == PLUS) sum += i;
			else if(operation[i] == MINUS) sum -= i;
			else {
				
				//if(checkDebug()) cout << "start...\n";
				//trường hợp này ko thêm dấu gì đằng trước số thứ i trong dãy
				int currOpera = operation[i];	// = KHONG_THEM_DAU
				int index = i;
				int temp = i-1;
				while(currOpera == KHONG_THEM_DAU) {
					temp = temp*10 + index;
					index++;
					if(index == n+1) break;
					currOpera = operation[index];
				}

				if(i == 2) {
					sum = temp;
					//printf("temp = %d\n", temp);
				} else if(operation[i-1] == PLUS) {
					sum = sum - (i-1) + temp;
				} else if(operation[i-1] == MINUS) {
					sum = sum + (i-1) - temp;
				}
				i = index-1;
			}
			//if(checkDebug()) printf("i = %d, sum = %d\n", i, sum);
		}

		if(sum == 0) {
			answer++;
			//printOperation();
			//printf("sum = %d\n", sum);
		}
		return;
	}

	for(int i=0; i<=2; i++) {
		operation[k] = i;
		bieuThucZero(k+1);
	}
}

int main() {
	freopen("BieuThucZero_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		bieuThucZero(2);
		cout << "#" << tc << " " << answer << endl;
	}
}

/*
input: xem file BieuThucZero_input.txt

output:
#1 0
#2 1
#3 1
#4 1
#5 1
#6 6
#7 10
#8 11

*/
