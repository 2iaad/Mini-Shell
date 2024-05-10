#include "includes/minishell.h"
#include "includes/tools.h"

int	ft_lstsize(t_env *lst)
{
	int		nofn;
	t_env	*ptr2n;

	nofn = 0;
	ptr2n = lst;
	if (ptr2n == NULL)
		return (0);
	while (ptr2n != NULL)
	{
		ptr2n = ptr2n->next; 
		nofn++;
	}
	return (nofn);
}

void	d_node(t_env	**env_args)
{
	t_env *tmp0; // hadi fiha salam li 9bl mn HELLO
	t_env *tmp1;
	t_env *tmp2; // hadi fiha salam li mnwra HELLO

	tmp0 = *env_args;
	tmp1 = *env_args;
	while (tmp0)
	{
		if (!ft_strcmp(tmp0->key, "HELLO", 4))
		{
			tmp2 = tmp0->next;
			break;
		}
		tmp0 = tmp0->next;
	}
	while (tmp1)
	{
		if (!ft_strcmp(tmp1->next->key, "HELLO", 4))
		{
			free(tmp1->next);
			tmp1->next = tmp2;
			break;
		}
		tmp1 = tmp1->next;
	}
}

void f(){system("leaks a.out");}

int main(int ac, char **av)
{
	int i = 0;
	t_env *head;
	t_env *tmp;

	atexit(f);
	head = NULL;
	while (i < 7)
	{
		if (i == 4)
			ft_lstadd_back(&head, ft_lstnew("HELLO","cv"));
		else
			ft_lstadd_back(&head, ft_lstnew("salam","cv"));
		i++;
	}
	// printf("%s",head->key);
	tmp = head;
	while (tmp)
	{
		printf("%s--->%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	printf("-->%d\n", ft_lstsize(head));

	d_node(&head);
	// printf("\n\n\n\n");
	// tmp = *head;
	// while (tmp)
	// {
	// 	printf("%s--->%s\n", tmp->key, tmp->value);
	// 	tmp = tmp->next;
	// }
	// printf("-->%d\n", ft_lstsize(*head));
}