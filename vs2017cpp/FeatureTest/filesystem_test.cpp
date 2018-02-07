#include <filesystem>
#include <iostream>
#include <string>

// see Repo755: tr2_filesystem.md


using namespace std;
using namespace std::experimental;

void TestStandard17(void)
{
	string dpath("d:\\");
	filesystem::path dp(dpath);
	auto dspace = filesystem::space(dp);
	cout << dspace.capacity << endl;
}


void FileSystemTest(void)
{
	TestStandard17();
	string sysPath = "C:\\bin\\ss";

	cout << "sys::path operation" << endl;

	filesystem::path pathSys("C:\\bin\\ss\\test.txt");

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

	if (filesystem::is_directory(sysPath))
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
	for (auto it = filesystem::directory_iterator(sysPath), end = filesystem::directory_iterator();
		it != end; ++it)
	{
		filesystem::path subpath = it->path();
		cout << subpath.string() << endl;
	}
	cout << "********************************" << endl;

	cout << "find all sub items in a path" << endl;
	for (auto it = filesystem::recursive_directory_iterator(sysPath),
		end = filesystem::recursive_directory_iterator();
		it != end; ++it)
	{
		int level = it.depth();
		filesystem::path subpath = it->path();
		cout << level << " " << subpath.string() << endl;
	}
	cout << "********************************" << endl;
}