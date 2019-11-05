/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 10:56:31 by rkirszba          #+#    #+#             */
/*   Updated: 2019/06/26 20:14:03 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	init_cmds(t_cmds *cmds)
{
	char	*termtype;
	int		ret;

	if (!(termtype = getenv("TERM")))
		return (print_noenv_error());
	ret = tgetent(NULL, termtype);
	if (ret == -1)
		return (print_noaccess_error());
	if (ret == 0)
		return (print_notdefined_error());
	if (!(cmds->clear = tgetstr("cl", NULL))\
		|| !(cmds->underline = tgetstr("us", NULL))\
		|| !(cmds->reverse = tgetstr("mr", NULL))\
		|| !(cmds->mv_curs = tgetstr("cm", NULL))\
		|| !(cmds->hide_curs = tgetstr("vi", NULL))\
		|| !(cmds->rst_curs = tgetstr("ve", NULL))\
		|| !(cmds->reset = tgetstr("me", NULL))\
		|| !(cmds->color = tgetstr("AF", NULL))\
		|| !(cmds->bg_color = tgetstr("AB", NULL))\
		|| !(cmds->bold = tgetstr("md", NULL)))
		return (print_cmd_error());
	return (0);
}

t_selecter	*init_selecter(int nb_args)
{
	t_selecter	*selecter;

	if (!(selecter = (t_selecter*)malloc(sizeof(t_selecter))))
	{
		print_sys_error();
		return (NULL);
	}
	ft_bzero(selecter->buff, sizeof(char) * 6);
	selecter->first_arg = NULL;
	selecter->current_arg = NULL;
	selecter->nb_args = nb_args;
	ioctl(0, TIOCGWINSZ, &(selecter->termsize));
	selecter->max_len = 0;
	selecter->freeze = 0;
	if ((init_cmds(&(selecter->cmds))))
		ft_memdel((void**)(&selecter));
	return (selecter);
}

void		init_cmd_tab(t_cmd_fun *cmd_tab)
{
	cmd_tab[0].check = &is_right_arrow;
	cmd_tab[0].manager = &manage_right_arrow;
	cmd_tab[1].check = &is_left_arrow;
	cmd_tab[1].manager = &manage_left_arrow;
	cmd_tab[2].check = &is_space;
	cmd_tab[2].manager = &manage_space;
	cmd_tab[3].check = &is_return;
	cmd_tab[3].manager = &manage_return;
	cmd_tab[4].check = &is_escape;
	cmd_tab[4].manager = &manage_escape;
	cmd_tab[5].check = &is_delete;
	cmd_tab[5].manager = &manage_delete;
	cmd_tab[6].check = &is_backspace;
	cmd_tab[6].manager = &manage_backspace;
}
