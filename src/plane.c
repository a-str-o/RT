/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:47:58 by yoelguer          #+#    #+#             */
/*   Updated: 2021/02/09 18:48:03 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

double		intersection_plan(t_obj *pln, t_ray r)
{
	double	nomi;
	double	dinomi;
	double	t;
	t_vect		up;
t_vect		hit;
	nomi = dot_product(sub_vect(r.or, pln->position), pln->direction);
	dinomi = dot_product(r.di, pln->direction);
	if ((dinomi == 0) || (nomi <= 0 && dinomi < 0) || (nomi >= 0 && dinomi > 0))
		return (-1);
	t = -nomi / dinomi;
	if (t < 0)
		return (-1);
	pln->hit = add_vect(r.or, vect_mult_val(r.di, t));
	pln->norm = norm(pln->direction);

if (pln->size != 0)
{
		up = new_vect(0, 1.0, 0);
	if (up.x == pln->position.x && up.z == pln->position.z)
		up = new_vect(0.0001, 1.0001, 0.0001);
	pln->w_dir = norm(sub_vect(pln->position, pln->direction));
	pln->u_dir = norm(cross_product(pln->direction, up));
	pln->v_dir = cross_product(pln->direction, pln->u_dir);
	hit = sub_vect(pln->hit, pln->position);
	if ((hit.y > pln->position.y + pln->size/2 ||
		hit.y < pln->position.y - pln->size/2) && pln->direction.y == 0)
		return (-1);
	if ((hit.x > pln->position.x + pln->size/2 ||
		hit.x < pln->position.x - pln->size/2) && pln->direction.x == 0)
		return (-1);
	if ((hit.z > pln->position.z + pln->size/2 ||
		hit.z < pln->position.z - pln->size/2) && pln->direction.z == 0)
		return (-1);
}
	return (t);
}
