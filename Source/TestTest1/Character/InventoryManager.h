#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/WeaponBase.h"
#include "InventoryManager.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTTEST1_API UInventoryManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UInventoryManager();

protected:
    virtual void BeginPlay() override;

private:
    // Текущее оружие в руках
    UPROPERTY()
    AWeaponBase* CurrentWeapon;

public:
    // Получить текущее оружие
    UFUNCTION(BlueprintCallable)
    AWeaponBase* GetCurrentWeapon() const { return CurrentWeapon; }

    UFUNCTION(BlueprintCallable)
    void PickUpWeapon();

    // Надеть оружие (назначить)
    UFUNCTION(BlueprintCallable)
    void EquipWeapon(AWeaponBase* NewWeapon);

    // Снять текущее оружие (сделать null)
    UFUNCTION(BlueprintCallable)
    void UnequipWeapon();

    // Стрельнуть из текущего оружия
    UFUNCTION(BlueprintCallable)
    void FireCurrentWeapon();

    // Перезарядить текущее оружие
    UFUNCTION(BlueprintCallable)
    void ReloadCurrentWeapon();

    UPROPERTY(EditAnywhere, Category = "Pickup")
    float PickupRange = 500.f;

};
