#include <shapes/box.hpp>
#include <algorithm>
#include <cmath>

box::box(const point3& _min, const point3& _max, std::shared_ptr<material> _material)
    : box_min(_min), box_max(_max), mat(_material) {
    // Ensure min is actually minimum and max is maximum
    point3 true_min(
        std::min(_min.x(), _max.x()),
        std::min(_min.y(), _max.y()),
        std::min(_min.z(), _max.z())
    );
    point3 true_max(
        std::max(_min.x(), _max.x()),
        std::max(_min.y(), _max.y()),
        std::max(_min.z(), _max.z())
    );
    box_min = true_min;
    box_max = true_max;
}

bool box::hit(const ray& r, interval ray_interval, hit_record& rec) const {
    // AABB (Axis-Aligned Bounding Box) ray intersection
    // Using slab method
    
    double tmin = ray_interval.min;
    double tmax = ray_interval.max;
    
    for (int a = 0; a < 3; a++) {
        double invD = 1.0 / r.direction()[a];
        double t0 = (box_min[a] - r.origin()[a]) * invD;
        double t1 = (box_max[a] - r.origin()[a]) * invD;
        
        if (invD < 0.0)
            std::swap(t0, t1);
        
        tmin = t0 > tmin ? t0 : tmin;
        tmax = t1 < tmax ? t1 : tmax;
        
        if (tmax <= tmin)
            return false;
    }
    
    // We have a valid intersection
    rec.t = tmin;
    rec.p = r.at(rec.t);
    rec.mat = mat;
    
    // Determine which face was hit and set normal
    vec3 outward_normal = get_normal(rec.p);
    rec.set_face_normal(r, outward_normal);
    
    return true;
}

vec3 box::get_normal(const point3& p) const {
    // Determine which face the point is on by finding the closest face
    const double epsilon = 1e-4;
    
    // Check each face
    if (std::fabs(p.x() - box_min.x()) < epsilon)
        return vec3(-1, 0, 0);
    if (std::fabs(p.x() - box_max.x()) < epsilon)
        return vec3(1, 0, 0);
    
    if (std::fabs(p.y() - box_min.y()) < epsilon)
        return vec3(0, -1, 0);
    if (std::fabs(p.y() - box_max.y()) < epsilon)
        return vec3(0, 1, 0);
    
    if (std::fabs(p.z() - box_min.z()) < epsilon)
        return vec3(0, 0, -1);
    if (std::fabs(p.z() - box_max.z()) < epsilon)
        return vec3(0, 0, 1);
    
    // Default (shouldn't happen)
    return vec3(0, 1, 0);
}