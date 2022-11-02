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
	ft_printf("ants are [%d]\n", data->ants);
	ft_printf("start is [%s]\n", data->start);
	ft_printf("end is [%s]\n", data->end);
	clean_all(data, 0);
	system("leaks lem-in > leaks.txt");
	return (TRUE);
}
