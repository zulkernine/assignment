#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int comparisonOrder(int n1, int n2){
    if (n1 <= n2) return -1; //ascending order
    else return 1; //Descending order
}
int sortedOrder(int* arr, int size){
    if (size < 2){
        return -1;//default ascending: -1
    }

    int order = comparisonOrder(arr[0], arr[1]);
    for (int i = 1;i < size - 1;i++){
        if (order == comparisonOrder(arr[i], arr[i + 1])) continue;
        else{
            return 0; // Not sorted
        }
    }

    return order;
}

int* merge_sorted_array(int* arr1, int size1, int* arr2, int size2, int order){
    int n = size1 + size2;
    int* merged = (int*)malloc(n * sizeof(int));

    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2){
        switch (order){
        case -1:{
            if (arr1[i] < arr2[j]){
                merged[k] = arr1[i];
                i++;
            }
            else if (arr1[i] == arr2[j]){
                merged[k] = arr1[i];
                j++;i++;
            }
            else{
                merged[k] = arr2[j];
                j++;
            }
            k++;
        }
               break;
        case 1:{
            if (arr1[i] > arr2[j]){
                merged[k] = arr1[i];
                i++;
            }
            else if (arr1[i] == arr2[j]){
                merged[k] = arr1[i];
                j++;i++;
            }
            else{
                merged[k] = arr2[j];
                j++;
            }
            k++;
        }
              break;
        }
    }

    while (i < size1) merged[k++] = arr1[i++];
    while (j < size2) merged[k++] = arr2[j++];

    //Feel rest of the array with INT_MAX or INT_MIN (if common elements are found, they are inserted once,)
    if (order == -1){
        while (k < n){
            merged[k++] = INT_MAX;
        }
    }
    else if (order == 1){
        while (k < n){
            merged[k++] = INT_MIN;
        }
    }

    return merged;
}




int main(){
    int* arr1, * arr2, size1, size2;
    printf(("Size of array-1: "));
    scanf("%d", &size1);
    if (size1 < 0){
        printf("invalid size\n");
        return 1;
    }
    arr1 = (int*)malloc(size1 * sizeof(int));
    printf("Enter array-1(all elemnts space separated): ");
    for (int i = 0;i < size1;i++) scanf("%d", arr1 + i);

    printf(("Size of array-2: "));
    scanf("%d", &size2);
    if (size2 < 0){
        printf("invalid size\n");
        return 1;
    }
    arr2 = (int*)malloc(size2 * sizeof(int));
    printf("Enter array-2(all elemnts space separated): ");
    for (int i = 0;i < size2;i++) scanf("%d", arr2 + i);

    int o1 = sortedOrder(arr1, size1), o2 = sortedOrder(arr2, size2);
    if (o1 != o2){
        printf("Sorted order of the arrays are different! Can't merge.\n");
        return 1;
    }
    else if (o1 * o2 == 0){
        printf("One of the array or both is unsorted. Can't merge!\n");
        return 1;
    }

    int* merged = merge_sorted_array(arr1, size1, arr2, size2, o1);
    printf("Merged array: ");
    for (int i = 0;i < size1 + size2;i++) printf("%d ", merged[i]);

    free(arr1);free(arr2);free(merged);

    printf("\n");
    return 0;
}

