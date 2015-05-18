#include "ini_parser.h"


namespace qh
{
    INIParser::INIParser()
    {
    
    }
    
    INIParser::~INIParser()
    {
    
    }

    //去除首尾的其他字符
    void Trim(std::string &str, const std::string &charToTrim = " \r\t\n", int mode = 0)
    {
        size_t start = str.find_first_not_of(charToTrim);
	if(std::string::npos == start)
	{
	    str.erase();
	    return;
	}
	if(mode < 2)
	    str = str.substr(start, str.size()-start);
	if(mode != 1)
	    str = str.substr(0, str.find_last_not_of(charToTrim)+1);
    }
   
    void INIParser::ParseSection(std::string &str, std::string &section, const std::string & key_value_seperator)
    {
        section = str;
	if(std::string::npos != str.find(key_value_seperator))
	{
	    std::string key = str.substr(0, str.find(key_value_seperator));
	    std::string value = str.substr(str.find(key_value_seperator)+key_value_seperator.size());
            mapResult.insert(std::pair<std::string, std::string>(section+key, value));

	}
	return;
    }

    bool INIParser::Parse(const std::string& ini_file_path)
    {
        std::ifstream inputFile(ini_file_path.c_str());
	std::string strFile;
	if(inputFile.is_open())
	    return false;
	
	std::string str;
        while(std::getline(inputFile, str))
	{
	    Trim(str);
            strFile = strFile + str + "\n";
	}

        Parse(strFile.c_str(), strFile.size());
        inputFile.close();
	return true;
    }

    bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator, const std::string& key_value_seperator)
    {
	std::string strIniData(ini_data, ini_data_len);
        
        strIniData += line_seperator;
	size_t position = strIniData.find(line_seperator);
	while(std::string::npos != position)
	{
	    std::string str = strIniData.substr(0, position);
            size_t lineSepLen = line_seperator.size();
	    strIniData.erase(0, position+lineSepLen);
            position = strIniData.find(line_seperator);
	    Trim(str);
	    if(str.size() > 0)
	    {
	        std::string section("");
	        ParseSection(str, section, key_value_seperator);
	    }
	}
	return true;
    }

    
    const std::string & INIParser::Get(const std::string &key, bool *found)
    {
        std::map<std::string, std::string>::iterator iter;
        iter = mapResult.find(key);
	if(mapResult.end() == iter)
	{
	    if(NULL != found)
	        *found = false;
            static std::string res("");
	    return res;
	}
	else
	{
	    if(NULL != found)
	        *found = true;
            return mapResult[key];
	}
    }


    const std::string & INIParser::Get(const std::string & section, const std::string & key, bool * found)
    {
        return Get(section+key, found);
    }

}
