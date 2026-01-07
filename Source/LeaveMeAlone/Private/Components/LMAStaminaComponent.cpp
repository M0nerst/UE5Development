// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Components/LMAStaminaComponent.h"

// Sets default values for this component's properties
ULMAStaminaComponent::ULMAStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULMAStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	Stamina = MaxStamina;
	
}


// Called every frame
void ULMAStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

