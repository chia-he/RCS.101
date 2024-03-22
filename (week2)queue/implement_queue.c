#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct ListNode {
        int val;
        struct ListNode* next;
} ListNode;

typedef struct cqueue {
        int size;
        struct ListNode* head;
        struct ListNode* tail;
} cqueue;

cqueue* cqueue_create() {
    cqueue* cq = (cqueue*)malloc(sizeof(cqueue));
    cq->size = 0;
    cq->head = (ListNode*)malloc(sizeof(ListNode));
    cq->tail = cq->head;
    cq->tail->next = NULL;
    return cq;
}
bool cqueue_empty(cqueue* cq) { return cq->size == 0; }

void cqueue_enqueue(cqueue* cq, int item) {
    cq->tail->val = item;
    cq->tail->next = (ListNode*)malloc(sizeof(ListNode));
    cq->tail = cq->tail->next;
    cq->size++;
}
int cqueue_dequeue(cqueue* cq) {
    if (cqueue_empty(cq)) return ~0;
    ListNode *temp = cq->head;
    int item = temp->val;
    cq->head = temp->next;
    cq->size--;
    free(temp);
    return item;
}
int cqueue_peek(cqueue* cq) {
    if (cqueue_empty(cq)) return ~0;
    return cq->head->val;
}
void cqueue_free(cqueue* cq) { 
    for(int i = 0; i < cq->size; i++){
        ListNode *temp = cq->head;
        cq->head = temp->next;
        free(temp);
    }
    free(cq);
}

// int main() {
//     cqueue* obj = cqueue_create(10);

//     cqueue_enqueue(obj, 10);
//     cqueue_enqueue(obj, 12);
//     int param_2 = cqueue_dequeue(obj);
//     int param_3 = cqueue_peek(obj);
//     bool param_4 = cqueue_empty(obj);
//     int param_5 = cqueue_dequeue(obj);
//     bool param_6 = cqueue_empty(obj);

//     printf("Result:\n[Dequeue(), Peek(), Empty(), Dequeue(), Empty()]\n");
//     printf("[%9d, %6d, %7d, %9d, %7d]", param_2, param_3, param_4, param_5,
//            param_6);

//     cqueue_free(obj);
// }