#include <stdio.h>

int power(int a, int b, int mod)
{
    int result = 1;
    a = a % mod;

    while (b > 0)
    {
        result = (result * a) % mod;
        b--;
    }

    return result;
}

int modInverse(int a, int mod)
{
    int i;

    for (i = 1; i < mod; i++)
    {
        if ((a * i) % mod == 1)
            return i;
    }

    return -1;
}

int main()
{
    int p, q, g, x, k, H;
    int y, r, s, w, u1, u2, v;

    printf("Enter prime number p: ");
    scanf("%d", &p);

    printf("Enter q (prime divisor of p-1): ");
    scanf("%d", &q);

    printf("Enter generator g: ");
    scanf("%d", &g);

    printf("Enter private key x: ");
    scanf("%d", &x);

    printf("Enter random number k: ");
    scanf("%d", &k);

    printf("Enter message hash H: ");
    scanf("%d", &H);

    if (p <= 2 || q <= 1 || g <= 1 || g >= p ||
        x < 1 || x >= q || k < 1 || k >= q || H < 0)
    {
        printf("Invalid input values.\n");
        return 1;
    }

    if (modInverse(k, q) == -1)
    {
        printf("Invalid k. Modular inverse does not exist.\n");
        return 1;
    }

    y = power(g, x, p);
    r = power(g, k, p) % q;

    if (r == 0)
    {
        printf("Invalid signature. Choose another k.\n");
        return 1;
    }

    s = (modInverse(k, q) * ((H + x * r) % q)) % q;

    printf("\nPublic key y = %d\n", y);
    printf("Signature (r, s) = (%d, %d)\n", r, s);

    printf("\nEnter received message hash: ");
    scanf("%d", &H);

    printf("Enter received signature r: ");
    scanf("%d", &r);

    printf("Enter received signature s: ");
    scanf("%d", &s);

    if (H < 0 || r <= 0 || r >= q ||
        s <= 0 || s >= q)
    {
        printf("Signature is invalid.\n");
        return 0;
    }

    w = modInverse(s, q);

    if (w == -1)
    {
        printf("Signature is invalid.\n");
        return 0;
    }

    u1 = (H * w) % q;
    u2 = (r * w) % q;

    v = ((power(g, u1, p) *
          power(y, u2, p)) % p) % q;

    printf("Verification value v = %d\n", v);

    if (v == r)
        printf("Signature is valid.\n");
    else
        printf("Signature is invalid.\n");

    return 0;
}