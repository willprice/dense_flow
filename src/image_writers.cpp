#include <opencv2/core/types_c.h>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <zip_utils.h>
#include "image_writers.h"

using namespace std;
using namespace boost::filesystem;

void writeImages(vector<vector<uchar>> images, string name_temp){
  for (int i = 0; i < images.size(); ++i){
    char tmp[256];
    sprintf(tmp, "_%05d.jpg", i+1);
    FILE* fp;
    fp = fopen((name_temp + tmp).c_str(), "wb");
    fwrite( images[i].data(), 1, images[i].size(), fp);
    fclose(fp);
  }
}


void writeFlow(string output_style, vector<vector<uchar>> out_vec, path output_path, string file_formatting) {
  if (output_style == "dir") {
    writeImages(out_vec, output_path.string());
  }else {
    writeZipFile(out_vec, file_formatting, output_path.replace_extension(".zip").string());
  }
}
