// Copyright Gallucci Nahuel.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


UCLASS()
class FPS_API AWeapon : public AActor
{
	GENERATED_BODY()

public:

	AWeapon();
	virtual void OnRep_Instigator() override;
	
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	
	USkeletalMeshComponent* GetMesh3P() const { return Mesh3P; }
	
	void AttachToOwningPawn() const;

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPS|WeaponType")
	FGameplayTag WeaponType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "FPS|Aiming")
	float AimFOV;

private:
	
	//weapon mesh: 1st person view
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;
	
	//weapon mesh: 3rd person view
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh3P;
	
	void SetMeshVisibilities(APawn* OwningPawn) const;
	
};

