#include <iostream>
#include <stack>

using namespace std;

int main() {
    stack<int> input, output;
    input.push(7);
    input.push(4);
    input.push(1);
    input.push(2);
    input.push(6);    
    
    while (!input.empty()) {
        int number = input.top();
        input.pop();
        if (output.empty() || number <= output.top()) {
            output.push(number);
        } else {
            while ( !output.empty() && number > output.top()) {
                int number_2 = output.top();
                output.pop();
                input.push(number_2);
            }
            output.push(number);
        }
    }
    
    /* print output */
    while (!output.empty()) {
        cout << output.top() << " ";
        output.pop();
    }
    cout << endl;
    
    return 0;
}
