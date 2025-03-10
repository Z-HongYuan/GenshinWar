// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "PaperSprite.h"
#include "AbilitySystem/GenshinAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/GenshinAbilityBase.h"
#include "GameFramework/Actor.h"
#include "TargetDataActor/GenshinAbilityTargetActor_LineTrace.h"
#include "GenshinWeaponActor.generated.h"

class AGenshinCharacterBase;
/**
 * 最主要的WeaponActor基类
 * 用于装载技能等功能
 * 拥有的信息
 * ASC技能系统
 * Tag
 * Icon
 * FireMode等
 */
UCLASS()
class GENSHINWAR_API AGenshinWeaponActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	AGenshinWeaponActor();

	//武器自己的资产Tag
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "AbilitySystem|Weapon")
	FGameplayTag WeaponTag;

	//武器的Icon
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AbilitySystem|UI")
	UPaperSprite* WeaponIcon;

	//武器射击模式
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly, Category = "AbilitySystem|Weapon")
	FGameplayTag FireMode;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override{return AbilitySystem;}

	//有用的工具函数
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AbilitySystem|WeaponMesh")
	virtual USkeletalMeshComponent* GetWeaponMesh() const{return WeaponMesh;}

	//初始化拥有者
	void SetOwningCharacter(AGenshinCharacterBase* InOwningCharacter);

	//只暴露Equip和UnEquip方法
	virtual void Equip();

	virtual void UnEquip();

	virtual void AddAbilities();
	
	virtual void RemoveAbilities();

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Weapon")
	virtual void ResetWeapon();
	

	/**
	 *这里是武器弹药的Get和Set方法如下,如果需要的话
	 *
	*UFUNCTION(BlueprintCallable, Category = "GASShooter|GSWeapon")
	virtual int32 GetPrimaryClipAmmo() const;
	 * 
	 * @return 
	 */

	//单例TargetActor
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Targeting")
	AGenshinAbilityTargetActor_LineTrace* GetLineTraceTargetActor();

	//reload
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Weapon")
	virtual void ReloadBullet(bool bPrimary);
	
	//主要子弹数量
	UPROPERTY(EditAnywhere, Category = "AbilitySystem|Weapon")
	int32 MaxPrimaryBulletCount;
	
	//主要子弹数量
	UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem|Weapon")
	int32 PrimaryBulletCount;

	//次要子弹数量
	UPROPERTY(EditAnywhere, Category = "AbilitySystem|Weapon")
	int32 MaxSecondaryBulletCount;
	
	//次要子弹数量
	UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem|Weapon")
	int32 SecondaryBulletCount;

protected:
	//AbilitySystem
	UPROPERTY(BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UGenshinAbilitySystemComponent> AbilitySystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RootComponent")
	TObjectPtr<USceneComponent> RootSceneComponent;
	
	//武器的Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem|WeaponMesh")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	//拥有者
	UPROPERTY(BlueprintReadOnly, Category = "AbilitySystem|Weapon")
	TObjectPtr<AGenshinCharacterBase> OwningCharacter;

	//使用的TargetDataActor
	UPROPERTY()
	TObjectPtr<AGenshinAbilityTargetActor_LineTrace> LineTraceTargetActor;

	//武器的Mesh相对位置
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AbilitySystem|WeaponMesh")
	FTransform WeaponMeshRelativeTransform;

	//给予Owner的技能
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AbilitySystem|Weapon")
	TArray<TSubclassOf<UGenshinAbilityBase>> Abilities;

	//AbilitySpecHandle,用于保存技能添加后的Handle,以便移除
	UPROPERTY(BlueprintReadOnly, Category = "AbilitySystem|Weapon")
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	//默认的射击模式
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AbilitySystem|Weapon")
	FGameplayTag DefaultFireMode;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	
	

};
