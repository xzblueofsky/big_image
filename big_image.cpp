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

	for (unsigned int i = 0;i < files.size();i++) {
	    cout << files[i] << endl;
    }

	return 0;
}
