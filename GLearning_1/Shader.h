#pragma once
#include<GL/glew.h>
#include<string>

class Shader//着色器列表
{
	static const GLuint numShaders = 2;//用于设定着色器数量

	GLuint m_pragmram;//unsigned int,用于管理此着色器列表
	GLuint m_shaders[numShaders];//思路和管理 片元网格 里的顶点一致，用于创建着色器，此为着色器id的数组

public:
	Shader(const std::string filename);//此参数用于获取 着色器文本 的路径

	void Bind();
	~Shader();
};

