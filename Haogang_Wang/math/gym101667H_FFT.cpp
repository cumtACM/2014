#include <bits/stdc++.h>

using namespace std;
typedef long long lolo;

const int maxn = (int)1e5 + 5;

template<class T>
inline void out(T x) {
    if (x > 9) out(x / 10);
    x = x % 10;
    putchar('0' + x);
}

struct Complex {
    double r, i;
    Complex(double _r = 0, double _i = 0) :r(_r), i(_i) {}
    Complex operator +(const Complex &b) {
        return Complex(r + b.r, i + b.i);
    }
    Complex operator -(const Complex &b) {
        return Complex(r - b.r, i - b.i);
    }
    Complex operator *(const Complex &b) {
        return Complex(r*b.r - i*b.i, r*b.i + i*b.r);
    }
};
typedef Complex cd;//复数类的定义
const int maxl=maxn<<2;//nlogn的最大长度(来自leo学长的博客)
const double PI=acos(-1.0);//圆周率,不解释


cd a[maxl],b[maxl];//用于储存变换的中间结果
int rev[maxl];//用于储存二进制反转的结果
void getrev(int bit){
    for(int i=0;i<(1<<bit);i++){//高位决定二进制数的大小
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
    }//能保证(x>>1)<x,满足递推性质
}

void fft(cd* a,int n,int dft){//变换主要过程
    for(int i=0;i<n;i++){//按照二进制反转
        if(i<rev[i])//保证只把前面的数和后面的数交换,(否则数组会被翻回来)
            swap(a[i],a[rev[i]]);
    }
    for(int step=1;step<n;step<<=1){//枚举步长的一半
        cd wn=Complex(cos(-dft * PI / step), sin(-dft * PI / step)); //exp(cd(0,dft*PI/step));//计算单位复根
        for(int j=0;j<n;j+=step<<1){//对于每一块
            cd wnk(1,0); //!!每一块都是一个独立序列,都是以零次方位为起始的
            for(int k=j;k<j+step;k++){//蝴蝶操作处理这一块
                cd x=a[k];
                cd y=wnk*a[k+step];
                a[k]=x+y;
                a[k+step]=x-y;
                wnk=wnk*wn;//计算下一次的复根
            }
        }
    }
    if(dft==-1){
        for(int i=0;i<n;i++)
            a[i].r/=n,a[i].i/=n;
    }
}
int bit,len;
int n,m,nm;
char s[maxn],t[maxn];
int ans[maxn];
void calc(char ch) {
    for (int i = 0; i < n; ++i) {
        a[i].r=s[i]==ch?1:0;
        b[i+m].r=b[i+m].i=0;
        a[i].i=0;
    }
    for (int i = 0; i < m; ++i) {
        b[i].r=t[i]==ch?1:0;
        a[i+n].r=a[i+n].i=0;
        b[i].i=0;
    }
    for (int i = n+m; i < len; ++i) {
        a[i].r=a[i].i=b[i].r=b[i].i=0;
    }
    fft(a,len,1);
    fft(b,len,1);
    for (int i = 0; i < len; ++i) a[i]=a[i]*b[i];
    fft(a,len,-1);
    for (int i = 0; i < n; ++i) ans[i]+=floor(a[i+m-1].r+0.5);
}
int main() {
//    freopen("../in.txt","r",stdin);
    while(scanf("%d %d",&n,&m)==2) {
        scanf("%s%s", s, t);
        nm = n + m - 1;
        bit = 1, len = 2;
        memset(ans, 0, sizeof(ans));
        for (bit = 1; (1 << bit) < nm; bit++) {
            len <<= 1;
        }
        getrev(bit);
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'P') s[i] = 'S';
            else if (s[i] == 'S') s[i] = 'R';
            else s[i] = 'P';
        }
        reverse(t, t + m);
        calc('S');
        calc('R');
        calc('P');
        int ret = -1;
        for (int i = 0; i < n; ++i) {
            ret = max(ret, ans[i]);
        }
        out(ret);
        putchar('\n');
    }
    return 0;
}
