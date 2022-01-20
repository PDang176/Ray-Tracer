#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit result;
    double a = dot(ray.direction, ray.direction);
	double b = 2 * dot(ray.direction, ray.endpoint - center);
	double c = dot(ray.endpoint - center, ray.endpoint - center) - pow(radius, 2);
	
	double root = pow(b, 2) - (4 * a * c);
	if(root < 0){
		result.object = NULL;
	}
	else{
		result.object = this;
		result.dist = (-b - sqrt(root)) / (2 * a);
		result.part = part;
	}
    return result;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
