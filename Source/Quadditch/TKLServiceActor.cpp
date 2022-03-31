#include "TKLServiceActor.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Classes/RI/Service.h"
#include "ROSIntegration/Public/quadditch/AdminCmdRequest.h"
#include "ROSIntegration/Public/quadditch/AdminCmdResponse.h"

#include "ROSIntegration/Public/ROSBaseServiceResponse.h"

// Sets default values
ATKLServiceActor::ATKLServiceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATKLServiceActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATKLServiceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATKLServiceActor::Init(FString newTopic) {
    topic = newTopic;
    ROSInst = Cast<UROSIntegrationGameInstance>(GetGameInstance());
    if (ROSInst)
    {
        ServiceClient = NewObject<UService>(UService::StaticClass());
        ServiceClient->Init(ROSInst->ROSIntegrationCore, topic, TEXT("quadditch/AdminCmd"));
    }
    initialized = true;
}

void ATKLServiceActor::CallService(ECmdState cmdState, ECmdInter cmdInter)
{

    if (!initialized) {
        UE_LOG(LogTemp, Warning, TEXT("Service client not initialized"));
        return;
    }

    FString strCmdState = GetEnumValueAsString<ECmdState>("ECmdState", cmdState);
    FString strCmdInter = GetEnumValueAsString<ECmdInter>("ECmdInter", cmdInter);

    if (ROSInst)
    {
        acked = false;
        TSharedPtr<quadditch::FAdminCmdRequest> Request(new quadditch::FAdminCmdRequest());
        Request->_cmd = strCmdState;
        Request->_inter = strCmdInter;
        ServiceClient->CallService(Request, std::bind(&ATKLServiceActor::ResponseCB, this, std::placeholders::_1));
    }
}

void ATKLServiceActor::ResponseCB(TSharedPtr<FROSBaseServiceResponse> Response)
{
    auto CastResponse = StaticCastSharedPtr<quadditch::FAdminCmdResponse>(Response);
    if (!CastResponse)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to cast Response"));
        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("Acked?: %s"), (CastResponse->_ack ? "true" : "false"));
    acked = CastResponse->_ack;

}
