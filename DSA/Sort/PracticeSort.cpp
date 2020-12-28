/*
Bài này tập gõ lại hàm sort để nhớ!
Chỉ dùng merge sort
*/

#include <iostream>
#include <stdio.h>

#define MAX 100000

using namespace std;

void copyString(char* from, char* to) {
	int i = 0;
	while (from[i]) {
		to[i] = from[i];
		i++;
	}
	to[i] = '\0';
}

/********* Sort for int array ***********/
void mergeIntArrays(int arr[], int left, int mid, int right) {
	int i = left, j = mid + 1, k = 0;
	int len = right - left + 1;
	int* temp = new int[len];

	while (i <= mid && j <= right) {
		if (arr[i] < arr[j]) temp[k++] = arr[i++];
		else temp[k++] = arr[j++];
	}

	while (i <= mid) temp[k++] = arr[i++];
	while (j <= right) temp[k++] = arr[j++];

	// copy temp to arr
	k = 0;
	for (i = left; i <= right; i++) arr[i] = temp[k++];
}
void sortInt(int arr[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		sortInt(arr, left, mid);
		sortInt(arr, mid + 1, right);

		mergeIntArrays(arr, left, mid, right);
	}
}

/********* Sort for char array ***********/
void mergeCharArrays(char* str, int left, int mid, int right) {
	int i = left, j = mid + 1, k = 0;
	int len = right - left + 1;
	char* temp = new char[len + 1];

	while (i <= mid && j <= right) {
		if (str[i] < str[j]) temp[k++] = str[i++];
		else temp[k++] = str[j++];
	}

	while (i <= mid) temp[k++] = str[i++];
	while (j <= right) temp[k++] = str[j++];
	temp[k] = '\0';

	// copy temp to str
	k = 0;
	for (i = left; i <= right; i++) {
		char c = 'z';
		str[i] = temp[k];
		k++;
	}
}
void sortString(char str[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		sortString(str, left, mid);
		sortString(str, mid + 1, right);

		mergeCharArrays(str, left, mid, right);
	}
}

int getStringLength(char* str) {
	int len = 0;
	while (str[len] != '\0') len++;
	return len;
}

int main() {
	int const A_LEN = 12;
	int a[A_LEN] = { 2,34,23,429,324,49,3291,425,994,3032,23,403 };
	sortInt(a, 0, A_LEN - 1);
	cout << "After sort: " << endl;
	for (int i = 0; i < A_LEN; i++) {
		cout << a[i] << " ";
	}
	cout << endl;

	// If we use this:
	// char *str1 = "iamnotgonnaletyoumakemefeelsadagain";
	// We cannot assign: str1[0] = 'z', because str is just a pointer. It doesn't point anywhere valid
	char str1[1000] = "iamnotgonnaletyoumakemefeelsadagain";

	char str2[1000];
	str2[0] = 't';
	str2[1] = 'h';
	str2[2] = 'i';
	str2[3] = 's';
	str2[4] = 'b';
	str2[5] = 'k';
	str2[6] = 's';
	str2[7] = 'a';
	str2[8] = 'n';
	str2[9] = '\0';

	int str1Len = getStringLength(str1);
	printf("str1Len = %d\n", str1Len);
	sortString(str1, 0, str1Len - 1);
	cout << "After sort: " << str1 << endl;
}