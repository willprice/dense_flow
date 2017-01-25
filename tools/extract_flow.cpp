#include "dense_flow.h"
#include <boost/filesystem.hpp>
#include <file_utils.h>
#include <cmd_utils.h>
#include "image_writers.h"
#include "zip_utils.h"


INITIALIZE_EASYLOGGINGPP

using namespace boost::filesystem;
using namespace std;

int main(int argc, char** argv)
{
	// IO operation

	const char* keys =
		{
      "{ h  | help         | false   | print help message}"
			"{ f  | vidFile      | ex2.avi | filename of video }"
			"{ x  | xFlowFile    | flow_x  | filename of flow x component }"
			"{ y  | yFlowFile    | flow_y  | filename of flow x component }"
			"{ i  | imgFile      | flow_i  | filename of flow image}"
			"{ b  | bound        | 15      | specify the maximum of optical flow}"
			"{ o  | out          | zip     | output style}"
		};

	CommandLineParser cmd(argc, argv, keys);

  PRINT_HELP_IF_FLAGGED(cmd);

	path vidFile = canonicalPath(cmd.get<string>("vidFile"));
	path xFlowFile = absolutePath(cmd.get<string>("xFlowFile"));
	path yFlowFile = absolutePath(cmd.get<string>("yFlowFile"));
	string imgFile = cmd.get<string>("imgFile");
	string output_style = cmd.get<string>("out");
	int bound = cmd.get<int>("bound");

	vector<vector<uchar> > out_vec_x, out_vec_y, out_vec_img;

  CHECK_FILE_EXISTS_OR_EXIT(vidFile);

	cout << "Calculating optical flow of " << vidFile << endl;
	calcDenseFlow(vidFile.string(), bound, 0, 1,
					 out_vec_x, out_vec_y, out_vec_img);

	writeFlow(output_style, out_vec_x, xFlowFile, "x_%05.jpg");
	writeFlow(output_style, out_vec_y, yFlowFile, "y_%05.jpg");
	writeFlow(output_style, out_vec_img, imgFile, "i_%05.jpg");

	return 0;
}

