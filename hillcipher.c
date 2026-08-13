#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char str[100], temp[100];
    char encrypted[100], decrypted[100];

    int key[2][2] = {{5, 8}, {17, 3}};
    int inv[2][2] = {{9, 4}, {13, 15}};

    int i, n = 0, k = 0;
    int a, b;

    printf("Enter the string to be encrypted:\n");
    fgets(str, sizeof(str), stdin);

    str[strcspn(str, "\n")] = '\0';

    /* Check the input */
    for(i = 0; str[i] != '\0'; i++)
    {
        if(str[i] != ' ' && !isalpha(str[i]))
        {
            printf("Invalid character in the string. ");
            printf("Please enter only alphabets and spaces.\n");
            return 0;
        }
    }

    /* Remove spaces and convert to uppercase */
    for(i = 0; str[i] != '\0'; i++)
    {
        if(str[i] != ' ')
        {
            temp[n] = toupper(str[i]);
            n++;
        }
    }

    /* Add X if number of letters is odd */
    if(n % 2 != 0)
    {
        temp[n] = 'X';
        n++;
    }

    temp[n] = '\0';

    /* Encryption */
    for(i = 0; i < n; i += 2)
    {
        a = temp[i] - 'A';
        b = temp[i + 1] - 'A';

        encrypted[k++] =
        ((key[0][0] * a + key[0][1] * b) % 26) + 'A';

        encrypted[k++] =
        ((key[1][0] * a + key[1][1] * b) % 26) + 'A';
    }

    encrypted[k] = '\0';

    printf("Encrypted string: %s\n", encrypted);

    /* Decryption */
    k = 0;

    for(i = 0; i < n; i += 2)
    {
        a = encrypted[i] - 'A';
        b = encrypted[i + 1] - 'A';

        decrypted[k++] =
        (((inv[0][0] * a + inv[0][1] * b) % 26) + 26) % 26 + 'A';

        decrypted[k++] =
        (((inv[1][0] * a + inv[1][1] * b) % 26) + 26) % 26 + 'A';
    }

    decrypted[k] = '\0';

    printf("Decrypted string: %s\n", decrypted);

    return 0;
}