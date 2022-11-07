
#include "json.hpp"

#include <iterator>
#include <iostream>
#include <fstream>
#include <string>

#include <streambuf>


class redditPost_Json 
{
private:
	std::string author;
	std::string title;
public:
	void set(json::Value *v)
	{

	}
};

int main()
{
	std::ifstream in("../reddit.json");
	//std::istreambuf_iterator<char> first(in);
	//std::istreambuf_iterator<char> first(std::cin);
	//std::istreambuf_iterator<char> last;
	std::string str((std::istreambuf_iterator<char>(in)),
                 std::istreambuf_iterator<char>());
	std::string temp;

	json::Value* v = json::parse(str);
		for(std::string::iterator start = str.begin(); start != str.end(); start++)
		{
			if(*(static_cast<char*>(*start)) == "\"")
			{
				getline(start, temp, '\"');
				if(temp == "author")
				{
					getline(start, temp, '\"');
					std::cout << temp;
				}
			}
		}
	//std::cout << *v << '\n';

	redditPost_Json j;
	j.set(v);
}
