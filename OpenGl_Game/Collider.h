#pragma once

class Object;
class Cube;
class Model;
// �浹ü�� ������ ������Ʈ�� �̵��� �� �� �浹ü�� ���� �̵��Ͽ��� ��
class Collider
{
	// ���� �˻�
private:
	static UINT g_iNextID;
	// Collider �� �����ϰ� �ִ� ������Ʈ
	Cube* m_pOwner;

	// ������, ���� ��ġ(������Ʈ)�κ��� ������� ���̰� / �� ���� �̿��Ͽ� �浹ü ������ �̵���Ų��.
	vec3	m_vOffsetPos;

	// �������� �̿��Ͽ� ����Ͽ� ���� ��ġ ����
	vec3	m_vFinalPos;

	// �浹ü�� ũ��
	vec3	m_vScale;

	UINT	m_iID;		// �浹ü�� ������ ID��
	int		m_iCol;		// �浹ü�� �浹 ���� ����

	bool	m_bActive;	// �浹ü Ȱ��ȭ ����

	// AABB �ٿ�� �ڽ��� ��Ÿ���� �ּ� �� �ִ� ���� �߰�
	vec3 _minAABB;
	vec3 _maxAABB;

public:
	// AABB ���� �� �������� �Լ� �߰�
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
	// �浹 ���� �Լ� ���
	void OnCollision(Collider* _pOther);		// �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(Collider* _pOther);	// �浹�� �� ������ ��� ȣ��Ǵ� �Լ�
	void OnCollisionExit(Collider* _pOther);	// �浹���� ��� ��� ȣ��Ǵ� �Լ�

	// ���� ������ ��ü �����ϱ� - �� ������ ���� �⺻ �����ڰ� �Ǽ��ζ� ��������� �� ��
	Collider& operator = (Collider& _origin) = delete;

	Collider();
	// ���� id ������ ���� ��������� ���� ���� ȣ��
	Collider(const Collider& _origin);

	~Collider();


	friend class CObject;
	friend class Cube;
};

