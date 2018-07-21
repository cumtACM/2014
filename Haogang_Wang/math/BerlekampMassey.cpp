/**
*设有一个线性递推数列{An}满足 c1 * An + c2 * An-1 + ... + ck * An-k+1 = 0
*输入这个数列的前m项，m >= k, 输出c1, c2, ..., ck
*/

#include <bits/stdc++.h>
using namespace std;

vector<double> BerlekampMassey(const vector<int>& a){
    const double eps = 1e-6;
    const int maxsz = 100;
    vector<double> r[maxsz], last;
    r[0].push_back(1.0);
    last.push_back(1.0);
    int n = a.size(), s = 1;
    double v = 1.0;
    for(int k = 1; k <= n; k++){
        r[k] = r[k - 1];
        double u = 0.0;
        for(int i = 0; i < r[k].size(); i++){
            u += a[k - i - 1] * r[k][i];
        }
        if(fabs(u) > eps){
            if(int(r[k].size()) < int(last.size()) + s){
                int cnt = int(last.size()) + s - int(r[k].size());
                for(int i = 0; i < cnt; i++){
                    r[k].push_back(0.0);
                }
                for(int i = 0; i < last.size(); i++){
                    r[k][i + s] -= u / v * last[i];
                }
                last = r[k - 1];
                v = u;
                s = 0;
            }
            else{
                for(int i = 0; i < last.size(); i++){
                    r[k][i + s] -= u / v * last[i];
                }
            }
        }
        s++;
    }
    return r[n];
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> v;
    for(int i = 0; i < n; i++){
        int x;
        scanf("%d", &x);
        v.push_back(x);
    }
    vector<double> u = BerlekampMassey(v);
    for(int i = 0; i < u.size(); i++){
        cout << u[i] << " ";
    }
    cout << endl;
    return 0;
}
