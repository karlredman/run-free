/*! \file debug.h
    \brief project debug macros
    
    These macros are here for convenience. Mostly I use this kind of
    stuff for light debug work here and there. Please feel free to
    steal what you need and use it as your own -parasyte.
*/
/* NOTICE:
    Copyright (C) 2004  Karl N. Redman (SleepingStill.com)

    This file ONLY, independent and free from any and all other files,
    in whole or in part, is NOT covered under any license and may be
    considered free to use, in whole or in part, by any entity in any
    way that said entity sees fit to do so. Furthermore, it is the
    intention of the copyright holder, Karl N. Redman, that content
    found in this file be considered public domain information.


    For further information contact: parasyte@sleepingstill.com
*/

/*********************** NOTE:
This file is intended to be used on a per project basis and should be
edited accourdingly (until it is generic enough to leave alone, I
guess). In an automake project you can drop this file into a directory
and have local debuging ability. 

If you are using autoconf be sure to define the PRINTF preprocessor in
config.h (configure.ac) if you want to use something other than printf
to ouput your debug messages. 


 */
#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

/** 
    program DEBUGING STATEMENTS. 
    
    These would be called in the following ways:<br>
    dprint("this is a string");<br>
    dprint_s1("this is also a string");<br>
    dprint_s2("foo", "bar");<br>
    dprint_f1("%s", "thing");<br>
    dprint_f1("%d", 1);<br>
    dprint_f2("%s", "%d", "stuff", 69);<br>
    dprint_f2("%s", "%x", "a hex number", 255);<br>
    
    This would be the output (assuming PACKAGE is defined as
    "run-free"):<br>
    run-free DEBUG(this is a string)<br>
    run-free DEBUG(this is also a string)<br>
    run-free DEBUG(foo:bar)<br>
    run-free DEBUG(thing)<br>
    run-free DEBUG(1)<br>
    run-free DEBUG(stuff:69)<br>
    run-free DEBUG(a hex number:ff)  <br>
*/
///compile time option
#ifdef DEBUG	
#define DEBUG_MODE 1
#else
#define DEBUG_MODE 0
#endif


/** @name Debugging Message output
 *  These macros define attributes of debug message output
 */
//@{ 

#ifndef DEBUG_PRINTF
/// The kind of prinf() style of function debug uses for output
#define DEBUG_PRINTF printf

#ifndef DEBUG_PRINTF_INCLUDE
/// The support header file for the debug function
#define DEBUG_PRINTF_INCLUDE <stdio.h>
#include DEBUG_PRINTF_INCLUDE
#endif //DEBUG_PRINTF_INCLUDE

#endif //DEBUG_PRINTF

/// The package name
#define DEBUG_PREMSG PACKAGE
/// a submessage 
#define DEBUG_SUBMSG "DEBUG"
//@}

/** @name Debugging statments
 *  These macros print statements to the command line when run-free is
 *  compiled with the --enable-debug=yes directive from configure
 */
//@{ 
/// print a string in debug mode -a convenience function
#define dprint(string) dprint_s1(string)
/// single string printing
#define dprint_s1(string) if(DEBUG_MODE) DEBUG_PRINTF(""DEBUG_PREMSG" "DEBUG_SUBMSG"(%s)\n", string)
/// double string printing
#define dprint_s2(string1, string2) if(DEBUG_MODE) DEBUG_PRINTF(""DEBUG_PREMSG" "DEBUG_SUBMSG"(%s:%s)\n", string1, string2)
/// single format debugging from gprint
#define dprint_f1(format, data) if(DEBUG_MODE) DEBUG_PRINTF(""DEBUG_PREMSG" "DEBUG_SUBMSG"("format")\n", data)
/// double format debugging from gprint
#define dprint_f2(format1, format2, data1, data2) if(DEBUG_MODE) DEBUG_PRINTF(""DEBUG_PREMSG" "DEBUG_SUBMSG"("format1":"format2")\n", data1, data2)
//@}

#endif //_DEBUG_H_
