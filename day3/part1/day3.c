#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>


typedef struct s_value
{
	int max_x;
	int max_y;
	int range[2][2];
	int num[2];
	char **table;
}	t_value ;
t_value v;

//frees the double array
void	free_table(char **table)
{
	int	i = 0;
	if (table)
	{
		while (table[i++])
		{
			if (table[i])
				free(table[i]);
		}
		free(table);
	}
}

// callocs a table that is the size of the engine schematic needed
char	**get_table(void)
{
	FILE *file = fopen("data", "r");
	char line[200];
	int y = 0;
	int x = 0;
	while (fgets(line, sizeof(line), file) != NULL)
	{
		if (x == 0)
			x = strlen(line);
		y++;
	}
	fclose(file); // always close the file, I made that mistake enough

	// sets the max to avoid having to check it later
	v.max_y = y;
	v.max_x = x;
	char **table = calloc(y + 1, sizeof(char *)); //calloc for table's height
	if (!table)
		return (NULL);

	int i = 0;
	while (i < y)
	{
		table[i] = calloc(x + 1, sizeof(char)); // callocs for table's width
		if (!table[i])
		{
			free_table(table);
			return (NULL);
		}
		i++;
	}

	return (table);
}

// sets all the value of the table according to the engine schematics
void	set_table(char **table)
{
	FILE *file = fopen("data", "r");
	char line[200];
	int	y = 0;
	while (fgets(line, sizeof(line), file) != NULL)
	{
		int x = 0;
		while (line[x])
		{
			table[y][x] = line[x];
			x++;
		}
		y++;
	}
	fclose(file);
}

// sets the range to be able to check for special characters within that range
void	set_range(int y, int x)
{
	if (x == 0)
	{

	}
	else if (x == v.max_x)
	{

	}
}

void	get_number(int y, int x)
{
	char number[4];
	int	i = 0;

	while (isdigit(v.table[y][x]))
	{
		number[i++] = v.table[y][x++];
	}
	number[i] = '\0';
	v.num[1] = atoi(number);
	v.num[2] = i;
}

// handles first line and last line exceptions too
unsigned int	add_numbers(void)
{
	int y = 0;

	while (v.table[y])
	{
		int	x = 0;
		while (v.table[y][x])
		{
			if (isdigit(v.table[y][x]))
			{
				get_number(y, x);
				set_range(y, x);
			}
		}
	}
}

int	main()
{
	unsigned int total = 0;
	v.table = get_table();

	set_table(v.table);
	total += add_numbers();
	printf("total: %d\n", total);
	free_table(v.table);
}