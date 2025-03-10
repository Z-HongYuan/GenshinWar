// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GenshinAbilitySystemComponent.h"
#include "GameFramework/Actor.h"
#include "GenshinActorBase.generated.h"

/**
 * 带有ASC的基类Actor
 */
UCLASS()
class GENSHINWAR_API AGenshinActorBase : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	
	AGenshinActorBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override{return AbilitySystem;}


protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UGenshinAbilitySystemComponent> AbilitySystem;
};
