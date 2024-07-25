/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_coll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:19:54 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/23 19:26:47 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_aloc(t_free **list_aloc, t_free *new)
{
	t_free	*ptr;

	if (new == NULL)
		return ;
	if (!(*list_aloc))
	{
		*list_aloc = new;
		return ;
	}
	ptr = *list_aloc;
	while (ptr && ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

t_free	*ft_lstnew_aloc(void *ptr, t_free **list_aloc)
{
	t_free	*new;

	new = malloc(sizeof(t_free));
	if (!new)
		(ft_free(list_aloc), exit(1));
	new->ptr = ptr;
	new->next = NULL;
	return (new);
}

void	*gv_collc(t_free **list_aloc, size_t size)
{
	t_free	*new_node;
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		(ft_free(list_aloc), exit(1));
	new_node = ft_lstnew_aloc(ptr, list_aloc);
	ft_lstadd_back_aloc(list_aloc, new_node);
	return (ptr);
}

void	ft_free(t_free **list_aloc)
{
	t_free	*current;
	t_free	*next;

	current = *list_aloc;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		current->ptr = NULL;
		free(current);
		current = next;
	}
	*list_aloc = NULL;
}
