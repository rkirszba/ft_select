/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:20:26 by rkirszba          #+#    #+#             */
/*   Updated: 2019/06/26 19:46:29 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	cases_dir_file(struct stat fstat)
{
	if (S_ISDIR(fstat.st_mode))
	{
		if (fstat.st_mode & S_IWOTH)
		{
			if (fstat.st_mode & S_ISVTX)
				return (10);
			return (11);
		}
		return (1);
	}
	if (fstat.st_mode & S_IXUSR || fstat.st_mode & S_IXGRP\
		|| fstat.st_mode & S_IXOTH)
	{
		if (fstat.st_mode & S_ISUID)
			return (8);
		if (fstat.st_mode & S_ISGID)
			return (9);
		return (5);
	}
	return (0);
}

static int	give_arg_type(char *name)
{
	struct stat	fstat;

	if (stat(name, &fstat) == -1)
		return (0);
	if (S_ISLNK(fstat.st_mode))
		return (2);
	if (S_ISSOCK(fstat.st_mode))
		return (3);
	if (S_ISFIFO(fstat.st_mode))
		return (4);
	if (S_ISBLK(fstat.st_mode))
		return (6);
	if (S_ISCHR(fstat.st_mode))
		return (7);
	return (cases_dir_file(fstat));
}

t_arg		*create_argument(char *str)
{
	t_arg	*arg;

	if (!(arg = (t_arg*)malloc(sizeof(t_arg))))
		return (NULL);
	if (!(arg->str = ft_strdup((const char*)str)))
	{
		free_arg(&arg);
		return (NULL);
	}
	arg->selected = 0;
	arg->len = ft_strlen(arg->str);
	arg->type = give_arg_type(arg->str);
	return (arg);
}

void		append_argument(t_selecter *selecter, t_arg *arg)
{
	t_arg	*current;

	if (!(arg->str[0]))
	{
		free_arg(&arg);
		selecter->nb_args -= 1;
		return ;
	}
	if (arg->len > selecter->max_len)
		selecter->max_len = arg->len;
	if (!selecter->first_arg)
	{
		selecter->first_arg = arg;
		selecter->current_arg = arg;
		arg->next = arg;
		return ;
	}
	current = selecter->first_arg;
	while (current->next != selecter->first_arg)
		current = current->next;
	current->next = arg;
	arg->next = selecter->first_arg;
}

void		give_max_len(t_selecter *selecter)
{
	t_arg	*current;

	selecter->max_len = selecter->first_arg->len;
	current = selecter->first_arg->next;
	while (current != selecter->first_arg)
	{
		if (current->len > selecter->max_len)
			selecter->max_len = current->len;
		current = current->next;
	}
}
