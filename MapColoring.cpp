/*
Map Coloring
We consider a geographical map with N countries numbered from 1 to N (1 <= N <=  1000). For every country we know the numbers of other countries which are connected with its border. From every country we can reach to any other one, eventually crossing some borders. Write a program which determines whether it is possible to color the map only in two colors-red and blue in such a way that if two countries are connected their colors are different. The color of the first country is red. Your program must output one possible coloring for the other countries, or show, that such coloring is impossible.

[Input]
The first line is the total number of test cases T.

A test case has two lines. In each test case, the first line has N (the number of countries) and E (the number of border) separated by a space. The next line enumerates E border. A border consists of the two countries it connects. For example, the border connecting countries 5 and 28 is represented by “5 28” or “28 5”. The indices of countries are 1 through N. All adjacent numbers in a line are each separated by a space.

[Output]
Output the each answer in 1 line. Each line starts with ‘#x’, where x means the index of a test case, and puts a space, and prints the answer.

If the coloring is possible, this answer must contain a list of zeros and ones, without any separators between them. The i-th digit in this sequence is the color of the i-th country. 0 corresponds to red color, and one - to blue color. If a coloring is not possible, output the integer −1.

 

[I/O Example]

Input

1                                ← Total test case T
3 2                              ← Starting test case 1
1 2 2 3

Output
#1 010

*/
/*
bài toán tô màu đồ thị:
Tô màu các quốc gia bằng 2 màu sao cho ko có 2 nước chung biên giới mà cùng màu

Bài này ko thể dùng backtrack vì thời gian là 2^1000 (1000 node)
ta dùng queue:
ban đầu ta cho đỉnh 1 vào queue
ở mỗi bước lặp:
	lấy 1 đỉnh k trong queue ra
	nếu đỉn đó chưa đc tô màu thì tô cho nó, sau đó nhét vào queue
	nếu đỉnh đó đã đc tô màu thì check xem nó có trùng màu với k hay ko

input:
7
6 9
3 5 2 6 4 2 6 3 3 1 3 4 6 1 5 1 1 4 
12 12
10 12 8 7 1 7 10 3 6 7 9 5 7 10 11 7 4 11 12 5 2 12 10 4 
46 45
32 10 7 26 5 29 15 45 13 38 5 27 24 41 46 23 12 25 22 21 44 42 40 15 17 34 17 37 27 43 10 25 16 27 13 2 43 8 22 15 17 1 17 4 8 3 36 39 36 6 30 5 40 44 39 4 18 39 1 29 36 15 16 12 38 26 24 13 28 43 41 19 17 33 7 42 11 13 13 31 46 43 6 14 2 35 9 6 35 20 
75 74
34 42 3 26 3 65 15 25 10 75 73 60 59 21 63 23 19 3 74 21 39 44 18 36 28 6 39 53 3 50 3 1 44 50 74 48 12 7 29 58 31 69 1 57 18 68 48 12 15 26 63 36 64 75 21 71 11 9 62 36 72 18 11 26 66 45 71 25 45 26 27 20 47 42 29 19 2 60 44 40 26 13 11 52 11 33 44 34 40 10 8 62 16 38 28 75 5 54 3 38 49 72 71 51 53 17 6 2 62 22 37 48 4 71 39 14 63 30 41 33 54 11 8 75 61 4 56 16 62 55 11 32 20 37 43 22 35 8 14 67 56 31 70 9 46 29 24 73 
108 111
41 56 45 18 60 54 93 51 103 42 35 96 54 102 69 58 73 26 21 23 7 98 28 73 65 45 32 59 64 94 40 60 72 45 78 84 58 29 52 76 37 28 2 54 4 82 38 77 3 69 93 54 31 39 45 107 43 66 100 47 25 101 68 1 48 108 19 26 34 101 89 52 12 74 35 85 52 99 3 32 74 52 6 86 101 9 12 37 15 84 94 51 93 25 17 15 27 38 22 5 10 107 5 44 70 42 53 49 90 35 55 49 65 69 59 71 52 87 22 46 68 22 83 35 31 47 35 94 94 33 61 77 27 94 55 104 3 60 1 41 1 6 53 41 21 43 11 75 72 42 37 24 5 52 106 86 1 95 46 3 48 104 88 22 62 45 81 70 82 87 107 30 39 34 79 89 14 4 106 98 13 40 21 106 16 40 11 102 8 32 62 80 97 41 50 51 78 31 57 73 36 34 11 20 63 31 105 56 91 24 67 56 46 92 103 73 60 107 70 69 51 102 
158 158
132 44 18 44 149 35 117 79 96 3 122 132 17 71 145 118 1 134 26 124 106 6 104 116 35 27 59 157 27 8 91 139 122 47 104 65 30 115 57 79 49 19 107 154 21 28 16 60 37 144 94 157 17 113 19 134 152 51 110 55 56 2 46 2 3 123 92 145 59 137 81 105 110 141 131 156 61 66 146 89 67 61 123 152 119 149 131 89 114 53 56 99 105 22 18 158 54 140 32 143 63 155 44 102 143 36 30 25 105 37 102 22 85 143 134 155 23 58 110 90 110 9 67 32 129 48 139 35 103 56 100 44 99 4 36 121 97 120 91 120 4 114 74 128 41 10 81 151 41 105 149 100 37 104 2 132 127 67 111 149 45 60 135 67 135 130 60 6 155 93 38 94 129 25 15 56 57 20 19 127 135 76 3 72 71 99 131 42 101 139 84 81 128 48 1 98 29 121 37 67 150 95 86 111 104 30 66 152 93 82 92 21 11 26 68 89 57 158 75 113 136 132 94 55 29 150 90 156 101 141 39 50 116 21 3 140 64 48 76 13 114 60 148 99 83 143 70 2 68 14 12 87 138 133 69 121 24 86 118 154 11 132 129 50 64 133 131 108 32 31 40 157 43 153 53 153 5 53 109 82 157 112 88 18 23 26 82 126 80 124 34 25 73 137 54 77 53 52 138 33 110 62 51 125 116 78 142 133 56 87 128 7 147 68 112 98 
206 205
191 163 190 120 20 109 136 151 194 94 61 82 47 126 162 62 6 189 196 99 155 80 83 166 5 172 112 26 32 52 182 55 112 99 86 142 2 84 27 202 109 116 72 105 64 19 203 54 27 2 145 99 8 161 128 129 118 39 23 72 54 163 94 201 192 95 9 80 177 206 174 118 41 111 95 54 27 164 32 197 45 43 5 51 58 8 117 142 98 154 102 74 113 145 147 18 52 113 165 176 169 57 64 165 9 192 9 55 84 93 172 206 48 155 102 179 49 156 54 3 60 16 153 61 196 60 41 1 175 169 42 151 18 10 185 178 179 184 181 60 55 18 159 70 41 176 32 29 152 156 14 16 109 24 174 99 102 76 59 58 27 143 178 9 115 118 41 151 46 206 152 153 166 15 49 188 137 81 18 127 182 115 158 30 152 133 26 97 134 23 141 115 170 67 121 100 67 61 184 204 55 130 159 172 120 194 176 34 133 182 8 18 184 106 177 126 156 83 63 150 140 88 89 78 57 157 25 121 6 20 1 17 65 82 141 168 100 149 159 186 34 143 110 206 164 172 189 87 165 153 180 4 164 131 59 149 77 45 89 172 143 144 6 187 156 134 113 187 39 173 35 108 153 66 85 59 101 55 35 192 30 59 83 135 145 53 199 192 148 87 179 18 163 120 103 18 114 86 60 167 22 39 98 87 190 12 187 169 152 180 75 34 33 198 143 122 49 90 129 154 50 114 162 182 171 117 30 13 117 35 185 104 67 77 44 192 96 4 203 205 185 92 157 140 87 7 48 198 183 147 21 164 13 107 68 177 136 139 200 26 156 56 195 180 79 161 21 36 38 19 82 125 138 76 100 150 139 71 181 81 140 11 194 160 37 179 140 132 90 31 179 124 64 193 168 28 40 19 77 119 91 158 146 109 123 135 153 73 136 69 

output:
#1 -1
#2 001100101001
#3 0100011101110010101110010011111000000110000101
#4 011010010111111100000110001111100001100011011000000010101010100100010111110
#5 01011110010010110011001000001101000111101110111011000000000110100011101011110
1011010101111101111001011011101
#6 01101100101010111001011000111101010111101001100010010110000011111001100000100
01010101111010110100110001000101000010101010101111110100111111011000100100110001
1
#7 00110100101001101110110001110111011010001111011010101001010111001100011110001
10010111011001000100010110000101100110001001111100101110101010011010000110101101
0001010100011111000100001111100010011100110101000

*/

#include <iostream>
#include <stdio.h>

#define MAX 1001
#define INF 9999999

using namespace std;

int T;
int n, e;
int a[MAX][MAX];	//lưu danh sách kề của đồ thị
int color[MAX];
int myQueue[MAX];
int front, rear;

bool isColoring;

void input() {
	cin >> n >> e;
	//init
	isColoring = false;
	for(int i = 0; i <= n; i++) {
		color[i] = -1;
		for(int j = 0; j <= n; j++) {
			a[i][j] = 0;
		}
	}

	int u,v;
	for(int i = 1; i <= e; i++) {
		cin >> u >> v;
		a[u][0]++;
		a[v][0]++;
		a[u][a[u][0]] = v;
		a[v][a[v][0]] = u;
	}
}

/*============ my queue ===============*/
void initQueue() {	
	front = rear = -1;
}

void enQueue(int value) {
	rear++;
	myQueue[rear] = value;
}

int deQueue() {
	front++;
	int temp = myQueue[front];
	if(front == rear) front = rear = -1;
	return temp;
}

bool isEmpty() {
	return front==-1 && rear==-1;
}
/*============ end of my queue ===============*/

void printColor() {
	for(int i = 1; i <= n; i++) {
		cout << color[i];
	}
	cout<<endl;
}

bool mapColoring() {
	while(!isEmpty()) {
		int node = deQueue();
		if(color[node] == -1) {
			color[node] = 0;
		}

		for(int i=1; i<=a[node][0]; i++) {
			//xét các đỉnh kề với node, nếu có đỉnh nào chưa tô màu
			//thì ta tô màu cho nó ngược với màu của node, sau đó nhét nó vào queue.
			//Nếu có đỉnh nào đã đc tô màu thì ta kiểm tra nó với
			//màu của node, nếu trùng nhau thì return false
			if(color[a[node][i]] == -1) {
				color[a[node][i]] = 1 - color[node];
				enQueue(a[node][i]);
			} else if(color[node] == color[a[node][i]]) return false;
		}
	}
	return true;
}

int main() {
	freopen("MapColoring.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		initQueue();
		color[1] = 0;
		enQueue(1);		//cho đỉnh 1 vào queue
		cout << "#" << tc << " ";
		if(mapColoring())
			printColor();
		else cout<<"-1"<<endl;
	}
}
