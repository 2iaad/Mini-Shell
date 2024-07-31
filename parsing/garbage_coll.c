/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_coll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:19:54 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/31 02:51:04 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_back_gv(t_garbage **lst, t_garbage *new)
{
	t_garbage	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->next = NULL;
}

static t_garbage	*new_gv(void *add)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (new == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	new->ptr = add;
	new->next = NULL;
	return (new);
}

void	*gv_coll(size_t size)
{
	static t_garbage	*ptr;
	t_garbage			*node;
	void				*add;

	add = malloc(size);
	if (!add)
		(perror("malloc"), exit(1));
	if (ptr == NULL)
	{
		ptr = new_gv(add);
		add_to_gc(ptr);
	}
	else
	{
		node = new_gv(add);
		add_back_gv(&ptr, node);
	}
	return (add);
}

void	add_to_gc(void *addr)
{
	static t_garbage	*ptr;
	t_garbage			*node;

	if (!ptr)
		ptr = addr;
	else
	{
		node = new_gv(addr);
		add_back_gv(&ptr, node);
	}
}
