#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char text[100], key[50];
    char cipher[100], plain[100];

    int i, j = 0;
    int k, keyLen;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    keyLen = strlen(key);

    if(keyLen == 0)
    {
        printf("Invalid key.\n");
        return 0;
    }

    /* Check plaintext */
    for(i = 0; text[i] != '\0'; i++)
    {
        if(text[i] != ' ' && !isalpha(text[i]))
        {
            printf("Invalid input. Use alphabets and spaces only.\n");
            return 0;
        }
    }

    /* Check key */
    for(i = 0; key[i] != '\0'; i++)
    {
        if(!isalpha(key[i]))
        {
            printf("Invalid key. Use alphabets only.\n");
            return 0;
        }
    }

    /* Encryption */
    j = 0;

    for(i = 0; text[i] != '\0'; i++)
    {
        if(isalpha(text[i]))
        {
            k = (toupper(text[i]) - 'A' +
                 toupper(key[j % keyLen]) - 'A') % 26;

            cipher[i] = k + 'A';

            j++;
        }
        else
        {
            cipher[i] = text[i];
        }
    }

    cipher[i] = '\0';

    printf("Encrypted text: %s\n", cipher);

    /* Decryption */
    j = 0;

    for(i = 0; cipher[i] != '\0'; i++)
    {
        if(isalpha(cipher[i]))
        {
            k = (cipher[i] - 'A' -
                 (toupper(key[j % keyLen]) - 'A') + 26) % 26;

            plain[i] = k + 'A';

            j++;
        }
        else
        {
            plain[i] = cipher[i];
        }
    }

    plain[i] = '\0';

    printf("Decrypted text: %s\n", plain);

    return 0;
}