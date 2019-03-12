#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int mod=1e9+7;
typedef long long ll;
void gcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b){
		d=a;x=1;y=0;
	}
	else{
		gcd(b,a%b,d,y,x);y-=x*(a/b);
	}
}
ll Inv(ll a,ll n){
	ll d,x,y;
	gcd(a,n,d,x,y);
	return d==1?(x+n)%n:-1;
}

ll inv[10002];
int main(void){
	int n;
	while(scanf("%d",&n)==1){
		ll ans=0;
		for(int i=2;i<n-1;i++){
			inv[i]=Inv(i,mod);
		}
		for(int i=2;i<n-1;i++){
			ll temp=1;
			for(int j=n-1;j>=n-i;j--){
				temp=(temp*j)%mod;
			}
			temp=(temp*(i-1)*(n-i-1))%mod;
			for(int j=2;j<=i;j++){
				temp=(temp*inv[j])%mod;
			}
			ans=(ans+temp)%mod;
		}
		printf("%lld\n",ans);
	}
    return 0;
}