#include<bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define IFOR(i,a,b) for(int i=(a);i>=(b);--i)

using namespace std;
struct Point {
    double x,y;
    Point(double x=0,double y=0):x(x),y(y) {}
};
typedef Point Vector;
Vector operator-(const Point& A,const Point& B) { return Vector(A.x-B.x,A.y-B.y);}
Vector operator+(Vector A,Vector B) { return Vector(A.x+B.x,A.y+B.y);}
Vector operator*(Vector A,double p) { return Vector(A.x*p,A.y*p);}
Vector Rotate(Vector A,double rad) {
    return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
double Dot(Vector A,Vector B) { return A.x*B.x+A.y*B.y;}
double Length(Vector A) { return sqrt(Dot(A,A));}
double Cross(Vector A,Vector B) { return A.x*B.y-A.y*B.x;}
double Angle(Vector A,Vector B) {
    return acos(Dot(A,B)/Length(A)/Length(B));
}
Point GetLineIntersection(Point P,Vector v,Point Q,Vector w) {
    Vector u = P-Q;
    double t=Cross(w,u)/Cross(v,w);
    return P+v*t;
}
Point GetD(Point A,Point B,Point C) {
    Vector bc=C-B;
    double a1=Angle(A-B,bc);
    bc=Rotate(bc,a1/3);
    Vector cb=B-C;
    double a2=Angle(cb,A-C);
    cb=Rotate(cb,-a2/3);
    return GetLineIntersection(B,bc,C,cb);
}
int main() {
    //freopen("../in.txt","r",stdin);
    int T;
    scanf("%d",&T);
    while (T--) {
        Point p[3];
        FOR(i,0,2) scanf("%lf %lf",&p[i].x,&p[i].y);
        Point D=GetD(p[0],p[1],p[2]);
        Point E=GetD(p[1],p[2],p[0]);
        Point F=GetD(p[2],p[0],p[1]);
        printf("%.6f %.6f %.6f %.6f %.6f %.6f\n",D.x,D.y,E.x,E.y,F.x,F.y);
    }
    return 0;
}