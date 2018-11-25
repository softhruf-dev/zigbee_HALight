/******************************************************************************
* This Source file is for registering end point "0x00"(ZDP), "0xFF" (Broadcast) 
* (compile time and Run time both) and Application end points at compile time.
*
* Copyright (c) 2008, Freescale, Inc. All rights reserved.
*
*
* No part of this document must be reproduced in any form - including copied,
* transcribed, printed or by any electronic means - without specific written
* permission from Freescale Semiconductor.
*
******************************************************************************/

#include "EmbeddedTypes.h"
#include "ZdpManager.h"

#include "BeeStackConfiguration.h"
#include "BeeStack_Globals.h"
#include "BeeStackUtil.h"

#include "ZbAppInterface.h"

/******************************************************************************
*******************************************************************************
* Private Macros
*******************************************************************************
******************************************************************************/
/* None */
/******************************************************************************
*******************************************************************************
* Private Prototypes
*******************************************************************************
******************************************************************************/
/* None */
/******************************************************************************
*******************************************************************************
* Private type definitions
*******************************************************************************
******************************************************************************/
/* None */
/******************************************************************************
*******************************************************************************
* Private Memory Declarations
*******************************************************************************
******************************************************************************/

/* Simple Discriptor for 0x00(ZDP) description*/
zbSimpleDescriptor_t gZdpEp = 
{
  0x00,                        /* End Point (1Byte) */
  0x00,0x00,                   /* Device Description (2Bytes) */
  0x00,0x00,                   /* Profile ID (2Bytes) */
  gAppDeviceVersionAndFlag_c,  /* AppDeviceVersionAndFlag (1Byte) */
  0x00,                        /* NumOfInputClusters(1Byte) */
  NULL,                        /* PointerToInputClusterList (1Byte) */
  0x00,                        /* NumOfOutputClusters (1Byte) */
  NULL                         /* PointerToOutputClusterList (1Byte) */
};



endPointDesc_t endPoint0Desc = {
    
  (zbSimpleDescriptor_t *)&gZdpEp,  /* Simple descriptor for ZDP. */
  Zdo_MsgDataCallBack,              /* Indication call back for this ep */
  Zdo_CnfCallBack,                  /* Confirm call back for this ep */
  0x00                              /* No fragmentation supported for this ep. */
};


/******************************************************************************
*******************************************************************************
* Public Functions
*******************************************************************************
******************************************************************************/
/* None */
/******************************************************************************
*******************************************************************************
* Private Functions
*******************************************************************************
******************************************************************************/
/* None */
/******************************************************************************
*******************************************************************************
* Private Debug Stuff
*******************************************************************************
******************************************************************************/
/* None */


