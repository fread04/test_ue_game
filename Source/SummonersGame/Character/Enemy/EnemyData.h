// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyData.generated.h"

/**
 * 
 */
class SUMMONERSGAME_API EnemyData
{
public:
	EnemyData();
	~EnemyData();
};

USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
    GENERATED_BODY();

    //UPROPERTY(EditAnywhere, BlueprintReadWrite)
    //FName EnemyID; // уникальное имя строки, можно использовать как "Goblin_Warrior"

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<ACharacter> EnemyClass; // какой класс спавним (например, EnemyBase или его наследник)

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MoveSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<USkeletalMesh> Mesh; // чтобы не грузить в память сразу

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UAnimBlueprint> AnimationBP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AController> AIControllerClass;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite)
    //TSoftObjectPtr<UBehaviorTree> BehaviorTree;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite)
    //FGameplayTagContainer EnemyTags; // "Enemy.Type.Summoner", "Enemy.Faction.Demons"

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName; // для UI

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> Icon; // если надо показывать врага в UI
};
