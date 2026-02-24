/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:42:31 by antoinebuet       #+#    #+#             */
/*   Updated: 2026/02/24 14:14:13 by antoinebuet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(void)
{
	void *mlx;

	mlx = mlx_init();
	mlx_new_window(mlx, 800, 800, "fdf");
	mlx_loop(mlx);
	return (0);
}