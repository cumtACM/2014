#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <map>
#include <set>
#include <cmath>

#define MIN(a,b) (a)<(b)?(a):(b)
#define MAX(a,b) (a)>(b)?(a):(b)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 300005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9+7;
const double eps = 1e-10;

inline void read(int &x) {
    x=0;
    char c;
    int flag=1;
    do {
        c= getchar();
    } while ((c<'0'||c>'9')&&c!='-');
    if(c=='-') {
        flag=-1;
        c='0';
    }
    do {
        x = x*10+c-'0';
        c= getchar();
    } while (c>='0'&&c<='9');
    x*=flag;
}
struct Point {
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
}point[2][4];
typedef Point Vector;
Vector operator - (const Point& A,const Point& B) {
    return Vector(A.x-B.x,A.y-B.y);
}
int dcmp(double x) {
    if(fabs(x)<eps) return 0; else return x<0?-1:1;
}
bool operator==(const Point& A,const Point& B) {
    return dcmp(A.x-B.x)==0 && dcmp(A.y-B.y)==0;
}
double Cross(Vector A,Vector B) {
    return A.x*B.y-A.y*B.x;
}
double Dot(Vector A,Vector B) { return A.x*B.x+A.y*B.y;}
bool OnSegment(Point p, Point a1, Point a2) {
    return dcmp(Cross(a1-p, a2-p)) ==0&&dcmp(Dot(a1-p,a2-p))<0;
}
double Jud(double x, double y, double dx, double dy, double x1, double y1, double x2, double y2)
{
    double t, k;
    if(x1==x2) {
        if(dx==0) {
            if(x!=x1)
                return 0;
            t = 0;
        }
        else {
            t = (x1-x)/dx;
            if(t<0)
                return 0;
        }
        if(y1>y2)
            swap(y1, y2);
        if(y+t*dy<y1 || y+t*dy>y2)
            return 0;
        return 1;
    }
    else {
        k = (y1-y2)/(x1-x2);
        if(fabs(k*dx-dy)<=1e-8) {
            if((y-y1)!=k*(x-x1))
                return 0;
            t = 0;
        }
        else {
            t = (y-y1+k*x1-k*x)/(k*dx-dy);
            if(t<0)
                return 0;
        }
        x += t*dx;
        if(x1>x2)
            swap(x1, x2);
        if(x<x1 || x>x2)
            return 0;
        return 1;
    }
}
int main() {
    int T,x,y;
    read(T);
    for(int Case=1;Case<=T;Case++) {
        bool collide=false;
        for(int i=0;i<2;i++) {
            for(int j=0;j<4;j++) {
                read(x);
                point[i][j].x=x;
                read(y);
                point[i][j].y=y;
            }
        }
        double a2,a1;
        for(int k=0;k<2;k++) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    a2 = point[k][3].y-point[(k + 1) % 2][3].y , a1 = point[k][3].x - point[(k + 1) % 2][3].x;
                    Point p = point[k][i], b1 = point[(k + 1) % 2][j], b2 = point[(k + 1) % 2][(j + 1) % 3];
                    if(Jud(p.x, p.y, a1, a2, b1.x, b1.y, b2.x, b2.y)) {
                        collide = true;
                        break;
                    }
//                    if (p == b1 || p == b2 || OnSegment(p, b1, b2)) {
//                        collide = true;
//                        break;
//                    }
//                    double x1 = b1.x - p.x, x2 = b2.x - p.x;
//                    double y1 = b1.y - p.y, y2 = b2.y - p.y;
//                    double t;
//                    if (a1 * y1 + a2 * x2 - a1 * y2 - a2 * x1 == 0) t = 0;
//                    else t = 1.0 * (x1 * y2 - x2 * y1) / (a1 * y1 + a2 * x2 - a1 * y2 - a2 * x1);
//                    if (dcmp(t) < 0) continue;
//                    p.x += point[0][3].x * t;
//                    p.y += point[0][3].y * t;
//                    b1.x += point[1][3].x * t;
//                    b1.y += point[1][3].y * t;
//                    b2.x += point[1][3].x * t;
//                    b2.y += point[1][3].y * t;
//                    if (p == b1 || p == b2 || OnSegment(p, b1, b2)) {
//                        collide = true;
//                        break;
//                    }
                }
                if (collide)
                    break;
            }
            if(collide)
                break;
        }
        printf("Case #%d: %s\n",Case, collide?"YES":"NO");
    }
    return 0;
}
