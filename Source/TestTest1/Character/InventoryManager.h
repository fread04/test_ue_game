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
    static constexpr int32 MaxSlots = 2;

    // Weapon slots (two maximum)
    UPROPERTY()
    AWeaponBase* Weapons[MaxSlots] = { nullptr, nullptr };

    // Currently equipped weapon slot index (-1 = none)
    int32 CurrentSlotIndex = -1;

    UPROPERTY(EditAnywhere, Category = "Pickup")
    float PickupRange = 500.f;

    // Helper to find first empty slot, returns -1 if inventory full
    int32 FindEmptySlot() const;

    // Attach weapon to character's mesh (right hand socket)
    void AttachWeaponToHand(AWeaponBase* Weapon);

    // Detach weapon from character
    void DetachWeapon(AWeaponBase* Weapon);

public:
    UFUNCTION(BlueprintCallable)
    AWeaponBase* GetCurrentWeapon() const;

    UFUNCTION(BlueprintCallable)
    void PickUpWeapon();

    UFUNCTION(BlueprintCallable)
    void EquipWeapon(int32 SlotIndex);

    UFUNCTION(BlueprintCallable)
    void UnequipCurrentWeapon();

    UFUNCTION(BlueprintCallable)
    void DropCurrentWeapon();

    UFUNCTION(BlueprintCallable)
    void NextWeapon();

    UFUNCTION(BlueprintCallable)
    void PreviousWeapon();

    UFUNCTION(BlueprintCallable)
    void FireCurrentWeapon();

    UFUNCTION(BlueprintCallable)
    void ReloadCurrentWeapon();
};
