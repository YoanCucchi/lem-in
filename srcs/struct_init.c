/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:09:04 by ycucchi           #+#    #+#             */
/*   Updated: 2022/11/02 16:09:10 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_data	*struct_init_2(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	data->init_2 = 1; // Check those malloc for the size
	data->rooms = (t_rooms *)ft_memalloc(sizeof(t_data) * data->nb_rooms);
	data->final_path = (int **)ft_memalloc(sizeof(int *) * (data->nb_rooms * 1000));
	data->tab = (int **)ft_memalloc(sizeof(int *) * (data->nb_rooms * 1000));
	if ( !data->tab || !data->rooms || !data->final_path)
		clean_all(data, 1);
	while (++i < data->nb_rooms)
	{
		data->final_path[i] = (int *)ft_memalloc(sizeof(int) * 10000);
		data->tab[i] = (int *)ft_memalloc(sizeof(int) * 1000);
		if (!data->tab[i])
			clean_all(data, 1);
		j = -1;
		while (data->tab[i][++j])
			data->tab[i][j] = 0;
		j = -1;
	}
	data->final_path[i] = 0;
	data->path_j = 1;
	return (data);
}

t_data	*struct_init(t_data *data)
{
	data = (t_data *)ft_memalloc(sizeof(t_data));
	if (!data)
		clean_all(data, 1);
	ft_bzero(data, sizeof (t_data));
	data->links = ft_strnew(data->nb_rooms * 10000);
	data->rooms_list = ft_strnew(data->nb_rooms * 10000);
	data->rooms_trim = ft_strnew(data->nb_rooms * 50000);
	data->start = ft_strnew(10000);
	data->end = ft_strnew(10000);
	data->trim_start = ft_strnew(10000);
	data->trim_end = ft_strnew(10000);
	if (!data->links || !data->rooms_list || !data->start || !data->end || \
	!data->trim_start || !data->trim_end || !data->rooms_trim)
		clean_all(data, 1);
	return (data);
}
