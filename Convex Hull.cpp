#include<bits/stdc++.h>
#include<vector>
using namespace std;
struct pt {
    double x, y;
};

bool cmp(pt a, pt b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}
vector<pt> a;
vector<pair<double,pair<double,double> > > pp;
void convex_hull(vector<pt>& a) {
    if (a.size() == 1)
        return;

    sort(a.begin(), a.end(), &cmp);
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)a.size(); i++) {
        if (i == a.size() - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    a.clear();
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]);
}
double darea(pt a,pt b,pt c)
{
    double dd=a.x*(b.y-c.y)-a.y*(b.x-c.x)+b.x*c.y-c.x*b.y;
    if(dd<0) dd=-dd;
    return dd;
}
int main()
{
    int n;
    while(true)
    {
        scanf("%d",&n);
        if(n<3) return 0;
        a.clear();
        pp.clear();
        pt p;
        int i,j;
        for(i=0;i<n;i++)
        {
            scanf("%lf %lf",&p.x,&p.y);
            a.push_back(p);
        }
        convex_hull(a);
        pair<double,pair<double,double> > info;
        pair<double,double> center;
        double weight=0;
        center.first=center.second=0;
        for(i=2;i<n;i++)
        {
            info.first=darea(a[0],a[i-1],a[i]);
            info.second.first=(a[0].x+a[i-1].x+a[i].x)/3;
            info.second.second=(a[0].y+a[i-1].y+a[i].y)/3;
            pp.push_back(info);
        }
        for(i=0;i<pp.size();i++)
        {
            weight=weight+pp[i].first;
            center.first=center.first+pp[i].first*pp[i].second.first;
            center.second=center.second+pp[i].first*pp[i].second.second;
        }
        center.first=center.first/weight;
        center.second=center.second/weight;
        printf("%.3f %.3f\n",center.first,center.second);
    }
    return 0;
}
