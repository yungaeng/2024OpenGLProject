#pragma once

class Object;

enum class GROUP_TYPE;

void CreateObject(Object* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(Object* _pObj);



//// �ڡڡ� ���ø��� ����� �����Ѵ�.
//template<typename T>
//void Safe_Delete_Vec(vector<T>& _vec)
//{
//	for (size_t i = 0; i < _vec.size(); ++i)
//	{
//		if (nullptr != _vec[i])
//			delete _vec[i];
//	}
//	_vec.clear();
//}
//
//template<typename T1, typename T2>
//void Safe_Delete_Map(map<T1, T2>& _map)
//{
//	// ���ø����� �̳�Ŭ������ ����Ϸ��� �տ� typename�� ������� �Ѵ�.
//	typename map<T1, T2>::iterator iter = _map.begin();
//	for (; iter != _map.end(); ++iter)
//	{
//		if (nullptr != iter->second)
//			delete iter->second;
//	}
//	_map.clear();
//}

