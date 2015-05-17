#include "qh_string.h"
#include <stdio.h>
#include <string.h>

namespace qh
{
    // TODO 将在这里写实现代码

    string::string()
        : data_(NULL), len_(0)
    {
    }

    string::string( const char* s )
    {
        if(NULL == s)
	{
	    data_ = NULL;
	    len_ = 0;
	    return;
	}
	len_ = strlen(s);
        data_ = new char[len_+1];
	strcpy(data_, s);
    }

    string::string( const char* s, size_t len )
    {
        
        if(NULL == s)
	{
	    data_ = NULL;
	    len_ = 0;
	    return;
	}
	size_t realLen = strlen(s);
	len_ = realLen > len ? len : realLen;
	data_ = new char[len_+1];
        strncpy(data_, s, len_+1);

    }



    string::string( const string& rhs )
    {
        len_ = rhs.size();
        if(0 == len_)
	{
	    data_ = NULL;
	    return;
	}
	data_ = new char[len_+1];
	strcpy(data_, rhs.c_str());
    }

    string& string::operator=( const string& rhs )
    {
        if(this == &rhs)
	    return *this;
	
	delete [] data_;
	len_ = rhs.size();
	data_ = new char(len_+1);
	strcpy(data_, rhs.c_str());
        
	return *this;
    }

    string::~string()
    {
        delete [] data_;
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        if(NULL == data_)
	    return NULL;
	else
	    return data_;
    }

    const char* string::c_str() const
    {
        if(NULL == data_)
	    return "";
	else
	    return data_;
    }

    char* string::operator[]( size_t index )
    {
        if(index > len_ || NULL == data_)
	    return NULL;
        return data_+index;
    }
}
