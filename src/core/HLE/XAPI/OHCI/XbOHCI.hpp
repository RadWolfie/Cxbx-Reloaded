// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;;
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   src->core->HLE->XAPI->OHCI->XbOHCI.hpp
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
#ifndef XBOHCI_HPP
#define XBOHCI_HPP

_XTL_BEGIN

// ******************************************************************
// * XINPUT_POLLING_PARAMETERS
// ******************************************************************
typedef struct _X_XINPUT_POLLING_PARAMETERS
{
    BYTE       fAutoPoll        : 1;
    BYTE       fInterruptOut    : 1;
    BYTE       ReservedMBZ1     : 6;
    BYTE       bInputInterval;
    BYTE       bOutputInterval;
    BYTE       ReservedMBZ2;
}
X_XINPUT_POLLING_PARAMETERS, *PX_XINPUT_POLLING_PARAMETERS;

// ******************************************************************
// * POLLING_PARAMETERS_HANDLE
// ******************************************************************
typedef struct _X_POLLING_PARAMETERS_HANDLE
{
    X_XINPUT_POLLING_PARAMETERS *pPollingParameters;

    DWORD dwPort;
}
X_POLLING_PARAMETERS_HANDLE, *PX_POLLING_PARAMETERS_HANDLE;

// ******************************************************************
// * XPP_DEVICE_TYPE
// ******************************************************************
typedef struct _XPP_DEVICE_TYPE
{
	ULONG CurrentConnected;
	ULONG ChangeConnected;
	ULONG PreviousConnected;
}
XPP_DEVICE_TYPE, *PXPP_DEVICE_TYPE;

// ******************************************************************
// * XPP_DEVICE_INPUTSTATE_DESC
// ******************************************************************
typedef struct _XPP_DEVICE_INPUTSTATE_DESC
{
    unsigned char ucSize;       //size of InputState, doesn't include the dwPacketNumber, seems DWORD aligned.
    unsigned char * pInputState;//pointer to InputState
    unsigned char ucUnknown[3]; //for DWORD align
}
XPP_DEVICE_INPUTSTATE_DESC, *PXPP_DEVICE_INPUTSTATE_DESC;

// ******************************************************************
// * XPP_DEVICE_FEEDBACK_DESC
// ******************************************************************
typedef struct _XPP_DEVICE_FEEDBACK_DESC
{
    unsigned char ucSize;       //size of Feedback, not include Feedback_Header,  seems DWORD aligned.
    unsigned char * pFeedback;  //pointer to Feedback
    unsigned char ucUnknown[3]; //for DWORD align
}
XPP_DEVICE_FEEDBACK_DESC, *PXPP_DEVICE_FEEDBACK_DESC;

// ******************************************************************
// * XID_TYPE_INFORMATION
// ******************************************************************
typedef struct _XID_TYPE_INFORMATION
{
	UCHAR				ucType;
    BYTE				bRemainingHandles;
	UCHAR				ucUnknown[2];//probably for DWORD align
	PXPP_DEVICE_TYPE    XppType;//pointer to DeviceType structure.
    PXPP_DEVICE_INPUTSTATE_DESC pInputStateDesc;//pointer to InputStateDesc structure
    PXPP_DEVICE_FEEDBACK_DESC pFeedbackDesc;//pointer to FeedbackDesc structure
    DWORD *             pConstant;//always 0x0801
    void *              pFunction;//unknown function for device related process
    DWORD				dwEndZero;//last DWROD, always 0
} XID_TYPE_INFORMATION, *PXID_TYPE_INFORMATION;

// ******************************************************************
// * XDEVICE_PREALLOC_TYPE
// ******************************************************************
typedef struct _XDEVICE_PREALLOC_TYPE 
{
    PXPP_DEVICE_TYPE DeviceType;
    DWORD            dwPreallocCount;
} 
XDEVICE_PREALLOC_TYPE, *PXDEVICE_PREALLOC_TYPE;

// ******************************************************************
// * XINPUT_GAMEPAD for xbox, xbox's GAMEPAD struc differs from PC's
// ******************************************************************
typedef struct _X_XINPUT_GAMEPAD
{
    WORD    wButtons;
    BYTE    bAnalogButtons[8];
    SHORT   sThumbLX;
    SHORT   sThumbLY;
    SHORT   sThumbRX;
    SHORT   sThumbRY;
}
X_XINPUT_GAMEPAD, *PX_XINPUT_GAMEPAD;

// ******************************************************************
// * X_SBC_GAMEPAD for xbox SteelBatalion GAMEPAD struc 
// ******************************************************************
typedef struct _X_SBC_GAMEPAD {
    WORD    wButtons[3];
    SHORT   sAimingX;
    SHORT   sAimingY;
    SHORT   sRotationLever;//maybe only high byte was used.
    SHORT   sSightChangeX;
    SHORT   sSightChangeY;
    WORD    wLeftPedal;//maybe only high byte was used.
    WORD    wMiddlePedal;//maybe only high byte was used.
    WORD    wRightPedal;//maybe only high byte was used.
    UCHAR   ucTunerDial;//low nibble, The 9 o'clock postion is 0, and the 6 o'clock position is 12. The blank area between the 6 and 9 o'clock positions is 13, 14, and 15 clockwise.
    UCHAR   ucGearLever;//GearLever 1~5 for gear 1~5, 7~13 for gear R,N,1~5, 15 for gear R. we use the continues range from 7~13
}
X_SBC_GAMEPAD, *PX_SBC_GAMEPAD;

// ******************************************************************
// * masks for digital buttons of X_SBC_GAMEPAD
// ******************************************************************

#define    X_SBC_GAMEPAD_W0_RIGHTJOYMAINWEAPON      0x0001
#define    X_SBC_GAMEPAD_W0_RIGHTJOYFIRE            0x0002
#define    X_SBC_GAMEPAD_W0_RIGHTJOYLOCKON          0x0004
#define    X_SBC_GAMEPAD_W0_EJECT                   0x0008
#define    X_SBC_GAMEPAD_W0_COCKPITHATCH            0x0010
#define    X_SBC_GAMEPAD_W0_IGNITION                0x0020
#define    X_SBC_GAMEPAD_W0_START                   0x0040
#define    X_SBC_GAMEPAD_W0_MULTIMONOPENCLOSE       0x0080
#define    X_SBC_GAMEPAD_W0_MULTIMONMAPZOOMINOUT    0x0100
#define    X_SBC_GAMEPAD_W0_MULTIMONMODESELECT      0x0200
#define    X_SBC_GAMEPAD_W0_MULTIMONSUBMONITOR      0x0400
#define    X_SBC_GAMEPAD_W0_MAINMONZOOMIN           0x0800
#define    X_SBC_GAMEPAD_W0_MAINMONZOOMOUT          0x1000
#define    X_SBC_GAMEPAD_W0_FUNCTIONFSS             0x2000
#define    X_SBC_GAMEPAD_W0_FUNCTIONMANIPULATOR     0x4000
#define    X_SBC_GAMEPAD_W0_FUNCTIONLINECOLORCHANGE 0x8000
#define    X_SBC_GAMEPAD_W1_WASHING                 0x0001
#define    X_SBC_GAMEPAD_W1_EXTINGUISHER            0x0002
#define    X_SBC_GAMEPAD_W1_CHAFF                   0x0004
#define    X_SBC_GAMEPAD_W1_FUNCTIONTANKDETACH      0x0008
#define    X_SBC_GAMEPAD_W1_FUNCTIONOVERRIDE        0x0010
#define    X_SBC_GAMEPAD_W1_FUNCTIONNIGHTSCOPE      0x0020
#define    X_SBC_GAMEPAD_W1_FUNCTIONF1              0x0040
#define    X_SBC_GAMEPAD_W1_FUNCTIONF2              0x0080
#define    X_SBC_GAMEPAD_W1_FUNCTIONF3              0x0100
#define    X_SBC_GAMEPAD_W1_WEAPONCONMAIN           0x0200
#define    X_SBC_GAMEPAD_W1_WEAPONCONSUB            0x0400
#define    X_SBC_GAMEPAD_W1_WEAPONCONMAGAZINE       0x0800
#define    X_SBC_GAMEPAD_W1_COMM1                   0x1000
#define    X_SBC_GAMEPAD_W1_COMM2                   0x2000
#define    X_SBC_GAMEPAD_W1_COMM3                   0x4000
#define    X_SBC_GAMEPAD_W1_COMM4                   0x8000
#define    X_SBC_GAMEPAD_W2_COMM5                   0x0001
#define    X_SBC_GAMEPAD_W2_LEFTJOYSIGHTCHANGE      0x0002
#define    X_SBC_GAMEPAD_W2_TOGGLEFILTERCONTROL     0x0004
#define    X_SBC_GAMEPAD_W2_TOGGLEOXYGENSUPPLY      0x0008
#define    X_SBC_GAMEPAD_W2_TOGGLEFUELFLOWRATE      0x0010
#define    X_SBC_GAMEPAD_W2_TOGGLEBUFFREMATERIAL    0x0020
#define    X_SBC_GAMEPAD_W2_TOGGLEVTLOCATION        0x0040

// ******************************************************************
// * enum for feedback status variables of X_SBC_FEEDBACK, it's a byte array after FeedbackHeader, each variable take 1 nibble, that's half byte.
// ******************************************************************
#define    X_SBC_FEEDBACK_EMERGENCYEJECT            0
#define    X_SBC_FEEDBACK_COCKPITHATCH              1
#define    X_SBC_FEEDBACK_IGNITION                  2
#define    X_SBC_FEEDBACK_START                     3
#define    X_SBC_FEEDBACK_OPENCLOSE                 4
#define    X_SBC_FEEDBACK_MAPZOOMINOUT              5
#define    X_SBC_FEEDBACK_MODESELECT                6
#define    X_SBC_FEEDBACK_SUBMONITORMODESELECT      7
#define    X_SBC_FEEDBACK_MAINMONITORZOOMIN         8
#define    X_SBC_FEEDBACK_MAINMONITORZOOMOUT        9
#define    X_SBC_FEEDBACK_FORECASTSHOOTINGSYSTEM    10
#define    X_SBC_FEEDBACK_MANIPULATOR               11
#define    X_SBC_FEEDBACK_LINECOLORCHANGE           12
#define    X_SBC_FEEDBACK_WASHING                   13
#define    X_SBC_FEEDBACK_EXTINGUISHER              14
#define    X_SBC_FEEDBACK_CHAFF                     15
#define    X_SBC_FEEDBACK_TANKDETACH                16
#define    X_SBC_FEEDBACK_OVERRIDE                  17
#define    X_SBC_FEEDBACK_NIGHTSCOPE                18
#define    X_SBC_FEEDBACK_F1                        19
#define    X_SBC_FEEDBACK_F2                        20
#define    X_SBC_FEEDBACK_F3                        21
#define    X_SBC_FEEDBACK_MAINWEAPONCONTROL         22
#define    X_SBC_FEEDBACK_SUBWEAPONCONTROL          23
#define    X_SBC_FEEDBACK_MAGAZINECHANGE            24
#define    X_SBC_FEEDBACK_COMM1                     25
#define    X_SBC_FEEDBACK_COMM2                     26
#define    X_SBC_FEEDBACK_COMM3                     27
#define    X_SBC_FEEDBACK_COMM4                     28
#define    X_SBC_FEEDBACK_COMM5                     29
#define    X_SBC_FEEDBACK_UNKNOWN                   30
#define    X_SBC_FEEDBACK_GEARR                     31
#define    X_SBC_FEEDBACK_GEARN                     32
#define    X_SBC_FEEDBACK_GEAR1                     33
#define    X_SBC_FEEDBACK_GEAR2                     34
#define    X_SBC_FEEDBACK_GEAR3                     35
#define    X_SBC_FEEDBACK_GEAR4                     36
#define    X_SBC_FEEDBACK_GEAR5                     37

#define    X_SBC_FEEDBACK_MAX                       38

// ******************************************************************
// * XINPUT_RUMBLE
// ******************************************************************
typedef struct _X_XINPUT_RUMBLE
{
    WORD   wLeftMotorSpeed;
    WORD   wRightMotorSpeed;
}
X_XINPUT_RUMBLE, *PX_XINPUT_RUMBLE;

// ******************************************************************
// * XINPUT_CAPABILITIES
// ******************************************************************
typedef struct _X_XINPUT_CAPABILITIES
{
    BYTE SubType;
    WORD Reserved;

    union
    {
        X_XINPUT_GAMEPAD Gamepad;
    }
    In;

    union
    {
        X_XINPUT_RUMBLE Rumble;
    }
    Out;
}
X_XINPUT_CAPABILITIES, *PX_XINPUT_CAPABILITIES;

// ******************************************************************
// * Device XBOX Input Device Types 
// ******************************************************************
// all game controller use 0x01 GAMEPAD device type. then specify the subtype in returned Capabilities when XInputGetCapabilities called.
#define X_XINPUT_DEVTYPE_GAMEPAD              0x01
// SteelBatalion controller is the only one with special device type other than 1.
#define X_XINPUT_DEVTYPE_STEELBATALION        0x80

// ******************************************************************
// * Device XBOX Input Device SubTypes, for use in XINPUT_CAPABILITIES
// ******************************************************************
//general GAMEPAD uses subtype 0x01.
#define X_XINPUT_DEVSUBTYPE_GC_GAMEPAD              0x01 
//SteelBatallion controller uses subtype 0x02
#define X_XINPUT_DEVSUBTYPE_GC_GAMEPAD_ALT          0x02
#define X_XINPUT_DEVSUBTYPE_GC_WHEEL                0x10
#define X_XINPUT_DEVSUBTYPE_GC_ARCADE_STICK         0x20
#define X_XINPUT_DEVSUBTYPE_GC_DIGITAL_ARCADE_STICK 0x21
#define X_XINPUT_DEVSUBTYPE_GC_FLIGHT_STICK         0x30
#define X_XINPUT_DEVSUBTYPE_GC_SNOWBOARD            0x40
#define X_XINPUT_DEVSUBTYPE_GC_LIGHTGUN             0x50
#define X_XINPUT_DEVSUBTYPE_GC_RADIO_FLIGHT_CONTROL 0x60
#define X_XINPUT_DEVSUBTYPE_GC_FISHING_ROD          0x70
#define X_XINPUT_DEVSUBTYPE_GC_DANCEPAD             0x80

// ******************************************************************
// * XINPUT_STATE for xbox, xbox uses different Gamepad struce.
// ******************************************************************
typedef struct _X_XINPUT_STATE
{
    DWORD dwPacketNumber;

    union
    {
        X_XINPUT_GAMEPAD Gamepad;
    };
}
X_XINPUT_STATE, *PX_XINPUT_STATE;

// ******************************************************************
// * offsets into analog button array
// ******************************************************************
#define X_XINPUT_GAMEPAD_A                0
#define X_XINPUT_GAMEPAD_B                1
#define X_XINPUT_GAMEPAD_X                2
#define X_XINPUT_GAMEPAD_Y                3
#define X_XINPUT_GAMEPAD_BLACK            4
#define X_XINPUT_GAMEPAD_WHITE            5
#define X_XINPUT_GAMEPAD_LEFT_TRIGGER     6
#define X_XINPUT_GAMEPAD_RIGHT_TRIGGER    7

// ******************************************************************
// * masks for digital buttons
// ******************************************************************
#define X_XINPUT_GAMEPAD_DPAD_UP          0x00000001
#define X_XINPUT_GAMEPAD_DPAD_DOWN        0x00000002
#define X_XINPUT_GAMEPAD_DPAD_LEFT        0x00000004
#define X_XINPUT_GAMEPAD_DPAD_RIGHT       0x00000008
#define X_XINPUT_GAMEPAD_START            0x00000010
#define X_XINPUT_GAMEPAD_BACK             0x00000020
#define X_XINPUT_GAMEPAD_LEFT_THUMB       0x00000040
#define X_XINPUT_GAMEPAD_RIGHT_THUMB      0x00000080

// ******************************************************************
// * XINPUT_FEEDBACK_HEADER
// ******************************************************************
#include "AlignPrefix1.h"
typedef struct _X_XINPUT_FEEDBACK_HEADER
{
    DWORD           dwStatus;
    HANDLE OPTIONAL hEvent;
    BYTE            Reserved[58];
}
#include "AlignPosfix1.h"
X_XINPUT_FEEDBACK_HEADER, *PX_XINPUT_FEEDBACK_HEADER;

// ******************************************************************
// * XINPUT_FEEDBACK
// ******************************************************************
typedef struct _X_XINPUT_FEEDBACK
{
    X_XINPUT_FEEDBACK_HEADER Header;

    union
    {
        X_XINPUT_RUMBLE Rumble;
    };
}
X_XINPUT_FEEDBACK, *PX_XINPUT_FEEDBACK;

// ******************************************************************
// * XINPUT_DEVICE_INFO
// ******************************************************************

typedef struct _X_XINPUT_DEVICE_INFO
{

    UCHAR                   ucType;             //xbox controller type
    UCHAR                   ucSubType;          //xbox controller subtype
    UCHAR				    ucInputStateSize;   //xbox controller input state size in bytes, not include dwPacketNumber
    UCHAR				    ucFeedbackSize;     //xbox controller feedback size in bytes, not include FeedbackHeader
    PXPP_DEVICE_TYPE        DeviceType;        //pointer to DeviceType structure.
}
X_XINPUT_DEVICE_INFO, *PX_XINPUT_DEVICE_INFO;

#define X_XONTROLLER_HOST_BRIDGE_HOSTTYPE_NOTCONNECT      0x00000000
#define X_XONTROLLER_HOST_BRIDGE_HOSTTYPE_XINPUT         0x00000001
#define X_XONTROLLER_HOST_BRIDGE_HOSTTYPE_DINPUT         0x00000002
#define X_XONTROLLER_HOST_BRIDGE_HOSTTYPE_VIRTUAL_SBC    0x00000080

//this structure is for use of tracking the xbox controllers assigned to 4 ports.
//user can specify the corresponding host input device
//whether it's XInput, directinput, or an virtual custom controller.
// ******************************************************************
// * X_CONTROLLER_HOST_BRIDGE 
// ******************************************************************
typedef struct _X_CONTROLLER_HOST_BRIDGE
{
    HANDLE                  hXboxDevice;        //xbox device handle to this controller, we use the address of this bridge as the handle, only set after opened. cleared after closed.
    DWORD                   dwXboxPort;         //xbox port# for this xbox controller
    PX_XINPUT_POLLING_PARAMETERS pXboxXPP;      //pointer to xbox polling parameter
    DWORD                   dwHostType;         //specify host input corresponding to this controller
                                                //0 not connected,
                                                //1 connect with XInput,
                                                //2 connect with directinput,
                                                //3 or above connect virtual custom controller
    DWORD                   dwHostPort;         //port of the host input device being bridged.
                                                //if hostinputtype==1 for using XInput, and hostport==2,
                                                //then bridge to XInput player 3 (port started from 0).

    //members listed below comes from interpreting xbe device table 
    X_XINPUT_DEVICE_INFO    XboxDeviceInfo;
    void *                  pXboxState;             //not used currently, keep it just in case
    PX_XINPUT_FEEDBACK_HEADER pXboxFeedbackHeader;  //pointer to feedback header,keep this in track for IO_PENDING status tracking.
    DWORD                   dwLatency;
}
X_CONTROLLER_HOST_BRIDGE, *PX_CONTROLLER_HOST_BRIDGE;


// ******************************************************************
// * XBGAMEPAD // this structure seems unused at all. anyway, keep it here.
// ******************************************************************
struct XBGAMEPAD : public X_XINPUT_GAMEPAD
{
	FLOAT      fX1;
	FLOAT      fY1;
	FLOAT      fX2;
	FLOAT      fY2;
	WORD       wLastButtons;
	BOOL       bLastAnalogButtons[8];
	WORD       wPressedButtons;
	BOOL       bPressedAnalogButtons[8];
	X_XINPUT_RUMBLE	Rumble;
	X_XINPUT_FEEDBACK	Feedback;
	X_XINPUT_CAPABILITIES caps;
	HANDLE     hDevice;
	BOOL       bInserted;
	BOOL       bRemoved;
};

// ******************************************************************
// * XGetDeviceEnumerationStatus flags
// ******************************************************************
#define XDEVICE_ENUMERATION_IDLE 0
#define XDEVICE_ENUMERATION_BUSY 1

// ******************************************************************
// * patch: XInitDevices
// ******************************************************************
extern VOID (WINAPI *HLE_XInitDevices)
(
	DWORD                   dwPreallocTypeCount,
	PXDEVICE_PREALLOC_TYPE  PreallocTypes
);

// ******************************************************************
// * patch: XGetDevices
// ******************************************************************
extern DWORD (WINAPI *HLE_XGetDevices)
(
	XPP_DEVICE_TYPE *DeviceType
);

// ******************************************************************
// * patch: XGetDeviceChanges
// ******************************************************************
extern BOOL (WINAPI *HLE_XGetDeviceChanges)
(
	PXPP_DEVICE_TYPE DeviceType,
	PDWORD           pdwInsertions,
	PDWORD           pdwRemovals
);

// ******************************************************************
// * patch: XInputOpen
// ******************************************************************
extern HANDLE (WINAPI *HLE_XInputOpen)
(
	IN PXPP_DEVICE_TYPE             DeviceType,
	IN DWORD                        dwPort,
	IN DWORD                        dwSlot,
	IN PX_XINPUT_POLLING_PARAMETERS   pPollingParameters OPTIONAL
);

// ******************************************************************
// * patch: XInputClose
// ******************************************************************
extern VOID (WINAPI *HLE_XInputClose)
(
	IN HANDLE hDevice
);

// ******************************************************************
// * patch: XInputPoll
// ******************************************************************
extern DWORD (WINAPI *HLE_XInputPoll)
(
	IN HANDLE Device
);

// ******************************************************************
// * patch: XInputGetCapabilities
// ******************************************************************
extern DWORD (WINAPI *HLE_XInputGetCapabilities)
(
	IN  HANDLE               hDevice,
	OUT PX_XINPUT_CAPABILITIES pCapabilities
);

// ******************************************************************
// * patch: XInputGetState
// ******************************************************************
extern DWORD (WINAPI *HLE_XInputGetState)
(
	IN  HANDLE         hDevice,
	OUT PX_XINPUT_STATE  pState
);

// ******************************************************************
// * patch: XInputSetState
// ******************************************************************
extern DWORD (WINAPI *HLE_XInputSetState)
(
	IN     HANDLE           hDevice,
	IN OUT PX_XINPUT_FEEDBACK pFeedback
);

// ******************************************************************
// * patch: XGetDeviceEnumerationStatus
// ******************************************************************
extern DWORD (WINAPI *HLE_XGetDeviceEnumerationStatus)();

// ******************************************************************
// * patch: XInputGetDeviceDescription
// ******************************************************************
extern DWORD (WINAPI *HLE_XInputGetDeviceDescription)
(
	HANDLE  hDevice,
	PVOID   pDescription
);

_XTL_END

#endif
