#include <stdio.h>
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
int timeRequiredToBuy(int* tickets, int ticketsSize, int k) {
    if (!tickets) return 0;

    int total_time = 0;
    int time;
    // pass tickets[k] second
    for (int i = 0; i < ticketsSize; i++) {
        // the others behind k can only buy less than k
        if(i>k && tickets[i]>=tickets[k])
            time = tickets[k] - 1;
        else
            time = tickets[i];
        total_time += MIN(time, tickets[k]);
    }
    return total_time;
}

int main() {
    int tickets[] = {84, 49, 5, 24, 70, 77, 87, 8};
    int ticketsSize = sizeof(tickets) / sizeof(tickets[0]);
    int k = 3;

    int ans = timeRequiredToBuy(tickets, ticketsSize, k);
    printf("Total: %d\n", ans);
}