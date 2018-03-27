/*
Prime Ring
Một vòng gồm N phần tử hình tròn. Trong mỗi hình tròn sẽ chứa một 
số nguyên P và tổng hai số nguyên trong hai hình tròn cạnh nhau 
trên vòng tròn tạo thành một số nguyên tố. Nhiệm vụ của bạn là với
một chuỗi gồm N phần tử số nguyên, đưa ta tổng số cách xếp N phần 
tử đó vào vòng tròn thỏa mãn yêu cầu trên.

Ví dụ

Ta có đầu vào là một dãy gồm 6 phần tử: 1, 2, 3, 4, 5, 6. Thì đầu 
ra sẽ có 2 cách xếp là cách 1: 1 - 4 - 3 - 2 - 5 - 6 và cách 2: 1 - 6 - 5 - 2 -  3 - 4


Input

Dòng đầu liên là T chính là số testcase (T ≤ 100). Mỗi testcase 
sẽ bao gồm 2 dòng:

Dòng đầu tiên là N chính là số lượng phần tử các số nguyên. (3 ≤ N ≤ 16)
Dòng thứ hai là một dãy gồm N số nguyên P ( 1 ≤ P ≤ 50)


Output
Kết quả được in ra trên một dòng theo định sạng sau: “Case number_testcase: answer”

Sample

Input

2

8

1 2 3 4 5 6 7 8

6

1 2 3 4 5 6

 

 

Output

Case 1: 4

Case 2: 2

Cách làm: quay lui. bài này khá dễ
*/
 
#include <iostream>
#include <stdio.h>

#define MAX 17

using namespace std;

int T;
int n;
int a[MAX];
int visited[MAX];	//visited[i] = đã lấy thằng a[i] hay chưa
int res[MAX];
int numOfWay;

void xuongDong() {
	cout<<endl;
}

void input() {
	cin >> n;
	numOfWay = 0;
	for(int i=1; i<=n; i++) {
		cin >> a[i];
		visited[n] = 0;
	}
}

bool checkPrimeNumber(int x) {
	if(x==2) return true;
	for(int i=2; i<=x/2; i++) {
		if(x%i == 0) return false;
	}
	return true;
}

//check xem res[k] = a[i] có đc ko
bool thuocTapUCV(int i, int k) {
	if(visited[i]==1) return false;
	if(checkPrimeNumber(res[k-1] + a[i])) return true;
	return false;
}

void printRes() {
	for(int i=1; i<=n; i++) {
		printf("%d ", res[i]);
	}
	cout<<endl;
}

//tìm số để đặt vào vị trí thứ k (gán cho res[k])
void primeRing(int k) {
	if(k>n) {
		if(checkPrimeNumber(res[n]+res[1])) numOfWay++;
		return;
	}

	for(int i=2; i<=n; i++) {
		if(thuocTapUCV(i, k)) {
			res[k] = a[i];
			visited[i] = 1;

			primeRing(k+1);

			res[k] = -1;
			visited[i] = 0;
		}
	}
}

int main() {
	freopen("PrimeRing_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		res[1] = a[1];
		visited[1] = 1;		//a[1] đã lấy rồi
		primeRing(2);
		cout << "Case " << tc << ": " << numOfWay << endl;
	}
}