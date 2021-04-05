#include "../header/rt.h"

t_sol			find_solution(double delta, t_vect abc)
{
	t_sol	sol;
	double	temp;

	if (delta < 0)
		return ((t_sol){-1., -1.});
	sol.tmin = (-1 * abc.y - sqrt(delta)) / (2 * abc.x);
	sol.tmax = (-1 * abc.y + sqrt(delta)) / (2 * abc.x);
	if (sol.tmin < 0 && sol.tmax < 0)
		return ((t_sol){-1., -1.});
	else if (sol.tmin > 0 && sol.tmax < 0)
		sol.tmax = -1;
	else if ((sol.tmax > 0 && sol.tmin < 0))
	{
		sol.tmin = sol.tmax;
		sol.tmax = -1;
	}
	else
	{
		temp = fmin(sol.tmin, sol.tmax);
		sol.tmax = fmax(sol.tmin, sol.tmax);
		sol.tmin = temp;
	}
	return (sol);
}