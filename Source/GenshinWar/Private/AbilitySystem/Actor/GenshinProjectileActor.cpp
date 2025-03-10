// Copyright 2025 鸿源z。保留所有权利。


#include "AbilitySystem/Actor/GenshinProjectileActor.h"



AGenshinProjectileActor::AGenshinProjectileActor()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	//根组件
	RootSceneComponent=CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SetRootComponent(RootSceneComponent);
	
	//抛射物移动组件
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed=3000.0f;
	ProjectileMovementComponent->ProjectileGravityScale=1.0f;
	
	//碰撞体
	CapsuleComponent=CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetCollisionProfileName(TEXT("Projectile"));
	CapsuleComponent->CanCharacterStepUpOn=ECanBeCharacterBase::ECB_No;
	CapsuleComponent->SetAllUseCCD(true);

	//抛射物网格体
	ProjectileMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetCollisionProfileName(TEXT("NoCollision"));
	ProjectileMesh->CanCharacterStepUpOn=ECanBeCharacterBase::ECB_No;
	ProjectileMesh->SetGenerateOverlapEvents(false);

}

void AGenshinProjectileActor::ApplyEffectToOverlap(AActor* ApplyActor,bool bIgnorePlayer)
{
	if (bIgnorePlayer)
	{
		if(!ApplyActor->ActorHasTag(TEXT("Player")))
		{
			UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ApplyActor);
			if (ASC)
			{
				// ASC->ApplyGameplayEffectToSelf(EffectToApply.GetDefaultObject());
			}
		}
	}
	else
	{
		
	}
	
	
}


