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
	
	//weapon mesh: 1st person view
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;
	
	//weapon mesh: 3rd person view
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> Mesh3P;
	
	void AttachToOwningPawn() const;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPS|WeaponType")
	FGameplayTag WeaponType;
	
	void WeaponTrace(FHitResult& OutHit, float TraceLength);
	
	void Local_Fire(const FVector& ImpactPoint, const FVector& ImpactNormal, TEnumAsByte<EPhysicalSurface> ImpactSurfaceType, bool bIsFirstPerson);
	
protected:
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void FireEffects(const FVector& ImpactPoint, const FVector& ImpactNormal, EPhysicalSurface ImpactSurfaceType, bool bIsFirstPerson);	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "FPS|Aiming")
	float AimFOV;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "FPS|Aiming")
	float TraceRadius = 5.f;


private:
	

	
	void SetMeshVisibilities(APawn* OwningPawn) const;
	
};

