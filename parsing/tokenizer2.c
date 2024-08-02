/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:39:20 by ibouram           #+#    #+#             */
/*   Updated: 2024/08/02 19:26:37 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_quotes(t_token **token)
{
	t_token	*node;
	int		i;

	node = *token;
	while (node)
	{
		i = 0;
		while (node->token[i])
		{
			if (node->token[i] == '\'')
				node->token[i] = -1;
			else if (node->token[i] == '\"')
				node->token[i] = -2;
			i++;
		}
		node = node->next;
	}
}

void	add_node_middle(t_token **node1, t_token **node2, t_token **next_node, char *content, int type)
{
    t_token	*node;

    node = ft_get_token(content, type);
    *next_node = node;
    if (node != NULL && node->token != NULL)
    {
        if (*node2 != *node1)
        {
            node->next = (*node2)->next;
            (*node2)->next = node;
            *node2 = node;
        }
        else
        {
            node->next = (*node1);
            *node2 = node;
            *node1 = node;  // Move node1 forward
        }
    }
}


void split_var_tokens(t_token **token)
{
    t_token *node;
    t_token *node_2;
    t_token *next_node;
    char **split;
    char **split_var;
    int i;

    node = *token;
    while (node)
    {
        node_2 = node;
        if (node->type != WORD || !node->var_flg)
        {
            node = node->next;
            continue;
        }
        printf("token = %s, flg: %d\n", node->token, node->var_flg);
        split = split_line(node->token);
        next_node = node->next;
        if (count_words(node->token) > 1)
        {
            i = 0;
            while (split[i])
            {
                split_var = split_line(split[i]);  // Split the variable value
                int var_count = count_words(split[i]);
                if (var_count > 1)
                {
                    add_node_middle(&node, &node_2, &next_node, split_var[var_count - 1], WORD);  // Add only the last part
                    // free_split(split_var); // Free the split_var array if necessary
                }
                else
                {
                    add_node_middle(&node, &node_2, &next_node, split[i], WORD);
                }
                i++;
            }
            node = next_node; // Update node to the original next node
            // free_split(split); // Free the split array if necessary
        }
        else
        {
            node = node->next; // If the token doesn't contain more than one word, move to the next node
        }
        // Free split array if necessary
        // free_split(split); // Assuming you have a function to free the split array
    }
}



int	tokenizer(char **splited, t_token **token, t_env *env)
{
	int	ambg_redir;

	tokenizer_1(splited, token);
	if (syntax_error(*token))
		return (1);
	tokenizer_2(token);
	replace_quotes(token);
	expanding(*token, env);
	split_var_tokens(token);
	tokenizer_3(token);
	return (0);
}
