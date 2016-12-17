// Fill out your copyright notice in the Description page of Project Settings.

#include "Computatorium.h"
#include "Worker.h"

// Sets default values
AWorker::AWorker()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Our root component will be a sphere that reacts to physics
    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius(40.0f);
    SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
    
    // Create and position a mesh component so we can see where our sphere is
    UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    SphereVisual->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
    if (SphereVisualAsset.Succeeded())
    {
        SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
        SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
        SphereVisual->SetWorldScale3D(FVector(0.8f));
    }
    
    // Use a spring arm to give the camera smooth, natural-feeling motion.
    USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
    SpringArm->TargetArmLength = 400.0f;
    SpringArm->bEnableCameraLag = true;
    SpringArm->CameraLagSpeed = 3.0f;
    
    // Create a camera and attach to our spring arm
    UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    
    // Create an instance of our movement component, and tell it to update the root.
    MovementComponent = CreateDefaultSubobject<UWorkerMovementComponent>(TEXT("CustomMovementComponent"));
    MovementComponent->UpdatedComponent = RootComponent;
    
    // Take control of the default player
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AWorker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorker::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

UPawnMovementComponent* AWorker::GetMovementComponent() const
{
    return MovementComponent;
}

// Called to bind functionality to input
void AWorker::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
    
    InputComponent->BindAxis("MoveForward", this, &AWorker::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &AWorker::MoveRight);
    InputComponent->BindAxis("Turn", this, &AWorker::Turn);
}

void AWorker::MoveForward(float AxisValue)
{
    if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
    {
        MovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
    }
}

void AWorker::MoveRight(float AxisValue)
{
    if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
    {
        MovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
    }
}

void AWorker::Turn(float AxisValue)
{
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += AxisValue;
    SetActorRotation(NewRotation);
}

