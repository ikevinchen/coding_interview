#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
int map_num[10]     = {0  , 0  , 3  , 3  , 3  , 3  , 3  , 4  , 3  , 4};
char map_letter[10] = {' ', ' ', 'a', 'd', 'g', 'j', 'm', 'p', 't', 'w'};
char** letterCombinations(char* digits, int* returnSize) {
    int digit_num = strlen(digits);
    int combination_num = 1;
    int i, j;
    char **answer = NULL;
    if (digits[0] == '\0') {
        * returnSize = 0;
        return NULL;
    }
    for (i = 0; i < digit_num; i++) {
        combination_num *= map_num[digits[i]-'0'];
    }
    answer = malloc(combination_num * sizeof(char*));
    for (i = 0; i < combination_num; i++) {
        answer[i] = malloc((digit_num+1) * sizeof(char));
        memset(answer[i], 0, (digit_num+1));
    }
    int fill_num = combination_num;
    for (i = 0; i < digit_num; i++) {
        fill_num = fill_num /  map_num[digits[i]-'0'];
        for (j = 0; j < combination_num; j++) {
            answer[j][i] = map_letter[digits[i]-'0'] + ((j / fill_num) % map_num[digits[i]-'0']);
        }
    }

    *returnSize = combination_num;
    return answer;
}

int main()
{
    int answer_size, i;
    char **answer = letterCombinations("abd", &answer_size);
    printf("%d\n", answer_size);
    for (i = 0;i < answer_size; i++) {
        printf("%s\n", answer[i]);
    }
    return 0;
}
