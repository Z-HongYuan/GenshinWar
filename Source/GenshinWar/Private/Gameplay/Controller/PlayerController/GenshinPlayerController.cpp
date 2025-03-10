// Copyright 2025 鸿源z。保留所有权利。


#include "Gameplay/Controller/PlayerController/GenshinPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/GenshinPlayerCharacter.h"
#include "Input/GenshinEnhancedInputComponent.h"

AGenshinPlayerController::AGenshinPlayerController()
{
	
}

void AGenshinPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultContext,0);
	}
	SetInputMode(FInputModeGameOnly());
}

void AGenshinPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UGenshinEnhancedInputComponent* GenshinEnhancedInput = CastChecked<UGenshinEnhancedInputComponent>(InputComponent))
	{
		GenshinEnhancedInput->BindAction(
			MoveAction, 
			ETriggerEvent::Triggered,
			this,
			&AGenshinPlayerController::HandleMove
			);
		
		GenshinEnhancedInput->BindAction(
			LookAction, 
			ETriggerEvent::Triggered,
			this,
			&AGenshinPlayerController::HandleLook
			);
		
		GenshinEnhancedInput->BindAbilityAction(
			InputDataAsset,
			this,
			&ThisClass::AbilityInputTagPressed,
			&ThisClass::AbilityInputTagReleased,
			&ThisClass::AbilityInputTagHeld);
	}
}

void AGenshinPlayerController::HandleMove(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn())
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// 从控制旋转中提取出Forward和Right方向
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGenshinPlayerController::HandleLook(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	AddPitchInput(LookVector.Y * UpDownRate);
	AddYawInput(LookVector.X * LeftRightRate);
}

void AGenshinPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// GetASC()->
}

void AGenshinPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC()==nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void AGenshinPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC()==nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

UGenshinAbilitySystemComponent* AGenshinPlayerController::GetASC()
{
	if (GenshinAbilitySystemComponent==nullptr)
	{
		GenshinAbilitySystemComponent=Cast<UGenshinAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return GenshinAbilitySystemComponent;
}
