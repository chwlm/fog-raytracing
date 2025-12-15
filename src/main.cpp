#include <iostream>
#include <memory>

#include <objects/camera.hpp>
#include <objects/color.hpp>
#include <objects/hittable.hpp>

#include <shapes/sphere.hpp>
#include <shapes/plane.hpp>
#include <shapes/box.hpp>
#include <shapes/constant_medium.hpp>

#include <materials/lambertian.hpp>
#include <materials/metal.hpp>

signed main() {
  hittable_list world;

  auto material_ground = std::make_shared<lambertian>(color(0.11, 0.14, 0.22));
  std::vector<std::shared_ptr<lambertian>> material_center = {
    std::make_shared<lambertian>(color(0.9, 0.1, 0.1)),
    std::make_shared<lambertian>(color(0.3, 0.7, 0.3)),
    std::make_shared<lambertian>(color(0.0, 0.2, 0.4)),
    std::make_shared<lambertian>(color(0.1, 0.1, 0.1)),
    std::make_shared<lambertian>(color(0.9, 0.9, 0.9))
  };
  auto material_side = std::make_shared<metal>(color(0.4, 0.4, 0.4), 0.1);
  auto material_box_1 = std::make_shared<lambertian>(color(0.2, 0.8, 0.3));
  auto material_box_2 = std::make_shared<lambertian>(color(0.6, 0.6, 0.3));
  auto material_box_3 = std::make_shared<lambertian>(color(1.0, 0.2, 1.0));
  // auto material_box_3 = std::make_shared<metal>(color(0.4, 0.4, 0.4), 0.04);
  auto material_box_4 = std::make_shared<lambertian>(color(1.0, 1.0, 0.1));
  auto material_box_5 = std::make_shared<lambertian>(color(0.1, 1.0, 1.0));
  // auto material_box_5 = std::make_shared<metal>(color(0.4, 0.4, 0.4), 0.01);

  world.add(std::make_shared<plane>(
      point3(0, -0.5, 0),      // Point on plane
      vec3(0, 1, 0),           // Normal pointing up
      material_ground
  ));

  std::vector<std::tuple<point3, float, int>> sphere_data = {
    std::make_tuple(point3( 12.44, 0, -5.31 ), 1.47, 2),
    std::make_tuple(point3( -37.18, 0, -12.77 ), 0.82, 2),
    std::make_tuple(point3( 48.92, 0, -0.44 ), 1.93, 0),
    std::make_tuple(point3( -22.06, 0, -28.19 ), 0.58, 4),
    std::make_tuple(point3( 7.58, 0, -9.02 ), 1.12, 1),
    std::make_tuple(point3( -11.93, 0, -15.41 ), 0.74, 3),
    std::make_tuple(point3( 33.27, 0, -29.55 ), 1.66, 3),
    std::make_tuple(point3( -4.12, 0, -7.88 ), 1.04, 2),
    std::make_tuple(point3( 25.63, 0, -2.19 ), 0.39, 1),
    std::make_tuple(point3( -46.77, 0, -23.93 ), 1.88, 0),
    std::make_tuple(point3( 14.09, 0, -19.44 ), 1.21, 4),
    std::make_tuple(point3( -28.31, 0, -1.15 ), 0.55, 1),
    std::make_tuple(point3( 6.72, 0, -26.48 ), 1.79, 3),
    std::make_tuple(point3( 41.28, 0, -14.07 ), 0.96, 2),
    std::make_tuple(point3( -33.69, 0, -4.62 ), 0.33, 4),
    std::make_tuple(point3( 19.34, 0, -8.11 ), 1.58, 0),
    std::make_tuple(point3( -2.49, 0, -29.02 ), 1.09, 0),
    std::make_tuple(point3( 9.18, 0, -6.73 ), 0.71, 4),
    std::make_tuple(point3( 27.54, 0, -3.08 ), 1.42, 1),
    std::make_tuple(point3( -14.88, 0, -11.29 ), 0.84, 2),
    std::make_tuple(point3( 1.67, 0, -27.95 ), 1.36, 3),
    std::make_tuple(point3( -49.56, 0, -17.62 ), 0.49, 4),
    std::make_tuple(point3( 38.11, 0, -22.01 ), 1.25, 2),
    std::make_tuple(point3( -8.43, 0, -5.90 ), 0.62, 0),
    std::make_tuple(point3( 12.99, 0, -14.37 ), 1.97, 3),
    std::make_tuple(point3( -21.72, 0, -2.56 ), 0.44, 1),
    std::make_tuple(point3( 47.66, 0, -28.82 ), 1.52, 1),
    std::make_tuple(point3( -35.20, 0, -9.24 ), 1.08, 0),
    std::make_tuple(point3( 24.44, 0, -1.33 ), 0.67, 3),
    std::make_tuple(point3( -17.05, 0, -20.77 ), 1.83, 4),
    std::make_tuple(point3( 8.83, 0, -12.08 ), 1.14, 2),
    std::make_tuple(point3( -6.67, 0, -29.78 ), 0.91, 2),
    std::make_tuple(point3( 29.10, 0, -4.21 ), 1.73, 3),
    std::make_tuple(point3( -46.15, 0, -25.17 ), 0.37, 4),
    std::make_tuple(point3( 16.71, 0, -10.92 ), 1.60, 1),
    std::make_tuple(point3( -31.39, 0, -18.45 ), 0.46, 0),
    std::make_tuple(point3( 5.62, 0, -7.19 ), 1.30, 3),
    std::make_tuple(point3( 43.18, 0, -1.72 ), 1.02, 1),
    std::make_tuple(point3( -22.50, 0, -24.64 ), 0.79, 0),
    std::make_tuple(point3( 10.04, 0, -3.57 ), 1.95, 2),
    std::make_tuple(point3( -4.98, 0, -16.71 ), 1.19, 4),
    std::make_tuple(point3( 28.47, 0, -8.74 ), 0.53, 4),
    std::make_tuple(point3( -39.91, 0, -11.53 ), 1.68, 3),
    std::make_tuple(point3( 20.28, 0, -29.90 ), 0.88, 1),
    std::make_tuple(point3( -13.24, 0, -6.33 ), 0.35, 0),
    std::make_tuple(point3( 32.76, 0, -27.61 ), 1.50, 2),
    std::make_tuple(point3( -28.89, 0, -14.01 ), 1.07, 0),
    std::make_tuple(point3( 3.41, 0, -2.39 ), 0.76, 2),
    std::make_tuple(point3( -44.30, 0, -21.77 ), 1.40, 4),
    std::make_tuple(point3( 18.96, 0, -0.97 ), 0.81f, 3)
  };

  for(int i=0;i<sphere_data.size();i++){
    auto p = std::get<0>(sphere_data[i]);  // point3
    auto s = std::get<1>(sphere_data[i]);  // float
    auto m = std::get<2>(sphere_data[i]);  // int
    world.add(std::make_shared<sphere>(p, s, material_center[m]));
  }

  world.add(std::make_shared<box>(point3(-1, -0.5, -3), point3(-0.2, 0.3, -2.2), material_box_1));
  world.add(std::make_shared<box>(point3(-5, -0.5, -3), point3(-3, 1.5, -2), material_box_2));
  world.add(std::make_shared<box>(point3(3, -0.5, 1), point3(4, 0.7, 2), material_box_3));
  world.add(std::make_shared<box>(point3(-8, -0.5, -7), point3(-8.5, 2, 7.5), material_box_4));
  world.add(std::make_shared<box>(point3(8, -0.5, -14), point3(16, 8, -18), material_box_5));


  // Dummy material for fog boundary
  auto dummy_material = std::make_shared<lambertian>(color(1, 1, 1));
  
  // CHOOSE ONE FOG TYPE:
  
  // // 1. Exponential (physically correct, Beer's Law)
  // auto fog_boundary = std::make_shared<sphere>(point3(0, 0, -1), 50, dummy_material);
  // world.add(std::make_shared<constant_medium>(fog_boundary, 0.005, color(0.8, 0.8, 0.9), 
  //     fog_distribution::EXPONENTIAL));
  
  // // 2. Uniform (equal probability everywhere)
  // auto fog_boundary = std::make_shared<sphere>(point3(0, 0, -1), 50, dummy_material);
  // world.add(std::make_shared<constant_medium>(fog_boundary, 0.02, color(0.8, 0.8, 0.9), 
  //     fog_distribution::UNIFORM));
  
  // // 3. Linear ramp (increases with depth)
  // auto fog_boundary = std::make_shared<sphere>(point3(0, 0, -1), 50, dummy_material);
  // world.add(std::make_shared<constant_medium>(fog_boundary, 0.02, color(0.8, 0.8, 0.9), 
  //     fog_distribution::LINEAR));
  
  // // 4. Quadratic (faster falloff than exponential)
  // auto fog_boundary = std::make_shared<sphere>(point3(0, 0, -1), 50, dummy_material);
  // world.add(std::make_shared<constant_medium>(fog_boundary, 0.02, color(0.8, 0.8, 0.9), 
  //     fog_distribution::QUADRATIC));
  
  // // 5. Gaussian (concentrated in center)
  // auto fog_boundary = std::make_shared<sphere>(point3(0, 0, -1), 50, dummy_material);
  // world.add(std::make_shared<constant_medium>(fog_boundary, 0.1, color(0.8, 0.8, 0.9), 
  //     fog_distribution::GAUSSIAN));
  
  // // 6. Gamma (flexible shape)
  // auto fog_boundary = std::make_shared<sphere>(point3(0, 0, -1), 50, dummy_material);
  // world.add(std::make_shared<constant_medium>(fog_boundary, 0.02, color(0.8, 0.8, 0.9), 
  //     fog_distribution::GAMMA, 2.0, 1.0));  // alpha=1.0, beta=1.0

  camera cam("./images/out.ppm");

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1024;
  cam.max_depth = 30;
  cam.samples_per_pixel = 10;

  cam.render(world);

  std::cout << "\nImage rendered to ./images/out.ppm" << std::endl;
  
  return 0;
}