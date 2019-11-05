/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:10:12 by rkirszba          #+#    #+#             */
/*   Updated: 2019/06/26 19:48:59 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		manage_right_arrow(t_selecter *selecter)
{
	if (!selecter->freeze)
		selecter->current_arg = selecter->current_arg->next;
	return (0);
}

int		manage_left_arrow(t_selecter *selecter)
{
	t_arg	*current_arg;

	if (selecter->freeze)
		return (0);
	current_arg = selecter->current_arg;
	while (current_arg->next != selecter->current_arg)
		current_arg = current_arg->next;
	selecter->current_arg = current_arg;
	return (0);
}

int		manage_space(t_selecter *selecter)
{
	if (selecter->freeze)
		return (0);
	if (selecter->current_arg->selected == 1)
		selecter->current_arg->selected = 0;
	else
		selecter->current_arg->selected = 1;
	selecter->current_arg = selecter->current_arg->next;
	return (0);
}

int		manage_delete(t_selecter *selecter)
{
	t_arg	*arg;
	t_arg	*tmp;

	if (selecter->freeze)
		return (0);
	if (selecter->current_arg == selecter->current_arg->next)
	{
		free_arg(&(selecter->current_arg));
		selecter->first_arg = NULL;
		return (0);
	}
	if (selecter->current_arg == selecter->first_arg)
		selecter->first_arg = selecter->first_arg->next;
	arg = selecter->first_arg;
	while (arg->next != selecter->current_arg)
		arg = arg->next;
	tmp = arg->next;
	arg->next = tmp->next;
	selecter->current_arg = arg->next;
	free_arg(&tmp);
	selecter->nb_args -= 1;
	give_max_len(selecter);
	return (0);
}

int		manage_backspace(t_selecter *selecter)
{
	return (manage_delete(selecter));
}
