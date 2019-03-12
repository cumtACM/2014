#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int dx[4]={-1,1,0,0};
const int dy[4]={0,0,-1,1};
struct node{
	int x,y,step;
	node(int a,int b,int c){
		x=a;y=b;step=c;
	}
};
queue<node> Q;
int n;

int vis[1010][1010];
bool ok(int x,int y){
	return x>0&&x<=n&&y>0&&y<=n&&vis[x][y]!=-1;
}

int main(void){
	int m,k,d; 
	while(scanf("%d%d%d%d",&n,&m,&k,&d)==4){
		int x,y,need;
		memset(vis,0,sizeof(vis));
		while(!Q.empty()) Q.pop();
		while(m--){
			scanf("%d%d",&x,&y);
			Q.push(node(x,y,0));
			vis[x][y]=-1;
		}
		for(int i=0;i<k;i++){
			scanf("%d%d%d",&x,&y,&need);
			vis[x][y]+=need;
		}
		while(d--){
			scanf("%d%d",&x,&y);
			vis[x][y]=-1;
		}
		int cnt=0;
		long long ans=0;
		while(cnt<k&&!Q.empty()){
			node t=Q.front();Q.pop();
			for(int i=0;i<4;i++){
				int nx=t.x+dx[i],ny=t.y+dy[i];
				if(ok(nx,ny)){
					if(vis[nx][ny]>0){
						ans+=(long long)(t.step+1)*vis[nx][ny];
						cnt++;
					}
					vis[nx][ny]=-1;
					Q.push(node(nx,ny,t.step+1));
				}
			} 
		}
		printf("%lld\n",ans);
	}
    return 0;
}