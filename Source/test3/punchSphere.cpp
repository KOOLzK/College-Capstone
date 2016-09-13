// Fill out your copyright notice in the Description page of Project Settings.

#include "test3.h"
#include "punchSphere.h"
#include "dummy.h"
#include "test3Character.h"

#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel2
#define COLLISION_ALLIE ECollisionChannel::ECC_GameTraceChannel3

// Sets default values
ApunchSphere::ApunchSphere(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("CoiComp2"));
	CollisionComp->OnComponentHit.AddDynamic(this, &ApunchSphere::OnHit);

	CollisionComp->BodyInstance.SetCollisionProfileName("allie");
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);

	CollisionComp->SetCollisionObjectType(COLLISION_ALLIE);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ENEMY, ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ALLIE, ECollisionResponse::ECR_Ignore);

	RootComponent = CollisionComp;

}

// Called when the game starts or when spawned
void ApunchSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ApunchSphere::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//Atest3Character::GetActorLocation();
	//FVector ActorLocation = GetActorLocation();
	//FVector CharacterLocation;// = Atest3Character::getMyLocation();//Atest3Character::GetActorLocation();
	// Move it slightly  
	//ActorLocation = CharacterLocation;
	// Set the location- this will blindly place the actor at the given location  
	//SetActorLocation(ActorLocation, false);
}
void ApunchSphere::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(Adummy::StaticClass())) {
		if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}
	}
	/*else if (OtherActor->IsA(Atest3Character::StaticClass())) {
		if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
			SetActorLocation(OtherActor->GetActorLocation(), false);
		}
	}*/
}

void ApunchSphere::setMyLocation(FVector l)
{
	SetActorLocation(l, false);
}