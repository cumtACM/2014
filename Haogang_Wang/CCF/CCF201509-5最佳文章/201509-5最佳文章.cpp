#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;

const int maxn=1e4+2;
const ll inf=0x3f3f3f3f3f3f3f3f;
int rear;
int ch[maxn][26],f[maxn],End[maxn];

int New(){
	End[rear]=0;
	memset(ch[rear],0,sizeof(ch[rear]));
	rear++;
	return rear-1;
}
void init(){
	rear=0;
	New();
}
void add(char *a){
	int now=0;
	for(int i=0;a[i];i++){
		int c=a[i]-'a';
		if(!ch[now][c]){
			ch[now][c]=New();
		}
		now=ch[now][c];
	}
	End[now]++;
}
void mat_fill(mat& a,ll val){
	for(int i=0;i<a.size();i++)
		for(int j=0;j<a[i].size();j++)
			a[i][j]=val;
}
mat mat_mul(mat&a,mat&b){
	mat c(a.size(),vec(b.size()));
	mat_fill(c,-inf);
	for(int i=0;i<c.size();i++){
		for(int j=0;j<b.size();j++){
			for(int k=0;k<a.size();k++){
				if(a[i][k]+b[k][j]>=0){
					c[i][j]=max(c[i][j],a[i][k]+b[k][j]);
				}
			}
		}
	}	
	return c;
}
mat mat_pow(mat a,ll n){
	mat b=a;n--;
	while(n){
		if(n&1) b=mat_mul(b,a);
		a=mat_mul(a,a);
		n>>=1;
	}
	return b;
}
mat getFail(){
	queue<int> Q;
	f[0]=0;
	for(int c=0;c<26;c++){
		int u=ch[0][c];
		if(u){
			f[u]=0;Q.push(u);
		}
	}
	while(!Q.empty()){
		int r=Q.front();Q.pop();
		End[r]+=End[f[r]];
		for(int c=0;c<26;c++){
			int u=ch[r][c];
			if(!u) ch[r][c]=ch[f[r]][c];
			else{
				Q.push(u);
				int v=f[r];
				while(v&&!ch[v][c]) v=f[v];
				f[u]=ch[v][c];
			} 
		}
	}
	mat a(rear,vec(rear));
	mat_fill(a,-inf);
	for(int i=0;i<rear;i++){
		for(int j=0;j<26;j++){
			int next=ch[i][j];
			a[next][i]=End[next];
		}
	}
	return a;
}
int main(void){
	int n;ll m;
	char str[101];
	while(scanf("%d%lld",&n,&m)==2){
		init();
		for(int i=0;i<n;i++){
			scanf("%s",str);
			add(str);
		}
		mat a=getFail();
		a=mat_pow(a,m);
		ll ans=0LL;
		for(int i=0;i<rear;i++){
			ans=max(a[i][0],ans);
		}
		printf("%lld\n",ans);
	}
    return 0;
}