/* 给出n个字符串中，找到至少在它们中的m个中出现过的最长字符串
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100001 * 10 + 10;

struct SuffixArray {
    int s[maxn];      // 原始字符数组（最后一个字符应必须是0，而前面的字符必须非0）
    int sa[maxn];     // 后缀数组
    int rank[maxn];   // 名次数组. rank[0]一定是n-1，即最后一个字符
    int height[maxn]; // height数组
    int t[maxn], t2[maxn], c[maxn]; // 辅助数组
    int n; // 字符个数

    void clear() { n = 0; memset(sa, 0, sizeof(sa)); }

    // m为最大字符值加1。调用之前需设置好s和n
    void build_sa(int m) {
        int i, *x = t, *y = t2;
        for(i = 0; i < m; i++) c[i] = 0;
        for(i = 0; i < n; i++) c[x[i] = s[i]]++;
        for(i = 1; i < m; i++) c[i] += c[i-1];
        for(i = n-1; i >= 0; i--) sa[--c[x[i]]] = i;
        for(int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for(i = n-k; i < n; i++) y[p++] = i;
            for(i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i]-k;
            for(i = 0; i < m; i++) c[i] = 0;
            for(i = 0; i < n; i++) c[x[y[i]]]++;
            for(i = 0; i < m; i++) c[i] += c[i-1];
            for(i = n-1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1; x[sa[0]] = 0;
            for(i = 1; i < n; i++)
                x[sa[i]] = y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k] ? p-1 : p++;
            if(p >= n) break;
            m = p;
        }
    }

    void build_height() {
        int i, j, k = 0;
        for(i = 0; i < n; i++) rank[sa[i]] = i;
        for(i = 0; i < n; i++) {
            if(k) k--;
            int j = sa[rank[i]-1];
            while(s[i+k] == s[j+k]) k++;
            height[rank[i]] = k;
        }
    }
};

const int maxc = 10 + 2; // 串的个数
const int maxl = 100000 + 10; // 每个串的长度

SuffixArray sa;
int n,m;
char word[maxl];
int idx[maxn];
int flag[maxc];

// 子串[L,R) 是否符合要求
bool good(int L, int R) {
    memset(flag, 0, sizeof(flag));
    if(R - L < m) return false;
    int cnt = 0;
    for(int i = L; i < R; i++) {
        int x = idx[sa.sa[i]];                    // 看所属字符串
        if(x != n && !flag[x]) { flag[x] = 1; cnt++; }
    }
    return cnt >= m;
}

void print_sub(int L, int R) {
    for(int i = L; i < R; i++)
        printf("%c", sa.s[i] - 1 + 'a');
    printf("\n");
}

bool print_solutions(int len, bool print) {
    int L = 0;
    for(int R = 1; R <= sa.n; R++) {
        if(R == sa.n || sa.height[R] < len) { // 新开一段
            if(good(L, R)) {                      // 判断这一段是否包含不少于m个字符串
                if(print) print_sub(sa.sa[L], sa.sa[L] + len); else return true;
            }
            L = R;
        }
    }
    return false;
}

void solve(int maxlen) {
    if(!print_solutions(1, false))
        printf("?\n");
    else {
        int L = 1, R = maxlen, M;
        while(L < R) {
            M = L + (R-L+1)/2;
            if(print_solutions(M, false)) L = M;
            else R = M-1;
        }
        printf("%d\n",L);
//        print_solutions(L, true);
    }
}

// 给字符串加上一个字符，属于字符串i
void add(int ch, int i) {
    idx[sa.n] = i;
    sa.s[sa.n++] = ch;
}

int main() {
    scanf("%d%d", &n,&m);
    int maxlen = 0;
    sa.clear();
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        int sz = strlen(word);
        maxlen = max(maxlen, sz);
        for (int j = 0; j < sz; j++)
            add(word[j] - 'a' + 1, i);
        add(27 + i, n); // 结束字符
    }
    add(0, n);

    if (n == 1) printf("%s\n", word);
    else {
        sa.build_sa(27 + n);
        sa.build_height();
        solve(maxlen);
    }
    return 0;
}