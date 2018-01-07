#include <cstdio> 
#include <cstring>
#include <algorithm>

using namespace std; 

const int M=1010;
int m,n,q;
char A[M][M],B[M];

bool a[30][M][M],b[M],ans[2][M];

bool res[100][M];
int id[100],qr[100];

bool cmp(int a,int b){
	return qr[a]<qr[b];
}

int main(){
	while(scanf("%d",&m)==1){
		memset(a,false,sizeof(a));
		for(int i=0;i<m;i++) {
			scanf("%s",A[i]);
			for(int j=0;j<m;j++)
				a[0][i][j]=A[i][j]=='1'?true:false;
		}
		scanf("%s",B);
		for(int i=0;i<m;i++)
			b[i]=B[i]=='1'?true:false;
		for(int i=1;i<30;i++){
			for(int j=0;j<m;j++)
				for(int k=0;k<m;k++){
					for(int x=0;x<m;x++){
						a[i][j][k]=(a[i][j][k]!=(a[i-1][j][x]&&a[i-1][x][k]));
					}
				}
		}
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d",&qr[i]);
			id[i]=i;
		}
		sort(id,id+n,cmp);
		int pre=0,cur=0;
		memcpy(ans[0],b,sizeof(ans[0]));
		for(int k=0;k<n;k++){
			int q=qr[id[k]]-pre;
			for(int i=0;(1<<i)<=q;i++){
				if((1<<i)&q){
					cur^=1;
					memset(ans[cur],false,sizeof(ans[cur]));
					for(int j=0;j<m;j++){
						for(int k=0;k<m;k++){
							ans[cur][j]=(ans[cur][j]!=(a[i][j][k]&&ans[cur^1][k]));
						}
					}
				}
			}
			memcpy(res[id[k]],ans[cur],sizeof(ans[cur]));
			pre=qr[id[k]];
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++) putchar(res[i][j]?'1':'0');
			putchar('\n');
		}
	}
	return 0;
}
