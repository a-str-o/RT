/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:46:09 by yoelguer          #+#    #+#             */
/*   Updated: 2021/02/09 18:46:13 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void		f_cylinder2(char **str, int j, t_obj *cylinder)
{
	if (j == 6)
		init_vect(&cylinder->color, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 7)
		cylinder->radius = ft_atof(str[0]);
	if (j == 8)
		cylinder->size = ft_atof(str[0]);
	if (j == 9)
		cylinder->type = ft_atof(str[0]);
	if (j == 10)
		cylinder->trans = ft_atof(str[0]);
	if (j == 11)
		cylinder->refl = ft_atof(str[0]);
}
void		f_cylinder(char **str, int j, t_obj *cylinder)
{
	if (j == -1)
		init_vect(&cylinder->text_modif, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 0)
		init_vect(&cylinder->position, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 1)
		init_vect(&cylinder->direction, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 2)
		init_vect(&cylinder->translation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 3)
		init_vect(&cylinder->rotation, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 4)
		init_vect(&cylinder->slice, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	if (j == 5)
		init_vect(&cylinder->pos_slice, ft_atof(str[0]),
				ft_atof(str[1]), ft_atof(str[2]));
	
	f_cylinder2(str, j, cylinder);
}

int			s_cylinder(char **table, int i, t_all *data, t_obj *cylinder)
{
	int		j;
	char	**str;

	j = -1;
	cylinder->name = ft_strdup(table[i - 1]);
	cylinder->texture = ft_strdup(table[i]);
	while (table[++i] && j < 12)
	{
		str = ft_strsplit(table[i], ' ');
		if (f_str(str, j, 6) == -1)
			return (-1);
		f_cylinder(str, j, cylinder);
		j++;
	}
	data->id++;
	cylinder->id = data->id;
	if (ft_strcmp(cylinder->texture, ".") != 0)
		if(!(cylinder->surface = IMG_Load(cylinder->texture)))
			sdl_error("can't load surface");
	if (ft_strcmp(cylinder->texture, ".") == 0)		
	cylinder->direction = rot_vect_xyz(cylinder->direction, cylinder->rotation);
	cylinder->position = trans_vect_xyz(cylinder->position, 
		cylinder->translation);
	cylinder->inter = &intersection_cylindre;
	cylinder->half_size = cylinder->size / 2;
	return (0);
}
