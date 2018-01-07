// K-D树求m个最近点 HDU4347
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
#define Pair pair<double, Node>
#define Sqrt2(x) (x) * (x)

int n, k, idx;

struct Node {
    int feature[5];     //定义属性数组
    bool operator < (const Node &u) const
    {
        return feature[idx] < u.feature[idx];
    }
}_data[maxn];   //_data[]数组代表输入的数据

priority_queue<Pair> Q;     //队列Q用于存放离p最近的m个数据

struct KDTree{
    Node data[maxn<<1];    //data[]数组代表K-D树的所有节点数据
    int flag[maxn<<1];      //用于标记某个节点是否存在，1表示存在，-1表示不存在
    //如果找到更小的距离，则用于替换队列Q中最大的距离的数据
    void Build(int l, int r, int rt, int dept) {
        if(l > r) return;
        flag[rt] = 1;                   //表示编号为rt的节点存在
        flag[lson] = flag[rson] = -1;   //当前节点的孩子暂时标记不存在
        idx = dept % k;                 //按照编号为idx的属性进行划分
        int mid = (l + r) >> 1;
        nth_element(_data + l, _data + mid, _data + r + 1);   //nth_element()为STL中的函数
        data[rt] = _data[mid];
        Build(l, mid - 1, lson, dept + 1);  //递归左子树
        Build(mid + 1, r, rson, dept + 1);  //递归右子树
    }
    //如果找到更小的距离，则用于替换队列Q中最大的距离的数据
    void Query(Node p, int m, int rt, int dept) {
        if(flag[rt] == -1) return;   //不存在的节点不遍历
        Pair cur(0, data[rt]);       //获取当前节点的数据和到p的距离
        for(int i = 0; i < k; i++)
            cur.first += Sqrt2(cur.second.feature[i] - p.feature[i]);
        int dim = dept % k;          //跟建树一样，这样能保证相同节点的dim值不变
        bool fg = 0;                 //用于标记是否需要遍历右子树
        int x = lson;
        int y = rson;
        if(p.feature[dim] >= data[rt].feature[dim]) //数据p的第dim个特征值大于等于当前的数据，则需要进入右子树
            swap(x, y);
        if(~flag[x]) Query(p, m, x, dept + 1);      //如果节点x存在，则进入子树继续遍历

        //以下是回溯过程，维护一个优先队列
        if(Q.size() < m) {
            Q.push(cur);
            fg = 1;
        }
        else {
            //如果找到更小的距离，则用于替换队列Q中最大的距离的数据
            if(cur.first < Q.top().first)  {
                Q.pop();
                Q.push(cur);
            }
            if(Sqrt2(p.feature[dim] - data[rt].feature[dim]) < Q.top().first)
                fg = 1;
        }
        if(~flag[y] && fg)
            Query(p, m, y, dept + 1);
    }
}kd;

//输出结果
void Print(Node data) {
    for(int i = 0; i < k; i++)
        printf("%d%c", data.feature[i], i == k - 1 ? '\n' : ' ');
}

int main() {
    while(scanf("%d%d", &n, &k)!=EOF) {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < k; j++)
                scanf("%d", &_data[i].feature[j]);
        kd.Build(0, n - 1, 1, 0);
        int t, m;
        scanf("%d", &t);
        while(t--) {
            Node p;
            for(int i = 0; i < k; i++)
                scanf("%d", &p.feature[i]);
            scanf("%d", &m);
            while(!Q.empty()) Q.pop();   //事先需要清空优先队列
            kd.Query(p, m, 1, 0);
            printf("the closest %d points are:\n", m);
            Node tmp[25];
            for(int i = 0; !Q.empty(); i++) {
                tmp[i] = Q.top().second;
                Q.pop();
            }
            for(int i = m - 1; i >= 0; i--)
                Print(tmp[i]);
        }
    }
    return 0;
}
