#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

/* Advent of Code 2016
 * Solution for Day 5, Part 2
 */

void md5_hash(const char *str, unsigned char *digest)
{
	MD5_CTX md5;
	MD5_Init(&md5);
	MD5_Update(&md5, str, strlen(str));
	MD5_Final(digest, &md5);
}

int main(void)
{
	char *ins = "reyedfim";
	char pass[128] = { 0 };
	unsigned count = 0;
	unsigned num = 0;
	while (count < 8)
	{
		char str[128], hash[64];
		unsigned char digest[32];
		sprintf(str, "%s%d", ins, num++);
		md5_hash(str, digest);
		unsigned i, found = 0;
		for (i = 0; i < 16; i++)
			sprintf(&hash[i * 2], "%02x", digest[i]);
		for (i = 0; hash[i]; i++)
		{
			if (hash[i] == '0')
				found++;
			else
				break;
		}
		if (found >= 5)
		{
			int idx = hash[5] - '0';
			if (idx >= 0 && idx <= 7 && !pass[idx])
			{
				pass[idx] = hash[6];
				count++;
				printf("idx: %d ", idx);
				for (i = 0; i < 8; i++)
					putchar(!pass[i] ? '_' : pass[i]);
				printf(" %s\n", hash);
			}
		}
	}
	fprintf(stdout, "%s\n", pass);
	return 0;
}
