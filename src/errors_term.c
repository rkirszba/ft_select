/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_term.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:57:52 by rkirszba          #+#    #+#             */
/*   Updated: 2019/06/26 12:56:42 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		print_noenv_error(void)
{
	ft_putstr_fd("TERM must be set\n", 2);
	return (1);
}

int		print_noaccess_error(void)
{
	ft_putstr_fd("Could not access to the termcaps database\n", 2);
	return (1);
}

int		print_notdefined_error(void)
{
	ft_putstr_fd("Terminal is not defined in termcap database\n", 2);
	return (1);
}

int		print_noattr_error(void)
{
	ft_putstr_fd("Impossible to get or set the attributes\n", 2);
	return (1);
}
