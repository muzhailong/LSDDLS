#ifndef UTILS_H_
#define UTILS_H_
#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>
#include<vector>

#define UTILS_FREE(x) do{  \
    if(x!=NULL){           \
        free (x);          \
    }                      \
}while(0);

#define RANDOM_BLOCK(block1,block2) do{\
   int r = rand() % 2;                 \
   if(r==0){                           \
        block1                          \
        block2                          \
    }else{                              \
        block2                          \
        block1                          \
    }                                   \
}while(0);

int unique_id();
void split(const std::string& s, std::vector<std::string>& tokens, const std::string& delimiters = " ");
std::string& trim(std::string &s);

template<typename Type>
Type to(const std::string&str){
	std::istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

#endif
