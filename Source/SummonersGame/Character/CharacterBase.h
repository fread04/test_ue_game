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

    /** Компонент здоровья */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UHealthComponent* HealthComponent;

    /** Таблица характеристик персонажа */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    UDataTable* CharacterStatsTable;

    /** Имя строки в таблице характеристик */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    FName CharacterRowName;

    /** Загруженные характеристики */
    FCharacterStats LoadedStats;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    /** Загружает характеристики из текущей CharacterStatsTable & CharacterRowName */
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void LoadCharacterStats();

    /** Инициализирует персонажа таблицей и строкой (для динамического спавна) */
    void InitializeCharacter(UDataTable* Table, FName RowName);
};
