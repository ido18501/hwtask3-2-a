#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*******************************Defines****************************************/
#define ARR_MAX_LENGTH 50

/***************************Function declarations******************************/
/**
 * @fn search_shift_arr
 * @brief Return the index of 'target' in the shifted array arr.
 * @param arr - Shifted array of uniq integers.
 * @param n - Length of arr.
 * @param target - Number to find.
 * @return - Index of target, or -1 if target doesnt in the array.
 * @note Shifted array is sorted array in which an unknown number of its last
 * elements have been flipped be first.
 * @note Time complex is O(log(n)).
 */
int search_shift_arr(int arr[], int n, int target);

int check_close_nums(int arr[], int i, int n);
int sit_check(int *high, int *low, int *mid, int arr[], int *target, int *n);
int check_moved_nums(int arr[], int i, int n, int *high, int *low, int target);

int main() {
    int arr[ARR_MAX_LENGTH] = {0};
    int n = 0;
    int target = 0;

    printf("Please enter array length:\n");
    scanf("%d", &n);
    printf("Please enter target number:\n");
    scanf("%d", &target);
    printf("Please enter shifted array:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    printf("%d\n", search_shift_arr(arr, n, target));
    return 0;
}

/*************************Functions implementations****************************/
int search_shift_arr(int arr[], int n, int target) {
    //searching
    int low = 0;
    int high = n - 1;
    int mid;
    while (low <= high) {
        if (high + low == 1 && arr[1] == target) {
            //special case
            return 1;
        }
        mid = (high + low) / 2;
        if (arr[mid] == target) {
            //returning value if fund
            return mid;
        }
        sit_check(&high, &low, &mid, arr, &target, &n);
        //above checking situation
    }
    return -1;

}

int sit_check(int *high, int *low, int *mid, int arr[], int *target, int *n) {
    int k = check_close_nums(arr, *mid, *n);
    //checking neighbors
    if (k == 0) {
        //special case that needs farther checking
        check_moved_nums(arr, *mid, *n, high, low, *target);
    }
    if (k == 1) {
        //right on the last shifted number
        if (arr[*mid] > *target && arr[0] <= *target) {
            *high = *mid - 1;
        } else {
            *low = *mid + 1;
        }
    } else if (k == -1) {
        //right on the first number of original array
        if (arr[0] > *target && arr[*mid] <= *target) {
            *low = *mid + 1;
        } else {
            *high = *mid - 1;
        }
    }
    return 0;
}

int check_close_nums(int arr[], int i, int n) {
    //checking neighbors and returning values
    if (arr[i] > arr[i - 1] || i == 0) {
        if (arr[i] < arr[i + 1] || i == n - 1) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return -1;
    }
}

int check_moved_nums(int arr[], int i, int n, int *high, int *low, int target) {
    // if was normal - checking whether index is within
    // shifted numbers or not, then changing high/low accordingly
    if (arr[i] > arr[n - 1]) {
        if (arr[i] > target && arr[0] <= target) {
            *high = i - 1;
        } else {
            *low = i + 1;
        }
        return 0;
    }
    if (arr[i] < target && arr[n - 1] >= target) {

        *low = i + 1;
    } else {
        *high = i - 1;
    }
    return 0;
}
