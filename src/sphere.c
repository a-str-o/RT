#include "../header/rt.h"

double			intersection_ray_sphere(t_obj *sph, t_ray r)
{
	t_vect		abc;
	double		delta;
	t_sol		sol;

	abc.x = norm_2(r.di);
	abc.y = 2 * vect_scal(r.di, sub_vect(r.or, sph->position));
	abc.z = norm_2(sub_vect(r.or, sph->position))
		- (sph->radius * sph->radius);
	delta = abc.y * abc.y - 4 * abc.x * abc.z;
	sol = find_solution(delta, abc);
	sph->hit = add_vect(r.or, vect_mult_val(r.di, sol.tmin));
	//sol.tmin = slice_sphere(sph, r, sol);
	sph->norm = norm(sub_vect(sph->hit, sph->position));
	return (sol.tmin);
}
