/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:33:57 by ycucchi           #+#    #+#             */
/*   Updated: 2022/11/04 18:33:59 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	is_number(char **array, char *str, t_data *data)
{
	int	i;

	i = 0;
	if (str[0] == '-' || ft_isdigit(str[0]))
	{
		while (str[++i])
		{
			if (!ft_isdigit(str[i]))
				free_char_array(data, array, 1);
		}
	}
	else
		free_char_array(data, array, 1);
}

int	is_empty(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

void	copy_map(t_data *data, char *line)
{
	char	*line_copy;
	int		len;

	line_copy = NULL;
	line_copy = (char *)malloc(sizeof(char) * 500); // correct size to be found
	len = 0;
	if (is_empty(line))
		clean_all(data, 1);
	line_copy = ft_strcpy(line_copy, line);
	line_copy = ft_strcat(line_copy, "\n");
	if (data->map)
		len = ft_strlen(line_copy) + ft_strlen(data->map) + 1;
	free(data->map);
	data->map = (char *)malloc(sizeof(char) * len);
	if (!data->map)
		clean_all(data, 1);
	data->map = ft_strcat(data->map, line_copy);
	free(line_copy);
}

void	clean_line_array_all(t_data *data, char *s, char *line)
{
	if (s)
		ft_strdel(&s);
	if (line)
		ft_strdel(&line);
	clean_all(data, 1);
}

void	validate_room(t_data *data, char *line)
{
	char	**array;

	array = ft_strsplit(line, ' ');
	if (array[0][0] == 'L' || array[3] != NULL)
		free_char_array(data, array, 1);
	is_number(array, array[1], data);
	is_number(array, array[2], data);
	free_char_array(data, array, 0);
}
