#include "button.h"
#include <math.h>

NS_CROSSANY_BEGIN
NS_CROSSANY_UI_BEGIN
button::button(){
}
button::~button(){
}

void button::customdraw(){
	GLfloat R = (GLfloat)msize.getw() / 2;
	GLfloat Pi = 3.1415926f;
	int n = 100;
	glColor3f(1.0f, 1.0f, 0.0f);

	glBegin(GL_POLYGON);//OpenGL要求：指定顶点的命令必须包含在glBegin函数之后，
	//glEnd函数之前（否则指定的顶点将被忽略）。并由glBegin来指明如何使用这些点
	//GL_POLYGON表示画多边形（由点连接成多边形）
	for (int i = 0; i< n; ++i)
		glVertex2f(R*cos(2 * Pi / n*i)+100, R*sin(2 * Pi / n*i));

	glEnd();
	glColor3f(1.0f, 1.0f, 0.0f);

}
NS_CROSSANY_UI_END
NS_CROSSANY_END