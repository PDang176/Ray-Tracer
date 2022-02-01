#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"
#include <algorithm>

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    // TODO; //determine the color
    vec3 ambient, diffuse, specular;

    // Ambient
    ambient = color_ambient * world.ambient_color * world.ambient_intensity;

    // Looping through all the lights
    for(unsigned i = 0; i < world.lights.size(); i++){
        Light* curr = world.lights[i];
        vec3 shadow_direction;
        Ray shadow_ray;
        Hit shadow_hit;

        vec3 l = curr->position - intersection_point;

        if(world.enable_shadows){
            shadow_direction = l.normalized();
			shadow_ray.endpoint = intersection_point;
            shadow_ray.direction = shadow_direction;
			shadow_hit = world.Closest_Intersection(shadow_ray);
        }

        if(!world.enable_shadows || shadow_hit.object == NULL || shadow_hit.dist > l.magnitude()){
            // Diffuse
            vec3 light_color = curr->Emitted_Light(ray.direction) / l.magnitude_squared();

            l = l.normalized();

            double diffuse_intensity = std::max(dot(normal, l), 0.0);
            
            diffuse += color_diffuse * light_color * diffuse_intensity;

            // Specular
            vec3 r = (2 * dot(normal, l) * normal) - l;
            r = r.normalized();

            vec3 c = -ray.direction.normalized();
            double specular_intensity = std::max(dot(r, c), 0.0);
            specular_intensity = pow(specular_intensity, specular_power);

            specular += color_specular * light_color * specular_intensity;
        }
    }

    color = ambient + diffuse + specular;    
    return color;
}