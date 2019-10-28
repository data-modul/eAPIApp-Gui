/*
 *<KHeader>
 *+=========================================================================
 *I  Project Name: EApiDK Embedded Application Development Kit
 *+=========================================================================
 *I  $HeadURL: https://eapidk.svn.sourceforge.net/svnroot/eapidk/trunk/lib/WINNT/EApiOsNTC.c $
 *+=========================================================================
 *I   Copyright: Copyright (c) 2002-2009, Kontron Embedded Modules GmbH
 *I      Author: John Kearney,                  John.Kearney@kontron.com
 *I
 *I     License: All rights reserved. This program and the accompanying 
 *I              materials are licensed and made available under the 
 *I              terms and conditions of the BSD License which 
 *I              accompanies this distribution. The full text of the 
 *I              license may be found at 
 *I              http://opensource.org/licenses/bsd-license.php
 *I              
 *I              THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "
 *I              AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS OF 
 *I              ANY KIND, EITHER EXPRESS OR IMPLIED.
 *I
 *I Description: Auto Created for EApiOsNTC.c
 *I
 *+-------------------------------------------------------------------------
 *I
 *I  File Name            : EApiOsNTC.c
 *I  File Location        : lib\WINNT
 *I  Last committed       : $Revision: 38 $
 *I  Last changed by      : $Author: dethrophes $
 *I  Last changed date    : $Date: 2010-01-26 07:48:22 +0100 (Di, 26. Jan 2010) $
 *I  ID                   : $Id: EApiOsNTC.c 38 2010-01-26 06:48:22Z dethrophes $
 *I
 *+=========================================================================
 *</KHeader>
 */
#include <EApiOsNTC.h>
#include <Windows.h>

#ifdef __cplusplus
extern "C"
{
#endif

void usleep(unsigned long us)  
{ 
  LARGE_INTEGER cnt1;
  LARGE_INTEGER cnt2;
  QueryPerformanceCounter   (&cnt1);
  QueryPerformanceFrequency (&cnt2);
  cnt1.QuadPart+=(us*cnt2.QuadPart)/1000000;
  do{
    QueryPerformanceCounter (&cnt2);
  }while(cnt1.QuadPart>cnt2.QuadPart);
  return ;
}

#ifdef __cplusplus
}
#endif
