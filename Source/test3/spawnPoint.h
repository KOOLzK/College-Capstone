// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "spawnPoint.generated.h"

UCLASS()
class TEST3_API AspawnPoint : public AActor
{
	GENERATED_UCLASS_BODY()
	
public:	
	// Sets default values for this actor's properties
	//AspawnPoint();

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly)
	class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAssess = "true"))
	UStaticMeshComponent* spawnPointMesh;

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

	/*where the player is*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	FVector attackLocation;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	float health;

	float quarterHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	float FullHealth;

	float HealthBarSize;

	bool beingAttacked;
	
};
