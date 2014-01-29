//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2012 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------


#import <Foundation/Foundation.h>

// the purpose of this category extension is so that when SWIG is constructing
// a new object, as it initializes its super classes, it calls initWithCPtr
// to avoid creating new cpp objects as the super clases are initialized.
// By giving NSObject the new method initWithCptr, which actually does exactly
// what NSObject's init method does, we can call at as we would any other base
// class during initialization without attempting to determine that we are about
// to call init on NSObject (which proved difficult/impossible to do).
@interface NSObject (NSObjectInitWithCptr)
- (id)initWithCptr: (void*) cptr;
@end
