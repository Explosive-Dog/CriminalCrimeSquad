#include "Physical.h"

Physical::Physical(std::vector<Physical*>& physicalUpdatables){
	physicalUpdatables.push_back(this);
}

void Physical::setCollisionData(CollisionData collisionDataToSet){
	m_collisionData = collisionDataToSet;
}

Physical::CollisionData Physical::getCollisionData()
{
	return m_collisionData;
}

void Physical::clearCollisionData(){
	CollisionData resetToZero;
	m_collisionData = resetToZero;
}