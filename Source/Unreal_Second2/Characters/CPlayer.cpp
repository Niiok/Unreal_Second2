#include "CPlayer.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Component/COptionComponent.h"
#include "Component/CStatusComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CMontagesComponent.h"
#include "Component/CActionComponent.h"
#include "Component/CTargetComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Widgets/CUserWidget_ActionList.h"


ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	CHelpers::CreateActorComponent<UCOptionComponent>(this, &Option, "Option");
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCMontagesComponent>(this, &Montages, "Montages");
	CHelpers::CreateActorComponent<UCActionComponent>(this, &Action, "Action");
	CHelpers::CreateActorComponent<UCTargetComponent>(this, &Target, "Target");
	CHelpers::GetClass<UCUserWidget_ActionList>(&ActionListClass,
		TEXT("WidgetBlueprint'/Game/Widgets/WB_ActionList.WB_ActionList_C'"));

	bUseControllerRotationYaw = false;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");

	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/Player/ABP_CPlayer.ABP_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	State->OnStateTypeChanged.AddDynamic(this, &ACPlayer::OnStateTypeChanged);

	UMaterialInstanceConstant* body;
	UMaterialInstanceConstant* logo;
	
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&body, 
		L"MaterialInstanceConstant'/Game/Materials/M_UE4Man_Body_Inst.M_UE4Man_Body_Inst'");
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&logo, 
		L"MaterialInstanceConstant'/Game/Materials/M_UE4Man_ChestLogo_Inst.M_UE4Man_ChestLogo_Inst'");

	BodyMaterial = UMaterialInstanceDynamic::Create(body, this);
	LogoMaterial = UMaterialInstanceDynamic::Create(logo, this);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	Action->SetUnarmedMode();

	ActionList = CreateWidget<UCUserWidget_ActionList, APlayerController>
		(GetController<APlayerController>(), ActionListClass);

	ActionList->AddToViewport();
	ActionList->SetVisibility(ESlateVisibility::Hidden);

	ActionList->GetData(0).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ACPlayer::OnFist);
	ActionList->GetData(1).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ACPlayer::OnOneHand);
	ActionList->GetData(2).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ACPlayer::OnTwoHand);
	ActionList->GetData(3).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ACPlayer::OnWarp);
	ActionList->GetData(4).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ACPlayer::OnFireStorm);
	ActionList->GetData(5).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ACPlayer::OnIceBall);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);

	PlayerInputComponent->BindAction("Avoid", IE_Pressed, this, &ACPlayer::OnAvoid);

	PlayerInputComponent->BindAction("Fist", IE_Pressed, this, &ACPlayer::OnFist);
	PlayerInputComponent->BindAction("OneHand", IE_Pressed, this, &ACPlayer::OnOneHand);
	PlayerInputComponent->BindAction("TwoHand", IE_Pressed, this, &ACPlayer::OnTwoHand);
	PlayerInputComponent->BindAction("Warp", IE_Pressed, this, &ACPlayer::OnWarp);
	PlayerInputComponent->BindAction("FireStorm", IE_Pressed, this, &ACPlayer::OnFireStorm);
	PlayerInputComponent->BindAction("IceBall", IE_Pressed, this, &ACPlayer::OnIceBall);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ACPlayer::OnDoAction);
	
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ACPlayer::OffAim);

	PlayerInputComponent->BindAction("ViewActionList", IE_Pressed, this, &ACPlayer::OnViewActionList);
	PlayerInputComponent->BindAction("ViewActionList", IE_Released, this, &ACPlayer::OffViewActionList);
	
	PlayerInputComponent->BindAction("Target", IE_Pressed, this, &ACPlayer::OnTarget);
	PlayerInputComponent->BindAction("TargetLeft", IE_Pressed, this, &ACPlayer::OnTargetLeft);
	PlayerInputComponent->BindAction("TargetRight", IE_Pressed, this, &ACPlayer::OnTargetRight);
}

void ACPlayer::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Roll: Begin_Roll(); break;
	case EStateType::Backstep: Begin_Backstep(); break;
	}
}

void ACPlayer::OnMoveForward(float InAxis)
{
	CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();
	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnMoveRight(float InAxis)
{
	CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();
	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
	float rate = Option->GetHorizontalLookRate();
	AddControllerYawInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnVerticalLook(float InAxis)
{
	float rate = Option->GetVerticalLookRate();
	AddControllerPitchInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnAvoid()
{
	CheckFalse(Status->CanMove());
	CheckFalse(State->IsIdleMode());

	if (InputComponent->GetAxisValue("MoveForward") < 0.0f)
	{
		State->SetBackstepMode();
		return;
	}

	State->SetRollMode();
}

void ACPlayer::Begin_Roll()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	FVector start = GetActorLocation();
	FVector dest;

	if (GetVelocity() == FVector::ZeroVector)
		dest = start + GetActorForwardVector().GetSafeNormal2D();
	else
		dest = start + GetVelocity().GetSafeNormal2D();

	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, dest));

	Montages->PlayRoll();
}

void ACPlayer::Begin_Backstep()
{
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	Montages->PlayBackstep();
}

void ACPlayer::End_Roll()
{
	if (!Action->IsUnarmedMode() && !Action->IsWarpMode() && !Action->IsFireStormMode())
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	State->SetIdleMode();
}

void ACPlayer::End_Backstep()
{
	if (Action->IsUnarmedMode() || Action->IsWarpMode() || Action->IsFireStormMode())
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
	
	State->SetIdleMode();
}

void ACPlayer::OnFist()
{
	CheckFalse(State->IsIdleMode());
	Action->SetFistMode();
}

void ACPlayer::OnOneHand()
{
	CheckFalse(State->IsIdleMode());
	Action->SetOneHandMode();
}

void ACPlayer::OnTwoHand()
{
	CheckFalse(State->IsIdleMode());
	Action->SetTwoHandMode();
}

void ACPlayer::OnWarp()
{
	CheckFalse(State->IsIdleMode());
	Action->SetWarpMode();
}

void ACPlayer::OnFireStorm()
{
	CheckFalse(State->IsIdleMode());
	Action->SetFireStormMode();
}

void ACPlayer::OnIceBall()
{
	CheckFalse(State->IsIdleMode());
	Action->SetIceBallMode();
}

void ACPlayer::OnDoAction()
{
	Action->DoAction();
}

void ACPlayer::OnAim()
{
	Action->DoAim(true);
}

void ACPlayer::OffAim()
{
	Action->DoAim(false);
}

void ACPlayer::OnViewActionList()
{
	CheckFalse(State->IsIdleMode());

	ActionList->SetVisibility(ESlateVisibility::Visible);

	GetController<APlayerController>()->bShowMouseCursor = true;
	GetController<APlayerController>()->SetInputMode(FInputModeGameAndUI());

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1f);
}

void ACPlayer::OffViewActionList()
{
	//ActionList->SetVisibility(ESlateVisibility::Hidden);

	//GetController<APlayerController>()->bShowMouseCursor = false;
	//GetController<APlayerController>()->SetInputMode(FInputModeGameOnly());

	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}

void ACPlayer::OnTarget()
{
	Target->ToggleTarget();
}

void ACPlayer::OnTargetLeft()
{
	Target->ChangeTargetLeft();
}

void ACPlayer::OnTargetRight()
{
	Target->ChangeTargetRight();
}

void ACPlayer::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("LogoColor", InColor);
}