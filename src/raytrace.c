/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:48:25 by yoelguer          #+#    #+#             */
/*   Updated: 2021/03/28 19:12:15 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_ray		init_rayy(t_2d_i cor, t_data_camera *cam)
{
	t_vect	s;
	t_ray	r;
	t_vect	des;

	s = sub_vect(cam->pos, vect_mult_val(cam->dir, cam->dist));
	s = sub_vect(s, vect_mult_val(cam->u_dir, cor.i - (W / 2)));
	s = add_vect(s, vect_mult_val(cam->v_dir, (H / 2) - cor.j));
	r.di = sub_vect(s, cam->pos);
	normalize(&(r.di));
	des = add_vect(cam->pos, vect_mult_val(r.di, cam->focus_dis));
	r.di = norm(sub_vect(des, cam));
	return (r);
}

void			raytracing(t_all	*data)
{
	t_2d_i	cor;
	t_vect	col;
	t_ray	ray;

	cor.i = -1;	
	while (++cor.i <= H)
	{
		cor.j = -1;
		while (++cor.j <= W)
		{	
			init_vect(&col, 0., 0., 0.);
			ray = init_ray(cor,data->camera);
			col = col_pix(data, ray);
		}
	}
	
			// 
			// var.z = -1;
			// while (++var.z < ((data.aalias || data.deep) ? NBR_RAYS : 1))
			// {
			// 	ray = new_ray(var.x, var.y, data);
			// 	col = add_vect(col, vect_mult_val(rend_pix(data, ray, 6), 1. /
			// 		((data.aalias || data.deep) ? NBR_RAYS : 1)));
			// }
			// set_pixel(data, col, var, ray);

	//filtre(&data);
}
