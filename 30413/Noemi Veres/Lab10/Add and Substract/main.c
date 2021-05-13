#include <stdio.h>
#include <stdlib.h>
/// open a file (if possible)
FILE *openCheck (const char *path, const char *mode){
    FILE *pf = fopen(path,mode);
    if (pf == NULL){
        puts("cannot open the file");
        exit(1);
    }
    return pf;
}
/// memory allocation for an array of length n + initialize with 0
int *callocArray(int *a, int n){
    a = (int *)calloc(n,sizeof(int));
    return a;
}
/// fill the vector steps[] with the no. of steps needed to reach a certain number
void calculateSteps (int *steps, int N, int *v, int n, int ind){
    for (int i = 0; i < n; i++){
        if (steps[ind+v[i]] == 0){
            steps[ind+v[i]] = steps[ind] + 1;
        }
        if (ind-v[i] && steps[ind-v[i]] == 0){
            steps[ind-v[i]] = steps[ind] + 1;
        }
    }
}
int main(int argc, char *argv[]){
    FILE *pIn = openCheck("in.txt", "r");
    FILE *pOut = openCheck("out.txt", "w");
    int A, B, v[30], n = 0;
    fscanf(pIn,"%d",&A);
    fscanf(pIn,"%d",&B);
    fscanf(pIn,"%d",&v[n]);
    while (!feof(pIn)){
        n++;
        fscanf(pIn,"%d",&v[n]);
    }
    int N = abs(A-B)+1, *steps;
    steps = callocArray(steps,N);
    calculateSteps(steps,N,v,n,0);
    int st = 1, ok = 1;
    while(steps[N-1] == 0 && ok == 1){
        ok = 0;
        for (int i = 1; i < N; i++)
            if (steps[i] == st){
                calculateSteps(steps,N,v,n,i);
                ok = 1;
            }
        st++;
    }
    /*for (int i = 0; i < N; i++)
        printf("%d ",steps[i]);*/
    fprintf(pOut,"%d",steps[N-1]);
    fclose(pIn);
    fclose(pOut);
    return 0;
}
