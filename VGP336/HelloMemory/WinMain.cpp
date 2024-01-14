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
	Student(const std::string&name,int Mark)
		:mName(name)
		,mMark(Mark)
	{

	}
	void SetName(const std::string& name)
	{
		mName = name;

	}

	void SetStudent(int Mark)
	{
		mMark = Mark;
	}
private:
	std::string mName;
	int mMark;
};
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	TypedAllocator studentPool = TypedAllocator<Student>("StudentPool", 200);

	Student* a = studentPool.New("Jon");
	Student* b = studentPool.New("Winter");

	std::vector<Student*> students;
	int count = 100;

	for (int i = 0; i < 100; ++i)
	{
		std::string name = "Student" + std::to_string(i);
		students.push_back(studentPool.New(name));
	}
	for (int i = 0; i < 20; ++i)
	{
		auto student = students.back();
		students.pop_back();
		studentPool.Delete(student);

	}

	for (int i = 0; i < 50; ++i)
	{
		std::string name = "Student" + std::to_string(i);
		students.push_back(studentPool.New(name));
	} 



	for (auto student : students)
	{
		studentPool.Delete(student);
	}

	studentPool.Delete(a);
	studentPool.Delete(b);

	return(0);
}