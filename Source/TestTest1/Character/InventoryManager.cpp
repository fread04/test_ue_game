#include "InventoryManager.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

UInventoryManager::UInventoryManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryManager::BeginPlay()
{
    Super::BeginPlay();
    CurrentWeapon = nullptr;
}

void UInventoryManager::PickUpWeapon()
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    // ѕолучаем контроллер и камеру персонажа
    APlayerController* PC = Cast<APlayerController>(Owner->GetInstigatorController());
    if (!PC) return;

    FVector CameraLocation;
    FRotator CameraRotation;

    PC->GetPlayerViewPoint(CameraLocation, CameraRotation);

    FVector TraceStart = CameraLocation;
    FVector TraceEnd = TraceStart + (CameraRotation.Vector() * PickupRange);

    FHitResult HitResult;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);  // „тобы не попадать в самого персонажа

    bool bHit = Owner->GetWorld()->LineTraceSingleByChannel(
        HitResult,
        TraceStart,
        TraceEnd,
        ECC_Visibility,
        Params
    );

    // ƒл€ дебага: рисуем луч в мире
    DrawDebugLine(Owner->GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 2.f);

    if (bHit && IsValid(HitResult.GetActor()))
    {
        AWeaponBase* HitWeapon = Cast<AWeaponBase>(HitResult.GetActor());
        if (HitWeapon)
        {
            UE_LOG(LogTemp, Log, TEXT("Weapon found to pick up: %s"), *HitWeapon->GetName());
            EquipWeapon(HitWeapon);

            // ѕр€чем оружие из мира и отключаем коллизию
            HitWeapon->SetActorHiddenInGame(true);
            HitWeapon->SetActorEnableCollision(false);
        }
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("No weapon found in line of sight"));
    }
}


void UInventoryManager::EquipWeapon(AWeaponBase* NewWeapon)
{
    if (!NewWeapon) return;

    if (CurrentWeapon)
    {
        // ≈сли хочешь Ч можно добавить логику сн€ти€ старого оружи€, например, скрыть или дропнуть
        UnequipWeapon();
    }

    CurrentWeapon = NewWeapon;

    // —делать оружие дочерним актором персонажа, чтобы "в руках"
    AActor* Owner = GetOwner();
    if (Owner)
    {
        NewWeapon->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    }
}

void UInventoryManager::UnequipWeapon()
{
    if (CurrentWeapon)
    {
        CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        CurrentWeapon = nullptr;
    }
}

void UInventoryManager::FireCurrentWeapon()
{
    if (CurrentWeapon)
    {
        CurrentWeapon->Shoot();
    }
}

void UInventoryManager::ReloadCurrentWeapon()
{
    if (CurrentWeapon)
    {
        CurrentWeapon->Reload();
    }
}
