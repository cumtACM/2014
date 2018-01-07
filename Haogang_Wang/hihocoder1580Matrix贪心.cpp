#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <map>
#include <set>
#include <cmath>

#define MIN(a,b) (a)<(b)?(a):(b)
#define MAX(a,b) (a)>(b)?(a):(b)
#define lowbit(x) (x)&(-(x))

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 305;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;
const int SIGMA_SIZE = 26;
const int MAXNODE = 11000;
const int MAXS = 150 + 10;
inline void read(int &x) {
    x = 0;
    int flag=1;
    char c;
    do {
        c = getchar();
        if(c=='-') break;
    } while (c < '0' || c > '9');
    if(c=='-')
        c='0',flag=-1;
    do {
        x = x * 10 + c - '0';
        c = getchar();
    } while (c >= '0' && c <= '9');
    x*=flag;
}

int n,m,P;
int a[maxn][maxn],a2[maxn][maxn];

int colsum[maxn],l[maxn],r[maxn],sum[maxn],colmin[maxn];
int work(int row, int col, int mp[][maxn]) {
    int ans1=-INF,ans2=-INF;
    for (int r1 = 1; r1 <= row; r1++) {
        memset(colmin+1, INF, sizeof(int)*col);
        memset(colsum+1,0, sizeof(int)*col);
        for (int r2 = r1; r2 <= row; r2++) {
            for (int i = 1; i <= col; i++) {
                colsum[i] += mp[r2][i];
                colmin[i] = min(colmin[i], mp[r2][i]);
                sum[i] = sum[i - 1] + colsum[i];
                l[i]=min(l[i-1],sum[i]);
            }
            r[col] = sum[col];
            for (int i = col - 1; i >= 1; i--)
                r[i] = max(r[i + 1], sum[i]);
            for (int i = 1; i <= col; i++)
                ans1= max(ans1, r[i] - l[i - 1] + P - colmin[i]);
            if (r2 - r1 + 1 != row)
                for (int i = 1; i <= col; i++)
                    ans2 = max(ans2, r[i] - l[i - 1]);
        }
    }
    return max(ans1,ans2);
}
int main() {
    while (scanf("%d%d%d",&n,&m,&P)!=EOF) {
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=m;j++) {
                read(a[i][j]);
                a2[j][i]=a[i][j];
            }
        }
        int ans=-INF;
//        memset(d,0, sizeof(d));
//        RMQ_2D_PRE();
        ans= max(ans, work(n, m, a));
        ans = max(ans, work(m, n, a2));
        printf("%d\n",ans);
    }
    return 0;
}
