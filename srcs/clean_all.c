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

int	clean_all(t_data *data, t_room *room)
{
	if (data->start)
	{
		ft_printf("free data->start\n");
		free(data->start);
	}
	if (data->end)
	{
		ft_printf("free data->end\n");
		free(data->end);
	}
	if (room->name)
	{
		ft_printf("free room->name\n");
		free(room->name);
	}
	if (data)
	{
		ft_printf("free data\n");
		free(data);
	}
	if (room)
	{
		ft_printf("free room\n");
		free(room);
	}
	return (TRUE);
}
