/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:14:32 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/03 10:35:24 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/tools.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] == s2[i])
        i++;
    return(s1[i] - s2[i]);
}
