#include <memory>
#include <string>
#include <iostream>
#include "CFileSet.h"

int wmain(int argc, wchar_t **argv)
{
	setlocale(LC_ALL, "Russian");

	// directory with the files
	std::wstring path;
	// database
	std::wstring database;

	// If the database is defined...
	if (argc == 3) {
		path = argv[1];
		database = argv[2];
	// Otherwise, use the default database
	} else if (argc == 2) {
		path = argv[1];
		database = L"Database.bin";
	} else {
		std::cout << "usage:" << std::endl
		<< "\tchecker.exe path [database]" << std::endl
		<< "\tpath - path to the directory and mask (for example, c:\\windows\\*)," << std::endl
		<< "\tdatabase - name of the database (\"Database.bin\" by default)." << std::endl << std::endl;
		system("pause");
		return -1;
	}

	try {
		// Get the list of files
		std::unique_ptr<CFileSet> fileSet (new CFileSet(path));
		// Compare with the previous state
		fileSet->compare(database);
		// Save the current state.
		fileSet->save(database);
	}
	catch (std::exception &e)
	{
		std::cerr << "exception caught: " << e.what() << std::endl;
		return -1;
	}
	system("pause");
	return 0;
}