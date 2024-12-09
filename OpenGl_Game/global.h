#pragma once
#define _CRT_SECURE_NO_WARNINGS
// SIngleton ��ũ��
#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
								return &mgr;\
						}\
						private:\
						type();\
						~type();\

enum class GROUP_TYPE
{
	// �׷����� ���� ���� �߿�
	DEFAULT,
	TILE,
	BLOCK,
	GROUND,
	GUN,
	MONSTER,
	PLAYER,
	PROJ_PLAYER,	// �÷��̾� ����ü
	PROJ_MONSTER,	// ���� ����ü
	// 1209 ������ �߰�
	ITEM,


	// ���⼭ UI�� ��� ������Ʈ�� ���� �׷������� ���� ����
	UI = 31,
	END = 32,
};

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<map>
using std::map;
using std::make_pair;
float Random_0_to_1f();

using std::vector;
using glm::mat4;
using glm::radians;
using glm::vec2;
using glm::vec3;
using glm::vec4;
