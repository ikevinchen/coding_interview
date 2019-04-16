#include <stdio.h>
#include <stdlib.h>

int* spiralOrder() {
    int matrix[2][3] = {
         { 1, 2, 3},{ 4,5 ,6}
        };
    int matrixRowSize = 2;
    int matrixColSizes = 3;
    int *answer = malloc(sizeof(int) * matrixRowSize * matrixColSizes);
    int answer_ptr = 0;
    int i;

    int row_min = 0, row_max = matrixRowSize - 1;
    int col_min = 0, col_max = matrixColSizes - 1;
    int row_cur = 0, col_cur = 0;

    answer[answer_ptr++] = matrix[0][0];
    int first_move = 1;

    while (1) {

        /* right */
        if (col_cur + 1 <= col_max) {
            while (1) {
                col_cur = col_cur + 1;
                printf("right : %d\n", matrix[row_cur][col_cur]);
                answer[answer_ptr++] = matrix[row_cur][col_cur];
                if (col_cur == col_max) break;
            }
            row_min++;
        } else {
            if (first_move != 1) break;
        }
        
        /* down */
        if (row_cur + 1 <= row_max) {
            while (1) {
                row_cur = row_cur + 1;
                printf("down : %d\n", matrix[row_cur][col_cur]);
                answer[answer_ptr++] = matrix[row_cur][col_cur];
                if (row_cur == row_max) break;
            }
            col_max--;
            first_move = 0;
        } else {
            break;
        }
        

        /* left */
        if (col_cur - 1 >= col_min) {
            while (1) {
                col_cur = col_cur - 1;
                printf("left : %d\n", matrix[row_cur][col_cur]);
                answer[answer_ptr++] = matrix[row_cur][col_cur];
                if (col_cur == col_min) break;
            }
            row_max--;
            first_move = 0;
        } else {
            break;
        }

        /* up */
        if (row_cur - 1 >= row_min) {
            while (1) {
                row_cur = row_cur - 1;
                printf("up : %d\n", matrix[row_cur][col_cur]);
                answer[answer_ptr++] = matrix[row_cur][col_cur];
                if (row_cur == row_min) break;
            }
            col_min++;
            first_move = 0;
        } else {
            break;
        }

    }
    return answer;
}

int main() 
{
    int i;
    int *answer = spiralOrder();
    for (i = 0; i < 9; i++) {
        printf("%d ", answer[i]);
    }
    printf("\n");
    return 0;
}