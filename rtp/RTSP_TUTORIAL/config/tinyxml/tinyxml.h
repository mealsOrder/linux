#ifndef TINYXML_INCLUDED
#define TINYXML_INCLUDED

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4530)
#pragma warning(disable : 4786)
#endif

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

#ifdef TIXML_USE_STL
#include <string>
#include <iostream>
#include <sstream>
#define TIXML_STRING std::string
#else
#include "tinystr.h"
#define TIXML_STRING TiXmlString
#endif

#define TIXML_SAFE

#ifdef TIXML_SAFE
#if defined(_MSC_VER) && (_MSC_VER >= 1400)

#define TIXML_SNPRINTF _snpritf_s
#define TIXML_SSCANF sscanf_s
#elif defined(_MSC_VER) && (_MSC_VER >= 1200)

