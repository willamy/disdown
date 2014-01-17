#include "jj_memory.hpp"

DispatchData JJMemory::GetBlock(size_t sz){
	DispatchDataList::iterator iter = m_stFreeMemory.begin();
	for(;iter != m_stFreeMemory.end();){
		if(iter->data_capacity >= sz){
			DispatchData _got = *iter;
			m_stFreeMemory.erase(iter);
			return _got;
		}
	}

	DispatchData _got;
	_got.data_capacity = sz * 2;
	_got.data_len = 0;
	_got.data = (unsigned char*)malloc(_got.data_capacity);

	return _got;
}
void JJMemory::FreeBlock(DispatchData _data){
	_data.data_len = 0;
	m_stFreeMemory.push_back(_data);
}
JJMemory::~JJMemory(){
	DispatchDataList::iterator iter = m_stFreeMemory.begin();
	for(;iter != m_stFreeMemory.end(); ++iter){
		free(iter->data);
	}
}
