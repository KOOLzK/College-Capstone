// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "punchSphere.generated.h"

UCLASS()
class TEST3_API ApunchSphere : public AActor
{
	GENERATED_UCLASS_BODY()
	
public:	
	// Sets default values for this actor's properties
	//ApunchSphere();

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly)
	class USphereComponent* CollisionComp;//Sphere

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void setMyLocation(FVector l);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
