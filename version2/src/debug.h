/*! \file debug.h
    \brief run-free debug macros
    
    These macros are here for convenience. Mostly I use this kind of
    stuff for light debug work here and there. Please feel free to
    steal what you need and use it as your own -parasyte.
*/
/* NOTICE:
    Copyright (C) 2004  Karl N. Redman (SleepingStill.com)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    For further information contact: parasyte@sleepingstill.com
*/
#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

/** 
    run-free DEBUGING STATEMENTS. 
    
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

/// The package name
#define DEBUG_PREMSG PACKAGE

/// a submessage 
#define DEBUG_SUBMSG "DEBUG"

/** @name Debugging statments
 *  These macros print statements to the command line when run-free is
 *  compiled with the --enable-debug=yes directive from configure
 */
//@{ 
/// print a string in debug mode -a convenience function
#define dprint(string) dprint_s1(string)
/// single string printing
#define dprint_s1(string) if(DEBUG_MODE) g_print(""DEBUG_PREMSG" "DEBUG_SUBMSG"(%s)\n", string)
/// double string printing
#define dprint_s2(string1, string2) if(DEBUG_MODE) g_print(""DEBUG_PREMSG" "DEBUG_SUBMSG"(%s:%s)\n", string1, string2)
/// single format debugging from gprint
#define dprint_f1(format, data) if(DEBUG_MODE) g_print(""DEBUG_PREMSG" "DEBUG_SUBMSG"("format")\n", data)
/// double format debugging from gprint
#define dprint_f2(format1, format2, data1, data2) if(DEBUG_MODE) g_print(""DEBUG_PREMSG" "DEBUG_SUBMSG"("format1":"format2")\n", data1, data2)
//@}

#endif //_DEBUG_H_
