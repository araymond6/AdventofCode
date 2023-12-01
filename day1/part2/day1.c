#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char numbers[9][8] = {
	{'o', 'n', 'e', '\0'},
	{'t', 'w', 'o', '\0'},
	{'t', 'h', 'r', 'e', 'e', '\0'},
	{'f', 'o', 'u', 'r', '\0'},
	{'f', 'i', 'v', 'e', '\0'},
	{'s', 'i', 'x', '\0'},
	{'s', 'e', 'v', 'e', 'n', '\0'},
	{'e', 'i', 'g', 'h', 't', '\0'},
	{'n', 'i', 'n', 'e', '\0'}
};

int	check_nums(char *line)
{
	int	i = 0;

	while (i < 9)
	{
		if (strncmp(line, numbers[i], strlen(numbers[i])) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int get_first(char *line)
{
	int check;

	while (*line != '\0')
	{
		check = check_nums(line);
		if (*line >= '0' && *line <= '9')
		{
			return (*line);
		}
		else if (check != -1)
		{
			return (check + 48 + 1);
		}
		++line;
	}
	return ('0');
}

int get_last(char *line)
{
	int check;
	char digit = '0';

	while (*line != '\0')
	{
		check = check_nums(line);
		if (*line >= '0' && *line <= '9')
		{
			digit = *line;
		}
		else if (check != -1)
		{
			digit = check + 48 + 1;
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