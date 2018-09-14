
#include <stdio.h>

#if 0
see the position between "const" and "*"

const* : pointer to the const
*const : const pointer

    ex.
    (const int) * ==> pointer       to "const int"
    (int const) *
    int (* const) ==> const pointer to "int"

const** ==> (const *)* : pointer       to pointer to the const
*const* ==> (*const)*  : pointer       to const pointer
**const ==> *(*const)  : const pointer to the pointer

從右邊解讀回來
const*const*const
   step1. (const*const)(*const) ==> const pointer to "const*const"
   step2. const(*const) ==> const pointer to const
==> const pointer to const pointer to const


const*const*
    step1. (const*const)*  ==> pointer to "const*const"
    step2. const(*const) ==> const pointer to const
==> pointer to const pointer to const

    ex.
    ((const int) *)* ==> pointer       to pointer to "const int"
    ((int const) *)*
    (int (* const))* ==> pointer       to const pointer to "int"
    int *(* const)   ==> const pointer to pointer to "int"

int var;
&var          ==> pointer to "int"  

const int c_var; 
&c_var        ==> pointer to "cosnt int"
#endif

int global = 10;
void func_a(const int* ptr) {  /* pointer to "const int" */
    //*ptr = 10;       //compile error
       ptr = &global;  //compile okay
}

void func_b(int *const ptr) { /* const pointer to "int" */
      *ptr = 10;       //compile okay
    // ptr = &global;  //compile error
}

void func_c(int* ptr)       { /*       pointer to "int" */
      *ptr = 10;       //compile okay
       ptr = &global;  //compile okay
}

void func_d(const int **pptr) { /* pointer to pointer to "const int" */
    //**pptr = 10;         //compile error
       *pptr = &global;    //compile okay
        pptr = NULL;       //compile okay
}

void func_e(int * const* pptr) { /* pointer to const pointer to int */
      **pptr = 10;         //compile okay
    // *pptr = &global;    //compile error
        pptr = NULL;       //compile okay
}

void func_f(int **const pptr) { /* const pointer to pointer to int */
      **pptr = 10;         //compile okay
       *pptr = &global;    //compile okay
    //  pptr = NULL;       //compile error
}

int main()
{
    int local   = 30;
    const int c_local = 40;

    /* pass the pointer to int */
    func_a(&local);
    func_b(&local);
    func_c(&local);

    /* pass the pointer to const int */
    func_a(&c_local);
    func_b(&c_local); /* compile warning */
    func_c(&c_local); /* compile warning */

    int *ptr_1        = &local;
    int *ptr_1_c      = &c_local;  /* compile warning */
    const int *ptr_2  = &local; 
    const int *ptr_2_c= &c_local; 
    int *const ptr_3  = &local; 
    int *const ptr_3_c= &c_local;  /* compile warning */

    /* pass the pointer to "pointer to int" */
    func_d(&ptr_1); /* compile warning,
                            func_d : pointer of XXX
                            pass.  : pointer of YYY
                            (XXX = pointer to const int,
                             YYY = pointer to int
                            not the same type)
                       ref. http://c-faq.com/ansi/constmismatch.html
                    */
    func_e(&ptr_1); /* compeile okay,
                            func_e : pointer of const XXX
                            pass.  : pointer of XXX
                            (XXX = pointer to int)
                        so compatible, just like how line 84 works
                     */
    func_f(&ptr_1); /* compeile okay
                            func_f : const pointer of XXX
                            pass.  :       pointer of XXX
                            (XXX = pointer to int)
                        ==> okay
                     */

    /* pass the pointer to "pointer to const int" */
    func_d(&ptr_2);
    func_e(&ptr_2);  /* compile warning */
    func_f(&ptr_2);  /* compile warning */

    /* pass the pointer to "const pointer to int" */
    func_d(&ptr_3); /* compile warning */
    func_e(&ptr_3);
    func_f(&ptr_3); /* compile warning
                            func_f : const pointer of XXX
                            pass.  :       pointer of const XXX
                            (XXX = pointer to int)
                            ==> warning
                     */

    return 0;
}