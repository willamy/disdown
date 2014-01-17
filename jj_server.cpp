#include "jj_server.hpp"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

JJDispatchServer::JJDispatchServer(JJMemory* pMemory):
	m_pMemoryMng(pMemory) {

}

int JJDispatchServer::FlushData(){
	if(!m_pDataReceive){
		return 0;
	}
	DispatchDataList::iterator iter = m_stDataList.begin();
	for(;iter != m_stDataList.end();){
		size_t rev_len = m_pDataReceive->OnData(iter->data,iter->data_len);
		if(rev_len >= iter->data_len){
			m_pMemoryMng->FreeBlock(*iter);
			iter = m_stDataList.erase(iter);
		}else{
			iter->data_len -= rev_len;
			memmove(iter->data,iter->data + rev_len,iter->data_len);
			break;
		}
	}

	return !m_stDataList.empty();
}

int JJDispatchServer::AppendData(const unsigned char* data,size_t data_len){
	DispatchData* pData = NULL;
	DispatchData tmpData;
	bool new_data = true;
	size_t have_write = 0;
	if(!m_stDataList.empty()){
		DispatchData& _data =  m_stDataList.back();
		if(_data.data_len + data_len > _data.data_capacity){
			//need create one
			have_write = _data.data_capacity - _data.data_len;
			if(have_write){
				memcpy(_data.data + _data.data_len,data,have_write);
			}
			_data.data_len += have_write;
		} else{
			pData = &_data;
			new_data = false;
		}
	}
	if(!pData){
		tmpData = m_pMemoryMng->GetBlock(data_len);
		pData = &tmpData;
	}
	//write it
	memcpy(pData->data + pData->data_len,data + have_write,data_len - have_write);
	pData->data_len += (data_len - have_write);
	if(new_data){
		m_stDataList.push_back(*pData);
	}

	return data_len;
}
int JJDispatchServer::DataEmpty(){
	return m_stDataList.empty();
}

