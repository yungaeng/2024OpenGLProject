#pragma once
#define _CRT_SECURE_NO_WARNINGS
// SIngleton 매크로
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
	// 그려지는 순서 또한 중요
	DEFAULT,
	TILE,
	BLOCK,
	GROUND,
	GUN,
	MONSTER,
	PLAYER,
	PROJ_PLAYER,	// 플레이어 투사체
	PROJ_MONSTER,	// 몬스터 투사체
	// 1209 아이템 추가
	ITEM,


	// 여기서 UI는 모든 오브젝트의 위에 그려지도록 순서 조정
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
