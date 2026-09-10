#include <stdio.h>
#include <ctype.h>

int main()
{
    char text[100], key[27];
    char encrypted[100], decrypted[100];
    int i, j;

    printf("Enter message: ");
    scanf(" %[^\n]", text);

    printf("Enter 26 letter key: ");
    scanf("%s", key);

    for(i = 0; text[i] != '\0'; i++)
    {
        if(isalpha(text[i]))
        {
            char ch = toupper(text[i]);
            encrypted[i] = key[ch - 'A'];
        }
        else
            encrypted[i] = text[i];
    }

    encrypted[i] = '\0';

    for(i = 0; encrypted[i] != '\0'; i++)
    {
        if(isalpha(encrypted[i]))
        {
            for(j = 0; j < 26; j++)
            {
                if(key[j] == encrypted[i])
                {
                    decrypted[i] = 'A' + j;
                    break;
                }
            }
        }
        else
            decrypted[i] = encrypted[i];
    }

    decrypted[i] = '\0';

    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}