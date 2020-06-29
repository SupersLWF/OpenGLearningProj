#pragma once
#include<glm/glm.hpp>
#include<GL/glew.h>

class Vertex//定点类
{
	glm::vec3 pos;
public:
	Vertex(const glm::vec3& pos)//传入常量，glm为专门为opengl编写的数学库，此处为三维向量
	{
		this->pos = pos;
	}
};

class Mesh 
{
	enum
	{
		POSITION_VB,//OpenGL注册顶点数组缓冲区数组需要使用的参数
		NUM_BUFFERS//顶点数组的个数
		//枚举类型默认为1，可以定义时等号直接赋值，后续不可以更改值
	};


	GLuint m_vertexArrayObject;//顶点数组名。
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];//顶点数组缓冲区名。

	unsigned int m_drawCount;//顶点个数

public:
	Mesh(Vertex* vertices/*顶点数组*/, unsigned int numVertex/*顶点个数*/);
	~Mesh();

	void Draw();

};

