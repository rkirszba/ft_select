/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_char_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:06:13 by rkirszba          #+#    #+#             */
/*   Updated: 2019/06/19 12:07:08 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		is_return(char *buff)
{
	if (!ft_strcmp((const char*)"\n", (const char*)buff))
		return (1);
	return (0);
}

int		is_escape(char *buff)
{
	static char	*escape = "\x1b\0";

	if (!ft_strcmp((const char*)escape, (const char*)buff))
		return (1);
	return (0);
}
