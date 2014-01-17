

class IJJDispatch{
	
public:
	virtual int FlushData() = 0; //flush data which holed
	virtual int AppendData(const unsigned char* data,size_t data_len) = 0;
	virtual int DataEmpty() = 0;
};
