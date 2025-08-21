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
    //FName EnemyID; // ���������� ��� ������, ����� ������������ ��� "Goblin_Warrior"

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<ACharacter> EnemyClass; // ����� ����� ������� (��������, EnemyBase ��� ��� ���������)

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MoveSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<USkeletalMesh> Mesh; // ����� �� ������� � ������ �����

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UAnimBlueprint> AnimationBP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AController> AIControllerClass;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite)
    //TSoftObjectPtr<UBehaviorTree> BehaviorTree;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite)
    //FGameplayTagContainer EnemyTags; // "Enemy.Type.Summoner", "Enemy.Faction.Demons"

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName; // ��� UI

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> Icon; // ���� ���� ���������� ����� � UI
};
