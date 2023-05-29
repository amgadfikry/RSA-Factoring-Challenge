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
	mpz_t n, div_n, mod_n, sqrt_n, mod_n2;
	
	if (argc != 2)
		return (1);

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
		mpz_init(mod_n2);
		mpz_set_str(n, line, 10);
		mpz_sqrt(sqrt_n, n);
		while (num)
		{
			mpz_mod(mod_n2, n, sqrt_n);
			if (mpz_cmp_ui(mod_n2, 0) == 0)
			{
				mpz_div(div_n, n, sqrt_n);
				gmp_printf("%Zd=%Zd*%Zd\n", n, div_n, sqrt_n);
				break;
			}
			if ((res = mpz_mod_ui(mod_n, n, num)) == 0)
			{
				mpz_divexact_ui(div_n, n, num);
				gmp_printf("%Zd=%Zd*%d\n", n, div_n, num);
				break;
			}
			mpz_sub_ui(sqrt_n, sqrt_n, 1);
			num++;
		}
		mpz_clear(n);
		mpz_clear(div_n);
		mpz_clear(mod_n2);
		mpz_clear(sqrt_n);
		mpz_clear(mod_n);
		num = 2;
	}
	fclose(file);
	free(line);
	return (0);
}
