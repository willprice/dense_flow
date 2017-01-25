//
// Created by will on 25/01/17.
//

#ifndef DENSEFLOW_FILE_UTILS_H
#define DENSEFLOW_FILE_UTILS_H
#include <string>
#include <boost/filesystem.hpp>

#define CHECK_FILE_EXISTS_OR_EXIT(file) \
if (!boost::filesystem::exists(file)) { \
  std::cout << "Could not find file: " << file << std::endl; \
  return 1; \
}

boost::filesystem::path canonicalPath(std::string path);
boost::filesystem::path absolutePath(std::string path);

#endif //DENSEFLOW_FILE_UTILS_H
