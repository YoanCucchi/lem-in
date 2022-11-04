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

	data = struct_init();
	if (!argv || argc == 4) // change that
		return (FALSE);
	map_reader(data);
	ft_printf("ants str = [%s]\n", data->ants_str);
	ft_printf("links = [%s]\n", data->links);
	ft_printf("rooms list = [%s]\n", data->rooms_list);
	clean_all(data, 0);
	system("leaks lem-in > leaks.txt");
	return (TRUE);
}
