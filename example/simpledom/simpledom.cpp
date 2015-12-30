// JSON simple example
// This example does not handle errors.
// http://stackoverflow.com/questions/12742840/retrieving-a-nested-object-inside-a-json-string-using-rapidjson
// http://stackoverflow.com/questions/23887079/rapidjson-extract-key-and-value

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <vector>
#include <iostream>

using namespace rapidjson;

unsigned getNumberOfChild(Value& v)
{
    unsigned count = 0;
	for (Value::ConstMemberIterator iter = v.MemberBegin(); iter != v.MemberEnd(); ++iter){
		count++;
    }
	return count;
};

void getAllChildName(Value& v, std::vector<std::string>& ioList)
{
	std::vector<std::string> tmp;
    for (Value::ConstMemberIterator iter = v.MemberBegin(); iter != v.MemberEnd(); ++iter){

    	ioList.push_back(iter->name.GetString());
        //std::cout << iter->value.GetString();
    }

}

int main() {
    // 1. Parse a JSON string into DOM.
    const char* json = "{\"mainKey\": { \"BUSPT\": { \"code\":\"eus123\",\"integer\":10}, \"BUSPQ\" : {\"code\":\"eus246\",\"integer\":10}, \"aKey\" : \"it is really interesting\" } }";

    //std::cout << json;
    Document d;
    d.Parse(json);
    Value& mainKey = d["mainKey"];


    // 2. Modify it by DOM.
    Value& v = mainKey["BUSPT"];
    //std::cout << v.GetType();

    Value& v2 = v["integer"];
    //std::cout << v2.GetType();
    v2.SetInt(v2.GetInt() + 1);

    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    mainKey.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;


    std::cout << "Let's solve my problem ;)" << std::endl;

    // get number of child dirty way (making public attribute)
    mainKey.getData();
    std::cout << "size (dirty): " << mainKey.getData().o.size << std::endl;
    std::cout << "size (clean): " << getNumberOfChild(mainKey) << std::endl;


    // get all sub key
    std::cout << "Print all sub keys:" << std::endl;
    std::vector<std::string> vKey;
    getAllChildName(mainKey, vKey);
    for (std::vector<std::string>::iterator it = vKey.begin() ; it != vKey.end(); ++it)
    {
        std::cout << ' ' << *it << std::endl;
    }

    // get first key
    std::vector<std::string>::iterator it = vKey.begin();
    std::cout << "first key = " << *it << std::endl;

    return 0;
}
