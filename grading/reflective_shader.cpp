#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color = (1 - reflectivity) * shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
    // TODO; // determine the color

    if(recursion_depth < world.recursion_depth_limit){
        vec3 dir = ray.direction - (2 * dot(normal, ray.direction) * normal);

        Ray reflected(intersection_point, dir);

        vec3 reflected_color = world.Cast_Ray(reflected, recursion_depth + 1);

        color = color + (reflectivity * reflected_color);
    }

    return color;
}
