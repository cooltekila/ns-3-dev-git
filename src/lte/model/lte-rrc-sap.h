/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Nicola Baldo <nbaldo@cttc.es>
 */


#ifndef LTE_RRC_SAP_H
#define LTE_RRC_SAP_H

#include <stdint.h>
#include <list>

#include <ns3/ptr.h>

namespace ns3 {


class LteRlcSapUser;
class LtePdcpSapUser;
class LteRlcSapProvider;
class LtePdcpSapProvider;
class Packet;  

/**
 * Class holding definition common to all Ue/Enb SAP
 * Users/Providers. See 3GPP TS 36.331 for reference. 
 * Note that only those values that are (expected to be) used by the
 * ns-3 model are mentioned here. The naming of the variables that are
 * defined here is the same of 36.331, except for removal of "-" and
 * conversion to CamelCase or ALL_CAPS where needed in order to follow
 * the ns-3 coding style. Due to the 1-to-1 mapping with TS 36.311, 
 * detailed doxygen documentation is omitted, so please refer to
 * 36.311 for the meaning of these data structures / fields.
 * 
 */
class LteRrcSap
{
public:

  // Information Elements
  
  struct PlmnIdentityInfo
  {
    uint32_t plmnIdentity;
  };

  struct CellAccessRelatedInfo
  {
    PlmnIdentityInfo plmnIdentityInfo;
    uint32_t cellIdentity;
    bool csgIndication;
    uint32_t csgIdentity;
  };
  
  struct FreqInfo
  {
    uint16_t ulCarrierFreq;
    uint8_t ulBandwidth;
  };

  struct RlcConfig
  {
    enum
      {
        AM, 
        UM_BI_DIRECTIONAL,
        UM_UNI_DIRECTIONAL_UL,
        UM_UNI_DIRECTIONAL_DL
      } choice;    
  };

  struct LogicalChannelConfig
  {
    uint8_t priority;
    uint16_t prioritizedBitRateKbps;
    uint16_t bucketSizeDurationMs;
    uint8_t logicalChannelGroup;
  };

  struct SoundingRsUlConfigCommon
  {
    enum {SETUP, RESET} type;
    uint8_t srsBandwidthConfig;
    uint8_t srsSubframeConfig;
  };

  struct SoundingRsUlConfigDedicated
  {
    enum {SETUP, RESET} type;
    uint8_t srsBandwidth;
    uint16_t srsConfigIndex;
  };

  struct AntennaInfoDedicated
  {
    uint8_t transmissionMode;
  };


  struct PhysicalConfigDedicated
  {
    bool haveSoundingRsUlConfigDedicated;
    SoundingRsUlConfigDedicated soundingRsUlConfigDedicated;
    bool haveAntennaInfoDedicated;
    AntennaInfoDedicated antennaInfo;
  };


  struct SrbToAddMod
  {
    uint8_t srbIdentity;   
    LogicalChannelConfig logicalChannelConfig;
  };
  
  struct DrbToAddMod
  {
    uint8_t epsBearerIdentity;
    uint8_t drbIdentity;
    RlcConfig rlcConfig;
    uint8_t logicalChannelIdentity;
    LogicalChannelConfig logicalChannelConfig;
  };

  struct PreambleInfo
  {
    uint8_t numberOfRaPreambles;
  };
  
  struct RaSupervisionInfo
  {
    uint8_t preambleTransMax;
    uint8_t raResponseWindowSize;
  };

  struct RachConfigCommon
  {
    PreambleInfo preambleInfo;
    RaSupervisionInfo raSupervisionInfo;
  };

  struct RadioResourceConfigCommon
  {    
    RachConfigCommon rachConfigCommon;
  };

  struct RadioResourceConfigCommonSib
  {    
    RachConfigCommon rachConfigCommon;
  };

  struct RadioResourceConfigDedicated
  {
    std::list<SrbToAddMod> srbToAddModList;
    std::list<DrbToAddMod> drbToAddModList;    
    std::list<uint8_t> drbToReleaseList;
    bool havePhysicalConfigDedicated;
    PhysicalConfigDedicated physicalConfigDedicated;
  };

  struct MeasConfig
  {

  };

  struct CarrierFreqEutra
  {
    uint16_t dlCarrierFreq;
    uint16_t ulCarrierFreq;
  };

  struct CarrierBandwidthEutra
  {
    uint8_t dlBandwidth;
    uint8_t ulBandwidth;
  };

  struct RachConfigDedicated 
  {
    uint8_t raPreambleIndex;
    uint8_t raPrachMaskIndex;
  };

  struct MobilityControlInfo
  {
    uint16_t targetPhysCellId;
    bool haveCarrierFreq;
    CarrierFreqEutra carrierFreq;    
    bool haveCarrierBandwidth;
    CarrierBandwidthEutra carrierBandwidth;   
    uint16_t newUeIdentity;
    RadioResourceConfigCommon radioResourceConfigCommon;
    bool haveRachConfigDedicated;
    RachConfigDedicated rachConfigDedicated;
  };

  struct ReestabUeIdentity
  {
    uint16_t cRnti;
    uint16_t physCellId;    
  };

  enum ReestablishmentCause 
    { 
      RECONFIGURATION_FAILURE,
      HANDOVER_FAILURE,
      OTHER_FAILURE
    };

  struct MasterInformationBlock
  {
    uint8_t dlBandwidth;
    uint8_t systemFrameNumber;
  };
  
  struct SystemInformationBlockType1
  {
    CellAccessRelatedInfo cellAccessRelatedInfo;
  };

  struct SystemInformationBlockType2
  {
    RadioResourceConfigCommonSib radioResourceConfigCommon;
    FreqInfo freqInfo;    
  };

  struct SystemInformation
  {
    bool haveSib2;
    SystemInformationBlockType2 sib2;
  }
    ;
  struct AsConfig
  {
    MeasConfig sourceMeasConfig;
    RadioResourceConfigDedicated sourceRadioResourceConfig;
    uint16_t sourceUeIdentity;      
    MasterInformationBlock sourceMasterInformationBlock;
    SystemInformationBlockType1 sourceSystemInformationBlockType1;
    uint16_t sourceDlCarrierFreq;
  };


  // Messages

  struct RrcConnectionRequest
  {
    uint64_t ueIdentity;
  };

  struct RrcConnectionSetup
  {
    uint8_t rrcTransactionIdentifier;
    RadioResourceConfigDedicated radioResourceConfigDedicated;
  };
   
  struct RrcConnectionSetupCompleted
  {
    uint8_t rrcTransactionIdentifier;
  };

  struct RrcConnectionReconfiguration
  {
    uint8_t rrcTransactionIdentifier;
    bool haveMeasConfig;
    MeasConfig measConfig;
    bool haveMobilityControlInfo;
    MobilityControlInfo mobilityControlInfo;
    bool haveRadioResourceConfigDedicated;
    RadioResourceConfigDedicated radioResourceConfigDedicated;
  };
    
  struct RrcConnectionReconfigurationCompleted
  {
    uint8_t rrcTransactionIdentifier;
  };
    
      
  struct RrcConnectionReestablishmentRequest
  {
    ReestabUeIdentity ueIdentity;
    ReestablishmentCause reestablishmentCause;
  };
    
  struct RrcConnectionReestablishment
  {
    uint8_t rrcTransactionIdentifier;
    RadioResourceConfigDedicated radioResourceConfigDedicated;
  };
      
  struct RrcConnectionReestablishmentComplete
  {
    uint8_t rrcTransactionIdentifier;
  };

  struct RrcConnectionReestablishmentReject
  {
  };

  struct RrcConnectionRelease
  {
  };

  struct HandoverPreparationInfo
  {
    AsConfig asConfig;
  };
  
};



/**
 * Service Access Point (SAP) used by the UE RRC to send messages to
 * the eNB. Each method defined in this class correspond to the
 * transmission of a message that is defined in section 6.2.2 of TS
 * 36.331. 
 */
class LteUeRrcSapUser : public LteRrcSap
{
public:

  struct SetupParameters 
  {
    LteRlcSapProvider* srb0SapProvider;
    LtePdcpSapProvider* srb1SapProvider;       
  };

  virtual void Setup (SetupParameters params) = 0;
  virtual void Reestablish () = 0;
  virtual void SendRrcConnectionRequest (RrcConnectionRequest msg) = 0;
  virtual void SendRrcConnectionSetupCompleted (RrcConnectionSetupCompleted msg) = 0;
  virtual void SendRrcConnectionReconfigurationCompleted (RrcConnectionReconfigurationCompleted msg) = 0;
  virtual void SendRrcConnectionReestablishmentRequest (RrcConnectionReestablishmentRequest msg) = 0;
  virtual void SendRrcConnectionReestablishmentComplete (RrcConnectionReestablishmentComplete msg) = 0;

};


/**
 * Service Access Point (SAP) used to let the UE RRC receive a message
 * from the eNB RRC. Each method defined in this class correspond to
 * the reception of a message that is defined in section 6.2.2 of TS
 * 36.331. 
 */
class LteUeRrcSapProvider : public LteRrcSap
{
public:

  virtual void RecvMasterInformationBlock (MasterInformationBlock msg) = 0;
  virtual void RecvSystemInformationBlockType1 (SystemInformationBlockType1 msg) = 0;
  virtual void RecvSystemInformation (SystemInformation msg) = 0;
  virtual void RecvRrcConnectionSetup (RrcConnectionSetup msg) = 0;
  virtual void RecvRrcConnectionReconfiguration (RrcConnectionReconfiguration msg) = 0;
  virtual void RecvRrcConnectionReestablishment (RrcConnectionReestablishment msg) = 0;
  virtual void RecvRrcConnectionReestablishmentReject (RrcConnectionReestablishmentReject msg) = 0;
  virtual void RecvRrcConnectionRelease (RrcConnectionRelease msg) = 0;

};


/**
 * Service Access Point (SAP) used by the eNB RRC to send messages to
 * the UE RC.  Each method defined in this class correspond to
 * the transmission of a message that is defined in section 6.2.2 of TS
 * 36.331. 
 */
class LteEnbRrcSapUser : public LteRrcSap
{
public:

  struct SetupUeParameters 
  {
    LteRlcSapProvider* srb0SapProvider;
    LtePdcpSapProvider* srb1SapProvider;       
  };

  virtual void SetupUe (uint16_t rnti, SetupUeParameters params) = 0;
  virtual void RemoveUe (uint16_t rnti) = 0;
  virtual void SendSystemInformationBlockType1 (SystemInformationBlockType1 msg) = 0;
  virtual void SendSystemInformation (SystemInformation msg) = 0;
  virtual void SendRrcConnectionSetup (uint16_t rnti, RrcConnectionSetup msg) = 0;
  virtual void SendRrcConnectionReconfiguration (uint16_t rnti, RrcConnectionReconfiguration msg) = 0;
  virtual void SendRrcConnectionReestablishment (uint16_t rnti, RrcConnectionReestablishment msg) = 0;
  virtual void SendRrcConnectionReestablishmentReject (uint16_t rnti, RrcConnectionReestablishmentReject msg) = 0;
  virtual void SendRrcConnectionRelease (uint16_t rnti, RrcConnectionRelease msg) = 0;
  virtual Ptr<Packet> EncodeHandoverPreparationInformation (HandoverPreparationInfo msg) = 0;
  virtual HandoverPreparationInfo DecodeHandoverPreparationInformation (Ptr<Packet> p) = 0;
  virtual Ptr<Packet> EncodeHandoverCommand (RrcConnectionReconfiguration msg) = 0;
  virtual RrcConnectionReconfiguration DecodeHandoverCommand (Ptr<Packet> p) = 0;

};


/**
 * Service Access Point (SAP) used to let the eNB RRC receive a
 * message from a UE RRC.  Each method defined in this class correspond to
 * the reception of a message that is defined in section 6.2.2 of TS
 * 36.331. 
 */
class LteEnbRrcSapProvider : public LteRrcSap
{
public:
   

  struct CompleteSetupUeParameters 
  {
    LteRlcSapUser* srb0SapUser;
    LtePdcpSapUser* srb1SapUser;       
  };

  virtual void CompleteSetupUe (uint16_t rnti, CompleteSetupUeParameters params) = 0;
  virtual void RecvRrcConnectionRequest (uint16_t rnti, RrcConnectionRequest msg) = 0;
  virtual void RecvRrcConnectionSetupCompleted (uint16_t rnti, RrcConnectionSetupCompleted msg) = 0;
  virtual void RecvRrcConnectionReconfigurationCompleted (uint16_t rnti, RrcConnectionReconfigurationCompleted msg) = 0;
  virtual void RecvRrcConnectionReestablishmentRequest (uint16_t rnti, RrcConnectionReestablishmentRequest msg) = 0;
  virtual void RecvRrcConnectionReestablishmentComplete (uint16_t rnti, RrcConnectionReestablishmentComplete msg) = 0;

};






////////////////////////////////////
//   templates
////////////////////////////////////


/**
 * Template for the implementation of the LteUeRrcSapUser as a member
 * of an owner class of type C to which all methods are forwarded
 * 
 */
template <class C>
class MemberLteUeRrcSapUser : public LteUeRrcSapUser
{
public:
  MemberLteUeRrcSapUser (C* owner);

  // inherited from LteUeRrcSapUser
  virtual void Setup (SetupParameters params);
  virtual void Reestablish ();
  virtual void SendRrcConnectionRequest (RrcConnectionRequest msg);
  virtual void SendRrcConnectionSetupCompleted (RrcConnectionSetupCompleted msg);
  virtual void SendRrcConnectionReconfigurationCompleted (RrcConnectionReconfigurationCompleted msg);
  virtual void SendRrcConnectionReestablishmentRequest (RrcConnectionReestablishmentRequest msg);
  virtual void SendRrcConnectionReestablishmentComplete (RrcConnectionReestablishmentComplete msg);

private:
  MemberLteUeRrcSapUser ();
  C* m_owner;
};

template <class C>
MemberLteUeRrcSapUser<C>::MemberLteUeRrcSapUser (C* owner)
  : m_owner (owner)
{
}

template <class C>
MemberLteUeRrcSapUser<C>::MemberLteUeRrcSapUser ()
{
}

template <class C>
void 
MemberLteUeRrcSapUser<C>::Setup (SetupParameters params)
{
  m_owner->DoSetup (params);
}

template <class C>
void 
MemberLteUeRrcSapUser<C>::Reestablish ()
{
  m_owner->DoReestablish ();
}

template <class C>
void 
MemberLteUeRrcSapUser<C>::SendRrcConnectionRequest (RrcConnectionRequest msg)
{
  m_owner->DoSendRrcConnectionRequest (msg);
}

template <class C>
void 
MemberLteUeRrcSapUser<C>::SendRrcConnectionSetupCompleted (RrcConnectionSetupCompleted msg)
{
  m_owner->DoSendRrcConnectionSetupCompleted (msg);
}

template <class C>
void 
MemberLteUeRrcSapUser<C>::SendRrcConnectionReconfigurationCompleted (RrcConnectionReconfigurationCompleted msg) 
{
  m_owner->DoSendRrcConnectionReconfigurationCompleted (msg) ;
}

template <class C>
void 
MemberLteUeRrcSapUser<C>::SendRrcConnectionReestablishmentRequest (RrcConnectionReestablishmentRequest msg)
{
  m_owner->DoSendRrcConnectionReestablishmentRequest (msg);
}

template <class C>
void 
MemberLteUeRrcSapUser<C>::SendRrcConnectionReestablishmentComplete (RrcConnectionReestablishmentComplete msg)
{
  m_owner->DoSendRrcConnectionReestablishmentComplete (msg);
}

/**
 * Template for the implementation of the LteUeRrcSapProvider as a member
 * of an owner class of type C to which all methods are forwarded
 * 
 */
template <class C>
class MemberLteUeRrcSapProvider : public LteUeRrcSapProvider
{
public:
  MemberLteUeRrcSapProvider (C* owner);

  // methods inherited from LteUeRrcSapProvider go here  
  virtual void RecvMasterInformationBlock (MasterInformationBlock msg);
  virtual void RecvSystemInformationBlockType1 (SystemInformationBlockType1 msg);
  virtual void RecvSystemInformation (SystemInformation msg);
  virtual void RecvRrcConnectionSetup (RrcConnectionSetup msg);
  virtual void RecvRrcConnectionReconfiguration (RrcConnectionReconfiguration msg);
  virtual void RecvRrcConnectionReestablishment (RrcConnectionReestablishment msg);
  virtual void RecvRrcConnectionReestablishmentReject (RrcConnectionReestablishmentReject msg);
  virtual void RecvRrcConnectionRelease (RrcConnectionRelease msg);

private:
  MemberLteUeRrcSapProvider ();
  C* m_owner;
};

template <class C>
MemberLteUeRrcSapProvider<C>::MemberLteUeRrcSapProvider (C* owner)
  : m_owner (owner)
{
}

template <class C>
MemberLteUeRrcSapProvider<C>::MemberLteUeRrcSapProvider ()
{
}

template <class C>
void 
MemberLteUeRrcSapProvider<C>::RecvMasterInformationBlock (MasterInformationBlock msg)
{
  m_owner->DoRecvMasterInformationBlock (msg);
}

template <class C>
void 
MemberLteUeRrcSapProvider<C>::RecvSystemInformationBlockType1 (SystemInformationBlockType1 msg)
{
  m_owner->DoRecvSystemInformationBlockType1 (msg);
}

template <class C>
void 
MemberLteUeRrcSapProvider<C>::RecvSystemInformation (SystemInformation msg)
{
  m_owner->DoRecvSystemInformation (msg);
}

template <class C>
void 
MemberLteUeRrcSapProvider<C>::RecvRrcConnectionSetup (RrcConnectionSetup msg)
{
  m_owner->DoRecvRrcConnectionSetup (msg);
}

template <class C>
void 
MemberLteUeRrcSapProvider<C>::RecvRrcConnectionReconfiguration (RrcConnectionReconfiguration msg)
{
  m_owner->DoRecvRrcConnectionReconfiguration (msg);
}

template <class C>
void 
MemberLteUeRrcSapProvider<C>::RecvRrcConnectionReestablishment (RrcConnectionReestablishment msg)
{
  m_owner->DoRecvRrcConnectionReestablishment (msg);
}

template <class C>
void 
MemberLteUeRrcSapProvider<C>::RecvRrcConnectionReestablishmentReject (RrcConnectionReestablishmentReject msg)
{
  m_owner->DoRecvRrcConnectionReestablishmentReject (msg);
}

template <class C>
void 
MemberLteUeRrcSapProvider<C>::RecvRrcConnectionRelease (RrcConnectionRelease msg)
{
  m_owner->DoRecvRrcConnectionRelease (msg);
}



/**
 * Template for the implementation of the LteEnbRrcSapUser as a member
 * of an owner class of type C to which all methods are forwarded
 * 
 */
template <class C>
class MemberLteEnbRrcSapUser : public LteEnbRrcSapUser
{
public:
  MemberLteEnbRrcSapUser (C* owner);

  // inherited from LteEnbRrcSapUser

  virtual void SetupUe (uint16_t rnti, SetupUeParameters params);
  virtual void RemoveUe (uint16_t rnti);
  virtual void SendMasterInformationBlock (MasterInformationBlock msg);
  virtual void SendSystemInformationBlockType1 (SystemInformationBlockType1 msg);
  virtual void SendSystemInformation (SystemInformation msg);
  virtual void SendRrcConnectionSetup (uint16_t rnti, RrcConnectionSetup msg);
  virtual void SendRrcConnectionReconfiguration (uint16_t rnti, RrcConnectionReconfiguration msg);
  virtual void SendRrcConnectionReestablishment (uint16_t rnti, RrcConnectionReestablishment msg);
  virtual void SendRrcConnectionReestablishmentReject (uint16_t rnti, RrcConnectionReestablishmentReject msg);
  virtual void SendRrcConnectionRelease (uint16_t rnti, RrcConnectionRelease msg);
  virtual Ptr<Packet> EncodeHandoverPreparationInformation (HandoverPreparationInfo msg);
  virtual HandoverPreparationInfo DecodeHandoverPreparationInformation (Ptr<Packet> p);
  virtual Ptr<Packet> EncodeHandoverCommand (RrcConnectionReconfiguration msg);
  virtual RrcConnectionReconfiguration DecodeHandoverCommand (Ptr<Packet> p);

private:
  MemberLteEnbRrcSapUser ();
  C* m_owner;
};

template <class C>
MemberLteEnbRrcSapUser<C>::MemberLteEnbRrcSapUser (C* owner)
  : m_owner (owner)
{
}

template <class C>
MemberLteEnbRrcSapUser<C>::MemberLteEnbRrcSapUser ()
{
}

template <class C>
void 
MemberLteEnbRrcSapUser<C>::SetupUe (uint16_t rnti, SetupUeParameters params)
{
  m_owner->DoSetupUe (rnti, params);
}

template <class C>
void 
MemberLteEnbRrcSapUser<C>::RemoveUe (uint16_t rnti)
{
  m_owner->DoRemoveUe (rnti);
}

template <class C>
void 
MemberLteEnbRrcSapUser<C>::SendMasterInformationBlock (MasterInformationBlock msg)
{
  m_owner->DoSendMasterInformationBlock (msg);
}

template <class C>
void 
MemberLteEnbRrcSapUser<C>::SendSystemInformationBlockType1 (SystemInformationBlockType1 msg)
{
  m_owner->DoSendSystemInformationBlockType1 (msg);
}

template <class C>
void 
MemberLteEnbRrcSapUser<C>::SendSystemInformation (SystemInformation msg)
{
  m_owner->DoSendSystemInformation (msg);
}

template <class C>
void 
MemberLteEnbRrcSapUser<C>::SendRrcConnectionSetup (uint16_t rnti, RrcConnectionSetup msg) 
{
  m_owner->DoSendRrcConnectionSetup (rnti, msg) ;
}

template <class C>
void 
MemberLteEnbRrcSapUser<C>::SendRrcConnectionReconfiguration (uint16_t rnti, RrcConnectionReconfiguration msg)
{
  m_owner->DoSendRrcConnectionReconfiguration (rnti, msg);
}

template <class C>
void 
MemberLteEnbRrcSapUser<C>::SendRrcConnectionReestablishment (uint16_t rnti, RrcConnectionReestablishment msg)
{
  m_owner->DoSendRrcConnectionReestablishment (rnti, msg);
}

template <class C>
void 
MemberLteEnbRrcSapUser<C>::SendRrcConnectionReestablishmentReject (uint16_t rnti, RrcConnectionReestablishmentReject msg)
{
  m_owner->DoSendRrcConnectionReestablishmentReject (rnti, msg);
}

template <class C>
void 
MemberLteEnbRrcSapUser<C>::SendRrcConnectionRelease (uint16_t rnti, RrcConnectionRelease msg)
{
  m_owner->DoSendRrcConnectionRelease (rnti, msg);
}

template <class C>
Ptr<Packet> 
MemberLteEnbRrcSapUser<C>::EncodeHandoverPreparationInformation (HandoverPreparationInfo msg)
{
  return m_owner->DoEncodeHandoverPreparationInformation (msg);
}

template <class C>
LteRrcSap::HandoverPreparationInfo 
MemberLteEnbRrcSapUser<C>::DecodeHandoverPreparationInformation (Ptr<Packet> p)
{
  return m_owner->DoDecodeHandoverPreparationInformation (p);
}


template <class C>
Ptr<Packet>  
MemberLteEnbRrcSapUser<C>::EncodeHandoverCommand (RrcConnectionReconfiguration msg)
{
  return m_owner->DoEncodeHandoverCommand (msg);
}

template <class C>
LteRrcSap::RrcConnectionReconfiguration  
MemberLteEnbRrcSapUser<C>::DecodeHandoverCommand (Ptr<Packet> p)
{
  return m_owner->DoDecodeHandoverCommand (p);
}

/**
 * Template for the implementation of the LteEnbRrcSapProvider as a member
 * of an owner class of type C to which all methods are forwarded
 * 
 */
template <class C>
class MemberLteEnbRrcSapProvider : public LteEnbRrcSapProvider
{
public:
  MemberLteEnbRrcSapProvider (C* owner);

  // methods inherited from LteEnbRrcSapProvider go here  
  
  virtual void CompleteSetupUe (uint16_t rnti, CompleteSetupUeParameters params);
  virtual void RecvRrcConnectionRequest (uint16_t rnti, RrcConnectionRequest msg);
  virtual void RecvRrcConnectionSetupCompleted (uint16_t rnti, RrcConnectionSetupCompleted msg);
  virtual void RecvRrcConnectionReconfigurationCompleted (uint16_t rnti, RrcConnectionReconfigurationCompleted msg);
  virtual void RecvRrcConnectionReestablishmentRequest (uint16_t rnti, RrcConnectionReestablishmentRequest msg);
  virtual void RecvRrcConnectionReestablishmentComplete (uint16_t rnti, RrcConnectionReestablishmentComplete msg);

private:
  MemberLteEnbRrcSapProvider ();
  C* m_owner;
};

template <class C>
MemberLteEnbRrcSapProvider<C>::MemberLteEnbRrcSapProvider (C* owner)
  : m_owner (owner)
{
}

template <class C>
MemberLteEnbRrcSapProvider<C>::MemberLteEnbRrcSapProvider ()
{
}

template <class C>
void 
MemberLteEnbRrcSapProvider<C>::CompleteSetupUe (uint16_t rnti, CompleteSetupUeParameters params)
{
  m_owner->DoCompleteSetupUe (rnti, params);
}

template <class C>
void 
MemberLteEnbRrcSapProvider<C>::RecvRrcConnectionRequest (uint16_t rnti, RrcConnectionRequest msg)
{
  m_owner->DoRecvRrcConnectionRequest (rnti, msg);
}

template <class C>
void 
MemberLteEnbRrcSapProvider<C>::RecvRrcConnectionSetupCompleted (uint16_t rnti, RrcConnectionSetupCompleted msg)
{
  m_owner->DoRecvRrcConnectionSetupCompleted (rnti, msg);
}

template <class C>
void 
MemberLteEnbRrcSapProvider<C>::RecvRrcConnectionReconfigurationCompleted (uint16_t rnti, RrcConnectionReconfigurationCompleted msg)
{
  m_owner->DoRecvRrcConnectionReconfigurationCompleted (rnti, msg);
}

template <class C>
void 
MemberLteEnbRrcSapProvider<C>::RecvRrcConnectionReestablishmentRequest (uint16_t rnti, RrcConnectionReestablishmentRequest msg)
{
  m_owner->DoRecvRrcConnectionReestablishmentRequest (rnti, msg);
}

template <class C>
void 
MemberLteEnbRrcSapProvider<C>::RecvRrcConnectionReestablishmentComplete (uint16_t rnti, RrcConnectionReestablishmentComplete msg)
{
  m_owner->DoRecvRrcConnectionReestablishmentComplete (rnti, msg);
}















} // namespace ns3


#endif // LTE_RRC_SAP_H



