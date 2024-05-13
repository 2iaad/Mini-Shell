#include "includes/minishell.h"
#include "includes/tools.h"
#include <unistd.h>

// void    echo(t_list	*lst) // handle "echo -n -n"
// {
//     int flag;

//     flag = flag_check(lst->cmd[1]);
//     if (lst->cmd[1] == NULL) // echo
//         return (void) write(1, "\n", 1);
// 	if (!flag) // echo -n and echo -nnnnnn
// 	{
// 		if (lst->cmd[2])
// 			ft_putstr(lst->cmd[2], 1);
// 	}
// 	else
// 	{
// 		if (lst->cmd[1][0] == '$' && (lst->cmd[1][1] != '$' && lst->cmd[1][1] != '?')) // ila kan lst->cmd[1] o lst->cmd[1][0] = '$' => expand
// 			expand(lst, lst->cmd[1] + 1);
// 		else
// 			ft_putstr(lst->cmd[1], 1); // else echo string
// 	}
// 	if (flag)
// 		write(1, "\n", 1);
// }

int main()
{
	printf("%d",getpid());
}