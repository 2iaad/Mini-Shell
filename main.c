#include "includes/minishell.h"
#include "includes/tools.h"

void	alpha_arrang(t_env *env)
{
	char *temp;
	t_env *tmp;

	tmp = env;
	while (tmp && tmp->next)
	{
		if (tmp->key[0] > tmp->next->key[0])
		{
			temp = tmp->key;
			tmp->key = tmp->next->key;
			tmp->next->key = temp;
			tmp = env;
		}
		else
			tmp = tmp->next;
	}
}

void f(){system("leaks a.out");}

int main(int ac, char **av)
{
	int i = 0;
	t_env *head;
	t_env *tmp;
	t_env *tmp2;

	// atexit(f);
	head = NULL;
	while (i < 3)
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("armani"),ft_strdup("cv")));
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("maserati"),ft_strdup("cv")));
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("black_jack"),ft_strdup("cv")));
		i++;
	}


	tmp2 = head;
	while (tmp2)
	{
		printf("%s--->%s\n", tmp2->key, tmp2->value);
		tmp2 = tmp2->next;
	}

	printf("\n\n\nafter:\n\n\n");

	alpha_arrang(head);
	tmp = head;
	while (tmp)
	{
		printf("%s--->%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	ft_lstclear(&head);
}