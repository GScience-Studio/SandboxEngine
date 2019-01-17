#pragma once

#define SANDBOX_ENGINE_VERSION "Alpha 0.0.1"

#define SEAPI extern "C" __declspec(dllexport)

#define SBE_NameToStr(name) #name

enum SBE_ModInitializer_Type
{
	ModInitializer,
	BlockInitializer
};

struct SBE_BlockRegisterFunInfo
{
	const char* name;
	void* func;
};

typedef void (*SBE_BlockRegisterFunPtr)(const char* blockName, int infoNum, SBE_BlockRegisterFunInfo* infos);

struct SBE_ModBlockInitializerInfo
{
	SBE_BlockRegisterFunPtr RegisterFunPtr;
};

typedef void (*SBE_ModInitializer)(SBE_ModInitializer_Type type, const void* data);

#define SBE_ModInitializerFun SEAPI void SBE_ModMain(SBE_ModInitializer_Type type,const void* data)

#include "SandboxEngine/GameEventArgs.h"