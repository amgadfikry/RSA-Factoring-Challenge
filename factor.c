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
	mpz_t num, num_half, num_mod, num_div, num_ui, num_mod_ui, num_div_ui;
	mpz_t num_sqrt, num_mod_sq, num_div_sq;
	
	if (argc != 2)
		exit(EXIT_FAILURE);

	file = fopen(argv[1], "r");
	if (file == NULL)
		exit(EXIT_FAILURE);

	while ((line_num = getline(&line, &line_n, file)) != -1)
	{
		mpz_init(num);
		mpz_init(num_half);
		mpz_init(num_mod);
		mpz_init(num_div);
		mpz_init(num_ui);
		mpz_init(num_mod_ui);
		mpz_init(num_div_ui);
		mpz_init(num_sqrt);
		mpz_init(num_mod_sq);
		mpz_init(num_div_sq);

		mpz_set_str(num, line, 10);
		mpz_set_ui(num_ui, 2);
		mpz_divexact_ui(num_half, num, 2);
		mpz_sqrt(num_sqrt, num);

		while (1)
		{
			mpz_mod(num_mod, num, num_half);
			if (mpz_cmp_ui(num_mod, 0) == 0)
			{
				mpz_div(num_div, num, num_half);
				gmp_printf("%Zd=%Zd*%Zd\n", num, num_half, num_div);
				break;
			}
			mpz_sub_ui(num_half, num_half, 1);

			mpz_mod(num_mod_ui, num, num_ui);
			if (mpz_cmp_ui(num_mod_ui, 0) == 0)
			{
				mpz_div(num_div_ui, num, num_ui);
				gmp_printf("%Zd=%Zd*%Zd\n", num, num_div_ui, num_ui);
				break;
			}
			mpz_add_ui(num_ui, num_ui, 1);

			mpz_mod(num_mod_sq, num, num_sqrt);
			if (mpz_cmp_ui(num_mod_sq, 0) == 0)
			{
				mpz_div(num_div_sq, num, num_sqrt);
				gmp_printf("%Zd=%Zd*%Zd\n", num, num_sqrt, num_div_sq);
				break;
			}
			mpz_sub_ui(num_sqrt, num_sqrt, 1);
		}
		mpz_clear(num);
		mpz_clear(num_half);
		mpz_clear(num_mod);
		mpz_clear(num_div);
		mpz_clear(num_ui);
		mpz_clear(num_mod_ui);
		mpz_clear(num_div_ui);
		mpz_clear(num_sqrt);
		mpz_clear(num_mod_sq);
		mpz_clear(num_div_sq);
	}

	fclose(file);
	free(line);
	exit(EXIT_SUCCESS);
	return (0);
}
