#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
	double b = 2 * dot(ray.direction, ray.endpoint - center);
	double c = dot(ray.endpoint - center, ray.endpoint - center) - pow(radius, 2);
	
	double root = pow(b, 2) - (4 * c);
	if(root >= 0){
		double t1 = (-b - sqrt(root)) / 2;
		double t2 = (-b + sqrt(root)) / 2;

		double t = t1 < 0 ? t2 : t1;
		if(t >= small_t){
			return {this, t, part};
		}
	}
    return {NULL, 0, part};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    // TODO; // compute the normal direction
    normal = point - center;
	return normal.normalized();
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    // TODO; // calculate bounding box
    box.hi = center + vec3(radius, radius, radius);
	box.lo = center - vec3(radius, radius, radius);
    return box;
}
