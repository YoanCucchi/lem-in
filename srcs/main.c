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

void	print_final_path(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_printf("============================================================\n");
	while (i < data->path_counter)
	{
		j = 1;
		ft_printf("data->final_path[%d][0] =", i);
		ft_printf(" %d", data->final_path[i][0]);
		ft_printf(" ==> name : %s\n", data->rooms[0].name);
		while (data->final_path[i][j] != 0)
		{
			ft_printf("data->final_path[%d]", i);
			ft_printf("[%d]", j);
			ft_printf(" = %d", data->final_path[i][j]);
			ft_printf(" ==> name : %s\n", data->rooms[data->final_path[i][j]].name);
			j++;
		}
		ft_printf("--------------------------------------------------------\n");
		i++;
	}
	ft_printf("============================================================\n");
}

void	print_path(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_printf("============================================================\n");
	while (i < 2 || (i > 2 && data->path[i][j] >= 1))
	{
		j = 0;
		while (j < data->nb_rooms || (j > 2 && data->path[i][j] >= 1))
		{
			ft_printf("data->path[%d]", i);
			ft_printf("[%d]", j);
			ft_printf(" = %d\n", data->path[i][j]);
			j++;
		}
		ft_printf("--------------------------------------------------------\n");
		i++;
	}
	ft_printf("============================================================\n");
}

static void	free_map_array(t_data *data)
{
	int	i;

	i = -1;
	while (data->rooms[++i].name)
	{
		ft_strdel(&data->rooms[i].name);
	}
	free(data->rooms);
}

static void	clean_struct(t_data *data)
{
	if (data->trim_start)
		free(data->trim_start);
	if (data->trim_end)
		free(data->trim_end);
	if (data->links)
		free(data->links);
	if (data->rooms_list)
		free(data->rooms_list);
	if (data->rooms_trim)
		free(data->rooms_trim);
	if (data->start)
		free(data->start);
	if (data->end)
		free(data->end);
	if (data->path)
		free_tab_array(data, data->path);
	if (data->final_path)
		free_tab_array(data, data->final_path);
	if (data->map)
		free(data->map);
	if (data->rooms)
		free_map_array(data);
	if (data->tab)
		free_tab_array(data, data->tab);
	free(data);
}

void	clean_all(t_data *data, int error)
{
	if (data)
		clean_struct(data);
	if (error)
	{
		ft_putstr_fd("ERROR\n", 2);
		exit(1);
	}
	// exit(0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

// maps 42 malloc issue not enough memory probleme is with line
// des fois line = "" sans raison au cours du programme.
	data = NULL;
	if (argc != 1 || !ft_strcmp(argv[0], "lem-in"))
		clean_all(data, 1);
	data = struct_init(data);
	map_reader(data);
	make_rooms_array(data);
	tab_array(data);
	print_matrix(data);
	// solver(data, 1);
	// result(data);
	path_finder(data);
	clean_all(data, 0);
	system("leaks lem-in > leaks.txt");
	return (0);
}
