// Copyright Gallucci Nahuel.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/PlayerInterface.h"
#include "ShooterTypes/ShooterTypes.h"
#include "ShooterCharacter.generated.h"

struct FGameplayTag;
class UInputAction;
class UCombatComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class FPS_API AShooterCharacter : public ACharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:

	AShooterCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/* player interface */
	
	virtual FName GetWeaponAttachPoint_Implementation(const FGameplayTag& WeaponType) const override;
	
	virtual USkeletalMeshComponent* GetMesh1P_Implementation() const override;
	
	virtual USkeletalMeshComponent* GetMesh3P_Implementation() const override;
	
	/* player interface */	
	
	virtual void BeginPlay() override;
                          	
	virtual void PossessedBy(AController* NewController) override;
                          	
	virtual void BeginDestroy() override;
	
	void CalculateFABRIKSocketTransform();
	
	void CalculateTurnInPlace(float DeltaTime);
	
	void TurnInPlace(float DeltaTime);
	
	float InterpAO_Yaw;
	
	FRotator StartingAimRotation;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|TurnInPlace")
	float AO_Yaw;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|Strafing")
	float MovementOffsetYaw;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|TurnInPlace")
	ETurningInPlace TurningStatus;

	UPROPERTY(BlueprintReadOnly, Category = "FPS|FABRIK")
	FTransform FABRIK_SocketTransform;
	
protected:
	
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "FPS|Combat")
	TObjectPtr<UCombatComponent> CombatComponent;
	
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "FPS|Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "FPS|Combat")
	void OnAim(bool bPressed);
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "FPS|Camera")
	float DefaultFOV;
	
	UFUNCTION(BlueprintCallable, Category = "FPS|Combat")
	FRotator GetFixedAimRotation() const;

private:
	
	void Input_CycleWeapon();
	void Input_ReloadWeapon();
	void Input_FireWeapon_Pressed();
	void Input_FireWeapon_Released();	
	void Input_Aim_Pressed();
	void Input_Aim_Released();
	
	//1st person view (arms)
	UPROPERTY(visibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;
	
	UPROPERTY(visibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(EditAnywhere, Category = "FPS|Input")
	TObjectPtr<UInputAction> CycleWeaponAction;
	
	UPROPERTY(EditAnywhere, Category = "FPS|Input")
	TObjectPtr<UInputAction> FireWeaponAction;
	
	UPROPERTY(EditAnywhere, Category = "FPS|Input")
	TObjectPtr<UInputAction> ReloadWeaponAction;
	
	UPROPERTY(EditAnywhere, Category = "FPS|Input")
	TObjectPtr<UInputAction> AimAction;
	
};
