#ifndef ISOTROPIC_HPP
#define ISOTROPIC_HPP

#include <materials/base.hpp>
#include <objects/color.hpp>
#include <objects/ray.hpp>
#include <objects/hit_record.hpp>

class isotropic : public material {
public:
    isotropic(const color& albedo);
    
    bool scatter(
        const ray& r_in, 
        const hit_record& rec, 
        color& attenuation, 
        ray& scattered
    ) const override;

private:
    color albedo;
};

#endif