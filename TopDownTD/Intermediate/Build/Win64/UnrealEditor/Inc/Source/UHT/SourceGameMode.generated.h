// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SourceGameMode.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SOURCE_SourceGameMode_generated_h
#error "SourceGameMode.generated.h already included, missing '#pragma once' in SourceGameMode.h"
#endif
#define SOURCE_SourceGameMode_generated_h

#define FID_Source_Source_Source_SourceGameMode_h_12_SPARSE_DATA
#define FID_Source_Source_Source_SourceGameMode_h_12_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Source_Source_Source_SourceGameMode_h_12_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Source_Source_Source_SourceGameMode_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Source_Source_Source_SourceGameMode_h_12_ACCESSORS
#define FID_Source_Source_Source_SourceGameMode_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASourceGameMode(); \
	friend struct Z_Construct_UClass_ASourceGameMode_Statics; \
public: \
	DECLARE_CLASS(ASourceGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Source"), SOURCE_API) \
	DECLARE_SERIALIZER(ASourceGameMode)


#define FID_Source_Source_Source_SourceGameMode_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	SOURCE_API ASourceGameMode(ASourceGameMode&&); \
	SOURCE_API ASourceGameMode(const ASourceGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(SOURCE_API, ASourceGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASourceGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASourceGameMode) \
	SOURCE_API virtual ~ASourceGameMode();


#define FID_Source_Source_Source_SourceGameMode_h_9_PROLOG
#define FID_Source_Source_Source_SourceGameMode_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Source_Source_Source_SourceGameMode_h_12_SPARSE_DATA \
	FID_Source_Source_Source_SourceGameMode_h_12_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Source_Source_Source_SourceGameMode_h_12_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Source_Source_Source_SourceGameMode_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Source_Source_Source_SourceGameMode_h_12_ACCESSORS \
	FID_Source_Source_Source_SourceGameMode_h_12_INCLASS_NO_PURE_DECLS \
	FID_Source_Source_Source_SourceGameMode_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SOURCE_API UClass* StaticClass<class ASourceGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Source_Source_Source_SourceGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
