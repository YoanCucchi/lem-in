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
	find_path(data);

	ft_printf("--------------------------------------------------\n");
	ft_printf("final\n");
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->final_path[0][0] = %d\n", data->final_path[0][0]);
	ft_printf("data->final_path[0][1] = %d\n", data->final_path[0][1]);
	ft_printf("data->final_path[0][2] = %d\n", data->final_path[0][2]);
	ft_printf("data->final_path[0][3] = %d\n", data->final_path[0][3]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->final_path[1][0] = %d\n", data->final_path[1][0]);
	ft_printf("data->final_path[1][1] = %d\n", data->final_path[1][1]);
	ft_printf("data->final_path[1][2] = %d\n", data->final_path[1][2]);
	ft_printf("data->final_path[1][3] = %d\n", data->final_path[1][3]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->final_path[2][0] = %d\n", data->final_path[2][0]);
	ft_printf("data->final_path[2][1] = %d\n", data->final_path[2][1]);
	ft_printf("data->final_path[2][2] = %d\n", data->final_path[2][2]);
	ft_printf("data->final_path[2][3] = %d\n", data->final_path[2][3]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->final_path[3][0] = %d\n", data->final_path[3][0]);
	ft_printf("data->final_path[3][1] = %d\n", data->final_path[3][1]);
	ft_printf("data->final_path[3][2] = %d\n", data->final_path[3][2]);
	ft_printf("data->final_path[3][3] = %d\n", data->final_path[3][3]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->final_path[4][0] = %d\n", data->final_path[4][0]);
	ft_printf("data->final_path[4][1] = %d\n", data->final_path[4][1]);
	ft_printf("data->final_path[4][2] = %d\n", data->final_path[4][2]);
	ft_printf("data->final_path[4][3] = %d\n", data->final_path[4][3]);
	ft_printf("--------------------------------------------------\n");
	clean_all(data, 0);
	system("leaks lem-in > leaks.txt");
	return (0);
}
