#include "Shader.h"
#include<string>
#include<ifstream>

//此函数与OpenGL无关
static void CheckShaderError(GLuint shader,//与之前定义的着色器管理常数类型一致
							 GLuint Flag,//
							 bool isProgram,
							 const std::string& errorMessage);

void CheckShaderError(GLuint shader, GLuint Flag, bool isProgram, const std::string& errorMessage)
{

}

//此函数与OpenGL无关
static std::string LoadShader(const std::string& filename);

std::string LoadShader(const std::string& filename) {

	std::ifstream file;

	file.open((filename).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good()) {
			getline(file, line);
			output.append(line + "\n");
		}
	}

	return output;
	//记得改为c语言的文件打开方式
	//constexpr auto MaxTempSize = 1024;
	//	FILE* shaderfile;
	//
	//	char* buf = {0};
	//
	//
	//	if (!fopen_s(&shaderfile, filename.c_str(), "wb"))
	//	{
	//		char Temp[MaxTempSize];
	//		int MaxSize = 0;
	//		while (fscanf_s(shaderfile, "%[^\n]", Temp))//读取脚本文件时，可能需要跳过换行符
	//		{
	//			fgetc(shaderfile);
	//			
	//			MaxSize += strlen(Temp);
	//			strcat_s(buf, MaxSize, Temp);
	//		}
	//
	//		
	//
	//
	//	}
	//	else {
	//		std::cerr << "file open error" << std::endl;
	//	}
	//
	//	return std::string(buf);
}



static GLuint CreateShader(const std::string& text, GLenum ShaderType);//来自GLenum的shadertype常量

GLuint CreateShader(const std::string& text, GLenum ShaderType) {

	GLuint shader = glCreateShader(ShaderType);

	if (!shader)
	{
		std::cerr << "Error: Shader creation failure" << std::endl;
	}

	const GLchar* shaderSourceString[1];

	GLint shaderSourceStringLength[1];

	shaderSourceString[0] = text.c_str();
	shaderSourceStringLength[0] = text.length();
	
	glShaderSource(shader, 1, shaderSourceString, shaderSourceStringLength);//加载shader
	glCompileShader(shader);//编译shader


	return shader;

}

Shader::Shader(const std::string filename)
{
	m_pragmram = glCreateProgram();

	m_shaders[0] = CreateShader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER);//分别创建顶点着色器，以及片元着色器
	m_shaders[1] = CreateShader(LoadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < numShaders; i++) {
	
		glAttachShader(m_pragmram, m_shaders[i]);//安装着色器

	}

	glLinkProgram(m_pragmram);//链接shader

	glValidateProgram(m_pragmram);//验证shader

	
}

void Shader::Bind()
{
	glUseProgram(m_pragmram);
}

Shader::~Shader() {
	for (unsigned int i = 0; i < numShaders; i++) {

		glDetachShader(m_pragmram, m_shaders[i]);
		glDeleteShader(m_shaders[i]);

	}

	glDeleteProgram(m_pragmram);

}