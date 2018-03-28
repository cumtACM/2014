#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)

using namespace std;

const int maxn = (int)2e4 + 5;
const int maxm = (int)3e5 + 5;


template<class T>
inline void out(T x) {
    if(x>9) out(x/10);
    x=x%10;
    putchar('0'+x);
}

int ans,sz,root,n,ch[maxm][26],fail[maxm],last[maxm],dp[maxm],v[maxm],rec[maxn],val[maxn],pos[maxn];
int newnode();
char str[maxm];
void getfail(),ins(int k),init();

int main(){
    int T;
    scanf("%d",&T);
    FOR(cas,1,T){
        printf("Case #%d: ",cas);
        scanf("%d",&n);
        init();
        for(int i=0;i<n;++i){
            scanf("%s%d",str+pos[i],val+i);
            pos[i+1]=pos[i]+(int)strlen(str+pos[i]);
            ins(i);
        }
        getfail();

        for(int i=0,u=root,p;i<n;++i,u=root)
            if(val[i]>0){
                for(int j=pos[i];j<pos[i+1];++j){
                    p=u=ch[u][str[j]];
                    if(!v[p]&&last[p]!=root)
                        p=last[p];
                    while(v[p]){    // 查找子串
                        dp[rec[i]]=max(dp[rec[i]],dp[p]);
                        p=last[p];
                    }
                }
                dp[rec[i]]+=val[i];
                ans=max(ans,dp[rec[i]]);
            }
        out(ans);
        putchar('\n');
    }
    return 0;
}

void init(){
    sz=ans=0;
    root=newnode();
}

void ins(int k){
    int u=root;
    for(int i=pos[k];str[i];++i){
        str[i]-='a';
        if(ch[u][str[i]]==root)
            ch[u][str[i]]=newnode();
        u=ch[u][str[i]];
    }
    v[u]=1;
    rec[k]=u;
}

void getfail(){
    queue<int> q;
    for(int i=0;i<26;++i)
        if(ch[root][i]!=root){
            q.push(ch[root][i]);
            fail[ch[root][i]]=last[ch[root][i]]=root;
        }

    int u;
    while(!q.empty()){
        u=q.front();q.pop();
        for(int i=0;i<26;++i)
            if(ch[u][i]==root)
                ch[u][i]=ch[fail[u]][i];
            else{
                fail[ch[u][i]]=ch[fail[u]][i];
                last[ch[u][i]]=(v[fail[ch[u][i]]]?fail[ch[u][i]]:last[fail[ch[u][i]]]);
                q.push(ch[u][i]);
            }
    }
}

int newnode(){
    dp[sz]=v[sz]=0;
    memset(ch[sz],0,sizeof ch[sz]);
    return sz++;
}