#include "CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

ACharacterBase::ACharacterBase()
{
    PrimaryActorTick.bCanEverTick = true;
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void ACharacterBase::BeginPlay()
{
    Super::BeginPlay();

    // Загружаем статы
    if (CharacterStatsTable && !CharacterRowName.IsNone())
    {
        LoadCharacterStats();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Character stats not initialized! Table: %s | Row: %s"),
            CharacterStatsTable ? TEXT("OK") : TEXT("NULL"),
            *CharacterRowName.ToString());
    }
}


void ACharacterBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterBase::LoadCharacterStats()
{
    if (!CharacterStatsTable || CharacterRowName.IsNone()) return;

    FCharacterStats* Data = CharacterStatsTable->FindRow<FCharacterStats>(CharacterRowName, TEXT(""));

    if (Data)
    {
        LoadedStats = *Data;

        // Устанавливаем скорость
        if (GetCharacterMovement())
        {
            GetCharacterMovement()->MaxWalkSpeed = LoadedStats.WalkSpeed;
        }

        // Устанавливаем здоровье
        if (HealthComponent)
        {
            HealthComponent->SetMaxHealth(LoadedStats.MaxHealth);
            HealthComponent->SetCurrentHealth(LoadedStats.MaxHealth);
        }

        UE_LOG(LogTemp, Log, TEXT("Loaded stats for %s: WalkSpeed=%.1f, MaxHealth=%.1f"),
            *CharacterRowName.ToString(), LoadedStats.WalkSpeed, LoadedStats.MaxHealth);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No row found for %s in CharacterStatsTable"), *CharacterRowName.ToString());
    }
}
