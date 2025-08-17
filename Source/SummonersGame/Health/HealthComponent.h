// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUMMONERSGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    float CurrentHealth;

public:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDeath OnDeath;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnHealthChanged OnHealthChanged;

    UFUNCTION(BlueprintCallable, Category = "Health")
    void TakeDamage(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Health")
    void Heal(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const;

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealth() const;

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetMaxHealth() const;

    UFUNCTION(BlueprintCallable, Category = "Health")
    void SetMaxHealth(float NewMaxHealth)
    {
        MaxHealth = FMath::Max(NewMaxHealth, 1.f);
        // Не трогаем CurrentHealth здесь, пусть вызывающий код сам задаст CurrentHealth
        OnHealthChanged.Broadcast(CurrentHealth);
    }


    UFUNCTION(BlueprintCallable, Category = "Health")
    void SetCurrentHealth(float NewHealth)
    {
        CurrentHealth = FMath::Clamp(NewHealth, 0.f, MaxHealth);
        OnHealthChanged.Broadcast(CurrentHealth);

        if (CurrentHealth <= 0.f)
        {
            OnDeath.Broadcast();
        }
    }

};