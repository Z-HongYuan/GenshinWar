// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "WheeledVehiclePawn.h"
#include "AbilitySystem/GenshinAbilitySystemComponent.h"
#include "AbilitySystem/Attribute/GenshinAttributeSet.h"
#include "GenshinVehiclePawn.generated.h"

/**
 * 拥有ASC的载具Pawn
 * 注意切换UI和切换技能
 */
UCLASS()
class GENSHINWAR_API AGenshinVehiclePawn : public AWheeledVehiclePawn,public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AGenshinVehiclePawn();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override{return AbilitySystemComponent;}
	UGenshinAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UGenshinAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UGenshinAttributeSet> AttributeSet;
};
