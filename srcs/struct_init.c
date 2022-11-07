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

t_data	*struct_init(void)
{
	t_data	*data;

	data = NULL;
	data = (t_data *)ft_memalloc(sizeof(t_data));
	data->links = ft_strnew(1);
	data->ants_str = ft_strnew(1);
	data->rooms_list = ft_strnew(1);
	data->start = ft_strnew(1);
	data->end = ft_strnew(1);
	data->nb_rooms = 0;
	data->ants = 0;
	data->dispatch = 0;
	data->curr_room = 0;
	data->p_ind = 0;
	data->init_2 = 0;
	data->rooms = NULL;
	data->tab = NULL;
	data->path = NULL;
	return (data);
}
