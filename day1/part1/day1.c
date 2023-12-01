#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int get_first(char *line)
{
	while (*line != '\0')
	{
		if (*line >= '0' && *line <= '9')
		{
			return (*line);
		}
		++line;
	}
	return ('0');
}

int get_last(char *line)
{
	char digit = '0';

	while (*line != '\0')
	{
		if (*line >= '0' && *line <= '9')
		{
			digit = *line;
		}
		++line;
	}
	return (digit);
}

int	get_count(char *line)
{
	char nums[3];
	int line_total = 0;

	nums[0] = get_first(line);
	nums[1] = get_last(line);
	nums[2] = '\0';

	line_total = atoi(nums);
	return (line_total);
}

int main()
{
	FILE *file = fopen("data", "r");
	uint32_t total = 0;
	char line[100];
	int nbcount = 0;

	while (fgets(line, sizeof(line), file) != NULL)
	{
		total += get_count(line);
	}
	printf("%d", total);
	fclose(file);
}