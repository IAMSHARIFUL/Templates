#include<bits/stdc++.h>
#include<stdio.h>
#include<vector>
using namespace std;
#define MAX 100001
int P[MAX];
int Find(int x)
{
    if(P[x]==x) return x;
    else
    {
        P[x]=Find(P[x]);
        return P[x];
    }
}
bool Join(int x,int y)
{
    int PoX=Find(x),PoY=Find(y);
    if(PoX==PoY) return false;
    else if(PoX<PoY)
    {
        P[PoY]=PoX;
    }
    else
    {
        P[PoX]=PoY;
    }
    return true;
}
int main()
{

}
