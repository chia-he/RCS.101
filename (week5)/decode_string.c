#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\header\cstack.h"

int isAlpha(char s) {
    if (s == '\0')
        return 0;
    else if (s >= 'A' && s <= 'Z' || s >= 'a' && s <= 'z')
        return 1;
    return 0;
}
char* decodeString(char* s) {
    cstack(char) stack = NULL;

    char* ptr = s;
    while (*ptr != '\0') {
        if (*ptr == ']') {
            // [cba]
            cstack(char) sub_stack = NULL;
            cstack_push(sub_stack, '\0');
            while (!cstack_empty(stack)) {
                char c = *cstack_top(stack);
                cstack_pop(stack);
                if (c == '[')
                    break;
                else
                    cstack_push(sub_stack, c);
            }
            // [abc]
            int length = cstack_size(sub_stack);
            char* sub_s = (char*)malloc(sizeof(char) * length);
            for (int i = 0; i < length; i++) {
                sub_s[i] = *cstack_top(sub_stack);
                cstack_pop(sub_stack);
            }
            // mun
            cstack_push(sub_stack, '\0');
            while (!cstack_empty(stack)) {
                char c = *cstack_top(stack);
                if (isAlpha(c) || c == '[')
                    break;
                else
                    cstack_push(sub_stack, c);
                cstack_pop(stack);
            }
            // num
            length = cstack_size(sub_stack);
            char* num_s = (char*)malloc(sizeof(char) * length);
            for (int i = 0; i < length; i++) {
                num_s[i] = *cstack_top(sub_stack);
                cstack_pop(sub_stack);
            }
            // string num to int num
            int times = (int)strtol(num_s, NULL, 10);
            for (int i = 0; i < times; i++) {
                for (int j = 0; j < strlen(sub_s); j++)
                    cstack_push(stack, sub_s[j]);
            }
            cstack_free(sub_stack);
        } else
            cstack_push(stack, *ptr);
        ptr++;
    }

    int strLength = cstack_size(stack) + 1;
    char* decoded = (char*)malloc(sizeof(char) * strLength);

    for (int i = strLength - 2; i >= 0; i--) {
        decoded[i] = *cstack_top(stack);
        cstack_pop(stack);
    }
    decoded[strLength - 1] = '\0';
    cstack_free(stack);
    return decoded;
}

int main() {
    char s[] = "3[a2[b]]";

    char* decoded = decodeString(s);
    printf("%s\n", decoded);

    free(decoded);
}