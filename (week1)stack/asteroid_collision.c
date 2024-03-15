#include <stdio.h>
#include "..\header\cstack.h"

/**
 * @note go right if positive, go right if negative.
 * @param  asteroids: a list of integers
 * @return a list of integers
 */

int sameSign(int a, int b) { return a > 0 && b > 0 || a < 0 && b < 0; }
int* asteroidCollision(int* asteroids, int asteroidsSize, int* returnSize) {
    /**
     * 1.Create a support stack, sup.
     * 2.Sequentially peek the asteroids and sup at the same time.
     * 3.If sup is empty, push one item.
     * 4.If number is positive, push it into sup.
     * 5.If sup top and number are same sign, push it into sup.
     * 6.If number is negative, peek sup.
     * 7.pop the smaller size or both while same size.
     */
    cstack(int) sup = NULL;
    for (int i = 0; i < asteroidsSize; i++) {
        int num_1 = *(asteroids + i);
        if (cstack_empty(sup) || num_1 > 0) {
            cstack_push(sup, num_1);
        } else {
            int num_2 = *cstack_top(sup);
            if (sameSign(num_1, num_2))
                cstack_push(sup, num_1);
            else {
                if (num_1 + num_2 < 0) {
                    cstack_pop(sup);
                    i--;
                }
                else if (num_1 + num_2 == 0) {
                    cstack_pop(sup);
                }
            }
        }
    }
    *returnSize = cstack_size(sup);
    return sup;
}

// int main() {
//     int arr[] = {5, 10, -5};
//     int arrSize = sizeof(arr) / sizeof(arr[0]);
//     int returnSize = 0;

//     int* ans = asteroidCollision(arr, arrSize, &returnSize);

//     for (int i = 0; i < returnSize; i++) {
//         printf("%d,", *(ans + i));
//     }
//     cstack_free(ans);
// }