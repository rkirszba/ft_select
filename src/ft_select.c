/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:36:50 by rkirszba          #+#    #+#             */
/*   Updated: 2019/11/07 15:19:17 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_selecter	*g_selecter = NULL;

int			set_term_mode(t_selecter *selecter, int i)
{
	struct termios	term_conf;
	struct termios	term_conf_backup;

	if (!i)
	{
		if ((tcgetattr(0, &term_conf)) || tcgetattr(0, &term_conf_backup))
			return (print_noattr_error());
		term_conf.c_lflag &= ~(ICANON);
		term_conf.c_lflag &= ~(ECHO);
		term_conf.c_cc[VMIN] = 1;
		term_conf.c_cc[VTIME] = 0;
		if (tcsetattr(0, TCSADRAIN, &term_conf))
			return (print_noattr_error());
		selecter->term_conf = term_conf;
		selecter->term_conf_backup = term_conf_backup;
		tputs(tgetstr("ti", NULL), 1, &outc);
		tputs(selecter->cmds.hide_curs, 1, &outc);
		return (0);
	}
	tputs(tgetstr("te", NULL), 1, &outc);
	tputs(selecter->cmds.rst_curs, 1, &outc);
	if (tcsetattr(0, TCSADRAIN, &(selecter->term_conf_backup)))
		return (print_noattr_error());
	return (0);
}

static int	check_void_args(int ac, char **av)
{
	int		current;

	current = 0;
	while (++current < ac)
	{
		if (av[current][0])
			return (0);
	}
	return (1);
}

static int	input_manager(t_selecter *selecter, t_cmd_fun *cmd_tab)
{
	int	i;
	int	ret;

	ft_bzero(selecter->buff, sizeof(char) * 6);
	read(0, selecter->buff, 6);
	ret = 0;
	i = -1;
	while (++i < 7)
		if ((cmd_tab[i].check(selecter->buff)))
		{
			ret = cmd_tab[i].manager(selecter);
			break ;
		}
	return (ret);
}

static int	ft_select(t_selecter *selecter)
{
	t_cmd_fun	cmd_tab[7];
	int			ret;
	int			ret2;

	g_selecter = selecter;
	tputs(selecter->cmds.hide_curs, 1, &outc);
	ft_bzero(cmd_tab, sizeof(t_cmd_fun) * 7);
	init_cmd_tab(cmd_tab);
	signals_manager();
	ret2 = 0;
	while (42)
	{
		tputs(tgoto((const char*)selecter->cmds.mv_curs, 0, 0), 1, &outc);
		ret = 0;
		write_args(selecter);
		if ((ret = input_manager(selecter, cmd_tab)) || !selecter->first_arg)
			break ;
	}
	tputs(selecter->cmds.clear, 1, &outc);
	del_lines(selecter);
	ret2 = set_term_mode(selecter, 1);
	del_lines(selecter);
	if (!ret2 && ret == 1 && selecter->first_arg)
		write_final_args(selecter);
	return (!ret2 && g_sig != -1 ? 0 : -1);
}

int			main(int ac, char **av)
{
	int			i;
	int			ret;
	t_selecter	*selecter;
	t_arg		*arg;

	if (ac == 1 || check_void_args(ac, av))
		return (print_usage());
	if (!(selecter = init_selecter(ac - 1)))
		return (1);
	i = 0;
	while (++i < ac)
	{
		if (!(arg = create_argument(av[i])))
		{
			free_manager(selecter);
			return (print_sys_error());
		}
		append_argument(selecter, arg);
	}
	if (!(ret = set_term_mode(selecter, 0)))
		ret = ft_select(selecter);
	free_manager(selecter);
	return (ret);
}
