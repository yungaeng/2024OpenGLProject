#include "global.h"
#include "ColMgr.h"
#include "SceneManager.h"
#include "Object.h"
#include "Collider.h"

CollisionMgr::CollisionMgr()
	:m_arrCheck{}
{

}
CollisionMgr::~CollisionMgr()
{

}

void CollisionMgr::update()
{
	// �浹 �˻�
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		m_arrCheck[iRow];
		// �˻�� iRow ��° ��Ʈ���� �˻縦 �����Ѵ�. (�迭 ����  / ��Ī�̱� ������ �ѹ��� �˻�)
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			// iRow���� 32��Ʈ(4����Ʈ UINT)�� iCol��° ��Ʈ�� �ִ� ��Ʈ�� 1�� end(1)�ΰ��
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				// ������� �� �׷��� ������Ʈ�� �����ͼ� �˻縦 ���� - �Ű� �ŸŴ��� include
				CollisionUpdateGroup((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CollisionMgr::CollisionUpdateGroup(GROUP_TYPE _eleft, GROUP_TYPE _eright)
{
	// ���� ��� �׳� �ܼ��� ���������� ��, �޴� ��� ���۷��� ȭ�� ����� ������ ����������.
	// ���� ���� ���� ���۷����� ���� ������ �������� �߰��ȴ�.
	const vector<Object*>& vecLeft = SceneManager::getInstance().GetGroupObject(_eleft);
	const vector<Object*>& vecRight = SceneManager::getInstance().GetGroupObject(_eright);

	// �ݺ������� �ʱ�ȭ ���� �ʰ� ���⼭ ����
	map<ULONGLONG, bool>::iterator iter;

	// ���� ���� �׷��� �޾ƿ� ���, �ڱ� �ڽŰ��� �浹�� ���ܽ��Ѿ� �Ѵ�.
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		for (auto& lpart : vecLeft[i]->getParts())
		{
			// ���� �浹ü�� ���� ���
			if (nullptr == lpart->getCollider())
			{
				continue;	// ��Ƽ���� ���� �׳� �� �ݸ� ������ ������ ���ǰ� ���� �� ���� �ݺ���
			}
			for (size_t j = 0; j < vecRight.size(); ++j)
			{
				for(auto& rpart : vecRight[j]->getParts())
				{
					// ���� �浹ü�� ���� ���, ���� �ڱ� �ڽŰ��� �浹�� �˻��Ϸ��� ���
					if (nullptr == rpart->getCollider()
						|| (lpart == rpart))
					{
						continue;	// ��Ƽ���� ���� �׳� �� �ݸ��� ������ ���� �ݺ��� ����
					}

					Collider* pLeftCol = lpart->getCollider();
					Collider* pRightCol = rpart->getCollider();
					
					// �������� �浹üũ - �浹ü ���� ���̵� ����
					COLLIDER_ID ID;
					ID.Left_id = pLeftCol->GetID();
					ID.Right_id = pRightCol->GetID();
					// �̷��� �ϼ��� 4 + 4 8����Ʈ ID�� ������ ID�� �ȴ�

					iter = m_mapColInfo.find(ID.ID);

					// �浹 ������ �� ��� ������ ��� (�浹���� �ʾҴ�=false �� ����)
					if (m_mapColInfo.end() == iter)
					{
						m_mapColInfo.insert(make_pair(ID.ID, false));
						iter = m_mapColInfo.find(ID.ID);
					}

					if (IsCollision(pLeftCol, pRightCol))
					{
						// ���� �浹 ���̴�.

						if (iter->second)
						{
							// �������� �浹�ϰ� �־���. ( ������ )

							if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
							{
								// �� �� �ϳ��� ���� �����̸� �浹�� ��� �������� ������Ѵ�.
								pLeftCol->OnCollisionExit(pRightCol);
								pRightCol->OnCollisionExit(pLeftCol);
								iter->second = false;
							}
							else
							{	// ���� ������ �ƴ϶�� ��� �浹 ���̴�.
								pLeftCol->OnCollision(pRightCol);
								pRightCol->OnCollision(pLeftCol);
							}
						}
						else
						{
							// �������� �浹���� �ʾ����� ���� �浹�ߴ� ( ������ ) �ٵ� ���� �� ������ ���̴�.
							// �׷� ���� �浹 �� �� �ɷ� ���� 
							// �ƴ϶�� ���� �浹�� ������ ���̴�.
							if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
							{
								pLeftCol->OnCollisionEnter(pRightCol);
								pRightCol->OnCollisionEnter(pLeftCol);
								iter->second = true;
							}


						}
					}
					else// �浹�ϰ� ���� ���� ���
					{
						if (iter->second)
						{
							// �浹�ϴٰ� �̹��� �浹�� ������. ( ������ )
							pLeftCol->OnCollisionExit(pRightCol);
							pRightCol->OnCollisionExit(pLeftCol);
							iter->second = false;
						}

					}
				}
			}
		}
	}
}

bool CollisionMgr::IsCollision(Collider* _pLeftCol, Collider* _pRightCol)
{
	vec3 vLeftMin = _pLeftCol->GetMinAABB();
	vec3 vLeftMax = _pLeftCol->GetMaxAABB();

	vec3 vRightMin = _pRightCol->GetMinAABB();
	vec3 vRightMax = _pRightCol->GetMaxAABB();

	// AABB �浹 �˻�
	if (vLeftMax.x < vRightMin.x || vLeftMin.x > vRightMax.x)
		return false;
	if (vLeftMax.y < vRightMin.y || vLeftMin.y > vRightMax.y)
		return false;
	if (vLeftMax.z < vRightMin.z || vLeftMin.z > vRightMax.z)
		return false;

	return true;
}

void CollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eright)
{
	// �׷�� �׷찣�� �浹 ���� �� enum���� ���� �׷��� enum�� ������ ��� 
	// ���� �迭 �ʿ��� ǥ�� ����
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ)�� ���

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eright;

	// ���� �� ū ��Ȳ���� �� ���� �ٲ� �ٽ� �ִ´�.
	if (iCol < iRow)
	{
		iRow = (UINT)_eright;
		iCol = (UINT)_eLeft;
	}
	// �̹� 1�̾ end������ 1�� ���� ���
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		// �����ؼ� �ִ´�.
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{// 1�� iCol��ŭ ��Ʈ ����Ʈ ����Ʈ �ؼ� ���� �־��ش�.
		m_arrCheck[iRow] |= (1 << iCol);
	}
}

