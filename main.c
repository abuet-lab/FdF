/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuet <abuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:42:31 by antoinebuet       #+#    #+#             */
/*   Updated: 2026/04/09 14:31:56 by abuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "struct.h"

static void	draw_line(t_mlx *mlx, t_draw *l)
{
	t_drawline	t;	

	t.delta_x = (float)(l->x2 - l->x1);
	t.delta_y = (float)(l->y2 - l->y1);
	if (fabs(t.delta_x) >= fabs(t.delta_y))
		t.steps = fabs(t.delta_x);
	else
		t.steps = fabs(t.delta_y);
	if (t.steps == 0)
	{
		put_pixel_bgra(mlx, l->x1, l->y1, l->color);
		return ;
	}
	t.inc_x = t.delta_x / t.steps;
	t.inc_y = t.delta_y / t.steps;
	t.x = (float)l->x1;
	t.y = (float)l->y1;
	t.i = 0;
	while (t.i <= (int)t.steps)
	{
		put_pixel_bgra(mlx, (int)roundf(t.x), (int)roundf(t.y), l->color);
		t.x += t.inc_x;
		t.y += t.inc_y;
		t.i++;
	}
}

static void	draw_square(t_mlx *mlx, t_square *s)
{
	t_draw	draw;

	draw = fill_draw(&s->s1, &s->s2);
	draw_line(mlx, &draw);
	draw = fill_draw(&s->s2, &s->s4);
	draw_line(mlx, &draw);
	draw = fill_draw(&s->s4, &s->s3);
	draw_line(mlx, &draw);
	draw = fill_draw(&s->s3, &s->s1);
	draw_line(mlx, &draw);
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
			square.s3 = translate_iso(dynamic_size(x, y + 1, map, sizetab),
					sizetab);
			square.s4 = translate_iso(dynamic_size(x + 1, y + 1, map, sizetab),
					sizetab);
			draw_square(mlx, &square);
			y++;
		}
		x++;
	}
}

static int	handle_key(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	if (keycode == KEY_ESC)
		handle_close(data);
	else if (keycode == KEY_UP || keycode == KEY_DOWN)
		zoom(keycode, data);
	else if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		translate(keycode, data);
	else if (keycode == KEY_W || keycode == KEY_S)
		rotate(keycode, data);
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
	mlx_hook(d.mlx.win, 12, 1L << 15, handle_expose, &d);
	mlx_loop(d.mlx.mlx);
}
