/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:14:04 by abuet             #+#    #+#             */
/*   Updated: 2026/04/09 14:45:05 by antoinebuet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_close(void *param)
{
	t_data	*d;
	int		i;

	d = (t_data *)param;
	i = 0;
	mlx_destroy_image(d->mlx.mlx, d->mlx.img);
	mlx_destroy_window(d->mlx.mlx, d->mlx.win);
	mlx_destroy_display(d->mlx.mlx);
	free(d->mlx.mlx);
	while (i < d->sizetab.line)
	{
		free(d->map[i][0]);
		free(d->map[i]);
		i++;
	}
	free(d->map);
	exit(0);
}

void	zoom(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
		data->sizetab.size_square += 1;
	if (keycode == KEY_DOWN)
		data->sizetab.size_square -= 1;
	mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	data->mlx.img = mlx_new_image(data->mlx.mlx, WITH, HEIGHT);
	data->mlx.data = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.line_len, &data->mlx.endian);
	draw_landscape(&data->mlx, data->map, &data->sizetab);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

void	translate(int keycode, t_data *data)
{
	mlx_clear_window(data->mlx.mlx, data->mlx.win);
	if (keycode == KEY_RIGHT)
		data->sizetab.x += 5;
	else
		data->sizetab.x -= 5;
	mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	data->mlx.img = mlx_new_image(data->mlx.mlx, WITH, HEIGHT);
	data->mlx.data = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.line_len, &data->mlx.endian);
	draw_landscape(&data->mlx, data->map, &data->sizetab);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

void	rotate(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->sizetab.angle += 1;
	else
		data->sizetab.angle -= 1;
	mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	data->mlx.img = mlx_new_image(data->mlx.mlx, WITH, HEIGHT);
	data->mlx.data = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.line_len, &data->mlx.endian);
	draw_landscape(&data->mlx, data->map, &data->sizetab);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

int	handle_expose(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	mlx_put_image_to_window(d->mlx.mlx, d->mlx.win, d->mlx.img, 0, 0);
	return (0);
}
