#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

/* Day 4: The Ideal Stocking Stuffer */
/* Part 2 */
/* bruteforce an md5 hash until you find
 * the lowest number that produces an md5 hash
 * with at least 6 leading zeros
 */

unsigned bruteforce_hash(const char *key)
{
	unsigned num = 1;
	const unsigned LEADING_ZEROS = 6;
	while (1)
	{
		unsigned char hash[MD5_DIGEST_LENGTH];
		char hex[MD5_DIGEST_LENGTH];
		char str[100];
		sprintf(str, "%s%u", key, num);

		MD5(str, strlen(str), hash);

		unsigned i; /* convert unsigned char to 2char hex */
		for (i = 0; i < MD5_DIGEST_LENGTH; i++)
		{
			sprintf(&hex[i * 2], "%02x", hash[i]);
		}

		unsigned j;
		unsigned zero_ct = 0; /* count number of zeros */
		for (j = 0; j < LEADING_ZEROS; j++)
		{
			if (hex[j] == '0')
			{
				zero_ct++;
			}
		}
		if (zero_ct == LEADING_ZEROS)
			return num;
		else
			num++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage: %s %s\n", argv[0], "filename");
		return 0;
	}
	FILE *file = fopen(argv[1], "r");
	if (!file)
	{
		perror("Could not open file.\n");
		return 1;
	}
	char key[10];
	fscanf(file, "%s", key);
	printf("%u\n", bruteforce_hash(key));

	fclose(file);
	return 0;
}
