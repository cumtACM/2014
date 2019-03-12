#include <cstdio> 
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std; 


const int mod=1e9+7;
const int maxn=1<<8;
typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;
mat T1,T2; 


int m,tot,man; 
ll n;

void mat_fill(mat& a,ll val){
	for(int i=0;i<a.size();i++)
		for(int j=0;j<a[i].size();j++)
			a[i][j]=val;
}
mat mat_mul(mat &a,mat &b){
	mat c(a.size(),vec(b[0].size()));
	mat_fill(c,0);
	for(int i=0;i<c.size();i++){
		for(int j=0;j<c[i].size();j++){
			for(int k=0;k<a[0].size();k++){
				if(a[i][k]*b[k][j]>0){
					c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
				}
			}
		}
	}	
	return c;
}

mat mat_pow(mat& a,ll n){
	mat b=a;n--;
	while(n){
		if(n&1) b=mat_mul(b,a);
		a=mat_mul(a,a);
		n>>=1;
	}
	return b;
}
void dfs(int x,int y,int k,int z){
	if(k==m){
		T1[y][x]=z;return;
	} 
	dfs(x<<1,y<<1|1,k+1,z);
	if(k+2<=m){
		dfs(x<<2,y<<2|3,k+2,z);
		dfs((x<<2)|1,y<<2,k+2,z);
		dfs((x<<2)|2,y<<2,k+2,z);
		dfs((x<<2)|3,y<<2|1,k+2,z);
		dfs((x<<2)|3,y<<2|2,k+2,z);
	}
	if(k+3<=m){
		dfs(x<<3|7,y<<3,k+3,2*z);
	} 
}
ll solve(ll r,int c){
	tot=1<<c;man=tot-1;
	T1.resize(tot);
	for(int i=0;i<tot;i++) T1[i].resize(tot);
	mat_fill(T1,0);
	mat T2(tot,vec(1));
	mat_fill(T2,0);
	dfs(0,0,0,1);
	T2[man][0]=1;
	mat temp=mat_pow(T1,r);
	mat ans=mat_mul(temp,T2);
	return ans[man][0];
}
int main(){
	while(scanf("%lld%d",&n,&m)==2){
		if(n*m%3){
			printf("0\n");
			continue;
		}
		printf("%lld\n",solve(n,m));
	}
	return 0;
} 
