// CharacterBase.cpp
#include "CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

ACharacterBase::ACharacterBase()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create health component
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

    // Create inventory component
    InventoryManager = CreateDefaultSubobject<UInventoryManager>(TEXT("InventoryManager"));
}

void ACharacterBase::BeginPlay()
{
    Super::BeginPlay();

    // Load stats if table and row are set
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

void ACharacterBase::LoadCharacterStats()
{
    if (!CharacterStatsTable || CharacterRowName.IsNone())
        return;

    FCharacterStats* Data = CharacterStatsTable->FindRow<FCharacterStats>(CharacterRowName, TEXT(""));

    if (Data)
    {
        LoadedStats = *Data;

        // Set movement speed
        if (GetCharacterMovement())
        {
            GetCharacterMovement()->MaxWalkSpeed = LoadedStats.WalkSpeed;
        }

        // Set health
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

void ACharacterBase::InitializeCharacter(UDataTable* Table, FName RowName)
{
    CharacterStatsTable = Table;
    CharacterRowName = RowName;
    LoadCharacterStats();
}
