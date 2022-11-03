/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:36:33 by ycucchi           #+#    #+#             */
/*   Updated: 2022/10/25 17:36:35 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clean_all(t_data *data, int error)
{
	int	i;

	free(data->links);
	free(data->ants_str);
	free(data->rooms_list);
	if (data->init_2)
	{
		free(data->path);
		i = -1;
		while (++i < data->nb_rooms)
			free(data->tab[i]);
		free(data->tab);
		i = -1;
		while (++i < data->nb_rooms)
			free(data->rooms[i]);
		free(data->rooms);
	}
	free(data);
	if (error)
	{
		ft_putstr_fd("ERROR\n", 2);
		// exit(1);
	}
	// exit(0);
}
