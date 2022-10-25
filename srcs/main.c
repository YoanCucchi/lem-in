/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:16:12 by ycucchi           #+#    #+#             */
/*   Updated: 2022/10/25 15:16:15 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_room	*room;

	data = NULL;
	room = NULL;
	data = (t_data *)malloc(sizeof(t_data));
	room = (t_room *)malloc(sizeof(t_room));
	if (!argv || argc == 4)
	{
		clean_all(data, room);
		return (FALSE);
	}
	ft_bzero(data, sizeof data);
	ft_bzero(room, sizeof room);
	// check map
	// if ok solve
	// if not exit
	// if solved exit
	if (!map_reader(data))
	{
		ft_printf("error\n");
		clean_all(data, room);
	}
	ft_printf("ants are [%d]\n", data->ants);
	ft_printf("start is [%s]\n", data->start);
	ft_printf("end is [%s]\n", data->end);
	clean_all(data, room);
	system("leaks lem-in > leaks.txt");
	return (TRUE);
}
