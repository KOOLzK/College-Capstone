// Fill out your copyright notice in the Description page of Project Settings.

#include "test3.h"
#include "bot.h"
#include "Commander.h"
#include "Water.h"
/*#include <iostream>
#include <sstream>
using namespace std;*/
/*#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel2
#define COLLISION_ALLIE ECollisionChannel::ECC_GameTraceChannel3
#define COLLISION_HAZARD ECollisionChannel::ECC_GameTraceChannel4*/

// Sets default values
Abot::Abot()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthBar = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("HealthBarMesh"));
	HealthBar->AttachTo(GetCapsuleComponent()); //AttachParent = GetCapsuleComponent();
	HealthBar->RelativeLocation = FVector(0, 0, 100.0f);
	HealthBar->RelativeScale3D = FVector(0.1f, 1.0f, 0.1f);

	//FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();

	/*TSubclassOf<ACommander> ClassToFind;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);

	if (FoundActors.Num() > 0) {
		if (FoundActors[0]->IsA(ACommander::StaticClass())) {
			ACommander* b = Cast<ACommander>(FoundActors[0]);
			b->addEnemy(this);
		}
	}*/

	/*GetCapsuleComponent()->BodyInstance.SetCollisionProfileName("enemy");
	GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);

	GetCapsuleComponent()->SetCollisionObjectType(COLLISION_ENEMY);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_ENEMY, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_ALLIE, ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_HAZARD, ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &Abot::OnHit);*/
}

// Called when the game starts or when spawned
void Abot::BeginPlay()
{
	Super::BeginPlay();
	movement = false;
	attacking = false;

	FullHealth = 30;
	health = FullHealth;
	HealthBarSize = FullHealth / FullHealth;
	quarterHealth = FullHealth / 4;

	hasRetreatedOnce = false;
	dance = false;
	dead = false;
	destroy = false;
	deathTimer = 100;
	soundDelay = 0;
	playerSoundDelay = 0;
	firstAttack = true;

	int temp = rand() % 10;
	if (temp < 5) {
		moveAttack = true;
	}
	else 
	{
		moveAttack = false;
	}

	//ACommander* a = Cast<ACommander>(AIControl);
	//a->addEnemy(this);
}

// Called every frame
void Abot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HealthBarSize = health / FullHealth;
	if (HealthBarSize > 0) {
		HealthBar->RelativeScale3D = FVector(0.1f, HealthBarSize, 0.1f);
		if (health > quarterHealth * 3) {
			HealthBar->SetMaterial(0, Material100);
		}
		else if(health > quarterHealth * 2)
		{
			HealthBar->SetMaterial(0, Material75);
		}
		else if (health > quarterHealth)
		{
			HealthBar->SetMaterial(0, Material50);
		}
		else //if (health < 25)
		{
			HealthBar->SetMaterial(0, Material25);
		}
	}

	if (health < 0) {
		dead = true;
	}
	if (destroy) {
		deathTimer--;
	}
	if (deathTimer < 0) {
		Destroy();
	}
	/*if (move) {
	AddMovementInput(GetActorForwardVector(), 1.0f);
	}*/

	//if (movement) {
	//GetCapsuleComponent()->AddImpulseAtLocation(FVector(0, 0, 50), GetActorLocation());
	//SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 50));
	//Jump();
	//}
	//movement = !movement;
	//finds the distense between this enemy and the player
	float c = FVector::Dist(GetActorLocation(), attackLocation);
	if (c < 100) {
		attacking = true;
		/*if (!attacked) {
			if (attacking) {
				if (firstAttack) {
					if (moveAttack) {
						moveAttack = true;
						firstAttack = false;
					}
				}
				else 
				{
					moveAttack = false;
				}
			}
		}*/
		
	}
	else
	{
		attacking = false;
		//firstAttack = true;
		//moveAttack = true;
	}

	//if the player is attacking check to see if they hit this enemy
	if (beingAttacked) {
		//float c = FVector::Dist(GetActorLocation(), attackLocation);
		if (c < 100) {
			//movement = true;////////////
			//this should get where the enemy is compared to the player
			//1 is in front, 0 is to the sides, -1 is behind the player
			//:note* this doesn't work
			FVector one =GetActorForwardVector();
			one.Normalize();
			FVector two = attackedFrom;
			two.Normalize();
			DotProduct = FVector::DotProduct(one, two);
			/*UE_LOG(LogTemp, Warning, TEXT("GetActorLocation().X %f"));
			UE_LOG(LogTemp, Warning, TEXT("GetActorLocation().Y %f"));
			UE_LOG(LogTemp, Warning, TEXT("GetActorLocation().Z %f"));

			UE_LOG(LogTemp, Warning, TEXT("attackedFrom.X %f"));
			UE_LOG(LogTemp, Warning, TEXT("attackedFrom.Y %f"));
			UE_LOG(LogTemp, Warning, TEXT("attackedFrom.Z %f"));

			stringstream ss(stringstream::in | stringstream::out);
			ss << temp;
			std::string f(ss.str());
			std::string f = "%f",temp;
			UE_LOG(LogTemp, Warning, TEXT(f.c_str));*/
			//:note* maybe make only work when enemy is in first circle
			if (DotProduct < -0.5f) {
				movement = true;
				health--;

				/*if ((soundDelay / 5) > PunchSound->GetDuration()) {
					UGameplayStatics::PlaySoundAtLocation(this, PunchSound, GetActorLocation());
					playerSoundDelay = 0;
				}
				else
				{
					playerSoundDelay++;
				}*/
				
				//PunchSound->GetDuration();PunchSound->Duration

				//if (PunchSound->CurrentPlayCount < 0) {
					UGameplayStatics::PlaySoundAtLocation(this, PunchSound, GetActorLocation());
				//}
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
	/*if (GetActorLocation().Z < 4400) {//4300 should work
		health = 0;
	}*/
}

// Called to bind functionality to input
void Abot::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

/*void Abot::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(AWater::StaticClass())) {
		health = 0;
	}
}*/
