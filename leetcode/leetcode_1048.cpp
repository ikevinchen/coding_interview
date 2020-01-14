#include <vector>
#include <iostream>

#define MAXLEN    (16)

using namespace std;

typedef struct data_s {
    string *str;
    int len_chain; /* the longest chain begin from this string */
} data_t;

/* check whether str_a is predecessor of str_b */
bool isPredecessor (string *str_a, string *str_b) {
    bool new_char_happen = false;
    int a = 0, b = 0;
    while ((*str_a)[a] != '\0' && (*str_b)[b] != '\0') {
        if ((*str_a)[a] != (*str_b)[b]) {
            if (new_char_happen == true) {
                return false;
            } else {
                new_char_happen = true;
                a++;
            }
        } else {
            a++;
            b++;
        }
    }
    if (new_char_happen == false &&
        (*str_a)[a] != '\0' && (*str_a)[a+1] == '\0' &&
        (*str_b)[b] == '\0') {
        return true;
    } else if (new_char_happen == true && 
               (*str_a)[a] == '\0' && (*str_b)[b] == '\0') {
        return true;
    } else {
        return false;
    }
}

int longestStrChain(vector<string>& words)
{
    if (words.size() == 0) {
        return 0;
    }
    
    int best_answer = 1;
    vector<data_t> database[MAXLEN+1]; /* use database[1] ~ database[16] */
    for (int i = 0; i < words.size(); i++) {
        data_t new_data;
        int len = words[i].length();
        new_data.str = &(words[i]);
        new_data.len_chain = 1;        
        database[len].push_back(new_data);
    }
    for (int len = MAXLEN - 1; len >= 1 ; len--) {
        for (int i = 0; i < database[len].size(); i++) {            
            for (int j = 0; j < database[len+1].size(); j++) {
                if (isPredecessor(database[len+1][j].str,
                                  database[len][i].str) == true) {
                    if (database[len+1][j].len_chain + 1 > database[len][i].len_chain) {
                        database[len][i].len_chain = database[len+1][j].len_chain + 1;
                        if (database[len][i].len_chain > best_answer) {
                            best_answer = database[len][i].len_chain;
                        }
                    }
                }
            }
        }
    }        
    return best_answer;
}

int main()
{
    vector<string> words;
    cout << longestStrChain(words) << endl;
    words.push_back("ab");
    cout << longestStrChain(words) << endl;
    words.push_back("a");
    cout << longestStrChain(words) << endl;
    words.push_back("acb");
    cout << longestStrChain(words) << endl;
    words.push_back("dacb");
    cout << longestStrChain(words) << endl;
    //cout << isPredecessor("abc", "ac") << endl;
    //cout << isPredecessor("abc", "abc") << endl;
    //cout << isPredecessor("bac", "ac") << endl;
    //cout << isPredecessor("acb", "ac") << endl;
    //cout << isPredecessor("abbc", "abc") << endl;
    return 0;
}
