/*
[Problem]

A formula consisting of four fundamental arithmetic operations 
can be expressed in a binary tree. Following diagram depicts 
a formula “(9/(6-4))*3” in a binary tree.

If an operator is in a peak, the operator is applied using the 
result of the left subtree and result of right subtree.

Create a program outputting the calculation result of a formula 
when a binary tree consisting of only the operators “+,-, *, /”
and positive integer is given.

All operations are based on real number operations. If the final 
result is not an integer, only the integer part is output. In the 
above, the calculation result is 13.5, thus 13 is output.


[Constraints]

Total number of peaks N is 1≤N≤1000.

[Input]

In the first line of the input file, total number of peaks N(1≤N≤1000) 
of the tree of each test case is given. The peak data are given in the 
next n lines. If the peak is a number, the peak number and the value 
are given. If the peak is an operator, the peak number, operator, peak 
number of left child and peak number of right child are given in that order.

An integer between 1 ~ N is given as the peak number. There is no 
special rule for numbering the peak.However, the number of the 
root peak is always 1.

The adjacent numbers or operators are all separated by the space.

In the above example, if the number 4 corresponds to the 7th peak, 
it is given “7 4”. If the operator ‘/’ corresponds to the 2nd peak, 
it is given “2 / 4 5” since two child nodes are the 4th peak with 
number 9 and 5th peak with operator ‘-‘.

Total of 10 test cases are given.


[Output]

Output the answer to each test case. Each line begins with ‘#x’, 
and the answer is recorded after a line feed. Note that the answer 
is always recorded in an integer form.

[Input Example]

5
1 - 2 3
2 - 4 5
3 10
4 88
5 65
7
1 / 2 3
2 - 4 5
3 - 6 7
4 261
5 61
6 81
7 71

[Output Example]
#1 13
#2 20
*/
/*
Bài này hiểu như sau:
input: cho cây biểu thức
output: kết quả của phép tính

Ví dụ nếu input như sau:
1 - 2 3  	//đỉnh đầu tiên: chứa dấu '-', 2 con trái là đỉnh 2 và 3
2 - 4 5 	//đỉnh 2: chứa dấu '-', 2 con trái là đỉnh 4 v8
3 10 		//đỉnh 3: chứa giá trị = 10
4 88 		//đỉnh 4: chứa giá trị = 88
5 65 		//đỉnh 5: chứa giá trị = 65
Cây trên có thể vẽ thành như sau:

              (-)
              / \
            (-) (10)
            / \
         (88) (65)

Do đó kq của phép tính là: (88-65)-10 = 13
Chú ý: nếu phép chia có dư thì cứ để là số thực, sau đó kq cuối cùng
ép kiểu thành số nguyên, VD: 13.5 thành 13
*/

#include <stdio.h>
#include <iostream>
#define NUM_OF_TESTCASES 10	//change to 10 if you submit code to server
#define MAX 1001
#define BULLSHIT 'z'

using namespace std;

//char str[MAX];			//input
float number[MAX];		//giá trị của 1 node nếu node đó là số
int leftChild[MAX];		//vị trí con trái. VD: leftChild[32] = 71 nghĩa là con trái của node thứ 32 là node thứ 71 (chứ ko phải giá trị của con trái của node 32 bằng 71)
int rightChild[MAX];	//vị trí con phải
char opera[MAX];		//toán tử. VD: nếu opera[19] = '+' nghĩa là node 19 chứa giá trị là dấu cộng
int n;		//amount of nodes
char str[MAX];	//temp variable
int f[MAX];		//hàm tính giá trị phép toán

int myAtoi(char *str)
{
    int res = 0; // Initialize result
  
    // Iterate through all characters of input string and
    // update result
    for (int i = 0; str[i] != '\0'; ++i)
        res = res*10 + str[i] - '0';
  
    // return result.
    return res;
}

void input() {
	cin >> n;

	int nodeIndex;
	for(int i = 1; i <= n; i++) {
		//init
		number[i] = 0;
		leftChild[i] = 0;
		rightChild[i] = 0;

		cin >> nodeIndex;
		scanf("%s", str);
		/*if(strcmp(str, "+") == 0 || strcmp(str,"-")== 0 || 
			strcmp(str,"/") == 0 || strcmp(str,"*")== 0) {*/
		if(str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/') {
				opera[i] = str[0];
				cin >> leftChild[nodeIndex];
				cin >> rightChild[nodeIndex];
		} else {
			number[nodeIndex] = myAtoi(str);
		}
	}
}

float tryMyBest2(int k) {
	float res = -1.0;	//result
	// trường hợp node k là số
	if(number[k] != 0) res = number[k];

	// trường hợp node k là phép toán
	else if(opera[k] == '+') {
		res = tryMyBest2(leftChild[k]) + tryMyBest2(rightChild[k]);
	}
	else if(opera[k] == '-') {
		res = tryMyBest2(leftChild[k]) - tryMyBest2(rightChild[k]);
	}
	else if(opera[k] == '*') {
		res = tryMyBest2(leftChild[k]) * tryMyBest2(rightChild[k]);
	}
	else if(opera[k] == '/') {
		float f1 = tryMyBest2(leftChild[k]);
		float f2 = tryMyBest2(rightChild[k]);
		res = (float) f1 / f2;
	}
	
	return res;
}

void printResult() {
	printf("print result. n = %d\n", n);
	//demo
	for(int i = 1; i <= n; i++) {
		cout << number[i]<<", "<<opera[i]<<", "<<leftChild[i]<<", "<<rightChild[i]<<endl;
	}
	cout << endl;
}

int main(void)
{
	int tc, T;
	//freopen("AlgebraicExpression.txt", "r", stdin);
	T = NUM_OF_TESTCASES;

	for(tc = 1; tc <= T; tc++)
	{
		input();
		//printResult();
		//cout << endl;

		cout << "#" <<tc << " " << (int) tryMyBest2(1) << endl;
		//printResult();
		//cout << "#" <<tc << " " << longest_palindrome << endl;
		//cout << endl<<endl;
	}
	/*int a = 5, b = 9;
	float x = (float) a/b;
	cout<<(float)x;*/

	//return 0;//Your program should return 0 on normal termination.
	/*cout <<"enter something...\n";
	scanf("%s", str);
	cout <<"you enter: "<<str<<endl;

	cout <<"enter something 2...\n";
	scanf("%s", str);
	cout <<"you enter: "<<str<<endl;

	cout <<"enter something 3...\n";
	scanf("%s", str);
	cout <<"you enter: "<<str<<endl;
	int tm = atoi(str);
	tm += 93;
	cout<<tm;*/
}


