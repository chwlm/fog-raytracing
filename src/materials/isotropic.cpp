#include <materials/isotropic.hpp>
#include <randomizer.hpp>

isotropic::isotropic(const color& albedo) : albedo(albedo) {}

bool isotropic::scatter(
    const ray& r_in, 
    const hit_record& rec, 
    color& attenuation, 
    ray& scattered
) const {
    scattered = ray(rec.p, random_unit_vector());
    attenuation = albedo;
    return true;
}