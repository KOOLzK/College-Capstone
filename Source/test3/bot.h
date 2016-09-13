// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "bot.generated.h"

UCLASS()
class TEST3_API Abot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Abot();

	/*TArray<AActor*> FoundActors;
	UPROPERTY(EditAnywhere, Category = AI)
	class ACharacter* AIControl;*/

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

	/*enemy goes to player*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool attack;

	/*enemy plays attack animation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool attacking;

	/*the enemy has attacked*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool attacked;

	/*enemy is moving to position*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool move;

	/*enemy is being pushed back, trun out ai and apple launch*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool movement;

	/*the player is attacking*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool beingAttacked;

	bool beingPushedAttacked;

	/*player dead enemy should dance*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool dance;

	/*the first attack animation enemy does is different*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool moveAttack;

	/*the drection the player is attacking in*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	FVector attackedFrom;

	/*where the player is*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	FVector attackLocation;

	/*where the enemy should go to get to they place in formation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	FVector moveLocation;

	/*plays when a punch hits*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* PunchSound;

	/*player kill the enemy*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool dead;

	/*delete enemy*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool destroy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	float DotProduct;

	float soundDelay;

	float playerSoundDelay;

	float deathTimer;

	float health;

	float quarterHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	float FullHealth;

	float HealthBarSize;

	bool hasRetreatedOnce;

	bool firstAttack;

	/*UFUNCTION()
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);*/

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;



};