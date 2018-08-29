// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;;
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   src->core->XTL->DSound->DSoundX.h
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
// *  (c) 2017-2018 RadWolfie
// *
// *  All rights reserved
// *
// ******************************************************************
#ifndef DSOUNDX_H
#define DSOUNDX_H

#undef FIELD_OFFSET     // prevent macro redefinition warnings

#include <windows.h>
#include "core/XTL/XTL.hpp"

_XTL_BEGIN
// TODO: Move dsound headers outside of XTL when moving is done.
#include <dsound.h>
#include "d3dx9math.h"

#ifdef __cplusplus
extern "C" {
#endif

void CxbxInitAudio();

#ifdef __cplusplus
}
#endif

// EmuIDirectSoundBuffer_Play flags
#define X_DSBPLAY_LOOPING       0x00000001
#define X_DSBPLAY_FROMSTART     0x00000002
#define X_DSBPLAY_SYNCHPLAYBACK 0x00000004

// EmuIDirectSoundBuffer_Pause flags
#define X_DSBPAUSE_RESUME             0x00000000
#define X_DSBPAUSE_PAUSE              0x00000001
#define X_DSBPAUSE_SYNCHPLAYBACK      0x00000002

// EmuIDirectSoundStream_Pause flags
#define X_DSSPAUSE_RESUME             0x00000000
#define X_DSSPAUSE_PAUSE              0x00000001
#define X_DSSPAUSE_SYNCHPLAYBACK      0x00000002
#define X_DSSPAUSE_PAUSENOACTIVATE    0x00000003

// EmuIDirectSoundStream_FlushEx flags
#define X_DSSFLUSHEX_IMMEDIATE        0x00000000
#define X_DSSFLUSHEX_ASYNC            0x00000001
#define X_DSSFLUSHEX_ENVELOPE         0x00000002
#define X_DSSFLUSHEX_ENVELOPE2        0x00000004

// EmuIDirectSoundStream_GetStatus flags
#define X_DSSSTATUS_READY             0x00000001
#define X_DSSSTATUS_PLAYING           0x00010000
#define X_DSSSTATUS_PAUSED            0x00020000
#define X_DSSSTATUS_STARVED           0x00040000
#define X_DSSSTATUS_ENVELOPECOMPLETE  0x00080000

// EmuIDirectSoundBuffer_GetStatus flags
#define X_DSBSTATUS_PLAYING           0x00000001
#define X_DSBSTATUS_PAUSED            0x00000002
#define X_DSBSTATUS_LOOPING           0x00000004

// EmuIDirectSoundBuffer_StopEx flags
#define X_DSBSTOPEX_IMMEDIATE         0x00000000
#define X_DSBSTOPEX_ENVELOPE          0x00000001
#define X_DSBSTOPEX_RELEASEWAVEFORM   0x00000002
#define X_DSBSTOPEX_ALL               (X_DSBSTOPEX_ENVELOPE | X_DSBSTOPEX_RELEASEWAVEFORM)

// ******************************************************************
// * X_DSBUFFERDESC
// ******************************************************************
struct X_DSBUFFERDESC
{
    DWORD           dwSize;
    DWORD           dwFlags;
    DWORD           dwBufferBytes;
    LPWAVEFORMATEX  lpwfxFormat;
    LPVOID          lpMixBins;      // TODO: Implement
    DWORD           dwInputMixBin;
};

typedef VOID(CALLBACK *LPFNXMOCALLBACK)(LPVOID pStreamContext, LPVOID pPacketContext, DWORD dwStatus);

// ******************************************************************
// * X_DSSTREAMDESC
// ******************************************************************
struct X_DSSTREAMDESC
{
    DWORD                       dwFlags;
    DWORD                       dwMaxAttachedPackets;
    LPWAVEFORMATEX              lpwfxFormat;
    LPFNXMOCALLBACK             lpfnCallback;
    LPVOID                      lpvContext;
    PVOID                       lpMixBins;      // TODO: Implement
};

// ******************************************************************
// * REFERENCE_TIME
// ******************************************************************
typedef LONGLONG REFERENCE_TIME, *PREFERENCE_TIME, *LPREFERENCE_TIME;

// ******************************************************************
// * XMEDIAPACKET
// ******************************************************************
typedef struct _XMEDIAPACKET
{
    LPVOID pvBuffer;
    DWORD dwMaxSize;
    PDWORD pdwCompletedSize;
    PDWORD pdwStatus;
    union {
        HANDLE  hCompletionEvent;
        PVOID  pContext;
    };
    PREFERENCE_TIME prtTimestamp; // Not supported in xbox
}
XMEDIAPACKET, *PXMEDIAPACKET, *LPXMEDIAPACKET;

#define XMP_STATUS_SUCCESS          S_OK
#define XMP_STATUS_PENDING          E_PENDING
#define XMP_STATUS_FLUSHED          E_ABORT
#define XMP_STATUS_FAILURE          E_FAIL
#define XMP_STATUS_RELEASE_CXBXR    0xFFFFFFFF

// ******************************************************************
// * XMEDIAINFO
// ******************************************************************
typedef struct _XMEDIAINFO
{
    DWORD  dwFlags;
    DWORD  dwInputSize;
    DWORD  dwOutputSize;
    DWORD  dwMaxLookahead;
} 
XMEDIAINFO, *PXEIDIAINFO, *LPXMEDIAINFO;

// XMEDIAINFO Flags
#define XMO_STREAMF_FIXED_SAMPLE_SIZE           0x00000001      // The object supports only a fixed sample size
#define XMO_STREAMF_FIXED_PACKET_ALIGNMENT      0x00000002      // The object supports only a fixed packet alignment
#define XMO_STREAMF_INPUT_ASYNC                 0x00000004      // The object supports receiving input data asynchronously
#define XMO_STREAMF_OUTPUT_ASYNC                0x00000008      // The object supports providing output data asynchronously
#define XMO_STREAMF_IN_PLACE                    0x00000010      // The object supports in-place modification of data
#define XMO_STREAMF_MASK                        0x0000001F

// XDSMIXBIN Flags
enum {
    XDSMIXBIN_FRONT_LEFT        = 0,
    XDSMIXBIN_FRONT_RIGHT       = 1,
    XDSMIXBIN_FRONT_CENTER      = 2,
    XDSMIXBIN_LOW_FREQUENCY     = 3,
    XDSMIXBIN_BACK_LEFT         = 4,
    XDSMIXBIN_BACK_RIGHT        = 5,
    XDSMIXBIN_SPEAKERS_MAX      = 6 // Max count for speakers
};
// Other flags are used 

// ******************************************************************
// * X_DSMIXBINVOLUMEPAIR
// ******************************************************************
typedef struct _XDSMIXBINSVOLUMEPAIR {
    DWORD       dwMixBin;
    LONG        lVolume;
} X_DSMIXBINSVOLUMEPAIR, *X_LPDSMIXBINSVOLUMEPAIR;

// ******************************************************************
// * X_DSMB
// ******************************************************************
typedef struct _XDSMIXBINS {
    DWORD                       dwCount;
    X_LPDSMIXBINSVOLUMEPAIR     lpMixBinVolumePairs;
} X_DSMIXBINS, *X_LPDSMIXBINS;

// ******************************************************************
// * X_DSFILTERDESC
// ******************************************************************
struct X_DSFILTERDESC
{
    DWORD dwMode;
    DWORD dwQCoefficient;
    DWORD adwCoefficients[4];
};

// X_DSFILTERDESC modes
#define DSFILTER_MODE_BYPASS        0x00000000      // The filter is bypassed
#define DSFILTER_MODE_DLS2          0x00000001      // DLS2 mode
#define DSFILTER_MODE_PARAMEQ       0x00000002      // Parametric equalizer mode
#define DSFILTER_MODE_MULTI         0x00000003      // Multifunction mode

// ******************************************************************
// * DSLFODESC
// ******************************************************************
typedef struct _DSLFODESC
{
    DWORD dwLFO;
    DWORD dwDelay;
    DWORD dwDelta;
    LONG lPitchModulation;
    LONG lFilterCutOffRange;
    LONG lAmplitudeModulation;
}
DSLFODESC, *LPCDSLFODESC;

// ******************************************************************
// * XBOXADPCMWAVEFORMAT
// ******************************************************************
typedef struct xbox_adpcmwaveformat_tag
{
    WAVEFORMATEX    wfx;                    // WAVEFORMATEX data
    WORD            wSamplesPerBlock;       // Number of samples per encoded block.  It must be 64.
}
XBOXADPCMWAVEFORMAT, *PXBOXADPCMWAVEFORMAT, *LPXBOXADPCMWAVEFORMAT;

typedef const XBOXADPCMWAVEFORMAT *LPCXBOXADPCMWAVEFORMAT;

// ******************************************************************
// * X_DSOUTPUTLEVELS
// ******************************************************************
struct X_DSOUTPUTLEVELS
{
    DWORD dwAnalogLeftTotalPeak;    // analog peak
    DWORD dwAnalogRightTotalPeak;
    DWORD dwAnalogLeftTotalRMS;        // analog RMS
    DWORD dwAnalogRightTotalRMS;
    DWORD dwDigitalFrontLeftPeak;    // digital peak levels
    DWORD dwDigitalFrontCenterPeak;
    DWORD dwDigitalFrontRightPeak;
    DWORD dwDigitalBackLeftPeak;
    DWORD dwDigitalBackRightPeak;
    DWORD dwDigitalLowFrequencyPeak;
    DWORD dwDigitalFrontLeftRMS;    // digital RMS levels
    DWORD dwDigitalFrontCenterRMS;
    DWORD dwDigitalFrontRightRMS;
    DWORD dwDigitalBackLeftRMS;
    DWORD dwDigitalBackRightRMS;
    DWORD dwDigitalLowFrequencyRMS;
};

// ******************************************************************
// * X_DSCAPS
// ******************************************************************
struct X_DSCAPS
{                                                       
    DWORD dwFree2DBuffers;
    DWORD dwFree3DBuffers;
    DWORD dwFreeBufferSGEs;
    DWORD dwMemoryAllocated;
};

#define X_DSSPEAKER_STEREO          0x00000000
#define X_DSSPEAKER_MONO            0x00000001
#define X_DSSPEAKER_SURROUND        0x00000002
#define X_DSSPEAKER_ENABLE_AC3      0x00010000
#define X_DSSPEAKER_ENABLE_DTS      0x00020000

struct X_DS3DBUFFER {
    DWORD dwSize;
    D3DXVECTOR3 vPosition;
    D3DXVECTOR3 vVelocity;
    DWORD dwInsideConeAngle;
    DWORD  dwOutsideConeAngle;
    D3DXVECTOR3 vConeOrientation;
    LONG lConeOutsideVolume;
    FLOAT flMinDistance;
    FLOAT flMaxDistance;
    DWORD dwMode;
    FLOAT flDistanceFactor;
    FLOAT flRolloffFactor;
    FLOAT flDopplerFactor;
};

struct X_DSI3DL2LISTENER {
    LONG lRoom;
    LONG lRoomHF;
    FLOAT flRoomRolloffFactor;
    FLOAT flDecayTime;
    FLOAT flDecayHFRatio;
    LONG  lReflections;
    FLOAT flReflectionsDelay;
    LONG  lReverb;
    FLOAT flReverbDelay;
    FLOAT flDiffusion;
    FLOAT flDensity;
    FLOAT flHFReference;
};

struct X_DSI3DL2OBSTRUCTION {
    LONG            lHFLevel;
    FLOAT           flLFRatio;
};

struct X_DSI3DL2OCCLUSION {
    LONG            lHFLevel;
    FLOAT           flLFRatio;
};

struct X_DSI3DL2BUFFER {
    LONG lDirect;
    LONG lDirectHF;
    LONG lRoom;
    LONG lRoomHF;
    FLOAT flRoomRolloffFactor;
    X_DSI3DL2OBSTRUCTION Obstruction;
    X_DSI3DL2OCCLUSION Occlusion;
};

typedef struct IDirectSoundStream IDirectSoundStream;
typedef IDirectSoundStream *LPDIRECTSOUNDSTREAM;

// ******************************************************************
// * X_CDirectSound
// ******************************************************************
struct X_CDirectSound
{
    // TODO: Fill this in?
};

enum X_DSB_TOGGLE {
    X_DSB_TOGGLE_DEFAULT = 0,
    X_DSB_TOGGLE_PLAY,
    X_DSB_TOGGLE_LOOP
};

typedef struct _DSoundBuffer_Lock {
    PVOID   pLockPtr1;
    DWORD   dwLockBytes1;
    PVOID   pLockPtr2;
    DWORD   dwLockBytes2;
    DWORD   dwLockOffset;
    DWORD   dwLockFlags;
} DSoundBuffer_Lock;

// ******************************************************************
// * X_CDirectSoundBuffer
// ******************************************************************
struct X_CDirectSoundBuffer
{
    BYTE    UnknownA[0x20];     // Offset: 0x00

    union                       // Offset: 0x20
    {
        PVOID                   pMpcxBuffer;
        LPDIRECTSOUNDBUFFER8    EmuDirectSoundBuffer8;
    };

    BYTE                    UnknownB[0x0C];     // Offset: 0x24
    LPVOID                  X_BufferCache;      // Offset: 0x28
    DSBUFFERDESC            EmuBufferDesc;      // Offset: 0x2C
    /*LPVOID                  EmuLockPtr1;        // Offset: 0x30
    DWORD                   EmuLockBytes1;      // Offset: 0x34
    LPVOID                  EmuLockPtr2;        // Offset: 0x38
    DWORD                   EmuLockBytes2;      // Offset: 0x3C*/
    DWORD                   EmuPlayFlags;       // Offset: 0x40
    DWORD                   EmuFlags;           // Offset: 0x44
    LPDIRECTSOUND3DBUFFER8  EmuDirectSound3DBuffer8;
    //DWORD                   EmuLockOffset;
    //DWORD                   EmuLockFlags;
    // Play/Loop Region Section
    X_DSB_TOGGLE            EmuBufferToggle;
    DWORD                   EmuRegionLoopStartOffset;
    DWORD                   EmuRegionLoopLength;
    DWORD                   EmuRegionPlayStartOffset;
    DWORD                   EmuRegionPlayLength;
    DWORD                   X_BufferCacheSize;
    DSoundBuffer_Lock       Host_lock;
    DSoundBuffer_Lock       X_lock;
    REFERENCE_TIME          Xb_rtPauseEx;
    LONG                    Xb_Volume;
    LONG                    Xb_VolumeMixbin;
    DWORD                   Xb_dwHeadroom;
};

#define WAVE_FORMAT_XBOX_ADPCM 0x0069
//Custom flags (4 bytes support up to 31 shifts,starting from 0)
#define DSE_FLAG_PCM                    (1 << 0)
#define DSE_FLAG_XADPCM                 (1 << 1)
#define DSE_FLAG_PCM_UNKNOWN            (1 << 2)
#define DSE_FLAG_SYNCHPLAYBACK_CONTROL  (1 << 10)
#define DSE_FLAG_PAUSE                  (1 << 11)
#define DSE_FLAG_FLUSH_ASYNC            (1 << 12)
#define DSE_FLAG_ENVELOPE               (1 << 13)
#define DSE_FLAG_ENVELOPE2              (1 << 14) // NOTE: This flag is a requirement for GetStatus to return X_DSSSTATUS_ENVELOPECOMPLETE value.
#define DSE_FLAG_RECIEVEDATA            (1 << 20)
#define DSE_FLAG_DEBUG_MUTE             (1 << 30) // Cxbx-R debugging usage only
#define DSE_FLAG_BUFFER_EXTERNAL        (1 << 31)
#define DSE_FLAG_AUDIO_CODECS           (DSE_FLAG_PCM | DSE_FLAG_XADPCM | DSE_FLAG_PCM_UNKNOWN)

// ******************************************************************
// * X_CMcpxStream
// ******************************************************************
class X_CMcpxStream
{
    public:
        // construct vtable (or grab ptr to existing)
        X_CMcpxStream(class X_CDirectSoundStream *pParentStream) : pVtbl(&vtbl), pParentStream(pParentStream) {};

    private:
        // vtable (cached by each instance, via constructor)
        struct _vtbl
        {
            DWORD Unknown1;                                                 // 0x00 - ???
            DWORD Unknown2;                                                 // 0x04 - ???
            DWORD Unknown3;                                                 // 0x08 - ???
            DWORD Unknown4;                                                 // 0x0C - ???

            //
            // TODO: Function needs X_CMcpxStream "this" pointer (ecx!)
            //

            VOID (WINAPI *Dummy_0x10)(DWORD dwDummy1, DWORD dwDummy2);   // 0x10
        }
        *pVtbl;

        // global vtbl for this class
        static _vtbl vtbl;

        // debug mode guard for detecting naughty data accesses
        #ifdef _DEBUG
        DWORD DebugGuard[256];
        #endif

    public:

        class X_CDirectSoundStream *pParentStream;
};

// host_voice_packet is needed for DirectSoundStream packet handling internally.
struct host_voice_packet {
    XMEDIAPACKET xmp_data;
    PVOID   pBuffer_data;
    DWORD   rangeStart;
    bool    isWritten;
    bool    isPlayed;
};

// ******************************************************************
// * X_CDirectSoundStream
// ******************************************************************
class X_CDirectSoundStream
{
    public:
        // construct vtable (or grab ptr to existing)
        X_CDirectSoundStream() : pVtbl(&vtbl) { pMcpxStream = new X_CMcpxStream(this); };

    private:
        // vtable (cached by each instance, via constructor)
        struct _vtbl
        {
            ULONG (WINAPI *AddRef)(X_CDirectSoundStream *pThis);            // 0x00
            ULONG (WINAPI *Release)(X_CDirectSoundStream *pThis);           // 0x04
            
            HRESULT (WINAPI *GetInfo)                                       // 0x08
            (
                X_CDirectSoundStream*   pThis,
                XMEDIAINFO*             pInfo
            );

            HRESULT (WINAPI *GetStatus)                                     // 0x0C
            (
                X_CDirectSoundStream*   pThis,
                LPDWORD                 pdwStatus
            );

            HRESULT (WINAPI *Process)                                       // 0x10
            (
                X_CDirectSoundStream*   pThis,
                PXMEDIAPACKET           pInputBuffer,
                PXMEDIAPACKET           pOutputBuffer
            );

            HRESULT (WINAPI *Discontinuity)(X_CDirectSoundStream *pThis);   // 0x14

            HRESULT (WINAPI *Flush)(X_CDirectSoundStream *pThis);           // 0x18

            DWORD Unknown2;                                                 // 0x1C - ???
            DWORD Unknown3;                                                 // 0x20 - ???
            DWORD Unknown4;                                                 // 0x24 - ???
            DWORD Unknown5;                                                 // 0x28 - ???
            DWORD Unknown6;                                                 // 0x2C - ???
            DWORD Unknown7;                                                 // 0x30 - ???
            DWORD Unknown8;                                                 // 0x34 - ???
            DWORD Unknown9;                                                 // 0x38 - ???
        }
        *pVtbl;

        // global vtbl for this class
        static _vtbl vtbl;

        DWORD Spacer[8];
        PVOID pMcpxStream;

        // debug mode guard for detecting naughty data accesses
        #ifdef _DEBUG
        DWORD DebugGuard[256];
        #endif

    public:
        // cached data
        LPDIRECTSOUNDBUFFER8                    EmuDirectSoundBuffer8;
        LPDIRECTSOUND3DBUFFER8                  EmuDirectSound3DBuffer8;
        PVOID                                   X_BufferCache; // Not really needed...
        DSBUFFERDESC                            EmuBufferDesc;
        PVOID                                   EmuLockPtr1;
        DWORD                                   EmuLockBytes1;
        PVOID                                   EmuLockPtr2;
        DWORD                                   EmuLockBytes2;
        DWORD                                   EmuPlayFlags;
        DWORD                                   EmuFlags;
        DWORD                                   X_BufferCacheSize; // Not really needed...
        DWORD                                   X_MaxAttachedPackets;
        std::vector<struct host_voice_packet>   Host_BufferPacketArray;
        DWORD                                   Host_dwWriteOffsetNext;
        DWORD                                   Host_dwTriggerRange;
        bool                                    Host_isProcessing;
        LPFNXMOCALLBACK                         Xb_lpfnCallback;
        LPVOID                                  Xb_lpvContext;
        REFERENCE_TIME                          Xb_rtFlushEx;
        REFERENCE_TIME                          Xb_rtPauseEx;
        LONG                                    Xb_Volume;
        LONG                                    Xb_VolumeMixbin;
        DWORD                                   Xb_dwHeadroom;
};

// ******************************************************************
// * X_XFileMediaObject
// ******************************************************************
class X_XFileMediaObject
{
    public:
    X_XFileMediaObject() : pVtbl(&vtbl) { EmuRefCount = 1; }

    private:
        // vtable (cached by each instance, via constructor)
        struct _vtbl
        {
            ULONG (WINAPI *AddRef)(X_XFileMediaObject *pThis);            // 0x00
            ULONG (WINAPI *Release)(X_XFileMediaObject *pThis);           // 0x04

            HRESULT (WINAPI *GetInfo)                                        // 0x08
            (
                X_XFileMediaObject*     pThis,
                XMEDIAINFO*             pInfo
            );
                                                                                                              
            HRESULT (WINAPI *GetStatus)                                     // 0x0C
            (
                X_XFileMediaObject*     pThis,
                LPDWORD                 pdwStatus
            );
 
            HRESULT (WINAPI *Process)                                       // 0x10
            (
                X_XFileMediaObject*     pThis,
                PXMEDIAPACKET           pInputBuffer,
                PXMEDIAPACKET           pOutputBuffer
            );
           
            HRESULT (WINAPI *Discontinuity)(X_XFileMediaObject *pThis);        // 0x14
                                                                           
            DWORD Unknown7;
/*
            HRESULT (WINAPI *Flush)(X_XFileMediaObject *pThis);                // 0x18
*/
            HRESULT (WINAPI *Seek)                                            // 0x1C
            (
                X_XFileMediaObject*     pThis,
                LONG                    lOffset, 
                DWORD                   dwOrigin, 
                LPDWORD                 pdwAbsolute
            );
/*
            HRESULT (WINAPI *GetLength)                                        // 0x20
            (
                X_XFileMediaObject       *pThis,
                LPDWORD                    pdwLength
            );*/

            DWORD Unknown9;

            void (WINAPI *DoWork)(X_XFileMediaObject *pThis);                // 0x24
        }
        *pVtbl;

        // global vtbl for this class
        static _vtbl vtbl;

        // debug mode guard for detecting naughty data accesses
        #ifdef _DEBUG
        DWORD DebugGuard[256];
        #endif

    public:
        // TODO: More?
        LPVOID                EmuBuffer;
        HANDLE                EmuHandle;
        UINT                EmuRefCount;
};
_XTL_END

#endif
