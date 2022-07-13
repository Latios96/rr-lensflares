#include "Utils.h"

#include <whereami.h>

std::filesystem::path Utils::getExecutableDirectory() {
  int length = wai_getExecutablePath(nullptr, 0, nullptr);
  std::string executablePathStr;
  executablePathStr.resize(length);
  wai_getExecutablePath(executablePathStr.data(), length, nullptr);
  auto executablePath = std::filesystem::path(executablePathStr);
  auto executableDirectory = executablePath.parent_path();
  return executableDirectory;
}
