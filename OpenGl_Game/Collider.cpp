#include "global.h"
#include "Collider.h"
#include "Object.h"

UINT Collider::g_iNextID = 0;

Collider::Collider()
	:m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_iCol(0)
	, m_bActive(true)
{
}

Collider::Collider(const Collider& _origin)
	:m_pOwner(nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
	, m_iCol(_origin.m_iCol)
	, m_bActive(_origin.m_bActive)
{
	// finalpos�� �浹ü���� �˾Ƽ� ����� �� �״� ����
}

Collider::~Collider()
{
}


void Collider::finalupdate()
{
	// Object�� ��ġ�� ���󰣴�.
	vec3 vObjectPos = m_pOwner->getPosition();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
	assert(0 <= m_iCol);
}

void Collider::render(HDC _dc)
{
}


void Collider::OnCollision(Collider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}
void Collider::OnCollisionEnter(Collider* _pOther)
{
	++m_iCol;
	m_pOwner->OnCollisionEnter(_pOther);
}

void Collider::OnCollisionExit(Collider* _pOther)
{
	--m_iCol;
	m_pOwner->OnCollisionExit(_pOther);
}
