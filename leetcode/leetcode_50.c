#include <stdio.h>

double myPow(double x, int n) {
    double answer = 1;
    double mul_value = 1;
    unsigned int iteration, i;
    
    if (x == 0) {
        return 0;
    } else if (x == 1) {
        return 1;
    } else if (x == -1) {
        if (n & 1 == 1) {
            return -1;
        } else {
            return 1;
        }
    }    

    if (n == 0) {
        return 1;
    } else if (n > 0) {
        mul_value = x;
        iteration = n;
    } else {
        mul_value = 1 / x;
        iteration = -n;
        /*    
            ex. 3-bit value
        
                000 (0)
                001 (1)     111 (-1)
                010 (2)     110 (-2)
                011 (3)     101 (-3)
                            100 (-4)
                            
                -(111) = 001
                -(110) = 010
                -(101) = 011
                -(100) = 100 (still the same!)
                
                however we could use "unsigned int" view to treat 100 as 4
         */
    }
    
    
    for (i = 0; i < iteration; i++) {
        answer = answer * mul_value;
        if (answer == 0) {
            break;
        }
    }
    return answer;
}

int main()
{
    printf("%f\n", myPow(2.00000, -2147483648));
    return 0;
}
