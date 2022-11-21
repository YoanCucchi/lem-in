/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:16:31 by ycucchi           #+#    #+#             */
/*   Updated: 2022/11/21 15:16:35 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	header(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	ft_printf("\n\n\x1B[36mindex\x1B[37m ");
	while (++i < data->nb_rooms)
	{
		j = i;
		while (ft_nbrlen(j, 10) > 1)
			j %= 10;
		ft_printf(" \x1B[36m%d\x1B[37m", j);
	}
	ft_printf("\t[\x1B[36mindex\x1B[37m] ->  [\x1B[33mroom_name\x1B[37m]\n");
	ft_printf("\n");
}

static void	print_help(int i, int nbr)
{
	if (nbr == 1)
	{
		if (ft_nbrlen(i, 10) == 1)
			ft_printf("  \x1B[36m%d\x1B[37m    ", i);
		else if (ft_nbrlen(i, 10) == 2)
			ft_printf(" \x1B[36m%d\x1B[37m    ", i);
		else
			ft_printf("\x1B[36m%d\x1B[37m    ", i);
	}
	else if (nbr == 2)
	{
		if (ft_nbrlen(i, 10) == 1)
			ft_printf("\t[\x1B[36m%d\x1B[37m]     ->  ", i);
		else if (ft_nbrlen(i, 10) == 2)
			ft_printf("\t[\x1B[36m%d\x1B[37m]    ->  ", i);
		else
			ft_printf("\t[\x1B[36m%d\x1B[37m]   ->  ", i);
	}
}

void	print_matrix(t_data *data)
{
	int	i;
	int	j;

	header(data);
	i = -1;
	while (++i < data->nb_rooms)
	{
		print_help(i, 1);
		j = -1;
		while (++j < data->nb_rooms)
		{
			if (data->tab[i][j] == 1)
				ft_printf("X ");
			else
				ft_printf("- ");
		}
		print_help(i, 2);
		ft_printf("[\x1B[33m%s\x1B[37m]\n", data->rooms[i]);
	}
	ft_printf("\n\n");
}
