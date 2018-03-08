/*
Earning Biggest Prize Money 2

The winner in a quiz contest will be given an opportunity to earn bonus prize money. 
Among the given number cards, the winner can choose two number cards and exchange 
their positions as many times as the set number. 

For example, let’s assume five number cards 3, 2, 8, 8, 8 are given as follows and 
the number of exchange is set to 2.

Before exchange:
3, 2, 8, 8, 8

For a first time, positions of 3 in the first card and 8 in the fourth card were 
switched and the order of the cards became 8, 2, 8, 3, 8.

8, 2, 8, 3, 8

Next, positions of 2 in the second card and 8 in the last card 
were switched and the order of the cards became 8, 8, 8, 3, 2.

8, 8, 8, 3, 2

After switch is made as many as the set number, prize money is 
calculated by the weight given to the positions of the cards. 
The prize money is 1 won at right end and it increases by ten 
times as it moves by one digit. When the order of the cards 
becomes 8,8,8,3,2 as shown in the example above, the winner 
will get the bonus prize money of 88832 won.

 
Note that switch must be made as many times as the set number, 
and the switch of the same positions switched can take place. 
In the following case, the number of exchange is set to 1, so 
switch must occur once to get 49 as the result.

9, 4 Switch once-> 4, 9

In case of 94, when switch is made twice, the order goes back 
to the original number which is 94.

Now, compute the biggest amount of prize money the winner can 
get when number cards are switched as many times as the set number.

Input Example
3    // number of testcase
123 1  // number cards, the number of exchange
2737 1 // number cards, the number of exchange
32888 2

Output Example
Case #1
321
Case #2
7732
Case #3
88832

*/
/*
Bài này hiểu như sau:
VD input: cho các số 3,2,8,8,8 và số lần chuyển đổi k = 2 (mỗi lần chuyển đổi chỉ
đc hoán vị 2 số với nhau). Hãy chuyển đổi 2 lần để có đc kq là 1 số lớn nhất
output: sau 2 lần chuyển thì đc số lớn nhất là 88832:
32888 -> 82838 -> 88832
VD input khác: 94, số lần chuyển đổi k = 1
kq: số 49 là lớn nhất
*/
//diep.thinh

#include <stdio.h>
#include<iostream>

using namespace std;

int Ans;
int K;
int len; //số lượng chữ số
int cnt = 0; //số lần đổi chỗ
int value;
char data[7], tmp;

//đổi mảng data thành số
int atoi()
{
	int re = 0;
	for (int i = 0; i < len; i++)
		re = re*10 + data[i]-'0';
	return re;
}

//đổi chỗ chữ số i và j trong mảng data
void Swap(int i, int j)
{
	tmp = data[i];
	data[i] = data[j];
	data[j] = tmp;
}

//Sinh hoán vị
void per(int i)
{
	if (i == len)//Nếu sinh hoán vị đầy đủ thì cập nhật Ans
	{
		value = atoi();
		if(cnt <= K && (K-cnt) % 2 == 0 && Ans < value)
			Ans = value;
		return;
	}
	for (int j = i; j < len; j++)
	{
		//Swap(i, j);//Đổi chỗ S[i] và S[j]
		//cnt += (i != j); //cập nhật số lần đổi chỗ
		//per(i+1); //Phần qui nạp
		//cnt -= (i != j); //reset số lần đổi chỗ
		//Swap(i, j);//Đổi chỗ S[i] và S[j]
		if(i != j) {
			Swap(i, j);
			cnt++;
		}
		per(i+1);
		if(i != j) {
			cnt--;
			Swap(i, j);
		}
	}
}

int main()
{
	int T;
	//freopen("BiggestPrize.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%s %d", data, &K);
		//tìm chiều dài xâu
		len = 0;
		while (data[len] != 0)
			len++;
		//Solve
		Ans = 0;
		per(0);

		printf("Case #%d\n%d\n", tc, Ans);
	}
	return 0;

	//Demo
	//char name[100];
	//scanf("%s", name);
	//cout<<"name = "<<name<<endl;
	//for(int i = 0; i <= 10; i++) {
	//	cout<<name[i]<<" ";
	//	if(name[i] == 0) cout<<"\n1 Name["<<i<<"] = 0"<<endl;		//in dòng này
	//	if(name[i] == '\0') cout<<"\n2 Name["<<i<<"] = '\0'"<<endl;	//in dòng này
	//	if(name[i] == '0') cout<<"\n3 Name["<<i<<"] = '0'"<<endl;	//ĐÉO in dòng này
	//}
}