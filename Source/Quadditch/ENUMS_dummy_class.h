// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECmdState : uint8 {
    NONE       UMETA(DisplayName = "NONE"),
    TAKEOFF    UMETA(DisplayName = "TAKEOFF"),
    LAND       UMETA(DisplayName = "LAND"),
};

UENUM(BlueprintType)
enum class ECmdInter : uint8 {
    PREP       UMETA(DisplayName = "PREP"),
    MOVE       UMETA(DisplayName = "MOVE"),
    FINISH     UMETA(DisplayName = "FINISH"),
};

// Example usage GetEnumValueAsString<EVictoryEnum>("EVictoryEnum", VictoryEnum))); 

template<typename TEnum>
static FORCEINLINE FString GetEnumValueAsString(const FString& Name, TEnum Value) {
    const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
    if (!enumPtr) return FString("Invalid");
    return enumPtr->GetNameStringByIndex((int64)Value);
}







class QUADDITCH_API ENUMS_dummy_class
{
public:
	ENUMS_dummy_class();
	~ENUMS_dummy_class();
    ECmdState dum_a;
    ECmdInter dum_b;
};
