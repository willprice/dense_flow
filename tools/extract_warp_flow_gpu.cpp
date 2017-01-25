#include "dense_flow.h"
#include "zip_utils.h"
#include <boost/filesystem.hpp>
#include <image_writers.h>
#include <file_utils.h>
#include <cmd_utils.h>

INITIALIZE_EASYLOGGINGPP

using namespace std;
using namespace boost::filesystem;
using namespace cv::gpu;

int main(int argc, char** argv){
	// IO operation
	const char* keys =
		{
      "{ h  | help         | false   | print help message}"
			"{ f  | vidFile      | ex2.avi | filename of video }"
			"{ x  | xFlowFile    | flow_x | filename of flow x component }"
			"{ y  | yFlowFile    | flow_y | filename of flow x component }"
			"{ b  | bound | 15 | specify the maximum of optical flow}"
			"{ t  | type | 0 | specify the optical flow algorithm }"
			"{ d  | device_id    | 0  | set gpu id}"
			"{ s  | step  | 1 | specify the step for frame sampling}"
			"{ o  | out | zip | output style}"
		};

	CommandLineParser cmd(argc, argv, keys);

	PRINT_HELP_IF_FLAGGED(cmd);

	path vidFile = canonicalPath(cmd.get<string>("vidFile"));
	path xFlowFile = absolutePath(cmd.get<string>("xFlowFile"));
	path yFlowFile = absolutePath(cmd.get<string>("yFlowFile"));
	string output_style = cmd.get<string>("out");
	int bound = cmd.get<int>("bound");
  int type  = cmd.get<int>("type");
  int device_id = cmd.get<int>("device_id");
  int step = cmd.get<int>("step");

	vector<vector<uchar> > out_vec_x, out_vec_y;

  CHECK_FILE_EXISTS_OR_EXIT(vidFile);

  cout << "Calculating optical flow of " << vidFile << endl;
	calcDenseWarpFlowGPU(vidFile.string(), bound, type, step, device_id,
					 out_vec_x, out_vec_y);

	writeFlow(output_style, out_vec_x, xFlowFile, "x_%05d.jpg");
	writeFlow(output_style, out_vec_y, yFlowFile, "y_%05d.jpg");

	return 0;
}
