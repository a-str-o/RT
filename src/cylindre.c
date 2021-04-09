/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:38:44 by yoelguer          #+#    #+#             */
/*   Updated: 2021/02/09 18:45:13 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

double			cly_slice(t_obj *cyl, t_ray r, t_sol sol, t_vect sly)
{
	cyl->hit = add_vect(r.or, vect_mult_val(r.di, sol.tmax));
	if (sol.tmax > 0 && dot_product(sub_vect(cyl->pos_slice, cyl->hit), sly) > 0.0)
	{
		cyl->norm = norm(vect_mult_val(sub_vect(sub_vect(cyl->hit, cyl->position),
			vect_mult_val(cyl->direction, dot_product(cyl->direction,
					sub_vect(cyl->hit, cyl->position)))), -1));
		return (sol.tmax);
	}
	return (-1);
}

double			limeted_cly(t_obj *cyl, t_ray r, t_sol sol)
{
	t_vect		up;
	t_vect		hit;
	t_vect		hit2;

	t_vect	sly;
	int		is;

	sly = cyl->slice;
	if (!sly.x && !sly.y && !sly.z)
		is = 0;
	else
		is = 1;
	if (is == 1 && dot_product(sub_vect(cyl->pos_slice, cyl->hit), sly) < 0.0)
		return (cly_slice(cyl, r, sol, sly));

	up = new_vect(0, 1.0, 0);
	if (up.x == cyl->position.x && up.z == cyl->position.z)
		up = new_vect(0.0001, 1.0001, 0.0001);
	cyl->w_dir = norm(sub_vect(cyl->position, cyl->direction));
	cyl->u_dir = norm(cross_product(cyl->direction, up));
	cyl->v_dir = cross_product(cyl->direction, cyl->u_dir);

	hit = sub_vect(cyl->hit, cyl->position);
	if (hit.y > cyl->position.y + cyl->size/2 ||
		hit.y < cyl->position.y - cyl->size/2)
	{
		cyl->hit = add_vect(r.or, vect_mult_val(r.di, sol.tmax));
		hit2 = sub_vect(cyl->hit, cyl->position);
		cyl->norm = norm(vect_mult_val(sub_vect(sub_vect(cyl->hit, cyl->position),
			vect_mult_val(cyl->direction, dot_product(cyl->direction,
					sub_vect(cyl->hit, cyl->position)))), -1));
		if (hit2.y >= cyl->position.y + cyl->size/2 ||
			hit2.y <= cyl->position.y - cyl->size/2)
			return -1;
		else 
			return (sol.tmax);
	}

	return (sol.tmin);
}

double			intersection_cylindre(t_obj *cyl, t_ray r)
{
	t_vect		f;
	t_vect		g;
	t_vect		abc;
	double		delta;
	t_sol		sol;

	g = sub_vect(r.or, cyl->position);
	f = sub_vect(r.di, vect_mult_val(cyl->direction,
				dot_product(r.di, cyl->direction)));
	g = sub_vect(g, vect_mult_val(cyl->direction,
				dot_product(g, cyl->direction)));
	abc.x = norm_2(f);
	abc.y = 2 * dot_product(f, g);
	abc.z = norm_2(g) - (cyl->radius * cyl->radius);
	delta = abc.y * abc.y - 4 * abc.x * abc.z;
	sol = find_solution(delta, abc);
	cyl->hit = add_vect(r.or, vect_mult_val(r.di, sol.tmin));
	cyl->norm = norm(sub_vect(sub_vect(cyl->hit, cyl->position),
				vect_mult_val(cyl->direction, dot_product(cyl->direction,
						sub_vect(cyl->hit, cyl->position)))));
	if (cyl->size != 0)
		return (limeted_cly(cyl, r, sol));
	return (sol.tmin);
}
