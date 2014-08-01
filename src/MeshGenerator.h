#pragma once

#include <memory>
#include <Mesh.h>

namespace Acidrain {

struct MeshGenerator {
    static std::shared_ptr<Mesh> cube();
    static std::shared_ptr<Mesh> sphere(int longitudePoints, int latitudePoints);
    static std::shared_ptr<Mesh> grid(int xSegments, int ySegments);
};

} // namespace Acidrain
