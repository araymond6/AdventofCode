#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// for getting the color when iterating through cubes
#define RED 0
#define GREEN 1
#define BLUE 2

typedef enum token
{
	DIGIT,
	COLOR,
	OTHER
}	t_token;

// defining colors
int redmin, greenmin, bluemin;
char cubes[3][6] = {
	{'r', 'e', 'd', '\0'},
	{'g', 'r', 'e', 'e', 'n', '\0'},
	{'b', 'l', 'u', 'e', '\0'}
};

t_token	get_type(char c)
{
	if (isdigit(c))
		return (DIGIT);
	else if (isalpha(c))
		return (COLOR);
	else
		return (OTHER);
}

// gets the # of cubes pulled out of the bag
int	get_value(char *line)
{
	char	num[4];
	int		i = 0;
	t_token type = get_type(*line);

	while (type == DIGIT)
	{
		num[i++] = *line;
		line++;
		type = get_type(*line);
	}
	num[i] = '\0';
	return (atoi(num));
}

void	reset_min()
{
	redmin = 0;
	greenmin = 0;
	bluemin = 0;
}

int	check_min(int value, int color)
{
	if (color == RED)
	{
		if (value > redlimit)
			return (1);
	}
	else if (color == GREEN)
	{
		if (value > greenlimit)
			return (1);
	}
	else //if color is blue
	{
		if (value > bluelimit)
			return (1);
	}
	return (0);
}

// returns 1 if the amount of cubes pulled out is over the limit
int	validate_cube(char *line, int value)
{
	int	color = 0;

	while(color < 3)
	{
		if (strncmp(cubes[color], line, strlen(cubes[color])) == 0)
		{
			if (check_limits(value, color) == 1)
				return (1);
			break;
		}
		color++;
	}
	return (0);
}

int	check_game(char *line)
{
	static int	gameid = 1;

	// skipping gameid
	while (*line != ':')
		line++;
	line += 2;

	while (*line != '\0')
	{
		int value = get_value(line);
		t_token type = get_type(*line);
		while (type != COLOR) // skipping until color
		{
			line++;
			type = get_type(*line);
		}
		if (validate_cube(line, value) == 1)
		{
			gameid++;
			return (0);
		}
		type = get_type(*line);
		while (type != DIGIT && *line != '\0') // setting up start of the loop
		{
			line++;
			type = get_type(*line);
		}
	}
	return (gameid++);
}

int	main()
{
	FILE *file = fopen("dataexample2", "r");
	unsigned int total = 0;
	char line[500];

	while (fgets(line, sizeof(line), file) != NULL)
	{
		total += check_game(line);
	}
	printf("total: %d\n", total);
}