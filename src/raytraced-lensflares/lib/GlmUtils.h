#ifndef RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GLMUTILS_H_
#define RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GLMUTILS_H_

#include <fmt/format.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

template <> struct fmt::formatter<glm::vec3> {
  template <typename ParseContext> constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

  template <typename FormatContext> auto format(glm::vec3 const &vec, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "({},{},{})", vec.x, vec.y, vec.z);
  };
};

template <> struct fmt::formatter<glm::vec2> {
  template <typename ParseContext> constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

  template <typename FormatContext> auto format(glm::vec2 const &vec, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "({},{})", vec.x, vec.y);
  };
};

#endif // RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GLMUTILS_H_
