#include <stdio.h>
#include <stdlib.h>

#include "..\header\cstack.h"

int score(char *s, int left, int right) {
    // case 1: "()"
    if (right - left == 1) return 1;
    int index = 0;
    for (int i = left; i < right; i++) {
        if (*(s + i) == '(')
            index++;
        else if (*(s + i) == ')')
            index--;
        // case 2: "() + ..."
        if (index == 0) return score(s, left, i) + score(s, i + 1, right);
    }
    // case 3: "(...)"
    return 2 * score(s, left + 1, right - 1);
}
int strLength(char *s) {
    int length = 0;
    char *ptr = s;
    while (ptr && *ptr != '\0') {
        length++;
        ptr++;
    }
    return length;
}
/**
 * @param  s: a balanced parentheses string
 * @retval integer score
 */
int scoreOfParentheses(char *s) { return score(s, 0, strLength(s) - 1); }

int main() {
    char s[] = "(()(()))";

    printf("score: %d\n", scoreOfParentheses(s));
}