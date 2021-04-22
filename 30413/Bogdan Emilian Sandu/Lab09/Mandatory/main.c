#include <stdio.h>

int max(int a, int b){
    if(a > b) return a;
    else return b;
}

int maxS(int array[], int len){
    if(len == 1)
        return array[0];
    int mid = len / 2;
    int left,right,leftS,rightS;
    left = maxS(array, mid);
    right = maxS(array + mid, len - mid);
    leftS = array[mid-1];
    rightS = array[mid];
    int sum = 0;
    for( int i = mid-1; i >= 0; i--){
        sum = sum + array[i];
        leftS = max(leftS,sum);
    }
    sum = 0;
    for ( int i = mid; i < len; i++){
        sum = sum + array[i];
        rightS = max(rightS,sum);
    }
    int MAX = max(left,right);
    return max(MAX,leftS + rightS);
}

int main(int argc, char *argv[]) {
    FILE *input, *output;
    input = fopen(argv[1],"r");
    if(input == NULL)
        exit(1);
    int d,nr,i,rez;
    nr = 0;
    i = 0;
    input = fopen(argv[1],"r");
    fscanf(input,"%d",&nr);
    //while (fscanf(input,"%d",&d) == 1){
    //    nr++;
    //}
    //fseek(input,0,SEEK_SET);
    int array[nr];
    while (fscanf(input,"%d",&d) == 1){
        array[i] = d;
        i++;
    }
    rez = maxS(array,nr);
    output = fopen(argv[2],"w");
    fprintf(output,"%d",rez);
    return 0;
}
