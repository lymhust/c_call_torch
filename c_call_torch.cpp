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
#include "luaT.h"
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

//lua_State *L;
//
//int print_error(int bRet)
//{
//	if (bRet)
//	{
//		const char *pErrorMsg = lua_tostring(L, -1);
//		cout << pErrorMsg << endl;
//		lua_close(L);
//		return 0;
//	}
//	return 1;
//}

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
	img.convertTo(img, CV_32FC3);
	img = img / 255;
	if(img.empty())
	{
		cout<<"error";
		return -1;
	}

	vector<Mat> mv;
	split(img, mv);
//	namedWindow("R", 1);
//	namedWindow("G", 1);
//	namedWindow("B", 1);
//
//	imshow("R",mv[0]);
//	imshow("G",mv[1]);
//	imshow("B",mv[2]);


	//Mat E = img(Range(1,128),Range(1,128)).clone();
	//E = 1;
	//imshow("mypic",E);

	float *ptrimg = (float*)img.data; // image pointer

    lua_State *L = luaL_newstate();
    luaL_openlibs( L );

    // loading the lua file
    if (luaL_loadfile(L, "./src/tensor.lua") || lua_pcall(L, 0, 0, 0))
    {
        printf("error: %s \n", lua_tostring(L, -1));
    }

	// convert the c array to Torch7 specific structure representing a tensor
	THFloatStorage *storage = THFloatStorage_newWithData(ptrimg, img.rows * img.cols * img.channels());
	THFloatTensor *tensor = THFloatTensor_newWithStorage3d(storage, 0, img.rows, img.cols*img.channels(),       //long size0_, long stride0_,
														   	   	   	   img.cols, img.channels(),
																	   img.channels(), 1);
	luaT_newmetatable(L, "torch.FloatTensor", NULL, NULL, NULL, NULL);

	// load the lua function hi_tensor
	lua_getglobal(L, "hi_tensor");
	if(!lua_isfunction(L,-1))
	{
		lua_pop(L,1);
	}

	//this pushes data to the stack to be used as a parameter
	//to the hi_tensor function call
	luaT_pushudata(L, (void *)tensor, "torch.FloatTensor");

	// call the lua function hi_tensor
	if (lua_pcall(L, 1, 1, 0) != 0)
	{
		printf("error running function `hi_tensor': %s \n", lua_tostring(L, -1));
	}

	// get results returned from the lua function hi_tensor
	THFloatTensor *z = (THFloatTensor*)luaT_toudata(L, -1, "torch.FloatTensor");
	lua_pop(L, 1);
	THFloatStorage *storage_res =  z->storage;
	float *result = storage_res->data;

	imshow("mypic",img);
	waitKey();
	return 0;
}
