// Copyright 2025 鸿源z。保留所有权利。


#include "Characters/GenshinCharacterBase.h"

#include "AbilitySystem/Abilities/GenshinAbilityBase.h"


AGenshinCharacterBase::AGenshinCharacterBase(const class FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer.SetDefaultSubobjectClass<UGenshinMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
	
	
	
	GetMesh()->bPropagateCurvesToFollowers = true;
	GetMesh()->SetCollisionProfileName("NoCollision");
	// GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->CastShadow = false;
	GetMesh()->SetVisibleFlag(false);
	GetMesh()->VisibilityBasedAnimTickOption=EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	
	CoverMesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CoverMesh"));
	CoverMesh->SetupAttachment(GetMesh());
	CoverMesh->SetRenderCustomDepth(true);

}


void AGenshinCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGenshinCharacterBase::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}


void AGenshinCharacterBase::InitAbilitySystemComponent()
{
}

void AGenshinCharacterBase::InitializeAttributeSet() const
{
	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*GetAbilitySystemComponent()->MakeOutgoingSpec(
			DefaultAttributes,
			0.f,
			GetAbilitySystemComponent()->MakeEffectContext()
			).Data.Get(),GetAbilitySystemComponent());
	}
}

void AGenshinCharacterBase::AddStartAbilitiesAndEffects()
{
	for (TSubclassOf<UGameplayEffect> Effect : DefaultEffects)
	{
		FGameplayEffectContextHandle ContextHandle=GetAbilitySystemComponent()->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle=GetAbilitySystemComponent()->MakeOutgoingSpec(Effect,0.f,ContextHandle);
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),GetAbilitySystemComponent());
	}
	
	for (TSubclassOf<UGameplayAbility> Ability : DefaultAbilities)
	{
		FGameplayAbilitySpec AbilitySpec=FGameplayAbilitySpec(Ability,0,-1,this);
		if (const UGenshinAbilityBase* GenshinAbility = Cast<UGenshinAbilityBase>(AbilitySpec.Ability))
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(GenshinAbility->InputTag);
		}
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
	
	for (TSubclassOf<UGameplayAbility> Ability : DefaultDoOnceAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(
			Ability,
			0,
			-1,
			this
			);
		GetAbilitySystemComponent()->GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void AGenshinCharacterBase::SpawnDefaultWeapon()
{
	int32 NumWeaponClasses = WeaponClass.Num();
	for (int32 i = 0; i < NumWeaponClasses; i++)
	{
		if (!WeaponClass[i])
		{
			// Pass空数组
			continue;
		}

		AGenshinWeaponActor* NewWeapon = GetWorld()->SpawnActorDeferred<AGenshinWeaponActor>
		(
			WeaponClass[i],
			FTransform::Identity,
			this,
			this,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);
		// NewWeapon->bSpawnWithCollision = false;
		NewWeapon->FinishSpawning(FTransform::Identity);

		NewWeapon->SetOwningCharacter(this);
		
		Weapons.Add(NewWeapon);

		//如果是第一个武器，则直接装备
		bool bEquipFirstWeapon = (i == 0);
		AddWeaponToInventory(NewWeapon, bEquipFirstWeapon);
	}
}

bool AGenshinCharacterBase::AddWeaponToInventory(AGenshinWeaponActor* NewWeapon, bool bEquipWeapon)
{
	// NewWeapon->SetOwningCharacter(this);已经被整合进生成时设置
	// NewWeapon->AddAbilities();因为AddAbilities已经被整合进Weapon的Equip
	//未来可能会添加一些检测,防止重复Add
	if (bEquipWeapon)
	{
		EquipWeapon(NewWeapon);
		// ClientSyncCurrentWeapon(CurrentWeapon);客户端同步当前武器(不需要)
	}
	return true;
}

void AGenshinCharacterBase::EquipWeapon(AGenshinWeaponActor* NewWeapon)
{
	SetCurrentWeapon(NewWeapon,CurrentWeapon);
	
}

void AGenshinCharacterBase::SetCurrentWeapon(AGenshinWeaponActor* NewWeapon, AGenshinWeaponActor* LastWeapon)
{
	if (NewWeapon == LastWeapon)
	{
		return;
	}
	CurrentWeapon=NewWeapon;
	NewWeapon->Equip();
	if (AbilitySystem)
	{
		//这里就不是卸载武器的技能了,因为武器技能在UnEquip的时候已经调用了,这里是为了取消正在释放的武器能力
		// FGameplayTagContainer AbilityTagsToCancel = FGameplayTagContainer(WeaponAbilityTag);
		// AbilitySystem->CancelAbilities(&AbilityTagsToCancel);
	}
	UnEquipWeapon(LastWeapon);
}

void AGenshinCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

