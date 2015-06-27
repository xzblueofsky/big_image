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
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

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
	if (argc!=4) {
		printf("Usage: ./big_image <path> <rows> <columns>\n");
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

	int row_num = atoi(argv[2]);
	int col_num = atoi(argv[3]);
	int size = files.size();

	Mat unit = imread(files[0]);
	int height = unit.rows;
	int width = unit.cols;
	int big_height = row_num * height;
	int big_width = col_num * width;
	printf("height = %d, width = %d, big_h = %d, big_w = %d\n", height, width, big_height, big_width);

	srand((int)time(0));
	Mat big_image = Mat::zeros(big_height, big_width, CV_8UC3);
	for ( int y=0; y<row_num; y++ ) {
		for ( int x=0; x<col_num; x++ ) {
			Mat patch = imread(files[rand()%size]);
			for ( int yy=0; yy<height; yy++ ) {
				for ( int xx=0; xx<width; xx++ ) {
					big_image.data[3 * ( (y*height)*big_width + yy*big_width + x*width + xx ) + 0 ] = patch.data[3*(yy*width+xx) + 0];
					big_image.data[3 * ( (y*height)*big_width + yy*big_width + x*width + xx ) + 1 ] = patch.data[3*(yy*width+xx) + 1];
					big_image.data[3 * ( (y*height)*big_width + yy*big_width + x*width + xx ) + 2 ] = patch.data[3*(yy*width+xx) + 2];
				}
			}
		}
	}
	imshow("big_image", big_image);
	waitKey(0);
	unsigned long long cur_time_in_microsend;
	// get the time in micro-second
	struct timeval start;
	gettimeofday(&start, NULL);
	cur_time_in_microsend = (start.tv_sec) * 1000000+ start.tv_usec;
	char image_loc[1024];
	sprintf(image_loc, "%lld.jpg", cur_time_in_microsend);
	imwrite(image_loc, big_image);

	return 0;
}
