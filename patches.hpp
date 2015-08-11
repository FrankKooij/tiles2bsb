// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// PATCHES.HPP
// Applying certain patches for ease of use
//
// Author: Thomas Brüggemann
// ---------------------------------------------------------------------------

#ifndef PATCHES_HPP
#define PATCHES_HPP

#include <sstream>

namespace patches
{
	template < typename T > std::string to_string( const T& n )
	{
		std::ostringstream stm;
		stm << n ;
		return stm.str() ;
	}
}

#endif