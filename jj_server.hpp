#ifndef __JJ_SERVER
#define __JJ_SERVER

#include <list>
#include "jj_dispatch.hpp"
#include "jj_memory.hpp"
#include "jj_datareceive.hpp"


//for dispatch the binary which receive from download...
class JJDispatchServer : public IJJDispatch{
public:

	JJDispatchServer(JJMemory* pMemory);
	virtual int FlushData(); //flush data which holed
	virtual int AppendData(const unsigned char* data,size_t data_len);
	virtual int DataEmpty();
	void SetReceive(IDataReceive* pDataReceive){
		m_pDataReceive = pDataReceive;
	}
private:
	DispatchDataList m_stDataList;
	JJMemory *m_pMemoryMng;
	IDataReceive *m_pDataReceive;
};

#endif
