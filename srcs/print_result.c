/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:46:44 by ycucchi           #+#    #+#             */
/*   Updated: 2022/11/23 13:46:47 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_ant(int ant, char *room)
{
	ft_putchar('L');
	ft_putnbr(ant);
	ft_putchar('-');
	ft_putstr(room);
	ft_putchar(' ');
}

static void	print_result(t_data *data, int n)
{
	int ants;

	if (n == (data->p_ind + data->ants + 1))
		return ;
	ants = data->ants + 1;
	while (--ants > 0)
	{
		if (n - ants > 0 && (n - ants) <= data->p_ind)
			print_ant(ants, data->rooms[data->path[n - ants]].name);
	}
	ft_putchar('\n');
	print_result(data, ++n);
}

void	result(t_data *data)
{
	int i;

	i = -1;
	ft_printf("%d\n", data->ants);
	ft_putendl(data->rooms_list); // problem with that one all # not stored
	ft_putendl(data->links);
	ft_putchar('\n');
	while (++i <= data->p_ind)
	{
		ft_putchar('[');
		ft_printf("%s", data->rooms[data->path[i]].name);
		ft_putchar(']');
		if (i != data->p_ind)
			ft_putchar('-');
	}
	ft_putstr("\n\n");
	print_result(data, 2);
}
