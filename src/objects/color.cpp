#include <cmath>

#include <objects/interval.hpp>
#include <objects/color.hpp>
#include <objects/vec3.hpp>

// color utility function definitions
double linear_to_gamma(double linear) {
  if(linear > 0) {
    return std::sqrt(linear);
  }
  return 0;
}

color get_color_byte(color c) {
  // Gamma correction
  double r = linear_to_gamma(c.x());
  double g = linear_to_gamma(c.y());
  double b = linear_to_gamma(c.z());

  // Clamp to [0, 0.999] to avoid overflow when scaling
  r = interval(0.0, 0.999).clamp(r);
  g = interval(0.0, 0.999).clamp(g);
  b = interval(0.0, 0.999).clamp(b);

  // Scale to [0, 255]
  return color(
    static_cast<int>(256 * r),
    static_cast<int>(256 * g),
    static_cast<int>(256 * b)
  );
}