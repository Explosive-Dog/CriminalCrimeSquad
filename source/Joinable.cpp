#include "Joinable.h"

Grabable::Grabable(std::vector<const Grabable*>& theGrabablesContainer) : grabableContainer(&theGrabablesContainer)
{
}

void Grabable::objectGrabbed() const
{
	if (grabableContainer != nullptr && grabableContainer->empty() != true) {
		auto thisGrabable = std::find(grabableContainer->begin(), grabableContainer->end(), this);
		grabableContainer->erase(thisGrabable);
	}
}

void Grabable::objectReleased() const
{
	if (grabableContainer != nullptr) {
		grabableContainer->push_back(this);
	}
}
