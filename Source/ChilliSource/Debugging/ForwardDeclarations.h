//
//  ForwardDeclarations.h
//  Chilli Source
//
//  Created by Ian Copland on 25/02/2014.
//  Copyright (c) 2014 Tag Games Ltd. All rights reserved.
//

#ifndef _CHILLISOURCE_DEBUGGING_FORWARDDECLARATIONS_H_
#define _CHILLISOURCE_DEBUGGING_FORWARDDECLARATIONS_H_

#include <ChilliSource/Core/Base/StandardMacros.h>

#include <memory>

namespace ChilliSource
{
    namespace Base
    {
        //--------------------------------------------------
        /// Base
        //--------------------------------------------------
#ifdef DEBUG_STATS
        CS_FORWARD_DECLARE_CLASS(DebugStats);
#endif
    }
}
#endif
