

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API AARItemChest : public AActor
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LidMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Animation")
	float AnimationSpeed = 50.0f;
	
	UPROPERTY(EditAnywhere, Category = "Animation")
	float AnimationTargetPitch = 120.0f;

	float CurrentAnimationPitch = 0.0f;

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	AARItemChest();
	
};
