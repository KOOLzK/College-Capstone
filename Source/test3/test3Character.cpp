// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "test3.h"
#include "test3Character.h"
#include "test3Projectile.h"
#include "punchSphere.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "dummy.h"
#include "bot.h"
#include "Water.h"


#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel2
#define COLLISION_ALLIE ECollisionChannel::ECC_GameTraceChannel3
#define COLLISION_HAZARD ECollisionChannel::ECC_GameTraceChannel4


DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// Atest3Character

Atest3Character::Atest3Character(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;


	CameraBoomComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoomComponent->AttachParent = GetCapsuleComponent();
	CameraBoomComponent->TargetArmLength = 350;
	CameraBoomComponent->bUsePawnControlRotation = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->AttachTo(CameraBoomComponent, USpringArmComponent::SocketName);
	FirstPersonCameraComponent->bUsePawnControlRotation = false;
	//FirstPersonCameraComponent->RelativeLocation = FVector(-350.f, 0, 90.f); // Position the camera
	//FirstPersonCameraComponent->bUsePawnControlRotation = true;

	//FirstPersonCameraComponent->SpawnActor

	GetCapsuleComponent()->BodyInstance.SetCollisionProfileName("allie");
	GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly, true);

	GetCapsuleComponent()->SetCollisionObjectType(COLLISION_ALLIE);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_ENEMY, ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_ALLIE, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_HAZARD, ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &Atest3Character::OnHit);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	/*Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;*/

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	//FP_Gun->AttachTo(Mesh1P, TEXT("GripPoint"), EAttachLocation::SnapToTargetIncludingScale, true);

	HealthBar = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("HealthBarMesh"));
	HealthBar->AttachTo(GetCapsuleComponent());
	HealthBar->RelativeLocation = FVector(-50.0f, 0, 30.0f);
	HealthBar->RelativeScale3D = FVector(0.1f, 0.1f, 1.0f);

	PushPowerBar = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("PushPowerBarMesh"));
	PushPowerBar->AttachTo(GetCapsuleComponent());
	PushPowerBar->RelativeLocation = FVector(-50.0f, 0, 30.0f);
	PushPowerBar->RelativeScale3D = FVector(0.1f, 1.0f, 1.0f);

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	FullHealth = 1000;
	health = FullHealth;
	HealthBarSize = FullHealth / FullHealth;
	quarterHealth = FullHealth / 4;

	FullPushPower = 1000;
	pushPower = FullPushPower;
	PushPowerBarSize = FullPushPower / FullPushPower;

	pushAttacking = false;
	dead = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void Atest3Character::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &Atest3Character::TouchStarted);
	if( EnableTouchscreenMovement(InputComponent) == false )
	{
		//InputComponent->BindAction("Fire", IE_Pressed, this, &Atest3Character::OnFire);
	}
	
	//InputComponent->BindAxis("MoveForward", this, &Atest3Character::MoveForward);
	//InputComponent->BindAxis("MoveRight", this, &Atest3Character::MoveRight);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &Atest3Character::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &Atest3Character::LookUpAtRate);
}

void Atest3Character::OnFire()
{ 
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<Atest3Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		//UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if(FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		/*UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if(AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}*/
	}

}

void Atest3Character::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if( TouchItem.bIsPressed == true )
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void Atest3Character::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if( ( FingerIndex == TouchItem.FingerIndex ) && (TouchItem.bMoved == false) )
	{
		OnFire();
	}
	TouchItem.bIsPressed = false;
}

void Atest3Character::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if ((TouchItem.bIsPressed == true) && ( TouchItem.FingerIndex==FingerIndex))
	{
		if (TouchItem.bIsPressed)
		{
			if (GetWorld() != nullptr)
			{
				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
				if (ViewportClient != nullptr)
				{
					FVector MoveDelta = Location - TouchItem.Location;
					FVector2D ScreenSize;
					ViewportClient->GetViewportSize(ScreenSize);
					FVector2D ScaledDelta = FVector2D( MoveDelta.X, MoveDelta.Y) / ScreenSize;									
					if (ScaledDelta.X != 0.0f)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.X * BaseTurnRate;
						AddControllerYawInput(Value);
					}
					if (ScaledDelta.Y != 0.0f)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.Y* BaseTurnRate;
						AddControllerPitchInput(Value);
					}
					TouchItem.Location = Location;
				}
				TouchItem.Location = Location;
			}
		}
	}
}

void Atest3Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void Atest3Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}
void Atest3Character::dodgeForwards(bool d) {
	relativeForward.X = 1;
	relativeForward.Y = 0;
	Dodge = d;
}
void Atest3Character::dodgeBackwards(bool d) {
	relativeForward.X = -1;
	relativeForward.Y = 0;
	Dodge = d;
}
void Atest3Character::dodgeLeft(bool d) {
	relativeForward.X = 0;
	relativeForward.Y = -1;
	Dodge = d;
}
void Atest3Character::dodgeRight(bool d) {
	relativeForward.X = 0;
	relativeForward.Y = 1;
	Dodge = d;
}

void Atest3Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void Atest3Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool Atest3Character::EnableTouchscreenMovement(class UInputComponent* InputComponent)
{
	bool bResult = false;
	if(FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch )
	{
		bResult = true;
		InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &Atest3Character::BeginTouch);
		InputComponent->BindTouch(EInputEvent::IE_Released, this, &Atest3Character::EndTouch);
		InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &Atest3Character::TouchUpdate);
	}
	return bResult;
}
void Atest3Character::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	HealthBarSize = health / FullHealth;
	/*HealthBarSize *= 10;
	round(HealthBarSize);
	HealthBarSize /= 10;*/
	if (HealthBarSize > 0) {
		HealthBar->RelativeScale3D = FVector(0.1f, 0.1f, HealthBarSize);
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

	PushPowerBarSize = pushPower / FullPushPower;

	if (PushPowerBarSize > 0) {
		PushPowerBar->RelativeScale3D = FVector(0.1f, PushPowerBarSize / 2, PushPowerBarSize /2);
		if (pushPower >= FullPushPower) {
			PushPowerBar->SetMaterial(0, MaterialCharged);
		}
		else {
			PushPowerBar->SetMaterial(0, MaterialCharging);
		}
	}

	if (pushPower < FullPushPower) {
		pushPower++;
	}

	if (health < 0) {
		dead = true;
	}
	else {

		if (DodgeForwardsMove) {
			MoveForward(1);
		}
		if (DodgeBackwardsMove) {
			MoveForward(-1);
		}
		if (DodgeLeftMove) {
			MoveRight(-1);
		}
		if (DodgeRightMove) {
			MoveRight(1);
		}
	}
}

void Atest3Character::testFire(bool f) {
	OnFire();
}
FVector Atest3Character::getMyLocation() {
	return GetActorLocation();
}

void Atest3Character::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	/*if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		//:note* this what a test I don't need it at the moment
		if (rightHookHit) {
			if (OtherActor->IsA(Adummy::StaticClass())) {
				Adummy* a = Cast<Adummy>(OtherActor);
				a->health--;
				OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
			}
		}
	}		*/
	/*if (OtherActor->IsA(Abot::StaticClass())) {
		Abot* a = Cast<Abot>(OtherActor);
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	}*/
	if (OtherActor->IsA(AWater::StaticClass())) {
		drowned = true;
		dead = true;
	}
}

void Atest3Character::pushAttacked() {
	if (pushPower >= FullPushPower) {
		pushAttacking = true;
		pushPower = 1;
	}
}