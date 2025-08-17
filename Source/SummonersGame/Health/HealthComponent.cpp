// Fill out your copyright notice in the Description page of Project Settings.


#include "Health/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    CurrentHealth = MaxHealth;
}

void UHealthComponent::TakeDamage(float Amount)
{
    UE_LOG(LogTemp, Log, TEXT("[HealthComp] TakeDamage called: Amount=%.2f | Before: Current=%.2f Max=%.2f"),
        Amount, CurrentHealth, MaxHealth);

    if (Amount <= 0.0f || IsDead())
        return;

    CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.f, MaxHealth);

    UE_LOG(LogTemp, Log, TEXT("[HealthComp] After TakeDamage: Current=%.2f"), CurrentHealth);

    OnHealthChanged.Broadcast(CurrentHealth);

    if (CurrentHealth <= 0.f)
    {
        UE_LOG(LogTemp, Log, TEXT("[HealthComp] Died"));
        OnDeath.Broadcast();
    }
}

void UHealthComponent::Heal(float Amount)
{
    UE_LOG(LogTemp, Log, TEXT("[HealthComp] Heal called: Amount=%.2f | Before: Current=%.2f Max=%.2f"),
        Amount, CurrentHealth, MaxHealth);

    if (Amount <= 0.0f || IsDead())
        return;

    CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.f, MaxHealth);

    UE_LOG(LogTemp, Log, TEXT("[HealthComp] After Heal: Current=%.2f"), CurrentHealth);

    OnHealthChanged.Broadcast(CurrentHealth);
}


bool UHealthComponent::IsDead() const
{
    return CurrentHealth <= 0.0f;
}

float UHealthComponent::GetHealth() const
{
    return CurrentHealth;
}

float UHealthComponent::GetMaxHealth() const
{
    return MaxHealth;
}