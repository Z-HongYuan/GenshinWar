// Copyright 2025 鸿源z。保留所有权利。


#include "Characters/GenshinEnemyCharacter.h"

class UGenshinMovementComponent;

AGenshinEnemyCharacter::AGenshinEnemyCharacter(const class FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer.SetDefaultSubobjectClass<UGenshinMovementComponent>(CharacterMovementComponentName))
{
	AbilitySystem = CreateDefaultSubobject<UGenshinAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<UGenshinAttributeSet>(TEXT("AttributeSet"));

	Tags.Add(FName("Enemy"));
}

void AGenshinEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystemComponent();
}

void AGenshinEnemyCharacter::InitAbilitySystemComponent()
{
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	
	InitializeAttributeSet();
	AddStartAbilitiesAndEffects();

	SpawnDefaultWeapon();

}
