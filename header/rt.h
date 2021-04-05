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
void		threading(t_all alll);
void	cartoon_filter(t_all *rt);
void			ft_filter_mb(t_all *rt);
void sepia_filtre(t_all *rt);
void	filtre(t_all *rt);
void			init_ray(t_ray *r, t_vect origine, t_vect direc);
int					light_direct(t_all data, t_ray ray);
t_vect				ft_refraction(t_obj *pos, t_all data, t_ray ray, int nbrbonds);
t_vect		        ft_reflection(t_obj *pos, t_all data, t_ray ray, int nbrbonds);
t_vect				rend_pix(t_all data, t_ray ray, int nbrbonds);
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
int                 s_cube(char **table, int i, t_all *data, t_obj *cube);
void				loop_program(t_all *data);
void				init_sdl(t_all *data);
void				ft_lstdel(t_obj **alst);
void				sdl_error(char *message);
void				ft_alloc_light(t_data_light **light);
void				ft_alloc_obj(t_obj **obj);
void			raytracing(t_all	*data);
void				ft_free_obj(t_all *data);
void                init_li(t_light *li, t_data_light *ligth, t_obj *obj, t_ray ray);
t_vect				light_obj(t_obj *obj,t_all data, t_ray ray, double t);
t_vect				on_shadow(t_obj *pos, t_all data, t_ray ray, t_vect col);
t_ray				init_rayy(int i, int j, t_data_camera *cam, double dx,double dy, double dx_aperture, double dy_aperture);
double				find_obj_scnd(t_all data, t_ray ray, t_ray to_light, t_obj *pos);
double				ft_atof(char *str);
void				texturing(t_obj *obj);
t_sol				find_solution(double delta, t_vect abc);
double				intersection_ray_sphere(t_obj *obj, t_ray r);
double				intersection_ray_ring(t_obj *obj, t_ray r);
double				intersection_ray_plan(t_obj *obj, t_ray r);
double				intersection_ray_cylindre(t_obj *obj, t_ray r);
double				intersection_ray_cone(t_obj *cone, t_ray r);
double				intersection_ray_triangle(t_obj *tri, t_ray r);
double				intersection_ray_geometry(t_obj *gem, t_ray r);
double				intersection_paraploid(t_obj *para, t_ray r);
double				intersection_ellipsoid(t_obj *eli, t_ray r);
double              intersection_cube(t_obj *box, t_ray r);
t_vect				safe_color(t_vect p);


void                sdl_set_text(char *txt, t_vect_i col, t_4d_i rect, t_all *data);
#endif
