//
// Created by lisen on 24-8-6.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iso646.h>

#define MAX_COLS 20       // define the columns of boundaries
#define MAX_INPUT 1000    // max length of input

int get_columns_number(int columns[], int max);

void get_shrinked_output(char *output, const char *input, int col_numbers, const int columns[]);

char * s_gets(char * str, int n);

int main() {
    int col_numbers = 0;
    int columns[MAX_COLS];
    char input[MAX_INPUT];
    char output[MAX_INPUT];

    col_numbers = get_columns_number(columns, MAX_COLS);

    while(s_gets(input, MAX_INPUT) != NULL && input[0] != '\0') {
        printf("Original input is %s \n", input);
        get_shrinked_output(output, input, col_numbers, columns);
        printf("Shrinked output is %s \n", output);
    }

}


int get_columns_number(int columns[], int max) {
    int nums = 0;   // returned value, used as index and tell main that how many items in this columns array

    while(nums < max and scanf("%d", &columns[nums]) == 1 and columns[nums] >= 0) {
        nums ++;
    }

    // make sure integers are entered by ascending order
    // newly added compare to the code in book
    for(int i = 0; i < nums - 1; i++) {
        if((columns[i] - columns[i + 1]) > 0) {
            printf("please enter boundaries in ascending order\n");
            exit(EXIT_FAILURE);
        }
    }

    // nums mod 2 equels to 0 otherwise last pair lost its right one
    if(nums % 2 != 0) {
        printf("last pair lost its right one\n");
        exit(EXIT_FAILURE);
    }

    while(getchar() != '\n');

    return nums;
}

void get_shrinked_output(char *output, const char *input, int col_numbers, const int columns[]) {
    int output_col = 0;
    for (int i = 0; i < col_numbers; i += 2) {
        if(columns[i] > strlen(input))
            break;
        int sub_len = columns[i + 1] - columns[i] + 1;

        strncpy(output + output_col, input + columns[i], sub_len);

        output_col += sub_len;
    }
}

// compared to book's code ,discord gets function, so in get_shrinked_output, ignore the if clause to check if the length
// is valid
char * s_gets(char * str, int n) {
    char * ret_val = fgets(str, n, stdin);
    char * find;

    if(ret_val) {
        find = strchr(str, '\n');
        if(find)
            *find = '\0';
        else {
            while(getchar() != '\n')
                continue;
        }
    }

    return ret_val;
}