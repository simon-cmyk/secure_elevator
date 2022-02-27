#include "array_handling.h"
#include <stdio.h>

int array_handling_find_max(int arr[], int arr_size){
    int max_val_arr = arr[0];
    for(unsigned int i = 0; i < arr_size; i++){
        if (arr[i] > max_val_arr){
            max_val_arr = arr[i];
        }
    }
    return max_val_arr;
}

void array_handling_print(int arr[], int arr_size){
    for (unsigned int i = 0; i < arr_size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}