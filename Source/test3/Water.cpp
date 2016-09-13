// Fill out your copyright notice in the Description page of Project Settings.

#include "test3.h"
#include "Water.h"


#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel2
#define COLLISION_ALLIE ECollisionChannel::ECC_GameTraceChannel3
#define COLLISION_HAZARD ECollisionChannel::ECC_GameTraceChannel4

// Sets default values
AWater::AWater(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CoiComp"));
	CollisionComp->OnComponentHit.AddDynamic(this, &AWater::OnHit);

	CollisionComp->BodyInstance.SetCollisionProfileName("hazard");
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);

	CollisionComp->SetCollisionObjectType(COLLISION_HAZARD);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ENEMY, ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ALLIE, ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_HAZARD, ECollisionResponse::ECR_Ignore);

	RootComponent = CollisionComp;

	WaterMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("WaterMesh"));
	WaterMesh->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AWater::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWater::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWater::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

