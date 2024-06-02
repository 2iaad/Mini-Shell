#include <stdio.h>
#include <stdlib.h>

// Returns the length of the string 's'
int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

int	valid_meta(char *line, int i, int j, int valid)
{
	int		in1;
	int		in2;
	char	quote;

	while (line[j])
	{
		if (line[j] == '\'' || line[j] == '\"')
		{
			in1 = j;
			quote = line[j++];
			while (line[j] && line[j] != quote)
				j++;
			if (line[j] == quote)
				in2 = j;
			if (i > in1 && i < in2)
			{
				valid = 0;
				break ;
			}
		}
		else
			j++;
	}
	return (valid);
}

char	*remove_quotes(char *line)
{
	int i = 0;
	int j = 0;
	char *new_line;

	new_line = malloc(ft_strlen(line) + 1);
	if (!new_line)
		return NULL;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && valid_meta(line, i, 0, 1))
		{
			i++;
			continue;
		}
		new_line[j++] = line[i++];
		new_line[j] = '\0';
		return (new_line);
	}
}

int main()
{
    char *line = "echo \"hello\" world\" ls \"";
    char *result = remove_quotes(line);
    if (result)
    {
        printf("%s\n", result);
        free(result); // Free the allocated memory to prevent memory leak
    }
    return 0;
}


