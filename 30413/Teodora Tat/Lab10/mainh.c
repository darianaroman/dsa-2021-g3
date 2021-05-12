#include <stdio.h>
#include <stdlib.h>
void f(int A, int B, int v[],int n,FILE* fi)
{   int nrop=0;
    while(fscanf(fi,"%d",&v[100]))
    {
        n++;
    }
    int m;
    if(A>B)
        m=A-B;
    else
        m=B-A;
        while(m!=0)
        {
            for(int i=0;i<n;i++)
            {nrop=0;
                while(m>0)
                {m=m-v[i];
                nrop++;}
                    while(m<0)
                    {m=m-v[i];
                    nrop++;}

            }
            if(nrop==0)
                printf("%d ", nrop);
        }
}
int main()
{ FILE* fi;
    int A,B,v[100], n;
    fi = fopen("file.txt", "r");
    fscanf(fi, "%d%d", &A,&B);
    f(A,B,v[100],n,"file.txt");

    return 0;
}
