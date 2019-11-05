/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:42:17 by rkirszba          #+#    #+#             */
/*   Updated: 2019/06/19 12:11:42 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		is_right_arrow(char *buff)
{
	static char	*arrow = NULL;

	if (!arrow)
	{
		arrow = tgetstr("kr", NULL);
		arrow[1] = 91;
	}
	if (!ft_strcmp((const char*)arrow, (const char*)buff))
		return (1);
	return (0);
}

int		is_left_arrow(char *buff)
{
	static char	*arrow = NULL;

	if (!arrow)
	{
		arrow = tgetstr("kl", NULL);
		arrow[1] = 91;
	}
	if (!ft_strcmp((const char*)arrow, (const char*)buff))
		return (1);
	return (0);
}

int		is_space(char *buff)
{
	if (!ft_strcmp((const char*)" ", (const char*)buff))
		return (1);
	return (0);
}

int		is_delete(char *buff)
{
	static char	*delete = NULL;

	if (!delete)
	{
		delete = tgetstr("kD", NULL);
		delete[1] = 91;
	}
	if (!ft_strcmp((const char*)delete, (const char*)buff)\
		|| !ft_strcmp((const char*)("\x7f\0"), (const char*)buff))
		return (1);
	return (0);
}

int		is_backspace(char *buff)
{
	static char	*backspace = "\x08\0";

	if (!ft_strcmp((const char*)backspace, (const char*)buff))
		return (1);
	return (0);
}
