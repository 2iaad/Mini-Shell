/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:49:29 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/18 21:41:26 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_words(char *line)
{
    int i;
    int count;
    char quote;

    i = 0;
    count = 0;
    while (line[i])
    {
        while (line[i] && whitespaces(line[i]))
            i++;
        if (i == 0 && line[i])
            count++;
        else if (i > 0 && whitespaces(line[i - 1]))
        {
            count++;
            if (line[i] == '\'' || line[i] == '\"')
            {
                quote = line[i++];
                while (line[i] && line[i] != quote)
                    i++;
            }
        }
        i++;
    }
    return (count);
}

static int calc_len(char *line)
{
    int i;
    int count;
    char quote;

    count = 0;
    i = 0;
    while (line[i] && !whitespaces(line[i]))
    {
        if (line[i] == '\'' || line[i] == '\"')
        {
            (1) && (count++, quote = line[i++]);
            while (line[i] && line[i] != quote)
                (1) && (i++, count++);
            (i++, count++);
        }
        else
        {
            count++;
            i++;
        }
    }
    return (count);
}

static char *get_tok(char **line)
{
    int i;
    char *subs;
    int len;
    // int in_quotes = 0;

    while (**line && whitespaces(**line))
        (*line)++;
    len = calc_len(*line);
    subs = malloc(len + 1);
    if (!subs)
        return (NULL);
    i = 0;
    while (i < len)
    {
        subs[i] = **line;
        i++;
        (*line)++;
    }
    subs[i] = '\0';
    return (subs);
}

char **split_line(char *line)
{
    int nbr_toks;
    char **toks;
    int i;

    i = 0;
    if (!line)
        return (NULL);
    nbr_toks = count_words(line);
    toks = malloc (sizeof(char*) * (nbr_toks + 1));
    if (!toks)
        return (NULL);
    while (i < nbr_toks)
    {
        toks[i] = get_tok(&line);
        if (!toks[i])
            return (NULL);
        i++;
    }
    toks[i] = NULL;
    return (toks);
}
