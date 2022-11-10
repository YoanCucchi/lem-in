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
	int		j;
	char	**trim;

	i = -1;
	j = -1;
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
	i = -1;
	ft_printf(" \x1B[36mindex\x1B[37m |           ");
	while (++i < data->nb_rooms)
	{
		ft_printf("| \x1B[36m%d\x1B[37m | ", i);
	}
	ft_printf("\n");
	ft_printf("       |-----------|----------------------                  \n");
	i = -1;
	ft_printf("       | \x1B[33mroom_name \x1B[0m");
	while (++i < data->nb_rooms)
	{
		ft_printf("|\x1B[33m %s \x1B[0m| ", data->rooms[i]);
	}
	ft_printf("\n");
	ft_printf("       |           |----------------------                  \n");
	i = -1;
	while (data->tab[++i] && i < data->nb_rooms)
	{
		j = -1;
		ft_printf("   \x1B[36m%d\x1B[37m   |   ", i);
		ft_printf("  \x1B[33m%s\x1B[0m     ", data->rooms[i]);
		while (++j < data->nb_rooms)
		{
			if (data->tab[i][j] == 1)
				ft_printf("| \x1B[31m%d \x1B[0m|", data->tab[i][j]);
			else
				ft_printf("| %d |", data->tab[i][j]);
			ft_putchar(' ');
		}
		ft_putendl(" ");
	}
	ft_printf("------------------------------------------------------------\n");
	i = -1;
	trim = ft_strsplit(data->links, '\n');
	ft_printf(" \x1B[32mlink list\x1B[0m |");
	while (trim[++i])
	{
		ft_printf(" \x1B[32m[%s]\x1B[0m |", trim[i]);
		free(trim[i]);
	}
	free(trim);
	ft_printf("\n");
	ft_printf("------------------------------------------------------------\n");
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	// Any non compliant or empty lines will automatically stop the ant 
	// farm’s reading as well as the orderly processing of the acquired data.
	if (argc != 1 || !ft_strcmp(argv[0], "lem-in"))
		clean_all(data, 1);
	data = struct_init(data);
	map_reader(data);
	make_rooms_array(data);
	tab_array(data);
	print_info(data);
	clean_all(data, 0);
	system("leaks lem-in > leaks.txt");
	return (0);
}
