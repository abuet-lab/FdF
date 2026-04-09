/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:42:31 by antoinebuet       #+#    #+#             */
/*   Updated: 2026/04/09 10:27:13 by antoinebuet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "struct.h"

static void	put_pixel_bgra(t_mlx *mlx, int x, int y, unsigned int color_bgra)
{
	if (x < 0 || (x >= WITH) || y < 0 || y >= HEIGHT)
		return ;
	*(unsigned int *)(mlx->data + y * mlx->line_len + x * 4) = color_bgra;
}

void	draw_line(t_mlx *mlx, int x1, int y1, int x2, int y2, unsigned int col)
{
	t_drawline	t;

    t.delta_x = (float)(x2 - x1);
    t.delta_y = (float)(y2 - y1);
    if (fabs(t.delta_x) >= fabs(t.delta_y))
        t.steps = fabs(t.delta_x);
    else
        t.steps = fabs(t.delta_y);
    if (t.steps == 0)
    {
        put_pixel_bgra(mlx, x1, y1, col);
        return ;
    }
    t.inc_x = t.delta_x / t.steps;
    t.inc_y = t.delta_y / t.steps;
    t.x = (float)x1;
    t.y = (float)y1;
    t.i = 0;
    while (t.i <= (int)t.steps)
    {
        put_pixel_bgra(mlx, (int)roundf(t.x), (int)roundf(t.y), col);
        t.x += t.inc_x;
        t.y += t.inc_y;
        t.i++;
    }
}

static	t_point translate_iso(t_point t, t_sizetab *a)
{
	t_point	point;

	point.x = (t.y - t.x) * cos(a->angle * M_PI / 180.0) + 
		(((a->colone + a->line) * a->size_square * 0.866) / 2) + a->x;
	point.y = (t.y + t.x) * sin(a->angle * M_PI / 180.0) - t.z + 200;
	point.color = t.color;
	return (point);
}

t_point	dynamic_size(int x, int y, long ***map, t_sizetab *sizetab)
{
	t_point	point;

	point.color = map[x][y][1];
	if (sizetab->size_square == 0)
	{
		if (sizetab->line > sizetab->colone)
			sizetab->size_square = WITH / (sizetab->line * 2);
		else 
			sizetab->size_square = HEIGHT / (sizetab->colone * 2);
		if (sizetab->size_square == 0)
			sizetab->size_square = 1;
	}
	point.x = x * sizetab->size_square;
	point.y = y * sizetab->size_square;
	if (sizetab->max_z == sizetab->min_z)
		point.z = 0;
	else 
		point.z = map[x][y][0] * (150 / (sizetab->max_z - sizetab->min_z));
	return (point);
}

void	upgrade_square(t_square *square, int up_x, int up_y)
{

	square->s1.x += up_x;
	square->s2.x += up_x;
	square->s3.x += up_x;
	square->s4.x += up_x;
	square->s1.y += up_y;
	square->s2.y += up_y;
	square->s3.y += up_y;
	square->s4.y += up_y;
}

void	draw_square(t_mlx *mlx, t_square *s)
{
	draw_line(mlx, s->s1.x, s->s1.y, s->s2.x, s->s2.y, s->s1.color);
	draw_line(mlx, s->s2.x, s->s2.y, s->s4.x, s->s4.y, s->s2.color);
	draw_line(mlx, s->s3.x, s->s3.y, s->s4.x, s->s4.y, s->s4.color);
	draw_line(mlx, s->s1.x, s->s1.y, s->s3.x, s->s3.y, s->s1.color);
}

void	draw_landscape(t_mlx *mlx, long ***map, t_sizetab *sizetab)
{
	int			x;
	int			y;
	t_square	square;
	
	x = 0;
	while (x < sizetab->line - 1)
	{
		y = 0;
		while (y < sizetab->colone - 1)
		{
			square.s1 = translate_iso(dynamic_size(x, y, map, sizetab), 
									sizetab); 
			square.s2 = translate_iso(dynamic_size(x + 1, y, map, sizetab),
									sizetab);
			square.s3 = translate_iso(dynamic_size(x , y + 1, map, sizetab),
									sizetab);
			square.s4 = translate_iso(dynamic_size(x + 1, y + 1, map, sizetab),
									sizetab);
			draw_square(mlx, &square);
			y++;
		}
		x++;
	}
}

int	handle_close(void *param)
{
	t_data	*d;
	int		i;

	d = (t_data *)param;
	i = 0;
	mlx_destroy_image(d->mlx.mlx, d->mlx.img);
	mlx_destroy_window(d->mlx.mlx, d->mlx.win);
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
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0 ,0);
}
int	handle_key(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	if (keycode == KEY_ESC)
		handle_close(data);
	else if (keycode == KEY_UP|| keycode == KEY_DOWN)
		zoom(keycode, data);
	else if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		translate(keycode, data);
	else if (keycode == KEY_W || keycode == KEY_S)
		rotate(keycode, data);
    return (0);
}

int	handle_expose(void *param)
{
    t_data *d;

    d = (t_data *)param;
    mlx_put_image_to_window(d->mlx.mlx, d->mlx.win, d->mlx.img, 0, 0);
    return (0);
}

int	main(int argc, char **argv)
{
	t_data	d;

	d.sizetab.size_square = 0;
	d.sizetab.x = 0;
	d.sizetab.y = 0;
	d.sizetab.angle = 30;
	if (argc != 2)
		return (0);
	d.map = parse_map(argv[1], &d.sizetab);
	if (!d.map)
		return (0);
	d.mlx.mlx = mlx_init();
	d.mlx.win = mlx_new_window(d.mlx.mlx, WITH, HEIGHT, "Test");
	d.mlx.img = mlx_new_image(d.mlx.mlx, WITH, HEIGHT);
	d.mlx.data = mlx_get_data_addr(d.mlx.img, &d.mlx.bpp, &d.mlx.line_len,
									&d.mlx.endian);
	draw_landscape(&d.mlx, d.map, &d.sizetab);
	mlx_put_image_to_window(d.mlx.mlx, d.mlx.win, d.mlx.img, 0, 0);
	mlx_do_key_autorepeatoff(d.mlx.mlx);
	mlx_key_hook(d.mlx.win, handle_key, &d);
	mlx_hook(d.mlx.win, 17, 0, handle_close, &d);
	mlx_hook(d.mlx.win, 12, 1L<<15, handle_expose, &d);
	mlx_loop(d.mlx.mlx);
}

