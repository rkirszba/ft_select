/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_functions_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:04:03 by rkirszba          #+#    #+#             */
/*   Updated: 2019/06/26 19:48:52 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		manage_return(t_selecter *selecter)
{
	if (selecter->freeze)
		return (0);
	return (1);
}

int		manage_escape(t_selecter *selecter)
{
	(void)selecter;
	return (-1);
}
