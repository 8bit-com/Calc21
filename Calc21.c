#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int strpars(char* str);
char* str_pars_el(char* str, int *i);
int check_scb(char *str);
int calc(char* str);

int main() {
    char *str = "(7+4+(8+(78-9-5)+2-(5+1+(3+7-((1+1)-(2+3))))))+9-(12-8)";
    printf("%s\n", str);
    printf("=\n%d", strpars(str));
    return 0;
}

int check_scb(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '(') return 1;
        else i++;
    }
    return 0;
}

int strpars(char* str) {
    int i = 0, j = 0;
    char* arr = malloc(10 * sizeof(char));
    char* arr2 = malloc(10 * sizeof(char));
    while (str[i] != '\0') {
        if (str[i] == '(') {
            i++;
            arr2 = str_pars_el(str, &i);
            if (check_scb(arr2)) {
                itoa(strpars(arr2), arr2, 10);
                for (int g = 0; arr2[g] != '\0'; g++)
                    arr[j++] = arr2[g];
                arr[j] = '\0';
            } else {
                itoa(calc(arr2), arr2, 10);
                for (int g = 0; arr2[g] != '\0'; g++)
                    arr[j++] = arr2[g];
                arr[j] = '\0';
            }
            i++;
        } else {
            arr[j++] = str[i++];
            arr[j] = '\0';
        }
    }
    printf("%s ", arr);
    return calc(arr);
}

int calc(char* str) {
    int k = 0, j = 0, a = 0, i = 0;
    char arr[100][100];
    while (str[i] != '\0') {
        if (str[i] == '+' || str[i] == '-') {
            if (str[i-1] == '-' && str[i] == '-') {
                k--;
                arr[j][k++] = '+';
                i++;
            } else {
                k = 0;
                arr[++j][k++] = str[i++];
            } 
        } else {
            arr[j][k++] = str[i++];
            arr[j][k] = '\0';
        }
    }
    for (int i = 0; i < j + 1; i++)
        a += atoi(arr[i]);
    return a;
}

char* str_pars_el(char* str, int *i) {
    int j = 0;
    int count_scob = 1;
    char* arr = malloc(100 * sizeof(char));
    int exit = 1;
    while (exit) {
        if (str[*i] == '(')
            count_scob++;
        if (str[*i] == ')')
            count_scob--;
        if (str[*i] == ')' && count_scob == 0)
            break;
        arr[j] = str[*i];
        j++;
        (*i)++;
    }
    arr[j] = '\0';
    return arr;
}
