#include "InventoryManager.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

UInventoryManager::UInventoryManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryManager::BeginPlay()
{
    Super::BeginPlay();
}

AWeaponBase* UInventoryManager::GetCurrentWeapon() const
{
    if (CurrentSlotIndex >= 0 && CurrentSlotIndex < MaxSlots)
    {
        return Weapons[CurrentSlotIndex];
    }
    return nullptr;
}

int32 UInventoryManager::FindEmptySlot() const
{
    for (int32 i = 0; i < MaxSlots; i++)
    {
        if (!Weapons[i])
            return i;
    }
    return -1;
}

void UInventoryManager::AttachWeaponToHand(AWeaponBase* Weapon)
{
    ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
    if (!OwnerChar || !Weapon) return;

    Weapon->AttachToComponent(
        OwnerChar->GetMesh(),
        FAttachmentTransformRules::SnapToTargetNotIncludingScale,
        FName("WeaponSocket") // Create this socket in skeletal mesh
    );
}

void UInventoryManager::DetachWeapon(AWeaponBase* Weapon)
{
    if (!Weapon) return;
    Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void UInventoryManager::PickUpWeapon()
{
    ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
    if (!OwnerChar) return;

    UCameraComponent* Camera = OwnerChar->FindComponentByClass<UCameraComponent>();
    if (!Camera) return;

    FVector Start = Camera->GetComponentLocation();
    FVector End = Start + Camera->GetForwardVector() * PickupRange;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(OwnerChar);

    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.f);

    if (bHit)
    {
        AWeaponBase* Weapon = Cast<AWeaponBase>(Hit.GetActor());
        if (Weapon)
        {
            int32 EmptySlot = FindEmptySlot();
            if (EmptySlot != -1)
            {
                Weapons[EmptySlot] = Weapon;
                Weapon->SetActorHiddenInGame(true);
                Weapon->SetActorEnableCollision(false);

                // If no weapon equipped - equip immediately
                if (CurrentSlotIndex == -1)
                {
                    EquipWeapon(EmptySlot);
                }
            }
        }
    }
}

void UInventoryManager::EquipWeapon(int32 SlotIndex)
{
    if (SlotIndex < 0 || SlotIndex >= MaxSlots) return;
    if (!Weapons[SlotIndex]) return;

    // Unequip current
    if (CurrentSlotIndex != -1 && Weapons[CurrentSlotIndex])
    {
        Weapons[CurrentSlotIndex]->SetActorHiddenInGame(true);
        DetachWeapon(Weapons[CurrentSlotIndex]);
    }

    CurrentSlotIndex = SlotIndex;

    Weapons[CurrentSlotIndex]->SetActorHiddenInGame(false);
    AttachWeaponToHand(Weapons[CurrentSlotIndex]);
}

void UInventoryManager::UnequipCurrentWeapon()
{
    if (CurrentSlotIndex != -1 && Weapons[CurrentSlotIndex])
    {
        DetachWeapon(Weapons[CurrentSlotIndex]);
        Weapons[CurrentSlotIndex]->SetActorHiddenInGame(true);
        CurrentSlotIndex = -1;
    }
}

void UInventoryManager::DropCurrentWeapon()
{
    if (CurrentSlotIndex == -1) return;

    ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
    if (!OwnerChar) return;

    AWeaponBase* Weapon = Weapons[CurrentSlotIndex];
    if (!Weapon) return;

    DetachWeapon(Weapon);
    Weapon->SetActorHiddenInGame(false);
    Weapon->SetActorEnableCollision(true);
    Weapon->SetActorLocation(OwnerChar->GetActorLocation() + OwnerChar->GetActorForwardVector() * 50.f);

    Weapons[CurrentSlotIndex] = nullptr;
    CurrentSlotIndex = -1;
}

void UInventoryManager::NextWeapon()
{
    if (MaxSlots < 2) return;
    int32 NewIndex = (CurrentSlotIndex + 1) % MaxSlots;
    if (Weapons[NewIndex])
    {
        EquipWeapon(NewIndex);
    }
}

void UInventoryManager::PreviousWeapon()
{
    if (MaxSlots < 2) return;
    int32 NewIndex = (CurrentSlotIndex - 1 + MaxSlots) % MaxSlots;
    if (Weapons[NewIndex])
    {
        EquipWeapon(NewIndex);
    }
}

void UInventoryManager::FireCurrentWeapon()
{
    if (GetCurrentWeapon())
    {
        GetCurrentWeapon()->Shoot();
    }
}

void UInventoryManager::ReloadCurrentWeapon()
{
    if (GetCurrentWeapon())
    {
        GetCurrentWeapon()->Reload();
    }
}
