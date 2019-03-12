#include <cstdio> 
#include <iostream>
#include <cstring>
#include <algorithm>
#include <complex> 
#include <vector>

using namespace std;
typedef long long ll;
typedef complex<ll> Point;
typedef Point Vector;
int Dot(Vector a,Vector b) {
	return real(conj(a)*b);
}
ll Cross(Vector a,Vector b) {
	return imag(conj(a)*b);
}
Point gr[100002];
int ans[100002];
int main(){
	int n;
	scanf("%d",&n);
	int a,b,m=0,res=0;
	for(int i=0;i<n;i++){
		bool flag=true;
		scanf("%d %d",&a,&b);
		gr[i].real((ll)a);
		gr[i].imag((ll)b);
		while(m>1&&Cross(gr[ ans[m-1]]-gr[ans[m-2]],gr[i]-gr[ans[m-2]])<=0) {
			flag=false;
			m--;
		}
		ans[m++]=i;
		if(flag) res++;
	}
	printf("%d\n",res-2);
	return 0;
}