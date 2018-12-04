#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run(const char* s, int s_i, const char* p, int p_i, int **DP)
{	
	if (p[p_i] == '\0') {
		if (s[s_i] == '\0') DP[s_i][p_i] = 1;
		else				DP[s_i][p_i] = 0;
	} else if (p[p_i + 1] != '*') {
		if (p[p_i] == '.' || p[p_i] == s[s_i]) {
			if (s[s_i] == '\0') {
				DP[s_i][p_i] = 0;
			} else {
				DP[s_i][p_i] = DP[s_i + 1][p_i + 1];
			}
		} else {
			DP[s_i][p_i] = 0;
		}
	} else {
		if (p[p_i] == '.' || p[p_i] == s[s_i]) {
			if (s[s_i] == '\0') {
				DP[s_i][p_i] = DP[s_i][p_i + 2];
			} else {
				DP[s_i][p_i] = DP[s_i + 1][p_i] | DP[s_i][p_i + 2];
			}
		} else {
			DP[s_i][p_i] = DP[s_i][p_i + 2];
		}			
	}
}

int check(char *s, char *p) {
	int **DP = NULL;
	int s_i, p_i;
	int answer;
	
	/* allocate */
	DP = malloc((strlen(s)+1) * sizeof(int*));
	for (s_i = 0; s_i <= strlen(s); s_i++) {
		DP[s_i] = malloc((strlen(p)+1) * sizeof(int));
	}
	
	/* run DP */
	for (p_i = strlen(p); p_i >= 0; p_i--) {
		for (s_i = strlen(s); s_i >= 0; s_i--) {
			run(s, s_i, p, p_i, DP);
		}
	}
	answer = DP[0][0];
	
	/* free */
	for (s_i = 0; s_i <= strlen(s); s_i++) {
		free(DP[s_i]);
		DP[s_i] = NULL;
	}
	free(DP);
	DP = NULL;
	
	return answer;
}

int main(){
    #if 1
    printf("%s\n", check("abc", "abc")==1 ? "true" :"false"); // true
    printf("%s\n", check("abc", "a..")==1 ? "true" :"false"); // true
    printf("%s\n", check("abc", "a.")==1 ? "true" :"false"); // false
    printf("%s\n", check("abc", "a.*")==1 ? "true" :"false"); // true
    printf("%s\n", check("abc", ".*")==1 ? "true" :"false"); // true
    printf("%s\n", check("abc", ".*c")==1 ? "true" :"false"); // true
    printf("%s\n", check("abc", ".*cd")==1 ? "true" :"false"); // false
    printf("%s\n", check("abc", "a.*c")==1 ? "true" :"false"); // true
    printf("%s\n", check("ac", "a.*c")==1 ? "true" :"false"); // true
    printf("%s\n", check("abc", "a*c")==1 ? "true" :"false"); // false
    printf("%s\n", check("a", "a*a")==1 ? "true" :"false"); // true
    printf("%s\n", check("aa", "a*")==1 ? "true" :"false"); // true
    printf("%s\n", check("abbbc", ".*b*c")==1 ? "true" :"false"); // true
    printf("%s\n", check("a", "ab*")==1 ? "true" :"false"); // true
    printf("%s\n", check("b", "b.*c")==1 ? "true" :"false"); // false
    printf("%s\n", check("aab", "b.*")==1 ? "true" :"false"); // false

    printf("%s\n", check("ab", ".*b*")==1 ? "true" :"false"); // true
    #endif
    printf("%s\n", check("abcbccbcba abbcbb", "c*a.*ab*.*ab*a*..b*")
            ==1 ? "true" :"false"); // true
    return 0;
}
