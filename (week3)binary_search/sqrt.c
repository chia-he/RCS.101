#include <stdio.h>

int mySqrt(int x) {
    if(x==0 || x==1) return x;

    int left = 0;
    int right = x;
    while(left <= right){
        int mid = left + (right-left) / 2;
        int div = x/mid;
        if(mid == div){
            return mid;
        }
        else if(mid < div){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }

    return right;
}

int main(){
    int x = 35;
    int ans = mySqrt(x);
    printf("Ans: %d\n", ans);
}