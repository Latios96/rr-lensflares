#ifndef RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_TESTS_GLMCATCHUTILS_H_
#define RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_TESTS_GLMCATCHUTILS_H_

#include "GlmUtils.h"
#include <catch2/catch_all.hpp>
#include <catch2/catch_tostring.hpp>
#include <fmt/format.h>
#include <glm/vec3.hpp>

namespace Catch {
template <> struct StringMaker<glm::vec3> {
  static std::string convert(glm::vec3 const &value) { return fmt::format("{}", value); }
};
} // namespace Catch*/

#endif // RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_TESTS_GLMCATCHUTILS_H_
