#include <windows.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "CFileSet.h"
#include "utils.h"

CFileSet::CFileSet (const std::wstring &path) {
	WIN32_FIND_DATA fd;

	HANDLE hFind=::FindFirstFile(path.c_str(), &fd);
	if(hFind != INVALID_HANDLE_VALUE)
    {
        do{
			// discard the directorys
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == false) {
				files.push_back(fd);
			}
         } while(::FindNextFile(hFind, &fd));

        ::FindClose(hFind);
    } else {
		throw std::runtime_error("Invalid handle value, the path contains an error or a directory is not available.");
	}
}

void CFileSet::save(const std::wstring &database) const {
	std::ofstream os(database, std::ios::binary | std::ios::trunc);
	if (!os)
	{
		throw std::exception("(ofstream) error while opening database file.");
	}
	for each (auto file in files) {
		// Save all data in the file
		os.write(reinterpret_cast<char*>(&file), sizeof(file));
	}
	os.close();
}

void CFileSet::compare(const std::wstring &database) {
	// vector contains the previous state of the directory
	std::vector<WIN32_FIND_DATA> previous;

	// Loading data from a file (if it exists)
	if (::GetFileAttributes(database.c_str()) != DWORD(-1)) {
		std::ifstream is(database, std::ios::binary);

		WIN32_FIND_DATA fd;
		is.read(reinterpret_cast<char*>(&fd), sizeof(fd));
		if (is.good()) {
			do {
				previous.push_back(fd);
				is.read(reinterpret_cast<char*>(&fd), sizeof(fd));
			} while (!is.eof());
		}
		is.close();
	}

	// If the vector is empty, all files are considered new.
	if (previous.empty()) {
		for each (auto file in files) {
			std::wcout << "[NEW] " << file.cFileName << std::endl;
		}
	// Otherwise, we must compare the previous and current states
	} else {
		using namespace utils;
		//Sort two vectors.
		fdcmp cmp;
		std::sort(previous.begin(), previous.end(), cmp);
		std::sort(files.begin(), files.end(), cmp);

		std::vector<WIN32_FIND_DATA>::iterator previousIt = previous.begin();
		std::vector<WIN32_FIND_DATA>::iterator filesIt = files.begin();

		while (previousIt!=previous.end() && filesIt!=files.end()) {
			// If nothing has changed
			if (*previousIt == *filesIt) {
				std::wcout << "[OK] " << (*previousIt).cFileName << std::endl;
				previousIt++;
				filesIt++;
			// If something has changed (except for name)
			} else if (*previousIt != *filesIt) {
				std::wcout << "[MOD] " << (*previousIt).cFileName << std::endl;
				previousIt++;
				filesIt++;
			} else if (*previousIt < *filesIt) {
				std::wcout << "[NEW] " << (*filesIt).cFileName << std::endl;
				filesIt++;
			} else {
				std::wcout << "[DEL] " << (*previousIt).cFileName << std::endl;
				previousIt++;
			}
		}
		// clean the debris))
		while (previousIt!=previous.end()) {
			std::wcout << "[DEL] " << (*previousIt).cFileName << std::endl;
			previousIt++;
		}
		while (filesIt!=files.end()) {
			std::wcout << "[NEW] " << (*filesIt).cFileName << std::endl;
			filesIt++;
		}
	}
}