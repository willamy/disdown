#include "config.hpp"
#include <iostream>
#include <strings.h>

Config  g_config;

int main(int argc,char **argv)
{
	int is_center = 0;
	const char* pFileName = NULL;
	std::string error_str;

	for(int i = 1; i < argc; ++i) {
		if(!strcasecmp(argv[i],"-c")){
			is_center = 1;
		}
		else if(!strcasecmp(argv[i],"-f")){
			if(i + 1 < argc) pFileName = argv[++i];
			else{
				error_str = "-f could follow a config name";
				break;
			}
		}
	}

	if(!pFileName || !error_str.empty()){
		std::cout << "run failed " << error_str.c_str() << std::endl;
		return -2;
	}

	int iret = g_config.ReadFile(pFileName);
	if(iret){
		std::cout << "parse file error " << iret << std::endl;
		return -1;
	}
	std::cout << g_config << std::endl;
	return 0;
}
