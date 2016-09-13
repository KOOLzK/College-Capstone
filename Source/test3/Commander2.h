// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Commander2.generated.h"

UCLASS()
class TEST3_API ACommander2 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACommander2();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	TArray<AActor*> enemys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	TArray<AActor*> spawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	AActor* player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	AActor* startObstacle;

	/*gets and puts an enemy in to an array*/
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void addSpawnPoint(AActor* c);

	/*gets and puts an enemy in to an array*/
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void addEnemy(AActor* c);

	/*plays when a punch hits*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* BitSound;

	/*plays when a dieds*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* deathSound;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	float spawnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	float spawnDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool resetSpawn;
	
};
