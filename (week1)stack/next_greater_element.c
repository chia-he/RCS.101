#include <stdio.h>
#include <stdlib.h>

#include "..\header\cstack.h"
#include "..\header\hashmap.h"

const char* int_to_string(int num) {
    char* buffer = (char*)malloc(12);
    sprintf(buffer, "%d", num);
    return buffer;
}
int* next_greater_element(int* nums1, int* nums2, int size1, int size2) {
    const unsigned initial_size = size2;
    struct hashmap_s hashmap;
    hashmap_create(initial_size, &hashmap);
    cstack(int) cs = NULL;
    int sp_num = -1;
    // put whole number int nums2 into hashmap
    for (int i = size2 - 1; i >= 0; i--) {
        // default value is -1
        const char* str = int_to_string(nums2[i]);
        hashmap_put(&hashmap, str, strlen(str), &sp_num);
        // using stack to record the next greater value
        while (!cstack_empty(cs)) {
            int item = *cstack_top(cs);
            if (nums2[i] < item) {
                hashmap_put(&hashmap, str, strlen(str), &item);
                break;
            } else {
                cstack_pop(cs);
            }
        }
        cstack_push(cs, nums2[i]);
    }
    cstack_free(cs);

    // look up the hashmap
    int* ans = (int*)malloc(sizeof(int) * size1);
    for (int i = 0; i < size1; i++) {
        const char* str = int_to_string(nums1[i]);
        int* const element = hashmap_get(&hashmap, str, strlen(str));
        ans[i] = *element;
    }
    hashmap_destroy(&hashmap);
    
    return ans;
}

int main() {
    int nums1[] = {4, 1, 2};
    int nums2[] = {1, 3, 4, 2};
    int* ans = next_greater_element(nums1, nums2, 3, 4);

    for (int i = 0; i < 3; i++) {
        printf("%d, ", ans[i]);
    }
}