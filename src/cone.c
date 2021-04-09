/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:38:38 by yoelguer          #+#    #+#             */
/*   Updated: 2021/02/09 18:45:03 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void			hit_norm(t_obj *cone, t_ray r, double t)
{
	double		k;
	double		m;

	k = tan((cone->radius * PI / 180) / 2);
	m = dot_product(r.di, vect_mult_val(cone->direction, t))
		+ dot_product(sub_vect(r.or, cone->position), cone->direction);
	cone->hit = add_vect(r.or, vect_mult_val(r.di, t));
	cone->norm = sub_vect(sub_vect(cone->hit, cone->position)
				, vect_mult_val(cone->direction, (1 + k + k) * m));
}

double			cone_slice(t_obj *cone, t_ray r, t_sol sol, t_vect sly)
{
	cone->hit = add_vect(r.or, vect_mult_val(r.di, sol.tmax));
	if (sol.tmax > 0 &&
			dot_product(sub_vect(cone->pos_slice, cone->hit), sly) > 0.0)
	{
		hit_norm(cone, r, sol.tmax);
		return (sol.tmax);
	}
	return (-1);
}

double			limeted_cone(t_obj *cone, t_ray r, t_sol sol)
{
	t_vect		up;
	t_vect		hit;
	t_vect		hit2;

	t_vect	sly;
	int		is;

	sly = cone->slice;
	if (!sly.x && !sly.y && !sly.z)
		is = 0;
	else
		is = 1;
	if (is == 1 && dot_product(sub_vect(cone->pos_slice, cone->hit), sly) <= 0.0)
		return (cone_slice(cone, r, sol, sly));

	up = new_vect(0, 1.0, 0);
	if (up.x == cone->position.x && up.z == cone->position.z)
		up = new_vect(0.0001, 1.0001, 0.0001);
	cone->w_dir = norm(sub_vect(cone->position, cone->direction));
	cone->u_dir = norm(cross_product(cone->direction, up));
	cone->v_dir = cross_product(cone->direction, cone->u_dir);
	hit = sub_vect(cone->hit, cone->position);
	if (hit.y >= cone->position.y + cone->size/2 ||
		hit.y <= cone->position.y - cone->size/2)
	{
		cone->hit = add_vect(r.or, vect_mult_val(r.di, sol.tmax));
		hit2 = sub_vect(cone->hit, cone->position);
		cone->norm = norm(vect_mult_val(cone->norm,-1));
		if (hit2.y >= cone->position.y + cone->size/2 ||
		hit2.y <= cone->position.y - cone->size/2)
			return -1;
		else 
			return (sol.tmax);
	}
	return (sol.tmin);
}
double			intersection_cone(t_obj *cone, t_ray r)
{
	t_vect		abc;
	t_vect		cp;
	t_vect		vd;
	double		angle;
	t_sol		sol;

	angle = cone->radius * PI / 180;
	vd = sub_vect(r.or, cone->position);
	cp.x = dot_product(vd, cone->direction);
	cp.y = dot_product(r.di, cone->direction);
	abc.x = (norm_2(sub_vect(r.di,
			vect_mult_val(cone->direction, cp.y))) * pow(cos(angle), 2))
		- (pow(cp.y, 2) * pow(sin(angle), 2));
	abc.y = 2 * ((dot_product(sub_vect(r.di,
		vect_mult_val(cone->direction, cp.y)), sub_vect(vd,
		vect_mult_val(cone->direction, cp.x)))
		* pow(cos(angle), 2)) - (cp.y * cp.x * pow(sin(angle), 2)));
	abc.z = (norm_2(sub_vect(vd, vect_mult_val(cone->direction, cp.x))) *
			pow(cos(angle), 2)) - (pow(cp.x, 2) * pow(sin(angle), 2));
	cp.z = abc.y * abc.y - 4 * abc.x * abc.z;
	sol = find_solution(cp.z, abc);
	hit_norm(cone, r, sol.tmin);
	
	if (cone->size != 0)
		sol.tmin = limeted_cone(cone, r, sol);
	cone->norm = norm(cone->norm);
	return (sol.tmin);
}
