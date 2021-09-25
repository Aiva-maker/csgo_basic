#pragma once

#define NOMINMAX
#include <Windows.h>

#include "Misc/Enums.hpp"
#include "Misc/vfunc.hpp"

#include "Math/VMatrix.hpp"
#include "Math/QAngle.hpp"
#include "Math/Vector.hpp"
#include "Misc/Studio.hpp"

#include "Interfaces/IAppSystem.hpp"
#include "Interfaces/IBaseClientDll.hpp"
#include "Interfaces/IClientEntity.hpp"
#include "Interfaces/IClientEntityList.hpp"
#include "Interfaces/IClientMode.hpp"
#include "Interfaces/IConVar.hpp"
#include "Interfaces/ICvar.hpp"
#include "Interfaces/IEngineTrace.hpp"
#include "Interfaces/IVEngineClient.hpp"
#include "Interfaces/IVDebugOverlay.hpp"
#include "Interfaces/ISurface.hpp"
#include "Interfaces/CInput.hpp"
#include "Interfaces/IVModelInfoClient.hpp"
#include "Interfaces/IVModelRender.hpp"
#include "Interfaces/IRenderView.hpp"
#include "Interfaces/IGameEventmanager.hpp"
#include "Interfaces/IMaterialSystem.hpp"
#include "Interfaces/IMoveHelper.hpp"
#include "Interfaces/IMDLCache.hpp"
#include "Interfaces/IPrediction.hpp"
#include "Interfaces/IPanel.hpp"
#include "Interfaces/IEngineSound.hpp"
#include "Interfaces/IViewRender.hpp"
#include "Interfaces/CClientState.hpp"
#include "Interfaces/IPhysics.hpp"
#include "Interfaces/IInputSystem.hpp"
#include "interfaces/IRefCounted.hpp"

#include "Misc/Convar.hpp"
#include "Misc/CUserCmd.hpp"
#include "Misc/glow_outline_effect.hpp"
#include "Misc/datamap.hpp"

#include "netvars.hpp"

struct IDirect3DDevice9;

namespace Interfaces
{
    void Initialize();
    void Dump();
}

IVEngineClient*       g_EngineClient   = nullptr;
IBaseClientDLL*       g_CHLClient      = nullptr;
IClientEntityList*    g_EntityList     = nullptr;
CGlobalVarsBase*      g_GlobalVars     = nullptr;
IEngineTrace*         g_EngineTrace    = nullptr;
ICvar*                g_CVar           = nullptr;
IPanel*               g_VGuiPanel      = nullptr;
IClientMode*          g_ClientMode     = nullptr;
IVDebugOverlay*       g_DebugOverlay   = nullptr;
ISurface*             g_VGuiSurface    = nullptr;
CInput*               g_Input          = nullptr;
IVModelInfoClient*    g_MdlInfo        = nullptr;
IVModelRender*        g_MdlRender      = nullptr;
IVRenderView*         g_RenderView     = nullptr;
IMaterialSystem*      g_MatSystem      = nullptr;
IGameEventManager2*   g_GameEvents     = nullptr;
IMoveHelper*          g_MoveHelper     = nullptr;
IMDLCache*            g_MdlCache       = nullptr;
IPrediction*          g_Prediction     = nullptr;
CGameMovement*        g_GameMovement   = nullptr;
IEngineSound*         g_EngineSound    = nullptr;
CGlowObjectManager*   g_GlowObjManager = nullptr;
IViewRender*          g_ViewRender     = nullptr;
IDirect3DDevice9*     g_D3DDevice9     = nullptr;
CClientState*         g_ClientState    = nullptr;
IPhysicsSurfaceProps* g_PhysSurface    = nullptr;
IInputSystem*         g_InputSystem    = nullptr;
IWeaponSystem*        g_WeaponSystem   = nullptr;

template<typename... Args>
void ConMsg(const char* pMsg, Args... args)
{
    static auto import = (void(*)(const char*, ...))GetProcAddress(GetModuleHandleW(L"tier0.dll"), "?ConMsg@@YAXPBDZZ");
    return import(pMsg, args...);
}
template<typename... Args>
void ConColorMsg(const Color& clr, const char* pMsg, Args... args)
{
    static auto import = (void(*)(const Color&, const char*, ...))GetProcAddress(GetModuleHandleW(L"tier0.dll"), "?ConColorMsg@@YAXABVColor@@PBDZZ");
    return import(clr, pMsg, args...);
}

#include "Misc/EHandle.hpp"

class C_LocalPlayer
{
    friend bool operator==(const C_LocalPlayer& lhs, void* rhs);
public:
    C_LocalPlayer() : m_local(nullptr) {}

    operator bool() const { return *m_local != nullptr; }
    operator C_BasePlayer*() const { return *m_local; }

    C_BasePlayer* operator->() { return *m_local; }

private:
    C_BasePlayer** m_local;
};

C_LocalPlayer g_LocalPlayer;

