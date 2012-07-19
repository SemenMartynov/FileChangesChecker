#include <windows.h>
#include <cstring> 
#include "utils.h"

namespace utils
{
	bool fdcmp::operator() (const WIN32_FIND_DATA& lhs, const WIN32_FIND_DATA& rhs) {
		return rhs < lhs;
	}

	bool operator==(const WIN32_FIND_DATA& lhs, const WIN32_FIND_DATA& rhs) {
		if ( lhs.dwFileAttributes == rhs.dwFileAttributes && // The file attributes of a file
			lhs.ftCreationTime.dwLowDateTime == rhs.ftCreationTime.dwLowDateTime && // when a file was created
			lhs.ftCreationTime.dwHighDateTime == rhs.ftCreationTime.dwHighDateTime &&
			lhs.ftLastAccessTime.dwLowDateTime == rhs.ftLastAccessTime.dwLowDateTime && // when the file was last read from, written to, or for executable files, run
			lhs.ftLastAccessTime.dwHighDateTime == rhs.ftLastAccessTime.dwHighDateTime &&
			lhs.ftLastWriteTime.dwLowDateTime == rhs.ftLastWriteTime.dwLowDateTime && // when the file was last written to, truncated, or overwritten
			lhs.ftLastWriteTime.dwHighDateTime == rhs.ftLastWriteTime.dwHighDateTime &&
			lhs.nFileSizeLow == rhs.nFileSizeLow && // file size
			lhs.nFileSizeHigh == rhs.nFileSizeHigh &&
			IsStringEqual(lhs.cFileName, rhs.cFileName)) // The name of the file.
			return true;
		else return false;
	}

	bool operator!=(const WIN32_FIND_DATA& lhs, const WIN32_FIND_DATA& rhs) {
		return IsStringEqual(lhs.cFileName, rhs.cFileName);
	}

	bool operator<(const WIN32_FIND_DATA& lhs, const WIN32_FIND_DATA& rhs) {
		if (wcscmp(lhs.cFileName, rhs.cFileName) < 0)
			return true;
		else return false;
	}

	bool IsStringEqual(const TCHAR *lhs, const TCHAR *rhs) {
		// It shall work quicker
		while(*lhs == *rhs) {
			if(*lhs==L'\0')
				return true;
			lhs++;
			rhs++;
		}
		return false;
	}
} // namespace utils