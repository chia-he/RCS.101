#include <stdio.h>

int binarySearch(int *nums, int numsSize) {
    if (!nums) return -1;

    int left = 0;
    int right = numsSize - 1;
    // target nums[idx] - idx == 0;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < mid) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return nums[left] == left ? left : -1;
}

// int main() {
//     int nums[] = {0, 1, 3, 5, 7};
//     int numsSize = sizeof(nums) / sizeof(nums[0]);
//     int ans = binarySearch(nums, numsSize);
//     printf("Ans: %d\n", ans);
// }