#include "WeaponBase.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

AWeaponBase::AWeaponBase()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
    PickupSphere->SetupAttachment(RootComponent);
    PickupSphere->SetSphereRadius(150.f);  // радиус подбора — настроить под себя
    PickupSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    PickupSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    PickupSphere->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    PickupSphere->SetHiddenInGame(false);

    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    WeaponMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
    WeaponMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

}

void AWeaponBase::BeginPlay()
{
    Super::BeginPlay();
    LoadWeaponData();
}

void AWeaponBase::LoadWeaponData()
{
    if (WeaponDataTable)
    {
        FWeaponData* Data = WeaponDataTable->FindRow<FWeaponData>(RowName, TEXT(""));

        if (Data)
        {
            WeaponStats = *Data;
            CurrentAmmo = WeaponStats.MagazineSize;
            UE_LOG(LogTemp, Log, TEXT("Loaded weapon: %s | Ammo: %d"), *WeaponStats.WeaponName, CurrentAmmo);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Weapon row not found: %s"), *RowName.ToString());
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("WeaponDataTable is NULL"));
    }
}

bool AWeaponBase::CanShoot() const
{
    return !GetWorldTimerManager().IsTimerActive(ShotDelayTimer) && !IsReloading() && CurrentAmmo > 0;
}

void AWeaponBase::Shoot()
{
    if (!CanShoot())
    {
        if (IsReloading())
        {
            UE_LOG(LogTemp, Warning, TEXT("%s is reloading!"), *WeaponStats.WeaponName);
        }
        else if (CurrentAmmo <= 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("%s: No ammo!"), *WeaponStats.WeaponName);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("%s: Can't shoot yet!"), *WeaponStats.WeaponName);
        }
        return;
    }

    
    CurrentAmmo--;
    UE_LOG(LogTemp, Log, TEXT("%s fired! Ammo left: %d"), *WeaponStats.WeaponName, CurrentAmmo);

    // Тут будет логика спавна пули
    TArray<AActor*> ActorsToIgnore;
    FHitResult HitResult;
    UKismetSystemLibrary::LineTraceSingle(this, GetActorLocation(), GetActorLocation() + GetActorForwardVector()*1000, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);

    // Разрешаем стрелять снова через FireRate
    GetWorldTimerManager().SetTimer(
        ShotDelayTimer,
        this,
        &AWeaponBase::ResetShot,
        1.f / WeaponStats.FireRate,
        false
    );
}


void AWeaponBase::Reload()
{
    if (IsReloading())
    {
        UE_LOG(LogTemp, Warning, TEXT("%s is already reloading!"), *WeaponStats.WeaponName);
        return;
    }

    if (CurrentAmmo == WeaponStats.MagazineSize)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: Magazine already full!"), *WeaponStats.WeaponName);
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("%s started reloading..."), *WeaponStats.WeaponName);

    // Симулируем задержку перезарядки через таймер
    GetWorldTimerManager().SetTimer(
        ReloadTimer,
        this,
        &AWeaponBase::FinishReload,
        WeaponStats.ReloadTime,
        false
    );
}

void AWeaponBase::FinishReload()
{
    CurrentAmmo = WeaponStats.MagazineSize;
    UE_LOG(LogTemp, Log, TEXT("%s reloaded. Ammo: %d"), *WeaponStats.WeaponName, CurrentAmmo);
}

void AWeaponBase::ResetShot()
{
    // Этот метод нужен, чтобы снять блокировку стрельбы после задержки FireRate
    // В твоём случае логика проста — мы просто прекращаем таймер (что и так происходит),
    // и потому можно не делать ничего здесь.
    // Но чтобы не было ошибки компиляции, метод должен быть определён.

    // Здесь можно оставить пустым или добавить логи, если хочешь
    UE_LOG(LogTemp, Log, TEXT("%s can shoot again."), *WeaponStats.WeaponName);
}
