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
	// 이벤트 매니저 업데이트 시작할 때 데드벡터가 채워져 있으면 이전 프레임이 등록한 이벤트일 것이다.
	// ==============================================
	// 이전 프레임에서 등록해 둔 Dead Object 들을 삭제한다
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
	//	EVENT 처리
	// ===================
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}



// 만약 Scene 체인지 이벤트가 등록되면, 그 이벤트를 처리한 후 나머지 이벤트는 없애는 방식으로 생각하기
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
		// 1. Object를 Dead 상태로 변경
		// 2. 삭제 예정 오브젝트를 모아둔다 m_vecDead에
		Object* pDeadObj = (Object*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
	break;
	}
}
