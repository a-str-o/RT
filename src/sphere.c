#include "../header/rt.h"

double			sph_slice(t_obj *sph, t_ray r, t_sol sol, t_vect sly)
{
	sph->hit = add_vect(r.or, vect_mult_val(r.di, sol.tmax));
	if (sol.tmax > 0 && dot_product(sub_vect(sph->pos_slice, sph->hit), sly) > 0.0)
	{
		sph->norm = norm(vect_mult_val(sub_vect(sph->hit, sph->position), -1));
		return (sol.tmax);
	}
	return (-1);
}

double			intersection_sphere(t_obj *sph, t_ray r)
{
	t_vect		abc;
	double		delta;
	t_sol		sol;
	t_vect		up;
	t_vect		hit;
	t_vect		hit2;

	abc.x = norm_2(r.di);
	abc.y = 2 * dot_product(r.di, sub_vect(r.or, sph->position));
	abc.z = norm_2(sub_vect(r.or, sph->position))
		- (sph->radius * sph->radius);
	delta = abc.y * abc.y - 4 * abc.x * abc.z;
	sol = find_solution(delta, abc);

	up = new_vect(0, 1.0, 0);
	if (up.x == sph->position.x && up.z == sph->position.z)
		up = new_vect(0.0001, 1.0001, 0.0001);
	sph->w_dir = norm(sub_vect(sph->position, sph->direction));
	sph->u_dir = norm(cross_product(sph->direction, up));
	sph->v_dir = cross_product(sph->direction, sph->u_dir);

sph->hit = add_vect(r.or, vect_mult_val(r.di, sol.tmin));
	hit = sub_vect(sph->hit, sph->position);
	sph->norm = norm(sub_vect(sph->hit, sph->position));
	t_vect	sly;
	int		is;

	sly = sph->slice;
	if (!sly.x && !sly.y && !sly.z)
		is = 0;
	else
		is = 1;
	if (is == 1 && dot_product(sub_vect(sph->pos_slice, sph->hit), sly) <= 0.0)
	{
		sph->hit = add_vect(r.or, vect_mult_val(r.di, sol.tmax));
		if (sol.tmax > 0 && dot_product(sub_vect(sph->pos_slice, sph->hit), sly) > 0.0)
		{
			sph->norm = norm(sub_vect(sph->hit, sph->position));
			return (sol.tmax);
		}
		return (-1);
	}
	return (sol.tmin);

	
	// if (hit.y > sph->size/2)
	// {
	// 	sph->hit = add_vect(r.or, vect_mult_val(r.di, sol.tmax));
	// 	hit2 = sub_vect(sph->hit, sph->position);
	// 	sph->norm = norm(vect_mult_val(sub_vect(sph->hit, sph->position), -1));
	// 	if (hit2.y >= sph->size/2)
	// 		return -1;
	// 	else if (hit2.y <= sph->size/2)
	// 		return (sol.tmax);
	// }
	//sol.tmin = slice_sphere(sph, r, sol);
	
	
	return (sol.tmin);
}
