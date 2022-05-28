#include<bits/stdc++.h>
#include<vector>
using namespace std;
vector<int>Mergesort_Tree_Data[(BEGIN+MAX)*4];
bool compare(int a,int b)
{
    return a<b;
}
void Mergesort_Tree_Build(int index,int left,int right)
{
    if(left==right)
    {
        Mergesort_Tree_Data[index].push_back(position[left]);
        return;
    }
    int middle=(left+right)/2;
    Mergesort_Tree_Build(index*2,left,middle);
    Mergesort_Tree_Build(index*2+1,middle+1,right);
    int j=0,k=0;
    int firstSize=Mergesort_Tree_Data[index*2].size();
    int secondSize=Mergesort_Tree_Data[index*2+1].size();
    while(j<firstSize||k<secondSize)
    {
        if(j==firstSize) Mergesort_Tree_Data[index].push_back(Mergesort_Tree_Data[index*2+1][k++]);
        else if(k==secondSize) Mergesort_Tree_Data[index].push_back(Mergesort_Tree_Data[index*2][j++]);
        else if(compare(Mergesort_Tree_Data[index*2+1][k],Mergesort_Tree_Data[index*2][j])) Mergesort_Tree_Data[index].push_back(Mergesort_Tree_Data[index*2+1][k++]);
        else Mergesort_Tree_Data[index].push_back(Mergesort_Tree_Data[index*2][j++]);
    }
}
int Query(int a,int b)
{
    return a+b;
}
int Mergesort_Tree_Query(int index,int left,int right,int L,int R,int value)
{
    if(R<left||L>right) return DEFAULT_VALUE;
    if(L<=left&&R>=right)
    {
        return upper_bound(Mergesort_Tree_Data[index].begin(),Mergesort_Tree_Data[index].end(),value)-Mergesort_Tree_Data[index].begin();
    }
    int middle=(left+right)/2;
    int firstHalf=Mergesort_Tree_Query(index*2,left,middle,L,R,value);
    int secondHalf=Mergesort_Tree_Query(index*2+1,middle+1,right,L,R,value);
    return Query(firstHalf,secondHalf);
}
int main()
{
    return 0;
}
