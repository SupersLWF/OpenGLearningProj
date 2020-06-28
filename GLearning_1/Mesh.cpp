#include "Mesh.h"

Mesh::Mesh(Vertex* vertices/*顶点数组*/, unsigned int numVertex/*顶点个数*/)
{
	m_drawCount = numVertex;

	//OpenGL函数
	glGenVertexArrays(1/*顶点数组的个数*/, &m_vertexArrayObject/*顶点数组对象名*/);//初始化顶点数组对象名到mesh
	glBindVertexArray(m_vertexArrayObject);//创建一个顶点数组，绑定到着色器中。

	//初始化顶点数组名缓冲区到mesh，这个缓冲区存放顶点数组名
	//创建顶点数组缓冲区，并初始化它

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER/*顶点数组类型*/, m_vertexArrayBuffers[POSITION_VB]/*绑定一个顶点数组缓冲区到着色器*/);

	//初始化顶点数组，存入顶点数组缓冲区。
	//拷贝顶点数组缓冲区 到OpenGL服务器

	glBufferData(GL_ARRAY_BUFFER, //顶点数组类型
				 numVertex * sizeof(vertices[0]),//分配一个顶点数组的大小 ,
				 vertices,//顶点数组的指针
				 GL_STATIC_DRAW);//设置之后如何读取此顶点数组，此次无需读取，因为此次运行时无需重绘。

								 
//

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);//将绑定了的顶点数组释放。

	
}

Mesh::~Mesh() 
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

//绘制顶点数组
void Mesh::Draw()
{
	//选取一个需要绘制的顶点数组
	glBindVertexArray(m_vertexArrayObject);

	//根据顶点数组来设置片元
	glDrawArrays(GL_TRIANGLES,//片元类型
				 0,//起始位置
				 m_drawCount);//片元个数

	glBindVertexArray(0);
	//绘制结束，释放数组
}
