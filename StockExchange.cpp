/*
Stock Exchange

John need to earn money, so he decide to buy stock of a company.
Each day, John can either buy stock of the company, sell some or 
all stocks that you have bought, or do nothing.
However each day he can buy at most one stock from this company. 
Very lucky, he has exactly information about the price of stock 
in the next N days from his friend.
But he doesn'n know how to earn maximum money from this information.

Given information about the price of stock in the next N days, 
please help him to earn maximum money.

[Constraint]
In the test case, there are 40% with 3 <= N <= 10, 40% with 10 < N <= 20, 
and 20% with 20 < N <= 30.
Time limit: 5 sec (Java : 10 sec).
Submit limit: 10 times.

[Example]
If he has the information of price in the next 4 days is 8, 5, 1, 10, 
then he can buy stock in the first 3 day with total prices is 14,
and he sell them in the last day to get 30
So total money he can earn is 30-14 = 16.
(dịch: ngày 1,2,3,4, giá cổ phiếu lần lượt là 8, 5, 1, 10. Do đó nên mua
vào ngày 1,2,3 và bán tất cả vào ngày 4, do đó lãi 16 đô-la)
(Mỗi ngày chỉ đc mua tối đa 1 cổ phiếu)
[Input]

There can be more than one test case in the input file. The first 
line has T, the number of test cases.

Then the totally T test cases are provided in the following lines 
(1 <= T <= 50)
In each test case, the first line has an integer N (3 <= N <= 30) 
is the number of days, in the next line is the price of stock for 
the next N days K (1 <= K <= 10000).

[Output]
In the each line, begin with "#x", where x is the test case number, 
following by a space and the maximum money that John can earn.

[Sample]

Input
5
4
8 5 1 10
7
9 9 3 5 6 6 2
10
2 2 6 3 8 7 2 5 3 4
5
9 7 6 3 1
10
7 2 9 10 3 8 10 6 5 4

Output
#1 16
#2 4
#3 23
#4 0
#5 21

Bài này hiểu như sau:
Đọc kỹ lại sẽ tự hiểu nhé! :v

Sử dụng thuật toán tham lam, ta duyệt từ cuối, VD: 2 2 6 3 8 7 2 5 3 4
giả sử tại i = 10, a[i] = 4, ta duyệt về trước, thấy a[9] = 3 < a[i], nên
ta sẽ mua tại ngày đó và bán vào ngày a[i] = 4
tương tự, tại i = 5, a[i] = 8, duyệt về trước thì tất cả đề < 8,
do đó ta sẽ mua tất cả stock từ các ngày 1-4 và bán vào ngày 5
*/

#include<iostream>
#define NUM_OF_TESTCASES = 2
#define MAX 31

using namespace std;

int T;
int n;
int a[MAX];
int money;	//result

void input() {
	money = 0;
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
}

void stock() {
	for(int i = n; i >= 1; i--) {
		//cout << "i = " << i <<", money = " << money << endl;
		int mEH = a[i];		//mEH = max end here
		for(int j = i - 1; j >= 1; j--) {
			if(a[j] <= mEH) {
				money += (mEH - a[j]);
				//cout << "\tj = "<<j<<", money = " << money << endl;
			}
			else {
				i = j + 1;
				break;
			}
			if(j == 1) i = 1;
		}
	}
}


int main() {
	//freopen("StockExchange.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		stock();
		cout << "#" << tc << " " << money << endl;
	}

}

