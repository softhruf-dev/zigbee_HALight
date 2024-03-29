/******************************************************************************
* ZCL.h
*
* Types, definitions and prototypes for the ZigBee Cluster Library, a library
* of clusters/attributes/commands that is used by muliple application profiles
* including Home Automation (HA).
*
* Copyright (c) 2007, Freescale, Inc.  All rights reserved.
*
*
* No part of this document must be reproduced in any form - including copied,
* transcribed, printed or by any electronic means - without specific written
* permission from  Freescale Semiconductor.
*
* Documents used in this specification:
* [R1] - 053520r16ZB_HA_PTG-Home-Automation-Profile.pdf
* [R2] - docs-07-5123-04-0afg-zigbee-cluster-library-specification.pdf
* 
* ZCL uses 3 structures to describe the attribute data associated with endpoints:
* 1. Device Definition (afDeviceDef_t)
*    Describes the device on a single endpoint. Contains a pointer to instance
*    data for that endpoint. This structure may be in ROM or RAM.
* 2. Cluster Definition (afClusterDef_t)
*    Describes the clusters for a given device. Can be used by muliple instances
*    of a device. This structure is in ROM.
* 3. Attribute Definition (zclAttrDef_t)
*    Describes the set of attributes for a cluster. Can be used by multiple
*    instances of a device. This stucture is in ROM.
* 
* Each device describes the data type, and data location. Data may be in ROM
* or RAM. For data in RAM, it takes 3 coordinates to get the actual pointer:
* 
* DeviceDef    +     ClusterDef           +      AttrDef
* ptr to instance    offset within instance      offset within cluster data
*                    of start of cluster data    to start of attribute
* 
******************************************************************************/
#ifndef _ZCL_H
#define _ZCL_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "ZclOptions.h"
#include "AfApsInterface.h"
#include "AppAfInterface.h"
#include "BeeStackInterface.h"
#include "BeeAppInit.h"
/******************************************************************************
*******************************************************************************
* Private macros & types
*******************************************************************************
******************************************************************************/


/******************************************************************************
*******************************************************************************
* Public macros & types
*******************************************************************************
******************************************************************************/
#define gZllProfileIdentifier_d         0x5E, 0xC0
#define gHAProfileIdentifier_d          0x04, 0x01


/******************************************
	General Commands
*******************************************/
typedef uint8_t zclCmd_t;
typedef uint8_t zclTSQ_t;
#define gZclCmdReadAttr_c               0x00 /* Read attributes 2.4.1 */
#define gZclCmdReadAttrRsp_c            0x01 /* Read attributes response 2.4.2 */
#define gZclCmdWriteAttr_c              0x02 /* Write attributes 2.4.3 */
#define gZclCmdWriteAttrUndivided_c     0x03 /* Write attributes undivided 2.4.4 */
#define gZclCmdWriteAttrRsp_c           0x04 /* Write attributes response 2.4.5 */
#define gZclCmdWriteAttrNoRsp_c         0x05 /* Write attributes no response 2.4.6 */
#define gZclCmdCfgReporting_c           0x06 /* Configure reporting 2.4.7 */
#define gZclCmdCfgReportingRsp_c        0x07 /* Configure reporting response 2.4.8 */
#define gZclCmdReadReportingCfg_c       0x08 /* Read reporting configuration 2.4.9 */
#define gZclCmdReadReportingCfgRsp_c    0x09 /* Read reporting configuration response 2.4.10 */
#define gZclCmdReportAttr_c             0x0a /* Report attributes 2.4.11 */
#define gZclCmdDefaultRsp_c             0x0b /* Default response command 2.4.12 */
#define gZclCmdDiscoverAttr_c           0x0c /* Discover attributes 2.4.13 */
#define gZclCmdDiscoverAttrRsp_c        0x0d /* Discover attributes response 2.4.14 */
#define gZclCmdReadAttrStructured_c     0x0e /* Read attributes structured 2.4.15 */
#define gZclCmdWriteAttrStructured_c    0x0f /* Write attributes structured 2.4.16 */
#define gZclCmdWriteAttrStructuredRsp_c 0x10 /* Write attributes structured response 2.4.17 */
#define gZclCmdDiscoverCmdReceived_c    0x11 /* Discover commands received 2.4.18 */
#define gZclCmdDiscoverCmdReceivedRsp_c 0x12 /* Discover commands received response 2.4.19  */
#define gZclCmdDiscoverCmdGenerated_c     0x13 /* Discover commands generated 2.4.20 */
#define gZclCmdDiscoverCmdGeneratedRsp_c  0x14 /* Discover commands generated response 2.4.21  */
#define gZclCmdDiscoverAttrExtended_c     0x15 /* Discover attributes extended 2.4.22 */
#define gZclCmdDiscoverAttrExtendedRsp_c  0x16 /* Discover attributes extended response 2.4.23  */

/******************************************
	cluster definitions 
*******************************************/

/* ZCL cluster IDs - note: all clusters in little endian order */
typedef uint16_t zclClusterId_t;

#if ( TRUE == gBigEndian_c )
/* The clusters ID are in OTA */
/* General Domain clusters */
#define gZclClusterBasic_c                    0x0000  /* Basic */
#define gZclClusterPowerCfg_c                 0x0100  /* Power configuration */
#define gZclClusterTemperatureCfg_c           0x0200  /* Device Temperature Configuration */
#define gZclClusterIdentify_c                 0x0300  /* Identify */
#define gZclClusterGroups_c                   0x0400  /* Groups */
#define gZclClusterScenes_c                   0x0500  /* Scenes */
#define gZclClusterOnOff_c                    0x0600  /* On/off */
#define gZclClusterOnOffCfg_c                 0x0700  /* On/off Switch Configuration */
#define gZclClusterLevelControl_c             0x0800  /* Level Control */
#define gZclClusterALarms_c                   0x0900  /* Alarms Cluster */
#define gZclClusterTime_c                     0x0a00  /* Time */
#define gZclClusterRssi_c                     0x0b00  /* RSSI - Location */
#define gZclClusterAnalogInput_c              0x0c00  /* Analog Input */
#define gZclClusterAnalogOutput_c             0x0d00  /* Analog Output */
#define gZclClusterAnalogValue_c              0x0e00  /* Analog Value */
#define gZclClusterBinaryInput_c              0x0f00  /* Binary Input */
#define gZclClusterBinaryOutput_c             0x1000  /* Binary Output */
#define gZclClusterBinaryValue_c              0x1100  /* Binary Value */
#define gZclClusterMultistateInput_c          0x1200  /* Multistate Input */
#define gZclClusterMultistateOutput_c         0x1300  /* Multistate Output */
#define gZclClusterMultistateValue_c          0x1400  /* Multistate Value */
#define gZclClusterCommissioning_c            0x1500  /* Commissioning */
#define gZclClusterPartition_c                0x1600  /* Partition */

/* Closures Domain clusters */
#define gZclClusterShadeCfg_c                 0x0001  /* Shade Configuration */
#define gZclClusterDoorLock_c                 0x0101  /* Door Lock */
#define gZclClusterWindowCovering_c           0x0201  /* Window Covering */

/* HVAC Domain Clsuters */
#define gZclClusterPumpCfg_c                  0x0002  /* Pump Configuration and Control */
#define gZclClusterThermostat_c               0x0102  /* Thermostat */
#define gZclClusterFanControl_c               0x0202  /* Fan Control */
#define gZclClusterDehumidificationControl_c  0x0203  /* Dehumidifier */
#define gZclClusterThermostatUiCfg_c          0x0402  /* Thermostat User Interface Configuration */

/* Lighting Domain Clusters */
#define gZclClusterColorControl_c             0x0003  /* Color control */
#define gZclClusterBallastConfiguration_c     0x0103  /* Ballast Configuration */

/* Measurement and sensing Domain clusters */
#define gZclClusterIlluminance_c              0x0004  /* Illuminance measurement */
#define gZclClusterIlluminanceLevel_c         0x0104  /* Illuminance level sensing  */
#define gZclClusterTemperature_c              0x0204  /* Temperature measurement  */
#define gZclClusterPressure_c                 0x0304  /* Pressure measurement  */
#define gZclClusterFlow_c                     0x0404  /* Flow measurement */
#define gZclClusterRelativeHumidity_c         0x0504  /* Relative humidity measurement */ 
#define gZclClusterOccupancy_c                0x0604  /* Occupancy sensing */

/* Security and safety Domain clusters */
#define gZclClusterIASZone_c             0x0005  /* IAS Zone IAS security zone */
#define gZclClusterIASACE_c              0x0105  /* IAS ACE IAS Ancillary Control Equipment */
#define gZclClusterIASWD_c               0x0205  /* IAS WD IAS Warning Devices. */

/* Energy@Home clusters*/ 
#define gZclClusterPowerProfile_c        0x1A00   /* Power Profile */ 
#define gZclClusterApplianceControl_c    0x1B00   /* EN50523 Appliance Control */

/* Home automation domain clusters */
#define gZclClusterApplianceIdentification_c  0x000B  /* EN50523 Appliance Identification */
#define gZclClusterMeterIdentification_c      0x010B  /* Meter Identification */
#define gZclClusterApplianceEventsAlerts_c    0x020B  /* EN50523 Appliance Events and Alerts */ 
#define gZclClusterApplianceStatistics_c      0x030B  /* Appliance Statistics */
#define gZclClusterPollControl_c              0x2000  /* Poll Control */

/* ZLL clusters */
#define gZclClusterZllCommissioning_c         0x0010  /* Zll commissioning Cluster */   
#else /* #if ( TRUE == gBigEndian_c ) */

/* General Domain clusters */
#define gZclClusterBasic_c                    0x0000  /* Basic */
#define gZclClusterPowerCfg_c                 0x0001  /* Power configuration */
#define gZclClusterTemperatureCfg_c           0x0002  /* Device Temperature Configuration */
#define gZclClusterIdentify_c                 0x0003  /* Identify */
#define gZclClusterGroups_c                   0x0004  /* Groups */
#define gZclClusterScenes_c                   0x0005  /* Scenes */
#define gZclClusterOnOff_c                    0x0006  /* On/off */
#define gZclClusterOnOffCfg_c                 0x0007  /* On/off Switch Configuration */
#define gZclClusterLevelControl_c             0x0008  /* Level Control */
#define gZclClusterALarms_c                   0x0009  /* Alarms Cluster */
#define gZclClusterTime_c                     0x000a  /* Time */
#define gZclClusterRssi_c                     0x000b  /* RSSI - Location */
#define gZclClusterAnalogInput_c              0x000c  /* Analog Input */
#define gZclClusterAnalogOutput_c             0x000d  /* Analog Output */
#define gZclClusterAnalogValue_c              0x000e  /* Analog Value */
#define gZclClusterBinaryInput_c              0x000f  /* Binary Input */
#define gZclClusterBinaryOutput_c             0x0010  /* Binary Output */
#define gZclClusterBinaryValue_c              0x0011  /* Binary Value */
#define gZclClusterMultistateInput_c          0x0012  /* Multistate Input */
#define gZclClusterMultistateOutput_c         0x0013  /* Multistate Output */
#define gZclClusterMultistateValue_c          0x0014  /* Multistate Value */
#define gZclClusterCommissioning_c            0x0015  /* Commissioning */
#define gZclClusterPartition_c                0x0016  /* Partition */

/* Closures Domain clusters */
#define gZclClusterShadeCfg_c                 0x0100  /* Shade Configuration */
#define gZclClusterDoorLock_c                 0x0101  /* Door Lock */ 
#define gZclClusterWindowCovering_c           0x0102  /* Window Covering */

/* HVAC Domain Clsuters */
#define gZclClusterPumpCfg_c                  0x0200  /* Pump Configuration and Control */
#define gZclClusterThermostat_c               0x0201  /* Thermostat */
#define gZclClusterFanControl_c               0x0202  /* Fan Control */
#define gZclClusterDehumidificationControl_c  0x0303  /* Dehumidifier */
#define gZclClusterThermostatUiCfg_c          0x0204  /* Thermostat User Interface Configuration */

/* Lighting Domain Clusters */
#define gZclClusterColorControl_c             0x0300  /* Color control */
#define gZclClusterBallastConfiguration_c     0x0301  /* Ballast Configuration */

/* Measurement and sensing Domain clusters */
#define gZclClusterIlluminance_c              0x0400  /* Illuminance measurement */
#define gZclClusterIlluminanceLevel_c         0x0401  /* Illuminance level sensing  */
#define gZclClusterTemperature_c              0x0402  /* Temperature measurement  */
#define gZclClusterPressure_c                 0x0403  /* Pressure measurement  */
#define gZclClusterFlow_c                     0x0404  /* Flow measurement */
#define gZclClusterRelativeHumidity_c         0x0405  /* Relative humidity measurement */ 
#define gZclClusterOccupancy_c                0x0406  /* Occupancy sensing */
#define gZclClusterOTA_c                      0x0019  /* Over The Air update*/

/* Security and safety Domain clusters */
#define gZclClusterIASZone_c             0x0500  /* IAS Zone IAS security zone */
#define gZclClusterIASACE_c              0x0501  /* IAS ACE IAS Ancillary Control Equipment. */
#define gZclClusterIASWD_c               0x0502  /* IAS WD IAS Warning Devices. */

/* Energy@Home clusters*/ 
#define gZclClusterPowerProfile_c       0x001A   /* Power Profile */ 
#define gZclClusterApplianceControl_c   0x001B   /* EN50523 Appliance Control */

/* Home automation domain clusters */
#define gZclClusterApplianceIdentification_c  0x0B00  /* EN50523 Appliance Identification */
#define gZclClusterMeterIdentification_c      0x0B01  /* Meter Identification */
#define gZclClusterApplianceEventsAlerts_c    0x0B02  /* EN50523 Appliance Events and Alerts */ 
#define gZclClusterApplianceStatistics_c      0x0B03  /* Appliance Statistics */
#define gZclClusterPollControl_c              0x0020  /* Poll Control */

/* ZLL clusters */
#define gZclClusterZllCommissioning_c         0x1000  /* Zll commissioning Cluster */   

#endif /* #if ( TRUE == gBigEndian_c ) */
/* cluster IDs (for endpoints... for now) */
#define gaZclClusterBasic_c                       0x00,0x00  /* Basic */
#define gaZclClusterPowerCfg_c                    0x01,0x00  /* Power configuration */
#define gaZclClusterTemperatureCfg_c              0x02,0x00  /* Device Temperature Configuration */
#define gaZclClusterIdentify_c                    0x03,0x00  /* Identify */
#define gaZclClusterGroups_c                      0x04,0x00  /* Groups */
#define gaZclClusterScenes_c                      0x05,0x00  /* Scenes */
#define gaZclClusterOnOff_c                       0x06,0x00  /* On/off */
#define gaZclClusterOnOffCfg_c                    0x07,0x00  /* On/off Switch Configuration */
#define gaZclClusterALarms_c                      0x09,0x00  /* Alarms Cluster */
#define gaZclClusterBinaryInput_c                 0x0F,0x00  /* Binary Input */
#define gaZclClusterLevelControl_c                0x08,0x00  /* Level Control */
#define gaZclClusterPartition_c                   0x16,0x00  /* Partition */
#define gaZclClusterThermostat_c                  0x01,0x02  /* Thermostat */
#define gaZclClusterFanControl_c                  0x02,0x02  /* Fan Control */
#define gaZclClusterThermostatUserInterfaceCfg_c  0x04,0x02  /* Thermostat User Interface Configuration */
#define gaZclClusterShadeCfg_c                    0x00,0x01  /* Shade Configuration */
#define gaZclClusterDoorLock_c                    0x01,0x01  /* Door Lock */
#define gaZclClusterWindowCovering_c              0x02,0x01  /* Window Covering */
#define gaZclClusterTemperatureSensor_c           0x02,0x04  /* Temperature sensor */
#define gaZclClusterOccupancySensor_c             0x06,0x04  /* Occupancy Sensor */
#define gaZclClusterCommissioning_c               0x15,0x00  /* Commissioning */
#define gaZclClusterThermostatUiCfg_c             0x04,0x02  /* Thermostat User Interface Configuration */
#define gaZclClusterTemperature_c                 0x02,0x04  /* Temperature measurement  */
#define gaZclClusterTime_c                        0x0A,0x00  /* Time */
#define gaZclClusterGeneralTunnel_c               0x00,0x06
#define gaZclCluster11073Tunnel_c                 0x14,0x06
#define gaZclClusterOTA_c                         0x19,0x00  /* Over The Air update*/
#define gaZclClusterIASZone_c                     0x00,0x05  /* IAS Zone IAS security zone */
#define gaZclClusterIASACE_c                      0x01,0x05  /* IAS ACE IAS Ancillary Control Equipment. */
#define gaZclClusterIASWD_c                       0x02,0x05  /* IAS WD IAS Warning Devices */
#define gaZclClusterPowerProfile_c                0x1A,0x00  /* Power Profile */
#define gaZclClusterApplianceControl_c            0x1B,0x00  /* EN50523 Appliance Control */
#define gaZclClusterApplianceIdentification_c     0x00,0x0B  /* EN50523 Appliance Identification */
#define gaZclClusterMeterIdentification_c         0x01,0x0B  /* Meter Identification */
#define gaZclClusterApplianceEventsAlerts_c       0x02,0x0B  /* EN50523 Appliance Events and Alerts */ 
#define gaZclClusterApplianceStatistics_c         0x03,0x0B  /* Appliance Statistics */
#define gaZclClusterPollControl_c                 0x20,0x00  /* Poll Control Cluster */  

/* Lighting Domain Clusters */
#define gaZclClusterColorControl_c                0x00, 0x03  /* Color control */
#define gaZclClusterBallastConfiguration_c        0x01, 0x03  /* Ballast Configuration */

/* ZLL clusters */
#define gaZclClusterZllCommissioning_c            0x00,0x10  /* Zll commissioning Cluster */   



/* ZCL error codes */
typedef uint8_t  zclStatus_t;
#define gZclSuccess_c                      0x00 /* operation was successful */
#define gZclFailure_c                      0x01 /* general failure */
#define gZclNoMem_c                        0x02 /* not enough memory */
#define gZclNoRsp_c                        0x03 /* no response needed flag */
#define gZclSuccessDefaultRsp_c            0x04 /* success default rsp when there is no default success status */
#define gZclMfgSpecific_c                  0x20 /* mfg specific field */
#define gZclNotAuthorized_c                0x7e /* not authorized */
#define gZclReservedFieldNotZero_c         0x7f /* reserved field contains non-zero value */
#define gZclMalformedCommand_c             0x80 /* malformed packet */
#define gZclUnsupportedClusterCommand_c    0x81 /* Not supported on the device. Command not carried out. */
#define gZclUnsupportedGeneralCommand_c    0x82 /* Not supported  */
#define gZclUnsupportedMfgClusterCommand_c 0x83 /* unknown manufacturer code. */
#define gZclUnsupportedMfgGeneralCommand_c 0x84 /* unknown manufacturer code. */
#define gZclInvalidField_c                 0x85 /* At least one field incorrect */
#define gZclUnsupportedAttribute_c         0x86 /* attribute does not exist  */
#define gZclInvalidValue_c                 0x87 /* Out of range error */
#define gZclReadOnly_c                     0x88 /* Attempt to write a read only attribute. */
#define gZclInsufficientSpace_c            0x89 /* not enough RAM   */
#define gZclDuplicateExists_c              0x8a /* duplicate already present */
#define gZclNotFound_c                     0x8b /* table entry could not be found. */
#define gZclUnreportableAttribute_c        0x8c /* attribute can be set to be reportable */
#define gZclInvalidDataType_c              0x8d /* data type given for an attribute is incorrect */
#define gZclInvalidSelector_c              0x8e /* The selector for an attribute is incorrect */
#define gZclWriteOnly_c                    0x8f /* Write only error code*/
#define gZclInconsistentStatupState_c      0x90 /* Inconsistent startup state */
#define gZclDefinedOutOfBand_c             0x91 /* attribute defined out of band */

#define gZclDontFreePacket_c               0x92 /* Used in ZCL_11073TunnelClusterServer to notify BeeApp.c not to free the packet */
#define gZclActionDenied_c                 0x93 /* action denied */    
#define gZclTimeout_c                      0x94 /* timeout */ 
#define gZclWaitForData_c                  0x97 /* Server does not have data block available yet. */

#define gZclHardwareFailure_c              0xc0 /* hardware failure. */
#define gZclSoftwareFailure_c              0xc1 /* software failure. */
#define gZclCalibrationError_c             0xc2 /* calibration failed */




/* Device enabled attributes */
#define gZclBasicAttr_DeviceEnabled        0x01; /* device is enabled */
#define gZclBasicAttr_DeviceDisabled       0x00; /* device is disabled */

/* ZCL simple types */
typedef uint8_t   zclSceneId_t;  /* (8-bit) scene identifier */
typedef uint16_t  zclAttrId_t;   /* attribute identifier, little endian */
typedef uint16_t  zclMfgId_t;    /* manufacturer identifier, little endian */

/* generic octet string type looks like this */
/* format of the date type - gZclDataTypeDate_c = 0xe1 */
typedef PACKED_STRUCT zclDate_tag
{
  uint8_t year;           /* range: 0..255 -  representing years from 1990 to 2155 */
  uint8_t month;          /* range: 1..12 - representing January to December */      
  uint8_t dayOfMonth;     /* range  1..31 */
  uint8_t dayOfWeek;      /* range  1..7 - representing Monday to Sunday */     
}zclDate_t;

typedef PACKED_STRUCT zclOctetStr_tag
{
  uint8_t length;     /* length encoded str */
  uint8_t aData[1];   /* variable length data */
} zclOctetStr_t;

typedef PACKED_STRUCT zclLongOctetStr_tag
{
  uint16_t length;    /* length encoded str */
  uint8_t aData[1];   /* variable length data */
} zclLongOctetStr_t;

/* specific string type, 5 bytes */
typedef PACKED_STRUCT zclStr05_tag
{
  uint8_t length;
  char    aStr[4];
} zclStr05_t;

/* specific string type, 9 bytes */
typedef PACKED_STRUCT zclStr09_tag
{
  uint8_t length;
  char    aStr[8];
} zclStr09_t;

/* specific string type, 10 bytes */
typedef PACKED_STRUCT zclStr10_tag
{
  uint8_t length;
  char    aStr[9];
} zclStr10_t;

/* specific string type, 32 bytes */
typedef PACKED_STRUCT zclStr32_tag
{
  uint8_t length;
  char    aStr[32];
} zclStr32_t;

/* specific string type, 33 bytes */
typedef PACKED_STRUCT zclStr33_tag
{
  uint8_t length;
  uint8_t    aStr[32];
} zclStr33_t;

/* specific string type, 17 bytes */
typedef PACKED_STRUCT zclStr17_tag
{
  uint8_t length;
  uint8_t    aStr[16];
} zclStr17_t;
/* specific string type, 16 bytes */
typedef PACKED_STRUCT zclStr16_tag
{
  uint8_t length;
  char    aStr[16];
} zclStr16_t;


typedef PACKED_STRUCT zclStr20_tag
{
  uint8_t length;
  uint8_t aStr[20];
} zclStr20_t;

typedef PACKED_STRUCT zclStr25_tag
{
  uint8_t length;
  uint8_t aStr[25];
} zclStr25_t;


/* specific octet string type, 12 bytes */
typedef PACKED_STRUCT zclStr12Oct_tag
{
  uint8_t length;
  uint8_t aStr[12];
} zclStr12Oct_t;


/* specific octet string type, 2 bytes */
typedef PACKED_STRUCT zclStr2Oct_tag
{
  uint8_t length;
  uint8_t aStr[2];
} zclStr2Oct_t;

/* specific octet string type, 6 bytes */
typedef PACKED_STRUCT zclStr6Oct_tag
{
  uint8_t length;
  uint8_t aStr[6];
} zclStr6Oct_t;


/* specific octet string type, 12 bytes */
typedef PACKED_STRUCT zclStr12_tag
{
  uint8_t length;
  uint8_t aStr[12];
} zclStr12_t;
/* specific octet string type, 16 bytes */
typedef PACKED_STRUCT zclStr16Oct_tag
{
  uint8_t length;
  uint8_t aStr[16];
} zclStr16Oct_t;
/* specific octet string type, 24 bytes */
typedef PACKED_STRUCT zclStr24Oct_tag
{
  uint8_t length;
  uint8_t aStr[24];
} zclStr24Oct_t;
/* specific octet string type, 32 bytes */
typedef PACKED_STRUCT zclStr32Oct_tag
{
  uint8_t length;
  uint8_t aStr[32];
} zclStr32Oct_t;

/* specific array type: array of uint16_t */
typedef PACKED_STRUCT zclArrayUint16_tag
{
  uint8_t  length;
  uint16_t data[16];
} zclArrayUint16_t;

/* ZCL data types */
typedef uint8_t  zclAttrType_t;   /* type of an attribute */
#define gZclDataTypeNull_c     0x00 /* no data */
#define gZclDataType8Bit_c     0x08 /* 8-bit data */
#define gZclDataType16Bit_c    0x09 /* 16-bit data */
#define gZclDataType24Bit_c    0x0a /* 24-bit data */
#define gZclDataType32Bit_c    0x0b /* 32-bit data */
#define gZclDataType40Bit_c    0x0c /* 40-bit data */
#define gZclDataType48Bit_c    0x0d /* 48-bit data */
#define gZclDataType56Bit_c    0x0e /* 56-bit data */
#define gZclDataType64Bit_c    0x0f /* 64-bit data */
#define gZclDataTypeBool_c     0x10 /* Boolean (8-bit) */
#define gZclDataTypeBitmap8_c  0x18 /* 8-bit bitmap */
#define gZclDataTypeBitmap16_c 0x19 /* 16-bit bitmap */
#define gZclDataTypeBitmap24_c 0x1a /* 24-bit bitmap */
#define gZclDataTypeBitmap32_c 0x1b /* 32-bit bitmap */
#define gZclDataTypeBitmap40_c 0x1c /* 40-bit bitmap */
#define gZclDataTypeBitmap48_c 0x1d /* 48-bit bitmap */
#define gZclDataTypeBitmap56_c 0x1e /* 56-bit bitmap */
#define gZclDataTypeBitmap64_c 0x1f /* 64-bit bitmap */
#define gZclDataTypeUint8_c    0x20 /* Unsigned 8-bit */
#define gZclDataTypeUint16_c   0x21 /* Unsigned 16-bit */
#define gZclDataTypeUint24_c   0x22 /* Unsigned 24-bit */
#define gZclDataTypeUint32_c   0x23 /* Unsigned 32-bit */
#define gZclDataTypeUint40_c   0x24 /* Unsigned 40-bit */
#define gZclDataTypeUint48_c   0x25 /* Unsigned 48-bit */
#define gZclDataTypeUint56_c   0x26 /* Unsigned 56-bit */
#define gZclDataTypeUint64_c   0x27 /* Unsigned 64-bit */
#define gZclDataTypeInt8_c     0x28 /* Signed 8-bit */
#define gZclDataTypeInt16_c    0x29 /* Signed 16-bit */
#define gZclDataTypeInt24_c    0x2a /* Signed 24-bit */
#define gZclDataTypeInt32_c    0x2b /* Signed 32-bit */
#define gZclDataTypeInt40_c    0x2c /* Signed 40-bit */
#define gZclDataTypeInt48_c    0x2d /* Signed 48-bit */
#define gZclDataTypeInt56_c    0x2e /* Signed 56-bit */
#define gZclDataTypeInt64_c    0x2f /* Signed 64-bit */
#define gZclDataTypeEnum8_c    0x30 /* 8-bit enumeration */
#define gZclDataTypeEnum16_c   0x31 /* 16-bit enumeration */
#define gZclDataTypeSemi_c     0x38 /* Semi-precision 2-bytes */
#define gZclDataTypeSingle_c   0x39 /* Single precision 4-bytes */
#define gZclDataTypeDouble_c   0x3a /* Double precision 8-bytes */
#define gZclDataTypeOctetStr_c 0x41 /* Octet string */
#define gZclDataTypeStr_c      0x42 /* Character string */
#define gZclDataTypeLongOctetStr_c  0x43 /* Long Octet string */
#define gZclDataTypeLongStr_c  0x44 /* Long Character string */
#define gZclDataTypeArray_c    0x48 /* Array */
#define gZclDataTypeStruct_c   0x4c /* Structure */
#define gZclDataTypeSet_c      0x50 /* Set */
#define gZclDataTypeBag_c      0x51 /* Bag */
#define gZclDataTypeTime_c     0xe0 /* Time of day  4-byte */
#define gZclDataTypeDate_c     0xe1 /* Date 4-byte */
#define gZclDataTypeUTCTime_c  0xe2 /* UTC Time */
#define gZclDataTypeCluster_c  0xe8 /* Cluster ID 2-byte */
#define gZclDataTypeAttr_c     0xe9 /* Attribute ID 2-byte */
#define gZclDataTypeBACnet_c   0xea /* BACnet OID 4-byte */
#define gZclDataTypeIeeeAddr_c 0xf0 /* IEEE address 8-byte */
#define gZclDataTypeSecurityKey_c 0xf1 /* 128-bit Security key */

/* Attribute Access Control field */
typedef uint8_t  zclAttrAccessCtrl_t;   
#define gZclAttrReadable_c     1<<0 /* readeble */
#define gZclAttrWriteable_c    1<<1 /* writeable */
#define gZclAttrReportable_c   1<<2 /* reportable */

/******************************************
	ZCL Command Frames
*******************************************/

/* [R2] 7.1.1 Read attributes command frame format */
typedef  PACKED_STRUCT  zclCmdReadAttr_tag
{
  zclAttrId_t  aAttr[1];   /* varPACKED_STRUCTlength array of attributes */
} zclCmdReadAttr_t;

/* [R2] - Figure 6 � Format of the read attributes status record field */
typedef PACKED_STRUCT zclCmdReadAttrRspRecord_tag
{
  zclAttrId_t    attrId;   /* attribute id */
  zclStatus_t    status;   /* worked or failed */
  zclAttrType_t  attrType; /* attribute type */
  uint8_t       aData[1];  /* variable length attribute data */
} zclCmdReadAttrRspRecord_t;

/* returned if error on that read attribute command */
typedef PACKED_STRUCT zclCmdReadAttrRspError_tag
{
  zclAttrId_t  attrId;
  zclStatus_t  status;
} zclCmdReadAttrRspError_t;

/* [R2] 7.2 Read attributes response command */
typedef PACKED_STRUCT zclCmdReadAttrRsp_tag
{
  zclCmdReadAttrRspRecord_t aRsp[1];  /* variable # of response records */
} zclCmdReadAttrRsp_t;

/* [R2] Figure 8 � OTA Format of the write attribute record field */
typedef PACKED_STRUCT zclCmdWriteAttrRecord_tag
{
  zclAttrId_t   attrId;       /* attribute id */
  zclAttrType_t attrType;     /* attribute type */ 
  uint8_t       aData[4];     /* variable length data */
} zclCmdWriteAttrRecord_t;

/* [R2] 7.3.1 Internal Write attributes command frame format */
typedef PACKED_STRUCT zclCmdWriteAttr_tag
{
  zclAttrId_t   attrId;
  zclAttrType_t attrType;  
  uint8_t      attrLen;    /* length, so the request knows how much to copy */
  uint8_t       aData[4];   /* up to 4 bytes data */
} zclCmdWriteAttr_t;

/* write response record (only used in error case, with a success, only has the status of 0) */
typedef PACKED_STRUCT zclCmdWriteAttrRspRecord_tag
{
  zclStatus_t  status;
  zclAttrId_t  attrId;
} zclCmdWriteAttrRspRecord_t;

/* write response */
typedef PACKED_STRUCT zclCmdWriteAttrRsp_tag
{
  zclCmdWriteAttrRspRecord_t aRsp[1];  /* variable # of response records */
} zclCmdWriteAttrRsp_t;

/* default response */
typedef PACKED_STRUCT zclCmdDefaultRsp_tag
{
  zclCmd_t    cmd; 
  zclStatus_t status;
} zclCmdDefaultRsp_t;


typedef PACKED_STRUCT zclCmdDiscoverAttr_tag
{
  zclAttrId_t  startAttr;  /* start attribute identifier */
  uint8_t      maxAttrIds; /* maximum attribute ids to be reported */
} zclCmdDiscoverAttr_t;


typedef PACKED_STRUCT zclCmdDiscoverAttrRspRecord_tag 
{
  zclAttrId_t   attrId;
  zclAttrType_t attrType; 
} zclCmdDiscoverAttrRspRecord_t;

typedef PACKED_STRUCT zclCmdDiscoverAttrRspHeader_tag 
{
  uint8_t discoveryComplete;
} zclCmdDiscoverAttrRspHeader_t;

typedef PACKED_STRUCT zclCmdDiscoverAttrRsp_tag
{
  zclCmdDiscoverAttrRspHeader_t header;
  zclCmdDiscoverAttrRspRecord_t aRsp[1];
} zclCmdDiscoverAttrRsp_t;

#define zclDiscoverAttrComplete    1
#define zclDiscoverAttrNotComplete 0


typedef PACKED_STRUCT zclCmdDiscoverAttrExtendedRspRecord_tag 
{
  zclAttrId_t             attrId;
  zclAttrType_t           attrType; 
  zclAttrAccessCtrl_t     attrAccessCtrl;           
} zclCmdDiscoverAttrExtendedRspRecord_t;

typedef PACKED_STRUCT zclCmdDiscoverAttrExtendedRsp_tag
{
  zclCmdDiscoverAttrRspHeader_t header;
  zclCmdDiscoverAttrExtendedRspRecord_t aRsp[1];
} zclCmdDiscoverAttrExtendedRsp_t;


typedef PACKED_STRUCT zclCmdDiscoverCommands_tag
{
  uint8_t   startCmd;  /* start command identifier */
  uint8_t   maxCmdIds; /* maximum command ids to be reported */
} zclCmdDiscoverCommands_t;

typedef PACKED_STRUCT zclCmdDiscoverCommandsRsp_tag
{
  uint8_t discoveryComplete;
  uint8_t cmdId[1];
} zclCmdDiscoverCommandsRsp_t;

/* reportable attributes need 3 copies: current value, report change, and last value */
#define zclReportableCopies_c       3
#define zclReportValueIndex_c       0 /* current value */
#define zclReportOldValueIndex_c    1 /* last reported value */
#define zclReportChangeIndex_c      2 /* change value (e.g. +/- 5) */

/* attribute report to server (direction 0x00) */
typedef PACKED_STRUCT zclCmdReportingCfgServerRecord_tag
{
  uint8_t       direction;            /* must be 0=to server */
  zclAttrId_t   attrId;               /* attribute ID */
  zclAttrType_t attrType;             /* attribute type */
  uint16_t      minReportingInterval; /* internval (in seconds) min before reporting */
  uint16_t      maxReportingInterval; /* internval (in seconds) max before reporting */
  uint8_t       aReportableChange[1]; /* variable length (depends on attr), change in value */
} zclCmdReportingCfgServerRecord_t;

/* attribute report to server (direction 0x00) */
typedef PACKED_STRUCT zclCmdReportingCfgServer_tag
{
  uint8_t       direction;            /* must be 0=to server */
  zclAttrId_t   attrId;               /* attribute ID */
  zclAttrType_t attrType;             /* attribute type */
  uint16_t      minReportingInterval; /* min interval (in seconds) before reporting */
  uint16_t      maxReportingInterval; /* max interval (in seconds) before reporting */
  uint8_t      attrLen;              /* length so request knows how much to copy */
  uint8_t       aReportableChange[8]; /* must be little endian, and same type as attr */
} zclCmdReportingCfgServer_t;


/* report to client (direction 0x01) */
typedef PACKED_STRUCT zclCmdReportingCfgClientRecord_tag
{
  uint8_t     direction;       /* must be 1=to client */
  zclAttrId_t attrId;          /* attribute ID */
  uint16_t    timeoutPeriod;   /* in seconds */
} zclCmdReportingCfgClientRecord_t;

/* reporting configuration */
typedef union zclCmdReportingCfg_tag
{
  zclCmdReportingCfgServer_t        server;
  zclCmdReportingCfgClientRecord_t  client;
} zclCmdReportingCfg_t;

#define gZclReportingTimeOff_c 0x0000  /* turn min/max time reporting */

/* 
  reporting configuration response record
  note: only failure statuses are reported. if all configurations worked, only a single 
  status of success is returned with no attrId.
*/
typedef PACKED_STRUCT zclCmdReportCfgRsp_tag
{
  zclStatus_t  status;
  uint8_t      direction; 
  zclAttrId_t  attrId;
} zclCmdReportCfgRsp_t;

/*
  A report record for reporting attributes
*/
typedef PACKED_STRUCT zclCmdReportAttr_tag
{
  zclAttrId_t   attrId;      /* attribute ID */
  zclAttrType_t attrType;    /* attribute type */  
  uint8_t       aData[1];    /* variable length data */  
} zclCmdReportAttr_t;

/* frame control field */
typedef uint8_t zclFrameControl_t;
#define gZclFrameControl_FrameTypeMask     0x03  /* mask to see which type */
#define gZclFrameControl_FrameTypeGeneral  0x00  /* general across whole profile */
#define gZclFrameControl_FrameTypeSpecific 0x01  /* specific to cluster */
#define gZclFrameControl_MfgSpecific       0x04  /* manufacturer specific command */
#define gZclFrameControl_DirectionRsp      0x08  /* set for responses (not for requests) */
#define gZclFrameControl_DisableDefaultRsp 0x10  /* disable default response */

/* Direction for setting attributes */
#define gZclServerAttr_c     0x00
#define gZclClientAttr_c     0x08

/* Direction for commands */
#define gZclCmdReceived_c      0x00
#define gZclCmdGenerated_c     0x01   

/* home automation frame */
typedef PACKED_STRUCT zclFrame_tag
{
  zclFrameControl_t  frameControl;
  uint8_t            transactionId;
  zclCmd_t           command;
}zclFrame_t;

/* home automation manufacturer specific frame */
typedef PACKED_STRUCT zclMfgFrame_tag
{
  zclFrameControl_t  frameControl;
  zclMfgId_t         mfgId;
  uint8_t            transactionId;
  zclCmd_t           command;
} zclMfgFrame_t;

/* manufacturer specific frame */
#define ZCL_IsMfgSpecificFrame(frameControl) ((frameControl) & gZclFrameControl_MfgSpecific)

/******************************************
	ZCL Internal Types (implementation specific)
*******************************************/

/* maximum clusters in a single list */
#define gZclMaxClusters_c 32

/* list of commands */
typedef PACKED_STRUCT zclCmdList_tag
{
  uint8_t     count;    /* # of commands */
  zclCmd_t    *pCmds;   /* ptr to array of commands */
} zclCmdList_t;

/* each string type is represented as this structure. If writable, will be in RAM. */
typedef PACKED_STRUCT zclStrType_tag
{
  uint8_t iCurrentLen;
  uint8_t *pData;
} zclStrType_t;

/* attribute flags, choose 1 of: InROM, InLine, Common, InRAM. RdOnly and Reportable are modifiers */
typedef uint16_t zclAttrFlags_t;
#define gZclAttrFlagsInROM_c          0x0080  /* in ROM only (not in RAM) (implies RdOnly, strings are C encoded) */
#define gZclAttrFlagsInLine_c         0x0040  /* attribute is in-line in ROM (not pointed to) */
#define gZclAttrFlagsCommon_c         0x0020  /* in RAM, stared among endpoints */
#define gZclAttrFlagsInRAM_c          0x0010  /* in the RAM data set (one per endpooint), not reportable */
#define gZclAttrFlagsRdOnly_c         0x0008  /* in RAM, but attribute is read only (defaults to RD/WR) */
#define gZclAttrFlagsReportable_c     0x0004  /* Can this attribute be reported? (also add to reportable list) */
#define gZclAttrFlagsInSceneTable_c   0x0002  /* is this attribute in the scene table extension list for the cluster */
#define gZclAttrFlagsInSceneData_c    0x0001  /* is this attribute pointed by pSceneData instead of pData */
#define gZclAttrFlagsNoFlags_c        0x0000  /* no flags used*/ 

#define gZclAttrFlagsWrOnly_c              0x0100
#define gZclAttrFlagsDefinedOutOfBand_c    0x0200
#define gZclAttrFlagsIsVector_c            0x0400
#define gZclAttrFlagsApsLinkKeySecurityRequired_c 0x0800

/*ZCL code will not read the variable and send the response automaticly, it must be done by the application */
#define gZclAttrFlagsAsynchronous_c 0x1000
#define gZclAttrFlagsIsClientAttribute_c 0x2000

#define gZclAttrFlagsInRAMClient_c              gZclAttrFlagsInRAM_c | gZclAttrFlagsIsClientAttribute_c 
#define gZclAttrFlagsClientRdOnly_c             gZclAttrFlagsRdOnly_c | gZclAttrFlagsIsClientAttribute_c 
#define gZclAttrFlagsInRAMRdOnly_c              gZclAttrFlagsInRAM_c | gZclAttrFlagsRdOnly_c
#define gZclAttrFlagsInRAMClientRdOnly_c        gZclAttrFlagsInRAM_c | gZclAttrFlagsRdOnly_c | gZclAttrFlagsIsClientAttribute_c 

/* test is this attribute is asynchronous */
#define ZclAttrIsAsynchronous_c(flags) ((flags) & gZclAttrFlagsAsynchronous_c)

/* test if attribute is read only */
#define ZclAttrIsReadOnly(flags) ((flags) & (gZclAttrFlagsRdOnly_c | gZclAttrFlagsInROM_c | gZclAttrFlagsInLine_c))

/* test if attribute is Write only */
#define ZclAttrIsWriteOnly(flags) ((flags) & (gZclAttrFlagsWrOnly_c))

/* test if attribute is Out of Band */
#define ZclAttrIsDefinedOutOfBand(flags) ((flags) & (gZclAttrFlagsDefinedOutOfBand_c))

/* test if ther is a vector of attributes */
#define ZclAttrIsVector(flags) ((flags) & gZclAttrFlagsIsVector_c)

/* test if the attribute is inline */
#define ZclAttrIsInLine(flags) ((flags) & gZclAttrFlagsInLine_c)

/* test if the attr data points to the item */
#define ZclAttrIsPtr(flags) ((flags) & (gZclAttrFlagsInROM_c | gZclAttrFlagsCommon_c))

/* is an instance type varible (uses instance data) */
#define ZclAttrIsInstance(flags) ((flags) & gZclAttrFlagsInRAM_c)

/* is this attribute reportable? */
#define ZclAttrIsReportable(flags) ((flags) & gZclAttrFlagsReportable_c)

/* is this attribute in the scene table extension list? */
#define ZclAttrIsInSceneTable(flags) ((flags) & gZclAttrFlagsInSceneTable_c)

/* is this attribute pointed bt pSceneData instead of pData  */
#define ZclAttrIsInSceneData(flags) ((flags) & gZclAttrFlagsInSceneData_c)

/* is this attribute a client attribute  */
#define ZclAttrIsOnClient(flags) ((flags) & gZclAttrFlagsIsClientAttribute_c)


typedef PACKED_UNION zclAttrData_tag
{
  void      *pData;     /* for common RAM on in-ROM (gZclAttrFlagsInROM_c) (gZclAttrFlagsCommon_c) */
  uint16_t   data16;    /* 16-bit ROM data (gZclAttrFlagsInLine_c) */
  uint8_t    data8;     /* 8-bit ROM data (gZclAttrFlagsInLine_c) */
  uint16_t   offset;    /* offset within cluster's data structure of field (gZclAttrFlagsInRAM_c) */
} zclAttrData_t;

/*
  ZCL Attribute Definition

  This structure will reside in ROM(Flash). And describes a single attribute. 
  It does NOT describe an instance of that attribute. That will be defined by 
  the profile (eg. HA).
  
  Each cluster constains a list of of 0 or more attributes.*/

typedef PACKED_STRUCT zclAttrDef_tag
{
  index_t    id;          /* attribute ID, cluster specific */
  zclAttrType_t  type;     /* attribute type (see 8.2 in ZCL Foundation) */
  zclAttrFlags_t flags;    /* attribute flags */
  uint8_t        size;      /* no of similar entries for vector types or max length for strings */
  zclAttrData_t   data;       /* ptr to data, or the data itself or offset */
} zclAttrDef_t;

/* a list of attributes. This sructure is in ROM. */
typedef PACKED_STRUCT zclAttrDefList_tag
{
  uint8_t       count;      /* # of items in the attribute list */
  zclAttrDef_t const *pAttrDef;   /* ptr to array of attributes */
} zclAttrDefList_t;

typedef PACKED_STRUCT zclAttrSet_tag
{
  index_t    id;       /* attribute ID, cluster specific */
  zclAttrDef_t const *pAttrDefList;   /* ptr to array of attribute sets */
  uint8_t size;
} zclAttrSet_t;

/* a list of attributes. This sructure is in ROM. */
typedef PACKED_STRUCT zclAttrSetList_tag
{
  uint8_t       count;      /* # of items in the attribute sets list */
  zclAttrSet_t const *pAttrSet;   /* ptr to array of attribute sets */
} zclAttrSetList_t;



typedef PACKED_STRUCT zclCommandsDefList_tag
{
  uint8_t              countReceived;             /* # of items in the commands received def list */
  zclCmd_t     const  *pCommandReceivedDef;       /* ptr to array of command received sets */
  uint8_t              countGenerated;            /* # of items in the commands generated def list */
  zclCmd_t     const  *pCommandGeneratedDef;      /* ptr to array of commands generated sets */
}zclCommandsDefList_t;



/* sent to the application to update the user interface */
typedef uint8_t zclUIEvent_t;
enum {
  gZclUI_NoEvent_c=0,                           /* no event */
  gZclUI_Disable_c = gAppEvent_End_c,           /* disable device */
  gZclUI_Enable_c,                              /* enable device */
  gZclUI_Off_c,                                 /* turn off light/device */
  gZclUI_On_c,                                  /* turn on light/device */
  gZclUI_IdentifyOff_c,                         /* turn off identify */
  gZclUI_IdentifyOn_c,                          /* turn on identify */
  gZclUI_GoToLevel_c,                           /* set the level of the level device */
  gZclUI_AddedToGroup_c,                        /* when a node is added to a group */
  gZclUI_IdentifyQueryRsp_c,                    /* got identify query response */
  gZclUI_ThermostatRaiseSetpoint_c,             /*Thermostat Raise Setpoin*/
  gZclUI_ThermostatLowerSetpoint_c,             /*Thermostat Raise Setpoin*/
  gZclUI_TempSensingTemperatureRaise_c,         /*Temperature Raise*/
  gZclUI_TempSensingTemperatureLower_c,         /*Temperature Lower*/
  gZclUI_LocalTemperatureChange_c,
  gZclUI_TurnCoolingOn_c,
  gZclUI_TurnHeatingOn_c,
  gZclUI_TurnCoolingOff_c,
  gZclUI_TurnHeatingOff_c,
  gZclUI_SendWriteAttributeRequest_c,
  gZclUI_WriteAttributeSuccess_c,
  gZclUI_SendReadAttributeRequest_c,    
  gZclUI_SendReportingAttributeRequest_c,
  gZclUI_KeyEstabSuccesful_c,
  gZclUI_KeyEstabFailed_c,
  gZclUI_KeyEstabTimeout_c,
  gZclUI_MsgDisplayMessageReceived_c,
  gZclUI_MsgCancelMessageReceived_c,
  gZclUI_MsgGetLastMessageReceived_c,
  gZclUI_MsgMessageConfirmReceived_c,
  gZclUI_MsgUpdateTimeInDisplay_c,
  gZclUI_LdCtrlEvt_c,
  gZclUI_PriceEvt_c,
  gZclUI_BlockPeriodEvt_c,
  gZclUI_TariffInformationEvt_c,
  gZclUI_PriceMatrixEvt_c,
  gZclUI_BlockThresholdsEvt_c,
  gZclUI_BillingPeriodEvt_c,
  gZclUI_CPPEvt_c,
  gZclUI_ConsolidatedBillEvt_c,
  gZclUI_CO2ValueEvt_c,
  gZclUI_ZCLResponse_c,
  gZclUI_SEServiceDiscoveryCompleted_c,
  gZclUI_SEReadyState,
  gZclUI_Lock_c,                       /* lock the door/device */
  gZclUI_Unlock_c,                     /* unlock the door/device */
  gZclUI_EnrollSuccesfull_c,           /* enroll succesfull IASZone*/
  gZclUI_EnrollFailed_c,               /* enroll failed IASZone*/ 
  gZclUI_ChangeNotification,           /* change notification IASZone*/
  gZclUI_StartWarning_c,                /* start warning device */
  gZclUI_StartStrobe_c,                 /* start strobe lighting device */  
  gZclUI_StartWarningStrobe_c,          /* start warning and strobe lighting */
  gZclUI_Squawk_c,                      /* Squawk event */
  gZclUI_AlarmGenerate_c,                /* Alarms(cluster) event */
  gZclUI_SETunnel_RequestTunnelReqReceived_c,
  gZclUI_SETunnel_TransferDataIndication_c,
  gZclUI_SETunnel_TransferDataErrorReceived_c,
  gZclUI_SETunnel_SupportedTunnelProtocolsRspReceived_c,
  gZclUI_FastPollReqRcv_c,
  gZclUI_MirroringReadPhyEnvironment_c,
  gZclUI_SEPrepayment_ChangePaymentModeReq_c,
  gZclUI_SEPrepayment_GetPrepaySnapshotReq_c,
  gZclUI_SEPrepayment_GetTopUpLogReq_c,
  gZclUI_SEPrepayment_SetLowCreditWarningLevelReq_c,
  gZclUI_SEPrepayment_GetDebtRepaymentLog,
  gZclUI_SEMetering_MirrorCreated,
  gZclUI_SEMetering_EnterAwakeState,
  gZclUI_CreditPaymentEvt_c,
  gZclUI_CurrencyConversionEvt_c,
  gZclUI_EZCommissioning_FindingAndBinding_c,
  gZclUI_EZCommissioning_Succesfull_c,
  gZclUI_EventEnd_c                             /* used to initialize the next set of system events */
};

enum {
/* 10.2.2.1.1 Temperature display mode values */
    gZclDisplayMode_TempCelsius_c = 0x00, /* Temperature in Celsius */
    gZclDisplayMode_TempFahrenheit_c = 0x01 /* Temperature in Fahrenheit */
};

/* rd/wr attribute data for scenes */
typedef PACKED_STRUCT zclSceneAttrs_tag
{
  uint8_t       sceneCount;   /* # of active elements in scene table */
  zbGroupId_t   currentGroup; /* current group */
  zclSceneId_t  currentScene; /* current scene */
  uint8_t       sceneValid;   /* is this currently a valid scene? */
#if gZclClusterOptionals_d
  zbIeeeAddr_t  lastConfiguredBy;
#endif
  uint8_t       sceneTableEntrySize; /* size of a single entry in the scene table */
}zclSceneAttrs_t;

/* each element in the scene table looks like this */
typedef PACKED_STRUCT zclSceneTableEntry_tag
{
  zbGroupId_t   aGroupId;         /* group ID */
  zclSceneId_t  sceneId;          /* scene ID */
  uint16_t      transitionTime;   /* in seconds */
#if gZclIncludeSceneName_d
  char          szSceneName[17];  /* scene name */
#endif
#if gASL_EnableZLLClustersData_d  
  uint8_t       transitionTime100ms; /* valid range 0x00 - 0x09,  Together with the scene transition time element, 
                                        this allows the transition time to be specified in tenths of a second*/
#endif   
} zclSceneTableEntry_t;

enum {
  gZclSceneInvalid_c  = 0x00,
  gZclSceneValid_c  = 0x01
};


/******************************************************************************
*******************************************************************************
* Public data
*******************************************************************************
******************************************************************************/

/* standard options for sending data */
extern zbApsTxOption_t const gZclTxOptions;

/* for read/write/report attribute commands */
extern const zclAttrSetList_t gZclBasicClusterAttrSetList;
extern const zclAttrSetList_t gZclPowerCfgClusterAttrSetList; 
extern const zclAttrDefList_t gZclTemperatureCfgClusterAttrSefList;
extern const zclAttrSetList_t gZclIdentifyClusterAttrSetList;
extern const zclAttrSetList_t gZclGroupClusterAttrSetList;
extern const zclAttrSetList_t gZclSceneClusterAttrSetList;
extern const zclAttrSetList_t gZclOnOffClusterAttrSetList;
extern const zclAttrSetList_t gZclBinaryInputClusterAttrSetList;
extern const zclAttrSetList_t gZclLevelCtrlClusterAttrSetList;
extern const zclAttrSetList_t gZclOnOffSwitchConfigureClusterAttrSetList;
extern const zclAttrSetList_t gZclAlarmsClusterAttrSetList;
extern const zclAttrSetList_t gZclThermostatClusterAttrSetList;
extern const zclAttrSetList_t gZclFanControlClusterAttrSetList;
extern const zclAttrSetList_t gZclThermostatUICfgClusterAttrSetList;
extern const zclAttrSetList_t gZclTemperatureMeasurementClusterAttrSetList;
extern const zclAttrSetList_t gZclOccupancySensingClusterAttrSetList;
extern const zclAttrSetList_t gZclDoorLockClusterAttrSetList;
extern const zclAttrSetList_t gZclShadeCfgClusterAttrSetList;
extern const zclAttrSetList_t gZclWindowCoveringClusterAttrSetList;
extern const zclAttrSetList_t gZclIASZoneClusterAttrSetList;
extern const zclAttrSetList_t gZclIASWDClusterAttrSetList;
extern const zclAttrSetList_t gZclOTAClusterAttrSetList;
extern const zclAttrSetList_t gZclBasicClusterMirrorAttrSetList;
extern const zclAttrSetList_t gZclPowerProfileClusterAttrSetList;
extern const zclAttrSetList_t gZclApplianceControlClusterAttrSetList;
extern const zclAttrSetList_t gZclApplianceStatisticsClusterAttrSetList;
extern const zclAttrSetList_t gZclApplianceIdentificationClusterAttrSetList;
extern const zclAttrSetList_t gZclMeterIdentificationClusterAttrSetList;
extern const zclAttrSetList_t gZclPollControlClusterAttrSetList;
extern const zclAttrSetList_t gZclColorCtrlClusterAttrSetList;

/* commands def */
extern const  zclCommandsDefList_t gZclPowerProfileClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclApplianceControlClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclApplianceStatisticsClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclApplianceEventsAlertClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclPartitiontClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclPollControlClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclIdentifyClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclOnOffClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclGroupClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclSceneClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclLevelCtrlClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclOTAClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclAlarmsClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclThermostaClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclIASZoneClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclIASACEClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclIASWDClusterCommandsDefList;
extern const  zclCommandsDefList_t gZclWindowCoveringClusterCommandsDefList;
extern const zclCommandsDefList_t gZclDoorLockClusterCommandsDefList;
extern const zclCommandsDefList_t gZclColorCtrlClusterCommandsDefList;

extern const zclCommandsDefList_t gZclZllCommissioningClusterCommandsDefList;
extern const zclCommandsDefList_t gaZclGeneralTunelClusterCommandsDefList;
extern const zclCommandsDefList_t gaZcl11073TunnelClusterCommandsDefList;

/* timers used by ZCL */

/* attribute definitions (used by cluster definitions) */
extern const zclAttrDefList_t gZclOnOffClusterAttrDefList;

/* for controlling ZCL state machine */
extern tsTaskID_t gZclTaskId;
#if gZclEnableReporting_c
#endif
/* transaction ID */


/******************************************************************************
*******************************************************************************
* Public prototypes
*******************************************************************************
******************************************************************************/

/* resets ZCL profile, turning off timers, etc... use when resetting stack */
void ZCL_Reset(void);
void ZCL_Init(void);
void InitZtcForZcl(void);
void ZCL_ResetDevice(afDeviceDef_t *pDevice);

/******************************************
	Public Interface To Requests
*******************************************/

/* read attribute request */
typedef PACKED_STRUCT zclReadAttrReq_tag
{
  afAddrInfo_t      addrInfo;     /* IN: source/dst address, cluster, etc... */
  uint8_t           count;        /* IN: how many to read? */
  zclCmdReadAttr_t  cmdFrame;     /* IN: read attribute command frame */
} zclReadAttrReq_t;

/* write attribute request */
typedef PACKED_STRUCT zclWriteAttrReq_tag
{
  afAddrInfo_t        addrInfo;     /* IN: source/dst address, cluster, etc... */
  uint8_t             reqType;      /* IN: write request type (write = 2, undivided=3, norsp=5) */
  uint8_t             count;        /* IN: how many records to write? */
  zclCmdWriteAttr_t   aCmdFrame[1]; /* IN: array of variable length command frames */
} zclWriteAttrReq_t;

/* discover attributes request */
typedef PACKED_STRUCT zclDiscoverAttrReq_tag
{
  afAddrInfo_t         addrInfo;     /* IN: source/dst address, cluster, etc... */
  zclCmdDiscoverAttr_t cmdFrame;     /* IN: discover attributes request command */
} zclDiscoverAttrReq_t;

/* discover attributes request */
typedef PACKED_STRUCT zclDiscoverAttrExtendedReq_tag
{
  afAddrInfo_t         addrInfo;     /* IN: source/dst address, cluster, etc... */
  uint8_t              direction;    /* IN: from client of server */
  zclCmdDiscoverAttr_t cmdFrame;     /* IN: discover attributes request command */
} zclDiscoverAttrExtendedReq_t;

/* discover attributes extended of another node */
#if gZclDiscoverAttrExtendedReq_d
zclStatus_t ZCL_DiscoverAttrExtendedReq
  (
  zclDiscoverAttrExtendedReq_t *pReq
  );  
#else
#define ZCL_DiscoverAttrExtendedReq(pReq) FALSE
#endif 

typedef PACKED_STRUCT zclDiscoverCommandsReq_tag
{
  afAddrInfo_t              addrInfo;     /* IN: source/dst address, cluster, etc... */
  uint8_t                   direction;    /* IN: from client to server or server to client */
  uint8_t                   commandId;    /* IN: commandId: Received(0x11)/Generated(0x13) */
  zclCmdDiscoverCommands_t  cmdFrame;     /* IN: discover commands request command */
} zclDiscoverCommandsReq_t;

#if gZclDiscoverCommandsReg_d
zclStatus_t ZCL_DiscoverCommandsReq
  (
  zclDiscoverCommandsReq_t *pReq
  );  
#else
#define ZCL_DiscoverCommandsReq(pReq) FALSE
#endif


/* read attribute request */
typedef PACKED_STRUCT zclReadAttrDirectedReq_tag
{
  afAddrInfo_t      addrInfo;     /* IN: source/dst address, cluster, etc... */
  uint8_t           direction;    /* IN: from client of server */    
  uint8_t           count;        /* IN: how many to read? */
  zclCmdReadAttr_t  cmdFrame;     /* IN: read attribute command frame */
} zclReadAttrDirectedReq_t;

/* write attribute request */
typedef PACKED_STRUCT zclWriteAttrDirectedReq_tag
{
  afAddrInfo_t        addrInfo;     /* IN: source/dst address, cluster, etc... */
  uint8_t             direction;    /* IN: from client of server */     
  uint8_t             reqType;      /* IN: write request type (write = 2, undivided=3, norsp=5) */
  uint8_t             count;        /* IN: how many records to write? */
  zclCmdWriteAttr_t   aCmdFrame[1]; /* IN: array of variable length command frames */
} zclWriteAttrDirectedReq_t;

/* discover attributes request */
typedef PACKED_STRUCT zclDiscoverAttrDirectedReq_tag
{
  afAddrInfo_t         addrInfo;     /* IN: source/dst address, cluster, etc... */
  uint8_t             direction;    /* IN: from client of server */
  zclCmdDiscoverAttr_t cmdFrame;     /* IN: discover attributes request command */
} zclDiscoverAttrDirectedReq_t;


/* configure reporting request*/
typedef PACKED_STRUCT zclConfigureReportingReq_tag
{
  afAddrInfo_t          addrInfo;   /* IN: source/dst address, cluster, etc... */
  uint8_t               count;      /* IN: how many records to configure? */
  zclCmdReportingCfgServer_t aCmdFrame[1];  /* IN: request command frame */
} zclConfigureReportingReq_t;

/* read reporting configuration request payload */
typedef PACKED_STRUCT zclCmdReadReportingCfgRecord_tag 
{
  uint8_t       direction;
  zclAttrId_t   attrId;  
}zclCmdReadReportingCfgRecord_t;


/* read reporting configuration request*/
typedef PACKED_STRUCT zclReadReportingCfgReq_tag
{
  afAddrInfo_t                       addrInfo;     /* IN: source/dst address, cluster, etc... */
  uint8_t                            count;        /* IN: how many records to configure? */
  zclCmdReadReportingCfgRecord_t     aCmdFrame[1]; /* IN: array of variable length command frames */
}zclReadReportingCfgReq_t;

typedef PACKED_STRUCT zclCmdReadReportCfg_Reported_tag
{
  uint8_t       attrDataType;
  uint16_t      minReportInterval;
  uint16_t      maxReportInterval; 
  uint8_t       reportableChange[1];
}zclCmdReadReportCfg_Reported_t;

typedef PACKED_STRUCT zclCmdReadReportCfg_Received_tag
{
  uint16_t       timeoutPeriod;  
}zclCmdReadReportCfg_Received_t;


/* read reporting configuration response payload */
typedef PACKED_STRUCT zclCmdReadReportingCfgRspRecord_tag 
{
  uint8_t       status;
  uint8_t       direction;
  zclAttrId_t   attrId;
  union {
    zclCmdReadReportCfg_Reported_t     reported; /* Valid when the direction field  is 0x00 */
    zclCmdReadReportCfg_Received_t     received; /* Valid when the direction field  is 0x01 */
  } recordData;
}zclCmdReadReportingCfgRspRecord_t;


/* read reporting configuration response */
typedef PACKED_STRUCT zclReadReportingCfgRsp_tag
{
  afAddrInfo_t                          addrInfo;     /* IN: source/dst address, cluster, etc... */
  uint8_t                               count;        /* IN: how many records to configure? */
  zclCmdReadReportingCfgRspRecord_t     aCmdFrame[1]; /* IN: array of variable length command frames */
}zclReadReportingCfgRsp_t;


/*
  Each reportable attribute shall be listed with the HA device definition. Listed here 
  because the ZCL routines need access to reportable attributes.
*/
typedef PACKED_STRUCT zclReportAttr_tag
{
  zbClusterId_t   aClusterId; /* little endian cluster */
  zclAttrId_t     attrId;     /* little endian attribute  */
} zclReportAttr_t;

/* used for generic requests */
typedef PACKED_STRUCT zclGenericReq_tag
{
  afAddrInfo_t            addrInfo;   /* IN: address info (cluster, dest, etc...) */
  uint8_t                 cmdFrame;   /* IN: variable length command frame */
} zclGenericReq_t;


/* for attribute reporting */
typedef PACKED_STRUCT zclReportingSetup_tag
{
  uint8_t  sendReportMask;      /* bit0 = 1: attr value reporting Enabled, bit1 = 1: attr value changed, bit2 = 1: timeout, 0x00 otherwise*/
  uint16_t reportTimeout;   /* in seconds (native endian). if 0, don't report on time */
  uint16_t reportMin;       /* minimum timeout in seconds */
  uint16_t reportCounter;   /* Second counter*/
  uint16_t minTimeCounter;  /* minimum time counter... counts down */
} zclReportingSetup_t;

/* for attribute reporting - client side - */
typedef PACKED_STRUCT zclReportingClientSetup_tag
{
  bool_t        aState;         /* TRUE if slot is free, FALSE if not */
  uint8_t       aEndpoint;      /* Endpoint*/        
  zbClusterId_t aClusterId;     /* Cluster ID*/
  zclAttrId_t   attrId;         /* Attribute Id*/
  uint16_t      reportTimeout;  /* in seconds (native endian). if 0, don't report on time */
} zclReportingClientSetup_t;


#define gZCLReportingAttrValueEnabled_c (0x01 << 0) 
#define gZCLReportingAttrValueChanged_c (0x01 << 1)
#define gZCLReportingAttrTimeout_c      (0x01 << 2)

/* global variable for attribute reporting - used when direction for configure reporting command is set to 0x01 */
#define gZClMaxAttrReportingReceivedTable_c 0x03
//extern zclReportingClientSetup_t gZclReportingClientSetup[gZClMaxAttrReportingReceivedTable_c];


/******************************************
*	ZCL Command Requests
*******************************************/

/* read an attribute from another node */
zclStatus_t ZCL_ReadAttrReq
  (
  zclReadAttrReq_t *pReq
  );

/* write an attribute to another node */
zclStatus_t ZCL_WriteAttrReq
  (
  zclWriteAttrReq_t *pReq
  );
  
/* discover attributes of another node */
#if gZclDiscoverAttrReq_d
zclStatus_t ZCL_DiscoverAttrReq
  (
  zclDiscoverAttrReq_t *pReq
  );  
#else
#define ZCL_DiscoverAttrReq(pReq) FALSE
#endif  

/* read an attribute from another node */
zclStatus_t ZCL_ReadAttrDirectedReq
  (
  zclReadAttrDirectedReq_t *pReq
  );

/* write an attribute to another node */
zclStatus_t ZCL_WriteAttrDirectedReq
  (
  zclWriteAttrDirectedReq_t *pReq
  );
  
/* discover attributes of another node */
#if gZclDiscoverAttrReq_d
zclStatus_t ZCL_DiscoverAttrDirectedReq
  (
  zclDiscoverAttrDirectedReq_t *pReq
  );  
#else
#define ZCL_DiscoverAttrDirectedReq(pReq) FALSE
#endif  

/* configure another node for reporting attributes */

zclStatus_t ZCL_ConfigureReportingReq
  (
  zclConfigureReportingReq_t * pReq
  );

/* read  reporting configuration from another node */
zclStatus_t ZCL_ReadReportingCfgReq
  (
  zclReadReportingCfgReq_t * pReq
  );


/* ZCL main task */
void TS_ZclTask(uint16_t events);
#define gZclEventReportTimeout_c  (1 << 0)  /* a reporting timer has fired, time to report attrs */
#define gZclEventReportTick_c     (1 << 1)  /*report timer tick event*/

/*******************************************
* Cross module helper functions
*******************************************/

/*
  ZCL_FindAttr

  Look through the cluster's attribute list to find this attribute.
  All mult-byte fields are little-endian.

  Returns pointer to the attribute, or NULL ifp not found.
*/
zclAttrDef_t *ZCL_FindAttr
  (
  afClusterDef_t *pCluster, 
  zclAttrId_t attrId,
  uint8_t direction 
  );


afToApsdeMessage_t *ZCL_CreateFrame
(
afAddrInfo_t *pAddrInfo,           /* IN: source and destination information */
zclCmd_t command, 	           /* IN: frame  command */
zclFrameControl_t frameControl,    /* IN: frame control field */
uint8_t *pTransactionId,
uint8_t *pPayloadLen, 		   /* IN/OUT: length of payload (then adjusted to length of asdu) */
void *pPayload		           /* IN: payload for entire frame */
);

/******************************************************************************
  ZCL_DataRequestNoCopy()
*******************************************************************************/
zclStatus_t ZCL_DataRequestNoCopy
(
afAddrInfo_t *pAddrInfo,      /* IN: source and destination information */
uint16_t payloadLen,           /* IN: length of payload */
afToApsdeMessage_t *pMsg     /* IN: allocated msg structure */
);
  
zclStatus_t ZCL_GenericReq(zclCmd_t command, uint8_t iPayloadLen, zclGenericReq_t *pReq);

/* Send Req from Client to Server with Zcl Transaction Sequence Id passed as parameter */  
zclStatus_t ZCL_SendClientReqSeqPassed(zclCmd_t command, uint8_t iPayloadLen, zclGenericReq_t *pReq);
/* Send Req From Server to Client with Zcl Transaction Sequence Id passed as parameter */
zclStatus_t ZCL_SendServerReqSeqPassed(zclCmd_t command, uint8_t iPayloadLen, zclGenericReq_t *pReq);
/* Send Rsp From Client to Server with Zcl Transaction Sequence Id passed as parameter */
zclStatus_t ZCL_SendClientRspSeqPassed(zclCmd_t command, uint8_t iPayloadLen, zclGenericReq_t *pReq);
/* Send Rsp From Server To Client with Zcl Transaction Sequence Id passed as parameter */
zclStatus_t ZCL_SendServerRspSeqPassed(zclCmd_t command, uint8_t iPayloadLen, zclGenericReq_t *pReq);
/* Send InterPan Rsp From Server To Client with Zcl Transaction Sequence Id passed as parameter */
zclStatus_t ZCL_SendInterPanServerRspSeqPassed(zclCmd_t command, uint8_t iPayloadLen, void *pReq);
/* Send InterPan Req from Client to Server with Zcl Transaction Sequence Id passed as parameter */  
zclStatus_t ZCL_SendInterPanClientReqSeqPassed(zclCmd_t command, uint8_t iPayloadLen, void *pReq);
/* Send InterPan Req from Server to Client with Zcl Transaction Sequence Id passed as parameter */  
zclStatus_t ZCL_SendInterPanServerReqSeqPassed(zclCmd_t command, uint8_t iPayloadLen, void *pReq);
/* Send InterPan Rsp From Client To Server with Zcl Transaction Sequence Id passed as parameter */
zclStatus_t ZCL_SendInterPanClientRspSeqPassed(zclCmd_t command, uint8_t iPayloadLen, void*pReq);

/* provided by each application */
void BeeAppUpdateDevice(zbEndPoint_t endPoint, zclUIEvent_t event, zclAttrId_t attrId, zbClusterId_t clusterId, void *pData);

void BeeAppHandleZclIndication(zbApsdeDataIndication_t *pIndication);


/* general foundation functions */
zbStatus_t ZCL_InterpretFrame(zbApsdeDataIndication_t *pIndication);
zbStatus_t ZCL_InterpretInterPanFrame(zbInterPanDataIndication_t *pIndication);
zbStatus_t ZCL_InterpretFoundationFrame(zbApsdeDataIndication_t *pIndication, afDeviceDef_t *pData);
void ZCL_SendDefaultMfgResponse(zbApsdeDataIndication_t *pIndication);

/* Build a response to the read attribute(s) command. */
uint8_t ZCL_BuildReadAttrResponse
  (
  afDeviceDef_t  *pDevice,    /* IN: device definition for this endpoint */
  afClusterDef_t *pCluster,   /* IN: cluster that was found */
  uint8_t count,              /* IN: # of responses */
  zclFrame_t *pFrame,         /* IN: read attr request */
  uint8_t maxAsduLen,         /* IN: maximum ASDU length */ 
  zclFrame_t *pFrameRsp       /* IN/OUT: response frame, allocated above, filled in here... */
  );

/* Given a cluster ID, find a pointer to the cluster structure. */
afClusterDef_t *ZCL_FindCluster
  (
  afDeviceDef_t *pDevice,     /* IN: device definition */
  zbClusterId_t aClusterId    /* IN: cluster ID to find in that device definition */
  );

/* helper functions */
bool_t ZCL_InCommandList(zclCmd_t command, zclCmdList_t *pCmdList);
void ZCL_SetupFrame(zclFrame_t *pDstFrame, zclFrame_t *pSrcFrame);
zbStatus_t ZCL_ReplyNoCopy(zbApsdeDataIndication_t *pIndication, uint8_t payloadLen,afToApsdeMessage_t *pMsg);
zbStatus_t ZCL_Reply(zbApsdeDataIndication_t *pIndication, uint8_t payloadLen, void *pPayload);
bool_t ZCL_IsZclEndPoint
  (
  afDeviceDef_t *pDevice    /* IN */
  );

#if gZclEnableReporting_c
/* start the reporting timer */
extern void ZCL_StartReportingTimer(void);
/* check and start reporting */
extern void ZCL_CheckAndStartAttrReporting(void);
/* stop attribute reporting per device */
extern void ZCL_StopAttrReporting(afDeviceDef_t *pDevice);
#endif

/* 
  note: Use ZCL_GetAttribute instead. Do NOT write to attributes directly, but 
  go through ZCL_SetAttribute(), to allow for reporting.
*/
void *ZCL_GetAttributePtr
    (
    afDeviceDef_t  *pDeviceDef, /* IN: pointer to device definition */
    afClusterDef_t *pCluster,   /* IN: pointer to cluster definition */
    zclAttrId_t attrId,         /* IN: attribute ID (in little endian) */
    uint8_t direction,            /* IN: 0x00 for Server Attributes and 0x08 for Client Attributes*/      
    uint8_t *pAttrLen           /* IN/OUT: return size of attribute (actual not max). */
    );




/* get an attribute */
zbStatus_t ZCL_GetAttribute
  (
    zbEndPoint_t  ep,           /* IN: pointer to instance data (derived from endpoint) */
    zbClusterId_t aClusterId,   /* IN: pointer to cluster definition (derived from clusterID */
    zclAttrId_t   attrId,       /* IN: attribute ID (in little endian) */
    uint8_t       direction,     /* IN: 0x00 for Server Attribute and 0x08 for Client */
    void          *pAttrData,   /* IN/OUT: get a copy of the attribute */
    uint8_t      *pAttrLen     /* IN/OUT: (optional) ptr to attribute length */
  );

/* set an attribute */
zbStatus_t ZCL_SetAttribute
  (
    zbEndPoint_t  ep,           /* IN: pointer to instance data (derived from endpoint) */
    zbClusterId_t aClusterId,   /* IN: pointer to cluster definition (derived from clusterID */
    zclAttrId_t   attrId,       /* IN: attribute ID (in little endian) */
    uint8_t       direction,     /* IN: 0x00 for Server Attribute and 0x08 for Client */
    void          *pAttrData    /* IN: ptr to attribute data (length is implied by ID) */
  );

void *ZCL_GetPayload(zbApsdeDataIndication_t *pIndication);
zclCmd_t ZCL_GetCommand(zbApsdeDataIndication_t *pIndication);
uint8_t ZCL_CopyStr(uint8_t *pDst, uint8_t *pSrc);
void ZCL_SaveNvmZclData(void);
uint8_t ZCL_GetDataTypeLen(uint8_t dataType, uint8_t *pAttrData, zclAttrDef_t *pAttrDef);
#ifdef __cplusplus
}
#endif
#endif  /* _ZCL_H */

