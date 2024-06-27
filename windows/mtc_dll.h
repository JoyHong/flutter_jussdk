#ifndef MTC_DLL_H
#define MTC_DLL_H

extern "C" __declspec(dllimport) int Mtc_CliInit(const char *pcProfDir, void *pCtx);
extern "C" __declspec(dllimport) int Mtc_CliDrive(void *zEvntId);

#endif