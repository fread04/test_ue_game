#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponData.h"
#include "Components/SphereComponent.h"

#include "WeaponBase.generated.h"

UCLASS()
class SUMMONERSGAME_API AWeaponBase : public AActor
{
    GENERATED_BODY()

public:
    AWeaponBase();

protected:
    virtual void BeginPlay() override;

    /*UFUNCTION()
    void OnPickupSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);*/

public:
    // ==== ���������� ====
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* Root;

    // ==== ��������� ====
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    UDataTable* WeaponDataTable;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    FName RowName; // ��� ������ � DataTable

    // ==== ������ ====
private:
    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    FWeaponData WeaponStats; // ������� ����� (�� DataTable)

    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    int32 CurrentAmmo; // ������� ������� � ��������

    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    bool bIsReloading = false;

    FTimerHandle ReloadTimer;

    FTimerHandle ShotDelayTimer;

    UPROPERTY(VisibleAnywhere, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
    USphereComponent* PickupSphere;

    UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* WeaponMesh;

public:
    // ==== ������ ====
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void LoadWeaponData();

    UFUNCTION(BlueprintPure, Category = "Weapon")
    FWeaponData GetWeaponStats() const { return WeaponStats; }

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    bool CanShoot() const ;

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void Shoot();

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void Reload();

    bool IsReloading() const { return GetWorldTimerManager().IsTimerActive(ReloadTimer); }

private:
    void FinishReload();

    void ResetShot();
};
