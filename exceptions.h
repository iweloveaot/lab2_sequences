#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

class BaseException {
private:
    const char* message;
public:
    BaseException(const char* msg = "Exeption") : message(msg) {}
    const char* what() const {
        return message;
    } 
};

class InvalidArgumentException : public BaseException {
public:
    InvalidArgumentException(const char* msg = "Invalid argument")
        : BaseException(msg) {}    
};

class EmptyContainerException : public BaseException {
public:
    EmptyContainerException(const char* msg = "Empty container")
        : BaseException(msg) {}    
};

class IndexOutOFRangeException : public BaseException {
public:
    IndexOutOFRangeException(const char* msg = "Index out of range")
        : BaseException(msg) {}    
};



#endif /* _EXCEPTIONS_H_ */