#include <stdio.h>
#include <string.h>
#define MAX_LEN 1000

/*
     s = babaabac
	 
	   P[i] = the array of all possible Palindrome end at index i
	   
		   P[0] = b
		   P[1] = a
		   P[2] = b, bab
		   P[3] = a, aba
		   P[4] = a, aa
		   P[5] = b, baab
		   
	   P[i] = 
		{	one character          : s[i]
		    two characters         : if s[i] == s[i-1]
			over two characters    : iterate each string p in P[i-1], if the "previous character of p" = s[i]
		}
 */
 
char answer[MAX_LEN+1];

char *longestPalindrome(char *s){
	int P_arr[2][MAX_LEN]; /* record the beginning index of MAX_LEN */
	int P_num[2]={0, 0};
	/* index 0,2,4,6,8 uses array[0]
	         1,3,5,7,9 uses array[1]
	 */
	int best_answer = 0;
	int best_answer_start = 0;
	int best_answer_end = 0;
	
	int i, j;
	for (i = 0; i < strlen(s); i++) {
		int cur_array_id  = i%2;
		int prev_array_id = (i+1)%2;
		int cur_best_answer = -1;
		
		P_num[cur_array_id] = 0;
		
		/* rule. 3 */
		for (j = 0; j < P_num[prev_array_id]; j++) {
			int s_begin_index = P_arr[prev_array_id][j];			
			if (s_begin_index !=0 && s[s_begin_index - 1] == s[i]) {
				P_arr[cur_array_id][P_num[cur_array_id]] = s_begin_index - 1;
				P_num[cur_array_id]++;
				if (cur_best_answer == -1) {
					cur_best_answer = (i) - (s_begin_index - 1) + 1;
				}
			}
		}
		
		/* rule. 2 */
		if (i != 0 && s[i] == s[i-1]) {
			P_arr[cur_array_id][P_num[cur_array_id]] = i - 1;
			P_num[cur_array_id]++;
			if (cur_best_answer == -1) {
				cur_best_answer = 2;
			}
		}
		
		/* rule. 1 */
		P_arr[cur_array_id][P_num[cur_array_id]] = i;
		P_num[cur_array_id]++;	
		if (cur_best_answer == -1) {
			cur_best_answer = 1;
		}	
		
		/* final update */
		if (cur_best_answer > best_answer) {
			best_answer = cur_best_answer;
			best_answer_end = i;
			best_answer_start = i - cur_best_answer + 1;
		}
	}
	

	//printf("%d %d %d %s\n", best_answer, best_answer_start, best_answer_end, s+best_answer_start);
	strncpy(answer, s+best_answer_start, best_answer);
	answer[best_answer] = '\0';
	return answer;
}

int main()
{
	printf("%s\n", longestPalindrome("a"));
	printf("%s\n", longestPalindrome("aaaaaa"));
	printf("%s\n", longestPalindrome("babaabaa"));
	printf("%s\n", longestPalindrome("cabbabccba"));
}
