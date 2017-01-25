#include "file_utils.h"

using namespace std;
using namespace boost::filesystem;

path canonicalPath(string path_str) {
  return canonical(path(path_str));
}

path absolutePath(string path_str) {
  return absolute(path(path_str));
}
