#include <shapes/constant_medium.hpp>
#include <materials/isotropic.hpp>
#include <randomizer.hpp>
#include <constants.hpp>
#include <cmath>

constant_medium::constant_medium(
    std::shared_ptr<hittable> boundary, 
    double density, 
    const color& albedo,
    fog_distribution dist_type,
    double param1,
    double param2
) : boundary(boundary), 
    neg_inv_density(-1.0 / density),
    phase_function(std::make_shared<isotropic>(albedo)),
    distribution_type(dist_type),
    param1(param1),
    param2(param2) {}

double constant_medium::sample_exponential(double distance) const {
    // Physically correct Beer's Law attenuation
    // std::cout<<neg_inv_density * std::log(random_double())<<"\n";
    return neg_inv_density * std::log(random_double());
}

double constant_medium::sample_uniform(double distance) const {
    // Equal probability throughout volume
    // return random_double() * neg_inv_density * -1;
    // std::cout<<distance / 100<<"\n";
    double u = random_double();
    return u * neg_inv_density * -1;
}

double constant_medium::sample_linear(double distance) const {
    // Linear ramp: probability increases linearly with depth
    // P(x) = 2x/L^2, CDF = x^2/L^2
    double u = random_double();
    // return neg_inv_density * std::sqrt(u) * -1 * distance;

    return std::sqrt(u) * neg_inv_density * -1;
}

double constant_medium::sample_quadratic(double distance) const {
    // Quadratic falloff: P(x) = 3x^2/L^3
    // Inverse square-like falloff
    double u = random_double();
    return std::pow(u, 1.0/3.0) * neg_inv_density * -1;
}

double constant_medium::sample_gaussian(double distance) const {
    // Gaussian distribution centered at middle of volume
    // Using Box-Muller transform
    double u1 = random_double();
    double u2 = random_double();
    
    // Standard normal
    double z = std::sqrt(-2.0 * std::log(u1)) * std::cos(2.0 * PI * u2);
    
    // Scale to volume: mean = distance/2, stddev = distance/6
    double mean = distance / 2.0;
    double stddev = distance / 6.0;
    double sample = mean + z * stddev;
    
    // Clamp to volume bounds
    if (sample < 0) sample = 0;
    if (sample > distance) sample = distance;
    
    return sample * neg_inv_density * -1;
}

double constant_medium::sample_gamma(double distance) const {
    // Gamma distribution using Marsaglia and Tsang method
    // param1 = alpha (shape), param2 = beta (scale)
    double alpha = param1;
    double beta = param2;
    
    if (alpha < 1.0) {
        // For alpha < 1, use rejection method
        double u = random_double();
        return sample_gamma(distance) * std::pow(u, 1.0 / alpha);
    }
    
    double d = alpha - 1.0/3.0;
    double c = 1.0 / std::sqrt(9.0 * d);
    
    while (true) {
        double x, v;
        do {
            double u1 = random_double();
            double u2 = random_double();
            x = std::sqrt(-2.0 * std::log(u1)) * std::cos(2.0 * PI * u2);
            v = 1.0 + c * x;
        } while (v <= 0);
        
        v = v * v * v;
        double u = random_double();
        
        if (u < 1.0 - 0.0331 * x * x * x * x)
            return (d * v * beta / distance) * distance * neg_inv_density * -1;
        
        if (std::log(u) < 0.5 * x * x + d * (1.0 - v + std::log(v)))
            return (d * v * beta / distance) * distance * neg_inv_density * -1;
    }
}

bool constant_medium::hit(const ray& r, interval ray_t, hit_record& rec) const {
    hit_record rec1, rec2;

    // Find where ray enters the boundary
    if (!boundary->hit(r, interval(-INF, INF), rec1))
        return false;

    // Find where ray exits the boundary
    if (!boundary->hit(r, interval(rec1.t + 0.0001, INF), rec2))
        return false;

    // Clip to ray interval
    if (rec1.t < ray_t.min) rec1.t = ray_t.min;
    if (rec2.t > ray_t.max) rec2.t = ray_t.max;

    if (rec1.t >= rec2.t)
        return false;

    if (rec1.t < 0)
        rec1.t = 0;

    double ray_length = r.direction().length();
    double distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
    
    // Sample based on distribution type
    double hit_distance;
    switch (distribution_type) {
        case fog_distribution::EXPONENTIAL:
            hit_distance = sample_exponential(distance_inside_boundary);
            break;
        case fog_distribution::UNIFORM:
            hit_distance = sample_uniform(distance_inside_boundary);
            break;
        case fog_distribution::LINEAR:
            hit_distance = sample_linear(distance_inside_boundary);
            break;
        case fog_distribution::QUADRATIC:
            hit_distance = sample_quadratic(distance_inside_boundary);
            break;
        case fog_distribution::GAUSSIAN:
            hit_distance = sample_gaussian(distance_inside_boundary);
            break;
        case fog_distribution::GAMMA:
            hit_distance = sample_gamma(distance_inside_boundary);
            break;
        default:
            hit_distance = sample_exponential(distance_inside_boundary);
    }

    // Check if scatter occurs within the volume
    if (hit_distance > distance_inside_boundary)
        return false;

    rec.t = rec1.t + hit_distance / ray_length;
    rec.p = r.at(rec.t);

    rec.normal = vec3(1, 0, 0);
    rec.front_face = true;
    rec.mat = phase_function;

    return true;
}