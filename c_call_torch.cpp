//============================================================================
// Name        : c_call_torch.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
extern "C"{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "luajit.h"
#include "TH/TH.h"
};

using namespace std;
using namespace cv;

/*
#include "luajit.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
 */

lua_State *L;

int print_error(int bRet)
{
	if (bRet)
	{
		const char *pErrorMsg = lua_tostring(L, -1);
		cout << pErrorMsg << endl;
		lua_close(L);
		return 0;
	}
	return 1;
}

/*
int main(int argc, char *argv[])
{
	L = luaL_newstate();
	luaL_openlibs(L);
	print_error(luaL_loadfile(L,"./src/generate_model.lua"));
	print_error(lua_pcall(L,0,0,0));
	print_error(luaL_dofile(L,"./src/test.lua"));
	lua_close(L);
	//system("ls");
	cout << "C++ Finish" << endl;
	return 1;
}
*/


int main()
{
    Mat img = imread("./src/test.jpg");
    if(img.empty())
    {
        cout<<"error";
        return -1;
    }

    float *ptrimg = (float*)img.data; // image pointer
    THFloatStorge *ptrstorge = THFloatStorage_newWithSize1(ptrimg);
    //THByteTensor *ptrtensor =

    imshow("mypic",img);
    waitKey();
    return 0;
}
