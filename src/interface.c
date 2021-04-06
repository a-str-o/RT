#include "../header/rt.h"

void            interface(t_all data)
{
    init_sdl(&data);
    data.light->ambient = data.camera->ambient;
    raytracing(data);
    loop_program(&data);
}