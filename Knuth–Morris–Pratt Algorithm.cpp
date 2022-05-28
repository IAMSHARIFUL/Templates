#include<bits/stdc++.h>
#include<cstring>
#include<vector>
using namespace std;
#define MAX 1000000
char A[MAX],B[MAX];
int pi[MAX],Length_of_B,Length_of_A;
vector<int> occurrences,rearranged_occurrences;
void input()
{
    scanf("%s%*c%s%*c",A,B);
}
void prefix()
{
    int now=-1,i;
    Length_of_B=strlen(B);
    pi[0]=now;
    for(i=1;i<Length_of_B;i++)
    {
        while(now!=-1&&B[now+1]!=B[i])
            now=pi[now];
        if(B[now+1]==B[i]) pi[i]=++now;
        else pi[i]=now=-1;
        //printf("pi[%d]=%d\n",i,pi[i]);
    }
}
void KMP()
{
    int now=-1,i;
    Length_of_A=strlen(A);
    for(i=0;i<Length_of_A;i++)
    {
        while(now!=-1&&B[now+1]!=A[i])
            now=pi[now];
        if(B[now+1]==A[i]) ++now;
        else now=-1;
        //printf("i=%d, now=%d\n",i,now);
        if(now==Length_of_B-1)
        {
            occurrences.push_back(i-Length_of_B+2);
            now=pi[now];
        }
    }
}
void output()
{
    if(occurrences.empty()) printf("Not Found");
    else
    {
        printf("%d\n",occurrences.size());
        while(!occurrences.empty())
        {
            rearranged_occurrences.push_back(occurrences[occurrences.size()-1]);
            occurrences.pop_back();
        }
        while(!rearranged_occurrences.empty())
        {
            printf("%d ",rearranged_occurrences[rearranged_occurrences.size()-1]);
            rearranged_occurrences.pop_back();
        }
    }
    printf("\n\n");
}
int main()
{
    int T;
    scanf("%d%*c",&T);
    while(T)
    {
        input();
        prefix();
        KMP();
        output();
        T--;
    }
}
