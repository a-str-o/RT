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

double			intersection_cylindre(t_obj *cyl, t_ray r)
{
	t_vect		f;
	t_vect		g;
	t_vect		abc;
	double		delta;
	t_sol		sol;

	t_vect		up;
	t_vect		hit;
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
{
	up = new_vect(0, 1.0, 0);
	if (up.x == cyl->position.x && up.z == cyl->position.z)
		up = new_vect(0.0001, 1.0001, 0.0001);
	cyl->w_dir = norm(sub_vect(cyl->position, cyl->direction));
	cyl->u_dir = norm(cross_product(cyl->direction, up));
	cyl->v_dir = cross_product(cyl->direction, cyl->u_dir);

	hit = sub_vect(cyl->hit, cyl->position);
	if (hit.y >= cyl->position.y + cyl->size/2 ||
		hit.y <= cyl->position.y - cyl->size/2)
		return (-1);
}
	return (sol.tmin);
}
