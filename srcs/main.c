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

static void	print_info(t_data *data)
{
	int		i;

	i = -1;
	ft_printf("------------------------------------------------------------\n");
	ft_printf("ants = [%s]\n", data->ants_str);
	ft_printf("------------------------------------------------------------\n");
	ft_printf("data->start = [%s]\n", data->start);
	ft_printf("------------------------------------------------------------\n");
	ft_printf("data->end = [%s]\n", data->end);
	ft_printf("------------------------------------------------------------\n");
	ft_printf("data->rooms_list = %s\n", data->rooms_list);
	ft_printf("------------------------------------------------------------\n");
	ft_printf("data->links = %s\n", data->links);
	ft_printf("------------------------------------------------------------\n");
	while (++i < data->nb_rooms)
	{
		ft_printf("data->rooms[%d] = ", i);
		ft_printf("[%s]\n", data->rooms[i]);
	}
	ft_printf("------------------------------------------------------------\n");
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 1 || !ft_strcmp(argv[0], "lem-in"))
		return (ft_printf("wtf\n"), FALSE);
	data = struct_init();
	map_reader(data);
	make_rooms_array(data);
	print_info(data);
	clean_all(data, 0);
	system("leaks lem-in > leaks.txt");
	return (TRUE);
}
