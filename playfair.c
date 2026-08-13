#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void createMatrix(char key[])
{
    int used[26] = {0};
    int i, r = 0, c = 0;
    char ch;

    used['J' - 'A'] = 1;

    /* Put key letters in matrix */
    for(i = 0; key[i] != '\0'; i++)
    {
        ch = toupper(key[i]);

        if(ch == ' ')
            continue;

        if(ch == 'J')
            ch = 'I';

        if(!used[ch - 'A'])
        {
            matrix[r][c++] = ch;
            used[ch - 'A'] = 1;

            if(c == 5)
            {
                c = 0;
                r++;
            }
        }
    }

    /* Fill remaining letters */
    for(ch = 'A'; ch <= 'Z'; ch++)
    {
        if(ch == 'J')
            continue;

        if(!used[ch - 'A'])
        {
            matrix[r][c++] = ch;
            used[ch - 'A'] = 1;

            if(c == 5)
            {
                c = 0;
                r++;
            }
        }
    }
}

void position(char ch, int *r, int *c)
{
    int i, j;

    if(ch == 'J')
        ch = 'I';

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            if(matrix[i][j] == ch)
            {
                *r = i;
                *c = j;
                return;
            }
        }
    }
}

int prepare(char input[], char output[])
{
    char temp[100];
    int i, n = 0, k = 0;

    /* Remove spaces and convert to uppercase */
    for(i = 0; input[i] != '\0'; i++)
    {
        if(input[i] != ' ')
        {
            temp[n] = toupper(input[i]);

            if(temp[n] == 'J')
                temp[n] = 'I';

            n++;
        }
    }

    i = 0;

    /* Make pairs */
    while(i < n)
    {
        output[k++] = temp[i];

        if(i + 1 < n && temp[i] == temp[i + 1])
        {
            output[k++] = 'X';
            i++;
        }
        else if(i + 1 < n)
        {
            output[k++] = temp[i + 1];
            i += 2;
        }
        else
        {
            output[k++] = 'X';
            i++;
        }
    }

    output[k] = '\0';

    return k;
}

void encrypt(char text[], char result[], int n)
{
    int i;
    int r1, c1, r2, c2;

    for(i = 0; i < n; i += 2)
    {
        position(text[i], &r1, &c1);
        position(text[i + 1], &r2, &c2);

        if(r1 == r2)
        {
            result[i] = matrix[r1][(c1 + 1) % 5];
            result[i + 1] = matrix[r2][(c2 + 1) % 5];
        }
        else if(c1 == c2)
        {
            result[i] = matrix[(r1 + 1) % 5][c1];
            result[i + 1] = matrix[(r2 + 1) % 5][c2];
        }
        else
        {
            result[i] = matrix[r1][c2];
            result[i + 1] = matrix[r2][c1];
        }
    }

    result[n] = '\0';
}

void decrypt(char text[], char result[], int n)
{
    int i;
    int r1, c1, r2, c2;

    for(i = 0; i < n; i += 2)
    {
        position(text[i], &r1, &c1);
        position(text[i + 1], &r2, &c2);

        if(r1 == r2)
        {
            result[i] = matrix[r1][(c1 + 4) % 5];
            result[i + 1] = matrix[r2][(c2 + 4) % 5];
        }
        else if(c1 == c2)
        {
            result[i] = matrix[(r1 + 4) % 5][c1];
            result[i + 1] = matrix[(r2 + 4) % 5][c2];
        }
        else
        {
            result[i] = matrix[r1][c2];
            result[i + 1] = matrix[r2][c1];
        }
    }

    result[n] = '\0';
}

int main()
{
    char key[50], input[100];
    char text[100], cipher[100], plain[100];

    int i, j, n;

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    printf("Enter plaintext: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    /* Check input */
    for(i = 0; input[i] != '\0'; i++)
    {
        if(input[i] != ' ' && !isalpha(input[i]))
        {
            printf("Invalid input. Use alphabets and spaces only.\n");
            return 0;
        }
    }

    createMatrix(key);

    printf("\nPlayfair Matrix:\n");

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            printf("%c ", matrix[i][j]);
        }

        printf("\n");
    }

    n = prepare(input, text);

    encrypt(text, cipher, n);

    decrypt(cipher, plain, n);

    printf("\nPrepared text: %s\n", text);
    printf("Encrypted text: %s\n", cipher);
    printf("Decrypted text: %s\n", plain);

    return 0;
}