#include <stdio.h>
#include <stdlib.h>
#include "..\header\cstack.h"
typedef struct Employee {
        int id;
        int importance;
        int numSubordinates;
        int* subordinates;
} Employee;

Employee* findEmployee(Employee* employees, int numEmployees, int id) {
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].id == id) {
            return &employees[i];
        }
    }
    return NULL;
}
int sumImportance(Employee* employees, int numEmployees, int id) {
    Employee* target = findEmployee(employees, numEmployees, id);
    if (!target || numEmployees == 0) return 0;
    int sum_imp = target->importance;
    for (int i = 0; i < target->numSubordinates; i++) {
        sum_imp +=
            sumImportance(employees, numEmployees, target->subordinates[i]);
    }
    return sum_imp;
}
int getImportance(Employee* employees, int numEmployees, int id) {
    // 1. Find the target id.
    // 2. Find all the target's subordinates.
    // 3. Summation all importance.
    return sumImportance(employees, numEmployees, id);
}
/*
 * Iterative version
int getImportance(Employee* employees, int numEmployees, int id) {
    Employee* target = findEmployee(employees, numEmployees, id);
    if (!target) return 0;

    cstack(Employee) cs = NULL;
    cstack_push(cs, *target);

    int sum_importance = 0;
    while (!cstack_empty(cs)) {
        Employee current = *cstack_top(cs);
        cstack_pop(cs);
        sum_importance += current.importance;
        for (int i = 0; i < current.numSubordinates; i++) {
            Employee* sub =
                findEmployee(employees, numEmployees, current.subordinates[i]);
            if (sub) cstack_push(cs, *sub);
        }
    }
    cstack_free(cs);

    return sum_importance;
}
*/
// Employee createEmployee(int id, int imp_factor, int numS, int* id_list) {
//     Employee person;
//     person.id = id;
//     person.importance = imp_factor;
//     person.numSubordinates = numS;
//     person.subordinates = (int*)malloc(sizeof(int) * numS);
//     if (person.subordinates)
//         memcpy(person.subordinates, id_list, sizeof(int) * numS);
//     return person;
// }
// int main() {
//     int id = 1;
//     int numEmployees = 4;
//     Employee* employees = (Employee*)malloc(sizeof(Employee) * numEmployees);
//     int subordinates_1[] = {2, 3};
//     employees[0] = createEmployee(1, 5, 2, subordinates_1);
//     int subordinates_2[] = {4};
//     employees[1] = createEmployee(2, 3, 1, subordinates_2);
//     employees[2] = createEmployee(3, 4, 0, NULL);
//     employees[3] = createEmployee(4, 1, 0, NULL);

//     printf("Importance of ID %d: %d", id,
//            getImportance(employees, numEmployees, id));
// }