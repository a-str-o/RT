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

t_vect			light_obj(t_obj *obj, t_data_light *light, t_ray ray, double t)
{
	t_vect		col;
	double		diff;
	double		spec;
	t_vect		rm;

	rm = norm(sub_vect(light->position, obj->hit));
	rm = sub_vect(vect_mult_val(obj->norm, 2 * dot_product(rm, obj->norm)), rm);
	diff = fmax(0.0, 0.6 * dot_product(norm(
					sub_vect(light->position, obj->hit)), obj->norm));
	spec = 1 * pow(fmax(0.0, dot_product(rm, norm(
						sub_vect(ray.or, obj->hit)))), 40);
	col.x = fmin(255, obj->color.x + light->ambient + light->color.x *
			diff + light->color.x * spec * light->intensity / (4 * PI *
				pow(norm_2(sub_vect(light->position, obj->hit)), 2)));
	col.y = fmin(255, obj->color.y + light->ambient + light->color.y *
			diff + light->color.y * spec * light->intensity / (4 * PI *
				pow(norm_2(sub_vect(light->position, obj->hit)), 2)));
	col.z = fmin(255, obj->color.z + light->ambient + light->color.z * diff +
			light->color.z * spec * light->intensity / (4 * PI *
				pow(norm_2(sub_vect(light->position, obj->hit)), 2)));
	return (col);
}

void		init_ray(t_ray *r, t_vect origine, t_vect direc)
{
	r->or = origine;
	r->di = direc;
}

t_ray		init_rayy(int i, int j, t_data_camera *cam)
{
	t_vect	s;
	t_ray	r;

	s = sub_vect(cam->pos, vect_mult_val(cam->dir, cam->dist));
	s = sub_vect(s, vect_mult_val(cam->u_dir, (i - (W / 2))));
	s = add_vect(s, vect_mult_val(cam->v_dir, ((H / 2) - j)));
	r.di = sub_vect(s, cam->pos);
	r.or = cam->pos;
	normalize(&(r.di));
	return (r);
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
			if (t1 > t || t1 == -1)
			{
				pos = header;
				t1 = t;
			}
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

	col = new_vect(100, 100, 100);
	pos = find_close(data, ray);
	if (pos->t != -1)
	{
		col = light_obj(pos, data.light, ray, pos->t);
	// 	col = on_shadow(pos, data, ray, col);
	}
	return (col);
}
void			raytracing(t_all data)
{
	int			j;
	int			i;
	t_ray		ray;
	t_vect		col;

	i = 0;
	while (i < W)
	{
		j = 0;
		while (j < H)
		{
			ray = init_rayy(i, j, data.camera);
			col = col_pix(data, ray);
			if (SDL_SetRenderDrawColor(data.rend,
						col.x, col.y, col.z, 255) != 0)
				sdl_error("Get color failed");
			if (SDL_RenderDrawPoint(data.rend, i, j) != 0)
				sdl_error("draw point failed");
			j++;
		}
		i++;
	}
}