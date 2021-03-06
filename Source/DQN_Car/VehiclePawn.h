// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
THIRD_PARTY_INCLUDES_START
#include "torch/torch.h"
THIRD_PARTY_INCLUDES_END
#include "CarGI.h"
#include "VehiclePawn.generated.h"

/**
 * 
 */
UCLASS()
class DQN_CAR_API AVehiclePawn : public AWheeledVehicle
{
	GENERATED_BODY()
	
public:
	AVehiclePawn();
	~AVehiclePawn();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	//virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void ApplyThrottle(float val);
	void ApplySteering(float val);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void TraceDistance(bool debugLine = false); // get state and reward
	void TraceByProfile(FHitResult& outHit, const FVector& start, const FVector& forward, bool drawDebug = false, FColor debugColor = FColor::Green);

	void TakeAction(torch::Tensor& action);

	FORCEINLINE torch::Tensor GetState() const { return CurrentState; }
	FORCEINLINE torch::Tensor GetReward() const { return CurrentReward; }
	FORCEINLINE bool GetDone() const { return Done; }

protected:

	UPROPERTY(Category = Camera, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	UPROPERTY(Category = Camera, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	// sensors
	UPROPERTY(Category = Sensor, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* SensorF;

	UPROPERTY(Category = Sensor, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* SensorL;

	UPROPERTY(Category = Sensor, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* SensorR;

	UPROPERTY(Category = Sensor, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* SensorLS;

	UPROPERTY(Category = Sensor, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* SensorRS;

	UPROPERTY(Category = Sensor, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* SensorLS1;

	UPROPERTY(Category = Sensor, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* SensorRS1;

private:
	torch::Tensor CurrentState;
	torch::Tensor CurrentReward;
	bool Done = false;
	bool HitGate = false;
	torch::Device Device = UCarGI::Device;
};
