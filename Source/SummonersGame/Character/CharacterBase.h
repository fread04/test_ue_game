// CharacterBase.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterStats.h"
#include "Health/HealthComponent.h"
#include "InventoryManager.h"
#include "CharacterBase.generated.h"

UCLASS()
class SUMMONERSGAME_API ACharacterBase : public ACharacter
{
    GENERATED_BODY()

public:
    ACharacterBase();

protected:
    virtual void BeginPlay() override;

    /** Health component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UHealthComponent* HealthComponent;

    /** Inventory component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UInventoryManager* InventoryManager;

    /** Character stats table */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    UDataTable* CharacterStatsTable;

    /** Row name in stats table */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    FName CharacterRowName;

    /** Loaded stats */
    FCharacterStats LoadedStats;

public:
    virtual void Tick(float DeltaTime) override;

    /** Load stats from table */
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void LoadCharacterStats();

    /** Initialize character for dynamic spawn */
    void InitializeCharacter(UDataTable* Table, FName RowName);
};
