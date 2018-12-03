#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*  check substr[index] if match pattern
    policy : 0 (find the shotest match) 1 (longest match)
       return the end index, if check okay,
       return -1, if failed
*/
int check(int index, const char * const str, const char *pattern, int policy) {
    if (*pattern == '\0') {
        return index;
    } else {
        if (*(pattern + 1) == '*') {
            /* str[index] should not be '.' */

            /* ex. pattern = "a*aa"
             *     input = "aa"
             *       ==> it matched, however pattern[0] shuold not be used
             */

            /* find the possible max expading number */
            int expading_max = 0;
            while(str[index+expading_max] != '\0') {
                if (str[index+expading_max] == *pattern) {
                    expading_max++;
                } else {
                    break;
                }
            }

            if (policy == 0) {
                int expading_i;
                for (expading_i = 0; expading_i <= expading_max;
                     expading_i++) {
                    int result = check(index + expading_i, str, pattern + 2, policy);
                    //printf("check index = %d, pattern = %s, return %d\n",
                    //       index + expading_i, pattern + 2, result);
                    if (result != -1) {
                        return result;
                    }
                }
                return -1;
            } else {
                int expading_i;
                for (expading_i = expading_max; expading_i >= 0;
                     expading_i--) {
                    int result = check(index + expading_i, str, pattern + 2, policy);
                    if (result != -1) {
                        return result;
                    }
                }
                return -1;
            }
        } else {
            if (str[index] == '\0') {
                return -1;
            }
            if (*pattern == '.' || str[index] == *pattern) {
                return check(index + 1, str, pattern + 1, policy);
            } else {
                return -1;
            }
        }
    }
}

/*  Find out the min index that substr[index] if match pattern
       return the end index, if check okay,
       return -1, if not existed
*/
int find_nearest_match(int start_index, const char * const str, const char *pattern) {
    int index = start_index;
    int find_out_end_index = -1;
    while(str[index] != '\0') {
        find_out_end_index = check(index, str, pattern, 0);
        if (find_out_end_index != -1) {
            break;
        }
        index++;
    }
    return find_out_end_index;
}

/*
   Check it this str is ennding with pattern, with uppper start limi
      0 : yes, -1: no
 */
int check_ending_with_pattern(int uplimit_index,
                              const char * const str,
                              const char *pattern) {
    int str_len = strlen(str);
    int check_result = -1;
    int i;
    for (i = str_len; i >= uplimit_index; i--) {
        check_result = check(i, str, pattern, 1);
        //printf("(check_ending_with_pattern) i = %d, return %d\n", i, check_result);
        if (check_result == str_len) {
        //    printf("success\n");
            return 0;
        }
    }
    return -1;
}

/* check regr match, 0 : yes, -1: no */
int regr_match(const char *str, const char *pattern) {

    if (pattern[0] == '\0') {
        return -1;
    }

    char *sub_pattern = malloc((strlen(pattern) + 1) * sizeof(char));
    int str_idx = 0;
    int pattern_idx = 0;
    int sub_pattern_idx = 0;

    int the_first_pattern = 0;

    memset(sub_pattern, 0, strlen(pattern) + 1); /* init */
    sub_pattern_idx = 0;

    while(pattern[pattern_idx] != '\0') {
        //printf("== %d ==\n", pattern_idx);
        if (pattern[pattern_idx] == '.' && pattern[pattern_idx + 1] == '*') {
            pattern_idx += 2;
            if (sub_pattern[0] != '\0') {
                int end_index;
                if (the_first_pattern == 1) {
                    end_index = check(0, str, sub_pattern, 0);
                } else {
                    end_index = find_nearest_match(str_idx, str, sub_pattern);
                }
                //printf("check sub-pattern %s, start = %d, return end = %d\n"
                //       , sub_pattern, str_idx, end_index);
                if (end_index == -1) {
                    return -1;
                }
                str_idx = end_index;
                memset(sub_pattern, 0, strlen(pattern) + 1); /* reset */
                sub_pattern_idx = 0;
                the_first_pattern = 0;
            }
        } else {
            //printf("  -- add %c --\n", pattern[pattern_idx]);
            if (pattern_idx == 0) {
                the_first_pattern = 1;
            }
            sub_pattern[sub_pattern_idx] = pattern[pattern_idx];
            sub_pattern_idx++;
            pattern_idx++;
        }
    }

    /* if there are still some pattern not checked
     *  (1) first and only one pattern  (ex. pattern = "a*b", sub-pattern = "a*b")
     *  (2) ending pattern (ex. pattern = ".*a*b", sub-pattern = "a*b")
     */
    //printf("sub_pattern %s\n", sub_pattern);
    if (sub_pattern[0] != '\0') {
        //printf("sub_pattern %s\n", sub_pattern);
        if (strcmp(pattern, sub_pattern) == 0) {
            int result = check(0, str, pattern, 1);
            //printf("check first and only one pattern %s, return %d\n",
            //       pattern, result);
            if (result == strlen(str)) {
                return 0;
            } else {
                return -1;
            }
        } else {
            //printf("chek pattern %s at ending\n", sub_pattern);
            return check_ending_with_pattern(str_idx, str, sub_pattern);
        }
    } else {
        return 0;
    }
}

int main(){
    #if 1
    printf("%s\n", regr_match("abc", "abc")==0 ? "true" :"false"); // true
    printf("%s\n", regr_match("abc", "a..")==0 ? "true" :"false"); // true
    printf("%s\n", regr_match("abc", "a.")==0 ? "true" :"false"); // false
    printf("%s\n", regr_match("abc", "a.*")==0 ? "true" :"false"); // true
    printf("%s\n", regr_match("abc", ".*")==0 ? "true" :"false"); // true
    printf("%s\n", regr_match("abc", ".*c")==0 ? "true" :"false"); // true
    printf("%s\n", regr_match("abc", ".*cd")==0 ? "true" :"false"); // false
    printf("%s\n", regr_match("abc", "a.*c")==0 ? "true" :"false"); // true
    printf("%s\n", regr_match("ac", "a.*c")==0 ? "true" :"false"); // true
    printf("%s\n", regr_match("abc", "a*c")==0 ? "true" :"false"); // false
    printf("%s\n", regr_match("a", "a*a")==0 ? "true" :"false"); // true
    printf("%s\n", regr_match("aa", "a*")==0 ? "true" :"false"); // true
    printf("%s\n", regr_match("abbbc", ".*b*c")==0 ? "true" :"false"); // true
    printf("%s\n", regr_match("a", "ab*")==0 ? "true" :"false"); // true
    printf("%s\n", regr_match("b", "b.*c")==0 ? "true" :"false"); // false
    printf("%s\n", regr_match("aab", "b.*")==0 ? "true" :"false"); // false

    printf("%s\n", regr_match("ab", ".*b*")==0 ? "true" :"false"); // true
    #endif
    printf("%s\n", regr_match("abcbccbcba abbcbb", "c*a.*ab*.*ab*a*..b*")
            ==0 ? "true" :"false"); // true
    return 0;
}





