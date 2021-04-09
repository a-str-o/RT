#include "../header/rt.h"

void        init_1(t_obj *obj, t_plans *pln, t_all *data)
{
	init_vect(&obj->position, pln->position.x, pln->position.y + 
                                pln->size/2, pln->position.z);
	init_vect(&obj->translation, pln->translation.x, 
                pln->translation.y, pln->translation.z);
	init_vect(&obj->rotation, pln->rotation.x, 
                    pln->rotation.y, pln->rotation.z);
	init_vect(&obj->color, pln->color.x, pln->color.y, pln->color.z);
	init_vect(&obj->direction, 0, 1, 0);
	obj->size = pln->size;
    obj->direction = rot_vect_xyz(obj->direction,
			obj->rotation);
	obj->position = trans_vect_xyz(obj->position, obj->translation);
	obj->half_size = obj->size / 2;
	obj->inter = &intersection_plan;
    obj->id = data->id;
}


void        init_2(t_obj *obj, t_plans *pln, t_all *data)
{
	init_vect(&obj->position, pln->position.x, pln->position.y - 
                                pln->size/2, pln->position.z);
	init_vect(&obj->translation, pln->translation.x, 
                pln->translation.y, pln->translation.z);
	init_vect(&obj->rotation, pln->rotation.x, 
                    pln->rotation.y, pln->rotation.z);
	init_vect(&obj->color, pln->color.x, pln->color.y, pln->color.z);
	init_vect(&obj->direction, 0, -1, 0);
	obj->size = pln->size;
    obj->direction = rot_vect_xyz(obj->direction,
			obj->rotation);
	obj->position = trans_vect_xyz(obj->position, obj->translation);
	obj->half_size = obj->size / 2;
	obj->inter = &intersection_plan;
    obj->id = data->id;
}

void        init_3(t_obj *obj, t_plans *pln, t_all *data)
{
	init_vect(&obj->position, pln->position.x, pln->position.y , pln->position.z+
                                pln->size/2);
	init_vect(&obj->translation, pln->translation.x, 
                pln->translation.y, pln->translation.z);
	init_vect(&obj->rotation, pln->rotation.x, 
                    pln->rotation.y, pln->rotation.z);
	init_vect(&obj->color, pln->color.x, pln->color.y, pln->color.z);
	init_vect(&obj->direction, 0, 0, 1);
	obj->size = pln->size;
      obj->direction = rot_vect_xyz(obj->direction,
			obj->rotation);
	obj->position = trans_vect_xyz(obj->position, obj->translation);
	obj->half_size = obj->size / 2;
	obj->inter = &intersection_plan;
    obj->id = data->id;
}


void        init_4(t_obj *obj, t_plans *pln, t_all *data)
{
	init_vect(&obj->position, pln->position.x, pln->position.y , pln->position.z -
                                pln->size/2);
	init_vect(&obj->translation, pln->translation.x, 
                pln->translation.y, pln->translation.z);
	init_vect(&obj->rotation, pln->rotation.x, 
                    pln->rotation.y, pln->rotation.z);
	init_vect(&obj->color, pln->color.x, pln->color.y, pln->color.z);
	init_vect(&obj->direction, 0, 0, -1);
	obj->size = pln->size;
      obj->direction = rot_vect_xyz(obj->direction,
			obj->rotation);
	obj->position = trans_vect_xyz(obj->position, obj->translation);
	obj->half_size = obj->size / 2;
	obj->inter = &intersection_plan;
    obj->id = data->id;
}

void        init_5(t_obj *obj, t_plans *pln, t_all *data)
{
	init_vect(&obj->position, pln->position.x + pln->size/2,
                pln->position.y , pln->position.z );
	init_vect(&obj->translation, pln->translation.x, 
                pln->translation.y, pln->translation.z);
	init_vect(&obj->rotation, pln->rotation.x, 
                    pln->rotation.y, pln->rotation.z);
	init_vect(&obj->color, pln->color.x, pln->color.y, pln->color.z);
	init_vect(&obj->direction, 1, 0, 0);
	obj->size = pln->size;
      obj->direction = rot_vect_xyz(obj->direction,
			obj->rotation);
	obj->position = trans_vect_xyz(obj->position, obj->translation);
	obj->half_size = obj->size / 2;
	obj->inter = &intersection_plan;
    obj->id = data->id;
}

void        init_6(t_obj *obj, t_plans *pln, t_all *data)
{
	init_vect(&obj->position, pln->position.x - pln->size/2,
                pln->position.y , pln->position.z );
	init_vect(&obj->translation, pln->translation.x, 
                pln->translation.y, pln->translation.z);
	init_vect(&obj->rotation, pln->rotation.x, 
                    pln->rotation.y, pln->rotation.z);
	init_vect(&obj->color, pln->color.x, pln->color.y, pln->color.z);
	init_vect(&obj->direction, -1, 0, 0);
	obj->size = pln->size;
      obj->direction = rot_vect_xyz(obj->direction,
			obj->rotation);
	obj->position = trans_vect_xyz(obj->position, obj->translation);
	obj->half_size = obj->size / 2;
	obj->inter = &intersection_plan;
    obj->id = data->id;
}

void        init_plans(t_obj **obj,int k, t_plans *pln, t_all *data)
{
	init_vect(&pln->position , 0 , 0 , 0);
    if (k == 0)
        init_1(*obj, pln, data);
    if (k == 1)
        init_2(*obj, pln, data);
    if (k == 2)
        init_3(*obj, pln, data);
    if (k == 3)
        init_4(*obj, pln, data);
    if (k == 4)
        init_5(*obj, pln, data);
    if (k == 5)
        init_6(*obj, pln, data);
}