#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long lolo;

const int maxn = (int)1e6 + 5;

template<class T>
inline void read(T &x) {
    x = 0; T flag = 1;char c;
    do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
    if (c == '-') { c = '0', flag = -1;}
    do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
    x *= flag;
}

bool not_prime[maxn];
int prime[maxn],cnt;
void getprime() {
    for(int i=2;i<maxn;++i) {
        if(!not_prime[i]) {
            prime[++cnt]=i;
            for(lolo j=1LL*i*i;j<maxn;j+=i) not_prime[j]=true;
        }
    }
}
inline lolo mull(lolo a,lolo b,lolo n)  {  
    lolo ans=0;  
    while(b)  {  
        if(b&1) ans=(ans+a)%n;  
        a=(a+a)%n;  
        b=b>>1;  
    }  
    return ans;  
}  
inline lolo pow_mod(lolo a,lolo b,lolo n)  {  
    lolo result=1;  
    lolo base=a%n;  
    while(b)  {  
        if(b&1) result=mull(result,base,n)%n;  
        base=mull(base,base,n)%n;  
        b=b>>1;  
    }  
    return result;  
}  
bool isProbablePrime(lolo n) {
    if(n<=maxn)  {  
        return !not_prime[n];
    }  
    lolo pan[4] = {2, 3, 7,11};  
    lolo i;  
    for(i=0; i<4; i++)  
        if(pow_mod(pan[i],n-1,n)!=1)break;  
    if(i==4)  
        return true;  
    else return false;  
}

int main() {
    getprime();
    int T;
    read(T);
    while(T--) {
        lolo n;
        read(n);
        lolo b = 2;
        int i=1;
        while(true) {
            lolo c = n-b;
            if(isProbablePrime(b)&&isProbablePrime(c)) {
                printf("%llu %llu\n",b, c);
                break;
            }
            if(i<cnt) b=prime[++i];
            else ++b;
        }
    }
    return 0;
}
