// Fill out your copyright notice in the Description page of Project Settings.

#include "test3.h"
#include "ramp.h"


#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel2
#define COLLISION_ALLIE ECollisionChannel::ECC_GameTraceChannel3
#define COLLISION_HAZARD ECollisionChannel::ECC_GameTraceChannel4

// Sets default values
Aramp::Aramp(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CoiComp"));
	CollisionComp->OnComponentHit.AddDynamic(this, &Aramp::OnHit);

	CollisionComp->BodyInstance.SetCollisionProfileName("allie");
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);

	CollisionComp->SetCollisionObjectType(COLLISION_ALLIE);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ENEMY, ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ALLIE, ECollisionResponse::ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_HAZARD, ECollisionResponse::ECR_Block);

	RootComponent = CollisionComp;

	rampMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("rampMesh"));
	rampMesh->AttachTo(RootComponent);


}

// Called when the game starts or when spawned
void Aramp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aramp::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void Aramp::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}