// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponData.generated.h"

/**
 * 
 */
class SUMMONERSGAME_API WeaponData
{
public:
	WeaponData();
	~WeaponData();
};

// Ёто ключева€ строчка Ч так мы говорим UE, что структура будет видна в блюпринтах и Data Table
USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
    GENERATED_BODY()

    // Weapon name
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FString WeaponName;

    // Base damage
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float Damage;

    // FireRate (shots per second)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float FireRate;

    // Magazine capacity
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    int32 MagazineSize;

    // Effective range
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float Range;

    // Speed of bullets
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float ProjectileSpeed;

    // Time to reload
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float ReloadTime;
};
