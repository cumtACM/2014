#include <bits/stdc++.h>

using namespace std;

const int maxn = (int)1e5 + 5;

template<class T>
inline void read(T &x) {
    x = 0; T flag = 1;char c;
    do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
    if (c == '-') { c = '0', flag = -1;}
    do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
    x *= flag;
}

vector<int> G[maxn];
int pre[maxn], lowlink[maxn], sccno[maxn], dfs_clock, scc_cnt, cnt[maxn];
stack<int> S;

void dfs (int u) {
    pre[u] = lowlink[u] = ++dfs_clock;
    S.push(u);
    for (int v : G[u]) {
        if (!pre[v]) {
             dfs(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        } else if (!sccno[v]) {
            lowlink[u] = min(lowlink[u], pre[v]);
        }
    }
    if (lowlink[u] == pre[u]) {
        ++scc_cnt;
        for (;;) {
            int x = S.top(); S.pop();
            sccno[x] = scc_cnt;
            ++cnt[scc_cnt];
            if (x==u) break;
        }
    }
}
int in[maxn];
int main() {
    freopen("../in.txt", "r", stdin);
    int n,m;
    read(n);read(m);
    int u,v;
    for (int i = 0; i < m; ++i) {
        read(u);read(v);
        G[u].push_back(v);
    }
    for (int i = 1; i < n+1; ++i) {
        if (!pre[i]) {
            dfs(i);
        }
    }
    for (int i = 1; i < n+1; ++i) {
        for (int y : G[i]) {
            if (sccno[i]!=sccno[y]) {
                in[sccno[y]]++;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i < scc_cnt+1; ++i) {
        if (!in[i]) {
            if (ans) {
                puts("0");
                return 0;
            }
            ans += cnt[i];
        }
    }
    printf("%d\n", ans);
    return 0;
}
