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
	cone->norm = norm(sub_vect(sub_vect(cone->hit, cone->position)
				, vect_mult_val(cone->direction, (1 + k + k) * m)));
}

double			intersection_cone(t_obj *cone, t_ray r)
{
	t_vect		abc;
	t_vect		cp;
	t_vect		vd;
	double		angle;
	t_sol		sol;

	t_vect		up;
	t_vect		hit;

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
{
	up = new_vect(0, 1.0, 0);
	if (up.x == cone->position.x && up.z == cone->position.z)
		up = new_vect(0.0001, 1.0001, 0.0001);
	cone->w_dir = norm(sub_vect(cone->position, cone->direction));
	cone->u_dir = norm(cross_product(cone->direction, up));
	cone->v_dir = cross_product(cone->direction, cone->u_dir);

	hit = sub_vect(cone->hit, cone->position);
	if (hit.y >= cone->position.y + cone->size/2 ||
		hit.y <= cone->position.y - cone->size/2)
		return (-1);
}
	return (sol.tmin);
}
