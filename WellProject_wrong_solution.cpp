/*
Well Project

Our company planned to help dig a well in a place in Africa which suffers from lack of water. 
After lots of research, we could dig the well full of water. 
After this success, we decided not only to dig the well but also to connect pipelines to towns scattered far from the well.


Now your task is to connect all towns together with the well with the minimum length of pipelines. 
Find out the minimum pipeline length.


Time limit : 1 sec (Java : 2 sec)


[Input]
There can be more than one test case in the input file. The first line has T, the number of test cases. 
Then the totally T test cases are provided in the following lines (T ≤ 10 )


In each test case, The size of the matrix (N) is given at the first row. (3 ≤ N ≤ 100)
The distance information of each town is given from the second row to row of N. 
The information is the format of N×N matrix. jth number of ith row is the distance from ith town to jth town. 
The number on a diagonal line is always 0.


[Output]
For each test case, you should print "Case #T" in the first line where T means the case number. For each test case, you should output the minimum pipeline length to connect each town in the first row.


[I/O Example]

Input
2
3
0 1 4
1 0 2
4 2 0
4
0 4 9 21
4 0 8 17
9 8 0 16
21 17 16 0

Output
Case #1
3
Case #2
28 
*/
/*
Bài này chính là bài tìm cây khung nhỏ nhất MST
Ta dùng thuật toán kruskal
*/

/*
Sau đây là lời giải SAI (CHƯA GIẢI XONG VÌ KHÁ PHỨC TẠP PHẦN CHECK LIÊN THÔNG)
*/

#include<iostream>
#include<stdio.h>

#define NUM_OF_TESTCASES = 2
#define MAX 101

using namespace std;

int T;
int n;
int a[MAX][MAX];	//lưu đồ thị = matrix trọng số
int mark[MAX];	//đánh dấu đỉnh để biết nó đã nằm trong cây khung nhỏ nhất hay chưa
int edgeSize;	//số lượng cạnh của đồ thị

struct edge {
	int headVertex, tailVertex;
	int weight;
};

struct edge edges[10000];

void input() {
	cin >> n;
	edgeSize = 0;
	int w;
	for(int i = 1; i <= n; i++) {
		mark[i] = 0;
		for(int j = 1; j <= n; j++) {
			cin >> w;
			//a[i][j] = w;
			if(j >= i+1) {
				edgeSize++;
				edges[edgeSize].headVertex = i;
				edges[edgeSize].tailVertex = j;
				edges[edgeSize].weight = w;
			}
		}
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
	int h = edges[a].headVertex;
	int t = edges[a].tailVertex;
	int w = edges[a].weight;

	edges[a].headVertex = edges[b].headVertex;
	edges[a].tailVertex = edges[b].tailVertex;
	edges[a].weight = edges[b].weight;

	edges[b].headVertex = t;
	edges[b].tailVertex = h;
	edges[b].weight = w;
}

//sắp xếp các cạnh theo thứ tự tăng dần về weight,
//dùng thuật toán selectionSort
void sortEdges() {
	int minIndex;
	for(int i = 1; i <= edgeSize; i++) {
		minIndex = i;

		//tìm phần tử nhỏ nhất từ i+1 -> n, 
		//sau đó đổi chỗ nó với phần tử thứ i
		for(int j = i + 1; j <= edgeSize; j++) {
			if(edges[minIndex].weight > edges[j].weight) {
				minIndex = j;
			}
		}
		if(minIndex != i) swapEdges(minIndex, i);
	}
}


//Kiểm tra xem có đường đi từ a->b hay ko
//nếu có thì return true
bool ifCycle(int a, int b) {
	return true;
}

int connectAllTownsWithTheWellWithTheMinimumLengthOfPipelines() {
	//print mark
	/*for(int i = 1; i <= n; i++) {
		cout<<mark[i]<<" ";
	}*/
	int minLength = 0;
	for(int i = 1; i <= edgeSize; i++) {
		if(mark[edges[i].headVertex] == 1 && mark[edges[i].tailVertex] == 1 && ifCycle(edges[i].headVertex, edges[i].tailVertex)) {
			//ĐÉO LÀM GÌ CẢ! vì 2 đỉnh của cạnh này đã ở trong cây
			//khung nhỏ nhất (MST) rồi, nên ko cần thêm cạnh này vào MST nữa

			//SAI Ở LẬP LUẬN TRÊN! Nếu 2 đỉnh a và b đều ở trong cây MST nhưng
			//chúng ở 2 thành phần liên thông khác nhau thì vẫn cho vào trong MST đc
		} else {
			mark[edges[i].headVertex] = 1;
			mark[edges[i].tailVertex] = 1;
			minLength += edges[i].weight;
		}
		//cout << "i = "<<i<<", minLength = " <<minLength <<endl;
	}
	return minLength;
}

int main() {
	freopen("WellProject.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		sortEdges();
		//printAllEdges();
		cout << "Case #" << tc << endl << connectAllTownsWithTheWellWithTheMinimumLengthOfPipelines() << endl;
	}
}

