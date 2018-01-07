#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map> 
#include<functional>

using namespace std;

struct Deal{
	int bosoc;
	double p;
	int s;
}all[5001];

typedef long long ll;


int main(void){
	map<double,ll> buy,sell;
	set<double,greater<double> > price;
	char op[10];
	int cnt=0;
	while(scanf("%s",op)!=EOF){
		if(strcmp(op,"cancel")==0){
			int sc;
			cnt++;
			scanf("%d",&sc);
			all[sc-1].bosoc=2;
		}
		else if(strcmp(op,"buy")==0){
			all[cnt].bosoc=0;
			scanf("%lf %d",&all[cnt].p,&all[cnt].s);
			cnt++;
		}
		else{
			all[cnt].bosoc=1;
			scanf("%lf %d",&all[cnt].p,&all[cnt].s);
			cnt++;
		} 
	} 
	for(int i=0;i<cnt;i++){
		if(all[i].bosoc==0){
			if(!buy.count(all[i].p)){
				buy[all[i].p]=all[i].s;
				if(!price.count(all[i].p))price.insert(all[i].p);
			} 
			else buy[all[i].p]+=all[i].s;
		}
		else if(all[i].bosoc==1){
			if(!sell.count(all[i].p)){
				sell[all[i].p]=all[i].s;
				if(!price.count(all[i].p))price.insert(all[i].p);
			}
			else sell[all[i].p]+=all[i].s;
		}
	}
	ll ans=0;
	double ansp;
	set<double,greater<double> >::iterator it;
	map<double,ll>::iterator b,s,t;
	for(it=price.begin();it!=price.end();it++){
		b=buy.lower_bound(*it);
		s=sell.upper_bound(*it);
		ll sumb=0,sums=0;
		for(;b!=buy.end();b++){
			sumb+=b->second;
		}
		for(t=sell.begin();t!=s;t++){
			sums+=t->second;
		}
		if(sums<ans) break;
		if(ans<min(sumb,sums)){
			ansp=*it;
			ans=min(sumb,sums);
		}
	}
	printf("%.2lf %lld\n",ansp,ans); 
    return 0;
}
