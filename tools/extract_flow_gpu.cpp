#include <cmd_utils.h>
#include "image_writers.h"
#include "file_utils.h"
#include "dense_flow.h"

INITIALIZE_EASYLOGGINGPP

using namespace std;
using namespace cv::gpu;
using namespace boost::filesystem;

int main(int argc, char** argv){
	// IO operation
	const char* keys =
		{
      "{ H  | help         | false   | print help message}"
			"{ f  | vidFile      | ex2.avi | filename of video }"
			"{ x  | xFlowFile    | flow_x | filename of flow x component }"
			"{ y  | yFlowFile    | flow_y | filename of flow x component }"
			"{ i  | imgFile      | flow_i | filename of flow image}"
			"{ b  | bound | 15 | specify the maximum of optical flow}"
			"{ t  | type | 0 | specify the optical flow algorithm }"
			"{ d  | device_id    | 0  | set gpu id}"
			"{ s  | step  | 1 | specify the step for frame sampling}"
			"{ o  | out | zip | output style}"
			"{ w  | newWidth | 0 | output style}"
			"{ h  | newHeight | 0 | output style}"
		};

	CommandLineParser cmd(argc, argv, keys);

  PRINT_HELP_IF_FLAGGED(cmd);

	path vidFile = canonicalPath(cmd.get<string>("vidFile"));
	path xFlowFile = absolutePath(cmd.get<string>("xFlowFile"));
	path yFlowFile = absolutePath(cmd.get<string>("yFlowFile"));
	path imgFile = cmd.get<string>("imgFile");
	string output_style = cmd.get<string>("out");
	int bound = cmd.get<int>("bound");
  int type  = cmd.get<int>("type");
  int device_id = cmd.get<int>("device_id");
  int step = cmd.get<int>("step");
  int new_height = cmd.get<int>("newHeight");
  int new_width = cmd.get<int>("newWidth");

	vector<vector<uchar> > out_vec_x, out_vec_y, out_vec_img;

	CHECK_FILE_EXISTS_OR_EXIT(vidFile);
  cout << "Calculating optical flow of " << vidFile << endl;

	calcDenseFlowGPU(vidFile.string(), bound, type, step, device_id,
					 out_vec_x, out_vec_y, out_vec_img, new_width, new_height);

  writeFlow(output_style, out_vec_x, xFlowFile, "x_%05.jpg");
	writeFlow(output_style, out_vec_y, yFlowFile, "y_%05.jpg");
	writeFlow(output_style, out_vec_img, imgFile, "i_%05.jpg");

	return 0;
}

