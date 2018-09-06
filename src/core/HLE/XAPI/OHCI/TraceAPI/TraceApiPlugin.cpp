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
// *   core->HLE->XAPI->OHCI->TraceAPI->TraceApiPlugin.cpp
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
// *  (c) 2018 RadWolfie
// *
// *  All rights reserved
// *
// ******************************************************************
#define _XBOXKRNL_DEFEXTRN_

#define LOG_PREFIX CXBXR_MODULE::OHCI

#include "CxbxKrnl/CxbxKrnl.h"
#include "Logging.h"
#include "core/HLE/CommonHLE.h"
#include "core/HLE/Intercept.hpp"

_XTL_BEGIN

// ******************************************************************
// * patch: XInitDevices
// ******************************************************************
static VOID WINAPI EMUPATCH(XInitDevices)
(
	DWORD                   dwPreallocTypeCount,
	PXDEVICE_PREALLOC_TYPE  PreallocTypes
)
{
	LOG_FUNC_BEGIN
		LOG_FUNC_ARG(dwPreallocTypeCount)
		LOG_FUNC_ARG((DWORD)PreallocTypes)
	LOG_FUNC_END;

	XB_trampoline(VOID, WINAPI, XInitDevices, (DWORD, PXDEVICE_PREALLOC_TYPE));
	XB_XInitDevices(dwPreallocTypeCount, PreallocTypes);
}

// ******************************************************************
// * patch: XGetDevices
// ******************************************************************
static DWORD WINAPI EMUPATCH(XGetDevices)
(
	PXPP_DEVICE_TYPE DeviceType
)
{
	LOG_FUNC_ONE_ARG(DeviceType);

	XB_trampoline(DWORD, WINAPI, XGetDevices, (PXPP_DEVICE_TYPE));
	DWORD ret = XB_XGetDevices(DeviceType);

	RETURN(ret);
}

// ******************************************************************
// * patch: XGetDeviceChanges
// ******************************************************************
static BOOL WINAPI EMUPATCH(XGetDeviceChanges)
(
	PXPP_DEVICE_TYPE DeviceType,
	PDWORD           pdwInsertions,
	PDWORD           pdwRemovals
)
{
	LOG_FUNC_BEGIN
		LOG_FUNC_ARG(DeviceType)
		LOG_FUNC_ARG(pdwInsertions)
		LOG_FUNC_ARG(pdwRemovals)
	LOG_FUNC_END;

	XB_trampoline(BOOL, WINAPI, XGetDeviceChanges, (PXPP_DEVICE_TYPE, PDWORD, PDWORD));
	BOOL ret = XB_XGetDeviceChanges(DeviceType, pdwInsertions, pdwRemovals);

	RETURN(ret);
}

// ******************************************************************
// * patch: XInputOpen
// ******************************************************************
static HANDLE WINAPI EMUPATCH(XInputOpen)
(
	IN PXPP_DEVICE_TYPE             DeviceType,
	IN DWORD                        dwPort,
	IN DWORD                        dwSlot,
	IN PX_XINPUT_POLLING_PARAMETERS pPollingParameters OPTIONAL
)
{
	LOG_FUNC_BEGIN
		LOG_FUNC_ARG(DeviceType)
		LOG_FUNC_ARG(dwPort)
		LOG_FUNC_ARG(dwSlot)
		LOG_FUNC_ARG(pPollingParameters)
	LOG_FUNC_END;

	XB_trampoline(HANDLE, WINAPI, XInputOpen, (PXPP_DEVICE_TYPE, DWORD, DWORD, PX_XINPUT_POLLING_PARAMETERS));
	HANDLE ret = XB_XInputOpen(DeviceType, dwPort, dwSlot, pPollingParameters);

	RETURN(ret);
}

// ******************************************************************
// * patch: XInputClose
// ******************************************************************
static VOID WINAPI EMUPATCH(XInputClose)
(
	IN HANDLE hDevice
)
{
	LOG_FUNC_ONE_ARG(hDevice);

	XB_trampoline(VOID, WINAPI, XInputClose, (HANDLE));
	XB_XInputClose(hDevice);
}

// ******************************************************************
// * patch: XInputPoll
// ******************************************************************
static DWORD WINAPI EMUPATCH(XInputPoll)
(
	IN HANDLE hDevice
)
{
	LOG_FUNC_ONE_ARG(hDevice);

	XB_trampoline(DWORD, WINAPI, XInputPoll, (HANDLE));
	DWORD ret = XB_XInputPoll(hDevice);

	RETURN(ret);
}

// ******************************************************************
// * patch: XInputGetCapabilities
// ******************************************************************
static DWORD WINAPI EMUPATCH(XInputGetCapabilities)
(
	IN  HANDLE               hDevice,
	OUT PX_XINPUT_CAPABILITIES pCapabilities
)
{
	LOG_FUNC_BEGIN
		LOG_FUNC_ARG(hDevice)
		LOG_FUNC_ARG_OUT(pCapabilities)
	LOG_FUNC_END;

	XB_trampoline(DWORD, WINAPI, XInputGetCapabilities, (HANDLE, PX_XINPUT_CAPABILITIES));
	DWORD ret = XB_XInputGetCapabilities(hDevice, pCapabilities);

	RETURN(ret);
}

// ******************************************************************
// * patch: XInputGetState
// ******************************************************************
static DWORD WINAPI EMUPATCH(XInputGetState)
(
	IN  HANDLE         hDevice,
	OUT PX_XINPUT_STATE  pState
)
{
	LOG_FUNC_BEGIN
		LOG_FUNC_ARG(hDevice)
		LOG_FUNC_ARG_OUT(pState)
	LOG_FUNC_END;

	XB_trampoline(DWORD, WINAPI, XInputGetState, (HANDLE, PX_XINPUT_STATE));
	DWORD ret = XB_XInputGetState(hDevice, pState);

	RETURN(ret);
}

// ******************************************************************
// * patch: XInputSetState
// ******************************************************************
static DWORD WINAPI EMUPATCH(XInputSetState)
(
	IN     HANDLE           hDevice,
	IN OUT PX_XINPUT_FEEDBACK pFeedback
)
{
	LOG_FUNC_BEGIN
		LOG_FUNC_ARG(hDevice)
		LOG_FUNC_ARG(pFeedback)
	LOG_FUNC_END;

	XB_trampoline(DWORD, WINAPI, XInputSetState, (HANDLE, PX_XINPUT_FEEDBACK));
	DWORD ret = XB_XInputSetState(hDevice, pFeedback);

	RETURN(ret);
}

#if 0 // TODO: Should it be handle by kernel or OHCI?
// ******************************************************************
// patch: XMountMUA
// ******************************************************************
static DWORD WINAPI EMUPATCH(XMountMUA)
(
	DWORD dwPort,
	DWORD dwSlot,
	PCHAR pchDrive
)
{
	LOG_FUNC_BEGIN
		LOG_FUNC_ARG(dwPort)
		LOG_FUNC_ARG(dwSlot)
		LOG_FUNC_ARG(pchDrive)
		LOG_FUNC_END;

	XB_trampoline(DWORD, WINAPI, XMountMUA, (DWORD, DWORD, PCHAR));
	DWORD ret = XB_XMountMUA(dwPort, dwSlot, pchDrive);

	RETURN(ret);
}
#endif

// ******************************************************************
// * patch: XGetDeviceEnumerationStatus
// ******************************************************************
static DWORD WINAPI EMUPATCH(XGetDeviceEnumerationStatus)()
{
	LOG_FUNC();

	XB_trampoline(DWORD, WINAPI, XGetDeviceEnumerationStatus, (VOID));
	DWORD ret = XB_XGetDeviceEnumerationStatus();

	RETURN(ret);
}

// ******************************************************************
// * patch: XInputGetDeviceDescription
// ******************************************************************
static DWORD WINAPI EMUPATCH(XInputGetDeviceDescription)
(
	HANDLE  hDevice,
	PVOID   pDescription
)
{
	LOG_FUNC_BEGIN
		LOG_FUNC_ARG(hDevice)
		LOG_FUNC_ARG(pDescription)
	LOG_FUNC_END;

	XB_trampoline(DWORD, WINAPI, XInputGetDeviceDescription, (HANDLE, PVOID));
	DWORD ret = XB_XInputGetDeviceDescription(hDevice, pDescription);

	RETURN(ret);
}

#if 0 // TODO: Should it be handle by kernel or OHCI?
// ******************************************************************
// * patch: XMountMURootA
// ******************************************************************
DWORD WINAPI EMUPATCH(XMountMURootA)
(
	DWORD dwPort,
	DWORD dwSlot,
	PCHAR pchDrive
)
{
	LOG_FUNC_BEGIN
		LOG_FUNC_ARG(dwPort)
		LOG_FUNC_ARG(dwSlot)
		LOG_FUNC_ARG(pchDrive)
		LOG_FUNC_END;

	XB_trampoline(DWORD, WINAPI, XMountMURootA, (DWORD, DWORD, PCHAR));
	DWORD ret = XB_XMountMURootA(dwPort, dwSlot, pchDrive);

	RETURN(ret);
}
#endif

// ******************************************************************
// * Initialize TraceAPI Plugin
// ******************************************************************
void init_xapi_ohci_plugin_trace_api()
{
	HLE_XGetDeviceChanges = EMUPATCH(XGetDeviceChanges);
	HLE_XGetDeviceEnumerationStatus = EMUPATCH(XGetDeviceEnumerationStatus);
	HLE_XGetDevices = EMUPATCH(XGetDevices);
	HLE_XInitDevices = EMUPATCH(XInitDevices);
	HLE_XInputClose = EMUPATCH(XInputClose);
	HLE_XInputGetCapabilities = EMUPATCH(XInputGetCapabilities);
	HLE_XInputGetDeviceDescription = EMUPATCH(XInputGetDeviceDescription);
	HLE_XInputGetState = EMUPATCH(XInputGetState);
	HLE_XInputOpen = EMUPATCH(XInputOpen);
	HLE_XInputPoll = EMUPATCH(XInputPoll);
	HLE_XInputSetState = EMUPATCH(XInputSetState);
}
_XTL_END
