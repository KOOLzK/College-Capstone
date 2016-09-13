// Fill out your copyright notice in the Description page of Project Settings.

#include "test3.h"
//#include "Animation/AnimInstance.h"
#include "Commander.h"
#include "bot.h"
#include "test3Character.h"
#include "obstacle.h"


// Sets default values
ACommander::ACommander()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	numberOfCircles = 2;
	distanceBetweenCircles = 400.0f;
	won = false;

	startDelay = 400;
	start = false;
	triggerPlayerHealthRefull1 = true;
	triggerPlayerHealthRefull2 = true;
}

// Called when the game starts or when spawned
void ACommander::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACommander::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//I feel like I might need time
	t += DeltaTime;

	//what circle you are on
	int circleNumber = 1;

	//how many enemys in the completed circles
	int enemysGoneThrough = 0;

	//devid circle by this to get enemy position :note* I think
	//:note* maybe call this iterator of current circle
	int positionInCircle = 1;
	int leftOversPositionInCircle = 1;

	//int leftOvers = (enemys.Num() - ((1 + 1) * 2));

	//if there are no more enemys then the player wins
	if (enemys.Num() == 0) {
		won = true;
	}

	Atest3Character* p = Cast<Atest3Character>(player);

	if (startObstacle != NULL) {
		Aobstacle* o = Cast<Aobstacle>(startObstacle);
		if (o->damageable) {
			if (o->health > 0) {
				if (p->leftHook) {
					float oc = FVector::Dist(p->GetActorLocation(), o->GetActorLocation());
					if (oc < 200) {
						o->health--;
					}
				}
			}
			else
			{
				if (triggerPlayerHealthRefull1) {
					startObstacle->Destroy();
					p->health = p->FullHealth;
					triggerPlayerHealthRefull1 = false;
				}
				/*if (startDelay > 0) {
					startDelay--;
				}
				else
				{
					start = true;
				}*/
			}
		}
	}
	if (!triggerPlayerHealthRefull1) {
		if (startDelay > 0) {
			startDelay--;
		}
		else
		{
			start = true;
		}
	}
	/*else
	{
		if (startDelay > 0) {
			startDelay--;
		}
		else
		{
			start = true;
		}
	}*/

	/*p->HealthBarSize = p->health / p->FullHealth;
	if (p->HealthBarSize > 0) {
		p->HealthBar->RelativeScale3D = FVector(0.1f, 0.1f, p->HealthBarSize);
	}*/
	if (start) {
		for (int i = 0; i < enemys.Num(); i++)
		{


			//grabs an enemy
			Abot* a = Cast<Abot>(enemys[i]);

			/*if (a->GetActorLocation().Z < 4500) {
				a->health = 0;
			}*/

			/*if (a->health < 0) {
				a->Destroy();
				enemys.RemoveAt(i);
			}*/

			if (a->destroy) {
				//a->Destroy();
				enemys.RemoveAt(i);
			}

			if (!a->hasRetreatedOnce && a->health < a->FullHealth / 2) {
				a->attack = false;
				a->hasRetreatedOnce = true;
				addEnemy(enemys[i]);
				enemys.RemoveAt(i);
			}

			if (a->attacked && a->attacking) {
				p->health--;
				/*:note* this is running every frame so I thought I would have to devid be 30 assuming PunchSound->Duration
				is in seconds, but the delay was too long, 5 is a guess but it seems to work*/
				//makes the sound effect not play until the last one is done
				if ((a->soundDelay / 5) > a->PunchSound->Duration) {
					UGameplayStatics::PlaySoundAtLocation(this, PunchSound, GetActorLocation());
					a->soundDelay = 0;
				}
				else
				{
					a->soundDelay++;
				}
			}

			playerLocation = p->GetActorLocation();
			a->attackLocation = playerLocation;
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
			a->attackedFrom = p->GetActorForwardVector();// attackDirection;

			//if this circle is full
			if (enemys.Num() >= ((circleNumber + 1) * 2) + enemysGoneThrough) {// + enemysGoneThrough
				//goes throght each one of the circle
				if (positionInCircle <= ((circleNumber + 1) * 2)) {
					//how far a part each enemy should be in the circle
					double circleDiv = (2 * PI) / ((circleNumber + 1) * 2);

					//sets enemyLocation to the place in the circle enemy should be
					enemyLocation.X = playerLocation.X + (distanceBetweenCircles * circleNumber) * cos(circleDiv * positionInCircle);
					enemyLocation.Y = playerLocation.Y + (distanceBetweenCircles * circleNumber) * sin(circleDiv * positionInCircle);
					enemyLocation.Z = playerLocation.Z;

					//tell the enemy where it should go
					//checks to see if enemy has riched its place in the circle
					float c = FVector::Dist(a->GetActorLocation(), enemyLocation);
					//if so tell it to attack
					if (circleNumber == 1 && a->move && c < 50) {
						a->attack = true;
						//a->moveAttack = false;
						a->move = false;
					}
					//if not tell it to keep going to it 
					else
					{

						a->move = true;
					}

					if (c < 50) {

						a->move = false;
					}
					else
					{
						//a->moveAttack = true;
					}

					//checks to see if the player is dead
					if (p->dead) {
						//makes enemys go in their circles and dance because the player is dead
						a->moveLocation = enemyLocation;
						a->dance = true;
					}
					else
					{
						if (a->attack) {
							//tell the enemy to go to the player
							a->moveLocation = playerLocation;
						}
						else
						{
							//tell the enemy where it should go
							a->moveLocation = enemyLocation;
						}
					}
					//a->moveLocation = enemyLocation;
					positionInCircle++;
				}
				else
				{
					enemysGoneThrough += (circleNumber + 1) * 2;
					circleNumber++;
					positionInCircle = 1;
				}
			}
			else
			{
				//checks to see if the leftovers are in the frist circle
				int leftOvers = (enemys.Num() - enemysGoneThrough);
				if (leftOvers > 0)
				{
					leftOvers = (enemys.Num() - enemysGoneThrough);
				}
				else
				{
					leftOvers = enemys.Num();
				}
				//:note* change leftOversPositionInCircle to positionInCircle maybe now that I reset it
				//if this circle is not full
				//goes throght how ever many are in the circle
				if (leftOversPositionInCircle <= leftOvers) {
					//how far a part each enemy should be in the circle
					double circleDiv = (2 * PI) / leftOvers;

					//sets enemyLocation to the place in the circle enemy should be
					enemyLocation.X = playerLocation.X + (distanceBetweenCircles * circleNumber) * cos(circleDiv * leftOversPositionInCircle);
					enemyLocation.Y = playerLocation.Y + (distanceBetweenCircles * circleNumber) * sin(circleDiv * leftOversPositionInCircle);
					enemyLocation.Z = playerLocation.Z;

					//tell the enemy where it should go
					a->moveLocation = enemyLocation;
					leftOversPositionInCircle++;

					//checks to see if enemy has riched its place in the circle
					float c = FVector::Dist(a->GetActorLocation(), enemyLocation);
					//if so tell it to attack
					if (circleNumber == 1 && a->move && c < 50) {
						a->attack = true;
						a->move = false;
					}
					//if not tell it to keep going to it 
					else
					{
						a->move = true;
					}

					if (c < 50) {
						a->move = false;
					}
					//checks to see if the player is dead
					if (p->dead) {
						//makes enemys go in their circles and dance because the player is dead
						a->moveLocation = enemyLocation;
						a->dance = true;
					}
					else
					{
						if (a->attack) {
							//tell the enemy to go to the player
							a->moveLocation = playerLocation;
						}
						else
						{
							//tell the enemy where it should go
							a->moveLocation = enemyLocation;
						}
					}
				}
			}
			float c = FVector::Dist(a->GetActorLocation(), enemyLocation);
			if (c < 50) {
				a->move = false;
			}
		}
	}

	p->pushAttacking = false;
	//:note* when have time figer out the LOG/DebugMessage stuff
	/*#if UE_BUILD_DEBUG
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "debug msg");
	#endif*/
	//UE_LOG(LogTemp, Warning, TEXT("Your message"));
}

// Called to bind functionality to input
void ACommander::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ACommander::addEnemy(AActor* c) {
	enemys.Push(c);
}