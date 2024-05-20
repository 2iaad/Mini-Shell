#include <stdio.h>
#include <stdlib.h>

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

char	*parse_protec(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (valid_meta(&line[i], i, 0, 1))
		{
			if (line[i] == '<' && line[i + 1] == '<')
			{
				line[i] = -2;
				line[i + 1] = -2;
				i++;
			}
			else if (line[i] == '>' && line[i + 1] == '>')
			{
				line[i] = -4;
				line[i + 1] = -4;
				i++;
			}
			else if (line[i] == '|')
				line[i] = -5;
			else if (line[i] == '<')
				line[i] = -1;
			else if (line[i] == '>')
				line[i] = -3;
		}
		i++;
	}
	return (line);
}
int main() {
    char line2[] = "< | << >>"; // Test with multiple characters
	char *result = parse_protec(line2);

    // Print the modified line to see the changes
    for (int i = 0; result[i]; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}






// t_token *word(char *line, int *i)
// {
// 	char	*word;
// 	t_token	*node;
// 	int start;

// 	start = *i;
// 	while (line[*i] && !whitespaces(line[*i]))
// 		(*i)++;
// 	word = (char *)malloc(*i - start + 1);
// 	if (!word)
// 		return (NULL);
// 	while(start < *i)
// 	{
// 		word[start - *i] = line[start];
// 		start++;
// 	}
// 	word[start - *i] = '\0';
// 	node = ft_lstnew(word, WORD);
// 	if (!node)
// 		return (NULL);
// 	return (node);	
// }

// t_token *red_in_herdk(char *line, int *i)
// {
// 	char	*redir;
// 	t_token	*node;

// 	if (line[*i] == '<' && line[*i + 1] == '<')
// 	{
// 		redir = malloc(sizeof(char) * 3);
// 		if(!redir)
// 			return (NULL);
// 		redir[0] = line[*i];
// 		redir[1] = line[*i + 1];
// 		redir[2] = '\0';
// 		(*i)++;
// 		node = ft_lstnew(redir, REDIR_HEREDOC);
// 	}
// 	else
// 	{
// 		redir = malloc(sizeof(char) * 2);
// 		if (!redir)
// 			return (NULL);
// 		redir[0] = line[*i];
// 		redir[1] = '\0';
// 		(*i)++;
// 		node = ft_lstnew(redir, REDIR_IN);
// 	}
// 	if (!node)
// 		return (NULL);
// 	return (node);
// }

// t_token *red_out_apnd(char *line, int *i)
// {
// 	char	*redir;
// 	t_token	*node;

// 	if (line[*i] == '>' && line[*i + 1] == '>')
// 	{
// 		redir = malloc(sizeof(char) * 3);
// 		if (!redir)
// 			return (NULL);
// 		redir[0] = line[*i];
// 		redir[1] = line[*i + 1];
// 		redir[2] = '\0';
// 		(*i)++;
// 		node = ft_lstnew(redir, REDIR_APPEND);
// 	}
// 	else
// 	{
// 		redir = malloc(sizeof(char) * 2);
// 		if(!redir)
// 			return (NULL);
// 		redir[0] = line[*i];
// 		redir[1] = '\0';
// 		(*i)++;
// 		node = ft_lstnew(redir, REDIR_OUT);
// 	}
// 	if (!node)
// 		return (NULL);
// 	return (node);
// }

// t_token *ft_pipe(char *line, int *i)
// {
// 	char	*pipe;
// 	t_token	*node;

// 	pipe = (char *)malloc(2);
// 	pipe[0] = line[*i];
// 	pipe[1] = '\0'; 
// 	(*i)++;
// 	node = ft_lstnew(pipe, PIPE);
// 	if (!node)
// 		return (NULL);
// 	return (node);
// }

// void	tokenizer(char *line, t_token **token)
// {
// 	int	i;
// 	t_token *node;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (i == 0 || whitespaces(line[i]))
// 		{
// 			while (line[i] && whitespaces(line[i]))
// 				i++;
// 			if (line[i] != '|' && line[i] != '<' && line[i] != '>')
// 				node = word(line, &i);
// 			else if (line[i] == '|')
// 				node = ft_pipe(line, &i);
// 			else if (line[i] == '<')
// 				node = red_in_herdk(line, &i);
// 			else if (line[i] == '>')
// 				node = red_out_apnd(line, &i);
// 			if (node->token != NULL)
// 				ft_lstadd_back(token, node);
// 			else
// 				i++;
// 		}
// 	}
// }