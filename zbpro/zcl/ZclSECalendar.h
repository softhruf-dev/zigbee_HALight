/*! @file 	ZclSECalendar.h
 *
 * @brief	Types, definitions and prototypes for the TOU Calendar cluster implementation.
 *
 * @copyright Copyright(c) 2013, Freescale, Inc. All rights reserved.
 *
 * @license	Redistribution and use in source and binary forms, with or without modification,
 *			are permitted provided that the following conditions are met:
 *
 *			o Redistributions of source code must retain the above copyright notice, this list
 *			of conditions and the following disclaimer.
 *
 *			o Redistributions in binary form must reproduce the above copyright notice, this
 *   		list of conditions and the following disclaimer in the documentation and/or
 *   		other materials provided with the distribution.
 *
 *			o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   		contributors may be used to endorse or promote products derived from this
 *   		software without specific prior written permission.
 *
 *			THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * 			ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * 			WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * 			DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * 			ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * 			(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * 			LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * 			ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * 			(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * 			SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _ZCLSECALENDAR_H
#define _ZCLSECALENDAR_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "AfApsInterface.h"
#include "AppAfInterface.h"
#include "BeeStackInterface.h"
#include "ZCL.h"
#include "SEProfile.h"

/******************************************************************************
*******************************************************************************
* Private macros
*******************************************************************************
******************************************************************************/

/******************************************
	TOU Calendar Cluster
  See Zigbee SE 1.x Extensions for UK - Section 3 [R1]
*******************************************/

/* [R1] 3.2.3 Commands Generated by the TOU Calendar Cluster Server */
#define gZclCmdTouCalendar_PublishCalendar_c                 0x00    /* O/M (UK) - publish calendar */
#define gZclCmdTouCalendar_PublishDayProfile_c               0x01    /* O/M (UK) - publish day profile */
#define gZclCmdTouCalendar_PublishWeekProfile_c              0x02    /* O/M (UK) - publish week profile */
#define gZclCmdTouCalendar_PublishSeasons_c                  0x03    /* O/M (UK) - publish seasons */
#define gZclCmdTouCalendar_PublishSpecialDays_c              0x04    /* O/M (UK) - publish special days */
#define gZclCmdTouCalendar_CancelCalendar_c             	 0x05    /* O/M (UK) - cancel calendar */
  

/* [R1] 3.2.4 Commands Received by the TOU Calendar Cluster Server */
#define gZclCmdTouCalendar_GetCalendar_c                     0x00    /* O/M (UK) - get calendar */
#define gZclCmdTouCalendar_GetDayProfiles_c                  0x01    /* O/M (UK) - get day profile */
#define gZclCmdTouCalendar_GetWeekProfiles_c                 0x02    /* O/M (UK) - get week profile */
#define gZclCmdTouCalendar_GetSeasons_c                      0x03    /* O/M (UK) - get seasons */
#define gZclCmdTouCalendar_GetSpecialDays_c                  0x04    /* O/M (UK) - get special days */


#define gTouCalendar_NotSeasonDefined_c          0x00                 /* season is not defined */
#define gTouCalendar_NotWeekProfileDefined_c     0x00                 /* week profile is not defined */
#define gTouCalendar_CalendarTypePresent_c       TRUE                 /* TRUE - Calendar type field is included in the GetCalendar and 
                                                                              GetSpecialDay commands payload, FALSE - otherwise */   
#define gTouCalendar_Type_NotSpecified_c         0xFF                 /* not specified calendar type */   

#define gTouCalendar_NoOfInstances_c             0x02                 /* the current and next one instances of the calendar */
#define gTouCalendar_NoOfSeasonEntries_c         0x02//0x04           /* max number of season Entry*/
#define gTouCalendar_NoOfWeekProfiles_c          0x02//0x04           /* max number of week profiles */  
#define gTouCalendar_NoOfDayProfiles_c           0x02//0x08           /* max number of Day Profiles */  
#define gTouCalendar_NoOfDayScheduleEntries_c    0x02//0x10           /* max number of Day schedule Entries */  
#define gTouCalendar_NoOfSpecialDayEntries_c     0x02//0x1E           /* max number of Special Day Entries */ 
  

/* cmdindex/TotalNumberOfCmds  bitmap format */
typedef PACKED_STRUCT zclCmdTouCalendar_IndexTotalCmdsFormat_tag 
{
#ifdef PROCESSOR_KINETIS    
  uint8_t cmdIndex     :4;
  uint8_t TotalNumberOfCmds         :4;
#else
  unsigned int cmdIndex      :4;
  unsigned int TotalNumberOfCmds     :4;
#endif  
}zclCmdTouCalendar_IndexTotalCmdsFormat_t; 


/* payload format for the PublishCalendar command */
typedef PACKED_STRUCT zclCmdTouCalendar_PublishCalendar_tag 
{
  uint32_t      providerId;	
  uint32_t      issuerEventId;  
  uint32_t      issuerCalendarId;
  ZCLTime_t     startTime;
  uint8_t       calendarType;
//uint8_t       calendarTimeReference;
  zclStr12Oct_t calendarName;               
  uint8_t       numberOfSeasons;
  uint8_t       numberOfWeekProfiles;
  uint8_t       numberOfDayProfiles;
}zclCmdTouCalendar_PublishCalendar_t; 


/* [R1] 3.2.3.1 PublishCalendar Command */
typedef PACKED_STRUCT zclTouCalendar_PublishCalendar_tag 
{
   afAddrInfo_t                        addrInfo;
   uint8_t                             zclTransactionId;
   zclCmdTouCalendar_PublishCalendar_t cmdFrame;
}zclTouCalendar_PublishCalendar_t; 

/* Calendar Type Enumeration([R1] Table 3-3) */
enum{
  gTouCalendar_CalendarType_DeliveredCalendar_c   = 0x00,                  /* delivered calendar */
  gTouCalendar_CalendarType_ReceivedCalendar_c,                            /* received calendar */
  gTouCalendar_CalendarType_DeliveredAndReceivedCalendar_c,                /* delivered and received calendar */
  gTouCalendar_CalendarType_FriendlyCreditCalendar_c,                      /* friendly Credit Calendar*/
  gTouCalendar_CalendarType_AuxillaryLoadSwitchCalendar_c				   /* Auxillary Load Switch Calendar*/	
};

/* Calendar Time Reference ([R1] Table 3-4) */
enum{
  gTouCalendar_CalendarTimeRef_StandardTime_c   = 0x00,                 /* standard time */
  gTouCalendar_CalendarTimeRef_LocalTime_c                              /* local time */
};

/* schedule entries for rate switch times */
typedef PACKED_STRUCT zclTouCalendar_ScheduleEntries_RateSwitchTimes_tag
{
  uint16_t startTime;
  uint8_t  activePriceTier;
}zclTouCalendar_ScheduleEntries_RateSwitchTimes_t;

/* schedule entries for friendly credit switch times */
typedef PACKED_STRUCT zclTouCalendar_ScheduleEntries_FriendlyCreditSwitchTimes_tag
{
  uint16_t startTime;
  bool_t   friendlyCreditEnable;
}zclTouCalendar_ScheduleEntries_FriendlyCreditSwitchTimes_t;

/* schedule entries for friendly credit switch times */
typedef PACKED_STRUCT zclTouCalendar_ScheduleEntries_AuxilliarySwitchTimes_tag
{
  uint16_t  startTime;
  uint8_t   auxiliaryLoadSwitchState;
}zclTouCalendar_ScheduleEntries_AuxilliarySwitchTimes_t;

/* day schedule entries */
typedef PACKED_UNION zclTouCalendar_DayScheduleEntries_tag {
  zclTouCalendar_ScheduleEntries_RateSwitchTimes_t           rateSwitchTimes;
  zclTouCalendar_ScheduleEntries_FriendlyCreditSwitchTimes_t friendlyCreditSwitchTimes;
  zclTouCalendar_ScheduleEntries_AuxilliarySwitchTimes_t	 auxiliarySwitchTimes;
} zclTouCalendar_DayScheduleEntries_t;

/* payload format for the PublishDayProfile command */
typedef PACKED_STRUCT zclCmdTouCalendar_PublishDayProfile_tag 
{
  uint32_t                             	 		providerId;
  uint32_t                              		issuerEventId;  
  uint32_t                              		issuerCalendarId;
  uint8_t                               		dayId;
  uint8_t                              		 	totalNoOfScheduleEntries;        
  zclCmdTouCalendar_IndexTotalCmdsFormat_t      commandIndex;
  zclTouCalendar_DayScheduleEntries_t   		dayScheduleEntries[1];
}zclCmdTouCalendar_PublishDayProfile_t; 

/* [R1] 3.2.3.2 Publish Day Profile Command */
typedef PACKED_STRUCT zclTouCalendar_PublishDayProfile_tag 
{
   afAddrInfo_t                                 addrInfo;
   uint8_t                                      zclTransactionId;
   zclCmdTouCalendar_PublishDayProfile_t        cmdFrame;
}zclTouCalendar_PublishDayProfile_t; 


/* week profile format */
typedef PACKED_STRUCT zclTouCalendar_WeekProfile_tag 
{									
  uint8_t                               weekId;
  uint8_t                               dayIdRefMonday;        
  uint8_t                               dayIdRefTuesday;
  uint8_t                               dayIdRefWednesday;    
  uint8_t                               dayIdRefThursday;
  uint8_t                               dayIdRefFriday;  
  uint8_t                               dayIdRefSaturday;  
  uint8_t                               dayIdRefSunday;  
}zclTouCalendar_WeekProfile_t; 


/* payload format for the PublishWeekProfile command */
typedef PACKED_STRUCT zclCmdTouCalendar_PublishWeekProfile_tag 
{
  uint32_t                              providerId;
  uint32_t                              issuerEventId;  
  uint32_t                              issuerCalendarId;
  zclTouCalendar_WeekProfile_t          weekProfile;
}zclCmdTouCalendar_PublishWeekProfile_t; 


/* [R1] 3.2.3.3 Publish Week Profile Command */
typedef PACKED_STRUCT zclTouCalendar_PublishWeekProfile_tag 
{
   afAddrInfo_t                                 addrInfo;
   uint8_t                                      zclTransactionId;
   zclCmdTouCalendar_PublishWeekProfile_t       cmdFrame;
}zclTouCalendar_PublishWeekProfile_t; 



/* season entry format */
typedef PACKED_STRUCT zclTouCalendar_SeasonEntry_tag
{
  zclDate_t     seasonStartDate;
  uint8_t       weekIdRef;
}zclTouCalendar_SeasonEntry_t;

/* payload format for the PublishSeasons command */
typedef PACKED_STRUCT zclCmdTouCalendar_PublishSeasons_tag 
{
  uint32_t                      			providerId;
  uint32_t                      			issuerEventId;  	
  uint32_t                      			issuerCalendarId;
  zclCmdTouCalendar_IndexTotalCmdsFormat_t	commandIndex;
  zclTouCalendar_SeasonEntry_t  			seasonEntry[1];  
}zclCmdTouCalendar_PublishSeasons_t; 

/* [R1] 3.2.3.4 Publish Seasons Command */
typedef PACKED_STRUCT zclTouCalendar_PublishSeasons_tag 
{
   afAddrInfo_t                                 addrInfo;
   uint8_t                                      zclTransactionId;
   zclCmdTouCalendar_PublishSeasons_t           cmdFrame;
}zclTouCalendar_PublishSeasons_t; 


/* special day entry format */
typedef PACKED_STRUCT zclTouCalendar_SpecialDayEntry_tag
{
  zclDate_t     specialDayDate;
  uint8_t       dayIdRef;
}zclTouCalendar_SpecialDayEntry_t;

/* payload format for the Publish Special Days command */
typedef PACKED_STRUCT zclCmdTouCalendar_PublishSpecialDays_tag 
{
  uint32_t                              	providerId;
  uint32_t                              	issuerEventId;
  uint32_t                              	issuerCalendarId;  
  ZCLTime_t                             	startTime;
  uint8_t                               	calendarType;
  uint8_t                               	totalNoSpecialDays;
  zclCmdTouCalendar_IndexTotalCmdsFormat_t	commandIndex;
  zclTouCalendar_SpecialDayEntry_t      	specialDayEntry[1];
}zclCmdTouCalendar_PublishSpecialDays_t; 

/* [R1] 3.2.3.5 Publish Special Days Command */
typedef PACKED_STRUCT zclTouCalendar_PublishSpecialDays_tag 
{
   afAddrInfo_t                                 addrInfo;
   uint8_t                                      zclTransactionId;
   zclCmdTouCalendar_PublishSpecialDays_t       cmdFrame;
}zclTouCalendar_PublishSpecialDays_t; 


/* payload format for the Cancel Calendar command */
typedef PACKED_STRUCT zclCmdTouCalendar_CancelCalendar_tag 
{
  uint32_t                              providerId;
  uint32_t                              issuerCalendarId; 
  uint8_t                               calendarType;
}zclCmdTouCalendar_CancelCalendar_t; 

/* [R1] 9.2.3.6 Cancel Calendar Command */
typedef PACKED_STRUCT zclTouCalendar_CancelCalendar_tag 
{
   afAddrInfo_t                                 addrInfo;
   uint8_t                                      zclTransactionId;
   zclCmdTouCalendar_CancelCalendar_t           cmdFrame;
}zclTouCalendar_CancelCalendar_t; 


/* payload format for the Get Calendar command */
typedef PACKED_STRUCT zclCmdTouCalendar_GetCalendar_tag 
{
  ZCLTime_t     startTime;
  uint8_t       numberOfCalendars;
  uint8_t       calendarType;           
  uint32_t		providerId;
  uint32_t		issuerCalendarId;
}zclCmdTouCalendar_GetCalendar_t; 

/* [R1] 3.2.4.1 Get Calendar Command */
typedef PACKED_STRUCT zclTouCalendar_GetCalendar_tag 
{
   afAddrInfo_t                          addrInfo;
   uint8_t                               zclTransactionId;
   zclCmdTouCalendar_GetCalendar_t       cmdFrame;
}zclTouCalendar_GetCalendar_t; 

/* payload format for the Get Day Profiles command */
typedef PACKED_STRUCT zclCmdTouCalendar_GetDayProfiles_tag 
{
  uint32_t		providerId;	
  uint32_t 		issuerCalendarId;
  uint8_t		dayId;
  uint8_t 		numberOfDays;
}zclCmdTouCalendar_GetDayProfiles_t; 

/* [R1] 3.2.4.2 Get Day Profiles Command */
typedef PACKED_STRUCT zclTouCalendar_GetDayProfiles_tag 
{
   afAddrInfo_t                          addrInfo;
   uint8_t                               zclTransactionId;
   zclCmdTouCalendar_GetDayProfiles_t    cmdFrame;
}zclTouCalendar_GetDayProfiles_t; 

/* payload format for the Get Week Profiles command */
typedef PACKED_STRUCT zclCmdTouCalendar_GetWeekProfiles_tag 
{
  uint32_t		providerId;	
  uint32_t 		issuerCalendarId;
  uint8_t		weekId;
  uint8_t 		numberOfWeeks;
}zclCmdTouCalendar_GetWeekProfiles_t; 

/* [R1] 3.2.4.3 Get Week Profiles Command */
typedef PACKED_STRUCT zclTouCalendar_GetWeekProfiles_tag 
{
   afAddrInfo_t                          addrInfo;
   uint8_t                               zclTransactionId;
   zclCmdTouCalendar_GetWeekProfiles_t   cmdFrame;
}zclTouCalendar_GetWeekProfiles_t; 

/* payload format for the Get Week Profiles command */
typedef PACKED_STRUCT zclCmdTouCalendar_GetSeasons_tag 
{
  uint32_t		providerId;	
  uint32_t 		issuerCalendarId;
}zclCmdTouCalendar_GetSeasons_t; 

/* [R1] 3.2.4.4 Get Seasons Command */
typedef PACKED_STRUCT zclTouCalendar_GetSeasons_tag 
{
   afAddrInfo_t                          addrInfo;
   uint8_t                               zclTransactionId;
   zclCmdTouCalendar_GetSeasons_t        cmdFrame;
}zclTouCalendar_GetSeasons_t; 

/* payload format for the Get Special Days command */
typedef PACKED_STRUCT zclCmdTouCalendar_GetSpecialDays_tag 
{
  ZCLTime_t     startTime;
  uint8_t       numberOfEvents;
  uint8_t       calendarType;           /* optional */
  uint32_t		providerId;	
  uint32_t 		issuerCalendarId;  
}zclCmdTouCalendar_GetSpecialDays_t; 

/* [R1] 3.2.4.5 Get Special Days Command */
typedef PACKED_STRUCT zclTouCalendar_GetSpecialDays_tag 
{
   afAddrInfo_t                          addrInfo;
   uint8_t                               zclTransactionId;
   zclCmdTouCalendar_GetSpecialDays_t    cmdFrame;
}zclTouCalendar_GetSpecialDays_t; 


/* format for the day profile table */
typedef PACKED_STRUCT zclTouCalendar_DayProfile_tag
{
  uint8_t                                       dayId;
  uint8_t                                       noOfDayScheduleEntries;
  zclTouCalendar_DayScheduleEntries_t           dayScheduleEntry[gTouCalendar_NoOfDayScheduleEntries_c];
}zclTouCalendar_DayProfile_t;

/* get day/week/season profile information entries */
typedef PACKED_UNION zclTouCalendar_GetInfCommands_tag {
  zclCmdTouCalendar_GetDayProfiles_t  getDay;
  zclCmdTouCalendar_GetWeekProfiles_t getWeek;
  zclCmdTouCalendar_GetSeasons_t	  getSeason;
} zclTouCalendar_GetInfCommands_t;


/* format for the activity calendar table */  
typedef PACKED_STRUCT zclTouCalendar_ActivityCalendar_tag
{
  uint32_t										issuerEventId;	
  uint32_t                                      issuerId;
  zclStr12Oct_t                                 name;     
  ZCLTime_t                                     startTime;
  uint8_t                                       type;
  uint8_t                                       noOfSeasonEntries;
  zclTouCalendar_SeasonEntry_t                  seasonTable[gTouCalendar_NoOfSeasonEntries_c];    /* seasons Table*/
  uint8_t                                       noOfWeekProfileEntries;
  zclTouCalendar_WeekProfile_t                  weekProfileTable[gTouCalendar_NoOfWeekProfiles_c];/* week Profile Table*/
  uint8_t                                       noOfDayProfileEntries;
  zclTouCalendar_DayProfile_t                   dayProfileTable[gTouCalendar_NoOfDayProfiles_c];  /* day Profile Table*/
}zclTouCalendar_ActivityCalendar_t;

typedef PACKED_STRUCT zclTouCalendar_ActivityCalendarInfo_tag
{
  uint8_t                                       entryStatus;
  uint32_t										providerId;
  zclTouCalendar_ActivityCalendar_t             calendar;
}zclTouCalendar_ActivityCalendarInfo_t;


/* format for the special day table */
typedef PACKED_STRUCT zclTouCalendar_SpecialDay_tag
{
  uint32_t                              issuerEventId;
  ZCLTime_t                             startTime;
  uint8_t                               calendarType;
  uint8_t                               noOfSpecialDayEntries;
  zclTouCalendar_SpecialDayEntry_t      specialDayEntries[gTouCalendar_NoOfSpecialDayEntries_c];       /* special Day Entries*/   
}zclTouCalendar_SpecialDay_t;

typedef PACKED_STRUCT zclTouCalendar_SpecialDayInfo_tag
{
  uint8_t                               entryStatus;
  uint32_t							    providerId;
  zclTouCalendar_SpecialDay_t           specialDay;     
}zclTouCalendar_SpecialDayInfo_t;


/* save next information from ActivityCalendarInfo that need to be sent after a 
GetCalendar Command and filter reqs*/
typedef PACKED_STRUCT zclTouCalendar_GetCalendarInf_tag 
{
   afAddrInfo_t         					addrInfo;
   uint8_t              					zclTransactionId;
   ZCLTime_t            					startTime;
   uint8_t              					noOfCalendarsRemaining;
   uint8_t              					calendarType;     
   uint32_t									issuerCalendarId;
   zclCmdTouCalendar_IndexTotalCmdsFormat_t index;
}zclTouCalendar_GetCalendarInf_t; 

/* save next information from ActivityCalendarInfo that need to be sent after a 
GetDayProfiles Command and filter reqs*/
typedef PACKED_STRUCT zclTouCalendar_GetDayProfilesInf_tag 
{
   afAddrInfo_t         addrInfo;
   uint8_t              zclTransactionId;
   uint32_t             issuerCalendarId;        
   uint8_t				NumberOfDays;
   uint8_t              dayIndex;               /* index in the DayProfilesTable*/
   zclCmdTouCalendar_IndexTotalCmdsFormat_t              commandIndex; 
   uint8_t              calendarIndex;          /* index in the CalendarActivity Table */
}zclTouCalendar_GetDayProfilesInf_t; 

/* save next information from ActivityCalendarInfo that need to be sent after a 
GetWeekProfiles Command and filter reqs*/
typedef PACKED_STRUCT zclTouCalendar_GetWeekProfilesInf_tag 
{
   afAddrInfo_t         addrInfo;
   uint8_t              zclTransactionId;
   uint32_t             issuerCalendarId;     
   uint8_t 				noOfweeks;
   uint8_t              weekIndex;               /* index in the WeekProfilesTable */
   uint8_t              calendarIndex;           /* index in the CalendarActivity Table */
}zclTouCalendar_GetWeekProfilesInf_t; 

/* save next information from ActivityCalendarInfo that need to be sent after a 
GetSeasons Command and filter reqs*/
typedef PACKED_STRUCT zclTouCalendar_GetSeasonsInf_tag 
{
   afAddrInfo_t         addrInfo;
   uint8_t              zclTransactionId;
   uint32_t             issuerCalendarId;        
   zclCmdTouCalendar_IndexTotalCmdsFormat_t              commandIndex;              
   uint8_t              calendarIndex;         /* index in the CalendarActivity Table */
}zclTouCalendar_GetSeasonsInf_t; 

/* save next information from  SpecialDayInfo that need to be sent after a 
GetSpecialDays Command and filter reqs*/
typedef PACKED_STRUCT zclTouCalendar_GetSpecialDayInf_tag 
{
   afAddrInfo_t         addrInfo;
   uint8_t              zclTransactionId;
   ZCLTime_t            startTime;
   uint8_t              noOfEvents;
   uint8_t 				issuerCalendarId;
   uint8_t              calendarType;       
   uint8_t              index;                /* index in the Special Days Info*/
   uint8_t              commandIndex; 
}zclTouCalendar_GetSpecialDayInf_t; 

#if gASL_ZclSE_12_Features_d || gASL_ZclTouCalendar_Optionals_d   
extern zclTouCalendar_ActivityCalendarInfo_t    gServerActivityCalendarInfo[gTouCalendar_NoOfInstances_c];
#endif

/*!
 * @fn 		zbStatus_t ZCL_TouCalendarClusterServer(zbApsdeDataIndication_t *pIndication, afDeviceDef_t *pDev) 
 *
 * @brief	Processes the requests received on the TOU Calendar Cluster server. 
 *
 */
zbStatus_t ZCL_TouCalendarClusterServer(zbApsdeDataIndication_t *pIndication, afDeviceDef_t *pDevice);

/*!
 * @fn 		zbStatus_t ZCL_TouCalendarClusterClient(zbApsdeDataIndication_t *pIndication, afDeviceDef_t *pDev) 
 *
 * @brief	Processes the requests received on the TOU Calendar Cluster client. 
 *
 */
zbStatus_t ZCL_TouCalendarClusterClient(zbApsdeDataIndication_t *pIndication, afDeviceDef_t *pDevice);

#if gASL_ZclSE_12_Features_d || gASL_ZclTouCalendar_Optionals_d   
/*!
 * @fn 		zbStatus_t zclTouCalendar_GetCalendar(zclTouCalendar_GetCalendar_t *pReq) 
 *
 * @brief	Sends over-the-air a Get Calendar frame from the TOU Calendar client. 
 *
 */
zbStatus_t zclTouCalendar_GetCalendar(zclTouCalendar_GetCalendar_t *pReq);

/*!
 * @fn 		zbStatus_t zclTouCalendar_PublishCalendar(zclTouCalendar_PublishCalendar_t *pReq) 
 *
 * @brief	Sends over-the-air a Publish Calendar frame from the TOU Calendar server. 
 *
 */
zbStatus_t zclTouCalendar_PublishCalendar(zclTouCalendar_PublishCalendar_t *pCommandRsp);

/*!
 * @fn 		zbStatus_t zclTouCalendar_GetDayProfiles(zclTouCalendar_GetDayProfiles_t *pReq) 
 *
 * @brief	Sends over-the-air a Get Day Profiles frame from the TOU Calendar client. 
 *
 */
zbStatus_t zclTouCalendar_GetDayProfiles(zclTouCalendar_GetDayProfiles_t *pReq);

/*!
 * @fn 		zbStatus_t zclTouCalendar_PublishDayProfile(zclTouCalendar_PublishDayProfile_t *pCommandRsp, uint8_t payloadLen) 
 *
 * @brief	Sends over-the-air a Publish Day Profile frame from the TOU Calendar server. 
 *
 */
zbStatus_t zclTouCalendar_PublishDayProfile(zclTouCalendar_PublishDayProfile_t *pCommandRsp, uint8_t payloadLen);

/*!
 * @fn 		zbStatus_t zclTouCalendar_GetWeekProfiles(zclTouCalendar_GetWeekProfiles_t *pReq) 
 *
 * @brief	Sends over-the-air a Get Week Profiles frame from the TOU Calendar client. 
 *
 */
zbStatus_t zclTouCalendar_GetWeekProfiles(zclTouCalendar_GetWeekProfiles_t *pReq); 

/*!
 * @fn 		zbStatus_t zclTouCalendar_PublishWeekProfile(zclTouCalendar_PublishWeekProfile_t *pCommandRsp) 
 *
 * @brief	Sends over-the-air a Publish Week Profile frame from the TOU Calendar server. 
 *
 */
zbStatus_t zclTouCalendar_PublishWeekProfile(zclTouCalendar_PublishWeekProfile_t *pCommandRsp) ;

/*!
 * @fn 		zbStatus_t zclTouCalendar_GetSeasons(zclTouCalendar_GetSeasons_t *pReq) 
 *
 * @brief	Sends over-the-air a Get Seasons frame from the TOU Calendar client. 
 *
 */
zbStatus_t zclTouCalendar_GetSeasons(zclTouCalendar_GetSeasons_t *pReq);

/*!
 * @fn 		zbStatus_t zclTouCalendar_PublishSeasons(zclTouCalendar_PublishSeasons_t *pCommandRsp) 
 *
 * @brief	Sends over-the-air a Publish Seasons frame from the TOU Calendar server. 
 *
 */
zbStatus_t zclTouCalendar_PublishSeasons(zclTouCalendar_PublishSeasons_t *pCommandRsp);

/*!
 * @fn 		zbStatus_t zclTouCalendar_GetSpecialDays(zclTouCalendar_GetSpecialDays_t *pReq)
 *
 * @brief	Sends over-the-air a Get Special Days frame from the TOU Calendar client. 
 *
 */
zbStatus_t zclTouCalendar_GetSpecialDays(zclTouCalendar_GetSpecialDays_t *pReq);

/*!
 * @fn 		zbStatus_t zclTouCalendar_PublishSpecialDays(zclTouCalendar_PublishSpecialDays_t *pCommandRsp, uint8_t payloadLen)
 *
 * @brief	Sends over-the-air a Publish Special Days frame from the TOU Calendar client. 
 *
 */
zbStatus_t zclTouCalendar_PublishSpecialDays(zclTouCalendar_PublishSpecialDays_t *pCommandRsp, uint8_t payloadLen);

void SendTouCalendarClusterEvt(uint32_t evtId);
void ZCL_HandleSETouCalendarClusterEvt(void);

/*!
 * @fn 		zbStatus_t ZtcTouCalendar_StoreServerActivityCalendarInfo(uint8_t *pMsg)
 *
 * @brief	Stores activity calendar information received from the Provider. 
 *
 */
zbStatus_t ZtcTouCalendar_StoreServerActivityCalendarInfo(uint8_t *pMsg);

/*!
 * @fn 		zbStatus_t ZtcTouCalendar_StoreServerSpecialDayInfo(zclTouCalendar_SpecialDayInfo_t *pMsg)
 *
 * @brief	Stores special days information received from the Provider. 
 *
 */
zbStatus_t ZtcTouCalendar_StoreServerSpecialDayInfo(zclTouCalendar_SpecialDayInfo_t *pMsg);
#endif /* gASL_ZclSE_12_Features_d || gASL_ZclTouCalendar_Optionals_d */
#ifdef __cplusplus
}
#endif
#endif /* _ZCLSECALENDAR_H */
