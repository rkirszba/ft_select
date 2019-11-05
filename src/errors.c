/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 11:39:29 by rkirszba          #+#    #+#             */
/*   Updated: 2019/06/26 12:53:16 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		print_usage(void)
{
	ft_putstr_fd("Usage : ./ft_select [non void argument ...]\n", 2);
	return (1);
}

int		print_sys_error(void)
{
	ft_putstr_fd("System error\n", 2);
	return (1);
}

int		print_cmd_error(void)
{
	ft_putstr_fd("Terminal probably obsolete\n", 2);
	return (1);
}
