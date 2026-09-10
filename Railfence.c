#include <stdio.h>
#include <string.h>

int main()
{
    char text[100], encrypted[100], decrypted[100];
    char rail[20][100];

    int rails, len;
    int i, j, row, direction;
    int index;

    printf("Enter message: ");
    scanf(" %[^\n]", text);

    printf("Enter number of rails: ");
    scanf("%d", &rails);

    len = strlen(text);

    if(rails <= 1 || rails > len)
    {
        printf("Invalid number of rails\n");
        return 0;
    }

    for(i = 0; i < rails; i++)
        for(j = 0; j < len; j++)
            rail[i][j] = '\0';

    row = 0;
    direction = 1;

    for(i = 0; i < len; i++)
    {
        rail[row][i] = text[i];

        if(row == 0)
            direction = 1;
        else if(row == rails - 1)
            direction = -1;

        row += direction;
    }

    index = 0;

    for(i = 0; i < rails; i++)
    {
        for(j = 0; j < len; j++)
        {
            if(rail[i][j] != '\0')
                encrypted[index++] = rail[i][j];
        }
    }

    encrypted[index] = '\0';

    for(i = 0; i < rails; i++)
        for(j = 0; j < len; j++)
            rail[i][j] = '\0';

    row = 0;
    direction = 1;

    for(i = 0; i < len; i++)
    {
        rail[row][i] = '*';

        if(row == 0)
            direction = 1;
        else if(row == rails - 1)
            direction = -1;

        row += direction;
    }

    index = 0;

    for(i = 0; i < rails; i++)
    {
        for(j = 0; j < len; j++)
        {
            if(rail[i][j] == '*')
                rail[i][j] = encrypted[index++];
        }
    }

    row = 0;
    direction = 1;

    for(i = 0; i < len; i++)
    {
        decrypted[i] = rail[row][i];

        if(row == 0)
            direction = 1;
        else if(row == rails - 1)
            direction = -1;

        row += direction;
    }

    decrypted[len] = '\0';

    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}