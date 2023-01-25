# UnrealPortpolio
포트폴리오 목적으로 제작된 RPG 데모 게임입니다.

# 플레이 동영상
[![Video Label](http://img.youtube.com/vi/7sPk10bjTaY/0.jpg)](https://www.youtube.com/watch?v=7sPk10bjTaY)

# 기술 설명서

## Controller - Character 구조
![image](https://user-images.githubusercontent.com/121685997/212113656-b9192749-69b3-4838-84c7-281d21282aae.png)

## EnemyCharacter
걸어다니며 근접 공격을 하는 몬스터 캐릭터의 부모 클래스
- HPBarWidget 관리
- TakeDamage는 Characterstat 액터컴포넌트에서 처리

## DHCharacterStat
> TakeDamage -> SetDamage -> SetHP

    float AEnemyCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
	{
		float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

		MonsterStat->SetDamage(FinalDamage);
		return FinalDamage;
	}
	
	void UDHMonsterStat::SetDamage(float NewDamage)
	{
		DHCHECK(nullptr != CurrentStatData);
		SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.f, CurrentStatData->MaxHP));
	}
	
	void UDHMonsterStat::SetHP(float NewHP)
	{
		CurrentHP = NewHP;
		OnHPChanged.Broadcast();
		if (CurrentHP < KINDA_SMALL_NUMBER)
		{
			CurrentHP = 0.f;
			OnHPIsZero.Broadcast();
		}
	}

## EnemyCharacter 처리 방식(예시: DHTroll)
- 애님블루프린트/비헤이비어트리

> AnimBlueprint
![image](https://user-images.githubusercontent.com/121685997/214459375-98142ae3-7fad-4855-b7cc-1657e8052aad.png)
![image](https://user-images.githubusercontent.com/121685997/214459410-927229af-e793-4bea-bae6-bb14fa84c8d3.png)

> BehaviorTree
![image](https://user-images.githubusercontent.com/121685997/214459497-35ccc047-25d2-4e1e-8851-a11423276ae5.png)


## NormalMonsterAICon
- BehaviorTree와 BlackBoard를 관리, 구동

## InventoryComponent
- DHCharacter의 인벤토리 관리 ActorComponent
- 아이템의 리스트 관리

> AddItem

	bool UInventoryComponent::AddItem(class UItemBase* Item)
	{
		if (Items.Num() >= Capacity || !Item)
		{
			return false;
		}
	
		Item->OwningInventory = this;
		Items.Add(Item);
	
		//UI update
		OnInventoryUpdated.Broadcast();

		return true;
	}

