/******************************************************************************
* This file contains the prototype definitions of interface function provided 
* to ZDO
*
*
* (c) Copyright 2005, Freescale, Inc. All rights reserved.
*
*
* No part of this document must be reproduced in any form - including copied,
* transcribed, printed or by any electronic means - without specific written
* permission from Freescale Semiconductor.
*
******************************************************************************/
#ifndef _AF_ZDO_INTERFACE_H_
#define _AF_ZDO_INTERFACE_H_

#ifdef __cplusplus
    extern "C" {
#endif

#include "EmbeddedTypes.h"
/******************************************************************************
*******************************************************************************
* Public macros
*******************************************************************************
******************************************************************************/

/* None */

/******************************************************************************
*******************************************************************************
* Public type definitions
*******************************************************************************
******************************************************************************/

/* None */

/******************************************************************************
*******************************************************************************
* Public memory declarations
*******************************************************************************
******************************************************************************/

/* None */

/******************************************************************************
*******************************************************************************
* Public prototypes
*******************************************************************************
******************************************************************************/

/******************************************************************************
* Returns # of active endpoints
******************************************************************************/
uint8_t AF_NumOfEndPoints(void);
  
/******************************************************************************
* find the simple descriptor, given and endpoint #
******************************************************************************/
zbSimpleDescriptor_t* AF_FindEndPointDesc 
( 
  uint8_t endPoint /* IN: EndPoint Id */
);
  
/******************************************************************************
* Returns a list of the active endpoints
******************************************************************************/
zbEndPoint_t *AF_EndPointsList
( 
  uint8_t *pNoOfEndPoints /* OUT: returns # of endpoints too */
);  
/******************************************************************************
*******************************************************************************
* Public functions
*******************************************************************************
******************************************************************************/

/* None */
#ifdef __cplusplus
}
#endif
#endif /*_AF_ZDO_INTERFACE_H_*/