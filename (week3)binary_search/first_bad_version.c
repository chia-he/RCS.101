#include <stdio.h>
#include <stdbool.h>

bool isBadVersion(int version){
    return version>=4;
}

int firstBadVersion(int n) {
    if(n < 0) return -1;

    int left = 1;
    int right = n;

    while(left < right){
        int mid = left + (right-left)/2;
        if(!isBadVersion(mid))
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

int main(){
    int n = 5;
    int ans = firstBadVersion(n);
    printf("Ans: %d\n", ans);
}