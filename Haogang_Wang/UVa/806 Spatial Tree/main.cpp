#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int mod=1e9+7;
typedef long long ll;

char pic[70][70];
int po[10];
vector<int> seq;
int rep[10];
void solve(int l,int r,int s,int cur) {
    bool w=false,b=false;
    for(int i=l;i<l+s;i++) {
        for(int j=r;j<r+s;j++) {
            if(pic[i][j]=='0') w=true;
            else b=true;
        }
        if(w&&b) break;
    }
    if(!w) {
        int x=0;
        for(int i=0;i<cur;i++)
            x+=rep[i]*po[i];
        seq.push_back(x);
    }
    else if(b) {
        s>>=1;
        rep[cur]=1;
        solve(l,r,s,cur+1);
        rep[cur]=2;
        solve(l,r+s,s,cur+1);
        rep[cur]=3;
        solve(l+s,r,s,cur+1);
        rep[cur]=4;
        solve(l+s,r+s,s,cur+1);
    }
}
int main(void) {
    po[0]=1;
    for(int i=1;i<10;i++) po[i]=5*po[i-1];
	int n,im=0,l,r,s;
    int flag=false;
	while(scanf("%d",&n)!=EOF&&n!=0) {
        if(flag) putchar('\n');
        else flag=true;
        seq.clear();
        if(n>0) {
            for(int i=0;i<n;i++)
                scanf("%s",pic[i]);
            solve(0,0,n,0);
            int cnt=1;
            printf("Image %d\n",++im);
            if(!seq.empty()) {
                sort(seq.begin(),seq.end());
                printf("%d",seq[0]);
                for(int i=1;i<seq.size();i++) {
                    if(cnt==12){
                        putchar('\n');
                        cnt=0;
                    }
                    else putchar(' ');
                    cnt++;
                    printf("%d",seq[i]);
                }
                putchar('\n');
            }
            printf("Total number of black nodes = %d\n",seq.size());
        }
        else {
            int x;
            n=-n;
            memset(pic,'.',sizeof(pic));
            while(true) {
                scanf("%d",&x);
                if(x==-1) break;
                l=r=0;
                s=n;
                while(x) {
                    int dir=x%5;
                    x/=5;
                    s>>=1;
                    switch(dir) {
                        case 1: break;
                        case 2: r+=s; break;
                        case 3: l+=s; break;
                        case 4: l+=s; r+=s; break;
                    }
                }
                for(int i=l;i<l+s;i++)
                    for(int j=r;j<r+s;j++)
                        pic[i][j]='*';
            }
            printf("Image %d\n",++im);
            for(int i=0;i<n;i++) {
                pic[i][n]='\0';
                printf("%s\n",pic[i]);
            }
        }
	}
    return 0;
}
