#include "../header/rt.h"



double			intersection_sphere(t_obj *sph, t_ray r)
{
	t_vect		abc;
	double		delta;
	t_sol		sol;
	t_vect		up;
	t_vect		hit2;
	t_vect		hit3;
	t_vect		hit;

	abc.x = norm_2(r.di);
	abc.y = 2 * vect_scal(r.di, sub_vect(r.or, sph->position));
	abc.z = norm_2(sub_vect(r.or, sph->position))
		- (sph->radius * sph->radius);
	delta = abc.y * abc.y - 4 * abc.x * abc.z;
	sol = find_solution(delta, abc);

	up = new_vect(0, 1.0, 0);
	if (up.x == sph->position.x && up.z == sph->position.z)
		up = new_vect(0.0001, 1.0001, 0.0001);
	sph->w_dir = norm(sub_vect(sph->position, sph->direction));
	sph->u_dir = norm(vect_cross(sph->direction, up));
	sph->v_dir = vect_cross(sph->direction, sph->u_dir);


	sph->hit = add_vect(r.or, vect_mult_val(r.di, sol.tmin));
	hit2 = sub_vect(sph->hit, sph->position);

	hit = add_vect(r.or, vect_mult_val(r.di, sol.tmax));
	hit3 = sub_vect(sph->hit, sph->position);

	if (hit2.y >= 0 || hit3.y >= 0)
		return -1;
	//sol.tmin = slice_sphere(sph, r, sol);
	sph->norm = norm(sub_vect(sph->hit, sph->position));
	
	return (sol.tmin);
}
