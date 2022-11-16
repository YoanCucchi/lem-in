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

static void	free_tab_array(t_data *data, int **tab)
{
	int	i;

	i = -1;
	while (++i < data->nb_rooms)
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	tab = NULL;
}

static void	clean_struct(t_data *data)
{
	if (data->links)
		free(data->links);
	if (data->ants_str)
		free(data->ants_str);
	if (data->rooms_list)
		free(data->rooms_list);
	if (data->rooms_list2)
		free(data->rooms_list2);
	if (data->start)
		free(data->start);
	if (data->end)
		free(data->end);
	if (data->path)
		free(data->path);
	if (data->tab)
		free_tab_array(data, data->tab);
	if (data->rooms)
		free_char_array(data->rooms);
	free(data);
}

void	free_char_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

void	clean_all(t_data *data, int error)
{
	if (data)
		clean_struct(data);
	if (error)
	{
		ft_putstr_fd("ERROR\n", 2);
		// exit(1);
	}
	// exit(0);
}
