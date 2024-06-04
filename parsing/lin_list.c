/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lin_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 03:09:32 by ibouram           #+#    #+#             */
/*   Updated: 2024/06/04 02:41:55 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

t_token	*ft_lstnew_parse(char *content, int type)
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

t_token	*ft_lstlast_parse(t_token *lst)
{
	t_token	*last;

	if (!lst)
		return (NULL);
	last = NULL;
	while (lst)
	{
		last = lst;
		lst = lst->next;
	}
	return (last);
}

t_env	*ft_lstlast2_parse(t_env *lst)
{
	t_env	*last;

	last = NULL;
	while (lst)
	{
		last = lst;
		lst = lst->next;
	}
	return (last);
}

void	ft_lstadd_back_parse(t_token **lst, t_token *new)
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
		last = ft_lstlast_parse(*lst);
		last->next = new;
	}
}


t_final	*ft_lstlast3_parse(t_final *lst)
{
	t_final	*last;

	if (!lst)
		return (NULL);
	last = NULL;
	while (lst)
	{
		last = lst;
		lst = lst->next;
	}
	return (last);
}

void	ft_lstadd_back3_parse(t_final **lst, t_final *new)
{
	t_final	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		last = ft_lstlast3_parse(*lst);
		last->next = new;
	}
}

void	ft_lstadd_back_2_parse(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		last = ft_lstlast2_parse(*lst);
		last->next = new;
	}
}
