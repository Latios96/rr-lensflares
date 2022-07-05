#ifndef RR_LENSFLARES_SRC_LENSSYSTEM_H_
#define RR_LENSFLARES_SRC_LENSSYSTEM_H_

#include <string>
#include <vector>

struct Lens {
    float curvatureRadius;
    float thickness;
    float ior;
    float apertureRadius;
    Lens(float curvatureRadius, float thickness, float ior, float apertureRadius);
};

struct LensSystem {
    std::string name;
    std::vector<Lens> lenses;
    LensSystem(const std::string &name, const std::vector<Lens> &lenses);
};



#endif //RR_LENSFLARES_SRC_LENSSYSTEM_H_
