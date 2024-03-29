#include <stdio.h>
#include <math.h>

int eatingAll(int* piles, int pilesSize, int h, int k){
    if(k <= 0) return 0;
    
    int max_time = h;
    for(int i = 0; i < pilesSize; i++){
        max_time -= ceil((double)piles[i]/(double)k);
        if(max_time < 0)
            break;
    }
    return max_time >= 0;
}

int minEatingSpeed(int* piles, int pilesSize, int h) {
    if(!piles) return 0;

    int left = 0;
    int right = 0;

    for(int i = 0; i < pilesSize; i++){
        if(piles[i]>right)
            right = piles[i];
    }

    while(left < right){
        int mid = left+(right-left)/2;
        if(!eatingAll(piles, pilesSize, h, mid)){
            left = mid + 1;
        }
        else{
            right = mid;
        }
    }
    return left;
}

int main(){
    int piles[] = {30,11,23,4,20};
    int pilesSize = sizeof(piles)/sizeof(piles[0]);
    int h = 5;
    int ans = minEatingSpeed(piles, pilesSize, h);
    printf("Ans: %d\n", ans);
}