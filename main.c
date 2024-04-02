#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printSubsetArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            printf("%d ", arr[i]);
        } else {
            break;
        }
    }
    printf("\n");
}

void printTable(int **table, int arr[], int n, int k) {
    //print column labels
    printf("   ");
    for(int i = 0; i <= k; i++) {
        printf("%3d ", i);
    }
    printf("\n");

    //print table values
    for (int i = 0; i < n; i++) {
        //print row labels
        printf("%d  ", arr[i]);
        for (int j = 0; j <= k; j++) {
            printf("%3d ", table[i][j]);
        }
        printf("\n");
    }
}

void sort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        for (j = i -1; j >= 0; j--) {
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
            } else {
                
                break;
            }
        }
        arr[j+1] = key;
        
    }
}
 
int *sliceArray(int *arr, int end) {
    int *slicedArray = (int*) malloc(end*sizeof(int));
    for (int i = 0; i < end; i++) {
        slicedArray[i] = arr[i];
    }

    return slicedArray;
}

void initializeTable(int **arr, int n, int k) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            arr[i][j] = 0;
        }
    }
}

void fillTable(int **table, int arr[], int n, int k) {
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            table[i][0] = 1;
            table[i][arr[i]] = 1;
        } else {
            for (int j = 0; j <= k; j++) {
                if (j < arr[i] ) {
                    if (table[i-1][j]) 
                        table[i][j] = 1; 
                } 
                else {
                    if (table[i-1][j] || table[i-1][j-arr[i]])
                        table[i][j] = 1;
                }
            }
        }
    }
}

int* traceSubset(int **table, int arr[], int n, int k) {
    // printTable(table, arr, n, k);
    int *subset = (int*) malloc(n*sizeof(int));;
    int subsetCount = 0;

    int i;
    for (i = 0; i < n; i++) {
        if (table[i][k] == 1) {
            subset[subsetCount] = arr[i];
            subsetCount++;
            break;
        }
    }

    if (subsetCount == 0) {
        return subset;
    }

    int current_col = k;

    for (int j = i-1; j >= 0; j--) {
        current_col = current_col-arr[j+1];
        while (j > 0 && table[j-1][current_col] == 1) {
            j--;
        }

        if (current_col != 0) {
            subset[subsetCount] = arr[j];
            subsetCount++;
        } 
    }

    return sliceArray(subset, subsetCount);

}


int main() {
    int array[] = {3, 2, 9, 7, 5};
    int n = 5;
    int k = 21;
    sort(array, n);
    printf("Array: \n");
    printArray(array, n);

    //allocate table with memory
    int **subsetTable = (int**) malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++) {
        subsetTable[i] = (int*) malloc((k+1)*sizeof(int));
    }

    //fill the table with zeroes
    initializeTable(subsetTable, n, k);
    printf("\n");

    //fill the table by 1's and 0's
    fillTable(subsetTable, array, n, k);
    printf("Matix:\n");
    printTable(subsetTable, array, n, k);
    printf("\n");

    //track down the numbers that make up the subset
    int *subset = traceSubset(subsetTable, array, n, k);
    
    //
    if (subset[0]) {
        printf("A subset of the array that add up to %d is: ", k);
        printSubsetArray(subset, n);
    } else {
        printf("No subset was found!\n");
    }
    
    return 0;
}