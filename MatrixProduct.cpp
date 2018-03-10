/*
Bài matrix, nhưng viết = C++, xem đề bài ở file MatrixProduct.java
Cảm ơn Huy Trần đã đóng góp lời giải, nếu ai muốn hẹn hò với Huy Trần có
thể vào đây để kết bạn:
https://www.facebook.com/huycucpro.vip

*/

#include<iostream>
using namespace std;


int T;
int size;
int mulNum;
long long **data;


void print(long long** test){
	for(int i = 0; i < size;i++){
		for(int j = 0;j < size;j++){
			cout<<test[i][j]<<" ";
		}
		cout<<endl;
	}
	//cout<<endl;
}

void input(){
	data = new long long*[size];
	for(int i = 0;i < size;i++){
		data[i] = new long long[size];
	}
	for(int i = 0; i < size;i++){
		for(int j = 0;j < size;j++){
			cin>>data[i][j];
		}
	}
}

long long** Nhan(long long **a,long long **b,int size)
{
	//cout<<"Nhan:"<<endl;
	long long **c;
	c = new long long*[size];
	for(int i = 0;i < size;++i){
		c[i] = new long long[size];
	}
	for(int i = 0;i < size;i++){
		for(int j = 0;j < size;j++){
			long long ans = 0;
			for(int k = 0;k < size;k++){
				ans += ((a[i][k]*b[k][j])% 100000007);

			}
			if(ans > 100000007) ans = ans % 100000007;
			c[i][j] = ans;
		}
	}
	return c;
}

long long** recursive(long long**a,int mul){
//	cout<<"mul = "<<mul<<endl;
	if(mul == 1) return a;
	if(mul % 2 == 0) {
		//cout<<"chan:"<<endl;

		long long **c;
		/*c = new long long*[size];
		for(int i = 0;i < size;++i){
			c[i] = new long long[size];			
		}*/
		//cout<<"dang chan:"<<endl;
		c = recursive(a,mul/2);
		
		//print(c);
		return Nhan(c,c,size);
	}
	else{
		//cout<<"le:"<<endl;
		long long **c;
		/*c = new long long*[size];
		for(int i = 0;i < size;++i){
			c[i] = new long long[size];			
		}*/
	//	cout<<"dang le:"<<endl;
		c = recursive(a,(mul-1)/2);
		
		//print(c);
		return Nhan(Nhan(c,c,size),a,size);
	}
}

int main(){
	freopen("data.txt","r",stdin);
	cin>>T;
	for(int tc = 1;tc <= T;tc++){
		cin>>size;
		cin>>mulNum;
		input();

		long long** test;
		test = recursive(data,mulNum);
		//Matrix test,test2;
		//test.input(size);
		cout<<"Case #"<<tc<<endl;
		print(test);
		//test2 = test;
		//test2 = Nhan(test,test);
		//test2.print();
	}
	return 0;
}