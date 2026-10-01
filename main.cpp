#include "RTWeekend.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

#include "Ray.h"
#include "Color.h"
#include "Vec3.h"

#include <iostream>


Color RayColor(const Ray& ray, const Hittable& world)
{
    HitRecord hitRecord;
    if (world.Hit(ray, Interval(0.0, Infinity), hitRecord))
    {
        return 0.5 * (hitRecord.Normal + Color(1.0, 1.0, 1.0));
    }

    Vec3 unitDirection = UnitVector(ray.Direction());
    auto a = 0.5 * (unitDirection.Y() + 1.0);

    return (1.0 - a) * Color(1.0, 1.0, 1.0)
        + a * Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image

    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;

    // Calculate the image height, and ensure that it's at least 1
    int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // World

    HittableList world;
    world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0));

    // Camera

    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);
    auto cameraCenter = Point3(0.0, 0.0, 0.0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges
    auto viewportU = Vec3(viewportWidth, 0.0, 0.0);
    auto viewportV = Vec3(0.0, -viewportHeight, 0.0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel
    auto pixelDeltaU = viewportU / imageWidth;
    auto pixelDeltaV = viewportV / imageHeight;

    // Calculate the location of the upper left pixel
    auto viewportUpperLeft =
        cameraCenter
        - Vec3(0.0, 0.0, focalLength)
        - viewportU / 2.0
        - viewportV / 2.0;

    auto pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    // Render

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int scanlineIndex = 0; scanlineIndex < imageHeight; scanlineIndex++)
    {
        std::clog
            << "\rScanlines remaining: "
            << (imageHeight - scanlineIndex)
            << ' '
            << std::flush;

        for (int pixelIndex = 0; pixelIndex < imageWidth; pixelIndex++)
        {
            auto pixelCenter =
                pixel00Location
                + (pixelIndex * pixelDeltaU)
                + (scanlineIndex * pixelDeltaV);

            auto rayDirection = pixelCenter - cameraCenter;
            Ray ray(cameraCenter, rayDirection);

            Color pixelColor = RayColor(ray, world);
            WriteColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
}
