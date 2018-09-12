#include <stdio.h>


int global = 10;

void func_a(const int **pptr) {
    *pptr = &global;
}

void func_b(int *const *pptr) {
    **pptr = 20;
}


int main()
{
    int local = 30;
    int *ptr_1 = &local;
    const int *ptr_2 = &local;
    int* const ptr_3 = &local;
    func_a(&ptr_1); /* compile warning */
    func_a(&ptr_2); /* compile okay */
    func_a(&ptr_3); /* compile warning */

    func_b(&ptr_1); /* compile okay? */
    func_b(&ptr_2); /* compile warning */
    func_b(&ptr_3); /* compile okay */

    return 0;
}
