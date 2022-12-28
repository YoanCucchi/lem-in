/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:16:40 by ycucchi           #+#    #+#             */
/*   Updated: 2022/11/22 14:16:42 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	nb_links(t_data *data) //give all links end included
{
	int	i;
	int	j;
	int	links;

	i = -1;
	j = -1;
	links = 0;
	while (++i < data->nb_rooms - 1)
	{
		data->rooms[i].links = 0;
		j = -1;
		links = 0;
		while (++j < data->nb_rooms)
		{
			if (data->tab[i][j])
				links++;
		}
		ft_printf("data->tab[%d]", i);
		ft_printf(" = %d\n", links);
		data->rooms[i].links = links;
	}
}

int	solver(t_data *data, int i)
{
	if (i)
		nb_links(data);
	ft_printf("data->visited.links = %d\n", data->rooms[0].visited);
	ft_printf("data->visited.links = %d\n", data->rooms[0].links);
	// je connais le nombre de lien de chaque salle
	// si start à + d'un lien valide go
	return (1);
}
