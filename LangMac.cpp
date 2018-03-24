#include <iostream>
#include <stdio.h>

#define MAX 21

using namespace std;

int a[MAX][MAX];
int n;

void input() {
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			cin >> a[i][j];
		}
	}
	
}

int main() {
	freopen("LangMac_input.txt", "r", stdin);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		input();
		scoreBackTracking(1);
		cout << "Case " << tc << endl;
		if(isFoundSolution)
			cout << soTruongHopThoaMan << "\n";
		else cout << "-1\n";
	}
}
