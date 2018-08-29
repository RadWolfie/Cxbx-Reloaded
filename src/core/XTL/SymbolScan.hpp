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
// *   src->core->XTL->SymbolScan.hpp
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
#ifndef SYMBOLSCAN_HPP
#define SYMBOLSCAN_HPP
#pragma once

#include "core/XTL/XTL.hpp"
#include "CxbxKrnl/CxbxKrnl.h"
#pragma comment(lib, "XbSymbolDatabase.lib")
#include "../import/XbSymbolDatabase/XbSymbolDatabase.h"

#include "DSound/DSound.hpp"

#include <map>
#include <unordered_map>
#include <subhook.h>

extern std::map<std::string, xbaddr> g_SymbolAddresses;
extern std::unordered_map<std::string, subhook::Hook> g_FunctionHooks;

extern bool bLLE_APU; // Set this to true for experimental APU (sound) LLE
extern bool bLLE_GPU; // Set this to true for experimental GPU (graphics) LLE
extern bool bLLE_USB; // Set this to true for experimental USB (input) LLE
extern bool bLLE_JIT; // Set this to true for experimental JIT

void SymbolScanXbe(Xbe::Header *pXbeHeader);

std::string GetDetectedSymbolName(xbaddr address, int *symbolOffset);
void* GetXboxFunctionPointer(std::string functionName);

#endif
