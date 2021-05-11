#include "FLCollect.h"

float * FLCollect::targetPtr = nullptr;
float FLCollect::target;

//	Set the current target
void FLCollect::SetTarget( float & newTarget ) {
	target = newTarget;
}

//	Check the given input, and if it's valid, set the targetPtr
void FLCollect::ExtractTarget( float & data ) {
	if( target == data ) {
		targetPtr = &data;
	}
}

//	Return the targetPtr
float & FLCollect::GetTargetPtr() {
	return( *targetPtr );
}
