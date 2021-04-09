/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:37:40 by yoelguer          #+#    #+#             */
/*   Updated: 2021/02/09 18:37:41 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define W       1000
# define H       1000
# define NBR_RAYS    40 // nbr for focus or aalias or 1 for nothing 
# define PI          3.14159265359
# define CLAMP(nbr, min, max) (nbr <= min ? min : nbr >= max ? max : nbr)

# include "vector.h"
# include <pthread.h>
# include "data.h"
# include "../libft/libft.h"
# include <stdio.h>
# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"
# include "vector.h"
# include <math.h>
t_vect		init_rayy(int i, int j, t_all data);
void		ft_alloc_cube(t_cube **obj);
void			init_sdl(t_all *data);
void			loop_program(t_all *data);
t_vect				safe_color(t_vect p);
t_sol			find_solution(double delta, t_vect abc);

void		ft_free_obj(t_all *data);

int					ft_val(char *str);
int					ft_val2(char *str);
int					ft_camera(char **table, t_all *data);
int					ft_obj(char **table, t_all *data);
int					check_str2(char **str, int j, int k);
int					f_str(char **str, int j, int k);
int					check_str1(char **str, int j, int k);
int					f_str2(char **str, int j, int d);
int					ft_cylinder(char **table, t_all *data);
int					ft_light(char **table, t_all *data);
int					file_checker(char *str, t_all *data);
int					s_sphere(char **table, int i, t_all *data, t_obj *sphere);
int					s_plane(char **table, int i, t_all *data, t_obj *plane);
int					s_cone(char **table, int i, t_all *data, t_obj *cone);
int					s_ring(char **table, int i, t_all *data, t_obj *ring);
int					s_cylinder(char **table, int i,t_all *data, t_obj *cyl);
int					s_triangle(char **table, int i,t_all *data, t_obj *tri);
int					s_paraploid(char **table, int i, t_all *d, t_obj *par);
int					s_ellipsoid(char **table, int i, t_all *data, t_obj *el);
int                 s_cube(char **table, int i, t_all *data, t_plans **cube);
void				loop_program(t_all *data);
void				init_sdl(t_all *data);
void				ft_lstdel(t_obj **alst);
void				sdl_error(char *message);
void				ft_alloc_light(t_data_light **light);
void				ft_alloc_obj(t_obj **obj);
double				ft_atof(char *str);

double				intersection_sphere(t_obj *obj, t_ray r);
double				intersection_ring(t_obj *obj, t_ray r);
double				intersection_plan(t_obj *obj, t_ray r);
double				intersection_cylindre(t_obj *obj, t_ray r);
double				intersection_cone(t_obj *cone, t_ray r);
double				intersection_triangle(t_obj *tri, t_ray r);
double				intersection_geometry(t_obj *gem, t_ray r);
double				intersection_paraploid(t_obj *para, t_ray r);
double				intersection_ellipsoid(t_obj *eli, t_ray r);
double              intersection_cube(t_obj *box, t_ray r);

void        init_plans(t_obj **obj,int k, t_plans *pln, t_all *data);


void                sdl_set_text(char *txt, t_vect_i col, t_4d_i rect, t_all *data);
///////////
void			raytracing(t_all data);
void            interface(t_all data);



#endif
