#include <iostream>
#include <stdio.h>

#define MAX 100000

using namespace std;

int arr[MAX];
int n, T;

void input() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
}

void printArray() {
	for (int i = 1; i <= n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

/*=========== Merge sort ===========*/
void mergeArrays(int* a, int L, int M, int R) {
	int i = L, j = M + 1, k = 0;
	int length = R - L + 1;

	/* create temp arrays */
	int* temp = new int[length];

	// merge 2 dãy và lưu vào mảng temp
	// (2 dãy đó là: a[L : M] và a[M+1 : R]
	while (i <= M && j <= R) {
		if (a[i] < a[j]) temp[k++] = a[i++];
		else temp[k++] = a[j++];
	}

	// Copy the remaining elements of L[], if there are any
	while (i <= M) temp[k++] = a[i++];

	// Copy the remaining elements of R[], if there are any
	while (j <= R) temp[k++] = a[j++];

	// copy temp to a
	i = L;
	for (k = 0; k < length; k++) {
		a[i] = temp[k];
		i++;
	}

}

void mergeSort(int* arr, int left, int right) {
	// printf("left = %d, right = %d\n", left, right);

	if (left < right) {
		// Same as (left+right)/2, but avoids overflow for 
		// large left and right 
		int mid = (left + right - 1) / 2;

		// Sort first and second halves
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);

		// then merge these halves
		mergeArrays(arr, left, mid, right);
	}
}

/*======= Merge sort for string ========*/
void mergeArraysString(char str[], int left, int mid, int right) {
	int i = left, j = mid + 1;
	int len = right - left + 1;

	char* temp = new char[len];

	// merge 2 dãy và lưu vào mảng temp
	int k = 0;
	while (i <= mid && j <= right) {
		if (str[i] < str[j]) temp[k++] = str[i++];
		else temp[k++] = str[j++];
	}

	// Copy the remaining elements of L[] or R[]
	while (i <= mid) temp[k++] = str[i++];
	while (j <= right) temp[k++] = str[j++];

	// copy temp to str
	i = left;
	for (k = 0; k < len; k++)
	{
		str[i] = temp[k];
		i++;
	}
}

void mergeSortString(char str[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;

		mergeSortString(str, left, mid);
		mergeSortString(str, mid + 1, right);

		mergeArraysString(str, left, mid, right);
	}
}

/*=========== Quick sort ===========*/
// source: https://www.geeksforgeeks.org/quick-sort/
void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

/*
This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot.
Return: the index (position) of pivot
*/
int partition(int* arr, int low, int high)
{
	int pivot = arr[high];    // pivot 
	int i = (low - 1);  // Index of smaller element

	// duyệt để chuyển hết những thằng <= pivot về đầu dãy
	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (arr[j] <= pivot) {
			i++;    // increment index of smaller element
			swap(&arr[i], &arr[j]);
			//printf("i = %d, j = %d\n", i, j);
		}
	}

	// sau khi chuyển hết những thằng <= pivot về đầu dãy thì chuyển pivot về vị trí
	// ngay sau phần tử cuối cùng của đầu dãy này (dãy gồm các phần tử <= pivot)
	swap(&arr[i + 1], &arr[high]);

	// return index of pivot
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low  --> Starting index,
high  --> Ending index */
void quickSort(int* arr, int low, int high) {
	if (low < high) {
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

int getStringLength(char* str) {
	int len = 0;
	while (*str++) len++;
	return len;
}

int main() {
	freopen("input.txt", "r", stdin);

	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		input();
		quickSort(arr, 1, n);
		printf("#%d ", tc);
		printArray();
	}

	// CHÚ Ý: nếu dùng char *str = new char[1000]; thì sẽ LỖI KHI SORT!
	char str[1000];
	scanf(" %[^\n]s", &str);
	mergeSortString(str, 0, getStringLength(str) - 1);
	cout << "After sort: " << str << endl;
}
