#include <filesystem>
#include <iostream>
#include <string>

// see Repo755: tr2_filesystem.md


using namespace std;
using namespace std::tr2;

void TestStandard17(void)
{
	string dpath("d:\\");
	sys::path dp(dpath);
	auto dspace = sys::space(dp);
	cout << dspace.capacity << endl;
}


void FileSystemTest(void)
{
	TestStandard17();
	string sysPath = "C:\\bin\\ss";

	cout << "sys::path operation" << endl;

	sys::path pathSys("C:\\bin\\ss\\test.txt");

	// path.member                        
	cout << pathSys.filename() << endl;         // test.txt        
	cout << pathSys.stem() << endl;             // test       
	cout << pathSys.extension() << endl;        // .txt      
	cout << pathSys.has_extension() << endl;    // true                
	cout << pathSys.generic_string() << endl;   // C:/bin/ss/test.txt  
	cout << pathSys.u8string() << endl;         // C:\bin\ss\test.txt  
	cout << pathSys.root_path() << endl;        // C:\                 
	cout << pathSys.relative_path() << endl;    // bin\ss\test.txt     
	cout << pathSys.parent_path() << endl;      // C:\bin\ss           

	if (sys::is_directory(sysPath))
	{
		cout << pathSys << " is directory" << endl;
	}
	// part of path: 
	// C: / bin Python27 Tools
	cout << "each part: " << endl;
	for (auto it : pathSys)
	{
		cout << "\t" << it << endl;
	}

	cout << "********************************" << endl;

	cout << "find items in a path" << endl;
	for (auto it = sys::directory_iterator(sysPath), end = sys::directory_iterator();
		it != end; ++it)
	{
		sys::path subpath = it->path();
		cout << subpath.string() << endl;
	}
	cout << "********************************" << endl;

	cout << "find all sub items in a path" << endl;
	for (auto it = sys::recursive_directory_iterator(sysPath),
		end = sys::recursive_directory_iterator();
		it != end; ++it)
	{
		int level = it.depth();
		sys::path subpath = it->path();
		cout << level << " " << subpath.string() << endl;
	}
	cout << "********************************" << endl;
}