/*!
\file locker.h "server\desktop\src\common\locker.h"
\authors Dmitry Zaitsev
\copyright � MSiYB 2017
\license GPL license
\version 1.0
\date 08 July 2017
*/

#pragma once

#ifdef _WIN32
#include "../cross/windows/winlocker.h"
typedef WinLocker OSLocker;
#elif _unix_
#include "../cross/unix/unixlocker.h"
typedef UnixLocker OSLocker;
#endif

/*!
\class Locker locker.h "server\desktop\src\common\locker.h"
\brief  RAII for mutex, spinlock, SRWlock, critical etc
*/
class Locker
{
public:
	/*!
	Lock object.
	\param[in] locker Locker object.
	*/
	Locker(ILocker& locker);

	/*!
	Unlock object.
	*/
	~Locker();

	/*!
	Determine locker object.
	\return Locker object.
	*/
	static ILocker* GetLocker(unsigned long timeout = INFINITE, bool oneProcess = false, bool useTry = false);

private:
	ILocker& _locker;	///< Locker object
};