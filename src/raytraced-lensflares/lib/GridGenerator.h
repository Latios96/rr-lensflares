#ifndef RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GRIDGENERATOR_H_
#define RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GRIDGENERATOR_H_

#include "Mesh.h"

class GridGenerator {
public:
  void generateGrid(Mesh &mesh, int subdivs);

private:
  void generatePoints(Mesh &mesh, int subdivs);
  void generateIndices(Mesh &mesh, int subdivs);
};

#endif // RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GRIDGENERATOR_H_
