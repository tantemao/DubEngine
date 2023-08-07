#include<DubEngine/Inc/DubEngine.h>
using namespace DubEngine;
using namespace DubEngine::Core;

class Student
{
public:
	Student() = default;
	Student(const std::string& name)
		:mName(name)
	{

	}
	Student(const std::string&name,int classMark)
		:mName(name)
		,mClassMark(classMark)
	{

	}
	void SetName(const std::string& name)
	{
		mName = name;

	}

	void SetStudent(int classMark)
	{
		mClassMark = classMark;
	}
private:
	std::string mName;
	int mClassMark;
};
int WINAPI WinmAIN(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	TypedAllocator studentPool = TypedAllocator<Student>("StudentPool", 100);
	Student* a = studentPool.New("Frank");
	Student* b = studentPool.New("Leon",97);

	a->SetName("Frank");
	b->SetName("Leon");


	studentPool.Delete(a);
	studentPool.Delete(b);

	return(0);
}