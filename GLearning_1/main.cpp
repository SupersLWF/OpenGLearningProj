#include<iostream>
#include<GL/glew.h>
#include"Display.h"
#include"Mesh.h"

int main(int _Argc, char** argv)
{
	//std::cout << "test program" << std::endl;
	Display display(800, 400, "testprogram");

	//顶点数组
	Vertex vertices[] = {Vertex(glm::vec3(-0.5,-0.5,0)),
						 Vertex(glm::vec3(0,0.5,0)),
						 Vertex(glm::vec3(0.5,-0.5,0))};

	//初始化片元网格
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	//此while循环用于接收opengl调用
	while (!display.IsClosed())
	{
		display.Clear(0.0F/*RED*/, 0.15F/*GREEN*/, 0.3F/*BLUE*/, 1.0F/*ALHFA*/);
		
		//绘制片元网格
		mesh.Draw();
		
		display.update();//display内部有缓冲区交换函数，此函数作用是交换缓冲区，然后update窗口

	}

	return 0;
}