

#pragma once

#include "CoreMinimal.h"
#include "Core/ARInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "ARItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API AARItemChest : public AActor, public IARInteractionInterface
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


	UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
	void ChestAnimationComplete();


public:	

	virtual void Interact() override;
	
	virtual void Tick(float DeltaTime) override;

	AARItemChest();
	
};
