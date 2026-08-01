// =====================================================================
//  SH3 Graphics Saver  ->  SH3GraphicsSaver.asi
//
//  Purpose
//  -------
//  Silent Hill 3 (PC) stores two graphics options in savedata\disp.ini:
//
//      shadow           -> "Real-Time Shadow"    (1 = ON,  0 = OFF)
//      lensflare_ztest  -> "Lens Flare Quality"  (1 = Detail, 0 = Fast)
//
//  On this port those two can get reset on launch. This plugin is loaded
//  by the Ultimate ASI Loader (the game's dinput8.dll) at startup and,
//  BEFORE the game reads disp.ini, forces those two keys to the values
//  you chose in "SH3GraphicsSaver.ini" (sitting next to sh3.exe).
//
//  It does NOT hook the game or patch memory -- it only rewrites two
//  lines in a text file, so it is safe and version-independent.
//
//  Build: compile as a 32-bit (Win32/x86) DLL, output renamed to
//  "SH3GraphicsSaver.asi", placed next to sh3.exe. See build_asi.bat.
// =====================================================================

#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

// Get the folder that this .asi lives in (== the game folder).
static std::string GetModuleDir(HMODULE hModule)
{
    char path[MAX_PATH] = {0};
    GetModuleFileNameA(hModule, path, MAX_PATH);
    std::string p(path);
    size_t slash = p.find_last_of("\\/");
    return (slash == std::string::npos) ? std::string(".") : p.substr(0, slash);
}

// Read an integer key from our own .ini (default if missing/invalid).
static int ReadIniInt(const std::string& iniPath, const char* key, int def)
{
    // GetPrivateProfileInt handles [Graphics] section lookups for us.
    return (int)GetPrivateProfileIntA("Graphics", key, def, iniPath.c_str());
}

// Rewrite "key=value" in disp.ini, preserving every other line. If the
// key is missing it is appended.
static void SetDispKey(std::vector<std::string>& lines,
                       const std::string& key, int value)
{
    std::string prefix = key + "=";
    std::string newLine = key + "=" + std::to_string(value);
    for (auto& line : lines)
    {
        if (line.compare(0, prefix.size(), prefix) == 0)
        {
            line = newLine;
            return;
        }
    }
    lines.push_back(newLine);
}

static void ApplySettings(HMODULE hModule)
{
    std::string dir     = GetModuleDir(hModule);
    std::string iniPath = dir + "\\SH3GraphicsSaver.ini";
    std::string disp    = dir + "\\savedata\\disp.ini";

    // Desired values from our config (default to max quality = 1).
    int shadow    = ReadIniInt(iniPath, "Shadow", 1);
    int lensflare = ReadIniInt(iniPath, "LensFlare", 1);

    // Read disp.ini into memory (line by line).
    std::vector<std::string> lines;
    {
        std::ifstream in(disp.c_str());
        if (in.good())
        {
            std::string line;
            while (std::getline(in, line))
            {
                if (!line.empty() && line.back() == '\r') line.pop_back();
                lines.push_back(line);
            }
        }
    }

    // If disp.ini didn't exist / was empty, nothing else to preserve --
    // the game will regenerate the rest, we just seed our two keys.
    SetDispKey(lines, "shadow", shadow);
    SetDispKey(lines, "lensflare_ztest", lensflare);

    // Write it back (CRLF, matching the game's format).
    std::ofstream out(disp.c_str(), std::ios::binary | std::ios::trunc);
    if (out.good())
    {
        for (const auto& line : lines)
            out << line << "\r\n";
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        // Runs while the ASI loader is initializing, which is before the
        // game opens disp.ini -- so our values are in place in time.
        ApplySettings(hModule);
    }
    return TRUE;
}
