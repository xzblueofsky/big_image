/*
 * =====================================================================================
 *
 *       Filename:  big_image.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年06月27日 15时27分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  XinZhao (zx), xinzhao@deepglint.com
 *        Company:  DeepGlint
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace cv;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
	    DIR *dp;
	    struct dirent *dirp;
	    if((dp  = opendir(dir.c_str())) == NULL) {
	        cout << "Error(" << errno << ") opening " << dir << endl;
	        return errno;
	    }

	    while ((dirp = readdir(dp)) != NULL) {
			if (string(dirp->d_name)=="." || string(dirp->d_name)=="..") {
				continue;
			}
	        files.push_back(dir + "/" +string(dirp->d_name));
	    }
	    closedir(dp);
	    return 0;
}

int main(int argc, char* argv[]) {
	printf("big image\n");
	if (argc!=2) {
		printf("Usage: ./big_image <path>\n");
		return -1;
	}

	vector<string> files = vector<string>();

	getdir(argv[1],files);

	if (files.size()==0) {
		printf("File read error: %s\n", argv[1]);
		return -1;
	}

	for (unsigned int i = 0;i < files.size();i++) {
	    cout << files[i] << endl;
    }

	int row_num = 2, col_num = 2;
	int size = files.size();

	Mat unit = imread(files[0]);
	int height = unit.rows;
	int width = unit.cols;
	int big_height = row_num * height;
	int big_width = col_num * width;
	printf("height = %d, width = %d, big_h = %d, big_w = %d\n", height, width, big_height, big_width);

	Mat big_image = Mat::zeros(big_height, big_width, CV_8UC3);
	/*for ( int i=0; i<size; i++ ) {
		Mat patch = imread(files[i]);
		imshow("patch", patch);
		waitKey(0);
	}*/
	for ( int y=0; y<row_num; y++ ) {
		for ( int x=0; x<col_num; x++ ) {
			static int i=0;
			Mat patch = imread(files[i++%size]);
			imshow("patch", patch);
			for ( int yy=0; yy<height; yy++ ) {
				for ( int xx=0; xx<width; xx++ ) {
					printf("y = %d, x = %d, yy = %d, xx = %d\n", y, x, yy, xx);
					printf("index = %d\n", (y*height)*big_width + yy*xx*width + x* width + xx);
					big_image.data[3 * ( (y*height)*big_width + yy*big_width + x*width + xx ) + 0 ] = patch.data[3*(yy*width+xx) + 0];
					big_image.data[3 * ( (y*height)*big_width + yy*big_width + x*width + xx ) + 1 ] = patch.data[3*(yy*width+xx) + 1];
					big_image.data[3 * ( (y*height)*big_width + yy*big_width + x*width + xx ) + 2 ] = patch.data[3*(yy*width+xx) + 2];
				}
			}
			imshow("big_image", big_image);
			waitKey(0);
		}
	}
	imshow("big_image", big_image);
	waitKey(0);

	return 0;
}
