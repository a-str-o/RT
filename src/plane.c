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

double		intersection_ray_plan(t_obj *pln, t_ray r)
{
	double	nomi;
	double	dinomi;
	double	t;

	nomi = dot_product(sub_vect(r.or, pln->position), pln->direction);
	dinomi = dot_product(r.di, pln->direction);
	if ((dinomi == 0) || (nomi <= 0 && dinomi < 0) || (nomi >= 0 && dinomi > 0))
		return (-1);
	t = -nomi / dinomi;
	if (t < 0)
		return (-1);
	pln->hit = add_vect(r.or, vect_mult_val(r.di, t));
	pln->norm = norm(pln->direction);
	return (t);
}
