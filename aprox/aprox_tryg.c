#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main( int argc, char **argv)
{
    int n = 0, m, i = 0, j;
    double *a, *b, *y, czyt;

    FILE *in = fopen( argc > 1 ? argv[1], "r" : "dane.txt", "r");
    FILE *out = fopen( argc > 2 ? argv[2], "w" : "wyniki.txt", "w");

    while( fscanf( in, "%lf", &czyt) == 1) // liczenie n
        n++;

    m = ( n - 1) / 2; // liczenie stopnia wielomianu
    if( n > m)
        m--;

    y = malloc( ( n + 5) * sizeof *y);
    a = malloc( ( m + 5) * sizeof *a);
    b = malloc( ( m + 5) * sizeof *b);

    fseek( in, 0, 0);
    while( fscanf( in, "%lf", &czyt) == 1) // wrzucanie danych do wektora
    {
        i++;
        y[i] = czyt;
    }

    a[0] = 0;
    for( j = 1; j <= n; j++) // wyliczenie a0
        a[0] += y[j];
    a[0] /= n;

    fprintf( out, "%f\n", a[0]);

    for( i = 1; i <= m; i++) // wyliczanie ai i bi
    {
        a[i] = 0;
        b[i] = 0;

        for( j = 1; j <= n; j++) // iteracja po yj
        {
            a[i] += y[j] * cos( 2 * i * j * M_PI / n);
            b[i] += y[j] * sin( 2 * i * j * M_PI / n);
        }

        a[i] = a[i] * 2 / n;
        b[i] = b[i] * 2 / n;

        fprintf( out, "%f\t%f\n", a[i], b[i]);
    }

    fclose(in);
    fclose(out);
    free(y);
    free(a);
    free(b);

    return EXIT_SUCCESS;
}
