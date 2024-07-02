#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct s_zbi
{
	int a;
	struct s_zbi *next;
}	t_zbi;

int main()
{
	t_zbi *a = malloc(sizeof(t_zbi));
	t_zbi *b = malloc(sizeof(t_zbi));
	t_zbi *c = malloc(sizeof(t_zbi));
	
	a->a = 1;
	a->next = b;	

	b->a = 2;
	b->next = c;	

	c->a = 3;
	c->next = NULL;

	t_zbi *tmp = a;

	a = a->next;

	printf("tmp->a   :    %d\n", tmp->a);
	printf("a->a     :    %d\n", a->a);
	free(tmp);

	printf("a->a     :    %d\n", a->a);
}