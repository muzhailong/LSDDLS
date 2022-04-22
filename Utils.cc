#include "Utils.h"

static std::mutex _mtx;
static int proc_id=0;

int unique_id(){
	std::lock_guard<std::mutex>lck(_mtx);
	int tmp=proc_id;
	proc_id+=1;
	return tmp;
}

void split(const std::string& s, std::vector<std::string>& tokens, const std::string& delimiters)
{
    std::string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    std::string::size_type pos = s.find_first_of(delimiters, lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos) {
        tokens.push_back(s.substr(lastPos, pos - lastPos));//use emplace_back after C++11
        lastPos = s.find_first_not_of(delimiters, pos);
        pos = s.find_first_of(delimiters, lastPos);
    }
}

std::string& trim(std::string &s){
	if (s.empty()){
	return s;
	}
	s.erase(0,s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}


