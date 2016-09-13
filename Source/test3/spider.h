// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "spider.generated.h"

UCLASS()
class TEST3_API Aspider : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Aspider();
	//Aspider(FVector spawnPosition);

	/*enemy goes to player*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool attack;

	/*enemy plays attack animation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool attacking;

	/*the enemy has attacked*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool attacked;

	/*enemy is being pushed back, trun out ai and apple launch*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool movement;

	float soundDelay;

	float playerSoundDelay;

	/*the player is attacking*/
	bool beingAttacked;

	bool beingPushedAttacked;

	/*where the player is*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	FVector attackLocation;

	/*the drection the player is attacking in*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	FVector attackedFrom;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	float DotProduct;

	float health;
	
};
