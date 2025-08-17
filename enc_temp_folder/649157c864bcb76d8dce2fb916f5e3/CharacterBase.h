// CharacterBase.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterStats.h"
#include "Health/HealthComponent.h"
#include "CharacterBase.generated.h"

UCLASS()
class SUMMONERSGAME_API ACharacterBase : public ACharacter
{
    GENERATED_BODY()

public:
    ACharacterBase();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UHealthComponent* HealthComponent;

    // Table and row for character stats
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    UDataTable* CharacterStatsTable;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    FName CharacterRowName;

    FCharacterStats LoadedStats;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    /** Loads stats from the current CharacterStatsTable & CharacterRowName */
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void LoadCharacterStats();

    /** Initialize character with specific table & row (for dynamic spawning) */
    void InitializeCharacter(UDataTable* Table, FName RowName);
};
