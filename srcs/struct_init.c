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
	data = (t_data *)malloc(sizeof(t_data));
	data->links = ft_strnew(1);
	data->ants_str = ft_strnew(1);
	data->rooms_list = ft_strnew(1);
	ft_bzero(data, sizeof data);
	return (data);
}
