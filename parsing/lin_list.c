/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lin_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 03:09:32 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/09 03:47:37 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_token	*ft_lstnew(char *content, int type)
{
	t_token	*n;

	n = (t_token *)malloc(sizeof(t_token));
	if (!n)
		return (NULL);
	n->token = content;
	n->type = type;
	n->next = NULL;
	return (n);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		last = ft_lstlast(*lst);
		last -> next = new;
	}
}
