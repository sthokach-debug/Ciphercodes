#include <stdio.h>
#include <string.h>
#include <ctype.h>

void getOrder(char key[], int order[], int n)
{
    int i, j, temp;

    for(i = 0; i < n; i++)
        order[i] = i;

    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(key[order[i]] > key[order[j]])
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
    char matrix[100][20] = {0};
    int order[20];
    int len = strlen(text);
    int cols = strlen(key);
    int rows = (len + cols - 1) / cols;
    int i, j, k = 0;

    for(i = 0; i < len; i++)
        matrix[i / cols][i % cols] = text[i];

    getOrder(key, order, cols);

    for(j = 0; j < cols; j++)
    {
        for(i = 0; i < rows; i++)
        {
            if(matrix[i][order[j]] != '\0')
            {
                result[k] = matrix[i][order[j]];
                k++;
            }
        }
    }

    result[k] = '\0';
}

void decrypt(char text[], char key[], char result[])
{
    char matrix[100][20] = {0};
    int order[20];
    int len = strlen(text);
    int cols = strlen(key);
    int rows = (len + cols - 1) / cols;
    int base = len / cols;
    int extra = len % cols;
    int i, j, k = 0;
    int columnLength;

    getOrder(key, order, cols);

    for(j = 0; j < cols; j++)
    {
        columnLength = base;

        if(order[j] < extra)
            columnLength++;

        for(i = 0; i < columnLength; i++)
        {
            matrix[i][order[j]] = text[k];
            k++;
        }
    }

    k = 0;

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            if(matrix[i][j] != '\0')
            {
                result[k] = matrix[i][j];
                k++;
            }
        }
    }

    result[k] = '\0';
}

int main()
{
    char text[100];
    char key1[20], key2[20];
    char first[100], encrypted[100];
    char second[100], decrypted[100];

    int i, j = 0;

    printf("Enter message: ");
    scanf(" %99[^\n]", text);

    printf("Enter first key: ");
    scanf("%19s", key1);

    printf("Enter second key: ");
    scanf("%19s", key2);

    for(i = 0; key1[i] != '\0'; i++)
    {
        if(!isalpha(key1[i]))
        {
            printf("Invalid key\n");
            return 0;
        }

        key1[i] = toupper(key1[i]);
    }

    for(i = 0; key2[i] != '\0'; i++)
    {
        if(!isalpha(key2[i]))
        {
            printf("Invalid key\n");
            return 0;
        }

        key2[i] = toupper(key2[i]);
    }

    for(i = 0; text[i] != '\0'; i++)
    {
        if(isalpha(text[i]))
        {
            text[j] = toupper(text[i]);
            j++;
        }
    }

    text[j] = '\0';

    if(strlen(key1) > 20 || strlen(key2) > 20)
    {
        printf("Key too long\n");
        return 0;
    }

    encrypt(text, key1, first);
    encrypt(first, key2, encrypted);

    printf("\nEncrypted: %s\n", encrypted);

    decrypt(encrypted, key2, second);
    decrypt(second, key1, decrypted);

    printf("Decrypted: %s\n", decrypted);

    return 0;
}
