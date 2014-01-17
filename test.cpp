#include "jj_server.hpp"
#include <cstdio>
#include "jj_datareceive.hpp"

class TestReceive: public IDataReceive{
public:
	TestReceive(const char* filename){
		m_fp = fopen(filename,"w+");
	}

	virtual size_t OnData(unsigned char* pData,size_t len){
		size_t real_len = len;
		if(real_len > 10240) real_len = 10240;
		size_t fw = fwrite(pData,1,real_len,m_fp);
		printf("ondata:%d,fw:%d\n",len,fw);
		return fw;
	}
private:
	FILE *m_fp;

};

int main(int argc,char **argv)
{
	if(argc < 2){
		return -1;
	}
	const char* file_name = argv[1];
	FILE* fp = fopen(file_name,"r");

	JJMemory *_pMemoryMng = new JJMemory;
	TestReceive _testReceive("good");

	JJDispatchServer _disServer(_pMemoryMng);
	_disServer.SetReceive( &_testReceive);
	const size_t need_size = 50 * 1024;
	unsigned char data[ need_size];
	
	size_t _read = 0;
	while((_read = fread(data,1,need_size,fp))){
		_disServer.AppendData(data,_read);
		printf("now write :%lld\n",_read);
	}

	while(_disServer.FlushData());

	delete _pMemoryMng;

	return 0;
}
