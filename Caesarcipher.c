#include <stdio.h>
#include <ctype.h>

int main()
{
    char text[100];
    char encrypted[100], decrypted[100];
    int key, i;

    printf("Enter message: ");
    scanf(" %[^\n]", text);

    printf("Enter key: ");
    scanf("%d", &key);

    key = key % 26;

    for(i = 0; text[i] != '\0'; i++)
    {
        if(isalpha(text[i]))
        {
            char ch = toupper(text[i]);
            encrypted[i] = (ch - 'A' + key) % 26 + 'A';
        }
        else
            encrypted[i] = text[i];
    }

    encrypted[i] = '\0';

    for(i = 0; encrypted[i] != '\0'; i++)
    {
        if(isalpha(encrypted[i]))
            decrypted[i] = (encrypted[i] - 'A' - key + 26) % 26 + 'A';
        else
            decrypted[i] = encrypted[i];
    }

    decrypted[i] = '\0';

    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}