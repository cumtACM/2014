#include <bits/stdc++.h>
#define MEM(a,b) memset((a),(b),sizeof(a))
using namespace std;
typedef long long lolo;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const int MOD = 100000007;
const int maxn = 500006;
const int maxp = 1000000;


inline void read(int &x){
    x=0;
    char c;
    do {
        c=getchar();
    }while (c<'0'||c>'9');
    do {
        x = x*10+ c-'0';
        c=getchar();
    } while (c>='0'&&c<='9');
}

const double eps=1e-9;

struct Point {
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
    double len() { return sqrt(x*x+y*y); }
};
struct Line {
    Point a,b;
    Line() {}
    Line(Point x,Point y):a(x),b(y){}
};
Point operator+(const Point& a,const Point& b) {
    return Point(a.x+b.x,a.y+b.y);
}
Point operator-(const Point& a,const Point& b) {
    return Point(a.x-b.x,a.y-b.y);
}
Point operator*(const double& p,const Point& a) {
    return Point(p*a.x,p*a.y);
}
Point operator/(const Point& a,const double& p) {
    return Point(a.x/p,a.y/p);
}
double Cross(const Point& a, const Point& b) {
    return a.x*b.y-a.y*b.x;
}
int dcmp(double x) {
    if(fabs(x)<eps) return 0;
    return x<0?-1:1;
}

double Dot(const Point& a,const Point& b) {
    return a.x*b.x+a.y*b.y;
}
inline double dists(Point p, Point a, Point b) {
    if (dcmp(b.x-a.x)==0&&dcmp(b.y-a.y)==0) return (p-a).len();
    Point v1=b-a, v2=p-a, v3=p-b;
    if (dcmp(Dot(v1,v2))<=0) return v2.len();
    else if (dcmp(Dot(v1,v3))>=0) return v3.len();
    else return fabs(Cross(v1,v2))/v1.len();
}
struct Poly {
    vector<Point> p; int n;
    Poly() { n=0; }
    void add(Point &v) { ++n;p.push_back(v); }
    bool in(const Point& P) {
        double x=P.x, y=P.y; bool wn=false; double k, d1, d2;
        for (int i=0;i<n; ++i) {
            if (dcmp(dists(P,p[i],p[(i+1)%n]))==0) return true ;
            k=dcmp(Cross(p[(i+1)%n]-p[i],P-p[i]));
            d1=dcmp(p[i].y-P.y), d2=dcmp(p[(i+1)%n].y-P.y);
            if (k>0&&d1<=0&&d2>0) wn^=1;
            if (k<0&&d1>0&&d2<=0) wn^=1;
        }
        return wn;
    }
} po;
double ConvexPolyArea(const Poly& p) {
    double as=0;
    for(int i=0;i<p.n;i++)
        as+= Cross(p.p[i], p.p[(i+1)%p.n]);
    return as/2.0;
}
bool Ins(Point a, Point b, Point c, Point d) {
    Point u=b-a, v=d-c, t1, t2;
    if (dcmp(Cross(u,v))==0) return false;
    t1=c-a, t2=d-a;
    return dcmp(Cross(u,t1)*Cross(u,t2))<0;
}
Point GLI(Point p, Point u, Point q, Point v) {
    Point w=p-q; double t = Cross(v,w)/Cross(u,v);
    return p+t*u;
}
Poly cutpolygon(Poly p, Point a, Point b) {
    Point c, d, ip; Poly np=Poly();
    for (int i=0; i<p.n; ++i) {
        c=p.p[i], d=p.p[(i+1)%p.n];
        if (dcmp(Cross(b-a,c-a))>=0) np.add(c);
        if (Ins(a,b,c,d)) ip=GLI(a,b-a,c,d-c),np.add(ip);
    }
    return np;
}

int main() {
    Point a;
    for(int i=0;i<4;i++)
        scanf("%lf%lf",&a.x,&a.y),po.add(a);
    double as=((double)4*5*5);
    as+=ConvexPolyArea(cutpolygon(po,Point(-0.5,-0.5),Point(-0.5,0.5)))*4;
    as+=ConvexPolyArea(cutpolygon(po,Point(-0.5,0.5),Point(0.5,0.5)))*6;
    as+=ConvexPolyArea(cutpolygon(po,Point(0.5,0.5),Point(0.5,-0.5)))*3;
    as+=ConvexPolyArea(cutpolygon(po,Point(0.5,-0.5),Point(-0.5, -0.5)));
    printf("%.10lf\n", as*5/(5*5*5-1));
    return 0;
}