#include <stdio.h>

int arr_global[3] = {7, 8, 9};
void func(const int **arr_pptr) {
    *arr_pptr = arr_global;
}

int global_c = 5;
int global_d = 6;
/* cannot modify "**pptr" ==> "int" */
void func_a(const int **pptr) {
    *pptr = &global_c;
    //**pptr = 10; /* compile error */
}

/* cannot modify "*pptr" ==> "int *" */
void func_b(int *const *pptr) {
    //*pptr = &global_c; /* compile error */
    **pptr = 10;
}

//void func_3(int **const pptr) {
//    /* cannot modify "pptr" */
//    *pptr = &global_c;
//}

int main()
{
    /*
        1. const int a  = int const a
        2. const int *a = int const *a
           int* const a
     */

    int local = 10;
    int *ptr_1 = &local;
    const int *ptr_2 = &local;
    int* const ptr_3 = &local;
    func_a(&ptr_1); /* compile warning :
                       func_1 do not want to modify "int"
                       however *ptr_1 could be modified here
                     */
    func_a(&ptr_2); /* compile okay */
    func_a(&ptr_3); /* compile warning */


    func_b(&ptr_1); /* compile okay? */
    func_b(&ptr_2); /* compile warning */
    func_b(&ptr_3); /* compile okay */
    //*ptr = 10; /* compile error */

    int arr_a[3] = {1, 2, 3};
    int arr_b[3] = {4, 5, 6};
    const int *arr_ptr = NULL;
    arr_ptr = arr_a;
    arr_ptr = arr_b;
    func(&arr_ptr);


    //arr_ptr[0] = 12; /* compile error */

    int **arr_pptr = NULL;
    *arr_pptr = arr_a;

    #if 0
    //int **arr_pptr = &arr_a; /* initialization from incompatible pointer type */
    int (*arr_pptr)[3] = &arr_a;
    #endif

    return 0;
}
