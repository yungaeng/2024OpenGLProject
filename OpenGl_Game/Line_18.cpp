#include "Line_18.h"
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>


using glm::mat4;
using glm::radians;
#include <vector>
#include <cmath>

float Random_0_to_1f();

Line::Line()
	:Polygon(mode_Line)
	,_lineshape{0}
	,_Colors{0}
	,_size(0)
	, _linemode(true)

{
}

Line::Line(GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4, GLfloat f5, GLfloat f6)
	:Polygon(mode_Line)
	, _lineshape{ {f1,f2,f3}, {f4,f5,f6} }
	, _Colors{ {Random_0_to_1f(),Random_0_to_1f() ,Random_0_to_1f()}
	,{ Random_0_to_1f(),Random_0_to_1f() ,Random_0_to_1f() }}
	,_size(3)
	, _linemode(true)
{
}

Line::Line(GLfloat x, GLfloat y)
	:Polygon(mode_Line)
	, _mouse_x(x)
	, _mouse_y(y)
	, _radius(0.f)
	, _theta(0.f)
	, _size(3)
	, _linemode(true)
{
}

Line::~Line()
{
}

void Line::move_On_dir(char dir)
{
	float dirx = 0;
	float diry = 0;
	switch (dir)
	{
	case 'w':
		diry = 0.05f;
		break;
	case 'a':
		dirx = -0.05f;
		break;
	case 's':
		diry = -0.05f;
		break;
	case 'd':
		dirx = 0.05f;
		break;
	default:
		break;
	}
	for (auto& a : _lineshape)
	{
		a[0] += dirx;
		a[1] += diry;
	}
}

void Line::Draw_Polygon()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	if(_linemode == true)
		glDrawArrays(GL_LINE_STRIP, 0, _size - 1);
	else
		glDrawArrays(GL_POINTS, 0, _size - 1);
}

void Line::init_buffer_polygon(GLuint* vao, GLuint* vbo)
{
	glGenBuffers(2, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�

	//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	//--- ���� triShape���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	// Line size = 3
	glBufferData(GL_ARRAY_BUFFER, 3 * _size * sizeof(GLfloat), get_vertex_ptr(), GL_STATIC_DRAW);

	//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//--- attribute �ε��� 0���� ��밡���ϰ� ��
	glEnableVertexAttribArray(0);

	//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- ���� colors���� ���ؽ� ������ �����Ѵ�.
	// 
	//--- colors �迭�� ������: 6= Line
	glBufferData(GL_ARRAY_BUFFER, 3 * _size * sizeof(GLfloat), get_color_ptr(), GL_STATIC_DRAW);
	//--- ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//--- attribute �ε��� 1���� ��� �����ϰ� ��.
	glEnableVertexAttribArray(1);
}

void Line::Update()
{
}

void Line::Change_Color(GLfloat r, GLfloat g, GLfloat b)
{
	for (auto &a : _Colors)
	{
		a = { r,g,b };
	}
}

GLfloat* Line::get_vertex_ptr()
{
	//return (GLfloat*)_lineshape;
	return (GLfloat*)_lineshape.data();
}

GLfloat* Line::get_color_ptr()
{
	return (GLfloat*)_Colors.data();
	//return (GLfloat*)_Colors;
}



void Line::init_line(bool ccwon)
{
	int py = 360;
	if (ccwon == true)
	{
		for (size_t i = 0; i < py * 5; i++)
		{
			/*if (i > 180)
			{
				_theta = _theta - 4.f;
				_radius = _radius - 0.001f;
			}
			else*/
			
			_theta = _theta + 4.f;
			_radius = _radius + 0.002f;
			


			float x = _radius * cosf(radians(_theta)) + _mouse_x;
			float y = _radius * sinf(radians(_theta)) + _mouse_y;
			/*if (i == 180)
			{
				_mouse_x = x + _radius;
				_theta -= 180;
				x = _radius * cosf(radians(_theta)) + _mouse_x;
				y = _radius * sinf(radians(_theta)) + _mouse_y;
			}*/

			_lineshape.emplace_back(x, y, 0.f);
			_Colors.emplace_back(1.f, 1.f, 1.f);
		}
	}
	else
	{

		for (size_t i = 0; i < 360; i++)
		{
			if (i > 180)
			{
				_theta = _theta + 4.f;
				_radius = _radius - 0.001f;
			}
			else
			{
				_theta = _theta - 4.f;
				_radius = _radius + 0.001f;
			}


			float x = _radius * cosf(radians(_theta)) + _mouse_x;
			float y = _radius * sinf(radians(_theta)) + _mouse_y;
			if (i == 180)
			{
				_mouse_x = x + _radius;
				_theta += 180;
				x = _radius * cosf(radians(_theta)) + _mouse_x;
				y = _radius * sinf(radians(_theta)) + _mouse_y;
			}

			_lineshape.emplace_back(x, y, 0.f);
			_Colors.emplace_back(1.f, 1.f, 1.f);
		}
	}

	return;
}
