#include <stdio.h>
/*
[Question]

A palindrome is a word, phrase, verse, or sentence that reads
the same backward or forwardlike “level” or “radar”.

Create a program which inspects the vertical and horizontal 
lines of a 100x100 character matrix and returns the length of 
the longest palindrome.

[Constraints]

The character in each block is the char type in c language 
and can be ‘A’, ‘B’ or ‘C’.

The character matrix is a square.

ABA and ABBA are both palindromes. A is also a palindrome 
with the length of 1 character.

Only the vertical and horizontal lines should be evaluated. 
In the following example, the word in yellow blocks would a 
palindrome with the length of 7 characters. However, it would 
not be accepted, because it is not a straight line.
<<
	ở đây ko copy được ảnh, thông cảm :). Do đó đã thay = bảng như ở dưới
	bảng này thì các ký tự X,X... hợp thành 1 palindrome nhưng từ palindrome
	này ko hợp lệ vì nó vừa ngang vừa dọc!
>>

oooooooo
oXXXoooo
oooXoooo
oooXXXoo
oooooooo

[Input]

The first line of the input file provides the length of the 
palindrome to search for. The test case is given in next lines.

Total of 10 test cases are given.

[Output]

The output file outputs the test case number following the ‘#’ symbol. 
It is followed by a space, and then the length of the longest palindrome.

[Input Example] 
1
CBCABBAC
BBABCABA
ABCBCACA
BACCAABB
BCBCACBC
CABACCCB
CAAACCAB
CBABACAC
2
CBCABBAC
BBABCABA
ABCBCACA
BACCAABB
BCBCACBC
CABACCCB
CAAACCAB
CBABBABC
3
CBCABBAC
BBABCABA
ABCBCACA
BACCAABB
BCBAACBA
CABACCCA
CAAACCAC
CBACBCBC

[Output Example]
#1 7
#2 8
#3 8
*/

/*
Bài này hiểu như sau:
palindrome là 1 từ mà đọc xuôi giống đọc ngược, VD: radar, level, ABBCCBBA...
input là 1 bảng gồm các ký tự A, B, C (mỗi ô chứa 1 ký tự)
cần tìm từ palindrome dài nhất từ bảng đã cho, và từ palindrome phải ở trên 1 hàng
hoặc 1 cột của bảng, ko được vừa ngang vừa dọc
*/

#include<iostream>
#define WIDTH_LENGTH 8

using namespace std;

char a[101][101];
int longest_palindrome;
int n;


void input() {
	longest_palindrome = 0;
	cin >> n;
	for(int i = 1; i <= WIDTH_LENGTH; i++) {
		for(int j = 1; j <= WIDTH_LENGTH; j++) {
			cin >> a[i][j];
		}
	}
}

void palindrome() {
	/*for(int i = 1; i <= WIDTH_LENGTH; i++) {
		for(int j = 1; j <= WIDTH_LENGTH; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}*/

	// horizontal check
	for(int i = 1; i <= WIDTH_LENGTH; i++) {
		for(int j = 1; j <= WIDTH_LENGTH - 1; j++) {
			// số ký tự chẵn
			if(a[i][j] == a[i][j+1]) {
				int temp = 2;
				for(int k = 1; k < j; k++) {
					if(j+1+k > WIDTH_LENGTH) break;
					if(a[i][j-k] == a[i][j+1+k]) temp += 2;
					else break;
				}
				if(longest_palindrome < temp) longest_palindrome = temp;
			} else {
				// số ký tự lẻ
				int temp = 1;
				for(int k = 1; k < j; k++) {
					if(j+k > WIDTH_LENGTH) break;
					if(a[i][j-k] == a[i][j+k]) temp += 2;
					else break;
				}
				if(longest_palindrome < temp) longest_palindrome = temp;
			}
		}
	}
	
	//vertical check
	for(int i = 1; i <= WIDTH_LENGTH; i++) {
		for(int j = 1; j <= WIDTH_LENGTH - 1; j++) {	//j chạy theo chiều dọc
			// số ký tự chẵn
			if(a[j][i] == a[j+1][i]) {
				int temp = 2;
				for(int k = 1; k < j; k++) {
					if(j+1+k > WIDTH_LENGTH) break;
					if(a[j-k][i] == a[j+1+k][i]) temp += 2;
					else break;
				}
				if(longest_palindrome < temp) longest_palindrome = temp;
			} else {
				// số ký tự lẻ
				int temp = 1;
				for(int k = 1; k < j; k++) {
					if(j+k > WIDTH_LENGTH) break;
					if(a[j-k][i] == a[j+k][i]) temp += 2;
					else break;
				}
				if(longest_palindrome < temp) longest_palindrome = temp;
			}
		}
	}
}

int main(void)
{
	int tc, T;
	//setbuf(stdout, NULL);
	//scanf("%d", &T);

	freopen("palindrome.txt", "r", stdin);
	T = 3;
	for(tc = 1; tc <= T; tc++)
	{
		input();
		palindrome();
		cout << "#" <<tc << " " << longest_palindrome << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
