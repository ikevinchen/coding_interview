#include <stdio.h>
#include <stdlib.h>

/* !!! however this needs not to use segement tree ...
 * Try to solve it in O(n)
 */

typedef struct node {
    int max; /* non-negtive value, -1 : not init, -2 : empty node  */
    int left;
    int right;
} Node_t;

Node_t *tree_node = NULL; /* segement tree */

void print_tree(int num) {
    int i;
    for (i = 0; i < num; i++) {
        printf("%d [%d, %d] ", tree_node[i].max, tree_node[i].left, tree_node[i].right);
        if (i == 0 || i == 2 || i == 6 || i == 14) {
            printf("\n");
        }
    }
}

void build_tree_recursive(int node_index) {
    if (tree_node[node_index].max != -1) {
        return; /* has been inited */
    }
    
    int left_child_index  = 2 * node_index + 1;
    int right_child_index = 2 * node_index + 2;
    
    build_tree_recursive(left_child_index);
    build_tree_recursive(right_child_index);    
    
    if (tree_node[left_child_index].max == -2 &&
        tree_node[right_child_index].max == -2) {
        tree_node[node_index].max = -2;
    } else if (tree_node[left_child_index].max == -2) {
        tree_node[node_index] = tree_node[right_child_index];
    } else if (tree_node[right_child_index].max == -2) {
        tree_node[node_index] = tree_node[left_child_index];
    } else {
        tree_node[node_index].max = (tree_node[left_child_index].max >= tree_node[right_child_index].max)?
                                     tree_node[left_child_index].max : tree_node[right_child_index].max;
        tree_node[node_index].left = tree_node[left_child_index].left;
        tree_node[node_index].right = tree_node[right_child_index].right;            
    }
}

int Pow(int x,int n)
{
    int i; /* Variable used in loop counter */
    int number = 1;

    for (i = 0; i < n; ++i)
        number *= x;

    return(number);
}

void build_tree(int arr_num, int *arr) {
    /* 
            ex. input arr = 4, 6, 1, 2, 3, 8, 1, 4
                tree =             8
                             6          8
                         6      2    8      4
                       4   6  1  2  3  8   1  4
                       
                (left  child index = 2*index + 1)
                (right child index = 2*index + 2)
     */
    int base = 0;
    int node_num = Pow(2, base);
    int i;
    while (arr_num > Pow(2, base)) {
        base++;    
        node_num += Pow(2, base);
        //printf("node_num += %d\n", Pow(2, base));
    }
    
    //printf("node_num = %d, base = %d\n", node_num, base);    
    
    /* init segement tree */
    tree_node = malloc(sizeof(Node_t) * node_num);    
    for (i = 0; i < node_num; i++) {
        tree_node[i].max = -1;        
    }    
    
    
    /* init leaf in the tree */
    for (i = 0; i < Pow(2, base); i++) {
        int leaf_index = Pow(2, base) - 1 + i;
        if (i < arr_num) {
            tree_node[leaf_index].max  = arr[i];
            tree_node[leaf_index].left = i;
            tree_node[leaf_index].right = i;
        } else {
            tree_node[leaf_index].max = -2;
        }
    }
    
    /* build tree */
    build_tree_recursive(0);    
}

int find_max_recursive(int left, int right, int node_index) {
    //printf("find_max_recursive, %d %d %d\n", left, right, node_index);
    
    if (tree_node[node_index].left == left && 
        tree_node[node_index].right == right) {
        //printf("return %d\n", tree_node[node_index].max);
        return tree_node[node_index].max;
    }    
    
    int left_child_index  = 2 * node_index + 1;
    int right_child_index = 2 * node_index + 2;
    int left_max = -1;
    int right_max = -1;
    if (tree_node[left_child_index].max != -2 && left <= tree_node[left_child_index].right) {
        int range_left  = left;
        int range_right = (right > tree_node[left_child_index].right) ?
                           tree_node[left_child_index].right : right;
        left_max = find_max_recursive(range_left, range_right, left_child_index);
    }
    if (tree_node[right_child_index].max != -2 && right >= tree_node[right_child_index].left) {
        int range_left  = (left < tree_node[right_child_index].left) ?
                           tree_node[right_child_index].left : left;
        int range_right = right;
        right_max = find_max_recursive(range_left, range_right, right_child_index);
    }
    //printf("left_max = %d, right_max = %d\n", left_max, right_max);
    return (left_max >= right_max) ? left_max : right_max;
}

int find_max(int left, int right) {
    int answer = find_max_recursive(left, right, 0);
    //printf("find max [%d , %d] = %d\n", left, right, answer);
    return answer;
}

int trap(int* height, int heightSize) {
    /*
            ex.
            
                     O
                O  O O
                O OOOO
                OOOOOO
                
            for colum 1 (level 1): left max = 3, right_max = 4 ==> answer += 2
            for colum 2 (level 2): left max = 3, right_max = 4 ==> answer += 1
            for colum 3 (level 3): left max = 3, right_max = 4 ==> answer += 0
            ....
     */
    if (heightSize <= 2) {
        return 0;
    }
    int i;
    int answer = 0;
    build_tree(heightSize, height);    
    for (i = 1; i <= heightSize-2; i++) {
        //printf(" -- %d --\n", i);
        int left_max = find_max(0, i-1);
        int right_max = find_max(i+1, heightSize-1);
        int left_diff, right_diff;
        left_diff  = (left_max - height[i] >= 0)  ? (left_max - height[i]) : 0;
        right_diff = (right_max - height[i] >= 0) ? (right_max - height[i]) : 0;
        answer += (left_diff < right_diff) ? left_diff : right_diff;
        //printf(" answer = %d \n", answer);
    }
    return answer;
}

int main()
{
    #if 0 /* just for segement-tree testing */
    int array[7] = {4, 6, 1, 2, 3, 8, 1}; 
    build_tree(7, array);
    print_tree(15);
    find_max(0, 6);
    find_max(3, 3);
    find_max(2, 4);
    #endif
    
    int array[12] = {0,1,0,2,1,0,1,3,2,1,2,1};
    int answer = trap(array, 12);
    printf("answer = %d\n", answer);
    return 0;
}
