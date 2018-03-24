/*
Lucky number
Trong một số nước châu Á, 8 và 6 được coi là những chữ số may mắn. 
Bất cứ số nguyên nào chỉ chứa chữ số 8 và 6 được coi là số may mắn, 
ví dụ 6, 8, 66, 668, 88, 886 …. Nguyên là một học sinh rất thích toán.
Nguyên thích các số may mắn nhưng chỉ thích các số có dạng

S = 8…86…6

trong đó S có ít nhất một chữ số và chữ số 6 và 8 không nhất thiết 
phải đồng thời xuất hiện. Ví dụ, 8, 88, 6, 66, 86, 886, 8866 … là 
các số có dạng S.

Cho trước một số nguyên dương X (1 < X < 10 000), Nguyên muốn tìm số
may mắn nhỏ nhất dạng S, có không quá 200 chữ số và chia hết cho X.

Nhiệm vụ của bạn là viết một chương trình tìm số đó cho Nguyên.

Input

Dữ liệu vào gồm nhiều bộ dữ liệu tương ứng với nhiều test. Dòng đầu 
tiên chứa một số nguyên dương không lớn hơn 20 là số lượng các bộ dữ 
liệu. Các dòng tiếp theo chứa các bộ dữ liệu.

Trên mỗi dòng tiếp theo chứa một số nguyên X tương ứng với mỗi bộ dữ liệu.

Ouput

Với mỗi bộ dữ liệu, ghi ra số may mắn dạng S nhỏ nhất chia hết cho X. 
Trường hợp không tồn tại số S có không quá 200 chữ số như vậy, ghi -1.

input:
20
5272
9040
7610
4000
5391
2268
2008
9668
576
134
2162
1792
3518
5198
1968
9774
653
813
8194
2403

output:
Case #1
-1
Case #2
-1
Case #3
-1
Case #4
-1
Case #5
88888888888888888888888888888888888888888888888888888888888888888888888888888888
88888888888888888888888888888888888888888886666666666666666666666666666666666
Case #6
88888888888888888888888888888888888888888888888888888888888888888888888888888888
88888888888888888888888888888888888888888888888888888888888888888888888888888888
88
Case #7
88888888888888888888888888888888888888888888888888
Case #8
-1
Case #9
-1
Case #10
888888866
Case #11
88886666666666666666666666666666666666
Case #12
-1
Case #13
88888888888888888888888888888886666666666666666666666666666666666666666666666666
66
Case #14
8666666666666666666666666666666666666666666666666666666
Case #15
-1
Case #16
8888886666666666666666666666666666
Case #17
88888888888888888888888666666666666
Case #18
66666
Case #19
88888888888888888888888888888888888888888888888888888888866666666666666666666666
6666666666666666666
Case #20
888888888888888888888888888666666666

*/

//Chú ý: lời giải này chạy đúng (100%) trên server của samsung, còn trên
//spoj thì lỗi runtime error

#include <iostream>
#include <stdio.h>

#define MAX 201
#define MAX_LENGTH 200

using namespace std;

int T;
int X;
int leng8, leng6;	//số lượng chữ số 8 và 6 của số cần tìm

int top;
int F[MAX][MAX];
//F[a][b] là số dư của số 88..8866..6 (a số 8, b số 6) khi chia cho X, nếu 
//như F[a][b] == 0 thì xem như ta đã tìm thấy số phải tìm.

//Mỗi vòng lặp thì ta gán số 6 
//vào sau hoặc gán số 8 vào trước để tính F[i][j], 
//đồng nghĩa với việc tăng y lên 1, x lên 1. Ưu tiên với
//viêc thêm số 6 vì ta cần số nhỏ nhất.

//Trường hơp thêm số 6 vào sau thì dư = (dư*10 + 6) % X:
//f[a][b+1] = (f[a][b]*10 + 6) % X;
//còn thêm số 8 vào trước thì dư = (8*(a+b)^10 + dư) % X:
//f[a+1][b] = ((8 * mu10(a+b)) % X + f[a][b]) % X;
//trong đó: hàm mu10(a) = a^10 MOD X

//Ta sẽ tính tất cả các F[i][j], nếu gặp trường hợp F[i][j] = 0 thì
//return: leng8 = i, leng6 = j
//Để tối ưu hơn thì ta có thể tính lần lượt như sau:
//F00, F01, F10, F02, F11, F20, F03, F12, F21, F30...
//Tức là tính theo đường chéo

void input() {
	cin >> X;
	leng8 = 0; leng6 = 0;
	for(int i = 0; i <= MAX; i++) {
		for(int j = 0; j <= MAX; j++) {
			F[i][j] = 0;
		}
	}
}

int mu10(int a) {
	int res = 1;
	for(int i=1; i<=a; i++) {
		res = (res*10)%X;
	}
	return res;
}

bool findLuckyNumber_BFS() {
	//if(a+b > MAX_LENGTH) return false;

	/*while(a + b <= MAX_LENGTH) {
		if(F[a][b+1] == 0) ;
	}*/

	int a,b;
	for(int i=0; i<=MAX_LENGTH; i++) {
		for(int j=0; j<=i; j++) {
			a = j;
			b = i-j;
			//(a,b) là vị trí của ô ta sẽ xét
			//Thứ tự xét các ô: 00, 01, 10, 02, 11, 20, 03, 12, 21, 30... 
			//Tức là xét theo đường chéo của mảng F[][]

			//Với mỗi ô (a,b), ta sẽ tính F[a][[b+1] và F[a+1][b]
			if(F[a][b+1] == 0) {
				F[a][b+1] = (F[a][b]*10 + 6) % X;
				if(F[a][b+1] == 0) {
					leng8 = a;
					leng6 = b+1;
					return true;
				}
			}
			if(F[a+1][b] == 0) {
				F[a+1][b] = (F[a][b] + mu10(a+b)*8) % X;
				if(F[a+1][b] == 0) {
					leng8 = a+1;
					leng6 = b;
					return true;
				}
			}
		}
	}
	return false;
}

int main() {
	freopen("LuckyNumber.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		cout << "Case #" << tc << endl;
		findLuckyNumber_BFS();
		if(findLuckyNumber_BFS()) {
			for(int i=1; i<=leng8; i++) cout<<"8";
			for(int i=1; i<=leng6; i++) cout<<"6";
			cout<<endl;
		}
		else cout << "-1\n";
	}
}
