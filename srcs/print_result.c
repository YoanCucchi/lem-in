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

// static void	print_ant(int ant, char *room)
// {
// 	ft_putchar('L');
// 	ft_putnbr(ant);
// 	ft_putchar('-');
// 	ft_putstr(room);
// 	ft_putchar(' ');
// }

// static void	print_result(t_data *data, int n)
// {
// 	int ants;
// 	int	j;
// 	int	i;

// 	i = 0;
// 	j = 1;
// 	if (n == (data->p_ind + data->ants + 1))
// 		return ;
// 	ants = data->ants + 1;
// 	while (--ants > 0)
// 	{
// 		ft_printf("blabla = %d\n", data->path[i][j]);
// 		if (n - ants > 0 && (n - ants) <= data->p_ind)
// 			print_ant(ants, data->rooms[i].name);
// 		j++;
// 	}
// 	ft_putchar('\n');
// 	print_result(data, ++n);
// }

void		result(t_data *data)
{
	int i;
	int	j;

	j = 1;
	i = 0;
	ft_printf("%d\n", data->ants);
	ft_printf("%s\n", data->rooms_list); // problem with that one all # not stored
	ft_printf("%s\n", data->links);
	ft_printf("\n");
	while (i <= data->nb_rooms && data->final_path[i][j])
	{
		while (j <= data->nb_rooms && data->final_path[i][j])
		{
				if (j == 1)
					ft_printf("[%s]-", data->rooms[0]);
				ft_printf("[%s]", data->rooms[data->final_path[i][j]].name);
				if (data->final_path[i][++j])
					ft_printf("-");
		}
		i++;
		j = 1;
		ft_printf("\n\n");
	}
	ft_printf("\n");
	// print_result(data, 2);
}
