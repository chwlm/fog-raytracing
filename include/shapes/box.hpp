#ifndef BOX_HPP
#define BOX_HPP

#include <objects/hittable.hpp>
#include <objects/vec3.hpp>
#include <objects/ray.hpp>
#include <objects/interval.hpp>
#include <objects/hit_record.hpp>
#include <materials/base.hpp>
#include <memory>

class box : public hittable {
public:
    point3 box_min;
    point3 box_max;
    std::shared_ptr<material> mat;

    // Constructor with two opposite corners and material
    box(const point3& _min, const point3& _max, std::shared_ptr<material> _material);

    bool hit(const ray& r, interval ray_interval, hit_record& rec) const override;

private:
    // Helper function to compute normal at a hit point
    vec3 get_normal(const point3& p) const;
};

#endif