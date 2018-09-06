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
// *   src->core->HLE->XAPI->OHCI->OHCIPlugins.cpp
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
// *  (c) 2018 RadWolfie
// *
// *  All rights reserved
// *
// ******************************************************************
#define _XBOXKRNL_DEFEXTRN_

#define LOG_PREFIX CXBXR_MODULE::OHCI

#include "Logging.h"

#include "OHCIPlugins.h"

_XTL_BEGIN

void init_xapi_ohci_plugins()
{
	// Set all OCHI to nullptr by default
	HLE_XGetDeviceChanges = nullptr;
	HLE_XGetDeviceEnumerationStatus = nullptr;
	HLE_XGetDevices = nullptr;
	HLE_XInitDevices = nullptr;
	HLE_XInputClose = nullptr;
	HLE_XInputGetCapabilities = nullptr;
	HLE_XInputGetDeviceDescription = nullptr;
	HLE_XInputGetState = nullptr;
	HLE_XInputOpen = nullptr;
	HLE_XInputPoll = nullptr;
	HLE_XInputSetState = nullptr;

	// Check which plugin to use then initialize specific plugin.
	init_xapi_ohci_plugin_xinput();
}

_XTL_END
