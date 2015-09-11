//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2015 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

#import "NSObjectInitWithCptr.h"

@implementation NSObject (NSObjectInitWithCptr)

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-designated-initializers"

-(instancetype)initWithCptr: (void*) cptr
{
    return self;
}
#pragma clang diagnostic pop


@end
