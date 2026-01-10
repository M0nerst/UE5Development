// LeaveMeAlone Game by Netologiya. All RightsReserved.

#include "Weapon/LMAWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/LMABaseWeapon.h"
#include "Player/LMADefaultCharacter.h"
#include "Animations/LMAReloadFinishedAnimNotify.h"

class ALMADefaultCharacter;

// Sets default values for this component's properties
ULMAWeaponComponent::ULMAWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void ULMAWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();

	InitAnimNotify();
}

// Called every frame
void ULMAWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULMAWeaponComponent::SpawnWeapon()
{
	Weapon = GetWorld()->SpawnActor<ALMABaseWeapon>(WeaponClass);
	if (Weapon)
	{
		const auto Character = Cast<ACharacter>(GetOwner());
		if (Character)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "r_Weapon_Socket");
			Weapon->OnAmmoEmpty.AddDynamic(this, &ULMAWeaponComponent::OnAmmoEmpty);
		}
	}
}


bool ULMAWeaponComponent::GetCurrentWeaponAmmo(FAmmoWeapon& AmmoWeapon) const
{
	if (Weapon)
	{
		AmmoWeapon = Weapon->GetCurrentAmmoWeapon();
		return true;
	}
	return false;
}


void ULMAWeaponComponent::InitAnimNotify()
{
	if (!ReloadMontage)
		return;
	const auto NotifiesEvents = ReloadMontage->Notifies;
	for (auto NotifyEvent : NotifiesEvents)
	{
		auto ReloadFinish = Cast<ULMAReloadFinishedAnimNotify>(NotifyEvent.Notify);
		if (ReloadFinish)
		{
			ReloadFinish->OnNotifyReloadFinished.AddUObject(this, &ULMAWeaponComponent::OnNotifyReloadFinished);
			break;
		}
	}
}
void ULMAWeaponComponent::OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh)
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (Character->GetMesh() == SkeletalMesh)
	{
		AnimReloading = false;
	}
	if (IsFiring)
	{
		StartFire();
	}
}

bool ULMAWeaponComponent::CanReload() const
{
	return !AnimReloading && Weapon && !Weapon->IsCurrentClipFull();
}

void ULMAWeaponComponent::Reload()
{
	if (!CanReload())
		return;

	Weapon->StopFire();

	Weapon->ChangeClip();
	AnimReloading = true;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	Character->PlayAnimMontage(ReloadMontage);
}

void ULMAWeaponComponent::StartFire()
{
	const auto Character = Cast<ALMADefaultCharacter>(GetOwner());
	if (Character && !Character->GetSprinting() && Weapon && !AnimReloading)
	{
		IsFiring = true;
		Weapon->StartFire();
	}
}

void ULMAWeaponComponent::Fire()
{
	const auto Character = Cast<ALMADefaultCharacter>(GetOwner());
	if (Weapon && !AnimReloading && !Character->GetSprinting())
	{
		Weapon->Fire();
	}
}

void ULMAWeaponComponent::StopFire()
{
	if (Weapon)
	{
		IsFiring = false;
		Weapon->StopFire();
	}
}

void ULMAWeaponComponent::OnAmmoEmpty()
{
	if (Weapon && CanReload())
	{
		Reload();
	}
}


