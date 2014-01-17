
#ifndef __DATARECEIVE
#define __DATARECEIVE
class IDataReceive{
public:
	virtual size_t OnData(unsigned char* pData,size_t len) = 0;
};

#endif
