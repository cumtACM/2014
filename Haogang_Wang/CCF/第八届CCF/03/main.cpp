#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct node{
	int hp,at;
}bat[2][8];
int cnt[2];
int main() {
	int n;
	char op[15];
	while(scanf("%d",&n)!=EOF){
		memset(bat,0,sizeof(bat));
		int winner=0;
		bat[0][0].hp=bat[1][0].hp=30;
		cnt[0]=cnt[1]=0;
		int now=0;
		for(int k=0;k<n;k++){
			scanf("%s",op);
			if(op[0]=='s'){
				int p,a,h;
				scanf("%d%d%d",&p,&a,&h);
				cnt[now]++;
				for(int i=cnt[now];i>p;i--){
					bat[now][i]=bat[now][i-1];
				}
				bat[now][p].at=a;bat[now][p].hp=h;
			}
			else if(op[0]=='a'){
				int a,b;
				scanf("%d%d",&a,&b);
				bat[now^1][b].hp-=bat[now][a].at;
				if(bat[now^1][b].hp<=0){
					if(b==0) winner=now==0?1:-1;
					else {
						for(int i=b+1;i<=cnt[now^1];i++){
							bat[now^1][i-1]=bat[now^1][i];
						}
						cnt[now^1]--;
					}
				}
				bat[now][a].hp-=bat[now^1][b].at;
				if(bat[now][a].hp<=0){
					for(int i=a+1;i<=cnt[now];i++){
						bat[now][i-1]=bat[now][i];
					}
					cnt[now]--;
				}
			}
			else now^=1;
		}
		printf("%d\n",winner);
		printf("%d\n",bat[0][0].hp);
		printf("%d",cnt[0]);
		for(int i=1;i<=cnt[0];i++){
			printf(" %d",bat[0][i].hp);
		}
		putchar('\n');
		printf("%d\n",bat[1][0].hp);
		printf("%d",cnt[1]);
		for(int i=1;i<=cnt[1];i++){
			printf(" %d",bat[1][i].hp);
		}
		putchar('\n');
	}
	return 0;
}
