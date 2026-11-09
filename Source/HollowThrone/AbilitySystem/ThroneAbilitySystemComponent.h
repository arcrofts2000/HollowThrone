// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ThroneAbilitySystemComponent.generated.h"



UENUM()
enum EAttributeModifyType
{
	Base,
	Modifier,
	OverrideBase,
	Invalid
};



DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChangedSignature, FGameplayTag /* AttributeTag */, float /* Old Value */, float /* New Value */);



class UThroneAbility;
class UThroneAttributeSet;
struct FThroneAttribute;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOLLOWTHRONE_API UThroneAbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UThroneAbilitySystemComponent();

	virtual void InitializeComponent() override;
	void InitializeAttributes();
	void InitializeAbilities();

	

	bool ApplyAttributeChange(FGameplayTag AttributeTag, float AttributeDelta, EAttributeModifyType ModifyType);


	FThroneAttribute* GetAttribute(FGameplayTag InAttributeTag);

	FOnAttributeChangedSignature& GetAttributeDelegate(FGameplayTag InAttributeTag);
	


	// Abilities

	FGameplayTagContainer ActiveGameplayTags;

	void StartAbility(FGameplayTag InAbilityName);
	void StopAbility(FGameplayTag InAbilityName);
	
	void GrantAbility(TSubclassOf<UThroneAbility> AbilityToGrant);

	


protected:

	UPROPERTY()
	TObjectPtr<UThroneAttributeSet> AttributeSet;

	TMap<FGameplayTag, FThroneAttribute*> CachedAttributes;

	/* NoClear prevents this from being set to NULL */
	UPROPERTY(EditAnywhere, Category = "Attributes", NoClear)
	TSubclassOf<UThroneAttributeSet> AttributeSetClass;

	TMap<FGameplayTag, FOnAttributeChangedSignature> AttributeDelegates;

	UPROPERTY()
	TArray<TObjectPtr<UThroneAbility>> Abilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UThroneAbility>> DefaultAbilities;


	
		
};
