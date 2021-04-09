/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:45:27 by yoelguer          #+#    #+#             */
/*   Updated: 2021/02/09 18:45:36 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void		ft_alloc_obj(t_obj **obj)
{
	(*obj) = (t_obj*)malloc(sizeof(t_obj));
	init_vect(&(*obj)->pos_slice, 0, 0, 0);
	init_vect(&(*obj)->col, 0, 0, 0);
	init_vect(&(*obj)->col_am, 0, 0, 0);
	init_vect(&(*obj)->a, 0, 0, 0);
	init_vect(&(*obj)->b, 0, 0, 0);
	init_vect(&(*obj)->c, 0, 0, 0);
	init_vect(&(*obj)->position, 0, 0, 0);
	init_vect(&(*obj)->text_modif, 0, 0, 0);
	init_vect(&(*obj)->slice, 0, 0, 0);
	init_vect(&(*obj)->translation, 0, 0, 0);
	init_vect(&(*obj)->rotation, 0, 0, 0);
	init_vect(&(*obj)->color, 0, 0, 0);
	init_vect(&(*obj)->axis, 0, 0, 0);
	init_vect(&(*obj)->hit, 0, 0, 0);
	init_vect(&(*obj)->norm, 0, 0, 0);
	init_vect(&(*obj)->direction, 0, 0, 0);
	(*obj)->radius = 0;
	(*obj)->radius2 = 0;
	(*obj)->size = 0;
	(*obj)->t = 0;
	(*obj)->type = 0;
	(*obj)->trans = 0;
	(*obj)->half_size = 0;
	(*obj)->refl = 0;
	(*obj)->texture = NULL;
	(*obj)->name = NULL;
	(*obj)->surface = NULL;
	(*obj)->next = NULL;
}


void		ft_alloc_cube(t_cube **obj)
{
	(*obj) = (t_cube*)malloc(sizeof(t_cube));
}
void		ft_alloc_light(t_data_light **light)
{
	(*light) = (t_data_light*)malloc(sizeof(t_data_light));
	init_vect(&(*light)->position, 0, 0, 0);
	init_vect(&(*light)->direction, 0, 0, 0);
	init_vect(&(*light)->color, 0, 0, 0);
	(*light)->intensity = 0;
	(*light)->type = 0;
	(*light)->angle = 0;
	(*light)->next = NULL;
}

void		ft_alloc_camera(t_data_camera **camera)
{
	(*camera) = (t_data_camera*)malloc(sizeof(t_data_camera));
	init_vect(&(*camera)->pos, 0, 0, 0);
	init_vect(&(*camera)->dir, 0, 0, 0);
	init_vect(&(*camera)->u_dir, 0, 0, 0);
	init_vect(&(*camera)->v_dir, 0, 0, 0);
	(*camera)->dist = 0;
	(*camera)->focus_dis = 0;
	(*camera)->ambient = 0;
}

void		ft_lstdel(t_obj **alst)
{
	t_obj	*temp;

	if (!alst)
		return ;
	while (*alst)
	{
		temp = (*alst)->next;
		free(*alst);
		*alst = temp;
	}
	*alst = NULL;
	return ;
}

void		ft_free_obj(t_all *data)
{
	while (data->light)
	{
		free(data->light);
		data->light = data->light->next;
	}
	free(data->camera);
	ft_lstdel(&data->obj);
}
