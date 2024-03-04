// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Source/SourceGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSourceGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	SOURCE_API UClass* Z_Construct_UClass_ASourceGameMode();
	SOURCE_API UClass* Z_Construct_UClass_ASourceGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Source();
// End Cross Module References
	void ASourceGameMode::StaticRegisterNativesASourceGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASourceGameMode);
	UClass* Z_Construct_UClass_ASourceGameMode_NoRegister()
	{
		return ASourceGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ASourceGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASourceGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Source,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASourceGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASourceGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "SourceGameMode.h" },
		{ "ModuleRelativePath", "SourceGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASourceGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASourceGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASourceGameMode_Statics::ClassParams = {
		&ASourceGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASourceGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ASourceGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ASourceGameMode()
	{
		if (!Z_Registration_Info_UClass_ASourceGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASourceGameMode.OuterSingleton, Z_Construct_UClass_ASourceGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASourceGameMode.OuterSingleton;
	}
	template<> SOURCE_API UClass* StaticClass<ASourceGameMode>()
	{
		return ASourceGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASourceGameMode);
	ASourceGameMode::~ASourceGameMode() {}
	struct Z_CompiledInDeferFile_FID_Source_Source_Source_SourceGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Source_Source_Source_SourceGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASourceGameMode, ASourceGameMode::StaticClass, TEXT("ASourceGameMode"), &Z_Registration_Info_UClass_ASourceGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASourceGameMode), 3611037195U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Source_Source_Source_SourceGameMode_h_1509624480(TEXT("/Script/Source"),
		Z_CompiledInDeferFile_FID_Source_Source_Source_SourceGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Source_Source_Source_SourceGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
