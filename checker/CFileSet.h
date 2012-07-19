#ifndef _CFILESET_H_
#define _CFILESET_H_

#include <string>
#include <vector>
#include <windows.h>

/**
* class CFileSet
*
* Contains information on files
* in a certain directory, allows
* to save and compare this information.
*
*/
class CFileSet {
public:
	/**
	* Constructor
	* Makes the file list in the specified directory.
	*
	* @param path - ath to the directory with the files.
	*
	*/
	CFileSet(const std::wstring &path);
	
	/**
	* Saves a current status to the specified file.
	*
	* @param database - file for saving an information.
	*
	*/
	void save(const std::wstring &database) const;
	
	/**
	* Compares a current state of files with the state saved in the specified file (if the file exists).
	*
	* @param lhs - file with the previous state.
	*
	*/
	void compare(const std::wstring &database);
private:
	//
	std::vector<WIN32_FIND_DATA> files;
};

#endif //_CFILESET_H_