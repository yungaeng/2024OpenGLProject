#pragma once

class Object;
class Cube;
class Model;
// 충돌체를 소유한 오브젝트는 이동할 때 그 충돌체가 같이 이동하여야 함
class Collider
{
	// 영역 검사
private:
	static UINT g_iNextID;
	// Collider 를 소유하고 있는 오브젝트
	Cube* m_pOwner;

	// 오프셋, 기준 위치(오브젝트)로부터 상대적인 차이값 / 이 값을 이용하여 충돌체 각각을 이동시킨다.
	vec3	m_vOffsetPos;

	// 오프셋을 이용하여 계산하여 최종 위치 결정
	vec3	m_vFinalPos;

	// 충돌체의 크기
	vec3	m_vScale;

	UINT	m_iID;		// 충돌체의 고유한 ID값
	int		m_iCol;		// 충돌체와 충돌 중인 개수

	bool	m_bActive;	// 충돌체 활성화 여부

	// AABB 바운딩 박스를 나타내는 최소 및 최대 벡터 추가
	vec3 _minAABB;
	vec3 _maxAABB;

public:
	// AABB 설정 및 가져오기 함수 추가
	void SetAABB(const vec3& min, const vec3& max) {
		_minAABB = min;
		_maxAABB = max;
	}
	void setOwner(Cube* _pOwner) { m_pOwner = _pOwner; }
	vec3 GetMinAABB() const { return _minAABB; }
	vec3 GetMaxAABB() const { return _maxAABB; }
	void SetOffsetPos(vec3 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(vec3 _vScale) { m_vScale = _vScale; }
	void SetFinalPos(vec3 _vPos) { m_vFinalPos = _vPos; }

	vec3 GetOffsetPos() { return m_vOffsetPos; }
	vec3 GetScale() { return m_vScale; }
	vec3 GetFinalPos() { return m_vFinalPos; }

	Cube* GetObj() { return m_pOwner; }
	UINT GetID() { return m_iID; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	// 충돌 시점 함수 목록
	void OnCollision(Collider* _pOther);		// 충돌 중인 경우 호출되는 함수
	void OnCollisionEnter(Collider* _pOther);	// 충돌에 막 진입한 경우 호출되는 함수
	void OnCollisionExit(Collider* _pOther);	// 충돌에서 벗어난 경우 호출되는 함수

	// 대입 연산자 자체 삭제하기 - 쓸 이유는 없는 기본 연산자가 실수로라도 만들어지면 안 됨
	Collider& operator = (Collider& _origin) = delete;

	Collider();
	// 개별 id 생성을 위한 복사생성자 깊은 복사 호출
	Collider(const Collider& _origin);

	~Collider();


	friend class CObject;
	friend class Cube;
};

