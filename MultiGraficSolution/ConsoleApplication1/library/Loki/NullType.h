////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
#ifndef NULLTYPE_INC_
#define NULLTYPE_INC_

namespace Loki
{

    class NullType 
    {
		public:
			struct Head { private: Head(); };
			struct Tail { private: Tail(); };
    };
}


#endif 

