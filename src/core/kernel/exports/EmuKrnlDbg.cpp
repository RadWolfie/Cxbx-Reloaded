// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// ******************************************************************
// *
// *  This file is part of the Cxbx project.
// *
// *  Cxbx and Cxbe are free software; you can redistribute them
// *  and/or modify them under the terms of the GNU General Public
// *  License as published by the Free Software Foundation; either
// *  version 2 of the license, or (at your option) any later version.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// *  GNU General Public License for more details.
// *
// *  You should have recieved a copy of the GNU General Public License
// *  along with this program; see the file COPYING.
// *  If not, write to the Free Software Foundation, Inc.,
// *  59 Temple Place - Suite 330, Bostom, MA 02111-1307, USA.
// *
// *  (c) 2002-2003 Aaron Robinson <caustik@caustik.com>
// *  (c) 2016 Patrick van Logchem <pvanlogchem@gmail.com>
// *
// *  All rights reserved
// *
// ******************************************************************

#define LOG_PREFIX CXBXR_MODULE::DBG


#include <core\kernel\exports\xboxkrnl.h> // For DbgPrint, etc.
#include "Logging.h" // For LOG_FUNC()
#include "EmuKrnlLogging.h"

// prevent name collisions
namespace NtDll
{
#include "core\kernel\support\EmuNtDll.h"
};


#include "core\kernel\support\Emu.h" // For EmuLog(LOG_LEVEL::WARNING, )

// ******************************************************************
// * 0x0005 - DbgBreakPoint()
// ******************************************************************
XBSYSAPI EXPORTNUM(5) xbox::void_xt NTAPI xbox::DbgBreakPoint()
{
	LOG_FUNC();

	LOG_UNIMPLEMENTED();
}

// ******************************************************************
// * 0x0006 - DbgBreakPointWithStatus()
// ******************************************************************
XBSYSAPI EXPORTNUM(6) xbox::void_xt NTAPI xbox::DbgBreakPointWithStatus
(
	IN ulong_xt Status 
)
{
	LOG_FUNC_ONE_ARG(Status);

	LOG_UNIMPLEMENTED();
}

// ******************************************************************
// * 0x0007 - DbgLoadImageSymbols()
// ******************************************************************
XBSYSAPI EXPORTNUM(7) xbox::ntstatus_xt NTAPI xbox::DbgLoadImageSymbols
(
	IN PANSI_STRING Name,
	IN PVOID Base,
	IN ulong_ptr_xt ProcessId
)
{
	LOG_FUNC_BEGIN;
		LOG_FUNC_ARG(Name)
		LOG_FUNC_ARG(Base)
		LOG_FUNC_ARG(ProcessId)
		LOG_FUNC_END;

	NTSTATUS result = S_OK;

	LOG_UNIMPLEMENTED();

	RETURN(result);
}

// ******************************************************************
// * 0x0008 - DbgPrint()
// ******************************************************************
XBSYSAPI EXPORTNUM(8) xbox::ulong_xt _cdecl xbox::DbgPrint
(
	PCHAR  Format, ...
)
{
	LOG_FUNC_BEGIN;
		LOG_FUNC_ARG(Format)
		LOG_FUNC_ARG("...")
		LOG_FUNC_END;

	if (Format != nullptr) {
		va_list argp;
		va_start(argp, Format);
		static std::vector<char> message;
		bool bRet = EmuLogFormatMessage(message, Format, argp);
		va_end(argp);

		// Allow DbgPrint to be disabled
		if (bRet) {
			EmuLog(LOG_LEVEL::INFO, "%s", message.data());
		}
	}

	RETURN(xbox::status_success);
}

// ******************************************************************
// * 0x000A - DbgPrompt()
// ******************************************************************
// Source:ReactOS
XBSYSAPI EXPORTNUM(10) xbox::ulong_xt NTAPI xbox::DbgPrompt
(
	IN PCCH Prompt,
	OUT PCH Response,
	IN ulong_xt MaximumResponseLength
)
{
	LOG_FUNC_BEGIN;
		LOG_FUNC_ARG(Prompt)
		LOG_FUNC_ARG_OUT(Response)
		LOG_FUNC_ARG(MaximumResponseLength)
		LOG_FUNC_END;

	NTSTATUS result = S_OK;

	LOG_UNIMPLEMENTED();

	RETURN(result);
}

// ******************************************************************
// * 0x000B - DbgUnLoadImageSymbols()
// ******************************************************************
// Source:ReactOS
XBSYSAPI EXPORTNUM(11) xbox::void_xt NTAPI xbox::DbgUnLoadImageSymbols
(
	IN PANSI_STRING Name,
	IN PVOID Base,
	IN ulong_ptr_xt ProcessId
)
{
	LOG_FUNC_BEGIN;
		LOG_FUNC_ARG(Name)
		LOG_FUNC_ARG(Base)
		LOG_FUNC_ARG(ProcessId)
		LOG_FUNC_END;

	LOG_UNIMPLEMENTED();
}
