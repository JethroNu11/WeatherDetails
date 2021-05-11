#if !defined(_FLCOLLECT_H)
#define _FLCOLLECT_H

/**
 *	@class 		FLCollect
 *
 * 	@brief 		Definition of the FLCollect Class.
 *
 * 	File Name: FLCollect.h
 *
 *	@author 	Geoffrey Lawson (33176674)
 *
 *	@version 	0.2		11/5/2021	Rebuild of FLCollect class to successfully extract data from a Bst.
 *	@version 	0.1		5/5/2021	Initial creation of the FLCollect class.
 *
 *	@date 		11/5/2021
 *
 */
class FLCollect {
public:
	static void SetTarget( float & newTarget );
	static void ExtractTarget( float & data );
	float & GetTargetPtr();
private:
	static float * targetPtr;
	static float target;
};

#endif  //_FLCOLLECT_H
