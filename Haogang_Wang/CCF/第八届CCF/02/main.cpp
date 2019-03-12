#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int ex[20][6];
int main(void) {
	int n;
	while(scanf("%d",&n)!=EOF){
		memset(ex,false,sizeof(ex));
		for(int i=0;i<20;i++) ex[i][0]=5;
		while(n--){
			int x;
			scanf("%d",&x);
			int i;
			bool flag=true;
			int cnt=0;
			for(i=0;i<20;i++){
				if(ex[i][0]>=x){
					ex[i][0]-=x;
					for(int j=1;j<=5;j++)
						if(!ex[i][j]){
							if(flag) flag=false;
							else putchar(' ');
							printf("%d",i*5+j);
							ex[i][j]=1;
							if(++cnt==x) break;
						}
					break;
				}
				if(cnt==x) break;
			}
			if(i<20) {
				putchar('\n');
				continue;
			}
			cnt=0;
			for(i=0;i<20;i++){
				for(int j=1;j<=5;j++){
					if(!ex[i][j]){
						ex[i][j]=1;
						if(flag) flag=false;
						else putchar(' ');
						printf("%d",i*5+j);
						ex[i][0]--;
						if(++cnt==x) break;
					}
				}
				if(cnt==x) break;
			}
			putchar('\n');
		}
	}
	return 0;
}
