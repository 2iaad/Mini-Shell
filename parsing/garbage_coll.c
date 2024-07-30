/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_coll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:19:54 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/30 04:02:29 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// void	ft_back(t_garbage **lst, t_garbage *new)
// {
// 	t_garbage	*ptr;

// 	if (new == NULL)
// 		return ;
// 	if (!(*lst))
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	ptr = *lst;
// 	while (ptr && ptr->next)
// 		ptr = ptr->next;
// 	ptr->next = new;
// }

// t_garbage	*ft_new(void *pt, t_garbage **lst)
// {
// 	t_garbage	*new;

// 	new = malloc(sizeof(t_garbage));
// 	if (!new)
// 		(ft__free(lst), exit(1));
// 	new->ptr = pt;
// 	new->next = NULL;
// 	return (new);
// }

// void	*gv_collc(t_garbage **lst, size_t len)
// {
// 	t_garbage	*new_node;
// 	void	*pt;

// 	pt = malloc(len);
// 	if (!pt)
// 		(ft__free(lst), exit(1));
// 	new_node = ft_new(pt, lst);
// 	ft_back(lst, new_node);
// 	return (pt);
// }

// void	ft__free(t_garbage **lst)
// {
// 	t_garbage	*cur;
// 	t_garbage	*next;

// 	cur = *lst;
// 	while (cur)
// 	{
// 		next = cur->next;
// 		free(cur->ptr);
// 		cur->ptr = NULL;
// 		free(cur);
// 		cur = next;
// 	}
// 	*lst = NULL;
// }

// static void    garb_add(t_c_addresses **lst, t_c_addresses *new)
// {
// 	t_c_addresses    *lastone;
// 	if (!lst || !new)
// 		return ;
// 	if (!(*lst))
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	lastone = *lst;
// 	while (lastone->next)
// 		lastone = lastone->next;
// 	lastone->next = new;
// 	new->next = NULL;
// }
// static t_c_addresses    *garb_new(void *addrress)
// {
// 	t_c_addresses    *newnode;
// 	newnode = malloc(sizeof(t_c_addresses));
// 	if (newnode == NULL)
// 	{
// 		perror("malloc");
// 		return (NULL);
// 	}
// 	newnode->adr = addrress;
// 	newnode->next = NULL;
// 	return (newnode);
// }
// void    *my_alloc(size_t size)
// {
// 	static t_c_addresses    *gooper;
// 	t_c_addresses            *node;
// 	void                    *address;
// 	address = malloc(size);
// 	if (!address)
// 		(perror("malloc"), exit(1));
// 	if (gooper == NULL)
// 		gooper = garb_new(address);
// 	else
// 	{
// 		node = garb_new(address);
// 		garb_add(&gooper, node);
// 	}
// 	return (address);
// }
