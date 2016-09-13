// Fill out your copyright notice in the Description page of Project Settings.

#include "test3.h"
#include "spider.h"


// Sets default values
Aspider::Aspider()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

/*Aspider::Aspider(FVector spawnPosition)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorLocation(spawnPosition);
}*/

// Called when the game starts or when spawned
void Aspider::BeginPlay()
{
	Super::BeginPlay();
	health = 20;
	soundDelay = 0;
}

// Called every frame
void Aspider::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	float c = FVector::Dist(GetActorLocation(), attackLocation);
	if (c < 100) {
		attacking = true;
	}
	else
	{
		attacking = false;
	}

	//if the player is attacking check to see if they hit this enemy
	if (beingAttacked) {
		//float c = FVector::Dist(GetActorLocation(), attackLocation);
		if (c < 100) {
			//movement = true;////////////
			//this should get where the enemy is compared to the player
			//1 is in front, 0 is to the sides, -1 is behind the player
			//:note* this doesn't work
			FVector one = GetActorForwardVector();
			one.Normalize();
			FVector two = attackedFrom;
			two.Normalize();
			DotProduct = FVector::DotProduct(one, two);

			//:note* maybe make only work when enemy is in first circle
			if (DotProduct < -0.5f) {
				movement = true;
				health--;

				//UGameplayStatics::PlaySoundAtLocation(this, PunchSound, GetActorLocation());

			}
		}
		else
		{
			//if the player didn't hit don't push this enemy back
			movement = false;
		}
	}
	else
	{
		//if this enemy gets too far away double check and make sure if not being pushed
		if (c > 300) {
			movement = false;
		}
	}

	if (beingPushedAttacked) {
		//float c = FVector::Dist(GetActorLocation(), attackLocation);
		if (c < 200) {
			movement = true;
		}
		else
		{
			//if the player didn't hit don't push this enemy back
			movement = false;
		}
	}
	else
	{
		//if this enemy gets too far away double check and make sure if not being pushed
		if (c > 300) {
			movement = false;
		}
	}

}

// Called to bind functionality to input
void Aspider::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

