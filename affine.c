#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(char* arg0)
{
		printf("Usage: %s [OPTIONS] [KEYA] [KEYB] \n\n", arg0);
		printf("Enciphers stdin using the affine cypher with (KEYA * x + KEYB)mod26\n\n", arg0);
		printf("Options:\n");
		printf("\t-h, --help\t\tPrint this help message\n");
		printf("\t-a, --key-a\t\tUse specified key A\n");
		printf("\t-b, --key-b\t\tUse specified key B\n");
}

int mod_inverse(int a, int m)
{
	// Since our modulus is only 26, we don't have to do this very efficiently
	a = a % m;
	for (int i = 1; i < m; i++)
		if ((a * i) % m == 1)
			return i;
	return 0; // No inverse
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		print_usage(argv[0]);
		return 1;
	}

	int key_a, key_b, decrypt = 0;

	if (argc == 3)
	{
		key_a = atoi(argv[1]);
		key_b = atoi(argv[2]);
	}

	// parse command line arguments
	for (int i = 1; i < argc; i++) // start at [1] to skip executable name
	{
		if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
		{
			print_usage(argv[0]);
			return 1;
		}
		else if (!strcmp(argv[i], "-a") || !strcmp(argv[i], "--key-a"))
			key_a = atoi(argv[i+1]);
		else if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--key-b"))
			key_b = atoi(argv[i+1]);
		else if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--decrypt"))
			decrypt = 1;
	}

	int i, c;
	if (!decrypt)
	{
		for (i = 0; (c = getchar()) != EOF; i++)
		{
			int alphabet_pos, is_capital = 0;
			if (c >= 'a' && c <= 'z')
				alphabet_pos = c - 'a';
			else if (c >= 'A' && c <= 'Z')
			{
				is_capital = 1;
				alphabet_pos = c - 'A';
			}
			else // character is not a letter; output it as-is and move on
			{
				putchar(c);
				continue;
			}

			char enciphered_char_pos = (key_a * alphabet_pos + key_b) % 26;
			if (is_capital)
				putchar(enciphered_char_pos + 'A');
			else
				putchar(enciphered_char_pos + 'a');
		}
	}
	else
	{
		for (i = 0; (c = getchar()) != EOF; i++)
		{
			int alphabet_pos, is_capital = 0;
			if (c >= 'a' && c <= 'z')
				alphabet_pos = c - 'a';
			else if (c >= 'A' && c <= 'Z')
			{
				is_capital = 1;
				alphabet_pos = c - 'A';
			}
			else // character is not a letter; output it as-is and move on
			{
				putchar(c);
				continue;
			}

			char deciphered_char_pos = (mod_inverse(key_a, 26) * (alphabet_pos - key_b)) % 26;
			if (deciphered_char_pos < 0) // why does C make me do this :(
				deciphered_char_pos = 26 + deciphered_char_pos;
			if (is_capital)
				putchar(deciphered_char_pos + 'A');
			else
				putchar(deciphered_char_pos + 'a');
		}
	}
}
