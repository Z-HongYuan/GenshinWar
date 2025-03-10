// Copyright 2025 鸿源z。保留所有权利。


#include "Characters/GenshinPlayerCharacter.h"

class UGenshinMovementComponent;

AGenshinPlayerCharacter::AGenshinPlayerCharacter(const class FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer.SetDefaultSubobjectClass<UGenshinMovementComponent>(CharacterMovementComponentName))
{
	AbilitySystem = CreateDefaultSubobject<UGenshinAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<UGenshinAttributeSet>(TEXT("AttributeSet"));

	//添加标签
	Tags.Add(FName("Player"));
	Tags.Add(FName("NeedCamera"));
}

void AGenshinPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystemComponent();
}

void AGenshinPlayerCharacter::InitAbilitySystemComponent()
{
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	
	InitializeAttributeSet();
	AddStartAbilitiesAndEffects();

	SpawnDefaultWeapon();
}
