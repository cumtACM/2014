#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

using namespace std;

const int N=300003;
struct node{
	int x,y;
	node(int a=0,int b=0){
		x=a;y=b;
	}
}canv[N];
set<int> rows[N];
set<int> cols[N];
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
			canv[i].x=x;canv[i].y=y;
			int r,c;
			if(!recr.count(x)){
				r=recr[x]=row++;
				rrecr[r]=x;
				rows[r].insert(y);
			}else{
				r=recr[x];
				rows[r].insert(y);
			}
			//rows[r].push_back(y);
			if(!recc.count(y)){
				c=recc[y]=col++;
				rrecc[c]=y;
				cols[c].insert(x);
			}else{
				c=recc[y];
				cols[c].insert(x);
			}
			//cols[c].push_back(x);
		}
		/*for(int i=recr.size()-1;i>=0;i--){
			sort(rows[i].begin(),rows[i].end());
		}
		for(int i=recc.size()-1;i>=0;i--){
			sort(cols[i].begin(),cols[i].end());
		}*/
		int ansn=0,anst=0;
		set<int>::iterator it,itt;
		for(int i=recr.size()-1;i>=0;i--){
			int r=rrecr[i];
			for(int j=recc.size()-1;j>=0;j--){
				int c=rrecc[j];
				if(c<=*rows[i].begin()||c>=*(--rows[i].end())) continue;
				if(r<=*cols[j].begin()||r>=*(--cols[j].end())) continue;
				it=rows[i].lower_bound(c);
				int gtr,lsr=0,gtc,lsc=0;
				for(itt=rows[i].begin();itt!=it;itt++) lsr++;
				if(lsr<ansn) continue; 
				gtr=rows[i].size()-lsr;
				if(*it==c){
					gtr--;
				}
				if(gtr<ansn) continue;
				it=cols[j].lower_bound(r);
				for(itt=cols[j].begin();itt!=it;itt++) lsc++;
				if(lsc<ansn) continue;
				gtc=cols[j].size()-lsc;
				if(*it==r) gtc--;
				if(gtc<ansn) continue;
				int ans=min(min(gtr,lsr),min(gtc,lsc));
				if(ans>ansn){
					ansn=ans;
					anst=0;
				}
				else if(ans==ansn) anst++;
			}
		}
		printf("%d\n",q==1?ansn:anst);
	}
	return 0;
}
