#include "mesh.h"
#include <fstream>
#include <string>
#include <limits>
#include <cfloat>
#include <algorithm>

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e;
    vec3 v;
    box.Make_Empty();
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
            box.Include_Point(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }
    }
    number_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{
    // TODO;

    Hit h;
    h.object = NULL;

    double dist;

    if(part < 0){ // All Parts
        double closest_dist = DBL_MAX;

        for(unsigned i = 0; i < triangles.size(); i++){
            if(Intersect_Triangle(ray, i, dist)){
                if(dist < closest_dist){ // Only send the first part intersected
                    h.object = this;
                    h.dist = dist;
                    h.part = i;
                    closest_dist = dist;
                }
            }
        }
    }
    else{ // Specific part
        if(Intersect_Triangle(ray, part, dist)){
            h.object = this;
            h.dist = dist;
            h.part = part;
        }
    }

    return h;
}

// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const vec3& point, int part) const
{
    assert(part>=0);
    // TODO;

    vec3 normal;
    ivec3 tri = triangles[part];
    vec3 a = vertices[tri[0]];
    vec3 b = vertices[tri[1]];
    vec3 c = vertices[tri[2]];

    vec3 ab = b - a;
    vec3 ac = c - a;

    normal = cross(ab, ac).normalized();

    return normal;
}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.
bool Mesh::Intersect_Triangle(const Ray& ray, int part, double& dist) const
{
    // TODO;
    bool intersection = false;

    ivec3 tri = triangles[part]; 
    vec3 a = vertices[tri[0]];
    vec3 b = vertices[tri[1]];
    vec3 c = vertices[tri[2]];

    vec3 ab = b - a;
    vec3 ac = c - a;

    vec3 u = ray.direction.normalized();

    vec3 ra = ray.endpoint - a;

    double denominator = dot(cross(u, ac), ab);
    double t = -dot(cross(ab, ac), ra) / dot(cross(ab, ac), u);

    if(t > small_t && denominator != 0){
        double bw1 = dot(cross(ab, u), ra) / denominator;
        double bw2 = dot(cross(u, ac), ra) / denominator;

        if(bw1 > weight_tolerance && bw2 > weight_tolerance && (1 - bw1 - bw2) > weight_tolerance){
            intersection = true;
            dist = t;
        }
    } 

    return intersection;
}

// Compute the bounding box.  Return the bounding box of only the triangle whose
// index is part.
Box Mesh::Bounding_Box(int part) const
{
    Box box;
    // TODO;

    if(part < 0){
        vec3 lo, hi;

        for(unsigned i = 0; i < triangles.size(); i++){
            ivec3 tri = triangles[i]; 
            vec3 a = vertices[tri[0]];
            vec3 b = vertices[tri[1]];
            vec3 c = vertices[tri[2]];
            for(unsigned j = 0; j < 3; j++){
                lo[j] = std::min({a[j], b[j], c[j], lo[j]});
                hi[j] = std::max({a[j], b[j], c[j], lo[j]});
            }
        }
    }
    else{
        ivec3 tri = triangles[part]; 
        vec3 a = vertices[tri[0]];
        vec3 b = vertices[tri[1]];
        vec3 c = vertices[tri[2]];

        vec3 lo, hi;
        for(unsigned i = 0; i < 3; i++){
            lo[i] = std::min({a[i], b[i], c[i]});
            hi[i] = std::max({a[i], b[i], c[i]});
        }

        box.lo = lo;
        box.hi = hi;
    }

    return box;
}
