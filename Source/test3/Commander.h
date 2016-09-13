// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Commander.generated.h"

UCLASS()
class TEST3_API ACommander : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACommander();

	UPROPERTY()
	TArray<AActor*> enemys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	AActor* player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	AActor* startObstacle;

	/*gets and puts an enemy in to an array*/
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void addEnemy(AActor* c);

	/*plays when a punch hits*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* PunchSound;

	/*player location*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	FVector playerLocation;

	/*the enemys place in the formation*/
	FVector enemyLocation;

	float d;

	/*how long the game his bin playing*/
	double t;

	double startDelay;

	bool start;

	bool triggerPlayerHealthRefull1;
	bool triggerPlayerHealthRefull2;

	/*number of circles of enemys around the play*/
	/*most be 1 or more*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	uint8 numberOfCircles;

	/*should probably be more then 100*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	float distanceBetweenCircles;

	/*the player is attacking*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool playerAttacking;

	/*where the play is facing*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	FVector attackDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool won;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;



};
