/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:39:41 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/02 19:07:10 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*nn;

	nn = (t_env *) malloc (sizeof(t_env));
	if (!nn)
		return (0);
	nn->key = key;
	nn->value = value;
	nn->next = NULL;
	return (nn);
}

void	ft_lstclear(t_env **lst)
{
	if (!lst || !(*lst))
		return ;
	if ((*lst)->next)
		ft_lstclear((&(*lst)->next));
	free((*lst)->key);
	free((*lst)->value);
	free(*lst);
	*lst = NULL;
}

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	ft_lstadd_back(t_env **lst, t_env *newn)
{
	t_env	*lastnode;

	if (!lst || !newn)
		return ;
	if (*lst == NULL)
		*lst = newn;
	else
	{
		lastnode = ft_lstlast(*lst);
		lastnode->next = newn;
	}
}
