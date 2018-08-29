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
// *   src->core->XTL->DSound->DSound.hpp
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
#ifndef DSOUND_HPP
#define DSOUND_HPP
#pragma once

#include "core/XTL/SymbolScan.hpp"
#include "DSoundX.hpp"
#include "DirectSound/DirectSound.hpp"

namespace XTL
{
	namespace HLE
	{
		class DSound {

		public:
			static void Init();
			static bool GetPatchSymbols();

			static bool Patch(const char* symbol_str, xbaddr func_addr);
		};

		const struct DSound_list_func {
#pragma region Misc class
			HRESULT(WINAPI* HLE_PATCH_FUNC(XAudioCreateAdpcmFormat))(WORD, DWORD, LPXBOXADPCMWAVEFORMAT);
			HRESULT(WINAPI* HLE_PATCH_FUNC(XAudioDownloadEffectsImage))(LPCSTR, LPVOID, DWORD, LPVOID*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(XAudioSetEffectData))(DWORD, void*, void*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(XWaveFileCreateMediaObjectEx))(LPCSTR, HANDLE, void**);
			HRESULT(WINAPI* HLE_PATCH_FUNC(XWaveFileCreateMediaObject))(LPCSTR, LPCWAVEFORMATEX*, void**);
			HRESULT(WINAPI* HLE_PATCH_FUNC(XFileCreateMediaObjectEx))(HANDLE, void**);
			HRESULT(WINAPI* HLE_PATCH_FUNC(XFileCreateMediaObject))(DWORD, DWORD, DWORD, DWORD, void**);
			HRESULT(WINAPI* HLE_PATCH_FUNC(XFileCreateMediaObjectAsync))(HANDLE, DWORD, void**);
#pragma endregion

#pragma region XFileMediaObject class
			ULONG(WINAPI* HLE_PATCH_FUNC(XFileMediaObject_AddRef))(X_XFileMediaObject*);
			ULONG(WINAPI* HLE_PATCH_FUNC(XFileMediaObject_Release))(X_XFileMediaObject*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(XFileMediaObject_Discontinuity))(X_XFileMediaObject*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(XFileMediaObject_Seek))(X_XFileMediaObject*, LONG, DWORD, LPDWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(XFileMediaObject_GetStatus))(X_XFileMediaObject*, LPDWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(XFileMediaObject_GetInfo))(X_XFileMediaObject*, XMEDIAINFO);
			HRESULT(WINAPI* HLE_PATCH_FUNC(XFileMediaObject_Process))(X_XFileMediaObject*, LPXMEDIAPACKET, LPXMEDIAPACKET);
			VOID(WINAPI* HLE_PATCH_FUNC(XFileMediaObject_DoWork))(X_XFileMediaObject*);
#pragma endregion

#pragma region DirectSound class
			DWORD(WINAPI* HLE_PATCH_FUNC(DirectSoundGetSampleTime))(VOID);
			HRESULT(WINAPI* HLE_PATCH_FUNC(DirectSoundUseFullHRTF))(VOID);
			HRESULT(WINAPI* HLE_PATCH_FUNC(DirectSoundUseLightHRTF))(VOID);
			HRESULT(WINAPI* HLE_PATCH_FUNC(DirectSoundUseFullHRTF4Channel))(VOID);
			HRESULT(WINAPI* HLE_PATCH_FUNC(DirectSoundUseLightHRTF4Channel))(VOID);
			HRESULT(WINAPI* HLE_PATCH_FUNC(DirectSoundCreate))(LPVOID, LPDIRECTSOUND8, LPUNKNOWN);
			HRESULT(WINAPI* HLE_PATCH_FUNC(DirectSoundCreateBuffer))(X_DSBUFFERDESC*, X_CDirectSoundBuffer**);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_CreateSoundBuffer))(LPDIRECTSOUND8, X_DSBUFFERDESC*, X_CDirectSoundBuffer**, LPUNKNOWN);
			HRESULT(WINAPI* HLE_PATCH_FUNC(DirectSoundCreateStream))(LPDIRECTSOUND8, X_CDirectSoundStream**);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_CreateSoundStream))(X_DSSTREAMDESC*, X_CDirectSoundStream**, PVOID);
			ULONG(WINAPI* HLE_PATCH_FUNC(IDirectSound_AddRef))(LPDIRECTSOUND8);
			ULONG(WINAPI* HLE_PATCH_FUNC(IDirectSound_Release))(LPDIRECTSOUND8);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSound_GetSpeakerConfig))(X_CDirectSound*, PDWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_GetSpeakerConfig))(LPDIRECTSOUND8, LPDWORD*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSound_SynchPlayback))(LPDIRECTSOUND8);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_SynchPlayback))(LPDIRECTSOUND8);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_DownloadEffectsImage))(LPDIRECTSOUND8, LPCVOID, DWORD, PVOID, PVOID);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_SetOrientation))(LPDIRECTSOUND8, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_SetDistanceFactor))(LPDIRECTSOUND8, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_SetRolloffFactor))(LPDIRECTSOUND8, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_SetDopplerFactor))(LPDIRECTSOUND8, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_SetI3DL2Listener))(LPDIRECTSOUND8, X_DSI3DL2LISTENER, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_SetMixBinHeadroom))(LPDIRECTSOUND8, DWORD, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_SetPosition))(LPDIRECTSOUND8, FLOAT, FLOAT, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_SetVelocity))(LPDIRECTSOUND8, FLOAT, FLOAT, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_SetAllParameters))(LPDIRECTSOUND8, LPCDS3DLISTENER, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSound_CommitDeferredSettings))(LPDIRECTSOUND8);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_CommitDeferredSettings))(LPDIRECTSOUND8);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_EnableHeadphones))(LPDIRECTSOUND8, BOOL);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_GetOutputLevels))(LPDIRECTSOUND8, X_DSOUTPUTLEVELS*, BOOL);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_GetCaps))(LPDIRECTSOUND8, X_DSCAPS*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_GetEffectData))(LPDIRECTSOUND8, DWORD, DWORD, LPVOID, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_SetEffectData))(LPDIRECTSOUND8, DWORD, DWORD, LPCVOID, DWORD, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSound_CommitEffectData))(LPDIRECTSOUND8);
			VOID(WINAPI* HLE_PATCH_FUNC(DirectSoundDoWork))(VOID);
#pragma endregion

#pragma region DirectSoundBuffer class
			ULONG(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_AddRef))(X_CDirectSoundBuffer*);
			ULONG(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_Release))(X_CDirectSoundBuffer*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetMixBins))(X_CDirectSoundBuffer, PVOID);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetMixBinVolumes_12))(X_CDirectSoundBuffer*, DWORD, const LONG*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetMixBinVolumes_8))(X_CDirectSoundBuffer*, X_LPDSMIXBINS);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetBufferData))(X_CDirectSoundBuffer*, LPVOID, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetPlayRegion))(X_CDirectSoundBuffer*, DWORD, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_Lock))(X_CDirectSoundBuffer*, DWORD, DWORD, LPVOID*, LPDWORD, LPVOID*, LPDWORD, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_Unlock))(X_CDirectSoundBuffer*, LPVOID, DWORD, LPVOID, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetHeadroom))(X_CDirectSoundBuffer*, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetLoopRegion))(X_CDirectSoundBuffer*, DWORD, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetPitch))(X_CDirectSoundBuffer*, LONG);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_GetStatus))(X_CDirectSoundBuffer*, LPDWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetVolume))(X_CDirectSoundBuffer*, LONG);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetCurrentPosition))(X_CDirectSoundBuffer*, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_GetCurrentPosition))(X_CDirectSoundBuffer*, PDWORD, PDWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_Stop))(X_CDirectSoundBuffer*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_StopEx))(X_CDirectSoundBuffer*, REFERENCE_TIME, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_Play))(X_CDirectSoundBuffer*, DWORD, DWORD, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_PlayEx))(X_CDirectSoundBuffer*, REFERENCE_TIME, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetFrequency))(X_CDirectSoundBuffer*, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetMaxDistance))(X_CDirectSoundBuffer*, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetRolloffFactor))(X_CDirectSoundBuffer*, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetDistanceFactor))(X_CDirectSoundBuffer*, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetConeAngles))(X_CDirectSoundBuffer*, DWORD, DWORD, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetConeOrientation))(X_CDirectSoundBuffer*, FLOAT, FLOAT, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetConeOutsideVolume))(X_CDirectSoundBuffer*, LONG, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetPosition))(X_CDirectSoundBuffer*, FLOAT, FLOAT, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetVelocity))(X_CDirectSoundBuffer*, FLOAT, FLOAT, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetDopplerFactor))(X_CDirectSoundBuffer*, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetI3DL2Source))(X_CDirectSoundBuffer*, X_DSI3DL2BUFFER*, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetMode))(X_CDirectSoundBuffer*, DWORD, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetFormat))(X_CDirectSoundBuffer*, LPCWAVEFORMATEX);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetLFO))(X_CDirectSoundBuffer*, LPCDSLFODESC);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetRolloffCurve))(X_CDirectSoundBuffer*, const FLOAT*, DWORD, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_PauseEx))(X_CDirectSoundBuffer*, REFERENCE_TIME, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_Pause))(X_CDirectSoundBuffer*, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetFilter))(X_CDirectSoundBuffer*, X_DSFILTERDESC*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetAllParameters))(X_CDirectSoundBuffer*, X_DS3DBUFFER*, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetOutputBuffer))(X_CDirectSoundBuffer*, X_CDirectSoundBuffer*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetEG))(X_CDirectSoundBuffer*, LPVOID);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_SetNotificationPositions))(X_CDirectSoundBuffer*, DWORD, LPCDSBPOSITIONNOTIFY);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_Use3DVoiceData))(X_CDirectSoundBuffer*, LPUNKNOWN);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundBuffer_GetVoiceProperties))(X_CDirectSoundBuffer*, void*);
#pragma endregion

#pragma region DirectSoundStream class
			ULONG(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_AddRef))(void*);
			ULONG(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_Release))(X_CDirectSoundStream*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CMcpxStream_Dummy_0x10))(DWORD, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetRolloffFactor))(X_CDirectSoundStream*, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_GetInfo))(X_CDirectSoundStream*, LPXMEDIAINFO);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_GetStatus))(X_CDirectSoundStream*, LPDWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_Process))(X_CDirectSoundStream*, PXMEDIAPACKET, PXMEDIAPACKET);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_Discontinuity))(X_CDirectSoundStream*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_Flush))(X_CDirectSoundStream*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_Pause))(X_CDirectSoundStream*, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetHeadroom))(X_CDirectSoundStream*, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundStream_SetHeadroom))(X_CDirectSoundStream*, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetAllParameters))(X_CDirectSoundStream*, X_DS3DBUFFER*, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetConeAngles))(X_CDirectSoundStream*, DWORD, DWORD, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetConeOutsideVolume))(X_CDirectSoundStream*, LONG, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetMaxDistance))(X_CDirectSoundStream*, D3DVALUE, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetMinDistance))(X_CDirectSoundStream*, D3DVALUE, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetVelocity))(X_CDirectSoundStream*, D3DVALUE, D3DVALUE, D3DVALUE, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetConeOrientation))(X_CDirectSoundStream*, D3DVALUE, D3DVALUE, D3DVALUE, DWORD );
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetPosition))(X_CDirectSoundStream*, D3DVALUE, D3DVALUE, D3DVALUE, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetFrequency))(X_CDirectSoundStream*, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundStream_SetFrequency))(X_CDirectSoundStream*, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundStream_SetPitch))(X_CDirectSoundStream*, LONG);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetI3DL2Source))(X_CDirectSoundStream*, X_DSI3DL2BUFFER*, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetMixBins))(X_CDirectSoundStream*, PVOID);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundStream_SetMixBins))(X_CDirectSoundStream*, PVOID);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetLFO))(X_CDirectSoundStream*, LPCDSLFODESC);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundStream_SetLFO))(X_CDirectSoundStream*, LPCDSLFODESC);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetVolume))(X_CDirectSoundStream*, LONG);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundStream_SetVolume))(X_CDirectSoundStream*, LONG);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetEG))(X_CDirectSoundStream*, LPVOID);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundStream_SetEG))(X_CDirectSoundStream*, LPVOID);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_FlushEx))(X_CDirectSoundStream*, REFERENCE_TIME, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetMode))(X_CDirectSoundStream*, DWORD, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetFilter))(X_CDirectSoundStream*, X_DSFILTERDESC*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(IDirectSoundStream_SetFilter))(X_CDirectSoundStream*, X_DSFILTERDESC*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetPitch))(X_CDirectSoundStream*, LONG);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetMixBinVolumes_12))(X_CDirectSoundStream*, DWORD, const LONG*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetMixBinVolumes_8))(X_CDirectSoundStream*, X_LPDSMIXBINS);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetFormat))(X_CDirectSoundStream*, LPCWAVEFORMATEX);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetOutputBuffer))(X_CDirectSoundStream*, X_CDirectSoundStream*);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetRolloffCurve))(X_CDirectSoundStream*, const FLOAT*, DWORD, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_PauseEx))(X_CDirectSoundStream*, REFERENCE_TIME, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetDistanceFactor))(X_CDirectSoundStream*, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_SetDopplerFactor))(X_CDirectSoundStream*, FLOAT, DWORD);
			HRESULT(WINAPI* HLE_PATCH_FUNC(CDirectSoundStream_GetVoiceProperties))(X_CDirectSoundStream*, void*);
#pragma endregion
		};
		static const std::string DSound_list_patch[] = {
#pragma region Misc class
			STRINGIZE(XAudioCreateAdpcmFormat)
			,STRINGIZE(XAudioDownloadEffectsImage)
			,STRINGIZE(XAudioSetEffectData)
			,STRINGIZE(XWaveFileCreateMediaObjectEx)
			,STRINGIZE(XWaveFileCreateMediaObject)
			,STRINGIZE(XFileCreateMediaObjectEx)
			,STRINGIZE(XFileCreateMediaObject)
			,STRINGIZE(XFileCreateMediaObjectAsync)
#pragma endregion

#pragma region XFileMediaObject class
			,STRINGIZE(XFileMediaObject_AddRef)
			,STRINGIZE(XFileMediaObject_Release)
			,STRINGIZE(XFileMediaObject_Discontinuity)
			,STRINGIZE(XFileMediaObject_Seek)
			,STRINGIZE(XFileMediaObject_GetStatus)
			,STRINGIZE(XFileMediaObject_GetInfo)
			,STRINGIZE(XFileMediaObject_Process)
			,STRINGIZE(XFileMediaObject_DoWork)
#pragma endregion

#pragma region DirectSound class
			,STRINGIZE(DirectSoundGetSampleTime)
			,STRINGIZE(DirectSoundUseFullHRTF)
			,STRINGIZE(DirectSoundUseLightHRTF)
			,STRINGIZE(DirectSoundUseFullHRTF4Channel)
			,STRINGIZE(DirectSoundUseLightHRTF4Channel)
			,STRINGIZE(DirectSoundCreate)
			,STRINGIZE(DirectSoundCreateBuffer)
			,STRINGIZE(IDirectSound_CreateSoundBuffer)
			,STRINGIZE(DirectSoundCreateStream)
			,STRINGIZE(IDirectSound_CreateSoundStream)
			,STRINGIZE(IDirectSound_AddRef)
			,STRINGIZE(IDirectSound_Release)
			,STRINGIZE(CDirectSound_GetSpeakerConfig)
			,STRINGIZE(IDirectSound_GetSpeakerConfig)
			,STRINGIZE(CDirectSound_SynchPlayback)
			,STRINGIZE(IDirectSound_SynchPlayback)
			,STRINGIZE(IDirectSound_DownloadEffectsImage)
			,STRINGIZE(IDirectSound_SetOrientation)
			,STRINGIZE(IDirectSound_SetDistanceFactor)
			,STRINGIZE(IDirectSound_SetRolloffFactor)
			,STRINGIZE(IDirectSound_SetDopplerFactor)
			,STRINGIZE(IDirectSound_SetI3DL2Listener)
			,STRINGIZE(IDirectSound_SetMixBinHeadroom)
			,STRINGIZE(IDirectSound_SetPosition)
			,STRINGIZE(IDirectSound_SetVelocity)
			,STRINGIZE(IDirectSound_SetAllParameters)
			,STRINGIZE(CDirectSound_CommitDeferredSettings)
			,STRINGIZE(IDirectSound_CommitDeferredSettings)
			,STRINGIZE(IDirectSound_EnableHeadphones)
			,STRINGIZE(IDirectSound_GetOutputLevels)
			,STRINGIZE(IDirectSound_GetCaps)
			,STRINGIZE(IDirectSound_GetEffectData)
			,STRINGIZE(IDirectSound_SetEffectData)
			,STRINGIZE(IDirectSound_CommitEffectData)
			,STRINGIZE(DirectSoundDoWork)
#pragma endregion

#pragma region DirectSoundBuffer class
			,STRINGIZE(IDirectSoundBuffer_AddRef)
			,STRINGIZE(IDirectSoundBuffer_Release)
			,STRINGIZE(IDirectSoundBuffer_SetMixBins)
			,STRINGIZE(IDirectSoundBuffer_SetMixBinVolumes_12)
			,STRINGIZE(IDirectSoundBuffer_SetMixBinVolumes_8)
			,STRINGIZE(IDirectSoundBuffer_SetBufferData)
			,STRINGIZE(IDirectSoundBuffer_SetPlayRegion)
			,STRINGIZE(IDirectSoundBuffer_Lock)
			,STRINGIZE(IDirectSoundBuffer_Unlock)
			,STRINGIZE(IDirectSoundBuffer_SetHeadroom)
			,STRINGIZE(IDirectSoundBuffer_SetLoopRegion)
			,STRINGIZE(IDirectSoundBuffer_SetPitch)
			,STRINGIZE(IDirectSoundBuffer_GetStatus)
			,STRINGIZE(IDirectSoundBuffer_SetVolume)
			,STRINGIZE(IDirectSoundBuffer_SetCurrentPosition)
			,STRINGIZE(IDirectSoundBuffer_GetCurrentPosition)
			,STRINGIZE(IDirectSoundBuffer_Stop)
			,STRINGIZE(IDirectSoundBuffer_StopEx)
			,STRINGIZE(IDirectSoundBuffer_Play)
			,STRINGIZE(IDirectSoundBuffer_PlayEx)
			,STRINGIZE(IDirectSoundBuffer_SetFrequency)
			,STRINGIZE(IDirectSoundBuffer_SetMaxDistance)
			,STRINGIZE(IDirectSoundBuffer_SetRolloffFactor)
			,STRINGIZE(IDirectSoundBuffer_SetDistanceFactor)
			,STRINGIZE(IDirectSoundBuffer_SetConeAngles)
			,STRINGIZE(IDirectSoundBuffer_SetConeOrientation)
			,STRINGIZE(IDirectSoundBuffer_SetConeOutsideVolume)
			,STRINGIZE(IDirectSoundBuffer_SetPosition)
			,STRINGIZE(IDirectSoundBuffer_SetVelocity)
			,STRINGIZE(IDirectSoundBuffer_SetDopplerFactor)
			,STRINGIZE(IDirectSoundBuffer_SetI3DL2Source)
			,STRINGIZE(IDirectSoundBuffer_SetMode)
			,STRINGIZE(IDirectSoundBuffer_SetFormat)
			,STRINGIZE(IDirectSoundBuffer_SetLFO)
			,STRINGIZE(IDirectSoundBuffer_SetRolloffCurve)
			,STRINGIZE(IDirectSoundBuffer_PauseEx)
			,STRINGIZE(IDirectSoundBuffer_Pause)
			,STRINGIZE(IDirectSoundBuffer_SetFilter)
			,STRINGIZE(IDirectSoundBuffer_SetAllParameters)
			,STRINGIZE(IDirectSoundBuffer_SetOutputBuffer)
			,STRINGIZE(IDirectSoundBuffer_SetEG)
			,STRINGIZE(IDirectSoundBuffer_SetNotificationPositions)
			,STRINGIZE(IDirectSoundBuffer_Use3DVoiceData)
			,STRINGIZE(IDirectSoundBuffer_GetVoiceProperties)
#pragma endregion

#pragma region DirectSoundStream class
			,STRINGIZE(CDirectSoundStream_AddRef)
			,STRINGIZE(CDirectSoundStream_Release)
			,STRINGIZE(CMcpxStream_Dummy_0x10)
			,STRINGIZE(CDirectSoundStream_SetRolloffFactor)
			,STRINGIZE(CDirectSoundStream_GetInfo)
			,STRINGIZE(CDirectSoundStream_GetStatus)
			,STRINGIZE(CDirectSoundStream_Process)
			,STRINGIZE(CDirectSoundStream_Discontinuity)
			,STRINGIZE(CDirectSoundStream_Flush)
			,STRINGIZE(CDirectSoundStream_Pause)
			,STRINGIZE(CDirectSoundStream_SetHeadroom)
			,STRINGIZE(IDirectSoundStream_SetHeadroom)
			,STRINGIZE(CDirectSoundStream_SetAllParameters)
			,STRINGIZE(CDirectSoundStream_SetConeAngles)
			,STRINGIZE(CDirectSoundStream_SetConeOutsideVolume)
			,STRINGIZE(CDirectSoundStream_SetMaxDistance)
			,STRINGIZE(CDirectSoundStream_SetMinDistance)
			,STRINGIZE(CDirectSoundStream_SetVelocity)
			,STRINGIZE(CDirectSoundStream_SetConeOrientation)
			,STRINGIZE(CDirectSoundStream_SetPosition)
			,STRINGIZE(CDirectSoundStream_SetFrequency)
			,STRINGIZE(IDirectSoundStream_SetFrequency)
			,STRINGIZE(IDirectSoundStream_SetPitch)
			,STRINGIZE(CDirectSoundStream_SetI3DL2Source)
			,STRINGIZE(CDirectSoundStream_SetMixBins)
			,STRINGIZE(IDirectSoundStream_SetMixBins)
			,STRINGIZE(CDirectSoundStream_SetLFO)
			,STRINGIZE(IDirectSoundStream_SetLFO)
			,STRINGIZE(CDirectSoundStream_SetVolume)
			,STRINGIZE(IDirectSoundStream_SetVolume)
			,STRINGIZE(CDirectSoundStream_SetEG)
			,STRINGIZE(IDirectSoundStream_SetEG)
			,STRINGIZE(CDirectSoundStream_FlushEx)
			,STRINGIZE(CDirectSoundStream_SetMode)
			,STRINGIZE(CDirectSoundStream_SetFilter)
			,STRINGIZE(IDirectSoundStream_SetFilter)
			,STRINGIZE(CDirectSoundStream_SetPitch)
			,STRINGIZE(CDirectSoundStream_SetMixBinVolumes_12)
			,STRINGIZE(CDirectSoundStream_SetMixBinVolumes_8)
			,STRINGIZE(CDirectSoundStream_SetFormat)
			,STRINGIZE(CDirectSoundStream_SetOutputBuffer)
			,STRINGIZE(CDirectSoundStream_SetRolloffCurve)
			,STRINGIZE(CDirectSoundStream_PauseEx)
			,STRINGIZE(CDirectSoundStream_SetDistanceFactor)
			,STRINGIZE(CDirectSoundStream_SetDopplerFactor)
			,STRINGIZE(CDirectSoundStream_GetVoiceProperties)
#pragma endregion
		};
		static_assert(sizeof(DSound_list_func)/sizeof(PVOID) == sizeof(DSound_list_patch)/sizeof(std::string), "");
	}
}

#endif
