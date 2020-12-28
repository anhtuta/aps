#include <iostream>
#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

#define MAX 10001

using namespace std;

int n, T, key;
int arr[MAX];

//  arr phải là 1 dãy sắp xếp tăng dần
void input() {
	cin >> n >> key;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
}

/*
search xem mảng arr có tồn tại giá trị nào = key hay ko.
nếu tồn tại thì return index của phần tử đó, nếu ko thì return -1
*/
int binarySearch(int key) {
	int l = 0;	// chỉ số phần tử đầu tiên của arr
	int r = n - 1;	// chỉ số phần tử cuối cùng của arr

	while (l <= r)
	{
		int m = (l + r) / 2;

		// Check if x is present at mid 
		if (arr[m] == key)
			return m;

		// If x greater, ignore left half 
		if (arr[m] < key)
			l = m + 1;

		// If x is smaller, ignore right half 
		else
			r = m - 1;
	}

	// if we reach here, then element was 
	// not present 
	return -1;
}

// chặt nhị phân:
// tìm trong dãy chỉ số phần tử nhỏ nhất mà >= key
int binaryCutLesser(int key) {
	// tìm kiếm cả mảng nên sẽ tìm từ 0 -> n-1
	int low = 0;
	int high = n - 1;
	int mid;
	int ans = -1;

	while (low <= high) {
		mid = (low + high) / 2;

		if (arr[mid] >= key) {
			ans = mid;

			// tiếp tục tìm phía bên trái (vì dãy sắp xếp tăng dần)
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}

	return ans;
}

// chặt nhị phân:
// tìm trong dãy chỉ số phần tử lớn nhất mà <= key
int binaryCutGreater(int key) {
	// tìm kiếm cả mảng nên sẽ tìm từ 0 -> n-1
	int low = 0;
	int high = n - 1;
	int mid;
	int ans = -1;

	while (low <= high) {
		mid = (low + high) / 2;

		if (arr[mid] <= key) {
			ans = mid;

			// tiếp tục tìm phía bên phải (vì dãy sắp xếp tăng dần)
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}

	return ans;
}

int main() {
	freopen("input.txt", "r", stdin);

	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		input();
		cout << "#" << tc << " " << binarySearch(key) << " " << binaryCutLesser(key) << " " << binaryCutGreater(key) << endl;
	}
}