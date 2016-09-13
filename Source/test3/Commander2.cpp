// Fill out your copyright notice in the Description page of Project Settings.

#include "test3.h"
#include "Commander2.h"
#include "test3Character.h"
#include "spawnPoint.h"
#include "spider.h"
#include "obstacle.h"


// Sets default values
ACommander2::ACommander2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACommander2::BeginPlay()
{
	Super::BeginPlay();

	spawnRate = 1000;
	spawnDelay = spawnRate;
	resetSpawn = false;
	
}

// Called every frame
void ACommander2::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (enemys.Num() == 0) {
		Aobstacle* o = Cast<Aobstacle>(startObstacle);
		o->damageable = true;
		Destroy();
	}

	Atest3Character* p = Cast<Atest3Character>(player);
	for (int i = 0; i < spawnPoints.Num(); i++)
	{
		AspawnPoint* s = Cast<AspawnPoint>(spawnPoints[i]);
		//s->Tick(DeltaTime);
		s->attackLocation = p->GetActorLocation();
		if (p->leftHook) {
			float c = FVector::Dist(s->GetActorLocation(), p->GetActorLocation());
			if (c < 100) {
				s->health--;
				//s->beingAttacked = true;
			}
			//s->health--;
			//
		}
		/*else
		{
			s->beingAttacked = false;
		}*/
		if (s->health < 0) {
			s->Destroy();
			spawnPoints.RemoveAt(i);
		}
		else
		{
			/*if (spawnDelay < 0) {
				//resetSpawn = true;
				spawnDelay = spawnRate;
				enemys.Push(GetWorld()->SpawnActor<Aspider>());//////not Atest3Character
				enemys.Last()->SetActorLocation(s->GetActorLocation());
			}
			else
			{
				spawnDelay--;
			}*/
		}
	}

	/*if (resetSpawn) {
		spawnDelay = spawnRate;
		resetSpawn = false;
	}*/

	for (int i = 0; i < enemys.Num(); i++)
	{
		Aspider* a = Cast<Aspider>(enemys[i]);

		if (a->health < 0) {
			//UGameplayStatics::PlaySoundAtLocation(this, deathSound, GetActorLocation());
			if (spawnPoints.Num() > 0) {
				a->health = 20;
				int temp = spawnPoints.Num() - 1;
				int temp2 = rand() % temp;
				a->SetActorLocation(spawnPoints[temp2]->GetActorLocation());
			}
			else
			{
				a->Destroy();
				enemys.RemoveAt(i);
			}
			
		}

		if (a->attacked && a->attacking) {
			p->health -= 0.1f;
			/*:note* this is running every frame so I thought I would have to devid be 30 assuming PunchSound->Duration
			is in seconds, but the delay was too long, 5 is a guess but it seems to work*/
			//makes the sound effect not play until the last one is done
			/*if ((a->soundDelay / 5) > BitSound->Duration) {
				UGameplayStatics::PlaySoundAtLocation(this, BitSound, GetActorLocation());
				a->soundDelay = 0;
			}
			else
			{
				a->soundDelay++;
			}*/
		}

		a->attackLocation = p->GetActorLocation();
		if (p->leftHook) {
			a->beingAttacked = true;
		}
		else {
			a->beingAttacked = false;
		}

		if (p->pushAttacking) {
			a->beingPushedAttacked = true;
		}
		else {
			a->beingPushedAttacked = false;
		}
		a->attackedFrom = p->GetActorForwardVector();
	}

}

// Called to bind functionality to input
void ACommander2::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ACommander2::addSpawnPoint(AActor* c) {
	spawnPoints.Push(c);
}

void ACommander2::addEnemy(AActor* c) {
	enemys.Push(c);
}
