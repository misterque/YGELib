#include <exception>
#include <string>


class YGEExceptionFileNotFound : public std::exception {

private:
	std::string missingFile;
public:
	YGEExceptionFileNotFound(std::string s){
		missingFile = s;
	}
	virtual const char* what() const throw(){
		return "FileNotFound!";
	}
};


class YGEExceptionMethodNotImplementedYet : public std::exception {

private:

public:
	virtual const char* what() const throw(){
		return "Method not implemented yet!";
	}
};