// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAStaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, NewStamina);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULMAStaminaComponent();

	UFUNCTION(BlueprintCallable)
	float GetStamina() const { return Stamina; }

	UPROPERTY(BlueprintAssignable)
	FOnStaminaChanged OnStaminaChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxStamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float StaminaDrainRate = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float StaminaRecoveryRate = 10.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:
	float Stamina = 0.0f;
};
