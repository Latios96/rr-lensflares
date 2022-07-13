#ifndef RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_UTILS_H_
#define RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_UTILS_H_

#include <spdlog/spdlog.h>
#include <string>

class Utils {
public:
  template <typename T> static void logAndThrow(const std::string &message) {
    spdlog::error(message);
    throw T(message);
  }
};

#endif // RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_UTILS_H_
