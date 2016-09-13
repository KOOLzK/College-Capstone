// Fill out your copyright notice in the Description page of Project Settings.

#include "test3.h"
#include "spawnPoint.h"


#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel2
#define COLLISION_ALLIE ECollisionChannel::ECC_GameTraceChannel3
#define COLLISION_HAZARD ECollisionChannel::ECC_GameTraceChannel4


// Sets default values
AspawnPoint::AspawnPoint(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CoiComp"));
	//CollisionComp->OnComponentHit.AddDynamic(this, &AspawnPoint::OnHit);

	CollisionComp->BodyInstance.SetCollisionProfileName("enemy");
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);

	CollisionComp->SetCollisionObjectType(COLLISION_ENEMY);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ENEMY, ECollisionResponse::ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ALLIE, ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_HAZARD, ECollisionResponse::ECR_Block);

	RootComponent = CollisionComp;

	spawnPointMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("spawnPointMesh"));
	spawnPointMesh->AttachTo(RootComponent);

	HealthBar = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("HealthBarMesh"));
	HealthBar->AttachTo(RootComponent); //AttachParent = GetCapsuleComponent();
	HealthBar->RelativeLocation = FVector(0, 0, 100.0f);
	HealthBar->RelativeScale3D = FVector(0.1f, 1.0f, 0.1f);

	FullHealth = 1000;
	health = FullHealth;
	HealthBarSize = FullHealth / FullHealth;
	quarterHealth = FullHealth / 4;

}

// Called when the game starts or when spawned
void AspawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AspawnPoint::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	HealthBarSize = health / FullHealth;
	if (HealthBarSize > 0) {
		HealthBar->RelativeScale3D = FVector(0.1f, HealthBarSize, 0.1f);
		if (health > quarterHealth * 3) {
			HealthBar->SetMaterial(0, Material100);
		}
		else if (health > quarterHealth * 2)
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

	/*if (beingAttacked) {
		float c = FVector::Dist(GetActorLocation(), attackLocation);
		if (c < 200) {
			health--;
		}
	}
	if (health < 0) {
		Destroy();
	}*/

}

