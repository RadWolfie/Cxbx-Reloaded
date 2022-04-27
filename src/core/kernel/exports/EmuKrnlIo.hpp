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
// *  All rights reserved
// *
// ******************************************************************
#pragma once

#include "core/kernel/common/types.h"

namespace xbox
{
	ntstatus_xt NTAPI IopParseDevice(
		IN PVOID ParseObject,
		IN struct _OBJECT_TYPE* ObjectType,
		IN ulong_xt Attributes,
		IN OUT POBJECT_STRING CompleteName,
		IN OUT POBJECT_STRING RemainingName,
		IN OUT PVOID Context OPTIONAL,
		OUT PVOID* Object
	);
};
