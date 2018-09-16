#include <stdio.h>

int main()
{
    /* https://www.geeksforgeeks.org/pointer-array-array-pointer/
     *    subscript have higher precedence than indirection
     *      type *var[]   ==> array of pointer
     *      type (*var)[] ==> pointer to array
     */

    int *p1;               /*          "pointer to int" */
    int *p2[5] = {NULL};   /* array of "potiner to int" */
    int (*p3)[5];          /* pointer to array of int   */

    int arr[5] = {1, 2, 3, 4, 5};
    p1 = arr;
    p2[0] = arr;
    p3 = &arr;

    printf("%lu %lu %lu\n", sizeof(p1), sizeof(p2), sizeof(p3));
    printf("%lu %lu %lu\n", sizeof(*p1), sizeof(*p2), sizeof(*p3));
    printf("%d %d %d\n", *p1, *p2[0], (*p3)[0]);
    printf("%p %p %p %p\n", p1, p2[0], p2[1], p3);
    p1++; p2[0]++; p3++;
    printf("%p %p %p %p\n", p1, p2[0], p2[1], p3);

    return 0;
}



/*
   output :

    8 40 8
    4 8 20
    1 1 1
    0x7ffee0a14aa0 0x7ffee0a14aa0 0x0 0x7ffee0a14aa0
    0x7ffee0a14aa4 0x7ffee0a14aa4 0x0 0x7ffee0a14ab4

 */
