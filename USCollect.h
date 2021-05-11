#if !defined(_USCOLLECT_H)
#define _USCOLLECT_H

/**
 *	@class 		USCollect
 *
 * 	@brief 		Definition of the USCollect Class.
 *
 * 	File Name: USCollect.h
 *
 *	@author 	Geoffrey Lawson (33176674)
 *
 *	@version 	0.2		11/5/2021	Rebuild of USCollect class to successfully extract data from a Bst.
 *	@version 	0.1		5/5/2021	Initial creation of the USCollect class.
 *
 *	@date 		11/5/2021
 *
 */
class USCollect {
public:
	static void SetTarget( unsigned & newTarget );
	static void ExtractTarget( unsigned & data );
	unsigned & GetTargetPtr();
private:
	static unsigned * targetPtr;
	static unsigned target;
};

#endif  //_USCOLLECT_H
