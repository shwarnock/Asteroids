#ifndef _PHYSICSMANAGER_H
#define _PHYSICSMANAGER_H

#include "../Physics/PhysicsEntity.h"
#include <bitset>

class PhysicsManager
{
public:
	enum class CollisionLayers
	{
		Friendly = 0,
		FriendlyProjectiles,
		Hostile,
		HostileProjectiles,

		MaxLayers
	};

	enum class CollisionFlags
	{
		None				 = 0x00,
		Friendly			 = 0x01,
		FriendlyProjectiles	 = 0x02,
		Hostile				 = 0x04,
		HostileProjectiles	 = 0x08
	};

private:
	static PhysicsManager* sInstance;

	vector <PhysicsEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
	bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

	unsigned long mLastId;

public:
	static PhysicsManager* Instance();
	static void Release();

	CollisionLayers GetCollisionLayer(unsigned long mId);

	void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flag);

	unsigned long RegisterEntity(PhysicsEntity* entity, CollisionLayers layer);
	void UnregisterEntity(unsigned long id);

	void Update();

private:
	PhysicsManager();
	~PhysicsManager();
};

inline PhysicsManager::CollisionFlags operator|(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b)
{
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline PhysicsManager::CollisionFlags operator&(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b)
{
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}
#endif