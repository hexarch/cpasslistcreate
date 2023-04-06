#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void getPermutationsHelper(char **arr, int len, bool *used, char *sb, int sb_len, FILE *file);
int count_words(const char *str);

int main() {
    char userInput[1000];
    printf("Lutfen verileri aralarinda bir bosluk birakarak giriniz: ");
    fgets(userInput, sizeof(userInput), stdin);

    int data_len = count_words(userInput);
    char **data = (char **)malloc(data_len * sizeof(char *));
    char *token = strtok(userInput, " \n");
    int index = 0;

    while (token != NULL) {
        data[index++] = token;
        token = strtok(NULL, " \n");
    }

    FILE *file = fopen("son.txt", "w");
    if (file == NULL) {
        printf("Hata: dosya acilamadi\n");
        return 1;
    }

    for (int length = 1; length <= data_len; length++) {
        bool used[data_len];
        memset(used, 0, sizeof(used));
        char sb[1000] = "";
        getPermutationsHelper(data, length, used, sb, 0, file);
    }

    fclose(file);
   
    free(data);
    return 0;
}

void getPermutationsHelper(char **arr, int len, bool *used, char *sb, int sb_len, FILE *file) {
    if (sb_len == len) {
        printf("%s\n", sb);
        if (len >= 8 && len <= 16)
            fprintf(file, "%s\n", sb);
        return;
    }

    for (int i = 0; i < len; i++) {
        if (!used[i]) {
            used[i] = true;
            strcat(sb, arr[i]);
            sb_len += strlen(arr[i]);
            getPermutationsHelper(arr, len, used, sb, sb_len, file);
            used[i] = false;
            sb_len -= strlen(arr[i]);
            sb[sb_len] = '\0';
        }
    }
}

int count_words(const char *str) {
    int count = 0;
    bool in_word = false;

    while (*str) {
        if (*str == ' ' || *str == '\n' || *str == '\t') {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            count++;
        }
        str++;
    }

    return count;
}