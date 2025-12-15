#ifndef CONSTANT_MEDIUM_HPP
#define CONSTANT_MEDIUM_HPP

#include <objects/hittable.hpp>
#include <objects/interval.hpp>
#include <objects/ray.hpp>
#include <objects/hit_record.hpp>
#include <objects/color.hpp>
#include <memory>

enum class fog_distribution {
    EXPONENTIAL,    // Physically correct (Beer's Law)
    UNIFORM,        // Equal probability throughout
    LINEAR,         // Linear ramp from entry to exit
    QUADRATIC,      // Quadratic falloff
    GAUSSIAN,       // Gaussian distribution centered in volume
    GAMMA           // Gamma distribution (adjustable shape)
};

class constant_medium : public hittable {
public:
    constant_medium(
        std::shared_ptr<hittable> boundary, 
        double density, 
        const color& albedo,
        fog_distribution dist_type = fog_distribution::EXPONENTIAL,
        double param1 = 2.0,  // For gamma: shape parameter (alpha)
        double param2 = 1.0   // For gamma: scale parameter (beta)
    );
    
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

private:
    std::shared_ptr<hittable> boundary;
    double neg_inv_density;
    std::shared_ptr<material> phase_function;
    fog_distribution distribution_type;
    double param1, param2;
    
    // Distribution sampling functions
    double sample_exponential(double distance) const;
    double sample_uniform(double distance) const;
    double sample_linear(double distance) const;
    double sample_quadratic(double distance) const;
    double sample_gaussian(double distance) const;
    double sample_gamma(double distance) const;
};

#endif