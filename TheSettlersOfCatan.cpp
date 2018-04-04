/*
The Settlers of Catan
Settlers of Catan, một trò chơi của người Đức ở năm 1995, người chơi
tham gia vào cuộc cai trị một hòn đảo bằng việc xây dựng các con đường,
các khu định cư, và các thành phố qua các vùng hoang dã chưa được thám hiểm.

Bạn được một công ty phần mềm thuê để phát triển một phiên bản máy 
tính cho trò chơi này, và bạn được chọn để xây dựng một trong các 
luật đặc biệt của trò chơi.

Khi trò chơi kết thúc, người chơi mà xây dựng được con đường dài 
nhất sẽ được thêm 2 điểm thắng cuộc.

Vấn đề gặp phải ở đây là người chơi thường xây dựng các mạng lưới 
con đường rất phức tạp và không chỉ theo một đường tuyến tính. Vì 
lý do đó, việc xác định con đường dài nhất không phải đơn giản (mặc 
dù những người chơi thường có thể thấy ngay lập tức).

Đối chiếu tới trò chơi gốc, chúng ta sẽ giải quyết một vấn đề đơn 
giản ở đây: Bạn được cho trước một tập các nodes (thành phố) và một 
tập các cạnh (các đoạn đường) có chiều dài là 1 kết nối các nodes.

Con đường dài nhất được định nghĩa như là đường đi dài nhất trong
mạng lưới đường mà không có cạnh nào được dử dụng hai lần. Dù vậy,
các nodes có thể được thăm hơn một lần.


Input

Input sẽ chứa một hoặc nhiều test cases.

Dòng đầu là số lượng test case T.

Dòng đầu tiên của mỗi test cases chứa 2 số nguyên: số nodes N (2<=N<=25) 
và số cạnh M (1<=M<=25). M dòng tiếp theo miêu tả M cạnh. Mỗi cạnh được 
cho bởi các số node kết nối với nhau. Các node được đánh số từ 0 -> N-1. 
Các cạnh không có hướng. Các node có bậc là 3 hoặc nhỏ hơn. Mạng lưới 
không cần thiết phải được kết nối thông suốt với nhau.

Output

Với mỗi test case, in ra chiều dài của con đường dài nhất trên một dòng.

Sample

Input

3

15 16

0 2

1 2

2 3

3 4

3 5

4 6

5 7

6 8

7 8

7 9

8 10

9 11

10 12

11 12

10 13

12 14

3 2

0 1

1 2

15 16

0 2

1 2

2 3

3 4

3 5

4 6

5 7

6 8

7 8

7 9

8 10

9 11

10 12

11 12

10 13

12 14

 

Output

12

2

12

*/
#include <iostream>
#include <stdio.h>

#define MAX 26

using namespace std;

int T;
int n, m;
int a[MAX][MAX];	//lưu đồ thị theo danh sách kề
int visited[MAX][MAX];	//visited[u][v] = đánh dấu xem cạnh uv đã đi qua hay chưa
int maxLongestPath;

void input() {
	cin >> n >> m;
	int u, v;
	for (int i = 1; i <= n; i++) {
		a[i][0] = 0;	//ban đầu các đỉnh i có số hàng xóm = 0 (a[i][0] = 0)
	}
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		u++; v++;	//Do input là các đỉnh bắt đầu từ chỉ số 0, mà tao lại thích các đỉnh bắt đầu từ chỉ số 1 :v
		a[u][0]++;
		a[u][a[u][0]] = v;
		a[v][0]++;
		a[v][a[v][0]] = u;
	}
	maxLongestPath = 0;
}

void resetVisited() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			visited[i][j] = 0;
		}
	}
}

//Cách 1: DFS tất cả các điểm để tìm đường đi dài nhất:
//nodeCost = chi phí khi tới điểm startNode
void DFS(int startNode, int nodeCost) {
	if (maxLongestPath < nodeCost) maxLongestPath = nodeCost;
	//printf("startNode = %d, nodeCost = %d\n", startNode, nodeCost);
	for (int i = 1; i <= a[startNode][0]; i++) {
		int neigh = a[startNode][i];	//NẾU BIÊN neigh LÀ BIẾN GLOBAL THÌ CHẮC CHẮN SẼ SAI, VÌ visited[startNode][neigh] Ở TRƯỚC VÀ SAU KHI GỌI HÀM DFS LÀ KHÁC NHAU
		if (visited[startNode][neigh] == 0) {
			visited[startNode][neigh] = 1;
			visited[neigh][startNode] = 1;
			
			DFS(neigh, nodeCost+1);

			visited[startNode][neigh] = 0;
			visited[neigh][startNode] = 0;
		}
	}
}
void theSettlersOfCatan() {
	for (int i = 1; i <= n; i++) {
		resetVisited();
		//maxLongestPath = 0;
		//ko được reset biến này, vì giả sử đang BFS ở đỉnh 5, tìm được maxLongestPath
		//chính là giá trị lớn nhất, sau đó nếu reset nó thì tử đỉnh 6 trở đi
		//sẽ ko tìm được thằng maxLongestPath nào lớn hơn nữa
		DFS(i, 0);
	}
}

//Cách 2: chỉ cần DFS 2 lần để tìm 2 điểm của đường đi dài nhất
//nhưng cách này ko được điểm tối đa, vì có nhiều thành  phần liên
//thông, nên nếu muốn làm đúng thì phải DFS 2 lần với mỗi thành phần
//liên thông
int firstNode;
void DFS2(int startNode, int nodeCost) {
	if (maxLongestPath < nodeCost) {
		maxLongestPath = nodeCost;
		firstNode = startNode;
	}
	for (int i = 1; i <= a[startNode][0]; i++) {
		int neigh = a[startNode][i];
		if (visited[startNode][neigh] == 0) {
			visited[startNode][neigh] = 1;
			visited[neigh][startNode] = 1;

			DFS2(neigh, nodeCost + 1);

			visited[startNode][neigh] = 0;
			visited[neigh][startNode] = 0;
		}
	}
}
void theSettlersOfCatan_smarterWay() {
	resetVisited();
	DFS2(1, 0);
	resetVisited();
	maxLongestPath = 0;	//phải reset biến này! Chú ý là cách 1 ko được reset

	DFS2(firstNode, 0);
}

int main() {
	FILE *stream; freopen_s(&stream, "TheSettlersOfCatan2.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		input();
		theSettlersOfCatan_smarterWay();	//cách giải này sai, chỉ đúng với trường hợp đồ thị liên thông
		theSettlersOfCatan();
		cout << maxLongestPath << endl;
	}
}


/*
input:
20
15 16
0 2
1 2
2 3
3 4
3 5
4 6
5 7
6 8
7 8
7 9
8 10
9 11
10 12
11 12
10 13
12 14
3 2
0 1
1 2
15 16
0 2
1 2
2 3
3 4
3 5
4 6
5 7
6 8
7 8
7 9
8 10
9 11
10 12
11 12
10 13
12 14
3 3
0 1
0 2
1 2
2 1
0 1
10 3
0 4
2 4
4 9
10 6
1 4
1 6
1 7
2 3
2 5
6 7
7 6
0 4
0 5
1 2
1 5
2 4
3 4
8 9
0 2
0 6
1 2
1 4
2 6
3 4
4 5
5 6
5 7
8 12
0 4
0 6
0 7
1 2
1 3
1 5
2 3
2 4
3 4
5 6
5 7
6 7
18 18
0 3
0 11
0 12
1 17
2 3
2 16
4 15
4 16
5 7
5 8
6 9
7 8
7 15
9 14
10 11
10 17
11 17
14 15
15 13
0 11
1 3
1 5
2 10
3 8
4 9
4 12
4 13
5 9
5 12
6 8
7 12
8 9
11 1
5 6
15 19
0 1
0 4
0 9
1 10
2 3
2 5
2 13
3 4
3 5
4 6
5 10
6 8
7 12
7 14
8 12
9 11
10 14
11 12
11 13
13 18
0 2
0 6
0 8
1 2
1 9
1 10
2 3
3 4
3 8
4 6
4 12
5 7
5 10
5 12
6 12
7 9
7 10
9 11
25 18
0 9
1 22
2 3
2 6
2 11
3 8
4 16
5 20
7 17
11 16
12 14
12 19
13 21
16 21
17 20
17 24
18 20
19 24
21 20
0 4
0 12
1 8
1 19
2 12
2 15
3 7
3 17
7 10
7 18
8 11
8 18
9 11
9 14
10 11
10 17
12 20
13 15
14 15
17 18
24 2
0 15
4 11
22 24
0 8
0 15
0 21
1 10
1 12
1 18
2 6
2 9
2 19
3 17
3 19
4 6
5 13
5 19
5 20
7 15
7 18
7 21
9 20
11 13
11 14
11 21
12 15
18 20
22 9
0 20
2 11
2 20
4 9
7 15
9 19
14 17
16 18
19 20
*/