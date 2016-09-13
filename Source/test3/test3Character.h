// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "test3Character.generated.h"


class UInputComponent;

UCLASS(config=Game)
class Atest3Character : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, Category = Default)
	class USkeletalMeshComponent* SkeletalMesh;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterial* Material100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterial* Material75;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterial* Material50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterial* Material25;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* PushPowerBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterial* MaterialCharging;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterial* MaterialCharged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoomComponent;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;
public:
	//Atest3Character();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class Atest3Projectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/*dodge in the prioity in the animation systume*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool Dodge;

	/*what dodge to use*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool DodgeForwardsMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool DodgeBackwardsMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool DodgeLeftMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool DodgeRightMove;

	/*used to set dodge animations*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector relativeForward;

	/*play attack animation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool rightHook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool leftHook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool pushAttack;

	/*attack animation is at its fullest check to see if it hit an enemy*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool rightHookHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool leftHookHit;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector attack;

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	FVector getMyLocation();

	UFUNCTION()
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	

	bool pushAttacking;

	float health;

	float quarterHealth;

	float FullHealth;

	float HealthBarSize;

	int pushPower;

	float FullPushPower;

	float PushPowerBarSize;

	/*enemy kill the player*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool dead;

	/*water kill the player*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool drowned;

protected:
	
	/** Fires a projectile. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual void Tick(float DeltaSeconds) override;

	// virtual void overlap
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	/*move in these directions*/
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void dodgeForwards(bool d);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void dodgeBackwards(bool d);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void dodgeLeft(bool d);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void dodgeRight(bool d);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void testFire(bool f);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void pushAttacked();


};

