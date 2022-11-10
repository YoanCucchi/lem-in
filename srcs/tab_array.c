/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:41:31 by ycucchi           #+#    #+#             */
/*   Updated: 2022/11/09 16:41:33 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	find_index(t_data *data, char *name)
{
	int	index;

	index = -1;
	while (data->rooms[++index] && index < data->nb_rooms)
	{
		if (!ft_strcmp(data->rooms[index], name))
			return (index);
	}
	return (index);
}

void	tab_array(t_data *data)
{
	int		i;
	int		r_1;
	int		r_2;
	char	**l;
	char	**links;

	i = -1;
	links = ft_strsplit(data->links, '\n');
	while (links[++i])
	{
		ft_printf("links[i] = [%s]\n", links[i]);
		// validate_link(data, links[i]);
		l = ft_strsplit(links[i], '-');
		r_1 = find_index(data, l[0]);
		ft_printf("r1 = [%d]\n", r_1);
		r_2 = find_index(data, l[1]);
		ft_printf("r2 = [%d]\n", r_2);
		if (r_2)
			data->tab[r_1][r_2] = 1;
		if (r_1)
			data->tab[r_2][r_1] = 1;
		free_char_array(l);
	}
	free_char_array(links);
}
