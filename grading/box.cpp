#include <limits>
#include "box.h"

// Return whether the ray intersects this box.
bool Box::Intersection(const Ray& ray) const
{
    // TODO;

    vec3 tmin = (lo - ray.endpoint) / ray.direction;
    vec3 tmax = (hi - ray.endpoint) / ray.direction;

    for(unsigned i = 0; i < 3; i++){
        if(tmin[i] > tmax[i]){
            double temp = tmin[i];
            tmin[i] = tmax[i];
            tmax[i] = temp;
        }
    }

    if(tmin[0] > tmax[1] || tmin[1] > tmax[0]){
        return false;
    }

    if(tmin[1] > tmin[0]){
        tmin[0] = tmin[1];
    }
    if(tmax[1] < tmax[0]){
        tmax[0] = tmax[1];
    }

    if(tmin[0] > tmax[2] || tmin[2] > tmax[0]){
        return false;
    }

    return true;
}

// Compute the smallest box that contains both *this and bb.
Box Box::Union(const Box& bb) const
{
    Box box;
    TODO;
    return box;
}

// Enlarge this box (if necessary) so that pt also lies inside it.
void Box::Include_Point(const vec3& pt)
{
    // TODO;

    for(unsigned i = 0; i < 3; i++){ // Compute if pt's inside the box for x, y, and z
        if(lo[i] > pt[i]){
            lo[i] = pt[i];
        }
        if(hi[i] < pt[i]){
            hi[i] = pt[i];
        }
    }
}

// Create a box to which points can be correctly added using Include_Point.
void Box::Make_Empty()
{
    lo.fill(std::numeric_limits<double>::infinity());
    hi=-lo;
}
