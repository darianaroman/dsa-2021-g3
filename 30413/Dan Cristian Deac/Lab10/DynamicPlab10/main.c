#include <stdio.h>
#include <stdlib.h>


int closest = -10;
int recursiveBinarySearch(int array[], int start_index, int end_index, int element){
   int middle;
   if (end_index >= start_index){
      middle = start_index + (end_index - start_index )/2;
      if (array[middle] == element)
         return middle;
      if (array[middle] > element)
      {
          closest = middle;
          return recursiveBinarySearch(array, start_index, middle-1, element);
      }

      closest = middle;
      return recursiveBinarySearch(array, middle+1, end_index, element);
   }

   return -1;
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int find_close(int num, int *V, int V_size)
{
    ///if the NUM in V its over in 1 operation
    if(recursiveBinarySearch(V,0, V_size - 1, num)!=-1)
    {
        return V[recursiveBinarySearch(V,0, V_size - 1, num)];
    }

    else  /// this is to find the closest number to NUM in V
    {   int result = V[closest];
        if(result > num)
        {
            if(result - num < num - V[closest-1] && closest-1 >= 0)
                return V[closest];
            return V[closest-1];
        }
        else if(result < num)
        {
            if(num - result < V[closest+1] - num && closest+1 <= V_size)
                return V[closest];
            return V[closest+1];
        }

    }
    return -1;
}


int main()
{
    char ch;
    FILE *f = fopen("data.txt", "r");
    int A, B, V[100];
    fscanf(f, "%d", &A);
    fscanf(f, "%d", &B);
    //printf("%d %d", A, B);

    ///read numbers in V
    int V_size = 0;
    while((ch = fgetc(f)) != EOF)
    {
        fscanf(f, "%d", &V[V_size++]);
    }
    V_size--;

    quickSort(V, 0, V_size - 1);


    int num; /// the number that needs to be found with V elements
    if (A < B)
        num = B - A;
    else
        if (B < A)
            num = A - B;
    else {
        printf("B is A");
        return 0;
    }

    //num = 15;
    //printf("%d\n", num);

    if (recursiveBinarySearch(V,0, V_size - 1, num)!= -1)
    {
        printf("1");
        return 0;
    }


    ///sum method for 2 move solution //////////////////////////////
    ///basically if there is a number that has a complementary to NUM in V then its 2 moves to get B from A
    for(int i = 0; i < V_size; i++)
    {
        //printf("%d\n", V[i]);
        if(V[i] < num){
            if(recursiveBinarySearch(V,0, V_size - 1,num - V[i])!=-1)
            {
                printf("2\n");
                //printf("%d", V[recursiveBinarySearch(V,0, V_size - 1,num - V[i])]);
                return 0;
            }
        } else
        {
            if(recursiveBinarySearch(V,0, V_size - 1,V[i] - num)!=-1)
            {
                printf("2\n");
                //printf("%d", V[recursiveBinarySearch(V,0, V_size - 1,num - V[i])]);
                return 0;
            }
        }

    }
    //printf("layer2 sol");

    /// ////////////////////////////////////////////////////////////




    /// For solutions > 2 i made this algorithm that does its best to find the minimum number of moves but it is not accurate

    int result = find_close(num, V, V_size);
    int times = 0;

int last = 0;
int error = 0;
    while(num != 0)
    {printf("%d \n", result);
        if(result < num)
            num -=result;
        else
            num = result - num;

        result = find_close(num, V, V_size);


        if(result == 0 || error > 50)
        {
            printf("cant solve");
            return 0;
        }

        if(last == result)
            error++;
        last = result;
        times++;
    }



    printf("%d", times);
/*
    printf("\n");
    //printing the vector
    for(int i =0; i < V_size; i++)
        printf("%d ", V[i]);

*/

    return 0;
}
