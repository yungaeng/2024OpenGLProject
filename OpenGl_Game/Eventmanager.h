#pragma once
#include <memory>
typedef ULONG_PTR DWORD_PTR, * PDWORD_PTR;

class Object;
enum class EVENT_TYPE;

struct tEvent
{
	// �̺�Ʈ�� �߰����� ����
	EVENT_TYPE	eEven;
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
};

class EventMgr
{
	SINGLE(EventMgr)
private:
	vector<tEvent> m_vecEvent;

	vector<Object*> m_vecDead;		// ���� ���� CObject ����

public:
	void update();

private:
	void Excute(const tEvent& _eve);

public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }
};

