#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

using namespace std;

const int N=300003;

vector<int> rows[N];
vector<int> cols[N];
map<int,int> recr;
map<int,int> recc;
int rrecr[N],rrecc[N];
int main(void) {
	int n,q;
	while(scanf("%d%d",&n,&q)!=EOF){
		int row=0,col=0;
		recr.clear();
		recc.clear();
		for(int i=0;i<n;i++){
			rows[i].clear();
			cols[i].clear();
		}
		for(int i=0;i<n;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			int r,c;
			if(!recr.count(x)){
				r=recr[x]=row++;
				rrecr[r]=x;
			}else{
				r=recr[x];
			}
			rows[r].push_back(y);
			if(!recc.count(y)){
				c=recc[y]=col++;
				rrecc[c]=y;
			}else{
				c=recc[y];
			}
			cols[c].push_back(x);
		}
		for(int i=recr.size()-1;i>=0;i--){
			sort(rows[i].begin(),rows[i].end());
		}
		for(int i=recc.size()-1;i>=0;i--){
			sort(cols[i].begin(),cols[i].end());
		}
		int ansn=0,anst=0;
		vector<int>::iterator it,itt;
		for(int i=recr.size()-2;i>=ansn;i--){
			int r=rrecr[i];
			for(int j=recc.size()-ansn;j>=ansn;j--){
				int c=rrecc[j]; 
				int lenr=rows[i].size(),lenc=cols[j].size();
				if(c<=rows[i][0]||c>=rows[i][lenr-1]) continue;
				if(r<=cols[j][0]||r>=cols[j][lenc-1]) continue;
				it=lower_bound(rows[i].begin(),rows[i].end(),c);
				int gtr,lsr=0,gtc,lsc=0;
				lsr=it-rows[i].begin();
				if(lsr<ansn) continue; 
				gtr=lenr-lsr;
				if(*it==c){
					gtr--;
				}
				if(gtr<ansn) continue;
				it=lower_bound(cols[j].begin(),cols[j].end(),r);
				lsc=it-cols[j].begin();
				if(lsc<ansn) continue;
				gtc=lenc-lsc;
				if(*it==r) gtc--;
				if(gtc<ansn) continue;
				int ans=min(min(gtr,lsr),min(gtc,lsc));
				if(ans>ansn){
					ansn=ans;
					anst=1;
				}
				else if(ans==ansn) anst++;
			}
		}
		printf("%d\n",q==1?ansn:anst);
	}
	return 0;
}
