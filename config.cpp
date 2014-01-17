#include "config.hpp"
#include <stdlib.h>
#include <stdio.h>

Config::Config(){
}

Config::~Config(){

}

void Config::Clear(){
	m_stKVMap.clear();
}

int Config::ReadFile(const std::string& fileName){
	FILE *fp = fopen(fileName.c_str(),"r");
	if(!fp){
		return -1;
	}
	static char content[1024];
	size_t len = sizeof(content);
	static char parse_temp[1024];

	size_t readed = 0;

	while(fgets(content,len,fp)){
		//per line
		const char *pread = content;
		bool reach_equal = false;
		size_t parse_sz = 0;
		std::string parse_key;

		while(*pread){
			if(isspace(*pread)){
				++pread;
				continue;
			}

			if(*pread == '=' && !reach_equal){
				parse_key = std::string(parse_temp,parse_sz);
				parse_sz = 0;
				reach_equal = true;
			}else{
				parse_temp[parse_sz] = *pread;
				++parse_sz;
			}

			++pread;
		}

		if(!parse_sz)continue;

		if(!reach_equal){
			return -2;
		}

		m_stKVMap[parse_key] = std::string(parse_temp,parse_sz);

	}
}

int64_t Config::GetValueInt(const std::string& key,int64_t default_value){
	KeyValueMap::iterator iter = m_stKVMap.find(key);
	if(iter != m_stKVMap.end()){
		return atoll(iter->second.c_str());
	}
	return default_value;
}

const std::string& Config::GetValueStr(const std::string& key,const std::string& default_value){
	KeyValueMap::iterator iter = m_stKVMap.find(key);
	if(iter != m_stKVMap.end()){
		return iter->second;
	}
	return default_value;
}
std::ostream& operator<<(std::ostream& out,Config& cfg){
	KeyValueMap::iterator iter = cfg.m_stKVMap.begin();
	for(;iter != cfg.m_stKVMap.end(); ++iter){
		out << iter->first.c_str() << " = " << iter->second.c_str() << std::endl;
	}

	return out;
}
