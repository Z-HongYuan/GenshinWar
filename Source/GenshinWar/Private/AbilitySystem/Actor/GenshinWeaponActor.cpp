// Copyright 2025 鸿源z。保留所有权利。


#include "AbilitySystem/Actor/GenshinWeaponActor.h"
#include "Characters/GenshinCharacterBase.h"


AGenshinWeaponActor::AGenshinWeaponActor()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	RootSceneComponent=CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SetRootComponent(RootSceneComponent);

	WeaponMesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	WeaponMesh->SetRenderCustomDepth(true);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// WeaponMesh->SetRelativeTransform(WeaponMeshRelativeTransform);
}

void AGenshinWeaponActor::SetOwningCharacter(AGenshinCharacterBase* InOwningCharacter)
{
	OwningCharacter=InOwningCharacter;
	if (OwningCharacter)
	{
		AbilitySystem=Cast<UGenshinAbilitySystemComponent>(OwningCharacter->GetAbilitySystemComponent());
		SetOwner(InOwningCharacter);
		AttachToComponent(OwningCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		if (OwningCharacter->GetCurrentWeapon()!=this)
		{
			WeaponMesh->CastShadow=false;
			WeaponMesh->SetVisibility(true,false);
			WeaponMesh->SetVisibility(false,false);
		}
	}
	else
	{
		AbilitySystem = nullptr;
		SetOwner(nullptr);
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}
}

void AGenshinWeaponActor::Equip()
{
	if (!OwningCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("%s %s OwningCharacter is nullptr"), *FString(__FUNCTION__), *GetName());
		return;
	}
	if (WeaponMesh)
	{
		WeaponMesh->AttachToComponent(OwningCharacter->GetCoverMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, OwningCharacter->GetWeaponAttachPointName());
		WeaponMesh->SetRelativeTransform(WeaponMeshRelativeTransform);
		WeaponMesh->CastShadow = true;
		WeaponMesh->bCastHiddenShadow = true;
		WeaponMesh->SetVisibility(true,true);
		AddAbilities();
	}
	if (WeaponTag.IsValid() || OwningCharacter)
	{
		OwningCharacter->GetAbilitySystemComponent()->AddLooseGameplayTag(WeaponTag);
	}
}

void AGenshinWeaponActor::UnEquip()
{
	if (OwningCharacter == nullptr)
	{
		return;
	}
	RemoveAbilities();
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	WeaponMesh->CastShadow = false;
	WeaponMesh->bCastHiddenShadow = false;
	WeaponMesh->SetVisibility(true,true);	
	WeaponMesh->SetVisibility(false,true);

	if (WeaponTag.IsValid() || OwningCharacter)
	{
		OwningCharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(WeaponTag);
	}
}

//添加技能到拥有者
void AGenshinWeaponActor::AddAbilities()
{
	if (!IsValid(OwningCharacter) || !OwningCharacter->GetAbilitySystemComponent())
	{
		return;
	}
	if (UGenshinAbilitySystemComponent* ASC = Cast<UGenshinAbilitySystemComponent>(OwningCharacter->GetAbilitySystemComponent()))
	{
		for (TSubclassOf<UGenshinAbilityBase> Ability : Abilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability,0, -1,this);
			if (const UGenshinAbilityBase* GenshinAbility = Cast<UGenshinAbilityBase>(AbilitySpec.Ability))
			{
				AbilitySpec.GetDynamicSpecSourceTags().AddTag(GenshinAbility->InputTag);
			}
			// GetAbilitySystemComponent()->GiveAbility(AbilitySpec);记得使用GiveAbility的时候需要为技能添加InputTag
			AbilitySpecHandles.Add(ASC->GiveAbility(AbilitySpec));
		}
	}
}

void AGenshinWeaponActor::RemoveAbilities()
{
	if (!IsValid(OwningCharacter) || !OwningCharacter->GetAbilitySystemComponent())
	{
		return;
	}
	if (UGenshinAbilitySystemComponent* ASC = Cast<UGenshinAbilitySystemComponent>(OwningCharacter->GetAbilitySystemComponent()))
	{
		for (FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
		{
			ASC->ClearAbility(Handle);
		}
	}
}

void AGenshinWeaponActor::ResetWeapon()
{
	FireMode = DefaultFireMode;
	PrimaryBulletCount=MaxPrimaryBulletCount;
	SecondaryBulletCount=MaxSecondaryBulletCount;
	// StatusText = DefaultStatusText;
}

AGenshinAbilityTargetActor_LineTrace* AGenshinWeaponActor::GetLineTraceTargetActor()
{
	if (LineTraceTargetActor)
	{
		return LineTraceTargetActor;
	}
	LineTraceTargetActor=GetWorld()->SpawnActor<AGenshinAbilityTargetActor_LineTrace>();
	LineTraceTargetActor->SetOwner(this);
	return LineTraceTargetActor;
}

void AGenshinWeaponActor::ReloadBullet(bool bPrimary)
{
	bPrimary ? PrimaryBulletCount=MaxPrimaryBulletCount : SecondaryBulletCount=MaxSecondaryBulletCount;
}


void AGenshinWeaponActor::BeginPlay()
{
	ResetWeapon();

	// if (!OwningCharacter && bSpawnWithCollision)
	// {
	// 	// Spawned into the world without an owner, enable collision as we are in pickup mode
	// 	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// }
	
	Super::BeginPlay();
	
}

void AGenshinWeaponActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (LineTraceTargetActor)
	{
		LineTraceTargetActor->Destroy();
	}
	Super::EndPlay(EndPlayReason);
}



