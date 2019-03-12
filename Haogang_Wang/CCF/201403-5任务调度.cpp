#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
int mn[42][6];
struct node{
	ll a;
	int b,c;
	node(ll d,int e,int f){
		a=d;b=e;c=f;
	}
};
vector<node> dp[401][8];
const int ways[6]={1,2,3,5,6,7};
int main(void){
	int n;
	while(scanf("%d",&n)==1){
		for(int i=0;i<n;i++){
			scanf("%d%d%d%d",&mn[i][0],&mn[i][2],&mn[i][3],&mn[i][5]);
			mn[i][1]=mn[i][0];mn[i][4]=mn[i][3];
		}
		dp[0][0].push_back(node(0LL,0,-1));
		int ans=-1;
		ll d=(1<<n)-1;
		for(int i=0;i<401;i++){
			if(ans!=-1) break;
			for(int j=0;j<8;j++){
				if(ans!=-1) break;
				if(j==4||j==2||j==6) continue;
				for(int id=0;id<dp[i][j].size();id++){
					if(ans!=-1) break;
					for(int k=0;k<n;k++){
						node &t=dp[i][j][id];
						if(t.a==d){
							ans=i;
							break;
						}
						if(!(t.a&(1LL<<k))&&k!=t.c){
							for(int x=0;x<6;x++){
								if((ways[x]&j)==0){
									int nj=j^ways[x];
									if(!(nj&1)&&(nj&2)) continue; 
									int &tr=t.b;
									if(tr&&mn[k][x]>tr){
										int nx=ways[x]==2?1:ways[x];
										nx=ways[x]==6?5:ways[x];
										dp[i+tr][nx].push_back(node(t.a^(1LL<<t.c),mn[k][x]-tr,k));
									}
									else if(tr&&mn[k][x]<tr){
										dp[i+mn[k][x]][j].push_back(node(t.a^(1LL<<k),
											tr-mn[k][x],t.c));
									}
									if(tr){
										int ma=max(mn[k][x],tr);
										dp[i+ma][0].push_back(node(t.a^(1LL<<k)^(1LL<<t.c),
											0,-1));
									}
									else{
										dp[i+mn[k][x]][0].push_back(node(t.a^(1LL<<k),0,-1));
									}
									if(nj!=7&&nj!=3){
										for(int a=0;a<n;a++){
											if((t.a&(1LL<<a))||a==k||a==t.c) continue;
											for(int b=0;b<6;b++){
												if(ways[b]&nj) continue;
												if(mn[k][x]>mn[a][b]){
													dp[i+mn[a][b]][ways[x]].push_back(node(
														t.a^(1LL<<a),mn[k][x]-mn[a][b],k));
												}
												else if(mn[k][x]<mn[a][b]){
													int yj=ways[a]==2?1:ways[a];
													yj=ways[a]==6?5:ways[a];
													dp[i+mn[k][x]][yj].push_back(node(
														t.a^(1LL<<k),mn[a][b]-mn[k][x],a));
												}
												int ma=max(mn[k][x],mn[a][b]);
												dp[i+ma][0].push_back(node(
												t.a^(1LL<<k)^(1LL<<a),0,-1));
											}
										}
									}
								}
							} 
						}
					}
						
				}
			}
		}
		printf("%d\n",ans);
		for(int i=0;i<=n*10;i++)
			for(int j=0;j<8;j++){
				dp[i][j].clear();
			}
	} 
    return 0;
}