/*http://blog.csdn.net/qwb492859377/article/details/50950293
题意： 大概就是告诉你一个字典，字典里字母总个数不超过100，要构造一个长度为m(<=1e15)的串，要含字典中的单词最多，输出最多的数量，可以重叠 
思路：看数据大小，再根据做题的经验，很容易就想到AC自动机来优化状态，再用矩阵快速幂来优化dp，但是这题很特别。
我们先把dp写出来
dp[i][j]=max(dp[i-1][j可能的上一个状态])+End[j]
i是长度，j是在AC自动机中的节点
但是，我们能发现，一般的矩阵快速幂都只能用来完成线性递推，通常是用来解决d[i][j]=A*d[i-1][a1]+B*d[i-2][a2]+...类似的问题
这题缺是来维护最大值。
这里就要讲到了矩阵乘法的变形了。之所以矩阵乘法是可行的是因为乘法的结合律，但是加法和max()同样有结合律
我们再回顾一下矩阵快速幂的另外一道经典题，告诉你一个有向图，可能有重边，告诉你起点和终点，要你恰好k步从起点走到终点，有多少种方法。
最后，我们的dp是这样写的
dp[i][j]=sigma(dp[i][k]*dp[k][j])
我们都知道，这个题的答案就只要拿邻接矩阵求幂，然后把第0列的数字加起来就行了。
我们如果把sigma改成max，把乘号改成加号，那么就和这道题的方程完全一样了。
实际上，这种做法是可行的！
对于这道题，我们只需要对矩阵乘法的定义稍作修改，就能用来优化取最大值的dp了！
这种dp是很常见的，有了这种矩阵快速幂的方法，又为我们加速dp优化打开了一个新世界的大门。*/
//http://blog.csdn.net/shadream/article/details/51106659
    #include <map>  
    #include <set>  
    #include <cmath>  
    #include <ctime>  
    #include <Stack>  
    #include <queue>  
    #include <cstdio>  
    #include <cctype>  
    #include <bitset>  
    #include <string>  
    #include <vector>  
    #include <cstring>  
    #include <iostream>  
    #include <algorithm>  
    #include <functional>  
    #define fuck(x) cout << "[" << x << "]"  
    #define FIN freopen("input.txt", "r", stdin)  
    #define FOUT freopen("output.txt", "w+", stdout)  
    using namespace std;  
    typedef long long LL;  
    typedef pair<int, int> PII;  
    typedef vector<LL> vec;  
    typedef vector<vec> mat;  
      
    const int MX = 1e4 + 5;  
    const LL INF = 0x3f3f3f3f3f3f3f3f;  
      
    int rear, root;  
    int Next[MX][26], Fail[MX], End[MX];  
    int New() {  
        rear++;  
        End[rear] = 0;  
        for(int i = 0; i < 26; i++) {  
            Next[rear][i] = -1;  
        }  
        return rear;  
    }  
    void Init() {  
        rear = 0;  
        root = New();  
    }  
    void Add(char *A) {  
        int n = strlen(A), now = root;  
        for(int i = 0; i < n; i++) {  
            int id = A[i] - 'a';  
            if(Next[now][id] == -1) {  
                Next[now][id] = New();  
            }  
            now = Next[now][id];  
        }  
        End[now]++;  
    }  
    void mat_fill(mat &A, LL val) {  
        for(int i = 0; i < A.size(); i++) {  
            for(int j = 0; j < A[0].size(); j++) {  
                A[i][j] = val;  
            }  
        }  
    }  
    mat Build() {  
        queue<int>Q;  
        Fail[root] = root;  
        for(int i = 0; i < 26; i++) {  
            if(Next[root][i] == -1) {  
                Next[root][i] = root;  
            } else {  
                Fail[Next[root][i]] = root;  
                Q.push(Next[root][i]);  
            }  
        }  
        while(!Q.empty()) {  
            int u = Q.front(); Q.pop();  
            End[u] += End[Fail[u]];  
            for(int i = 0; i < 26; i++) {  
                if(Next[u][i] == -1) {  
                    Next[u][i] = Next[Fail[u]][i];  
                } else {  
                    Fail[Next[u][i]] = Next[Fail[u]][i];  
                    Q.push(Next[u][i]);  
                }  
            }  
        }  
        mat A(rear, vec(rear));  
        mat_fill(A, -INF);  
        for(int i = 1; i <= rear; i++) {  
            for(int j = 0; j < 26; j++) {  
                int chd = Next[i][j];  
                A[chd - 1][i - 1] = End[chd];  
            }  
        }  
        return A;  
    }  
    mat mat_mul(mat &A, mat &B) {  
        mat C(A.size(), vec(B[0].size()));  
        mat_fill(C, -INF);  
        for(int i = 0; i < A.size(); i++) {  
            for(int j = 0; j < B[0].size(); j++) {  
                for(int k = 0; k < B.size(); k++) {  
                    if(A[i][k] + B[k][j] >= 0) {  
                        C[i][j] = max(C[i][j], A[i][k] + B[k][j]);  
                    }  
                }  
            }  
        }  
        return C;  
    }  
    mat mat_pow(mat A, LL n) {  
        mat B = A; n--;  
        while(n) {  
            if(n & 1) B = mat_mul(B, A);  
            A = mat_mul(A, A);  
            n >>= 1;  
        }  
        return B;  
    }  
    void print(mat &A) {  
        for(int i = 0; i < A.size(); i++) {  
            for(int j = 0; j < A[0].size(); j++) {  
                fuck(A[i][j]);  
            } printf("\n");  
        }  
    }  
      
    char S[MX];  
    int main() {  
        int n; LL m; //FIN;  
        scanf("%d%lld", &n, &m);  
        Init();  
        for(int i = 1; i <= n; i++) {  
            scanf("%s", S);  
            Add(S);  
        }  
        mat A = Build();  
        A = mat_pow(A, m);  
      
        LL ans = 0;  
        for(int i = 0; i < rear; i++) {  
            ans = max(ans, A[i][0]);  
        }  
        printf("%lld\n", ans);  
        return 0;  
    }  

// my version
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;

const int maxn=1e4+2;
const ll inf=0x3f3f3f3f3f3f3f3f;
int rear;
int ch[maxn][26],f[maxn],End[maxn];

int New(){
	End[rear]=0;
	memset(ch[rear],0,sizeof(ch[rear]));
	rear++;
	return rear-1;
}
void init(){
	rear=0;
	New();
}
void add(char *a){
	int now=0;
	for(int i=0;a[i];i++){
		int c=a[i]-'a';
		if(!ch[now][c]){
			ch[now][c]=New();
		}
		now=ch[now][c];
	}
	End[now]++;
}
void mat_fill(mat& a,ll val){
	for(int i=0;i<a.size();i++)
		for(int j=0;j<a[i].size();j++)
			a[i][j]=val;
}
mat mat_mul(mat&a,mat&b){
	mat c(a.size(),vec(b.size()));
	mat_fill(c,-inf);
	for(int i=0;i<c.size();i++){
		for(int j=0;j<b.size();j++){
			for(int k=0;k<a.size();k++){
				if(a[i][k]+b[k][j]>=0){
					c[i][j]=max(c[i][j],a[i][k]+b[k][j]);
				}
			}
		}
	}	
	return c;
}
mat mat_pow(mat a,ll n){
	mat b=a;n--;
	while(n){
		if(n&1) b=mat_mul(b,a);
		a=mat_mul(a,a);
		n>>=1;
	}
	return b;
}
mat getFail(){
	queue<int> Q;
	f[0]=0;
	for(int c=0;c<26;c++){
		int u=ch[0][c];
		if(u){
			f[u]=0;Q.push(u);
		}
	}
	while(!Q.empty()){
		int r=Q.front();Q.pop();
		End[r]+=End[f[r]];
		for(int c=0;c<26;c++){
			int u=ch[r][c];
			if(!u) ch[r][c]=ch[f[r]][c];
			else{
				Q.push(u);
				int v=f[r];
				while(v&&!ch[v][c]) v=f[v];
				f[u]=ch[v][c];
			} 
		}
	}
	mat a(rear,vec(rear));
	mat_fill(a,-inf);
	for(int i=0;i<rear;i++){
		for(int j=0;j<26;j++){
			int next=ch[i][j];
			a[next][i]=End[next];
		}
	}
	return a;
}
int main(void){
	int n;ll m;
	char str[101];
	while(scanf("%d%lld",&n,&m)==2){
		init();
		for(int i=0;i<n;i++){
			scanf("%s",str);
			add(str);
		}
		mat a=getFail();
		a=mat_pow(a,m);
		ll ans=0LL;
		for(int i=0;i<rear;i++){
			ans=max(a[i][0],ans);
		}
		printf("%lld\n",ans);
	}
    return 0;
}