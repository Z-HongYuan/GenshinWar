// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GenshinProjectileActor.generated.h"

/**
 * 带有ASC组件的抛射物Actor
 */
UCLASS()
class GENSHINWAR_API AGenshinProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:
	AGenshinProjectileActor();

	//TODO 应用GE到OverlyActor上
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Projectile")
	void ApplyEffectToOverlap(AActor* ApplyActor,bool bIgnorePlayer);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RootComponent")
	TObjectPtr<USceneComponent> RootSceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileMesh")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CapsuleComponent")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectileMovementComponent")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
};
