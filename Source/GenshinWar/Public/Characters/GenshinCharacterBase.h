// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/GenshinAbilitySystemComponent.h"
#include "AbilitySystem/Actor/GenshinWeaponActor.h"
#include "AbilitySystem/Attribute/GenshinAttributeSet.h"
#include "GameFramework/Character.h"
#include "Component/GenshinMovementComponent.h"
#include "GenshinCharacterBase.generated.h"

/**
 * 所有角色的基类
 * 重载Movement组件
 */
UCLASS()
class GENSHINWAR_API AGenshinCharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:	
	virtual void Tick(float DeltaTime) override;
	
	AGenshinCharacterBase(const class FObjectInitializer& ObjectInitializer);

	// 处理AbilitySystem相关
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override{return AbilitySystem;}
	UGenshinAttributeSet* GetAttributeSet() const { return AttributeSet; }

	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AbilitySystem|MyFunction")
	virtual USkeletalMeshComponent* GetCoverMesh() {return CoverMesh;}

	//获取当前武器
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AbilitySystem|MyFunction")
	virtual AGenshinWeaponActor* GetCurrentWeapon() {return CurrentWeapon;}

	FName GetWeaponAttachPointName(){return WeaponAttachPointName;}
	
protected:
	
	// 处理AbilitySystem相关
	UPROPERTY()
	TObjectPtr<UGenshinAbilitySystemComponent> AbilitySystem;
	UPROPERTY()
	TObjectPtr<UGenshinAttributeSet> AttributeSet;
	
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem|Default")
	TSubclassOf<UGameplayEffect> DefaultAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem|Default")
	TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;
	
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem|Default")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem|Default")
	TArray<TSubclassOf<UGameplayAbility>> DefaultDoOnceAbilities;
	
	virtual void InitAbilitySystemComponent();
	void InitializeAttributeSet() const;
	void AddStartAbilitiesAndEffects();

	//处理Mesh相关
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "CoverMesh")
	TObjectPtr<USkeletalMeshComponent> CoverMesh;
	
	//武器相关
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AbilitySystem|Weapon")
	FName WeaponAttachPointName;
	
	UPROPERTY(BlueprintReadOnly,Category = "AbilitySystem|Weapon")
	TObjectPtr<AGenshinWeaponActor> CurrentWeapon;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AbilitySystem|Weapon")
	TArray<TSubclassOf<AGenshinWeaponActor>> WeaponClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "AbilitySystem|Weapon")
	TArray<TObjectPtr<AGenshinWeaponActor>> Weapons;

	//用于生成默认的武器Actor
	void SpawnDefaultWeapon();

	//用于添加武器到背包
	bool AddWeaponToInventory(AGenshinWeaponActor* NewWeapon, bool bEquipWeapon = false);

	//用于装备武器的主函数
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Weapon")
	void EquipWeapon(AGenshinWeaponActor* NewWeapon);

	//用于设置当前武器
	void SetCurrentWeapon(AGenshinWeaponActor* NewWeapon, AGenshinWeaponActor* LastWeapon);

	//用于卸载武器的基础操作
	void UnEquipWeapon(AGenshinWeaponActor* WeaponToUnEquip){ if (WeaponToUnEquip) WeaponToUnEquip->UnEquip();}
};
