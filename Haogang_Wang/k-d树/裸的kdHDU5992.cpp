// 裸kd HDU5992
#include <bits/stdc++.h>

#define MIN(a,b) (a)<(b)?(a):(b)
#define MAX(a,b) (a)>(b)?(a):(b)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 200005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;

template<class T>
inline void read(T &x) {
    x = 0;
    T flag=1;
    char c;
    do {
        c = (char)getchar();
        if(c=='-') break;
    } while (c < '0' || c > '9');
    if(c=='-')
        c='0',flag=-1;
    do {
        x = x * 10 + c - '0';
        c = (char)getchar();
    } while (c >= '0' && c <= '9');
    x*=flag;
}

#define lson rt << 1
#define rson rt << 1 | 1
#define Pair pair<lolo, Node>
#define Sqrt2(x) (x) * (x)

int idx;

struct Node {
    int id;
    int feature[3];     //定义属性数组
    bool operator < (const Node &u) const
    {
        return feature[idx] < u.feature[idx];
    }
}_data[maxn];   //_data[]数组代表输入的数据

Pair ans;

struct KDTree {

    Node data[maxn<<2];    //data[]数组代表K-D树的所有节点数据
    bool flag[maxn<<2];
    void Build(int l, int r, int rt, int dept) {
        if(l > r) return;
        flag[rt] = true;                   //表示编号为rt的节点存在
        flag[lson] = flag[rson] = false;   //当前节点的孩子暂时标记不存在
        idx = dept % 2;                 //按照编号为idx的属性进行划分
        int mid = (l + r) >> 1;
        nth_element(_data + l, _data + mid, _data + r + 1);   //nth_element()为STL中的函数
        data[rt] = _data[mid];
        Build(l, mid - 1, lson, dept + 1);  //递归左子树
        Build(mid + 1, r, rson, dept + 1);  //递归右子树
    }
    void Query(Node p, int rt, int dept) {
        if(flag[rt] == -1) return;   //不存在的节点不遍历
        Pair cur(0, data[rt]);       //获取当前节点的数据和到p的距离
        for(int i = 0; i < 2; i++)
            cur.first += Sqrt2(1LL*cur.second.feature[i] - p.feature[i]);
        int dim = dept % 2;          //跟建树一样，这样能保证相同节点的dim值不变
        bool fg = 0;                 //用于标记是否需要遍历右子树
        int x = lson;
        int y = rson;
        if(p.feature[dim] >= data[rt].feature[dim]) //数据p的第dim个特征值大于等于当前的数据，则需要进入右子树
            swap(x, y);
        if(flag[x]) Query(p, x, dept + 1);      //如果节点x存在，则进入子树继续遍历

        if(ans.first==-1){
            if(cur.second.feature[2]<=p.feature[2])
                ans.first=cur.first,ans.second=cur.second;
            fg=1;
        }
        else {
            if(cur.second.feature[2]<=p.feature[2]&&(cur.first<ans.first||(cur.first==ans.first&&cur.second.id<ans.second.id)))
                ans.first=cur.first,ans.second=cur.second;
            if((Sqrt2((lolo)data[rt].feature[dim]-p.feature[dim]))<ans.first)
                fg=1;
        }
        if(fg&&flag[y]) Query(p,y,dept+1);
    }
}kd;


//输出结果
void Print(Node data) {
    for(int i = 0; i < 3; i++)
        printf("%d%c", data.feature[i], i == 2 ? '\n' : ' ');
}

int main() {
    int T,n,m;
    read(T);
    while(T--) {
        read(n);
        read(m);
        for(int i=1;i<=n;i++) {
            for(int j=0;j<3;j++)
                read(_data[i].feature[j]);
            _data[i].id=i;
        }
        kd.Build(1, n, 1, 0);
        while(m--) {
            Node p;
            for(int j=0;j<3;j++)
                read(p.feature[j]);
            ans.first=-1;
            kd.Query(p, 1, 0);
            Print(ans.second);
        }
    }
    return 0;
}
