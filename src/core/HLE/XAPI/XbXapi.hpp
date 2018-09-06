// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;;
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   src->core->HLE->XAPI->XbXapi.h
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
// *
// *  All rights reserved
// *
// ******************************************************************
#ifndef XBXAPI_H
#define XBXAPI_H

// ******************************************************************
// * calling conventions
// ******************************************************************
#define WINAPI              __stdcall

#include <Windows.h> // NOTE: Currently workaround, we need more complete list plus move XTL stuff out of XbXapi.hpp file

#define _XTL_BEGIN namespace XTL {
#define _XTL_END }

_XTL_BEGIN

// ******************************************************************
// * Basic types
// ******************************************************************
typedef char                CHAR, CCHAR;
typedef short               SHORT, CSHORT;
typedef long                LONG;
typedef unsigned char       UCHAR;
typedef unsigned char       BYTE;
typedef unsigned char       BOOLEAN;
typedef unsigned short      USHORT;
typedef unsigned short      WORD;
typedef unsigned long       ULONG;
typedef unsigned long       DWORD;
typedef unsigned long       SIZE_T, *PSIZE_T;
typedef unsigned long       ACCESS_MASK, *PACCESS_MASK;
typedef unsigned long       PHYSICAL_ADDRESS;
typedef long                INT_PTR;
typedef unsigned __int64    ULONGLONG;

// xapi
typedef int                 BOOL;
typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;
typedef LONG                HRESULT;

// ******************************************************************
// * Pointer types
// ******************************************************************
typedef CHAR               *PCHAR;
typedef CHAR               *PCSZ;
typedef BYTE               *PBYTE;
typedef BOOLEAN            *PBOOLEAN;
typedef UCHAR              *PUCHAR;
typedef USHORT             *PUSHORT;
typedef ULONG              *PULONG;
typedef DWORD              *LPDWORD;
typedef ACCESS_MASK        *PACCESS_MASK;
typedef LONG               *LONG_PTR;
typedef ULONG              *ULONG_PTR;
typedef INT_PTR            *PINT_PTR;
// Workaround for MAXULONG_PTR: in XTL, ULONG_PTR is defined as a pointer type instead of being an integer
static constexpr unsigned int XTL_MAXULONG_PTR = ~((::ULONG_PTR)0);
#ifndef VOID
	#define VOID void
#endif
typedef VOID               *PVOID, *LPVOID;
typedef void               *HANDLE;
typedef HANDLE             *PHANDLE;

// ******************************************************************
// * documentation purposes only
// ******************************************************************
#define EXPORTNUM(a)
#define UNALIGNED
#define OPTIONAL
#define IN
#define OUT

// ******************************************************************
// * LPSECURITY_ATTRIBUTES
// ******************************************************************
typedef void* LPSECURITY_ATTRIBUTES;

// ******************************************************************
// * PTHREAD_START_ROUTINE / LPTHREAD_START_ROUTINE
// ******************************************************************
typedef DWORD (WINAPI *PTHREAD_START_ROUTINE)
(
	LPVOID lpThreadParameter
);
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

// ******************************************************************
// * RTL_HEAP_PARAMETERS
// ******************************************************************
typedef struct _RTL_HEAP_PARAMETERS
{
	ULONG   Length;
	BYTE    Unknown[0x2C];
}
RTL_HEAP_PARAMETERS;

// ******************************************************************
// * XTHREAD_NOTIFY_PROC
// ******************************************************************
typedef VOID (WINAPI *XTHREAD_NOTIFY_PROC)(BOOL fCreate);

// ******************************************************************
// * XTHREAD_NOTIFICATION
// ******************************************************************
typedef struct _XTHREAD_NOTIFICATION
{
	LIST_ENTRY          Reserved;
	XTHREAD_NOTIFY_PROC pfnNotifyRoutine;
}
XTHREAD_NOTIFICATION, *PXTHREAD_NOTIFICATION;

// ******************************************************************
// * XCALCSIG_SIGNATURE
// ******************************************************************
#define XCALCSIG_SIGNATURE_SIZE         20

typedef struct _XCALCSIG_SIGNATURE
{
	BYTE    Signature[XCALCSIG_SIGNATURE_SIZE];
}
XCALCSIG_SIGNATURE, *PXCALCSIG_SIGNATURE;

#define XCALCSIG_FLAG_NON_ROAMABLE  (0x00000001)

// ******************************************************************
// * LAUNCH_DATA
// ******************************************************************
#define MAX_LAUNCH_DATA_SIZE    1024 * 3

typedef struct _LAUNCH_DATA 
{
	BYTE	Data[MAX_LAUNCH_DATA_SIZE];
} 
LAUNCH_DATA, *PLAUNCH_DATA;

#define LDT_TITLE                 0
#define LDT_FROM_DASHBOARD        2
#define LDT_FROM_DEBUGGER_CMDLINE 3
#define LDT_FROM_UPDATE           4

// ******************************************************************
// * XGetDeviceEnumerationStatus flags
// ******************************************************************
#define XDEVICE_ENUMERATION_IDLE 0
#define XDEVICE_ENUMERATION_BUSY 1

// ******************************************************************
// * macro: EMUPATCH - marker on patches on original Xbox functions
// ******************************************************************
#define EMUPATCH(Name) EmuPatch_##Name

// ******************************************************************
// * patch: XFormatUtilityDrive
// ******************************************************************
extern BOOL (WINAPI *HLE_XFormatUtilityDrive)();

#if 0 // Handled by ExQueryNonVolatileSetting(XC_MAX_OS) returning XBOX_USER_SETTINGS
// ******************************************************************
// * patch: GetTimeZoneInformation
// ******************************************************************
extern DWORD (WINAPI *HLE_GetTimeZoneInformation)
(
	OUT LPTIME_ZONE_INFORMATION lpTimeZoneInformation
);
#endif

// ******************************************************************
// * patch: CreateMutex
// ******************************************************************
extern HANDLE (WINAPI *HLE_CreateMutex)
(
	LPSECURITY_ATTRIBUTES   lpMutexAttributes,
	BOOL                    bInitialOwner,
	LPCSTR                  lpName
);

// ******************************************************************
// * patch: CloseHandle
// ******************************************************************
extern BOOL (WINAPI *HLE_CloseHandle)
(
	HANDLE hObject
);

// ******************************************************************
// * patch: SetThreadPriority
// ******************************************************************
extern BOOL (WINAPI *HLE_SetThreadPriority)
(
	HANDLE  hThread,
	int     nPriority
);

// ******************************************************************
// * patch: GetThreadPriority
// ******************************************************************
extern int (WINAPI *HLE_GetThreadPriority)
(
	HANDLE  hThread
);

// ******************************************************************
// * patch: SetThreadPriorityBoost
// ******************************************************************
extern BOOL (WINAPI *HLE_SetThreadPriorityBoost)
(
	HANDLE  hThread,
	BOOL    DisablePriorityBoost
);

// ******************************************************************
// * patch: GetExitCodeThread
// ******************************************************************
extern BOOL (WINAPI *HLE_GetExitCodeThread)
(
	HANDLE  hThread,
	LPDWORD lpExitCode
);

// ******************************************************************
// * patch: XapiThreadStartup
// ******************************************************************
extern VOID (WINAPI *HLE_XapiThreadStartup)
(
	DWORD dwDummy1,
	DWORD dwDummy2
);

/* Too High Level!
// ******************************************************************
// * patch: XapiSetupPerTitleDriveLetters
// ******************************************************************
NTSTATUS CDECL XapiSetupPerTitleDriveLetters(DWORD dwTitleId, LPCWSTR wszTitleName);
*/

// ******************************************************************
// * patch: XRegisterThreadNotifyRoutine
// ******************************************************************
extern VOID (WINAPI *HLE_XRegisterThreadNotifyRoutine)
(
	PXTHREAD_NOTIFICATION   pThreadNotification,
	BOOL                    fRegister
);

// ******************************************************************
// * patch: CreateFiber
// ******************************************************************
extern LPVOID (WINAPI *HLE_CreateFiber)
(
	DWORD                   dwStackSize,
	LPFIBER_START_ROUTINE   lpStartRoutine,
	LPVOID                  lpParameter
);

// ******************************************************************
// * patch: DeleteFiber
// ******************************************************************
extern VOID (WINAPI *HLE_DeleteFiber)
(
	LPVOID lpFiber
);

// ******************************************************************
// * patch: SwitchToFiber
// ******************************************************************
extern VOID (WINAPI *HLE_SwitchToFiber)
(
	LPVOID lpFiber 
);

// ******************************************************************
// * patch: ConvertThreadToFiber
// ******************************************************************
extern LPVOID (WINAPI *HLE_ConvertThreadToFiber)
(
	LPVOID lpParameter
);

// ******************************************************************
// * patch: XapiFiberStartup
// ******************************************************************
extern VOID (WINAPI *HLE_XapiFiberStartup)(DWORD dwDummy);

// ******************************************************************
// * patch: QueryPerformanceCounter
// ******************************************************************
extern BOOL (WINAPI *HLE_QueryPerformanceCounter)
(
	LARGE_INTEGER *lpPerformanceCount
);

// ******************************************************************
// * patch: QueueUserAPC
// ******************************************************************
extern DWORD (WINAPI *HLE_QueueUserAPC)
(
	PAPCFUNC    pfnAPC,
	HANDLE      hThread,
	DWORD       dwData
);

#if 0 // Handled by WaitForSingleObject
// ******************************************************************
// * patch: GetOverlappedResult
// ******************************************************************
extern BOOL (WINAPI *HLE_GetOverlappedResult)
(
	HANDLE          hFile,
	LPOVERLAPPED    lpOverlapped,
	LPDWORD         lpNumberOfBytesTransferred,
	BOOL            bWait
);
#endif

// ******************************************************************
// * patch: XLaunchNewImageA
// ******************************************************************
extern DWORD (WINAPI *HLE_XLaunchNewImageA)
(
	LPCSTR          lpTitlePath,
	PLAUNCH_DATA    pLaunchData
);

#if 0 // patch disabled
// ******************************************************************
// * patch: XGetLaunchInfo
// ******************************************************************
extern DWORD (WINAPI *HLE_XGetLaunchInfo)
(
	PDWORD          pdwLaunchDataType,
	PLAUNCH_DATA    pLaunchData
);
#endif

// ******************************************************************
// * patch: XSetProcessQuantumLength
// ******************************************************************
extern VOID (WINAPI *HLE_XSetProcessQuantumLength)
(
	DWORD dwMilliseconds
);

// ******************************************************************
// * patch: SignalObjectAndWait
// ******************************************************************
extern DWORD (WINAPI *HLE_SignalObjectAndWait)
(
	HANDLE  hObjectToSignal,
	HANDLE  hObjectToWaitOn,
	DWORD   dwMilliseconds,
	BOOL    bAlertable
);

// ******************************************************************
// * patch: timeSetEvent
// ******************************************************************
extern MMRESULT (WINAPI *HLE_timeSetEvent)
(
	UINT            uDelay,
	UINT            uResolution,
	LPTIMECALLBACK  fptc,
	DWORD           dwUser,
	UINT            fuEvent
);

// ******************************************************************
// * patch: timeKillEvent
// ******************************************************************
extern MMRESULT (WINAPI *HLE_timeKillEvent)
(
	UINT uTimerID  
);

// ******************************************************************
// * patch: RaiseException
// ******************************************************************
extern VOID (WINAPI *HLE_RaiseException)
(
	DWORD           dwExceptionCode,       // exception code
	DWORD           dwExceptionFlags,      // continuable exception flag
	DWORD           nNumberOfArguments,    // number of arguments
	CONST ULONG_PTR *lpArguments           // array of arguments
);

// ******************************************************************
// * patch: lstrcmpiW
// ******************************************************************
extern int (WINAPI *HLE_lstrcmpiW)
(
	LPCWSTR lpString1,
	LPCWSTR lpString2
);

// ******************************************************************
// * patch: XMountMUA
// ******************************************************************
extern DWORD (WINAPI *HLE_XMountMUA)
(
	DWORD dwPort,
	DWORD dwSlot,
	PCHAR pchDrive
);

// ******************************************************************
// * patch: XMountMURootA
// ******************************************************************
extern DWORD (WINAPI *HLE_XMountMURootA)
(
	DWORD dwPort,
	DWORD dwSlot,
	PCHAR pchDrive
);

// ******************************************************************
// * patch: XMountAlternateTitleA
// ******************************************************************
/*extern DWORD (WINAPI *HLE_XMountAlternateTitleA)
(
	LPCSTR lpRootPath,
	DWORD  dwAltTitleId,
	PCHAR  pchDrive
);*/

// ******************************************************************
// * patch: XUnmountAlternateTitleA
// ******************************************************************
//extern DWORD (WINAPI *HLE_XUnmountAlternateTitleA)(CHAR chDrive);

// ******************************************************************
// * patch: MoveFileA
// ******************************************************************
extern BOOL (WINAPI *HLE_MoveFileA)
(
	LPCSTR lpExistingFileName,
	LPCSTR lpNewFileName
);

// ******************************************************************
// * patch: SwitchToThread
// ******************************************************************
extern BOOL (WINAPI *HLE_SwitchToThread)();

// ******************************************************************
// * patch: ReadFileEx
// ******************************************************************
extern BOOL (WINAPI *HLE_ReadFileEx)
(
	HANDLE hFile,                                       // handle to file
	LPVOID lpBuffer,                                    // data buffer
	DWORD nNumberOfBytesToRead,                         // number of bytes to read
	LPOVERLAPPED lpOverlapped,                          // offset
	LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine // completion routine
);

// ******************************************************************
// * patch: WriteFileEx
// ******************************************************************
extern BOOL (WINAPI *HLE_WriteFileEx)
(
	HANDLE hFile,                                       // handle to output file
	LPCVOID lpBuffer,                                   // data buffer
	DWORD nNumberOfBytesToWrite,                        // number of bytes to write
	LPOVERLAPPED lpOverlapped,                          // overlapped buffer
	LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine // completion routine
);

// ******************************************************************
// * patch: OutputDebugStringA
// ******************************************************************
extern VOID (WINAPI *HLE_OutputDebugStringA)
(
	IN LPCSTR lpOutputString
);

// s+
/* not necessary?
// ******************************************************************
// * patch: XCalculateSignatureBegin
// ******************************************************************
extern HANDLE (WINAPI *HLE_XCalculateSignatureBegin)
(
	DWORD dwFlags
);

// ******************************************************************
// * patch: XCalculateSignatureBegin
// ******************************************************************
extern HANDLE (WINAPI *HLE_XCalculateSignatureBeginEx)
(
	DWORD dwFlags,
	DWORD dwAltTitleId
);

// ******************************************************************
// * patch: XCalculateSignatureUpdate
// ******************************************************************
extern DWORD (WINAPI *HLE_XCalculateSignatureUpdate)
(
	HANDLE        hCalcSig,
	const BYTE   *pbData,
	ULONG         cbData
);

// ******************************************************************
// * patch: XCalculateSignatureEnd
// ******************************************************************
extern DWORD (WINAPI *HLE_XCalculateSignatureEnd)
(
	HANDLE                hCalcSig,
	PXCALCSIG_SIGNATURE   pSignature
);
//*/
// +s

_XTL_END

#endif
