#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int main(void) {
	int n;
	while(scanf("%d",&n)!=EOF){
		int ans=0,x,pre;
		for(int i=0;i<n;i++){
			if(i){
				scanf("%d",&x);
				ans=max(ans,abs(x-pre));
				pre=x;
			} 
			else scanf("%d",&pre);
		}
		printf("%d\n",ans);
	}
	return 0;
}
