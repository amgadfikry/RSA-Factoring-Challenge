#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <gmp.h>

/**
 * main - function that factorize as many as possible
 * into product of two smaller number
 * @argc: length of args
 * @argv: array of args in function
 * Return: 0 if success to end
 */

int main(int argc, char *argv[])
{
	FILE *file;
	ssize_t line_num;
	size_t line_n = 0;
	char *line = NULL;
	unsigned int num = 2, res;
	mpz_t n, div_n, mod_n, sqrt_n;
	(void) argc;

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Can't open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while ((line_num = getline(&line, &line_n, file)) != -1)
	{
		mpz_init(n);
		mpz_init(div_n);
		mpz_init(mod_n);
		mpz_init(sqrt_n);
		mpz_set_str(n, line, 10);
		mpz_sqrt(sqrt_n, n);
		mpz_mod(mod_n, n, sqrt_n);
		if (mpz_cmp_ui(mod_n, 0) == 0)
		{
			gmp_printf("%Zd=%Zd*%Zd\n", n, sqrt_n, sqrt_n);		
			num = 0;
		}
		while (num != 0)
		{
			if ((res = mpz_mod_ui(mod_n, n, num)) == 0)
			{
				mpz_divexact_ui(div_n, n, num);
				gmp_printf("%Zd=%Zd*%d\n", n, div_n, num);
				break;
			}
			num++;
		}
		mpz_clear(n);
		mpz_clear(div_n);
		mpz_clear(mod_n);
		mpz_clear(sqrt_n);
		num = 2;
	}
	fclose(file);
	free(line);
	return (0);
}
