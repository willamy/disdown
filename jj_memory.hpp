#ifndef __DISPATCHDATA
#define __DISPATCHDATA

#include <malloc.h>
#include <list>


struct DispatchData{
	size_t data_capacity; //total size
	size_t data_len;		//content len
	unsigned char* data;
};

typedef std::list<DispatchData>  DispatchDataList;

class JJMemory{
public:
	~JJMemory();
	DispatchData GetBlock(size_t sz);
	void FreeBlock(DispatchData _data);
private:
	DispatchDataList m_stFreeMemory;
};

#endif
