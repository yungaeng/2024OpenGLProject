#include "global.h"
#include "EventManager.h"
#include "Object.h"
#include "SceneManager.h"

EventMgr::EventMgr()
{

}
EventMgr::~EventMgr()
{

}

void EventMgr::update()
{
	// �̺�Ʈ �Ŵ��� ������Ʈ ������ �� ���庤�Ͱ� ä���� ������ ���� �������� ����� �̺�Ʈ�� ���̴�.
	// ==============================================
	// ���� �����ӿ��� ����� �� Dead Object ���� �����Ѵ�
	// ==============================================
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		if (m_vecDead[i] != nullptr)
		{
			delete m_vecDead[i];
			m_vecDead[i] = nullptr;
		}
	}
	m_vecDead.clear();

	// ===================
	//	EVENT ó��
	// ===================
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}



// ���� Scene ü���� �̺�Ʈ�� ��ϵǸ�, �� �̺�Ʈ�� ó���� �� ������ �̺�Ʈ�� ���ִ� ������� �����ϱ�
void EventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Address
		// wParam :	GROUP_TYPE
		Object* pNewObj = (Object*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;
		SceneManager::getInstance().AddObject(pNewObj, eType);
	}

	break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Address
		// 1. Object�� Dead ���·� ����
		// 2. ���� ���� ������Ʈ�� ��Ƶд� m_vecDead��
		Object* pDeadObj = (Object*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
	break;
	}
}
