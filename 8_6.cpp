#include <stack>
#include <iostream>
using namespace std;

stack<int> s_1, s_2, s_3;

void print_stack(stack<int> *s) {
    stack<int> s_tmp;

    while (!s->empty())
    {
        s_tmp.push(s->top());
        s->pop();
    }
    while (!s_tmp.empty())
    {
        cout << s_tmp.top() << " ";
        s->push(s_tmp.top());
        s_tmp.pop();
    }
    cout << endl;
}

void print_stack_all() {
    cout << "| "; print_stack(&s_1);
    cout << "| "; print_stack(&s_2);
    cout << "| "; print_stack(&s_3);
    cout << endl;
}

void move(int num, stack<int>* from, stack<int>* to, stack<int>* another) {
    if (num == 1) {
        to->push(from->top());
        from->pop();
        print_stack_all();
    } else {
        move(num - 1, from, another, to);
        move(1, from, to, another);
        move(num - 1, another, to, from);
    }
}

int main()
{
    s_1.push(4); s_1.push(3); s_1.push(2); s_1.push(1);
    print_stack_all();
    move(4, &s_1, &s_3, &s_2);
    return 0;
}
