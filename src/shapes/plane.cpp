#include <shapes/plane.hpp>
#include <cmath>

plane::plane(point3 _point, vec3 _normal, std::shared_ptr<material> _material)
    : point(_point), normal(unit_vector(_normal)), mat(_material) {}

bool plane::hit(const ray& r, interval ray_interval, hit_record& rec) const {
    // Ray-plane intersection: (P - P0) · N = 0
    // P = ray.origin + t * ray.direction
    // Solving for t: t = (P0 - ray.origin) · N / (ray.direction · N)
    
    double denom = dot(r.direction(), normal);
    
    // Check if ray is parallel to plane (or nearly parallel)
    if (std::fabs(denom) < 1e-8)
        return false;
    
    double t = dot(point - r.origin(), normal) / denom;
    
    // Check if intersection is within valid interval
    if (!ray_interval.contains(t))
        return false;
    
    // Set hit record
    rec.t = t;
    rec.p = r.at(t);
    rec.mat = mat;
    rec.set_face_normal(r, normal);
    
    return true;
}