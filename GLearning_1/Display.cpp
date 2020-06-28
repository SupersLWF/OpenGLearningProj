#include "Display.h"
#include <GL/glew.h>
#include <iostream>

Display::Display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	//分别设置三原色各8位
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	//alpha深度也设置为8位
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.c_str(),
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								width, height,
								SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);


//glew环境初始化，如果嫌构造函数位置初始化项目太多，也可以滞后初始化
	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "GLEW INIT FAILURE" << std::endl;
	}

	m_isClosed = false;


}

Display::~Display()
{
	SDL_Quit();
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);


}

void Display::Clear(float r, float g, float b,float a){
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT);
}//此两行代码封装了opengl的两个比较常用的函数。

void Display::update() 
{
	SDL_GL_SwapWindow(m_window);//内存缓冲区交换

	SDL_Event E;

	while (SDL_PollEvent(&E)) {
		if (E.type == SDL_QUIT)  {
			m_isClosed = true;
		}
	
	}


}//用于循环调用pollevent检查是否有窗口事件需要处理（大概是swap会返回事件吧），
//和检查接受的event是否为sdl_quit；
//sdl封装的消息循环放在此处，是因为update函数在主函数中被置入了循环中，而该循环为主函数的主体，程序不结束此while循环就会一直轮询。

bool Display::IsClosed() {
	return m_isClosed;
};

//什么时内存缓冲区交换？

//假定内存1存放之前绘制的窗口的图形信息，那么内存2将存放OpenGL当前绘制的窗口信息，
//当内存二完成绘制，并且窗口需要重绘时，那么内存1，2就会交换，操作系统会将绘制好的内存2显示出来，把内存1交给OpenGL用于绘制。
//本篇主要讲解OpenGLapi的基础使用，不涉及sdl的内容，因此这部分仅供了解。