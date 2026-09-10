#include <stdio.h>
#include <string.h>
#include <ctype.h>

void findOrder(char key[], int order[], int n)
{
    int i, j, temp;

    for(i = 0; i < n; i++)
        order[i] = i;

    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(key[order[i]] > key[order[j]] ||
              (key[order[i]] == key[order[j]] && order[i] > order[j]))
            {
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
}

void encrypt(char text[], char key[], char result[])
{
    char matrix[100][20];
    int order[20];
    int rows, cols;
    int i, j, p = 0;

    cols = strlen(key);
    rows = (strlen(text) + cols - 1) / cols;

    for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            matrix[i][j] = 'X';

    for(i = 0; text[i] != '\0'; i++)
        matrix[i / cols][i % cols] = text[i];

    findOrder(key, order, cols);

    for(j = 0; j < cols; j++)
    {
        for(i = 0; i < rows; i++)
            result[p++] = matrix[i][order[j]];
    }

    result[p] = '\0';
}

void decrypt(char text[], char key[], char result[])
{
    char matrix[100][20];
    int order[20];
    int rows, cols;
    int i, j, p = 0;

    cols = strlen(key);
    rows = strlen(text) / cols;

    findOrder(key, order, cols);

    for(j = 0; j < cols; j++)
    {
        for(i = 0; i < rows; i++)
            matrix[i][order[j]] = text[p++];
    }

    p = 0;

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
            result[p++] = matrix[i][j];
    }

    result[p] = '\0';
}

int main()
{
    char text[200];
    char key1[20], key2[20];
    char first[300], encrypted[300];
    char second[300], decrypted[300];

    int i, j = 0;

    printf("Enter message: ");
    scanf(" %[^\n]", text);

    printf("Enter first key: ");
    scanf("%19s", key1);

    printf("Enter second key: ");
    scanf("%19s", key2);

    if(strlen(key1) == 0 || strlen(key2) == 0)
    {
        printf("Invalid key\n");
        return 0;
    }

    /* Convert message to uppercase and remove spaces */
    for(i = 0; text[i] != '\0'; i++)
    {
        if(isalpha(text[i]))
        {
            text[j] = toupper(text[i]);
            j++;
        }
    }

    text[j] = '\0';

    /* Convert keys to uppercase */
    for(i = 0; key1[i] != '\0'; i++)
        key1[i] = toupper(key1[i]);

    for(i = 0; key2[i] != '\0'; i++)
        key2[i] = toupper(key2[i]);

    /* First transposition */
    encrypt(text, key1, first);

    /* Second transposition */
    encrypt(first, key2, encrypted);

    printf("Encrypted: %s\n", encrypted);

    /* Decryption in reverse order */
    decrypt(encrypted, key2, second);
    decrypt(second, key1, decrypted);

    printf("Decrypted: %s\n", decrypted);

    return 0;
}