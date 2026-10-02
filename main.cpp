#include "rtweekend.h"

#include "Objects/camera.h"
#include "Objects/hittable.h"
#include "Objects/hittablelist.h"
#include "Objects/sphere.h"

int main()
{
	HittableList world;
	world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));
	world.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0));

	Camera camera;

	camera.aspectRatio = 16.0 / 9.0;
	camera.imageWidth = 400;
	camera.samplesPerPixel = 100;

	camera.Render(world);
}