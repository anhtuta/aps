/*
Tấn công thành trì
Sau một thời gian dài dưỡng thương  ở Hán Trung, Khổng Minh đã bình phục và quyết định tấn
công vào vào biên giới nước Ngụy để hoàn thành chí nguyện Bắc phạt của mình. Canh giữ biên
giới của Ngụy là  Tư Mã Ý, một viên tướng  cực kỳ khôn ngoan và mưu trí. Trước đó, Tư Mã Ý
đã cho xây dựng một hệ thống  phòng thủ  gồm các  thành  trì  (tòa  thành),  giữa  các  thành  trì  y lại
cho  đắp  các  thành  lũy  (bức  tường)  liên  kết  với  các  thành  trì    nhau  để  bảo  vệ  cho  các  đội  quân
đồn trú bên trong. Vì thế, trận địa phòng ngự của Ngụy quân rất vững chắc, tầng tầng lớp lớp.
Khổng Minh là một nhà quân sự tài ba, y đã vạch ra kế hoạch hoàn mỹ như sau:
Bước  1:  Dùng máy bắn  đá  phá  vỡ  một số  thành  lũy  liên  kết  giữa  các  thành  trì  của  quân  Ngụy,
sao cho không có đội quân nào của Ngụy được bảo vệ kín bởi hệ thống thành lũy.
Bước 2: Dùng nhân tâm kế để đánh giáp lá cà với Ngụy quân.
Theo thông tin thám báo, Khổng Minh biết rằng Tư Mã Ý đã chuẩn bị rất nhiều các máy bắn đá
để  bảo  vệ  các  thành  trì.  Theo  tính  toán  của  Khổng  Minh, để  đảm  bảo  phá  được  một  thành  lũy
thì cần sử dụng số máy bắn đá bằng với tổng số máy bắn đá ở hai đầu thành lũy đó

Hãy  giúp  Khổng  Minh  tính  toán  xem  cần  sử  dụng  ít  nhất  bao  nhiêu  máy  bắn  đá  để  thực  hiện
được bước 1 của chiến dịch trong chí nguyện Bắc phạt của mình.

Input
Dòng đầu tiên là số lượng bộ test T.
Mỗi test gồm được biễu diễn như sau:
Dòng đầu tiên gồm số nguyên M (2 <= M <= 100) là số thành trì của quân Ngụy, các thành trì
được đánh số từ 0 đến M-1.
Tiếp theo là mô tả M thành trì, mỗi thành trì được mô tả trên 2 dòng: dòng thứ nhất gồm 3 số
nguyên dương i (0 <= i <= M-1), u_i (1 <= u_i <= 50), c_i (1 <= c_i <= M-1) lần lượt là số hiệu
của thành trì, số máy bắn đá của quân Ngụy có trong thành trì và số lượng thành lũy liên kết tới
các thành trì khác. Dòng thứ hai gồm c_i số, thể hiện các thành trì có thành lũy liên kết tới
thành trì i.
Output
Với mỗi test, in ra tổng số máy bắn đá ít nhất cần sử dụng để thực hiện bước 1 của chiến dịch

sample input:
12
3
0 1 2
1 2
1 2 2
0 2
2 3 2
0 1
7
0 1 2
2 3
1 2 2
3 4
2 3 2
0 5
3 1 4
0 1 5 6
4 2 2
1 6
5 3 2
2 3
6 1 2
3 4
4
0 1 2
1 2
1 8 2
0 3
2 16 2
0 3
3 12 2
1 2
10
0 1 9
1 2 3 4 5 6 7 8 9
1 1 3
9 0 2
2 2 3
1 0 3
3 3 3
2 0 4
4 1 3
3 0 5
5 2 3
4 0 6
6 3 3
5 0 7
7 1 3
6 0 8
8 2 3
7 0 9
9 3 3
8 0 1
5
0 1 4
1 2 3 4
1 1 3
4 0 2
2 1 3
1 0 3
3 1 3
2 0 4
4 1 3
1 0 3
7
0 1 5
2 3 4 5 6
1 3 5
2 3 4 5 6
2 1 2
0 1
3 1 2
0 1
4 1 2
0 1
5 1 2
0 1
6 1 2
0 1
7
0 1 6
1 2 3 4 5 6
1 3 6
0 2 3 4 5 6
2 1 2
0 1
3 1 2
0 1
4 1 2
0 1
5 1 2
0 1
6 1 2
0 1
7
0 2 3
1 2 3
1 3 3
0 3 4
2 4 3
0 3 5
3 1 6
0 1 2 4 5 6
4 2 3
1 3 6
5 3 3
2 3 6
6 4 3
3 4 5
4
0 1 3
1 2 3
1 2 3
0 2 3
2 2 3
0 1 3
3 1 3
0 1 2
4
3 1 3
0 1 2
2 2 3
0 1 3
1 2 3
0 2 3
0 1 3
1 2 3
7
0 1 1
1
1 2 1
0
2 3 1
3
3 4 1
2
4 5 2
5 6
5 6 2
4 6
6 7 2
4 5
50
0 1 2
1 49
1 1 2
0 2
2 2 2
1 3
3 3 2
2 4
4 4 2
3 5
5 5 2
4 6
6 6 2
5 7
7 7 2
6 8
8 8 2
7 9
9 9 2
8 10
10 10 2
9 11
11 11 2
10 12
12 12 2
11 13
13 13 2
12 14
14 14 2
13 15
15 15 2
14 16
16 16 2
15 17
17 17 2
16 18
18 18 2
17 19
19 19 2
18 20
20 20 2
19 21
21 21 2
20 22
22 22 2
21 23
23 23 2
22 24
24 24 2
23 25
25 25 2
24 26
26 26 2
25 27
27 27 2
26 28
28 28 2
27 29
29 29 2
28 30
30 30 2
29 31
31 31 2
30 32
32 32 2
31 33
33 33 2
32 34
34 34 2
33 35
35 35 2
34 36
36 36 2
35 37
37 37 2
36 38
38 38 2
37 39
39 39 2
38 40
40 40 2
39 41
41 41 2
40 42
42 42 2
41 43
43 43 2
42 44
44 44 2
43 45
45 45 2
44 46
46 46 2
45 47
47 47 2
46 48
48 48 2
47 49
49 49 2
48 0

output:
Case #1
3
Case #2
4
Case #3
9
Case #4
24
Case #5
8
Case #6
8
Case #7
10
Case #8
24
Case #9
8
Case #10
8
Case #11
11
Case #12
2
*/

/*
Cách làm: tìm cây khung lớn nhất, chỉ tìm MỘT lần
trong lúc tìm cần đánh dấu cạnh nào đã ở trong cây khung

sau tất cả các bước trên thì những cạnh ko ở trong cây khung chính là
các cạnh cần bắn phá (các tường thành cần bắn phá) (vì chúng có giá nhỏ nhất
và nếu bỏ chúng đi thì sẽ mất chu trình)
*/

#include <iostream>
#include <stdio.h>

#define NUM_OF_TESTCASES = 2
#define MAX 101

using namespace std;

struct edge {
	int headVertex, tailVertex;
	int weight;
};

int T;
int m;
int edgeSize;	//số lượng cạnh của đồ thị
int p[MAX];		//p[x] = đại diện của tập chứa đỉnh x. Nếu 2 đỉnh a và b cùng cây khung (cùng 1 tập) thì: p[a] = p[b]
struct edge edges[10000];	//các cạnh của đồ thị (mỗi cạnh nối 2 thành trì với nhau (mỗi thành trì là 1 node của đồ thị))
int cannon[MAX];	//số lượng pháo ở mỗi thành trì
int mark[10000];	//mark[k] = đánh dấu xem cạnh k đã ở trong cây khung chưa
//bài này quy ước: 
//mảng p bắt đầu từ 0
//mảng cannon bắt đầu từ 0
//mảng edges bắt đầu từ 1


void input() {
	cin >> m;
	edgeSize = 0;
	int u, node, numOfNeighbor;

	for(int i = 0; i < m; i++) {
		cin >> node;	//node sẽ phải = i
		cin >> cannon[node];	//số lượng pháo của node này
		cin >> numOfNeighbor;	//số lượng thành trì khác mà node này liên kết với
		for(int j = 1; j <= numOfNeighbor; j++) {
			cin >> u;	//đọc từng thành trì khác mà liên kết với node này
			
			bool isExistEdge = false;
			for(int k = 1; k <= edgeSize; k++) {
				//kiểm tra xem đã tồn tại cạnh (node,u) hoặc cạnh (u,node) chưa
				if((edges[k].headVertex == u && edges[k].tailVertex == node) || 
					(edges[k].headVertex == node && edges[k].tailVertex == u)) {
					isExistEdge = true;
					break;
				}
			}

			if(isExistEdge) {
				continue;
			}

			edgeSize++;
			edges[edgeSize].headVertex = node;
			edges[edgeSize].tailVertex = u;
			mark[edgeSize] = 0;
		}
	}

	for(int i = 1; i <= edgeSize; i++) {
		edges[i].weight = cannon[edges[i].headVertex] + cannon[edges[i].tailVertex];
	}
}

void printAllEdges() {
	for(int i = 1; i <= edgeSize; i++) {
		cout << "(" << edges[i].headVertex << ", " << edges[i].tailVertex << ") - " << edges[i].weight << endl;
	}
	cout<<endl;
}

//hoán vị 2 cạnh edges[a] và edges[b]
void swapEdges(int a, int b) {
	int temp = edges[a].headVertex;
	edges[a].headVertex = edges[b].headVertex;
	edges[b].headVertex = temp;

	temp = edges[a].tailVertex;
	edges[a].tailVertex = edges[b].tailVertex;
	edges[b].tailVertex = temp;

	temp = edges[a].weight;
	edges[a].weight = edges[b].weight;
	edges[b].weight = temp;
}

//sắp xếp các cạnh theo thứ tự GIẢM dần về weight (để tìm cây khung lớn nhất),
//dùng thuật toán selectionSort
void sortEdges() {
	int maxIndex;
	for(int i = 1; i <= edgeSize; i++) {
		maxIndex = i;

		//tìm phần tử nhỏ nhất từ i+1 -> n, 
		//sau đó đổi chỗ nó với phần tử thứ i
		for(int j = i + 1; j <= edgeSize; j++) {
			if(edges[maxIndex].weight < edges[j].weight) {
				maxIndex = j;
			}
		}
		if(maxIndex != i) swapEdges(maxIndex, i);
	}
}

void makeSet(int x) {
	p[x] = x;
}

int findSet(int x) {
	if(x != p[x]) {
		p[x] = findSet(p[x]);
	}
	return p[x];
}

//hợp 2 tập, và lấy số nhỏ nhất làm gốc (làm đại diện của tập đó)
//@param x,y: là 2 đỉnh, và ta cần hợp 2 tập hợp mà chứa 2 đỉnh này
//sau đó chọn 1 đỉnh làm đại diện (làm cha) của tập mới đó
//ở đây chọn đỉnh có số hiệu nhỏ hơn làm đại diện
void jointSet(int x, int y) {
	if(x < y) p[findSet(y)] = findSet(x);
	else p[findSet(x)] = findSet(y);
}

// dùng thuật toán Kruskal để tìm cây khung LỚN NHẤT
void destroyCastle() {
	//set đại diện cho từng đỉnh trong đồ thị
	for(int i = 0; i < m; i++){
		makeSet(i);
	}

	//lấy từng cạnh theo độ dài tăng dần
	for(int i = 1; i <= edgeSize; i++) {
		int u = edges[i].headVertex;
		int v = edges[i].tailVertex;

		//Nếu đỉnh u và v ở 2 tập khác nhau
		if(findSet(u) != findSet(v)) {
			//cho cạnh (u,v) vào cây khung hiện tại
			//... do nothing
			//cout << "Cho canh (" << u << ", " << v << ") vao cay khung lon nhat, currEdge = " << i << endl;

			//đánh dấu cạnh này đã ở trong cây khung rồi!
			mark[i] = 1;

			//hợp tập chứa đỉnh u và v lại làm một
			jointSet(u,v);
		}
	}
}

int countCannon() {
	int hehehe = 0;
	for(int i = 1; i <= edgeSize; i++) {
		if(mark[i] == 0) {
			hehehe += edges[i].weight;
		}
	}
	return hehehe;
}

void debugWTF() {
	cout<<"printing p[]...\n";
	for(int i = 0; i < m; i++) {
		cout << p[i] << " ";
	}
	cout<<"printing mark[]...\n";
	for(int i = 1; i <= edgeSize; i++) {
		cout << mark[i] << " ";
	}
}

int main() {
	freopen("castle4.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		sortEdges();
		//printAllEdges();
		destroyCastle();
		cout << "Case #" << tc << endl;
		cout << countCannon() << endl;
		//debugWTF();
	}
}

