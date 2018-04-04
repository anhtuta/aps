
/*
Pizza Location
Our friend Picko is very reach and he wants to open lots of restaurants 
with delivery. The main food will be, of course, pizza. He has certain 
number of potential locations for the restaurants, and he knows the 
locations of the solitaires with lots of people which will often be his 
customers. Delivery of each restaurant will cover all the solitaires in 
given radius.

Picko can open only limited number of restaurants, and he wants that 
restaurants on the locations which will cover maximal number of people 
in solitaires.

Write a program that will calculate maximal number of people which we 
can cover with delivery.



Input
In the first line of the input file there are two integers K and R, 
separated with space, number of restaurants and radius of delivery, 
1 ≤ K ≤ 10, 1 ≤ R ≤ 500.

In the second line there is integer M, number of locations, K ≤ M ≤ 20.

In each of the next M lines there are two integer X and Y, separated 
with space, coordinates of each location, -1000 ≤ X,Y ≤ 1000.

In the next line there is integer N, number of solitaires, 1 ≤ N ≤ 100.

In each of the next N lines there are three integers X, Y and S, separated
with space, X and Y are coordinates of each solitaire, and S is number 
of people in that solitaire, -1000 ≤ X,Y ≤ 1000, 1 ≤ S ≤ 100.

We consider that solitaire is in radius of some restaurant if distance 
between them is less or equal to R. There are no two locations of 
restaurants on the same place.

Output
In only line of the output file we have to write maximal number from the 
text above.


Sample

Input

3

2 2

3

1 0

4 0

7 0

4

0 0 1

3 0 7

5 0 9

8 0 1

2 2

3

-2 0

0 1

3 0

8

-3 1 1

-3 0 1

-3 -1 1

-2 -1 1

0 0 3

0 2 1

2 1 3

4 0 2

3 3

5

0 0

1 6

2 3

6 6

7 2

8

0 1 2

0 5 3

0 6 1

1 0 1

3 2 3

3 6 2

6 2 4

8 6 3



Output

#1 18

#2 12

#3 17



*/
#include <iostream>
#include <stdio.h>

#define MAX 101
#define INF 999999

using namespace std;

struct Point {
	int x, y;
};
struct Solitaire {
	int x, y;	//tọa độ của khu dân cư
	int population;		//dân số của khu dân cư
};
int T;
int k;	//số lượng nhà hàng
int r;	//bán kính tối đa mà mỗi nhà hàng có thể giao pizza
int m;	//số lượng địa điểm (location)
Point locations[21];	//tập các địa điểm
int n;	//số lượng khu dân cư (solitaire)
Solitaire solitaires[101];	//tập các khu dân cư
int mark[21];	//mark[a] = đánh dấu xem location[a] có nhà hàng nào hay chưa
int disSolitLocale[101][21];	//disSolitLocale[a][b] = distance between solitaires[a] and locations[b]
//int res[11];	//vị trí đặt của các nhà hàng
int res[21];	//res[a] = 1 nghĩa là locations[a] có đặt 1 nhà hàng, = 0 nghĩa là ko đặt gì

int currPeople;	//số lượng người dân mà các nhà hàng có thể giao hàng đc
int maxPeople;	//số lượng người dân lớn nhất mà các nhà hàng có thể giao hàng đc

int numOfRestaurants;	//số lượng nhà hàng đã đc đặt ở 1 location nào đó
//tính bình phương khoảng cách giữa 2 điểm
int getDistance(int x1, int y1, int x2, int y2) {
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}

void input() {
	int xwtf, ywtf, popu;
	maxPeople = 0;
	numOfRestaurants = 0;

	cin >> k >> r;
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> xwtf >> ywtf;
		Point p;
		p.x = xwtf; p.y = ywtf;
		locations[i] = p;
		mark[i] = 0;
		res[i] = 0;
	}
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> xwtf >> ywtf >> popu;
		Solitaire s;
		s.x = xwtf; s.y = ywtf; s.population = popu;
		solitaires[i] = s;
	}
	//count distance and save result for later usage
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			disSolitLocale[i][j] = getDistance(solitaires[i].x, solitaires[i].y, locations[j].x, locations[j].y);
		}
	}
}

//Cách đầu tiên là quay lui theo nhà hàng, do có tối đa là 10 nhà hàng và 20 địa điểm,
//mỗi nhà hàng có thể đặt ở 1 trong 20 địa điểm đó, nên độ phức tạp của thuật toán là:
//  20*19*18*17*...*11*10 = 6,700,000,000,000 = 6700 tỷ phép toán
//Rõ ràng cách này ko thể thực hiện vì quá tồi! Code của nó như sau:

//void countTotalPeople() {
//	currPeople = 0;
//	//duyệt các khu dân cư
//	for (int i = 1; i <= n; i++)
//	{
//		//nếu khu dân cư nào trong bán kính của 1 nhà hàng thì update currPeople
//		//duyệt các nhà hàng
//		for (int j = 1; j <= k; j++)
//		{
//			//int distance = getDistance(solitaires[i].x, solitaires[i].y, locations[res[j]].x, locations[res[j]].y);
//			//printf("distance between solitaires[%d] and locations[%d] = %d, solitaires = (%d, %d), locations = (%d, %d)\n", i, res[j], distance, solitaires[i].x, solitaires[i].y, locations[res[j]].x, locations[res[j]].y);
//			if (disSolitLocale[i][res[j]] <= r*r) {
//				currPeople += solitaires[i].population;
//				break;
//			}
//		}
//	}
//
//	if (maxPeople < currPeople) maxPeople = currPeople;
//	//printf("maxPeople = %d\n", maxPeople);
//	/*
//	for (int i = 1; i <= k; i++)
//		printf("%d ", res[i]);
//	cout << endl;*/
//}

//tìm vị trí để đặt nhà hàng thứ a
//void pizza(int a) {
//	printf("a = %d\n", a);
//	if (a > k) {
//		countTotalPeople();
//		return;
//	}
//	for (int i = 1; i <= m; i++) {
//		if (mark[i] == 0) {
//			printf("\ti = %d\n", i);
//			res[a] = i;
//			mark[i] = 1;
//			pizza(a + 1);
//			res[a] = 0;
//			mark[i] = 0;
//		}
//	}
//}

//Cách 2: quay lui theo địa điểm, do có tối đa 20 địa điểm và 10 nhà hàng,
//mỗi địa điểm có thể đặt nhà hàng hoặc ko, nên độ phức tạp = 2^20 = 1,000,000
//rõ ràng nhanh hơn rất nhiều!
void countTotalPeople() {
	currPeople = 0;
	//duyệt các khu dân cư
	for (int i = 1; i <= n; i++)
	{
		//nếu khu dân cư nào trong bán kính của 1 nhà hàng thì update currPeople
		//duyệt các địa điểm
		for (int j = 1; j <= m; j++)
		{
			//int distance = getDistance(solitaires[i].x, solitaires[i].y, locations[res[j]].x, locations[res[j]].y);
			//printf("distance between solitaires[%d] and locations[%d] = %d, solitaires = (%d, %d), locations = (%d, %d)\n", i, res[j], distance, solitaires[i].x, solitaires[i].y, locations[res[j]].x, locations[res[j]].y);
			
			if (res[j] == 1) {
				//có nhà hàng trong locations[j],
				if (disSolitLocale[i][j] <= r * r) {
					currPeople += solitaires[i].population;
					break;
				}
			}
			
		}
	}

	if (maxPeople < currPeople) maxPeople = currPeople;
	//printf("maxPeople = %d\n", maxPeople);
	/*
	for (int i = 1; i <= k; i++)
	printf("%d ", res[i]);
	cout << endl;*/
}

//tại locations[a] có đặt nhà hàng hay ko
void pizza(int a) {
	if (a > m) {
		if (numOfRestaurants == k) {
			countTotalPeople();
		}
		return;
	}
	for (int i = 0; i <= 1; i++)	//i = 1 nghĩa là có đặt nhà hàng ở locations[a]
	{
		res[a] = i;
		if (i == 1) numOfRestaurants++;
		pizza(a + 1);
		if (i == 1) numOfRestaurants--;
	}
}

int main() {
	//FILE *stream; freopen_s(&stream, "PizzaLocation_input.txt", "r", stdin);
	freopen("PizzaLocation_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		input();
		pizza(1);
		cout << "#" << tc << " " << maxPeople << endl;
	}
}

/*
output:
#1 185
#2 302
#3 7
#4 207
#5 100
#6 165
#7 326
#8 283
#9 145
#10 451
#11 326
#12 105
#13 418
#14 162
#15 232
#16 223
#17 419
#18 103
#19 68
#20 402
#21 55
#22 258
#23 196
#24 179
#25 369
#26 379
#27 326
#28 364
#29 360
#30 26
#31 17
#32 178
#33 61
#34 276
#35 268
#36 275
#37 137
#38 23
#39 345
#40 75
#41 413
#42 37
#43 122
#44 194
#45 380
#46 97
#47 84
#48 312
#49 359
#50 74

*/