/*************************************************************************
一开始的读入之后判定能否围成环，不能直接开始推。
然后先求出正确的环的样子，因为不可能存下所有的环，所以默认从1开始推断，1就放在1，先正着存一遍。
答案就是与期待环位置不一致的数的个数，因为其实他们可以构成一个循环排，交换后得到期待的环。

反过来求位置正确的个数，使其最大。
先对每一个点先循环，用算出它的位置到正解位置所需移动的距离%n(注意负数)，将记录的ans[]++。这就是求出最多的相同的。
ans1中第i个存放了一个状态下（1号在i+1,2号在i+2,~~的环)下的最多相同位，ans2对应反过来的环。
 ************************************************************************/
#include <bits/stdc++.h>
using namespace std;
typedef long long lolo;
typedef pair<int,int> pii;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,b,a) for(int i=(b);i>=(a);i--)

const int maxn=50005;
const int INF=0x3f3f3f3f;
const lolo inf=0x3f3f3f3f3f3f3f3f;
template <class T>
void read(T& x) {
	x=(T)0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	do {
		x=(T)(x*10+c-'0');
		c=getchar();
	}while(c>='0'&&c<='9');
}
int a[maxn][2];
int h[maxn],ans1[maxn],ans2[maxn];
int main() {
	int n;
	read(n);
	FOR(i,1,n) {
		read(a[i][0]);
		read(a[i][1]);
	}
	FOR(i,1,n) {
		if((a[a[i][0]][0]!=i&&a[a[i][0]][1]!=i) || (a[a[i][1]][0]!=i&&a[a[i][1]][1]!=i)) {
				puts("-1");
				return 0;
			}
	}
	h[1]=1;
	h[n]=a[1][0];
	h[2]=a[1][1];
	FOR(i,3,n-1) {
		if(a[h[i-1]][0]==h[i-2]) h[i]=a[h[i-1]][1];
		else h[i]=a[h[i-1]][0];
	}
	FOR(i,1,n) {
		ans1[(h[i]-i+n)%n]++;
		ans2[(h[i]+i-1)%n]++;
	}
	int ans;
	FOR(i,0,n-1) {
		if(ans<ans1[i]) ans=ans1[i];
		if(ans<ans2[i]) ans=ans2[i];
	}
	printf("%d\n",n-ans);
	return 0;
}
