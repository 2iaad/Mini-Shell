#include <stdio.h>
#include <stdlib.h>
int	whitespaces(char s)
{
	return (s == ' ' || s == '\t' || s == '\n' || s == '\v' || s == '\f' || s == '\r');
}

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*space(char *line)
{
	// add space before and after "<", ">", ">>", "|"
	int		i;
	int		j;
	int 	len;
	char 	*new_line;

	i = 0;
	j = 0;
	len = ft_strlen(line);
	new_line = malloc((len * 3) + 1);
	while (line[i])
	{
		// if ((line[i] == '<' && line[i + 1] == '<') ||
		// 	(line[i] == '>' || line[i + 1] == '>'))
		// {
		// 	//cause check i - 1 so should i > 0
		// 	if (i > 1 && !whitespaces(line[i - 2]))
		// 		new_line[j++] = ' ';
		// 	new_line[j++] = line[i]; // add the char '>'
		// 	if (line[i + 2] && !whitespaces(line[i + 2]))
		// 		new_line[j++] = ' ';
		// }
		if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			//cause check i - 1 so should i > 0
			if (i > 0 && !whitespaces(line[i - 1]))
				new_line[j++] = ' ';
			new_line[j++] = line[i]; // add the char '>'
			if (line[i + 1] && !whitespaces(line[i + 1]))
				new_line[j++] = ' ';
		}
		else
			new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}
int main() {
    char s[] = "<ls>output|dd<<ls";
    char *modified = space(s);
    printf("%s\n", modified);
    free(modified); // Don't forget to free the allocated memory
    return 0;
}