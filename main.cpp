//
// Created by dasci on 5/25/26.
//

#include <windows.h>

#include "libhat/Scanner.hpp"
#include "libhat/Signature.hpp"
#include "safetyhook/easy.hpp"

safetyhook::InlineHook g_IsTrialHook{};
hat::fixed_signature g_IsTrialSig = hat::compile_signature<
    "56 48 83 EC ? 48 89 ? 48 8B ? ? ? ? ? 48 31 ? 48 89 ? ? ? 48 83 79 68">();

// char __fastcall OfferRepository::isTrial(OfferRepository* this)
bool hk_OfferRepository_isTrial(void*) {
    return false;
}

BOOL WINAPI DllMain(HMODULE /* module */, DWORD reason, LPVOID /* reserved */) {
    if (reason == DLL_PROCESS_ATTACH) {
        const hat::scan_result result = hat::find_pattern(g_IsTrialSig, ".text");
        if (!result.has_result()) {
            return TRUE;
        }

        g_IsTrialHook = safetyhook::create_inline(result.get(), hk_OfferRepository_isTrial);
    } else if (reason == DLL_PROCESS_DETACH) {
        g_IsTrialHook = {};
    }
    return TRUE;
}