#include<stdio.h>
#include<string.h>
#define MAX 100000
int pi[MAX];
char S[MAX],T[MAX];
void KMP()
{
    int now=-1;
    int i,j;
    int n=strlen(S);
    int m=strlen(T);
    for(i=0;i<n;i++)
    {
        while(now!=-1&&T[now+1]!=S[i])
            now=pi[now];
        if(T[now+1]!=S[i]) pi[i]=++now;
        else pi[i]=now=-1;
    }
}
int main()
{
    long long int Box[10][10][64]={0};
    int t,k,i,j,l,p;
    Box[0][0][0]=1;
    for(k=1;k<10;k++)
    {
        Box[k][k][1]=1;
    }
    for(k=1;k<10;k++)
    {
        for(t=1;t<10;t++)
        {
            Box[k][t][2]=((k+t)!=0&&(k+t)!=1&&(k+t)!=4&&(k+t)!=9&&(k+t)!=16);
        }
    }
    for(i=3;i<64;i++)
    {
        for(k=1;k<10;k++)
        {
            for(t=1;t<10;t++)
            {
                if(Box[k][t][i-1]==0) continue;
                for(j=1;j<10;j++)
                {
                    if(Box[t][j][2])
                    {
                        for(l=1;l<10;l++)
                        {
                            Box[k][l][i]=((Box[k][l][i]+(Box[k][t][i-1]*Box[j][l][i-1])%MOD)%MOD);
                        }
                    }
                }
            }
        }
    }
    scanf("%d",&t);
    for(k=1;k<=t;k++)
    {
        long long int n;
        scanf("%lld",&n);
        if(n==1)
        {
            printf("6\n");
            continue;
        }
        long long int last_digits[10]={0};
        long long int mask=1,total_ways=0;
        for(j=0;j<61;j++)
        {
            mask=mask*2;
        }
        for(j=61;mask>0;j--,mask=mask/2)
        {
            long long int m=n&mask;
            if(m)
            {

                for(i=1;i<10;i++)
                {
                    for(l=1;l<10;l++)
                    {
                        last_digits[i]=(last_digits[i]+Box[l][i][j+1])%MOD;
                    }
                }
                break;
            }
        }
        for(j=j-1,mask=mask>>1;mask>0;j--,mask=mask>>1)
        {
            long long int m=n&mask;
            if(m==0) continue;
            long long int temp[10]={0};
            for(i=1;i<10;i++)
            {
                if(last_digits[i]==0) continue;
                for(l=1;l<10;l++)
                {
                    if(Box[i][l][2]==0) continue;
                    for(p=1;p<10;p++)
                    {
                        temp[p]=(temp[p]+(last_digits[i]*Box[l][p][j+1])%MOD)%MOD;
                    }
                }
            }
            for(i=1;i<10;i++)
            {
                last_digits[i]=temp[i];
            }
        }
        for(i=1;i<10;i++)
        {
            total_ways=(total_ways+last_digits[i])%MOD;
        }
        printf("%lld\n",total_ways);
    }
    return 0;
}
