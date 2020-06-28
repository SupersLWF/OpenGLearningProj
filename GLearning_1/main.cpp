#include<iostream>
#include<GL/glew.h>
#include"Display.h"
#include "main.h"

int main(int _Argc, char** argv)
{
	std::cout << "test program" << std::endl;
	Display display(800, 400, "testprogram");


	//此while循环用于接收opengl调用
	while (!display.IsClosed())
	{
		display.Clear(0.0F/*RED*/, 0.15F/*GREEN*/, 0.3F/*BLUE*/, 1.0F/*ALHFA*/);
		display.update();//display内部有缓冲区交换函数，此函数作用是交换，然后update窗口

	}

	return 0;
}