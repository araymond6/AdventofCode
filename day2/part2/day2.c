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

// defining colors and their limits
int redmin = 0, greenmin = 0, bluemin = 0;
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

// sets the value if the # of cubes pulled out is higher than what has been seen
void	set_value(int value, int color)
{
	if (color == RED)
	{
		if (value > redmin)
			redmin = value;
	}
	else if (color == GREEN)
	{
		if (value > greenmin)
			greenmin = value;
	}
	else //if color is blue
	{
		if (value > bluemin)
			bluemin = value;
	}
}

// checks color to change, if needed
void	check_color(char *line, int value)
{
	int	color = 0;

	while(color < 3)
	{
		if (strncmp(cubes[color], line, strlen(cubes[color])) == 0)
		{
			set_value(value, color);
			break;
		}
		color++;
	}
}

void	reset_min(void)
{
	redmin = 0;
	greenmin = 0;
	bluemin = 0;
}

int	check_game(char *line)
{
	static int	gameid = 1;

	// skipping gameid
	while (*line != ':')
		line++;
	line += 2;

	//resetting values for new game
	reset_min();

	while (*line != '\0')
	{
		int value = get_value(line);
		t_token type = get_type(*line);
		while (type != COLOR) // skipping until color
		{
			line++;
			type = get_type(*line);
		}
		check_color(line, value);
		type = get_type(*line);
		while (type != DIGIT && *line != '\0') // setting up start of the loop
		{
			line++;
			type = get_type(*line);
		}
	}
	return (redmin * greenmin * bluemin);
}

int	main()
{
	FILE *file = fopen("data", "r");
	unsigned int total = 0;
	char line[500];

	while (fgets(line, sizeof(line), file) != NULL)
	{
		total += check_game(line);
	}
	printf("total: %d\n", total);
}