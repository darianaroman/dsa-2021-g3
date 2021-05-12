#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///creating utility functions to calculate min

int min2(int a, int b)
{
    return (a <= b)? a:b;
}

int min3(int a,int b,int c)
{
    return min2(min2(a,b),c);
}

///function for computing edit and giving result

int DP(char s1[],char s2[],int l1,int l2)
{
    ///array for memoization
    int dp[l1+1][l2+1];

    for(int i=0;i<=l1;i++)
    {
        for(int j=0;j<=l2;j++)
        {
            /// first string is empty
            if( i==0 )
                    dp[i][j]= j;
               else
            /// second string is empty
            if( j==0 ) dp[i][j]= i;
               else
            /// last characters are the same
            if( s1[l1-1]==s2[l2-1] ) dp[i][j]= dp[i-1][j-1];
               else
            /// last characters are different
                dp[i][j]= 1+ min3( dp[i-1][j], dp[i][j-1], dp[i-1][j-1]);
        }
    }
    return dp[l1][l2];
}

int dp2[2000][2000];

int DP2(char s1[],char s2[],int l1,int l2)
{
    ///string 1 or 2 is empty
    if(l1==0) return l2;
    if(l2==0) return l1;

    if(dp2[l1][l2]!=-1) return dp2[l1][l2];

    ///if charachters are equal
    if(s1[l1-1]==s2[l2-1])
    {
        if(dp2[l1-1][l2-1]==-1)
           return DP2(s1,s2,l1-1,l2-1);
           else dp2[l1][l2]=dp2[l1-1][l2-1];
    }
    else /// find minimum of the 3 options of altering word
         {
             int a,b,c;
             ///calculating the needed options and memoization
             if(dp2[l1-1][l2]==-1) a=DP2(s1,s2,l1-1,l2);
                else a= dp2[l1-1][l2];
             if(dp2[l1-1][l2-1]==-1) b=DP2(s1,s2,l1-1,l2-1);
                else b= dp2[l1-1][l2-1];
             if(dp2[l1][l2-1]==-1) c=DP2(s1,s2,l1,l2-1);
                else c= dp2[l1][l2-1];

             return dp2[l1][l2]= 1+ min3(a,b,c);

         }

}

int main()
{
    int dp;
    char s1[]="heap",s2[]="pea";
    int l1=strlen(s1), l2=strlen(s2);
    for(int i=0;i<=l1;i++)
        for(int j=0;j<=l2;j++)
           dp2[i][j]=-1;

    dp= DP2(s1,s2,l1,l2);
    printf("\nThe minimum number of operations needed is %d",dp);

    return 0;
}
