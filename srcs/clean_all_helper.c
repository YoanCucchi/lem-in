/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:36:33 by ycucchi           #+#    #+#             */
/*   Updated: 2022/10/25 17:36:35 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_tab_array(t_data *data, int **tab)
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

void	clean_line_all(t_data *data, char *line)
{
	if (line)
		ft_strdel(&line);
	clean_all(data, 1);
}

void	free_char_array(t_data *data, char **array, int leave)
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
	if (leave)
		clean_all(data, 1);
}
