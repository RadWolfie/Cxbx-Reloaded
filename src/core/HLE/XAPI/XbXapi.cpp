// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;;
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   core->HLE->XAPI->XbXapi.cpp
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
#define _XBOXKRNL_DEFEXTRN_

#define LOG_PREFIX CXBXR_MODULE::XAPI

#undef FIELD_OFFSET     // prevent macro redefinition warnings
/* prevent name collisions */
namespace xboxkrnl
{
	#include <xboxkrnl/xboxkrnl.h>
};

#include "XbXapi.hpp"
#include "OHCI/XbOHCI.hpp"
#include "Common/Logging.h"

_XTL_BEGIN

// ******************************************************************
// * patch: XInitDevices
// ******************************************************************
VOID (WINAPI *HLE_XInitDevices)
(
	DWORD                   dwPreallocTypeCount,
	PXDEVICE_PREALLOC_TYPE  PreallocTypes
);

// ******************************************************************
// * patch: XGetDevices
// ******************************************************************
DWORD (WINAPI *HLE_XGetDevices)
(
	PXPP_DEVICE_TYPE DeviceType
);

// ******************************************************************
// * patch: XGetDeviceChanges
// ******************************************************************
BOOL (WINAPI *HLE_XGetDeviceChanges)
(
	PXPP_DEVICE_TYPE DeviceType,
	PDWORD           pdwInsertions,
	PDWORD           pdwRemovals
);

// ******************************************************************
// * patch: XInputOpen
// ******************************************************************
HANDLE (WINAPI *HLE_XInputOpen)
(
	IN PXPP_DEVICE_TYPE             DeviceType,
	IN DWORD                        dwPort,
	IN DWORD                        dwSlot,
	IN PX_XINPUT_POLLING_PARAMETERS   pPollingParameters OPTIONAL
);

// ******************************************************************
// * patch: XInputClose
// ******************************************************************
VOID (WINAPI *HLE_XInputClose)
(
	IN HANDLE hDevice
);

// ******************************************************************
// * patch: XInputPoll
// ******************************************************************
DWORD (WINAPI *HLE_XInputPoll)
(
	IN HANDLE hDevice
);

// ******************************************************************
// * patch: XInputGetCapabilities
// ******************************************************************
DWORD (WINAPI *HLE_XInputGetCapabilities)
(
	IN  HANDLE               hDevice,
	OUT PX_XINPUT_CAPABILITIES pCapabilities
);

// ******************************************************************
// * patch: XInputGetState
// ******************************************************************
DWORD (WINAPI *HLE_XInputGetState)
(
	IN  HANDLE         hDevice,
	OUT PX_XINPUT_STATE  pState
);

// ******************************************************************
// * patch: XInputSetState
// ******************************************************************
DWORD (WINAPI *HLE_XInputSetState)
(
	IN     HANDLE           hDevice,
	IN OUT PX_XINPUT_FEEDBACK pFeedback
);

// ******************************************************************
// * patch: XGetDeviceEnumerationStatus
// ******************************************************************
DWORD (WINAPI *HLE_XGetDeviceEnumerationStatus)();

// ******************************************************************
// * patch: XInputGetDeviceDescription
// ******************************************************************
DWORD (WINAPI *HLE_XInputGetDeviceDescription)
(
	HANDLE  hDevice,
	PVOID   pDescription
);

// ******************************************************************
// * patch: SetThreadPriorityBoost
// ******************************************************************
BOOL (WINAPI *HLE_SetThreadPriorityBoost)
(
	HANDLE  hThread,
	BOOL    DisablePriorityBoost
);

// ******************************************************************
// * patch: SetThreadPriority
// ******************************************************************
BOOL (WINAPI *HLE_SetThreadPriority)
(
	HANDLE  hThread,
	int     nPriority
);


// ******************************************************************
// * patch: GetThreadPriority
// ******************************************************************
int (WINAPI *HLE_GetThreadPriority)
(
	HANDLE  hThread
);

// ******************************************************************
// * patch: GetExitCodeThread
// ******************************************************************
BOOL (WINAPI *HLE_GetExitCodeThread)
(
	HANDLE  hThread,
	LPDWORD lpExitCode
);

// ******************************************************************
// * patch: XapiThreadStartup
// ******************************************************************
VOID (WINAPI *HLE_XapiThreadStartup)
(
	DWORD dwDummy1,
	DWORD dwDummy2
);

// ******************************************************************
// * patch: XRegisterThreadNotifyRoutine
// ******************************************************************
VOID (WINAPI *HLE_XRegisterThreadNotifyRoutine)
(
	PXTHREAD_NOTIFICATION   pThreadNotification,
	BOOL                    fRegister
);

// ******************************************************************
// * patch: CreateFiber
// ******************************************************************
LPVOID (WINAPI *HLE_CreateFiber)
(
	DWORD                   dwStackSize,
	LPFIBER_START_ROUTINE   lpStartRoutine,
	LPVOID                  lpParameter
);

// ******************************************************************
// * patch: DeleteFiber
// ******************************************************************
VOID (WINAPI *HLE_DeleteFiber)
(
	LPVOID  lpFiber
);

// ******************************************************************
// * patch: SwitchToFiber
// ******************************************************************
VOID (WINAPI *HLE_SwitchToFiber)
(
	LPVOID  lpFiber
);

// ******************************************************************
// * patch: ConvertThreadToFiber
// ******************************************************************
LPVOID (WINAPI *HLE_ConvertThreadToFiber)
(
	LPVOID lpParameter
);

// ******************************************************************
// * patch: QueryPerformanceCounter
// ******************************************************************
BOOL (WINAPI *HLE_QueryPerformanceCounter)
(
	LARGE_INTEGER * lpPerformanceCount
);

// ******************************************************************
// * patch: QueueUserAPC
// ******************************************************************
DWORD (WINAPI *HLE_QueueUserAPC)
(
	PAPCFUNC    pfnAPC,
	HANDLE      hThread,
	DWORD       dwData
);

// ******************************************************************
// * patch: GetOverlappedResult
// ******************************************************************
BOOL (WINAPI *HLE_GetOverlappedResult)
(
	HANDLE          hFile,
	LPOVERLAPPED    lpOverlapped,
	LPDWORD         lpNumberOfBytesTransferred,
	BOOL            bWait
);

// ******************************************************************
// * patch: XLaunchNewImageA
// ******************************************************************
DWORD (WINAPI *HLE_XLaunchNewImageA)
(
	LPCSTR          lpTitlePath,
	PLAUNCH_DATA    pLaunchData
);

// ******************************************************************
// * patch: XGetLaunchInfo
// ******************************************************************
DWORD (WINAPI *HLE_XGetLaunchInfo)
(
	PDWORD          pdwLaunchDataType,
	PLAUNCH_DATA    pLaunchData
);

// ******************************************************************
// * patch: XSetProcessQuantumLength
// ******************************************************************
VOID (WINAPI *HLE_XSetProcessQuantumLength)
(
	DWORD dwMilliseconds
);

// ******************************************************************
// * patch: SignalObjectAndWait
// ******************************************************************
DWORD (WINAPI *HLE_SignalObjectAndWait)
(
	HANDLE  hObjectToSignal,
	HANDLE  hObjectToWaitOn,
	DWORD   dwMilliseconds,
	BOOL    bAlertable
);

// ******************************************************************
// * patch: timeSetEvent
// ******************************************************************
MMRESULT (WINAPI *HLE_timeSetEvent)
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
MMRESULT (WINAPI *HLE_timeKillEvent)
(
	UINT uTimerID
);

// ******************************************************************
// * patch: RaiseException
// ******************************************************************
VOID (WINAPI *HLE_RaiseException)
(
	DWORD           dwExceptionCode,       // exception code
	DWORD           dwExceptionFlags,      // continuable exception flag
	DWORD           nNumberOfArguments,    // number of arguments
	CONST ULONG_PTR *lpArguments           // array of arguments
);

// ******************************************************************
// patch: XMountMUA
// ******************************************************************
DWORD (WINAPI *HLE_XMountMUA)
(
	DWORD dwPort,
	DWORD dwSlot,
	PCHAR pchDrive
);

// ******************************************************************
// * patch: XMountMURootA
// ******************************************************************
DWORD (WINAPI *HLE_XMountMURootA)
(
	DWORD dwPort,
	DWORD dwSlot,
	PCHAR pchDrive
);

// ******************************************************************
// * patch: OutputDebugStringA
// ******************************************************************
VOID (WINAPI *HLE_OutputDebugStringA)
(
	IN LPCSTR lpOutputString
);

_XTL_END
