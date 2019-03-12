#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;


const int inf=0x3f3f3f3f;
vector<int> mc,r,u,v,w;
int dist[505][505],path[505][505],pa[505],edge[505][505];
bool is[505],vis[505][505],c;
bool cmp(int i,int j){
	return w[i]<w[j];
}
int findp(int x){
	return pa[x]==x?x:pa[x]=findp(pa[x]);
}
int ans;
void rt(int i,int j){
	if(!path[i][j]){
		if(!vis[i][j]){
			ans+=edge[i][j];
			vis[i][j]=vis[j][i]=true;
		}
	}
	else{
		rt(i,path[i][j]);
		rt(path[i][j],j);
	}
}
int main(){	
	int n,m,p,T;
	scanf("%d",&T);
	while(T--){
		ans=0;
		mc.clear();r.clear();u.clear();v.clear();
		w.clear();
		scanf("%d %d %d",&n,&m,&p);getchar();
		memset(edge,inf,sizeof(edge));
		memset(path,0,sizeof(path));
		memset(vis,false,sizeof(vis));
		for(int i=1;i<=n;i++){
			char x;
			pa[i]=i;
			x=getchar();
			if(x=='1'){
				is[i]=true;
				mc.push_back(i);
			}else is[i]=false;
		}
		getchar();
		for(int i=0;i<m;i++){
			int a,b,w;
			scanf("%d %d %d",&a,&b,&w);
			edge[a][b]=edge[b][a]=w;
		}
		memcpy(dist,edge,sizeof(dist));
		for(int i=1;i<=n;i++){
			for(int j=1;j<n;j++){
				if(i==j) continue; 
				for(int k=j+1;k<=n;k++)
					if(k!=i&&dist[j][i]!=inf&&dist[i][k]!=inf){
						if(dist[j][k]>dist[j][i]+dist[i][k]){
							dist[j][k]=dist[k][j]=dist[j][i]+dist[i][k];
							path[j][k]=path[k][j]=i;
						}
					}
			}
		}
		for(int i=0;i<mc.size();i++){
			for(int j=i+1;j<mc.size();j++){
				int x=mc[i],y=mc[j];
				if(dist[x][y]!=inf){
					r.push_back(r.size());
					u.push_back(x);
					v.push_back(y);
					w.push_back(dist[x][y]);
				}
			}
		}
		sort(r.begin(),r.end(),cmp);
		for(int i=0;i<r.size();i++){
			int t=r[i];
			int x=findp(u[t]),y=findp(v[t]);
			if(x!=y){
				pa[x]=y;
				rt(u[t],v[t]);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}