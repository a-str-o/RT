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
	t_vect	new_cam_pos;
	t_vect var;
t_2d_d alis;
t_2d_d deep;

	s = sub_vect(cam->pos, vect_mult_val(cam->dir, cam->dist));
	s = sub_vect(s, vect_mult_val(cam->u_dir, var.x - (W / 2) + alis.x));
	s = add_vect(s, vect_mult_val(cam->v_dir, (H / 2) - var.y + alis.y));
	r.di = sub_vect(s, cam->pos);
	normalize(&(r.di));
	des = add_vect(cam->pos, vect_mult_val(r.di,
	cam->focus_dis));
	new_cam_pos = add_vect(cam->pos, (t_vect){deep.x, deep.y, 0.});
	r.or = new_cam_pos;
	r.di = norm(sub_vect(des, new_cam_pos));
	return (r);
}
t_vect				safe_color(t_vect p)
{
	t_vect	col;

	col.x = fmin(255, p.x);
	col.y = fmin(255, p.y);
	col.z = fmin(255, p.z);
	return (col);
}
t_obj			*find_close(t_all data, t_ray ray)
{
	t_obj		*pos;
	t_obj		*header;
	double		t;
	double		t1;

	t1 = -1;
	header = data.obj;
	pos = header;
	while (header->next)
	{
		t = header->inter(header, ray);
		if (t != -1)
		{
			t1 == -1 ? pos = header : 0;
			t1 == -1 ? t1 = t : 0;
			t1 > t ? pos = header : 0;
			t1 > t ? t1 = t : 0;
		}
		header = header->next;
	}
	pos->t = t1;
	return (pos);
}
t_vect			col_pix(t_all data, t_ray ray)
{
	t_vect		col;
	t_obj		*pos;

	pos = find_close(data, ray);
	if (pos->t != -1)
	{
		col = pos->color;
	}
	return (safe_color(col));
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
			ray = init_rayy(cor,data->camera);
			col = col_pix(*data, ray);
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
