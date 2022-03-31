// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Classes/RI/Service.h"
#include "ROSIntegration/Public/quadditch/AdminCmdRequest.h"
#include "ROSIntegration/Public/quadditch/AdminCmdResponse.h"
#include "ROSIntegration/Public/ROSBaseServiceResponse.h"
#include "ENUMS_dummy_class.h"
#include "TKLServiceActor.generated.h"

UCLASS(BlueprintType)
class QUADDITCH_API ATKLServiceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATKLServiceActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	virtual void CallService(ECmdState cmdState, ECmdInter cmdInter);
	UFUNCTION(BlueprintCallable)
	virtual void Init(FString newTopic);
	bool initialized = false;
	FString topic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool acked;

private:
	// Your private code here...

	UPROPERTY()
		class UROSIntegrationGameInstance* ROSInst;

	UPROPERTY()
		class UService* ServiceClient;

	void ResponseCB(TSharedPtr<FROSBaseServiceResponse> Response);
};
