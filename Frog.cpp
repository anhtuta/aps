/*
Bài con cóc

Một đàm nước có n chiếc là nằm sát. Một con ếch đang ngồi 
trên chiếc lá thứ nhât và cần di chuyển đến chiếc lá thứ n. 
Những chiếc lá này có hình tròn và con ếch di chuyển giữa 2 
chiếc lá theo nguyên tắc: 
- Nếu khoảng cách giữa 2 điểm gần nhất của 2 chiếc lá 
không quá 40cm: con ếch có thể nhảy gần sang 
- Nếu khoảng cách giữa 2 điểm gần nhất của hai chiếc lá 
lớn hơn 40cm và không quá 90 cm : con ếch có thể nhảy xa sang. 
- Nếu khoảng cách giữa 2 điểm gần nhất của hai chiếc lá lớn 
hơn 90cm: con ếch không thể nhảy sang.

Một lần nhảy gần hầu như không tốn năng lượng nhưng một 
lần nhảy xa tốn rất nhiều năng lượng. Bởi vậy, đường đi từ 
chiếc lá này sang chiếc lá khác càng tốt nếu số lần nhảy xa 
càng ít, trong trường hợp số lần nhảy xa bằng nhau, đường đi 
có số lần nhảy ít hơn sẽ tốt hơn. Tìm đường đi tốt nhất cho 
con ếch, đưa ra số lần nhảy xa và số lần nhảy gần trên đường 
đi đó.

Dữ liệu vào: Dòng đầu tiên là số lượng testcase T (T <=10) 
Các testcase được đưa ra lần lượt từ 1->T. 
Mỗi testcase bao gồm các dữ liệu: - Dòng thứ nhất chứa số 
nguyên n (n <=200) - Dòng thứ I trong n dòng tiếp theo chứa các 
số nguyên xi, yi, ri với (xi, yi) là tọa độ của chiếc lá thứ I, 
ri là bán kính của chiếc lá thứ I (0<=xi, yi, ri, <=10000, đơn vị cm) 

Dữ liệu ra: Gồm n dòng, dòng thứ I chưa output của test case thứ i: 
đưa ra 2 số nguyên là số lần nhảy xa và số lần nhảy gần trên đường đi 
tốt nhất, trong trường hợp không có đường đi, đưa ra -1. Ví dụ 
Dữ liệu vào
2
2
1 10 10
100 100 15
4
0 10 10
20 60 12
30 10 10
70 10 8

Kết quả
-1
0 2


sample input:
4
2
1 10 10
100 100 15
4
0 10 10
20 60 12
30 10 10
70 10 8
10
41 7 5
110 59 5
38 108 5
65 11 4
81 101 2
112 17 1
21 44 3
126 88 6
49 22 6
14 103 4
40
41 67 7
100 169 3
78 158 6
64 105 6
81 27 1
91 195 1
27 36 3
4 102 7
21 116 7
95 47 6
171 138 1
112 67 1
35 94 4
133 73 3
141 111 2
157 37 1
123 141 6
178 116 5
190 42 2
48 46 6
90 129 4
150 6 1
193 148 2
154 156 4
166 176 2
115 39 7
73 186 3
72 70 6
97 112 5
36 155 2
55 174 7
124 166 1
7 137 2
109 9 1
21 188 4
30 13 7
162 55 2
150 91 2
174 20 5
199 68 6

output:
-1
0 2
1 1
0 5

*/
/*
Cách làm: tính bình phương khoảng cách giữa tâm của 2 lá:
D = (x1 - x2)^2 + (y1 - y2)^2
điều kiện: 
D <= (40 + R1 + R2)^2: nhảy gần
D <= (90 + R1 + R2)^2: nhảy gần
D > bọn trên: ko thể nhảy

do đó cách giải: dùng thuật toán Dijkstra tìm đường đi ngắn nhất giữa
lá 1 và lá n, sau đó tính số bước nhảy. Vì chỉ có ko quá 200 lá
nên giữa 2 lá có thể nhảy gần, ta sẽ cho giá của 2 node này = 1,
còn giá của 2 node (2 lá) mà nhảy xa thì = 1000
Nếu tìm đc đường đi ngắn nhất = 5003 thì nghĩa là: 5 nhảy xa và 3 nhảy ngắn

*/

#include<iostream>
#include<stdio.h>

#define NUM_OF_TESTCASES = 2
#define MAX 201
#define INF 999999

using namespace std;

int T;
int n;
int edgeSize;	//số lượng cạnh của đồ thị
int x[MAX];
int y[MAX];
int r[MAX];
int a[MAX][MAX];	//ma trận trọng số

int d[MAX], p[MAX], mark[MAX];

int s;	//đỉnh nguồn
int t;	//đỉnh đích

void input() {
	cin >> n;
	s = 1;
	t = n;
	for(int i = 1; i <= n; i++) {
		cin >> x[i] >> y[i] >> r[i];
	}

	//tính bình phương khoảng cách giữa các node và lưu vào matrix trọng số
	int hehe;
	for(int i = 1; i <= n; i++) {
		mark[i] = 0;
		for(int j = 1; j <= n; j++) {
			hehe = (x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]);
			if(hehe <= (40 + r[i] + r[j]) * (40 + r[i] + r[j])) a[i][j] = 1;	//nhảy gần
			else if(hehe <= (90 + r[i] + r[j]) * (90 + r[i] + r[j])) a[i][j] = 1000;	//nhảy xa
			else a[i][j] = 0;	//ko thể nhảy
		}
	}
}

bool isMarkEmpty() {
	//cout << "checking if T empty\n";
	//for(int i = 1; i <= n; i++) {
	//	cout << mark[i] << " ";
	//}
	//cout<<endl;
	for(int i = 1; i <= n; i++) {
		if(mark[i] != 0) return false;
	}
	return true;
}

//tìm đường đi ngắn nhất từ đỉnh 1 -> n
void init() {
	for(int i = 1; i <= n; i++) {
		if(i == s) {
			d[i] = 0;
			p[i] = s;
			mark[i] = 0;
			continue;
		}

		d[i] = (a[s][i] > 0 ? a[s][i] : INF);
		p[i] = s;
		mark[i] = i;
	}
}

bool dijkstra() {
	init();
	while(!isMarkEmpty()) {
		int u = 0;
		int min = INF;
		for(int i = 1; i <= n; i++) {
			if(mark[i] == 0) continue;	//chỉ xét các đỉnh ko nằm trong tập T
			if(d[i] < min) {
				u = i;
				min = d[i];
			}
		}

		//Khi không tìm đc đỉnh nào thì chứng tỏ ko có đường đi
		if(u == 0) return false;

		mark[u] = 0;	//remove u khỏi tập T
		//cout << "u = "<<u<<endl;
		if(u == t) break;
		
		for(int v = 1; v <= n; v++) {
			if(v == s) continue;
			if(a[u][v] > 0) {
				if(d[v] > d[u] + a[u][v]) {
					d[v] = d[u] + a[u][v];
					p[v] = u;
				}
				//cout << "dv = " << d[v] << endl;
			}
		}
	}
	return true;
}

int countShortestPath() {
	int currNode = t;
	int len = 0;
	while(currNode != s) {
		//in đường đi
		//cout << currNode << " <- ";
		len += a[currNode][p[currNode]];
		currNode = p[currNode];
	}
	//in đường đi
	//cout << currNode << endl;
	
	return len;
}

int main() {
	freopen("frog.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		if(dijkstra() == false) cout << "-1" << endl;
		else {
			int totalDistance = countShortestPath();
			int nhayDai = totalDistance/1000;
			int nhayNgan = totalDistance % 1000;
			cout << nhayDai << " " << nhayNgan << endl;
		}
	}
}

