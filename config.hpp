#include <cctype>
#include <stdint.h>
#include <string>
#include <map>
#include <iostream>

typedef std::map<std::string,std::string> KeyValueMap;
class Config{
public:
	friend std::ostream& operator<<(std::ostream& out,Config& cfg);
	Config();
	~Config();

	void Clear();
	int ReadFile(const std::string& fileName);

	int64_t GetValueInt(const std::string& key,int64_t default_value);
	const std::string& GetValueStr(const std::string& key,const std::string& default_value);
private:
	Config(const Config&);
	Config& operator=(const Config&);

	KeyValueMap m_stKVMap;
};

std::ostream& operator<<(std::ostream& out,Config& cfg);
