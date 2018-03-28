#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;

typedef pair<int, int> pii;
typedef long long lolo ;
const int maxn=100005;
char s[maxn];
int n;
// 最小表示法模版
int get_min() {
    int i=0,j=1,k=0,t;
    while(i<n&&j<n&&k<n) {
        t=s[(j+k)%n]-s[(i+k)%n];
        if(!t)
            k++;
        else {
            if(t>0)
                j=j+k+1;
            else
                i=i+k+1;
            if(i==j)
                j++;
            k=0;
        }
    }
    return (i<j?i:j);
}
int main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%s",&n,s);
        int ans=get_min();
        printf("%d\n",ans);
    }
    return 0;
}

/*   http://blog.csdn.net/zy691357966/article/details/39854359
定义三个指针，i,j,k
初始i=0;j=1;k=0
首先，如果s[i]<s[j]那么很明显j++
如果s[i]>s[j]那么也很明显i=j++
省下的就是如果s[i]==s[j]的时候。
这时候有一个性质就是在i和j之间的所有的字符一定是大于等于s[i]的
另k=0，循环寻找第一个s[i+k]!=s[j+k]的位置
如果s[i+k]<s[j+k]那么j+=k+1
为什么呢？
首先s[i]到s[i+k-1]一定是大于等于s[i]，因为如果其中有一个数小于s[i]，那么
这个数一定在s[j]到s[j+k-1]中存在，又因为必定有一个会在后面，所以如果s[j]先
碰到了，那么一定不会继续到k的位置的，所以一定不存在比s[i]小的字符。
所以从其中的任意一个字符开始当作起始点，都不会比现在更小，所以只有从选出来的序列的后面那一个字符开始才有可能会是最小。
所以j+=k+1
如果序列中某个数和s[i]相等的话，那么一定会有之前或者以后再这个位置起始过，所以不需要再从这个位置进行起始。
因为在这里i和j是等价的，i在前和j在前的结果是一样的，所以i和j的处理是相同的，下面就不仔细的进行讲解了，直接贴代码：
还有就是如果i==j那么让j++就可以回到原先的状态了
最后的时候，肯定是小的不会动，而大的会不停的向后移动，所以最后只需要输出i和j最小的一个即可
*/