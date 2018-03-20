/*
[Problem]

A planet uses a different number system than us. Values equivalent 
to 0~9 are shown below in the order.
"ZRO", "ONE", "TWO", "THR", "FOR", "FIV", "SIX", "SVN", "EGT", "NIN"

Create a program which accepts the words referring to numbers 0 ~ 9, 
sorting them, and outputting them in the order.

For example, if the input character string is "TWO NIN TWO TWO FIV FOR", 
the program should output "TWO TWO TWO FOR FIV NIN".

[Input]

The first line of the input file provides the number of test cases.

The next line provides the test case number following the ‘#’ symbol. 
It is followed by space then the length of the test case. The test 
case is given in next lines. The words are separated by a space.

The length N of the character string is 100≤N≤10000. 

[Output]

The output file outputs the test case number following the ‘#’ symbol. 

The sorted character string should be output in the next line.


[Input Example]
2
#1 11
TWO NIN TWO TWO FIV FOR SVN ONE EGT NIN ZRO
#2 11
TWO NIN TWO TWO FIV FOR SVN ONE EGT NIN ZRO
 

[Output Example]
#1
ZRO ONE TWO TWO TWO FOR FIV SVN EGT NIN NIN
#2
ZRO ONE TWO TWO TWO FOR FIV SVN EGT NIN NIN

*/
/*
bài này tạm hiểu như sau:
input là 1 chuỗi các từ, mỗi từ tương ứng với 1 số
output: in ra chuỗi số đã được sắp xếp tương ứng với chuỗi ký tự trên
*/

#include <stdio.h>
#include <iostream>

using namespace std;

char a[10001][4];
int n;	//number of words
int x[10001];
int counts[10];

//@param i: first index of array a
int getNumberFromString(int i) {
	if(a[i][1] == 'Z' && a[i][2] == 'R' && a[i][3] == 'O') return 0; 
	else if(a[i][1] == 'O' && a[i][2] == 'N' && a[i][3] == 'E') return 1;
	else if(a[i][1] == 'T' && a[i][2] == 'W' && a[i][3] == 'O') return 2;
	else if(a[i][1] == 'T' && a[i][2] == 'H' && a[i][3] == 'R') return 3;
	else if(a[i][1] == 'F' && a[i][2] == 'O' && a[i][3] == 'R') return 4;
	else if(a[i][1] == 'F' && a[i][2] == 'I' && a[i][3] == 'V') return 5;
	else if(a[i][1] == 'S' && a[i][2] == 'I' && a[i][3] == 'X') return 6;
	else if(a[i][1] == 'S' && a[i][2] == 'V' && a[i][3] == 'N') return 7;
	else if(a[i][1] == 'E' && a[i][2] == 'G' && a[i][3] == 'T') return 8;
	else if(a[i][1] == 'N' && a[i][2] == 'I' && a[i][3] == 'N') return 9;
}

void input() {
	char crap;	//lưu dấu cách
	cin >> n;
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= 3; j++) {
			cin >> a[i][j];
		}
		x[i] = getNumberFromString(i);
	}
}

//sort array x[]
void countingSort() {
	//init
	for(int i = 0; i < 10; i++) {
		counts[i] = 0;
	}

	//do sorting
	for(int i = 1; i <= n; i++) {
		counts[x[i]] += 1;
	}
}

void GNS() {
	countingSort();
}

void printResult() {
	char *currNum = "ZRO";

	for(int i = 0; i < 10; i++) {
		//ĐÉO DÙNG ĐƯỢC strcpy NHÉ!!! F*CK C/C++
		/*if(i==1) strcpy(currNum, "ONE");
		else if(i==2) strcpy(currNum, "TWO");
		else if(i==3) strcpy(currNum, "THR");
		else if(i==4) strcpy(currNum, "FOR");
		else if(i==5) strcpy(currNum, "FIV");
		else if(i==6) strcpy(currNum, "SIX");
		else if(i==7) strcpy(currNum, "SVN");
		else if(i==8) strcpy(currNum, "EGT");
		else if(i==9) strcpy(currNum, "NIN");*/

		if(i==1) currNum = "ONE";
		else if(i==2) currNum = "TWO";
		else if(i==3) currNum = "THR";
		else if(i==4) currNum = "FOR";
		else if(i==5) currNum = "FIV";
		else if(i==6) currNum = "SIX";
		else if(i==7) currNum = "SVN";
		else if(i==8) currNum = "EGT";
		else if(i==9) currNum = "NIN";
		
		for(int j = 1; j <= counts[i]; j++) {
			cout << currNum << " ";
		}
	}
	cout<<endl;
}

int main(void)
{
	int tc, T;
	//setbuf(stdout, NULL);
	//scanf("%d", &T);

	//freopen("GNS.txt", "r", stdin);
	cin >> T;
	for(tc = 1; tc <= T; tc++)
	{
		char crap1, crap2, crap3;
		if(tc >= 10) {	//VD: #10, #11, #38
			cin >> crap1; cin >> crap2; cin >> crap3;
		} else {	//VD: #3, #2
			cin >> crap1; cin >> crap2;
		}
		input();
		GNS();
		cout << "#" <<tc << endl;
		printResult();
		//cout << "#" <<tc << " " << longest_palindrome << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
