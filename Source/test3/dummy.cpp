// Fill out your copyright notice in the Description page of Project Settings.

#include "test3.h"
#include "dummy.h"
#include "test3Character.h"
#include "test3Projectile.h"

#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel2
#define COLLISION_ALLIE ECollisionChannel::ECC_GameTraceChannel3


// Sets default values
Adummy::Adummy(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CoiComp"));
	CollisionComp->OnComponentHit.AddDynamic(this, &Adummy::OnHit);

	CollisionComp->BodyInstance.SetCollisionProfileName("enemy");
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);

	CollisionComp->SetCollisionObjectType(COLLISION_ENEMY);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ENEMY, ECollisionResponse::ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ALLIE, ECollisionResponse::ECR_Block);

	RootComponent = CollisionComp;

	DummyMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("DummyMesh"));
	DummyMesh->AttachTo(RootComponent);

	health = 10;
}

// Called when the game starts or when spawned
void Adummy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Adummy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (health <= 0) {
		Destroy();
	}

}

void Adummy::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(Atest3Projectile::StaticClass())) {
		health--;
		if (health <= 0) {
			Destroy();
		}
	}
	if (OtherActor->IsA(Atest3Character::StaticClass())) {
		/*health--;
		if (health <= 0) {
			Destroy();
		}*/
	}
}
