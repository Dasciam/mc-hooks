//
// Created by dasci on 5/25/26.
//

#include <windows.h>

#include "libhat/Scanner.hpp"
#include "libhat/Signature.hpp"
#include "safetyhook/easy.hpp"

safetyhook::InlineHook g_IsTrialHook{};
hat::fixed_signature g_IsTrialSig = hat::compile_signature<
    "E8 ? ? ? ? 88 86 ? ? ? ? 48 8B 8E ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 8B 41">();

// __int64 __fastcall MinecraftScreenModel::isTrial(MinecraftScreenModel *this)
bool hk_MinecraftScreenModel_isTrial(void *) {
    return false;
}

BOOL WINAPI DllMain(HMODULE /* module */, DWORD reason, LPVOID /* reserved */) {
    if (reason == DLL_PROCESS_ATTACH) {
        const hat::scan_result result = hat::find_pattern(g_IsTrialSig, ".text");
        if (!result.has_result()) {
            return TRUE;
        }
        const auto addr = result.rel(1);

        g_IsTrialHook = safetyhook::create_inline(addr, hk_MinecraftScreenModel_isTrial);
    } else if (reason == DLL_PROCESS_DETACH) {
        g_IsTrialHook = {};
    }
    return TRUE;
}
