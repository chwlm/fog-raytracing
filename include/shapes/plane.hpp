#ifndef PLANE_HPP
#define PLANE_HPP

#include <objects/hittable.hpp>
#include <objects/vec3.hpp>
#include <objects/ray.hpp>
#include <objects/interval.hpp>
#include <objects/hit_record.hpp>
#include <materials/base.hpp>
#include <memory>

class plane : public hittable {
public:
    point3 point;
    vec3 normal;
    std::shared_ptr<material> mat;

    // Constructor with point, normal, and material
    plane(point3 _point, vec3 _normal, std::shared_ptr<material> _material);

    bool hit(const ray& r, interval ray_interval, hit_record& rec) const override;
};

#endif