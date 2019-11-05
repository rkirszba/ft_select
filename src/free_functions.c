/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:26:22 by rkirszba          #+#    #+#             */
/*   Updated: 2019/06/26 11:36:26 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	free_arg(t_arg **arg)
{
	ft_strdel(&((*arg)->str));
	free(*arg);
	*arg = NULL;
}

void	free_manager(t_selecter *selecter)
{
	t_arg	*current;
	t_arg	*tmp;

	if (!(selecter->first_arg))
	{
		free(selecter);
		return ;
	}
	if (selecter->first_arg == selecter->first_arg->next)
	{
		free_arg(&(selecter->first_arg));
		free(selecter);
		return ;
	}
	current = selecter->first_arg->next;
	selecter->first_arg->next = NULL;
	while (current)
	{
		tmp = current;
		current = current->next;
		free_arg(&tmp);
	}
	free(selecter);
}
