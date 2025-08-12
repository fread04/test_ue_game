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
    // ������� ������ � �����
    UPROPERTY()
    AWeaponBase* CurrentWeapon;

public:
    // �������� ������� ������
    UFUNCTION(BlueprintCallable)
    AWeaponBase* GetCurrentWeapon() const { return CurrentWeapon; }

    UFUNCTION(BlueprintCallable)
    void PickUpWeapon();

    // ������ ������ (���������)
    UFUNCTION(BlueprintCallable)
    void EquipWeapon(AWeaponBase* NewWeapon);

    // ����� ������� ������ (������� null)
    UFUNCTION(BlueprintCallable)
    void UnequipWeapon();

    // ���������� �� �������� ������
    UFUNCTION(BlueprintCallable)
    void FireCurrentWeapon();

    // ������������ ������� ������
    UFUNCTION(BlueprintCallable)
    void ReloadCurrentWeapon();

    UPROPERTY(EditAnywhere, Category = "Pickup")
    float PickupRange = 500.f;

};
