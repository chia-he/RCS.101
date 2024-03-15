#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
        int size;
        int capacity;
        int* array;
} cstack;

cstack* cstack_create(int n) {
    cstack* cs = (cstack*)malloc(sizeof(cstack));
    cs->size = 0;
    cs->capacity = n > 0 ? n : 10;
    cs->array = (int*)malloc(sizeof(int) * cs->capacity);
    return cs;
}
bool cstack_empty(cstack* cs) { return cs->size == 0; }
void cstack_grow(cstack* cs) {
    cs->capacity += 1;
    cs->array = (int*)realloc(cs->array, sizeof(int) * cs->capacity);
}
void cstack_push(cstack* cs, int item) {
    if (cs->size == cs->capacity) cstack_grow(cs);
    cs->array[cs->size++] = item;
}
int cstack_pop(cstack* cs) {
    if (cstack_empty(cs)) return ~0;
    return cs->array[--cs->size];
}
int cstack_top(cstack* cs) {
    if (cstack_empty(cs)) return ~0;
    return cs->array[cs->size - 1];
}
void cstack_free(cstack* cs) { free(cs); }

// int main() {
//     cstack* obj = cstack_create(10);

//     cstack_push(obj, 10);
//     cstack_push(obj, 12);
//     int param_2 = cstack_pop(obj);
//     int param_3 = cstack_top(obj);
//     bool param_4 = cstack_empty(obj);
//     int param_5 = cstack_pop(obj);
//     bool param_6 = cstack_empty(obj);

//     printf("Result:\n[Pop(), Top(), Empty(), Pop(), Empty()]\n");
//     printf("[%5d, %5d, %7d, %5d, %7d]", param_2, param_3, param_4, param_5,
//            param_6);

//     cstack_free(obj);
// }