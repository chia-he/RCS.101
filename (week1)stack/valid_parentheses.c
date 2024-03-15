#include <stdio.h>
#include "..\header\cstack.h"
/**
 * @param  s: a string containing just '(', ')', '{', '}', '[' and ']'
 * @return 1 if it's valid, 0 if it's not valid.
 */
int is_valid_parentheses(char* s) {
    if (!s) return 0;
    cstack(char) char_stack = NULL;
    while (*s != '\0') {
        if (*s == '(' || *s == '[' || *s == '{') {
            cstack_push(char_stack, *s);
        } else {
            char* c = cstack_top(char_stack);
            if (cstack_empty(char_stack) || *c == '(' && *s != ')' ||
                *c == '[' && *s != ']' || *c == '{' && *s != '}')
                return 0;
            cstack_pop(char_stack);
        }
        s++;
    }
    return cstack_empty(char_stack);
}

// int main() {
//     char s[] = "()[]{}";

//     printf("Ans: %d", is_valid_parentheses(s));
// }