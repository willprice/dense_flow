//
// Created by will on 25/01/17.
//

#ifndef DENSEFLOW_IMAGE_WRITERS_H
#define DENSEFLOW_IMAGE_WRITERS_H
#include <vector>
#include <string>
#include <opencv2/core.hpp>
#include <boost/filesystem.hpp>



void writeImages(std::vector<std::vector<uchar>> images, std::string name_temp);
void writeFlow(std::string output_style, std::vector<std::vector<uchar>> out_vec,
               boost::filesystem::path output_path, std::string file_formatting);


#endif //DENSEFLOW_IMAGE_WRITERS_H
