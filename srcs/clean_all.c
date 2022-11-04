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

static void	free_char_array(t_data *data, char **array)
{
	int	i;

	i = -1;
	while (++i < data->nb_rooms)
		free(array[i]);
	free(array);
}

static void	free_int_array(t_data *data, int **array)
{
	int	i;

	i = -1;
	while (++i < data->nb_rooms)
		free(array[i]);
	free(array);
}

void	clean_all(t_data *data, int error)
{
	free(data->links);
	free(data->ants_str);
	free(data->rooms_list);
	free(data->start);
	free(data->end);
	if (data->init_2)
	{
		free(data->path);
		free_int_array(data, data->tab);
		free_char_array(data, data->rooms);
	}
	free(data);
	if (error)
	{
		ft_putstr_fd("ERROR\n", 2);
		// exit(1);
	}
	// exit(0);
}
