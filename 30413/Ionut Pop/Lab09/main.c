#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int v[100];
int max_sum=INT_MIN;

int seq_sum(int left, int right){
    int sum=0;
    for (int i=left;i<=right;++i)
        sum+=v[i];
    return sum;
}

int bin_search(int left, int right) {

    if(left < right) {
        int mid = (left + right) / 2;

        int sum=seq_sum(left, right);
        if (sum>max_sum)
            max_sum=sum;
        sum=seq_sum(left, mid);
        if (sum>max_sum)
            max_sum=sum;
        sum=seq_sum(mid, right);
        if (sum>max_sum)
            max_sum=sum;
        bin_search(left, mid);
        bin_search(mid + 1, right);
        return max_sum;
    }
    else if (left==right)
        return v[left];
}


int main()
{
    FILE *in=fopen("./in.txt", "r");
    FILE *out=fopen("./out.txt", "w");

    int n;
    fscanf(in, "%d", &n);
    for (int i=1;i<=n;++i)
        fscanf(in, "%d", &v[i]);

    bin_search(1, n);

    printf("max sum is: %d", max_sum);

    return 0;
}
