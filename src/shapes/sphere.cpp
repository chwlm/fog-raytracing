#include <cmath>

#include <shapes/sphere.hpp>

#include <objects/color.hpp>
#include <objects/interval.hpp>
#include <objects/hit_record.hpp>
#include <objects/vec3.hpp>

bool sphere::hit(const ray& r, interval ray_interval, hit_record& rec) const {
  vec3 oc = r.origin() - center;
  auto a = dot(r.direction(), r.direction());
  auto half_b = dot(oc, r.direction());
  auto c = dot(oc, oc) - radius*radius;

  auto discriminant = half_b*half_b - a*c;
  if (discriminant < 0) return false;
  auto sqrt_d = std::sqrt(discriminant);

  // Find nearest root in range
  auto root = (-half_b - sqrt_d) / a;
  if (!ray_interval.surrounds(root)) {
    root = (-half_b + sqrt_d) / a;
    if (!ray_interval.surrounds(root))
      return false;
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  vec3 outward_normal = (rec.p - center) / radius;
  rec.set_face_normal(r, outward_normal);
  rec.mat = mat;

  return true;
}