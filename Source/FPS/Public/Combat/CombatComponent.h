// Copyright Gallucci Nahuel.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


class AWeapon;
class UWeaponData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPS_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UCombatComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//cycle to the next weapon in the inventory
	void Initiate_CycleWeapon();
	
	void Initiate_FireWeapon_Pressed();
	
	void Initiate_FireWeapon_Released();
	
	void Initiate_ReloadWeapon();
	
	void Initiate_Aim_Pressed();
	
	void Initiate_Aim_Released();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = "FPS|Weapon")
	TObjectPtr<UWeaponData> WeaponData;
	
	void Equip(AWeapon* Weapon);
	
	void SpawnInventory();
	
	void DestroyInventory();
	
	UPROPERTY(BlueprintReadOnly, replicated)
	bool bAiming;
	
	UFUNCTION(Server, Reliable)
	void Server_Aim(bool bPressed);
	
	void Local_Aim(bool bPressed);
	
	AWeapon* GetCurrentWeapon() const { return CurrentWeapon; }
	
protected:
	
		UPROPERTY(Transient, BlueprintReadOnly ,ReplicatedUsing= OnRep_CurrentWeapon)
    	TObjectPtr<AWeapon> CurrentWeapon;
	
private:
	
	UFUNCTION()
	void OnRep_CurrentWeapon(AWeapon* LastWeapon);
	
	UPROPERTY(Transient, Replicated)
	TArray<AWeapon*> Inventory;
	
	UPROPERTY(EditAnywhere, Category = "FPS|Weapon")
	TArray<TSubclassOf<AWeapon>> DefaultWeaponClasses;
	
	AWeapon* SpawnWeapon(TSubclassOf<AWeapon> WeaponClass) const;
	

};
