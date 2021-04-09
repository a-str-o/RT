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
void		init_ray(t_ray *r, t_vect origine, t_vect direc)
{
	r->or = origine;
	r->di = direc;
}
double			find_obj_shadow(t_all data, t_ray ray, t_ray to_light, t_obj *pos)
{
	t_obj		*header;
	double		t;
	double		t1;

	t1 = -1;
	header = data.obj;
	while (header->next)
	{
		if (header->id == pos->id && (header = header->next))
			continue;
		t = header->inter(header, to_light);
		if (t != -1)
		{
			if (t1 == -1)
				t1 = t;
			else
			{
				if (t1 > t)
					t1 = t;
			}
		}
		header = header->next;
	}
	return (t1);
}
t_vect			li_col(t_obj *obj, t_data_light *light, t_ray ray, double t)
{
	t_vect		col;
	t_vect		rm;
	double		diff;
	double		spec;

	while (light->next)
	{
		rm = norm(sub_vect(light->position, obj->hit));
		rm = sub_vect(vect_mult_val(obj->norm, 2 * dot_product(rm, obj->norm)), rm);
		diff = fmax(0.0, 0.6 * dot_product(norm(
						sub_vect(light->position, obj->hit)), obj->norm));
		spec = pow(fmax(0.0, dot_product(rm, norm(
							sub_vect(ray.or, obj->hit)))), 40);
		col.x = fmin(255,fmax(col.x , obj->col_am.x + light->color.x *
				diff + light->color.x * spec * light->intensity / (4 * PI *
					pow(norm_2(sub_vect(light->position, obj->hit)), 2))));
		col.y = fmin(255,fmax(col.y , obj->col_am.y + light->color.y *
				diff + light->color.y * spec * light->intensity / (4 * PI *
					pow(norm_2(sub_vect(light->position, obj->hit)), 2))));
		col.z = fmin(255,fmax(col.z , obj->col_am.z + light->color.z * diff +
				light->color.z * spec * light->intensity / (4 * PI *
					pow(norm_2(sub_vect(light->position, obj->hit)), 2))));
		light = light->next;
	}
	return (col);
}
t_2d_d				dis_light(t_obj *pos, t_data_light *light, double t1)
{
	t_vect			hit_sec;
	t_2d_d			light_dest;

	hit_sec = add_vect(pos->hit, vect_mult_val(light->to_light.di, t1));
	light_dest.x = norm_2(sub_vect(hit_sec, pos->hit)) *
	norm_2(sub_vect(hit_sec, pos->hit));
	light_dest.y = norm_2(sub_vect(light->position, pos->hit)) *
	norm_2(sub_vect(light->position, pos->hit));
	return (light_dest);
}
t_vect			shadow(t_obj *pos, t_all data, t_ray ray, t_vect col)
{
	double			dis_shad_lum;
	double			dis_shad_inter;
	double			t1;
	t_data_light	*light;

	light = data.light;
	while (light->next)
	{
		light->norm_light = norm(sub_vect(light->position, pos->hit));
		init_ray(&light->to_light, add_vect(pos->hit, light->norm_light), light->norm_light);
		t1 = find_obj_shadow(data, ray, light->to_light, pos);
		if (t1 != -1)
		{
			dis_shad_inter = dis_light(pos, light, t1).x;
			dis_shad_lum = dis_light(pos, light, t1).y;
			if ((dis_shad_lum > dis_shad_inter))
				init_vect(&col, col.x * 0.7, col.y * 0.7, col.z * 0.7);
		}
		light = light->next;
	}
	return (col);
}

t_vect			light_obj(t_obj *obj, t_all data, t_ray ray, double t)
{
	
	t_vect		col;
	t_data_light *light;

	light = data.light;
	obj->col_am = (t_vect){obj->color.x * light->ambient, 
		obj->color.y * light->ambient, obj->color.z * light->ambient};
	if (light->next == NULL)
		return (obj->col_am);
	col = li_col(obj, light, ray, t);
	col = shadow(obj, data, ray, col);
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
		col = light_obj(pos, data, ray, pos->t);
	// 	col = on_shadow(pos, data, ray, col);
	}
	return (col);
}
t_vect		init_rayy(int i, int j, t_all data)
{
	t_vect	s;
	t_ray	r;
	t_data_camera *cam;

	cam = data.camera;
	s = sub_vect(cam->pos, vect_mult_val(cam->dir, cam->dist));
	s = sub_vect(s, vect_mult_val(cam->u_dir, (i - (W / 2))));
	s = add_vect(s, vect_mult_val(cam->v_dir, ((H / 2) - j)));
	r.di = sub_vect(s, cam->pos);
	r.or = cam->pos;
	normalize(&(r.di));
	return (col_pix(data, r));
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
			col = init_rayy(i, j, data);
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