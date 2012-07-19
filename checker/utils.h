#ifndef _UTILS_H_
#define _UTILS_H_

#include <windows.h>

namespace utils
{
	/**
	* Predicate
	* Checks the inequality of the two structures.
	*
	* @param lhs - structure for check.
	* @param rhs - structure for check.
	*
	*/
	struct fdcmp {
		bool operator() (const WIN32_FIND_DATA& lhs, const WIN32_FIND_DATA& rhs);
	};

	/**
	* Checks equality of two structures on all fields.
	*
	* @param lhs - structure for check.
	* @param rhs - structure for check.
	*
	*/
	bool operator==(const WIN32_FIND_DATA& lhs, const WIN32_FIND_DATA& rhs);

	/**
	* Checks equality of two structures on all fields.
	*
	* @param lhs - structure for check.
	* @param rhs - structure for check.
	*
	*/
	bool operator!=(const WIN32_FIND_DATA& lhs, const WIN32_FIND_DATA& rhs);

	/**
	* Checks changes of two structures (their connection is determined by a name).
	*
	* @param lhs - structure for check.
	* @param rhs - structure for check.
	*
	*/
	bool operator<(const WIN32_FIND_DATA& lhs, const WIN32_FIND_DATA& rhs);

	/**
	* Checks equality of two strings.
	*
	* @param lhs - string for check.
	* @param rhs - string for check.
	*
	*/
	bool IsStringEqual(const TCHAR *lhs, const TCHAR *rhs);

} // namespace utils

#endif //_UTILS_H_