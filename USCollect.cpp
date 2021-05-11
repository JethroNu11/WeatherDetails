#include "USCollect.h"

unsigned * USCollect::targetPtr = nullptr;
unsigned USCollect::target;

//	Set the current target
void USCollect::SetTarget( unsigned & newTarget ) {
	target = newTarget;
}

//	Check the given input, and if it's valid, set the targetPtr
void USCollect::ExtractTarget( unsigned & data ) {
	if( target == data ) {
		targetPtr = &data;
	}
}

//	Return the targetPtr
unsigned & USCollect::GetTargetPtr() {
	return( *targetPtr );
}
