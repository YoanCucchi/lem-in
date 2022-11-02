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

void	free_array(char **array, t_data *data, int error)
{
	int i;

	i = 0;
	while (array[i])
		(array[i]) ? free(array[i++]) : 0;
	free(array);
	if (error)
		clean_all(data, 1);
	array = NULL;
}

void	clean_all(t_data *data, int error)
{
	int	i;

	free(data->links);
	free(data->ants_str);
	free(data->rooms_list);
	if (data->init_2)
	{
		free(data->path);
		free_array(data->rooms, data, 0);
		i = -1;
		while (++i < data->nb_rooms)
			free(data->tab[i]);
		free(data->tab);
	}
	free(data);
	if (error)
	{
		ft_putstr_fd("ERROR\n", 2);
		exit(1);
	}
	exit(0);
}
