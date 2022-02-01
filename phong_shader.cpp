#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    // TODO; //determine the color
    vec3 ambient = (world.ambient_color * world.ambient_intensity) + color_ambient;
    vec3 l = ray.endpoint - intersection_point;
    double diffuse_intensity = dot(l, normal);
    diffuse_intensity = diffuse_intensity > 0 ? diffuse_intensity : 0;
    vec3 diffuse = color_diffuse * diffuse_intensity;
    vec3 r = (dot(l, normal) * (normal - l)) * 2;
    double specular_intensity = dot(r, world.camera.position);
    specular_intensity = specular_intensity > 0 ? specular_intensity : 0;
    specular_intensity = pow(specular_intensity, specular_power);
    vec3 specular = color_specular * specular_intensity;

    color = ambient + diffuse + specular;
    
    return color;
}
