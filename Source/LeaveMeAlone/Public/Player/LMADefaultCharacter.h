// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULMAHealthComponent;
class ULMAWeaponComponent;
class UAnimMontage;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALMADefaultCharacter();

	UFUNCTION()
	ULMAHealthComponent* GetHealthComponent() const { return HealthComponent; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	float GetStamina() const { return Stamina; };

	UFUNCTION(BlueprintCallable, Category = "Character")
	float GetSprinting() const { return IsSprinting; };

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULMAWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components|Stamina")
	float SprintSpeedMultiplier = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Components|Stamina")
	float MaxStamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Components|Stamina")
	float StaminaDrainRate = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Components|Stamina")
	float StaminaRecoveryRate = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Stamina")
	bool IsSprinting = false;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
	ULMAHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

	

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
		
	float YRotation = -75.0f; //Поворот камеры по оси Y
	float ArmLength = 1400.0f; //Длина "штатива"

	float MaxArmLength = 3000.0f;
	float MinArmLength = 800.0f;
	float ZoomSpeed = 100.0f;

	float FOV = 55.0f; //Поле зрения

	float DefaultWalkSpeed;
	float Stamina = 0.0f;
	bool CanSprint = true;
	void StartSprinting();
	void StopSprinting();
	void StaminaManager();

	void MoveForward(float Value); //движение по оси Х
	void MoveRight(float Value); //движение по оси Y
	void MoveCameraZoom(float Value); //приближение\отдаление камеры

	void OnDeath(); //реакция на смерть персонажа
	void RotationPlayerOnCursor();
	void OnHealthChanged(float NewHealth);
};
