#include <stdio.h>
#include <ctype.h>

int modInverse(int n)
{
    int i;

    for(i = 1; i < 26; i++)
    {
        if((n * i) % 26 == 1)
            return i;
    }

    return -1;
}

int mod(int n)
{
    n = n % 26;

    if(n < 0)
        n += 26;

    return n;
}

int main()
{
    char text[100], clean[100];
    char encrypted[100], decrypted[100];

    int key[2][2], inverse[2][2];
    int i, n = 0;
    int det, invDet;
    int a, b;

    printf("Enter message: ");
    scanf(" %[^\n]", text);

    printf("Enter 2x2 key matrix:\n");

    scanf("%d %d", &key[0][0], &key[0][1]);
    scanf("%d %d", &key[1][0], &key[1][1]);

    for(i = 0; text[i] != '\0'; i++)
    {
        if(isalpha(text[i]))
        {
            clean[n] = toupper(text[i]);
            n++;
        }
    }

    if(n % 2 != 0)
    {
        clean[n] = 'X';
        n++;
    }

    clean[n] = '\0';

    det = mod(key[0][0] * key[1][1] -
              key[0][1] * key[1][0]);

    invDet = modInverse(det);

    if(invDet == -1)
    {
        printf("Invalid key matrix\n");
        return 0;
    }

    inverse[0][0] = mod(key[1][1] * invDet);
    inverse[0][1] = mod(-key[0][1] * invDet);
    inverse[1][0] = mod(-key[1][0] * invDet);
    inverse[1][1] = mod(key[0][0] * invDet);

    for(i = 0; i < n; i += 2)
    {
        a = clean[i] - 'A';
        b = clean[i + 1] - 'A';

        encrypted[i] =
            mod(key[0][0] * a + key[0][1] * b) + 'A';

        encrypted[i + 1] =
            mod(key[1][0] * a + key[1][1] * b) + 'A';
    }

    encrypted[n] = '\0';

    for(i = 0; i < n; i += 2)
    {
        a = encrypted[i] - 'A';
        b = encrypted[i + 1] - 'A';

        decrypted[i] =
            mod(inverse[0][0] * a +
                inverse[0][1] * b) + 'A';

        decrypted[i + 1] =
            mod(inverse[1][0] * a +
                inverse[1][1] * b) + 'A';
    }

    decrypted[n] = '\0';

    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
