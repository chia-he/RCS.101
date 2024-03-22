#include <stdio.h>

int countStudents(int* students, int studentsSize, int* sandwiches,
                  int sandwichesSize) {
    if (!students)
        return sandwichesSize;
    else if (!sandwiches)
        return 0;

    int st_cnt = 0;
    int st_full = 0;
    int st_head = 0;
    int st_tail = studentsSize - 1;
    int sd_top = 0;
    int sd_size = sandwichesSize;
    while (sd_top < sd_size) {
        // find a pair
        if (students[st_head] == sandwiches[sd_top]) {
            sd_top++;  // dequeue
            st_full++;  // queue size decrease
            st_cnt = 0; // refresh the number
        } else {
            st_tail = st_tail + 1 < studentsSize
                          ? (st_tail + 1)
                          : (st_tail + 1) % studentsSize; // circular queue
            students[st_tail] = students[st_head]; // cover the used data
            st_cnt++;  // counting the number of students unable to eat
        }
        // no one take the sandwich
        if (st_cnt == studentsSize - st_full) break;
        // next student
        st_head = st_head < (studentsSize - 1)
                      ? (st_head + 1)
                      : (st_head + 1) % studentsSize;
    }
    return st_cnt;
}

// int main() {
//     int students[] = {1,1,0,0};
//     int studentsSize = sizeof(students) / sizeof(students[0]);
//     int sandwiches[] = {0,1,0,1};
//     int sandwichesSize = sizeof(sandwiches) / sizeof(sandwiches[0]);

//     int ans = countStudents(students, studentsSize, sandwiches, sandwichesSize);
//     printf("Ans: %d", ans);
// }