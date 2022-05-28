#include<bits/stdc++.h>
using namespace std;
#define MAX 100000
int temp[MAX];
void mergesort(int a[],int indices[],int first,int last)
{
    if(first==last) return;
    int middle=(first+last)/2;
    mergesort(a,indices,first,middle);
    mergesort(a,indices,middle+1,last);
    int i,j,k;
    for(i=first,j=first,k=middle+1; i<=last; i++)
    {
        if(j==middle+1) temp[i]=indices[k++];
        else if(k==last+1) temp[i]=indices[j++];
        else if(a[indices[k]]<a[indices[j]]) temp[i]=indices[k++];
        else temp[i]=indices[j++];
    }
    for(i=first; i<=last; i++)
    {
        indices[i]=temp[i];
    }
}
int UpperBoundCeil(int a[],int indices[],int first,int last,int value)
{
    int middle=(first+last)/2;
    while(first<last)
    {
        if(last-first==1&&(a[indices[first]]<value||a[indices[last]]==value))
        {
            first=last;
        }
        else if(last-first==1)
        {
            last=first;
        }
        else if(a[indices[middle]]>value)
        {
            last=middle;
        }
        else
        {
            first=middle;
        }
        middle=(first+last)/2;
    }
    return first;
}
int UpperBoundFloor(int a[],int indices[],int first,int last,int value)
{
    int middle=(first+last)/2;
    while(first<last)
    {
        if(last-first==1&&(a[indices[last]]>value||a[indices[first]]==value))
        {
            last=first;
        }
        else if(last-first==1)
        {
            first=last;
        }
        else if(a[indices[middle]]>value)
        {
            last=middle;
        }
        else
        {
            first=middle;
        }
        middle=(first+last)/2;
    }
    return first;
}
int LowerBoundFloor(int a[],int indices[],int first,int last,int value)
{
    int middle=(first+last)/2;
    while(first<last)
    {
        if(last-first==1&&(a[indices[last]]>value||a[indices[first]]==value))
        {
            last=first;
        }
        else if(last-first==1)
        {
            first=last;
        }
        else if(a[indices[middle]]<value)
        {
            first=middle;
        }
        else
        {
            last=middle;
        }
        middle=(first+last)/2;
    }
    return first;
}
int LowerBoundCeil(int a[],int indices[],int first,int last,int value)
{
    int middle=(first+last)/2;
    while(first<last)
    {
        if(last-first==1&&(a[indices[first]]<value||a[indices[last]]==value))
        {
            first=last;
        }
        else if(last-first==1)
        {
            last=first;
        }
        else if(a[indices[middle]]<value)
        {
            first=middle;
        }
        else
        {
            last=middle;
        }
        middle=(first+last)/2;
    }
    return first;
}
int main()
{
    return 0;
}
