// $Id: HI_simple_sim.cc,v 1.3 2010/11/07 16:38:57 krajczar Exp $

#include "../interface/HI_simple_sim.h"

/*****************************************************************************/
HI_simple_sim::HI_simple_sim(const edm::ParameterSet& pset)
{
  resultFileLabel       = pset.getParameter<string>("file");
  hasL1Triggers_        = pset.getParameter<bool>("hasL1Triggers");
  produceVertexLocally_ = pset.getParameter<bool>("produceVertexLocally");
  src_                  = pset.getParameter<edm::InputTag>("src");
  vertexColl_           = pset.getParameter<edm::InputTag>("vertexColl");
  triggerLabel_         = pset.getParameter<edm::InputTag>("triggerLabel");
}

/*****************************************************************************/
HI_simple_sim::~HI_simple_sim()
{
}

/*****************************************************************************/
void HI_simple_sim::beginJob()
{

  // Root
  resultFile = new TFile(resultFileLabel.c_str(),"recreate","",6);
  TDirectory::TContext context(resultFile);

  //multiplicity
  hNum_0 = new TH1F("hNum_0","hNum_0",1,-0.5,0.5);
  hNum_1 = new TH1F("hNum_1","hNum_1",1,-0.5,0.5);
  hNum_2 = new TH1F("hNum_2","hNum_2",1,-0.5,0.5);
  hNum_3 = new TH1F("hNum_3","hNum_3",1,-0.5,0.5);

  multProp = new TNtuple("multProp","multProp",
     "centBin:lowEdge:B_mc:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:clusters:rver_z:isTrigger_1:isTrigger_2:isTrigger_3:HLT_HIZeroBias:HLT_HIZeroBiasPixel_SingleTrack:HLT_HIMinBiasBSC:HLT_HIMinBiasBSC_Core:HLT_HIMinBiasHF:HLT_HIMinBiasPixel_SingleTrack:HLT_HIL1Tech_BSC_minBias:HLT_HIL1Tech_BSC_minBias_OR:HLT_HIL1Tech_BSC_HighMultiplicity:HLT_HIL1Tech_HCAL_HF:HLT_HIClusterVertexCompatibility:HLT_HICentralityVeto:HLT_HIL1ETT30:HLT_HIL1ETT30_Core:HLT_HIL1ETT60:HLT_HIL1ETT60_Core:bit0:bit1:bit2:bit3:bit4:bit5:bit6:bit7:bit8:bit9:bit10:bit11:bit12:bit32:bit33:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:bit55:bit60:bit61:bit62:bit63:L1_ZeroBias:L1_BscMinBiasOR_BptxAND:L1_BscMinBiasInnerThreshold1_BptxAND:L1_BscMinBiasInnerThreshold2_BptxAND:L1_BscMinBiasThreshold1_BptxAND:L1_BscMinBiasThreshold2_BptxAND:L1_DoubleHfBitCountsRing1_P1N1:L1_DoubleHfBitCountsRing2_P1N1:L1_DoubleHfRingEtSumsRing1_P4N4:L1_DoubleHfRingEtSumsRing1_P200N200:L1_DoubleHfRingEtSumsRing2_P4N4:L1_DoubleHfRingEtSumsRing2_P200N200:L1_ZdcScintTightVertex_BptxAND:L1_ZdcScintLooseVertex_BptxAND:L1_BscMinBiasThreshold1:L1_ZdcCaloPlus:L1_ZdcCaloMinus:L1_ZdcCaloPlus_BptxAND:L1_ZdcCaloMinus_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND:L1_HcalHfMmOrPpOrPm:L1_HcalHfCoincidencePm:L1_HcalHfMmpOrMpp:L1_HcalHoTotalOR:L1_ETT60:L1_ETT60_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_ETT30_BptxAND:L1_ETT30:L1_ZdcScintTightVertex:L1_ZdcScintPlus:L1_ZdcScintMinus:L1_BscMinBiasInnerThreshold1:L1_BptxPlusANDMinus:L1_BscMinBiasOR_BptxPlusORMinus:numVtx:numEv:procID:T_truth_etaP6:T_truth_etaP5:T_truth_etaP4:T_truth_etaP3:T_truth_etaP2:T_truth_etaP1:T_truth_etaN1:T_truth_etaN2:T_truth_etaN3:T_truth_etaN4:T_truth_etaN5:T_truth_etaN6:T_truth_etaP6_eff:T_truth_etaP5_eff:T_truth_etaP4_eff:T_truth_etaP3_eff:T_truth_etaP2_eff:T_truth_etaP1_eff:T_truth_etaN1_eff:T_truth_etaN2_eff:T_truth_etaN3_eff:T_truth_etaN4_eff:T_truth_etaN5_eff:T_truth_etaN6_eff:clusters_on_layers:clustSizeY_etaP6:clustSizeY_etaP5:clustSizeY_etaP4:clustSizeY_etaP3:clustSizeY_etaP2:clustSizeY_etaP1:clustSizeY_etaN1:clustSizeY_etaN2:clustSizeY_etaN3:clustSizeY_etaN4:clustSizeY_etaN5:clustSizeY_etaN6:cluster_counter");
  nd_multProp = new TNtuple("nd_multProp","nd_multProp",
     "centBin:lowEdge:B_mc:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:clusters:rver_z:isTrigger_1:isTrigger_2:isTrigger_3:HLT_HIZeroBias:HLT_HIZeroBiasPixel_SingleTrack:HLT_HIMinBiasBSC:HLT_HIMinBiasBSC_Core:HLT_HIMinBiasHF:HLT_HIMinBiasPixel_SingleTrack:HLT_HIL1Tech_BSC_minBias:HLT_HIL1Tech_BSC_minBias_OR:HLT_HIL1Tech_BSC_HighMultiplicity:HLT_HIL1Tech_HCAL_HF:HLT_HIClusterVertexCompatibility:HLT_HICentralityVeto:HLT_HIL1ETT30:HLT_HIL1ETT30_Core:HLT_HIL1ETT60:HLT_HIL1ETT60_Core:bit0:bit1:bit2:bit3:bit4:bit5:bit6:bit7:bit8:bit9:bit10:bit11:bit12:bit32:bit33:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:bit55:bit60:bit61:bit62:bit63:L1_ZeroBias:L1_BscMinBiasOR_BptxAND:L1_BscMinBiasInnerThreshold1_BptxAND:L1_BscMinBiasInnerThreshold2_BptxAND:L1_BscMinBiasThreshold1_BptxAND:L1_BscMinBiasThreshold2_BptxAND:L1_DoubleHfBitCountsRing1_P1N1:L1_DoubleHfBitCountsRing2_P1N1:L1_DoubleHfRingEtSumsRing1_P4N4:L1_DoubleHfRingEtSumsRing1_P200N200:L1_DoubleHfRingEtSumsRing2_P4N4:L1_DoubleHfRingEtSumsRing2_P200N200:L1_ZdcScintTightVertex_BptxAND:L1_ZdcScintLooseVertex_BptxAND:L1_BscMinBiasThreshold1:L1_ZdcCaloPlus:L1_ZdcCaloMinus:L1_ZdcCaloPlus_BptxAND:L1_ZdcCaloMinus_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND:L1_HcalHfMmOrPpOrPm:L1_HcalHfCoincidencePm:L1_HcalHfMmpOrMpp:L1_HcalHoTotalOR:L1_ETT60:L1_ETT60_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_ETT30_BptxAND:L1_ETT30:L1_ZdcScintTightVertex:L1_ZdcScintPlus:L1_ZdcScintMinus:L1_BscMinBiasInnerThreshold1:L1_BptxPlusANDMinus:L1_BscMinBiasOR_BptxPlusORMinus:numVtx:numEv:procID:T_truth_etaP6:T_truth_etaP5:T_truth_etaP4:T_truth_etaP3:T_truth_etaP2:T_truth_etaP1:T_truth_etaN1:T_truth_etaN2:T_truth_etaN3:T_truth_etaN4:T_truth_etaN5:T_truth_etaN6:T_truth_etaP6_eff:T_truth_etaP5_eff:T_truth_etaP4_eff:T_truth_etaP3_eff:T_truth_etaP2_eff:T_truth_etaP1_eff:T_truth_etaN1_eff:T_truth_etaN2_eff:T_truth_etaN3_eff:T_truth_etaN4_eff:T_truth_etaN5_eff:T_truth_etaN6_eff:clusters_on_layers:clustSizeY_etaP6:clustSizeY_etaP5:clustSizeY_etaP4:clustSizeY_etaP3:clustSizeY_etaP2:clustSizeY_etaP1:clustSizeY_etaN1:clustSizeY_etaN2:clustSizeY_etaN3:clustSizeY_etaN4:clustSizeY_etaN5:clustSizeY_etaN6:cluster_counter");
  rd_multProp = new TNtuple("rd_multProp","rd_multProp",
     "centBin:lowEdge:B_mc:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:clusters:rver_z:isTrigger_1:isTrigger_2:isTrigger_3:HLT_HIZeroBias:HLT_HIZeroBiasPixel_SingleTrack:HLT_HIMinBiasBSC:HLT_HIMinBiasBSC_Core:HLT_HIMinBiasHF:HLT_HIMinBiasPixel_SingleTrack:HLT_HIL1Tech_BSC_minBias:HLT_HIL1Tech_BSC_minBias_OR:HLT_HIL1Tech_BSC_HighMultiplicity:HLT_HIL1Tech_HCAL_HF:HLT_HIClusterVertexCompatibility:HLT_HICentralityVeto:HLT_HIL1ETT30:HLT_HIL1ETT30_Core:HLT_HIL1ETT60:HLT_HIL1ETT60_Core:bit0:bit1:bit2:bit3:bit4:bit5:bit6:bit7:bit8:bit9:bit10:bit11:bit12:bit32:bit33:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:bit55:bit60:bit61:bit62:bit63:L1_ZeroBias:L1_BscMinBiasOR_BptxAND:L1_BscMinBiasInnerThreshold1_BptxAND:L1_BscMinBiasInnerThreshold2_BptxAND:L1_BscMinBiasThreshold1_BptxAND:L1_BscMinBiasThreshold2_BptxAND:L1_DoubleHfBitCountsRing1_P1N1:L1_DoubleHfBitCountsRing2_P1N1:L1_DoubleHfRingEtSumsRing1_P4N4:L1_DoubleHfRingEtSumsRing1_P200N200:L1_DoubleHfRingEtSumsRing2_P4N4:L1_DoubleHfRingEtSumsRing2_P200N200:L1_ZdcScintTightVertex_BptxAND:L1_ZdcScintLooseVertex_BptxAND:L1_BscMinBiasThreshold1:L1_ZdcCaloPlus:L1_ZdcCaloMinus:L1_ZdcCaloPlus_BptxAND:L1_ZdcCaloMinus_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND:L1_HcalHfMmOrPpOrPm:L1_HcalHfCoincidencePm:L1_HcalHfMmpOrMpp:L1_HcalHoTotalOR:L1_ETT60:L1_ETT60_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_ETT30_BptxAND:L1_ETT30:L1_ZdcScintTightVertex:L1_ZdcScintPlus:L1_ZdcScintMinus:L1_BscMinBiasInnerThreshold1:L1_BptxPlusANDMinus:L1_BscMinBiasOR_BptxPlusORMinus:numVtx:numEv:procID:T_truth_etaP6:T_truth_etaP5:T_truth_etaP4:T_truth_etaP3:T_truth_etaP2:T_truth_etaP1:T_truth_etaN1:T_truth_etaN2:T_truth_etaN3:T_truth_etaN4:T_truth_etaN5:T_truth_etaN6:T_truth_etaP6_eff:T_truth_etaP5_eff:T_truth_etaP4_eff:T_truth_etaP3_eff:T_truth_etaP2_eff:T_truth_etaP1_eff:T_truth_etaN1_eff:T_truth_etaN2_eff:T_truth_etaN3_eff:T_truth_etaN4_eff:T_truth_etaN5_eff:T_truth_etaN6_eff:clusters_on_layers:clustSizeY_etaP6:clustSizeY_etaP5:clustSizeY_etaP4:clustSizeY_etaP3:clustSizeY_etaP2:clustSizeY_etaP1:clustSizeY_etaN1:clustSizeY_etaN2:clustSizeY_etaN3:clustSizeY_etaN4:clustSizeY_etaN5:clustSizeY_etaN6:cluster_counter");
  multProp_looper = new TNtuple("multProp_looper","multProp_looper",
      "centBin:lowEdge:B_mc:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:isTrigger_1:isTrigger_2:isTrigger_3:rver_z:eta:eta_det:phi:eloss:type:numVtx:clustSizeY:clustSizeX:length:pixels:cluster_counter:HLT_HIZeroBias:HLT_HIZeroBiasPixel_SingleTrack:HLT_HIMinBiasBSC:HLT_HIMinBiasBSC_Core:HLT_HIMinBiasHF:HLT_HIMinBiasPixel_SingleTrack:HLT_HIL1Tech_BSC_minBias:HLT_HIL1Tech_BSC_minBias_OR:HLT_HIL1Tech_BSC_HighMultiplicity:HLT_HIL1Tech_HCAL_HF:HLT_HIClusterVertexCompatibility:HLT_HICentralityVeto:HLT_HIL1ETT30:HLT_HIL1ETT30_Core:HLT_HIL1ETT60:HLT_HIL1ETT60_Core:bit0:bit1:bit2:bit3:bit4:bit5:bit6:bit7:bit8:bit9:bit10:bit11:bit12:bit32:bit33:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:bit55:bit60:bit61:bit62:bit63:L1_ZeroBias:L1_BscMinBiasOR_BptxAND:L1_BscMinBiasInnerThreshold1_BptxAND:L1_BscMinBiasInnerThreshold2_BptxAND:L1_BscMinBiasThreshold1_BptxAND:L1_BscMinBiasThreshold2_BptxAND:L1_DoubleHfBitCountsRing1_P1N1:L1_DoubleHfBitCountsRing2_P1N1:L1_DoubleHfRingEtSumsRing1_P4N4:L1_DoubleHfRingEtSumsRing1_P200N200:L1_DoubleHfRingEtSumsRing2_P4N4:L1_DoubleHfRingEtSumsRing2_P200N200:L1_ZdcScintTightVertex_BptxAND:L1_ZdcScintLooseVertex_BptxAND:L1_BscMinBiasThreshold1:L1_ZdcCaloPlus:L1_ZdcCaloMinus:L1_ZdcCaloPlus_BptxAND:L1_ZdcCaloMinus_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND:L1_HcalHfMmOrPpOrPm:L1_HcalHfCoincidencePm:L1_HcalHfMmpOrMpp:L1_HcalHoTotalOR:L1_ETT60:L1_ETT60_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_ETT30_BptxAND:L1_ETT30:L1_ZdcScintTightVertex:L1_ZdcScintPlus:L1_ZdcScintMinus:L1_BscMinBiasInnerThreshold1:L1_BptxPlusANDMinus:L1_BscMinBiasOR_BptxPlusORMinus");
  nd_multProp_looper = new TNtuple("nd_multProp_looper","nd_multProp_looper",
      "centBin:lowEdge:B_mc:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:isTrigger_1:isTrigger_2:isTrigger_3:rver_z:eta:eta_det:phi:eloss:type:numVtx:clustSizeY:clustSizeX:length:pixels:cluster_counter:HLT_HIZeroBias:HLT_HIZeroBiasPixel_SingleTrack:HLT_HIMinBiasBSC:HLT_HIMinBiasBSC_Core:HLT_HIMinBiasHF:HLT_HIMinBiasPixel_SingleTrack:HLT_HIL1Tech_BSC_minBias:HLT_HIL1Tech_BSC_minBias_OR:HLT_HIL1Tech_BSC_HighMultiplicity:HLT_HIL1Tech_HCAL_HF:HLT_HIClusterVertexCompatibility:HLT_HICentralityVeto:HLT_HIL1ETT30:HLT_HIL1ETT30_Core:HLT_HIL1ETT60:HLT_HIL1ETT60_Core:bit0:bit1:bit2:bit3:bit4:bit5:bit6:bit7:bit8:bit9:bit10:bit11:bit12:bit32:bit33:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:bit55:bit60:bit61:bit62:bit63:L1_ZeroBias:L1_BscMinBiasOR_BptxAND:L1_BscMinBiasInnerThreshold1_BptxAND:L1_BscMinBiasInnerThreshold2_BptxAND:L1_BscMinBiasThreshold1_BptxAND:L1_BscMinBiasThreshold2_BptxAND:L1_DoubleHfBitCountsRing1_P1N1:L1_DoubleHfBitCountsRing2_P1N1:L1_DoubleHfRingEtSumsRing1_P4N4:L1_DoubleHfRingEtSumsRing1_P200N200:L1_DoubleHfRingEtSumsRing2_P4N4:L1_DoubleHfRingEtSumsRing2_P200N200:L1_ZdcScintTightVertex_BptxAND:L1_ZdcScintLooseVertex_BptxAND:L1_BscMinBiasThreshold1:L1_ZdcCaloPlus:L1_ZdcCaloMinus:L1_ZdcCaloPlus_BptxAND:L1_ZdcCaloMinus_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND:L1_HcalHfMmOrPpOrPm:L1_HcalHfCoincidencePm:L1_HcalHfMmpOrMpp:L1_HcalHoTotalOR:L1_ETT60:L1_ETT60_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_ETT30_BptxAND:L1_ETT30:L1_ZdcScintTightVertex:L1_ZdcScintPlus:L1_ZdcScintMinus:L1_BscMinBiasInnerThreshold1:L1_BptxPlusANDMinus:L1_BscMinBiasOR_BptxPlusORMinus");
  rd_multProp_looper = new TNtuple("rd_multProp_looper","rd_multProp_looper",
      "centBin:lowEdge:B_mc:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:isTrigger_1:isTrigger_2:isTrigger_3:rver_z:eta:eta_det:phi:eloss:type:numVtx:clustSizeY:clustSizeX:length:pixels:cluster_counter:HLT_HIZeroBias:HLT_HIZeroBiasPixel_SingleTrack:HLT_HIMinBiasBSC:HLT_HIMinBiasBSC_Core:HLT_HIMinBiasHF:HLT_HIMinBiasPixel_SingleTrack:HLT_HIL1Tech_BSC_minBias:HLT_HIL1Tech_BSC_minBias_OR:HLT_HIL1Tech_BSC_HighMultiplicity:HLT_HIL1Tech_HCAL_HF:HLT_HIClusterVertexCompatibility:HLT_HICentralityVeto:HLT_HIL1ETT30:HLT_HIL1ETT30_Core:HLT_HIL1ETT60:HLT_HIL1ETT60_Core:bit0:bit1:bit2:bit3:bit4:bit5:bit6:bit7:bit8:bit9:bit10:bit11:bit12:bit32:bit33:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:bit55:bit60:bit61:bit62:bit63:L1_ZeroBias:L1_BscMinBiasOR_BptxAND:L1_BscMinBiasInnerThreshold1_BptxAND:L1_BscMinBiasInnerThreshold2_BptxAND:L1_BscMinBiasThreshold1_BptxAND:L1_BscMinBiasThreshold2_BptxAND:L1_DoubleHfBitCountsRing1_P1N1:L1_DoubleHfBitCountsRing2_P1N1:L1_DoubleHfRingEtSumsRing1_P4N4:L1_DoubleHfRingEtSumsRing1_P200N200:L1_DoubleHfRingEtSumsRing2_P4N4:L1_DoubleHfRingEtSumsRing2_P200N200:L1_ZdcScintTightVertex_BptxAND:L1_ZdcScintLooseVertex_BptxAND:L1_BscMinBiasThreshold1:L1_ZdcCaloPlus:L1_ZdcCaloMinus:L1_ZdcCaloPlus_BptxAND:L1_ZdcCaloMinus_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND:L1_HcalHfMmOrPpOrPm:L1_HcalHfCoincidencePm:L1_HcalHfMmpOrMpp:L1_HcalHoTotalOR:L1_ETT60:L1_ETT60_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_ETT30_BptxAND:L1_ETT30:L1_ZdcScintTightVertex:L1_ZdcScintPlus:L1_ZdcScintMinus:L1_BscMinBiasInnerThreshold1:L1_BptxPlusANDMinus:L1_BscMinBiasOR_BptxPlusORMinus");
  hPabsTof = new TNtuple("hPabsTof","hPabsTof",
      "pabs:tof");
  nd_hPabsTof = new TNtuple("nd_hPabsTof","nd_hPabsTof",
      "pabs:tof");
  rd_hPabsTof = new TNtuple("rd_hPabsTof","rd_hPabsTof",
      "pabs:tof");
//  hLooperPt = new TH1D("hLooperPt","hLooperPt",100,0.,5.);
//  hPt = new TH1D("hPt","hPt",100,0.,5.);
//  hNonLooperPt = new TH1D("hNonLooperPt","hNonLooperPt",100,0.,5.);
//  hProba = new TH1D("hProba","hProba",10000,0.,1000.);
  hJustLooper = new TNtuple("hJustLooper","hJustLooper","B_mc:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:rver_z:eloss:eta:numVtx:clustSizeY:cluster_counter");
  nd_hJustLooper = new TNtuple("nd_hJustLooper","nd_hJustLooper","B_mc:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:rver_z:eloss:eta:numVtx:clustSizeY:cluster_counter");
  rd_hJustLooper = new TNtuple("rd_hJustLooper","rd_hJustLooper","B_mc:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:rver_z:eloss:eta:numVtx:clustSizeY:cluster_counter");
  hLastTOF = new TH1D("hLastTOF","hLastTOF",200,0.,40.);

  //cluster vertices
  nCLusterVertices = new TNtuple("nCLusterVertices","nCLusterVertices",
     "numRecHits_l1:sver_z:rver_z");
  nClusterPrim = new TNtuple("nClusterPrim","nClusterPrim",
     "eta_corr:sizeY");
  nClusterAll = new TNtuple("nClusterAll","nClusterAll",
     "eta_corr:sizeY");
  nClusterUnused = new TNtuple("nClusterUnused","nClusterUnused",
     "eta_corr:sizeY");
  hCorrEtaSizeY = new TH2F("hCorrEtaSizeY","hCorrEtaSizeY",300,-3.,3.,20,0.,20.);
  hCorrEtaADC = new TH2F("hCorrEtaADC","hCorrEtaADC",300,-3.,3.,125,0.,2500.);
  hClusterZSizeY = new TH2F("hClusterZSizeY","hClusterZSizeY",600,-30.,30.,200,0.,20.);
  ResPureClusterY = new TH1F("ResPureClusterY","ResPureClusterY",60,0.,30.);
  ResSimRecClusterY = new TH1F("ResSimRecClusterY","ResSimRecClusterY",60,0.,30.);
  ResElseSimRecClusterY = new TH1F("ResElseSimRecClusterY","ResElseSimRecClusterY",60,0.,30.);

  NLooper = new TNtuple("NLooper","NLooper",
     "looperHits_etaP6:looperHits_etaP5:looperHits_etaP4:looperHits_etaP3:looperHits_etaP2:looperHits_etaP1:looperHits_etaN1:looperHits_etaN2:looperHits_etaN3:looperHits_etaN4:looperHits_etaN5:looperHits_etaN6:cluster_counter");
  nd_NLooper = new TNtuple("nd_NLooper","nd_NLooper",
     "looperHits_etaP6:looperHits_etaP5:looperHits_etaP4:looperHits_etaP3:looperHits_etaP2:looperHits_etaP1:looperHits_etaN1:looperHits_etaN2:looperHits_etaN3:looperHits_etaN4:looperHits_etaN5:looperHits_etaN6:cluster_counter");
  rd_NLooper = new TNtuple("rd_NLooper","rd_NLooper",
     "looperHits_etaP6:looperHits_etaP5:looperHits_etaP4:looperHits_etaP3:looperHits_etaP2:looperHits_etaP1:looperHits_etaN1:looperHits_etaN2:looperHits_etaN3:looperHits_etaN4:looperHits_etaN5:looperHits_etaN6:cluster_counter");

  hTestEtaFull = new TH1D("hTestEtaFull","hTestEtaFull",14,-3.5,3.5);
  hTestEtaFull_0 = new TH1D("hTestEtaFull_0","hTestEtaFull_0",14,-3.5,3.5);
  hTestEtaFull_1 = new TH1D("hTestEtaFull_1","hTestEtaFull_1",14,-3.5,3.5);
  hTestEtaFull_2 = new TH1D("hTestEtaFull_2","hTestEtaFull_2",14,-3.5,3.5);
  hTestEtaFull_3 = new TH1D("hTestEtaFull_3","hTestEtaFull_3",14,-3.5,3.5);
  hTestEtaRestricted = new TH1D("hTestEtaRestricted","hTestEtaRestricted",14,-3.5,3.5);  

  full = 0;
  restricted = 0;

  PureCorrEta = new TH1F("PureCorrEta","PureCorrEta",30,-3.,3.);
  PureCutCorrEta = new TH1F("PureCutCorrEta","PureCutCorrEta",30,-3.,3.);
  DesiredEtaDist = new TH1F("DesiredEtaDist","DesiredEtaDist",30,-3.,3.);
  SimRecCorrEta = new TH1F("SimRecCorrEta","SimRecCorrEta",30,-3.,3.);
  RecAdc = new TH1F("RecAdc","RecAdc",2550,0.,2550.);
  ResCentralAdc = new TH1F("ResCentralAdc","ResCentralAdc",50,0.,2550.);
  ResCentralAdcFine = new TH1F("ResCentralAdcFine","ResCentralAdcFine",50,0.,500.);
  ResElseCentralAdc = new TH1F("ResElseCentralAdc","ResElseCentralAdc",50,0.,2550.);
  ResPureAdc = new TH1F("ResPureAdc","ResPureAdc",50,0.,2550.);
  ResPureAdc_det = new TH1F("ResPureAdc_det","ResPureAdc_det",50,0.,2550.);
  ResPureCentralAdc = new TH1F("ResPureCentralAdc","ResPureCentralAdc",50,0.,2550.);
  ResPureCutAdc = new TH1F("ResPureCutAdc","ResPureCutAdc",50,0.,2550.);
  ResPureCutCentralAdc = new TH1F("ResPureCutCentralAdc","ResPureCutCentralAdc",50,0.,2550.);

  SimEnergyLoss = new TH1F("SimEnergyLoss","SimEnergyLoss",200,0.,0.003);
  RecAdcvsCorrEta = new TH2F("RecAdcvsCorrEta","RecAdcvsCorrEta",300,-3.,3.,25500,0.,2550.);
  SimRecAdcvsCorrEta = new TH2F("SimRecAdcvsCorrEta","SimRecAdcvsCorrEta",300,-3.,3.,2550,0.,2550.);
  ResSimRecAdc = new TH1F("ResSimRecAdc","ResSimRecAdc",50,0.,2550.);
  ResSimRecAdc_det = new TH1F("ResSimRecAdc_det","ResSimRecAdc_det",50,0.,2550.);
  ResSimRecAdcFine = new TH1F("ResSimRecAdcFine","ResSimRecAdcFine",80,0.,800.);
  ResSimRecAdcLog = new TH1F("ResSimRecAdcLog","ResSimRecAdcLog",50,3.,10.);
  FullResSimAdc = new TH1F("FullResSimAdc","FullResSimAdc",50,0.,2550.);
  ElseSimRecAdcvsCorrEta = new TH2F("ElseSimRecAdcvsCorrEta","ElseSimRecAdcvsCorrEta",300,-3.,3.,25500,0.,2550.);
  ResElseSimRecAdc = new TH1F("ResElseSimRecAdc","ResElseSimRecAdc",50,0.,2550.);
  ResElseSimRecAdc_det = new TH1F("ResElseSimRecAdc_det","ResElseSimRecAdc_det",50,0.,2550.);
  PureAdcvsCorrEta = new TH2F("PureAdcvsCorrEta","PureAdcvsCorrEta",300,-3.,3.,2550,0.,2550.);
  PureCutAdcvsCorrEta = new TH2F("PureCutAdcvsCorrEta","PureCutAdcvsCorrEta",300,-3.,3.,25000,0.,2550.);
  hAdcPerCoshCorrEta = new TH2F("hAdcPerCoshCorrEta","hAdcPerCoshCorrEta",300,-3.,3.,25500,0.,2550.);

  test = 0;
  proba = 0;

}

/*****************************************************************************/
void HI_simple_sim::endJob()
{
  TDirectory::TContext context(resultFile);

  hNum_0->Write();
  hNum_1->Write();
  hNum_2->Write();
  hNum_3->Write();

  multProp->Write();
  nd_multProp->Write();
  rd_multProp->Write();
  multProp_looper->Write();
  nd_multProp_looper->Write();
  rd_multProp_looper->Write();
//  hPabsTof->Write();
//  nd_hPabsTof->Write();
//  rd_hPabsTof->Write();
//  hLooperPt->Write();
//  hPt->Write();
//  hNonLooperPt->Write();
//  hProba->Write();
  hJustLooper->Write();
  nd_hJustLooper->Write();
  rd_hJustLooper->Write();
//  hLastTOF->Write();

  //clusters
//  nCLusterVertices->Write();
//  nClusterPrim->Write();
//  nClusterAll->Write();
//  nClusterUnused->Write();
  hCorrEtaSizeY->Write();
  hCorrEtaADC->Write();
  hClusterZSizeY->Write();
//  ResPureClusterY->Write();
//  ResSimRecClusterY->Write();
//  ResElseSimRecClusterY->Write();

  NLooper->Write();
  nd_NLooper->Write();
  rd_NLooper->Write();

  hTestEtaFull->Write();
  hTestEtaFull_0->Write();
  hTestEtaFull_1->Write();
  hTestEtaFull_2->Write();
  hTestEtaFull_3->Write();
  hTestEtaRestricted->Write();

  PureCorrEta->Write();
  PureCutCorrEta->Write();
  DesiredEtaDist->Write();
  SimRecCorrEta->Write();
  RecAdc->Write();
  ResCentralAdc->Write();
  ResCentralAdcFine->Write();
  ResElseCentralAdc->Write();
  ResPureAdc->Write();
  ResPureAdc_det->Write();
  ResPureCentralAdc->Write();
  ResPureCutAdc->Write();
  ResPureCutCentralAdc->Write();

//  SimEnergyLoss->Write();
  RecAdcvsCorrEta->Write();
  SimRecAdcvsCorrEta->Write();
  ResSimRecAdc->Write();
  ResSimRecAdc_det->Write();
  ResSimRecAdcFine->Write();
  ResSimRecAdcLog->Write();
  FullResSimAdc->Write();
  ElseSimRecAdcvsCorrEta->Write();
  ResElseSimRecAdc->Write();
  ResElseSimRecAdc_det->Write();
  PureAdcvsCorrEta->Write();
  PureCutAdcvsCorrEta->Write();
  hAdcPerCoshCorrEta->Write();

  resultFile->Close();
  delete resultFile;
/*
  cerr<<"Test the number of events: filling RecCut: "<<test<<endl;
  cerr<<"Test the number of events: filling SimPrim: "<<proba<<endl;
  cerr<<"FULL: "<<full<<endl;
  cerr<<"RESTRICTED: "<<restricted<<endl;
*/
}

/*****************************************************************************/
float HI_simple_sim::getVertexZ
     (edm::Handle<SiPixelRecHitCollection> siPixelRecCollection, const edm::Event& ev)
{
  float rver_z = 0.;
  if(!produceVertexLocally_) {
    edm::Handle<reco::VertexCollection> vertexCollection;
    ev.getByLabel(vertexColl_,vertexCollection);
    const reco::VertexCollection * vertices = vertexCollection.product();
    unsigned int vertex_tracks = 0;
    for(reco::VertexCollection::const_iterator
        vertex = vertices->begin(); vertex!= vertices->end(); vertex++)
    {
       if(vertex->tracksSize()>vertex_tracks) {
         vertex_tracks = vertex->tracksSize();
         rver_z = vertex->z();
       }
    }
  } else {
    rver_z = produceClusterVertex(siPixelRecCollection);
  }
  return rver_z;
}

/*****************************************************************************/
int HI_simple_sim::getContainedHits
  (vector<VertexHit> hits, float z0, float & chi)
{
  int n = 0;
  chi = 0.;

  for(vector<VertexHit>::const_iterator hit = hits.begin();
                                        hit!= hits.end(); hit++)
  {
    // Predicted cluster width in y direction
    float p = 2 * fabs(hit->z - z0)/hit->r + 0.5; // check

    if(fabs(p - hit->w) <= 1.)
    {
      chi += fabs(p - hit->w);
      n++;
    }
  }

  return n;
}

/*****************************************************************************/
float HI_simple_sim::produceClusterVertex
     (edm::Handle<SiPixelRecHitCollection> siPixelRecCollection)
{
  const SiPixelRecHitCollection* thePixelHits = siPixelRecCollection.product();

  if(thePixelHits->size() > 0)
  {
    vector<VertexHit> hits;

    for(SiPixelRecHitCollection::DataContainer::const_iterator
           recHit = thePixelHits->data().begin(),
           recHitEnd = thePixelHits->data().end();
           recHit != recHitEnd; ++recHit)
    {
      if(recHit->isValid())
      {
       	DetId id = recHit->geographicalId();
        const PixelGeomDetUnit* pgdu =
          dynamic_cast<const PixelGeomDetUnit*>(theTracker->idToDetUnit(id));
        const RectangularPixelTopology* theTopol =
          dynamic_cast<const RectangularPixelTopology*>( &(pgdu->specificTopology()) );
        vector<SiPixelCluster::Pixel> pixels = recHit->cluster()->pixels();

        bool pixelOnEdge = false;
        for(vector<SiPixelCluster::Pixel>::const_iterator
               pixel = pixels.begin(); pixel!= pixels.end(); pixel++)
        {
          int pos_x = (int)pixel->x;
          int pos_y = (int)pixel->y;

          if(theTopol->isItEdgePixelInX(pos_x) ||
              theTopol->isItEdgePixelInY(pos_y))
          { pixelOnEdge = true; break; }
        }

	if(!pixelOnEdge)
        if(id.subdetId() == int(PixelSubdetector::PixelBarrel))
        {
          PXBDetId pid(id);

          LocalPoint lpos = LocalPoint(recHit->localPosition().x(),
                                       recHit->localPosition().y(),
                                       recHit->localPosition().z());

          GlobalPoint gpos = theTracker->idToDet(id)->toGlobal(lpos);

          VertexHit hit;
          hit.z = gpos.z();
          hit.r = gpos.perp();
          hit.w = recHit->cluster()->sizeY();

          hits.push_back(hit);
        }
      }
    }

    int nhits; int nhits_max = 0;
    float chi; float chi_max = 1e+9;

    float zest = 0;

//    for(float z0 = -15.9; z0 <= 15.95; z0 += 0.1) //2TeV: sigma_z = 5.3
    for(float z0 = -22.2; z0 <= 22.25; z0 += 0.1) //900GeV: sigma_z = 7.4
    {
      nhits = getContainedHits(hits, z0, chi);

      if(nhits > 0)
      {
       	if(nhits >  nhits_max)
        { chi_max = 1e+9; nhits_max = nhits; }

        if(nhits >= nhits_max)
        if(chi < chi_max)
        { chi_max = chi; zest = z0; }
      }
    }
    return zest;
  }
  else {
    return 0.;
  }
}

/*****************************************************************************/
void HI_simple_sim::clusterVertices
    (const edm::Event& ev, const edm::EventSetup& es,
//     const reco::VertexCollection* vertices,
     edm::Handle<SiPixelRecHitCollection> siPixelRecCollection)
{
  edm::Handle<edm::SimVertexContainer> simVertices;
  ev.getByType(                        simVertices);

  float sver_z = 0;
  if((*(simVertices.product())).size() > 0)
    sver_z = (*(simVertices.product())).at(0).position().z();

  // get vertex_z
  float rver_z = getVertexZ(siPixelRecCollection, ev);

  int numRecHits_1l = 0;
  edm::ESHandle<TrackerGeometry> geom;
  es.get<TrackerDigiGeometryRecord>().get(geom);
  const SiPixelRecHitCollection pixelRecHits = *(siPixelRecCollection.product());
  for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH) {
      const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit(iPRH->geographicalId()));
      PXBDetId pdetId = PXBDetId(iPRH->geographicalId());
      int layer=pdetId.layer();
      GlobalPoint globalPosition = pgdu->toGlobal(iPRH->localPosition());
      bool isAnyPixelAtEdge = isRecHitAtTheEdge(iPRH,pgdu);
      if(!isAnyPixelAtEdge && layer == 1 && (pgdu->subDetector() == GeomDetEnumerators::PixelBarrel))
        numRecHits_1l++;
  }

  vector<float> result;
  result.push_back(numRecHits_1l);
  result.push_back(sver_z);
  result.push_back(rver_z);
  nCLusterVertices->Fill(&result[0]);

}

/*****************************************************************************/
bool HI_simple_sim::aboveTriggerThreshold_1(edm::Handle<CaloTowerCollection> towers)
{
  int negTowers = 0;
  int posTowers = 0;
  for(CaloTowerCollection::const_iterator cal = towers->begin(); cal != towers->end(); ++cal) {
     for(unsigned int i = 0; i < cal->constituentsSize(); i++) {
        const DetId id = cal->constituent(i);
        if(id.det() == DetId::Hcal) {
          HcalSubdetector subdet=(HcalSubdetector(id.subdetId()));
          if(subdet == HcalForward) {
            if(cal->energy()>3. && cal->eta()<-3.)
              negTowers++;
            if(cal->energy()>3. && cal->eta()>3.)
              posTowers++;
          }
        }
     }    
  }
  if(negTowers>0 && posTowers>0)
    return true;

  return false;
}

/*****************************************************************************/
bool HI_simple_sim::aboveTriggerThreshold_2(edm::Handle<CaloTowerCollection> towers)
{
  int negTowers = 0;
  int posTowers = 0;
  for(CaloTowerCollection::const_iterator cal = towers->begin(); cal != towers->end(); ++cal) {
     for(unsigned int i = 0; i < cal->constituentsSize(); i++) {
        const DetId id = cal->constituent(i);
        if(id.det() == DetId::Hcal) {
          HcalSubdetector subdet=(HcalSubdetector(id.subdetId()));
          if(subdet == HcalForward) {
            if(cal->energy()>3. && cal->eta()<-3.)
              negTowers++;
            if(cal->energy()>3. && cal->eta()>3.)
              posTowers++;
          }
	}
     }    
  }
  if(negTowers>1 && posTowers>1)
    return true;

  return false;
}


/*****************************************************************************/
bool HI_simple_sim::aboveTriggerThreshold_3(edm::Handle<CaloTowerCollection> towers)
{
  int negTowers = 0;
  int posTowers = 0;
  for(CaloTowerCollection::const_iterator cal = towers->begin(); cal != towers->end(); ++cal) {
     for(unsigned int i = 0; i < cal->constituentsSize(); i++) {
        const DetId id = cal->constituent(i);
        if(id.det() == DetId::Hcal) {
          HcalSubdetector subdet=(HcalSubdetector(id.subdetId()));
          if(subdet == HcalForward) {
            if(cal->energy()>3. && cal->eta()<-3.)
              negTowers++;
            if(cal->energy()>3. && cal->eta()>3.)
              posTowers++;
          }
	}
     }    
  }
  if(negTowers>2 && posTowers>2)
    return true;

  return false;
}

/*****************************************************************************/
bool HI_simple_sim::isRecHitAtTheEdge(SiPixelRecHitCollection::DataContainer::const_iterator iPRH,
                                                    const PixelGeomDetUnit* pgdu)
{
  bool isAnyPixelAtEdge = false;
  std::vector<SiPixelCluster::Pixel> pixels = (*iPRH).cluster()->pixels();
  for(std::vector<SiPixelCluster::Pixel>::const_iterator pixel = pixels.begin(); pixel != pixels.end(); pixel++) {
     int pixelX = int((*pixel).x);
     int pixelY = int((*pixel).y);
     const RectangularPixelTopology* theTopol = dynamic_cast<const RectangularPixelTopology*>( & (pgdu->specificTopology()) );
     if(theTopol->isItEdgePixelInX(pixelX) || theTopol->isItEdgePixelInY(pixelY)) {
       isAnyPixelAtEdge = true;
//       cerr<<"XXXX At the EDGE"<<endl;
     }
  }
  return isAnyPixelAtEdge;
}

/*****************************************************************************/
void HI_simple_sim::FirstSimOnFirst(edm::Handle<SiPixelRecHitCollection>& siPixelRecCollection,
//                                                  const reco::VertexCollection* vertices,
                                                  const edm::Event& ev,
                                                  const edm::EventSetup& es)
{
  // Get simulated
  edm::Handle<TrackingParticleCollection> simCollection;
//  ev.getByType(simCollection);
  ev.getByLabel("mergedtruth","MergedTrackTruth",simCollection);

  const TrackingParticleCollection *tPC = simCollection.product();

  // get vertex_z
  float rver_z = getVertexZ(siPixelRecCollection, ev);

  TrackerHitAssociator simHitFinder(ev);
  edm::ESHandle<TrackerGeometry> geom;
  es.get<TrackerDigiGeometryRecord>().get(geom);  
  const SiPixelRecHitCollection pixelRecHits = *(siPixelRecCollection.product());
  std::vector<std::vector<const SiPixelRecHit*> > tpRecHitsVectorVector;

  bool isPrim = false;
  // Loop through the TrackingParticles
  for(TrackingParticleCollection::const_iterator t = tPC->begin(); t != tPC->end(); ++t) {
     std::vector<const SiPixelRecHit*> tpRecHitVector;

        if(t->trackPSimHit().size() == 0)
          continue;
        std::vector<PSimHit> TP_pSHV = t->trackPSimHit();
        PSimHit* earliestSH = findEarliestPSimHit(TP_pSHV);

        const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit(earliestSH->detUnitId()));   //tp_psh
        if(pgdu==0)
          continue;
        PXBDetId pdetId = PXBDetId(earliestSH->detUnitId());  //tp_psh
        int layer=pdetId.layer();

        // Selection based on proccess type and first barrel layer
        // First step
        // Primary, first pixel barrel
        if(earliestSH->processType()==2 && layer == 1 && (pgdu->subDetector() == GeomDetEnumerators::PixelBarrel)) {  //tp_psh

           // Loop through all recHits and find the associated simHits
           for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH ) {
            std::vector<PSimHit> associatedSimHits = simHitFinder.associateHit(*iPRH);

              // Loop through the associated simHits, find the one we had before
              float energy_loss = 0.;
              for(std::vector<PSimHit>::const_iterator aSH = associatedSimHits.begin(); aSH != associatedSimHits.end(); aSH++ ) {
                 energy_loss += aSH->energyLoss();
                 if(comparePSimHits(&(*earliestSH), &(*aSH)) ) {   //tp_psh
                     bool alreadyStoredRecHit = false;

                     // Cycle through the RecHits stored in the vector, making sure it hasn't already been added
                     for(std::vector<const SiPixelRecHit*>::const_iterator tpRHV = tpRecHitVector.begin(); tpRHV != tpRecHitVector.end(); ++tpRHV ) {
                         if(compareRecHits((*tpRHV), &(*iPRH)))
                             alreadyStoredRecHit = true;
                     }

                     if(!alreadyStoredRecHit) {
                       tpRecHitVector.push_back(&(*iPRH));
                       // Fill eta vs ADC of primary non-loopers
                       const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((*iPRH).geographicalId()));
                       GlobalPoint globalPosition = pgdu->toGlobal((*iPRH).localPosition());
                       float z = globalPosition.z();
                       float x = fabs(globalPosition.x() - theBeamSpot->position().x());
                       float y = fabs(globalPosition.y() - theBeamSpot->position().y());
                       float R = TMath::Sqrt(x*x + y*y);
                       float det_eta = globalPosition.eta();
                       float eta_corr = -999.;
                       eta_corr = -log(tan(atan2(R,(z-rver_z))/2.));
                       float ccharge = (*iPRH).cluster()->charge();
                       float adc = ccharge/135.;
                       //Is the recHit at the edge of the detector?
                       bool isAnyPixelAtEdge = isRecHitAtTheEdge(iPRH,pgdu);
//                       cerr<<"XXXX EdgeCheck"<<endl;
                       DesiredEtaDist->Fill(eta_corr); 
                       isPrim = true;
                       if(!isAnyPixelAtEdge) {
                         SimRecAdcvsCorrEta->Fill(eta_corr,adc);
                         SimRecCorrEta->Fill(eta_corr);
                         float adcpercorreta = adc/cosh(eta_corr);
                         hAdcPerCoshCorrEta->Fill(eta_corr,adcpercorreta);
                         // cluster inf.
                         vector<float> clustPrim;
                         clustPrim.push_back(eta_corr);  //eta
                         clustPrim.push_back((iPRH)->cluster()->sizeY());  //sizeY
                         nClusterPrim->Fill(&clustPrim[0]);
                         if(eta_corr<2.1 && eta_corr>1.9) {
                           ResSimRecAdc->Fill(adc);
                           ResSimRecClusterY->Fill((iPRH)->cluster()->sizeY());
                           ResSimRecAdcFine->Fill(adc);
                           ResSimRecAdcLog->Fill(log(adc));
//                           if(adc<400)
//                             cerr<<"XXXX Too low ADC!! problem?"<<endl;
                         }
                         if(det_eta<2.1 && det_eta>1.9)  //Just a test: what happens if we don't correct the eta
                           ResSimRecAdc_det->Fill(adc);
                         if(eta_corr<0.1 && eta_corr>-0.1) {
                           ResCentralAdc->Fill(adc);
                           ResCentralAdcFine->Fill(adc);
                         }
                       }
                       if(eta_corr<2.1 && eta_corr>1.9)
                         FullResSimAdc->Fill(adc);
                       break;
                     }

                 }
              }
              SimEnergyLoss->Fill(energy_loss);
           }
        }

     tpRecHitsVectorVector.push_back(tpRecHitVector);
  }

  // Check all and unused RecHits
  bool isRecHit = false;
  for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH) {
      bool recHitUsed = false;
      const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit(iPRH->geographicalId()));
      PXBDetId pdetId = PXBDetId(iPRH->geographicalId());
      int layer=pdetId.layer();
      GlobalPoint globalPosition = pgdu->toGlobal(iPRH->localPosition());
      float z = globalPosition.z();
      float x = fabs(globalPosition.x() - theBeamSpot->position().x());
      float y = fabs(globalPosition.y() - theBeamSpot->position().y());
      float R = TMath::Sqrt(x*x + y*y);
      float det_eta = globalPosition.eta();
      float eta_corr = -999.;
      eta_corr = -log(tan(atan2(R,(z-rver_z))/2.));
      float ccharge = (iPRH)->cluster()->charge();
      float adc = ccharge/135.;
      //all
      bool isAnyPixelAtEdge = isRecHitAtTheEdge(iPRH,pgdu);
      if(!isAnyPixelAtEdge && layer == 1 && (pgdu->subDetector() == GeomDetEnumerators::PixelBarrel)) {
         PureAdcvsCorrEta->Fill(eta_corr, adc);
         PureCorrEta->Fill(eta_corr);
         if((130.*cosh(eta_corr)-33.)<adc) {  //cut
            isRecHit = true;
            PureCutCorrEta->Fill(eta_corr);
            PureCutAdcvsCorrEta->Fill(eta_corr,adc);
         }
         // cluster , all
         vector<float> clustAll;
         clustAll.push_back(eta_corr);
         clustAll.push_back((iPRH)->cluster()->sizeY());
         nClusterAll->Fill(&clustAll[0]);
         // pixel size in y direction vs eta_corr
         hCorrEtaSizeY->Fill(eta_corr,(iPRH)->cluster()->sizeY());
         hCorrEtaADC->Fill(eta_corr,adc);
         hClusterZSizeY->Fill(z,(iPRH)->cluster()->sizeY());
         // partial distributions
         if(eta_corr<0.1 && eta_corr>-0.1)
            ResPureCentralAdc->Fill(adc);
         if(eta_corr<0.1 && eta_corr>-0.1 && ((130.*cosh(eta_corr)-33.)<adc)) //cut
            ResPureCutCentralAdc->Fill(adc);
         if(eta_corr<2.1 && eta_corr>1.9) {
            ResPureAdc->Fill(adc);
            ResPureClusterY->Fill((iPRH)->cluster()->sizeY());
         }
         if(det_eta<2.1 && det_eta>1.9)  //same as the preceding lines but we use detector eta here
            ResPureAdc_det->Fill(adc);
         if(eta_corr<2.1 && eta_corr>1.9 && ((130.*cosh(eta_corr)-33.)<adc)) //cut
            ResPureCutAdc->Fill(adc);
      }

      for(std::vector<std::vector<const SiPixelRecHit*> >::const_iterator rcV = tpRecHitsVectorVector.begin(); rcV != tpRecHitsVectorVector.end(); ++rcV) {

          for(std::vector<const SiPixelRecHit*>::const_iterator rc = rcV->begin(); rc != rcV->end(); ++rc) {
              if(compareRecHits((*rc), &(*iPRH))) {
                  recHitUsed = true;
              }
          }
      }

      //unused
      if(!recHitUsed ) {
        if(!isAnyPixelAtEdge && layer==1 && (pgdu->subDetector() == GeomDetEnumerators::PixelBarrel))  {  //if first pixel layer 
          ElseSimRecAdcvsCorrEta->Fill(eta_corr,adc);
          // cluster,  unused
          vector<float> clustUnused;
          clustUnused.push_back(eta_corr);
          clustUnused.push_back((iPRH)->cluster()->sizeY());
          nClusterUnused->Fill(&clustUnused[0]);
          if(eta_corr<2.1 && eta_corr>1.9) {
             ResElseSimRecAdc->Fill(adc);
             ResElseSimRecClusterY->Fill((iPRH)->cluster()->sizeY());
          }
          if(det_eta<2.1 && det_eta>1.9)
             ResElseSimRecAdc_det->Fill(adc);  //A test
          if(eta_corr<0.1 && eta_corr>-0.1)
             ResElseCentralAdc->Fill(adc);
        }
      }
  }
  if(isRecHit)
    test++;
  if(isPrim)
    proba++;
}

/*****************************************************************************/
PSimHit* HI_simple_sim::findLatestPSimHit
  (std::vector<PSimHit>& simHits)
{
  PSimHit* latest;
  latest = &(*(simHits.begin()));
  for(std::vector<PSimHit>::iterator simHit = simHits.begin(); simHit != simHits.end(); ++simHit) {
     if(simHit->pabs() < latest->pabs())  {
        latest = &(*simHit);
     }
  }

  return latest;
}

/*****************************************************************************/
PSimHit* HI_simple_sim::findEarliestPSimHit
  (std::vector<PSimHit>& simHits)
{
  if(simHits.size()<1)
    cerr<<"XXXX There're no simhits here"<<endl;
  PSimHit* earliest;
  earliest = &(*(simHits.begin()));
  int kkk = 0;
  int which_kkk = 0;
  for(std::vector<PSimHit>::iterator simHit = simHits.begin(); simHit != simHits.end(); ++simHit, kkk++) {
     if(simHit->timeOfFlight() < earliest->timeOfFlight())  {
        earliest = &(*simHit);
        which_kkk = kkk;
     }
  }

//test
  PSimHit* frenk;
  frenk = &(*(simHits.begin()));
  int kk = 0;
  int which_kk = 0;
  for(std::vector<PSimHit>::iterator simHit = simHits.begin(); simHit != simHits.end(); ++simHit, kk++) {
     if(simHit->pabs() > frenk->pabs())  {
        frenk = &(*simHit);
        which_kk = kk;
     }
  }
  
//  if(!comparePSimHits(&(*earliest), &(*frenk)))
//    cerr<<"XXXX DEAD DEAD DEAD   number of PSimHits: " << simHits.size() << ". Their position: "<<  which_kkk << ", " << which_kk << endl;

  return earliest;
}

/*****************************************************************************/
bool HI_simple_sim::comparePSimHits
  (const PSimHit * hit1, const PSimHit * hit2)
{
  return hit1->detUnitId() == hit2->detUnitId() &&
         hit1->trackId() == hit2->trackId() &&
         hit1->timeOfFlight() == hit2->timeOfFlight() &&
         hit1->pabs() == hit2->pabs() &&
         hit1->processType() == hit2->processType() &&
         hit1->particleType() == hit2->particleType() &&
         hit1->energyLoss() == hit2->energyLoss() &&
         hit1->thetaAtEntry() == hit2->thetaAtEntry() &&
         hit1->phiAtEntry() == hit2->phiAtEntry();
}

/*****************************************************************************/
bool HI_simple_sim::compareRecHits
  (const SiPixelRecHit * hit1, const SiPixelRecHit * hit2)
{
  return hit1->geographicalId() == hit2->geographicalId() &&
        (hit1->cluster())->charge() == (hit2->cluster())->charge() &&
        (hit1->cluster())->size() == (hit2->cluster())->size() &&
        (hit1->cluster())->sizeX() == (hit2->cluster())->sizeX() &&
        (hit1->cluster())->sizeY() == (hit2->cluster())->sizeY();
}

/*****************************************************************************/
float HI_simple_sim::geomAcc(double vert_z, double eta_l, double eta_h, int desLayer)
{
  // eta = -ln(tan(theta/2)); pixel in z dir: 55 cm
  // double eta_corr = -log(tan(atan2(R,(globalPosition.z()-rver_z))/2.));

  float eta_max_lemma = 2.5;
  float eta_min_lemma = -2.5;
  float eta_max = 2.5;
  float eta_min = -2.5;
  double R = 4.4;
  if(desLayer == 2) {eta_max = 2.; eta_min = -2.; R = 7.3;}
  if(desLayer == 3) {eta_max = 1.7; eta_min = -1.7; R = 10.2;}
  float binwidth = 0.5;
  float halflenght = 55./2.;  // 53? 54?

  eta_max_lemma = -log(tan(atan2(R,(halflenght-vert_z))/2.));
  eta_min_lemma = -log(tan(atan2(R,(-halflenght-vert_z))/2.));

  if(eta_max_lemma>eta_min_lemma) {
    eta_max = eta_max_lemma;
    eta_min = eta_min_lemma;
  } else {
    eta_max = eta_min_lemma;
    eta_min = eta_max_lemma;
  }

//  cerr<< " vert_z : " << vert_z << endl;
//  cerr<< " eta_min: " << eta_min << endl;
//  cerr<< " eta_max: " << eta_max << endl;
//  cerr<< " eta_l:   " << eta_l << endl;
//  cerr<< " eta_h:   " << eta_h << endl;

  // correction for small pt-s:
  eta_max = eta_max-0.006;  // TEST, BEWARE
  eta_min = eta_min+0.006;  // TEST, BEWARE

  if(eta_h < eta_min) { if(eta_l==0.0) cerr<< " STRANGE 1 " << endl; return 0.; }
  if(eta_l > eta_max) { if(eta_l==0.0) cerr<< " STRANGE 2 " << endl; return 0.; }
  if(eta_l > eta_min && eta_h < eta_max) { return 1.; }
  if(eta_l < eta_min && eta_h > eta_min) { return ((eta_h-eta_min)/binwidth); }
  if(eta_l < eta_max && eta_h > eta_max) { return ((eta_max-eta_l)/binwidth); }

  return -1.;
}

/*****************************************************************************/
void HI_simple_sim::multiplicityProperties
   (const edm::Event& ev, const edm::EventSetup& es, edm::Handle<CaloTowerCollection> towers,
    edm::Handle<SiPixelRecHitCollection> siPixelRecCollection,
    HepMC::GenEvent * myGenEvent,
    edm::Handle<reco::TrackCollection>& recCollection,
    Handle<HcalTrigPrimDigiCollection>& tpg,
    CentralityProvider * centrality_,
    const HepMC::HeavyIon * hi_mc,
    int desLayer)
{
  vector<float> result;

  //centrality
  int centBin = centrality_->getBin(ev);
  float lowEdge = centrality_->lowEdge(ev);

  double bMean_mc = hi_mc->impact_parameter();

  double npartMean = centrality_->NpartMean(ev);
  double npartSigma = centrality_->NpartSigma(ev);
  double ncollMean = centrality_->NcollMean(ev);
  double ncollSigma = centrality_->NcollSigma(ev);
  double nhardMean = centrality_->NhardMean(ev);
  double nhardSigma = centrality_->NhardSigma(ev);
  double bMean = centrality_->bMean(ev);
  double bSigma = centrality_->bSigma(ev);

  result.push_back(centBin); //centBin
  result.push_back(lowEdge); //lowEdge
  result.push_back(bMean_mc); //B_mc
  result.push_back(npartMean); //NPart
  result.push_back(npartSigma);//NPartSigma
  result.push_back(ncollMean); //NColl
  result.push_back(ncollSigma);//NCollSigma
  result.push_back(nhardMean); //NHard
  result.push_back(nhardSigma);//NHardSigma
  result.push_back(bMean);     //B
  result.push_back(bSigma);    //BSigma

  // Triggers
  edm::Handle<edm::TriggerResults> triggerResults;
  ev.getByLabel(triggerLabel_,triggerResults);

  const edm::TriggerNames & triggerNames = ev.triggerNames(*triggerResults);

  bool is_HLT_HIZeroBias = false;
  bool is_HLT_HIZeroBiasPixel_SingleTrack = false;
  bool is_HLT_HIMinBiasBSC = false;
  bool is_HLT_HIMinBiasBSC_Core = false;
  bool is_HLT_HIMinBiasHF = false;
  bool is_HLT_HIMinBiasPixel_SingleTrack = false;
  bool is_HLT_HIL1Tech_BSC_minBias = false;
  bool is_HLT_HIL1Tech_BSC_minBias_OR = false;
  bool is_HLT_HIL1Tech_BSC_HighMultiplicity = false;
  bool is_HLT_HIL1Tech_HCAL_HF = false;
  bool is_HLT_HIClusterVertexCompatibility = false;
  bool is_HLT_HICentralityVeto = false;
  bool is_HLT_HIL1ETT30 = false;
  bool is_HLT_HIL1ETT30_Core = false;
  bool is_HLT_HIL1ETT60 = false;
  bool is_HLT_HIL1ETT60_Core = false;

  bool is_bit0 = false;
  bool is_bit1 = false;
  bool is_bit2 = false;
  bool is_bit3 = false;
  bool is_bit4 = false;
  bool is_bit5 = false;
  bool is_bit6 = false;
  bool is_bit7 = false;
  bool is_bit8 = false;
  bool is_bit9 = false;
  bool is_bit10 = false;
  bool is_bit11 = false;
  bool is_bit12 = false;
  bool is_bit32 = false;
  bool is_bit33 = false;
  bool is_bit34 = false;
  bool is_bit35 = false;
  bool is_bit36 = false;
  bool is_bit37 = false;
  bool is_bit38 = false;
  bool is_bit39 = false;
  bool is_bit40 = false;
  bool is_bit41 = false;
  bool is_bit42 = false;
  bool is_bit43 = false;
  bool is_bit55 = false;
  bool is_bit60 = false;
  bool is_bit61 = false;
  bool is_bit62 = false;
  bool is_bit63 = false;

  bool is_L1_ZeroBias = false;
  bool is_L1_BscMinBiasOR_BptxAND = false;
  bool is_L1_BscMinBiasInnerThreshold1_BptxAND = false;
  bool is_L1_BscMinBiasInnerThreshold2_BptxAND = false;
  bool is_L1_BscMinBiasThreshold1_BptxAND = false;
  bool is_L1_BscMinBiasThreshold2_BptxAND = false;
  bool is_L1_DoubleHfBitCountsRing1_P1N1 = false;
  bool is_L1_DoubleHfBitCountsRing2_P1N1 = false;
  bool is_L1_DoubleHfRingEtSumsRing1_P4N4 = false;
  bool is_L1_DoubleHfRingEtSumsRing1_P200N200  = false;
  bool is_L1_DoubleHfRingEtSumsRing2_P4N4 = false;
  bool is_L1_DoubleHfRingEtSumsRing2_P200N200 = false;
  bool is_L1_ZdcScintTightVertex_BptxAND = false;
  bool is_L1_ZdcScintLooseVertex_BptxAND = false;
  bool is_L1_BscMinBiasThreshold1 = false;
  bool is_L1_ZdcCaloPlus = false;
  bool is_L1_ZdcCaloMinus = false;
  bool is_L1_ZdcCaloPlus_BptxAND = false;
  bool is_L1_ZdcCaloMinus_BptxAND = false;
  bool is_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND = false;
  bool is_L1_HcalHfMmOrPpOrPm = false;
  bool is_L1_HcalHfCoincidencePm = false;
  bool is_L1_HcalHfMmpOrMpp = false;
  bool is_L1_HcalHoTotalOR = false;
  bool is_L1_ETT60 = false;
  bool is_L1_ETT60_BptxAND = false;
  bool is_L1_ZdcCaloPlus_ZdcCaloMinus = false;
  bool is_L1_BptxMinus = false;
  bool is_L1_BptxPlus = false;
  bool is_L1_BptxPlusORMinus = false;
  bool is_L1_ETT30_BptxAND = false;
  bool is_L1_ETT30  = false;
  bool is_L1_ZdcScintTightVertex = false;
  bool is_L1_ZdcScintPlus = false;
  bool is_L1_ZdcScintMinus = false;
  bool is_L1_BscMinBiasInnerThreshold1 = false;
  bool is_L1_BptxPlusANDMinus = false;
  bool is_L1_BscMinBiasOR_BptxPlusORMinus = false;

  if(triggerResults.product()->wasrun())
  if(triggerResults.product()->accept())
  for(unsigned int itrig = 0; itrig < triggerResults.product()->size(); ++itrig) {
    if(triggerResults.product()->accept(itrig))
    {
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIZeroBias") == 0)
        is_HLT_HIZeroBias = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIZeroBiasPixel_SingleTrack") == 0)
        is_HLT_HIZeroBiasPixel_SingleTrack = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIMinBiasBSC") == 0)
        is_HLT_HIMinBiasBSC = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIMinBiasBSC_Core") == 0)
        is_HLT_HIMinBiasBSC_Core = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIMinBiasHF") == 0)
        is_HLT_HIMinBiasHF = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIMinBiasPixel_SingleTrack") == 0)
        is_HLT_HIMinBiasPixel_SingleTrack = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1Tech_BSC_minBias") == 0)
        is_HLT_HIL1Tech_BSC_minBias = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1Tech_BSC_minBias_OR") == 0)
        is_HLT_HIL1Tech_BSC_minBias_OR = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1Tech_BSC_HighMultiplicity") == 0)
        is_HLT_HIL1Tech_BSC_HighMultiplicity = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1Tech_HCAL_HF") == 0)
        is_HLT_HIL1Tech_HCAL_HF = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIClusterVertexCompatibility") == 0)
        is_HLT_HIClusterVertexCompatibility = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HICentralityVeto") == 0)
        is_HLT_HICentralityVeto = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1ETT30") == 0)
        is_HLT_HIL1ETT30 = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1ETT30_Core") == 0)
        is_HLT_HIL1ETT30_Core = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1ETT60") == 0)
        is_HLT_HIL1ETT60 = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1ETT60_Core") == 0)
        is_HLT_HIL1ETT60_Core = true;
    }
  }

  if(hasL1Triggers_) {
    edm::Handle< L1GlobalTriggerReadoutRecord > gtReadoutRecord;
    ev.getByLabel( edm::InputTag("gtDigis"), gtReadoutRecord);
    const TechnicalTriggerWord&  technicalTriggerWord = gtReadoutRecord->technicalTriggerWord();
    is_bit0 = technicalTriggerWord.at(0);
    is_bit1 = technicalTriggerWord.at(1);
    is_bit2 = technicalTriggerWord.at(2);
    is_bit3 = technicalTriggerWord.at(3);
    is_bit4 = technicalTriggerWord.at(4);
    is_bit5 = technicalTriggerWord.at(5);
    is_bit6 = technicalTriggerWord.at(6);
    is_bit7 = technicalTriggerWord.at(7);
    is_bit8 = technicalTriggerWord.at(8);
    is_bit9 = technicalTriggerWord.at(9);
    is_bit10 = technicalTriggerWord.at(10);
    is_bit11 = technicalTriggerWord.at(11);
    is_bit12 = technicalTriggerWord.at(12);
    is_bit32 = technicalTriggerWord.at(32);
    is_bit33 = technicalTriggerWord.at(33);
    is_bit34 = technicalTriggerWord.at(34);
    is_bit35 = technicalTriggerWord.at(35);
    is_bit36 = technicalTriggerWord.at(36);
    is_bit37 = technicalTriggerWord.at(37);
    is_bit38 = technicalTriggerWord.at(38);
    is_bit39 = technicalTriggerWord.at(39);
    is_bit40 = technicalTriggerWord.at(40);
    is_bit41 = technicalTriggerWord.at(41);
    is_bit42 = technicalTriggerWord.at(42);
    is_bit43 = technicalTriggerWord.at(43);
    is_bit55 = technicalTriggerWord.at(55);
    is_bit60 = technicalTriggerWord.at(60);
    is_bit61 = technicalTriggerWord.at(61);
    is_bit62 = technicalTriggerWord.at(62);
    is_bit63 = technicalTriggerWord.at(63);

    edm::ESHandle<L1GtTriggerMenu> menuRcd;
    es.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
    const L1GtTriggerMenu* menu = menuRcd.product();

    const DecisionWord& gtDecisionWordBeforeMask = gtReadoutRecord->decisionWord();
    is_L1_ZeroBias = menu->gtAlgorithmResult( "L1_ZeroBias", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasOR_BptxAND = menu->gtAlgorithmResult( "L1_BscMinBiasOR_BptxAND", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasInnerThreshold1_BptxAND = menu->gtAlgorithmResult( "L1_BscMinBiasInnerThreshold1_BptxAND", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasInnerThreshold2_BptxAND = menu->gtAlgorithmResult( "L1_BscMinBiasInnerThreshold2_BptxAND", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasThreshold1_BptxAND = menu->gtAlgorithmResult( "L1_BscMinBiasThreshold1_BptxAND", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasThreshold2_BptxAND = menu->gtAlgorithmResult( "L1_BscMinBiasThreshold2_BptxAND", gtDecisionWordBeforeMask);
    is_L1_DoubleHfBitCountsRing1_P1N1 = menu->gtAlgorithmResult( "L1_DoubleHfBitCountsRing1_P1N1", gtDecisionWordBeforeMask);
    is_L1_DoubleHfBitCountsRing2_P1N1 = menu->gtAlgorithmResult( "L1_DoubleHfBitCountsRing2_P1N1", gtDecisionWordBeforeMask);
    is_L1_DoubleHfRingEtSumsRing1_P4N4 = menu->gtAlgorithmResult( "L1_DoubleHfRingEtSumsRing1_P4N4", gtDecisionWordBeforeMask);
    is_L1_DoubleHfRingEtSumsRing1_P200N200 = menu->gtAlgorithmResult( "L1_DoubleHfRingEtSumsRing1_P200N200", gtDecisionWordBeforeMask);
    is_L1_DoubleHfRingEtSumsRing2_P4N4 = menu->gtAlgorithmResult( "L1_DoubleHfRingEtSumsRing2_P4N4", gtDecisionWordBeforeMask);
    is_L1_DoubleHfRingEtSumsRing2_P200N200 = menu->gtAlgorithmResult( "L1_DoubleHfRingEtSumsRing2_P200N200", gtDecisionWordBeforeMask);
    is_L1_ZdcScintTightVertex_BptxAND = menu->gtAlgorithmResult( "L1_ZdcScintTightVertex_BptxAND", gtDecisionWordBeforeMask);
    is_L1_ZdcScintLooseVertex_BptxAND = menu->gtAlgorithmResult( "L1_ZdcScintLooseVertex_BptxAND", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasThreshold1 = menu->gtAlgorithmResult( "L1_BscMinBiasThreshold1", gtDecisionWordBeforeMask);
    is_L1_ZdcCaloPlus = menu->gtAlgorithmResult( "L1_ZdcCaloPlus", gtDecisionWordBeforeMask);
    is_L1_ZdcCaloMinus = menu->gtAlgorithmResult( "L1_ZdcCaloMinus", gtDecisionWordBeforeMask);
    is_L1_ZdcCaloPlus_BptxAND = menu->gtAlgorithmResult( "L1_ZdcCaloPlus_BptxAND", gtDecisionWordBeforeMask);
    is_L1_ZdcCaloMinus_BptxAND = menu->gtAlgorithmResult( "L1_ZdcCaloMinus_BptxAND", gtDecisionWordBeforeMask);
    is_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND = menu->gtAlgorithmResult( "L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND", gtDecisionWordBeforeMask);
    is_L1_HcalHfMmOrPpOrPm = menu->gtAlgorithmResult( "L1_HcalHfMmOrPpOrPm", gtDecisionWordBeforeMask);
    is_L1_HcalHfCoincidencePm = menu->gtAlgorithmResult( "L1_HcalHfCoincidencePm", gtDecisionWordBeforeMask);
    is_L1_HcalHfMmpOrMpp = menu->gtAlgorithmResult( "L1_HcalHfMmpOrMpp", gtDecisionWordBeforeMask);
    is_L1_HcalHoTotalOR = menu->gtAlgorithmResult( "L1_HcalHoTotalOR", gtDecisionWordBeforeMask);
    is_L1_ETT60 = menu->gtAlgorithmResult( "L1_ETT60", gtDecisionWordBeforeMask);
    is_L1_ETT60_BptxAND = menu->gtAlgorithmResult( "L1_ETT60_BptxAND", gtDecisionWordBeforeMask);
    is_L1_ZdcCaloPlus_ZdcCaloMinus = menu->gtAlgorithmResult( "L1_ZdcCaloPlus_ZdcCaloMinus", gtDecisionWordBeforeMask);
    is_L1_BptxMinus = menu->gtAlgorithmResult( "L1_BptxMinus", gtDecisionWordBeforeMask);
    is_L1_BptxPlus = menu->gtAlgorithmResult( "L1_BptxPlus", gtDecisionWordBeforeMask);
    is_L1_BptxPlusORMinus = menu->gtAlgorithmResult( "L1_BptxPlusORMinus", gtDecisionWordBeforeMask);
    is_L1_ETT30_BptxAND = menu->gtAlgorithmResult( "L1_ETT30_BptxAND", gtDecisionWordBeforeMask);
    is_L1_ETT30 = menu->gtAlgorithmResult( "L1_ETT30", gtDecisionWordBeforeMask);
    is_L1_ZdcScintTightVertex = menu->gtAlgorithmResult( "L1_ZdcScintTightVertex", gtDecisionWordBeforeMask);
    is_L1_ZdcScintPlus = menu->gtAlgorithmResult( "L1_ZdcScintPlus", gtDecisionWordBeforeMask);
    is_L1_ZdcScintMinus = menu->gtAlgorithmResult( "L1_ZdcScintMinus", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasInnerThreshold1 = menu->gtAlgorithmResult( "L1_BscMinBiasInnerThreshold1", gtDecisionWordBeforeMask);
    is_L1_BptxPlusANDMinus = menu->gtAlgorithmResult( "L1_BptxPlusANDMinus", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasOR_BptxPlusORMinus = menu->gtAlgorithmResult( "L1_BscMinBiasOR_BptxPlusORMinus", gtDecisionWordBeforeMask);
  }

  // Get simulated
  edm::Handle<TrackingParticleCollection> simCollection;
//  ev.getByType(simCollection);
  ev.getByLabel("mergedtruth","MergedTrackTruth",simCollection);

  const TrackingParticleCollection *tPC = simCollection.product();

  edm::Handle<vector<PSimHit> > simHits;
  ev.getByLabel("g4SimHits","TrackerHitsPixelBarrelLowTof", simHits);

  edm::ESHandle<TrackerGeometry> geom;
  es.get<TrackerDigiGeometryRecord>().get(geom);

  const SiPixelRecHitCollection pixelRecHits = *(siPixelRecCollection.product());

  result.push_back(pixelRecHits.size());

  // get vertex_z
  double rver_z = (double)getVertexZ(siPixelRecCollection, ev);

  result.push_back(rver_z); //rver_z

  //simulate triggers
  result.push_back(aboveTriggerThreshold_1(towers));  //isTrigger_1
  result.push_back(aboveTriggerThreshold_2(towers));  //isTrigger_2
  result.push_back(aboveTriggerThreshold_3(towers));  //isTrigger_3

  result.push_back(is_HLT_HIZeroBias);
  result.push_back(is_HLT_HIZeroBiasPixel_SingleTrack);
  result.push_back(is_HLT_HIMinBiasBSC);
  result.push_back(is_HLT_HIMinBiasBSC_Core);
  result.push_back(is_HLT_HIMinBiasHF);
  result.push_back(is_HLT_HIMinBiasPixel_SingleTrack);
  result.push_back(is_HLT_HIL1Tech_BSC_minBias);
  result.push_back(is_HLT_HIL1Tech_BSC_minBias_OR);
  result.push_back(is_HLT_HIL1Tech_BSC_HighMultiplicity);
  result.push_back(is_HLT_HIL1Tech_HCAL_HF);
  result.push_back(is_HLT_HIClusterVertexCompatibility);
  result.push_back(is_HLT_HICentralityVeto);
  result.push_back(is_HLT_HIL1ETT30);
  result.push_back(is_HLT_HIL1ETT30_Core);
  result.push_back(is_HLT_HIL1ETT60);
  result.push_back(is_HLT_HIL1ETT60_Core);

  result.push_back(is_bit0);
  result.push_back(is_bit1);
  result.push_back(is_bit2);
  result.push_back(is_bit3);
  result.push_back(is_bit4);
  result.push_back(is_bit5);
  result.push_back(is_bit6);
  result.push_back(is_bit7);
  result.push_back(is_bit8);
  result.push_back(is_bit9);
  result.push_back(is_bit10);
  result.push_back(is_bit11);
  result.push_back(is_bit12);
  result.push_back(is_bit32);
  result.push_back(is_bit33);
  result.push_back(is_bit34);
  result.push_back(is_bit35);
  result.push_back(is_bit36);
  result.push_back(is_bit37);
  result.push_back(is_bit38);
  result.push_back(is_bit39);
  result.push_back(is_bit40);
  result.push_back(is_bit41);
  result.push_back(is_bit42);
  result.push_back(is_bit43);
  result.push_back(is_bit55);
  result.push_back(is_bit60);
  result.push_back(is_bit61);
  result.push_back(is_bit62);
  result.push_back(is_bit63);

  result.push_back(is_L1_ZeroBias);
  result.push_back(is_L1_BscMinBiasOR_BptxAND);
  result.push_back(is_L1_BscMinBiasInnerThreshold1_BptxAND);
  result.push_back(is_L1_BscMinBiasInnerThreshold2_BptxAND);
  result.push_back(is_L1_BscMinBiasThreshold1_BptxAND);
  result.push_back(is_L1_BscMinBiasThreshold2_BptxAND);
  result.push_back(is_L1_DoubleHfBitCountsRing1_P1N1);
  result.push_back(is_L1_DoubleHfBitCountsRing2_P1N1);
  result.push_back(is_L1_DoubleHfRingEtSumsRing1_P4N4);
  result.push_back(is_L1_DoubleHfRingEtSumsRing1_P200N200);
  result.push_back(is_L1_DoubleHfRingEtSumsRing2_P4N4);
  result.push_back(is_L1_DoubleHfRingEtSumsRing2_P200N200);
  result.push_back(is_L1_ZdcScintTightVertex_BptxAND);
  result.push_back(is_L1_ZdcScintLooseVertex_BptxAND);
  result.push_back(is_L1_BscMinBiasThreshold1);
  result.push_back(is_L1_ZdcCaloPlus);
  result.push_back(is_L1_ZdcCaloMinus);
  result.push_back(is_L1_ZdcCaloPlus_BptxAND);
  result.push_back(is_L1_ZdcCaloMinus_BptxAND);
  result.push_back(is_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND);
  result.push_back(is_L1_HcalHfMmOrPpOrPm);
  result.push_back(is_L1_HcalHfCoincidencePm);
  result.push_back(is_L1_HcalHfMmpOrMpp);
  result.push_back(is_L1_HcalHoTotalOR);
  result.push_back(is_L1_ETT60);
  result.push_back(is_L1_ETT60_BptxAND);
  result.push_back(is_L1_ZdcCaloPlus_ZdcCaloMinus);
  result.push_back(is_L1_BptxMinus);
  result.push_back(is_L1_BptxPlus);
  result.push_back(is_L1_BptxPlusORMinus);
  result.push_back(is_L1_ETT30_BptxAND);
  result.push_back(is_L1_ETT30);
  result.push_back(is_L1_ZdcScintTightVertex);
  result.push_back(is_L1_ZdcScintPlus);
  result.push_back(is_L1_ZdcScintMinus);
  result.push_back(is_L1_BscMinBiasInnerThreshold1);
  result.push_back(is_L1_BptxPlusANDMinus);
  result.push_back(is_L1_BscMinBiasOR_BptxPlusORMinus);

  result.push_back(1);  //numVtx
  result.push_back(1);    //numEv
  int procID = myGenEvent->signal_process_id();
  result.push_back(procID);  //process ID

  // T_truth
  int T_truth_etaP6 = 0; float T_truth_etaP6_eff = 0;
  int T_truth_etaP5 = 0; float T_truth_etaP5_eff = 0;
  int T_truth_etaP4 = 0; float T_truth_etaP4_eff = 0;
  int T_truth_etaP3 = 0; float T_truth_etaP3_eff = 0;
  int T_truth_etaP2 = 0; float T_truth_etaP2_eff = 0;
  int T_truth_etaP1 = 0; float T_truth_etaP1_eff = 0;
  int T_truth_etaN1 = 0; float T_truth_etaN1_eff = 0;
  int T_truth_etaN2 = 0; float T_truth_etaN2_eff = 0;
  int T_truth_etaN3 = 0; float T_truth_etaN3_eff = 0;
  int T_truth_etaN4 = 0; float T_truth_etaN4_eff = 0;
  int T_truth_etaN5 = 0; float T_truth_etaN5_eff = 0;
  int T_truth_etaN6 = 0; float T_truth_etaN6_eff = 0;

  bool isFull = false;
  bool isFull_0 = false;
  bool isFull_1 = false;
  bool isFull_2 = false;
  bool isFull_3 = false;
  bool isRestricted = false;

  for(TrackingParticleCollection::const_iterator t = tPC->begin(); t != tPC->end(); ++t) {

     if((t->charge()!=1 && t->charge()!=-1) || t->parentVertex()->nSourceTracks()!=0 || fabs(t->pdgId())==11 || fabs(t->pdgId())==13)
        continue;

     double tp_eta = t->eta();

     if(desLayer == 1) { //sim dNdeta is layer independent
        hTestEtaFull->Fill(tp_eta);
        isFull = true;
        if(centBin==0) {
           hTestEtaFull_0->Fill(tp_eta);
           isFull_0 = true;
        }
        if(centBin==1) {
           hTestEtaFull_1->Fill(tp_eta);
           isFull_1 = true;
        }
        if(centBin==2) {
           hTestEtaFull_2->Fill(tp_eta);
           isFull_2 = true;
        }
        if(centBin==3) {
           hTestEtaFull_3->Fill(tp_eta);
           isFull_3 = true;
        }
        if(rver_z!=0) {
          hTestEtaRestricted->Fill(tp_eta);
          isRestricted = true;
        }
     }

     //eta cut at 3.0!!! -to speed up the computations-
     if(fabs(tp_eta)>3.0)
        continue;
 
     if(tp_eta<3.0 && tp_eta>2.5) { //Positive
       T_truth_etaP6++;
       T_truth_etaP6_eff += 1.*geomAcc(rver_z,2.5,3.0,desLayer);
     }       
     if(tp_eta<2.5 && tp_eta>2.0) { //Positive
       T_truth_etaP5++;
       T_truth_etaP5_eff += 1.*geomAcc(rver_z,2.0,2.5,desLayer);
     }
     if(tp_eta<=2.0 && tp_eta>1.5) { //Positive
       T_truth_etaP4++;
       T_truth_etaP4_eff += 1.*geomAcc(rver_z,1.5,2.0,desLayer);
     }
     if(tp_eta<=1.5 && tp_eta>1.0) { //Positive
       T_truth_etaP3++;
       T_truth_etaP3_eff += 1.*geomAcc(rver_z,1.0,1.5,desLayer);
     }
     if(tp_eta<=1.0 && tp_eta>0.5) { //Positive
       T_truth_etaP2++;
       T_truth_etaP2_eff += 1.*geomAcc(rver_z,0.5,1.0,desLayer);
     }
     if(tp_eta<=0.5 && tp_eta>0.0) { //Positive
       T_truth_etaP1++;
       T_truth_etaP1_eff += 1.*geomAcc(rver_z,0.0,0.5,desLayer);
     }
     if(tp_eta<=0.0 && tp_eta>-0.5) { //Negative
       T_truth_etaN1++;
       T_truth_etaN1_eff += 1.*geomAcc(rver_z,-0.5,0.0,desLayer);
     }
     if(tp_eta<=-0.5 && tp_eta>-1.0) { //Negative
       T_truth_etaN2++;
       T_truth_etaN2_eff += 1.*geomAcc(rver_z,-1.0,-0.5,desLayer);
     }
     if(tp_eta<=-1.0 && tp_eta>-1.5) { //Negative
       T_truth_etaN3++;
       T_truth_etaN3_eff += 1.*geomAcc(rver_z,-1.5,-1.0,desLayer);
     }
     if(tp_eta<=-1.5 && tp_eta>-2.0) { //Negative
       T_truth_etaN4++;
       T_truth_etaN4_eff += 1.*geomAcc(rver_z,-2.0,-1.5,desLayer);
     }
     if(tp_eta<=-2.0 && tp_eta>-2.5) { //Negative
       T_truth_etaN5++;
       T_truth_etaN5_eff += 1.*geomAcc(rver_z,-2.5,-2.0,desLayer);
     }
     if(tp_eta<=-2.5 && tp_eta>-3.0) { //Negative
       T_truth_etaN6++;
       T_truth_etaN6_eff += 1.*geomAcc(rver_z,-3.0,-2.5,desLayer);
     }
  }

  if(isFull)
    full++;
  if(isFull_0)
    hNum_0->Fill(0);
  if(isFull_1)
    hNum_1->Fill(0);
  if(isFull_2)
    hNum_2->Fill(0);
  if(isFull_3)
    hNum_3->Fill(0);
  if(isRestricted)
    restricted++;

  result.push_back(T_truth_etaP6);  //T_truth_etaP6
  result.push_back(T_truth_etaP5);  //T_truth_etaP5
  result.push_back(T_truth_etaP4);  //T_truth_etaP4
  result.push_back(T_truth_etaP3);  //T_truth_etaP3
  result.push_back(T_truth_etaP2);  //T_truth_etaP2
  result.push_back(T_truth_etaP1);  //T_truth_etaP1
  result.push_back(T_truth_etaN1);  //T_truth_etaN1
  result.push_back(T_truth_etaN2);  //T_truth_etaN2
  result.push_back(T_truth_etaN3);  //T_truth_etaN3
  result.push_back(T_truth_etaN4);  //T_truth_etaN4
  result.push_back(T_truth_etaN5);  //T_truth_etaN5
  result.push_back(T_truth_etaN6);  //T_truth_etaN6
  // effective tracks (they hit the pixel detector)
  result.push_back(T_truth_etaP6_eff);  //T_truth_etaP6_eff
  result.push_back(T_truth_etaP5_eff);  //T_truth_etaP5_eff
  result.push_back(T_truth_etaP4_eff);  //T_truth_etaP4_eff
  result.push_back(T_truth_etaP3_eff);  //T_truth_etaP3_eff
  result.push_back(T_truth_etaP2_eff);  //T_truth_etaP2_eff
  result.push_back(T_truth_etaP1_eff);  //T_truth_etaP1_eff
  result.push_back(T_truth_etaN1_eff);  //T_truth_etaN1_eff
  result.push_back(T_truth_etaN2_eff);  //T_truth_etaN2_eff
  result.push_back(T_truth_etaN3_eff);  //T_truth_etaN3_eff
  result.push_back(T_truth_etaN4_eff);  //T_truth_etaN4_eff
  result.push_back(T_truth_etaN5_eff);  //T_truth_etaN5_eff
  result.push_back(T_truth_etaN6_eff);  //T_truth_etaN6_eff

  // cluster size -STARTS-
  int clustSizeY_etaP6 = 0;
  int clustSizeY_etaP5 = 0;
  int clustSizeY_etaP4 = 0;
  int clustSizeY_etaP3 = 0;
  int clustSizeY_etaP2 = 0;
  int clustSizeY_etaP1 = 0;
  int clustSizeY_etaN1 = 0;
  int clustSizeY_etaN2 = 0;
  int clustSizeY_etaN3 = 0;
  int clustSizeY_etaN4 = 0;
  int clustSizeY_etaN5 = 0;
  int clustSizeY_etaN6 = 0;
  std::vector<const SiPixelRecHit*> passedClusters;
  float clusters_on_layers = 0.;
  for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH ) {
     const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((*iPRH).geographicalId()));

     if(pgdu->subDetector() != GeomDetEnumerators::PixelBarrel)
        continue;

     PXBDetId pdetId = PXBDetId((*iPRH).geographicalId());
     int layer=pdetId.layer();

     if(layer != desLayer)
        continue;

     clusters_on_layers++;

     GlobalPoint globalPosition = pgdu->toGlobal((*iPRH).localPosition());
     float x = fabs(globalPosition.x() - theBeamSpot->position().x());
     float y = fabs(globalPosition.y() - theBeamSpot->position().y());
     double R = TMath::Sqrt(x*x + y*y);
     double eta_corr = -log(tan(atan2(R,(globalPosition.z()-rver_z))/2.));
     int clustSizeY = (iPRH)->cluster()->sizeY();

     if(eta_corr<3.0 && eta_corr>=2.5 && clustSizeY>8.5)   
       { clustSizeY_etaP6++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<2.5 && eta_corr>2.0 && clustSizeY>5.5)   //Positive etas
       { clustSizeY_etaP5++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=2.0 && eta_corr>1.5 && clustSizeY>3.5)   //Positive etas
       { clustSizeY_etaP4++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=1.5 && eta_corr>1.0 && clustSizeY>2.5)   //Positive etas
       { clustSizeY_etaP3++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=1.0 && eta_corr>0.5 && clustSizeY>1.5)   //Positive etas
       { clustSizeY_etaP2++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=0.5 && eta_corr>0.0)   //Positive etas + no cut
       { clustSizeY_etaP1++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=0.0 && eta_corr>-0.5)   //Negative etas + no cut
       { clustSizeY_etaN1++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=-0.5 && eta_corr>-1.0 && clustSizeY>1.5)   //Negative etas
       { clustSizeY_etaN2++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=-1.0 && eta_corr>-1.5 && clustSizeY>2.5)   //Negative etas
       { clustSizeY_etaN3++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=-1.5 && eta_corr>-2.0 && clustSizeY>3.5)   //Negative etas
       { clustSizeY_etaN4++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=-2.0 && eta_corr>-2.5 && clustSizeY>5.5)   //Negative etas
       { clustSizeY_etaN5++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=-2.5 && eta_corr>-3.0 && clustSizeY>8.5)   
       { clustSizeY_etaN6++; passedClusters.push_back(&(*iPRH)); }

  }
  result.push_back(clusters_on_layers); //clusters_on_layers

  result.push_back(clustSizeY_etaP6);  //clustSizeY_etaP6
  result.push_back(clustSizeY_etaP5);  //clustSizeY_etaP5
  result.push_back(clustSizeY_etaP4);  //clustSizeY_etaP4
  result.push_back(clustSizeY_etaP3);  //clustSizeY_etaP3
  result.push_back(clustSizeY_etaP2);  //clustSizeY_etaP2
  result.push_back(clustSizeY_etaP1);  //clustSizeY_etaP1
  result.push_back(clustSizeY_etaN1);  //clustSizeY_etaN1
  result.push_back(clustSizeY_etaN2);  //clustSizeY_etaN2
  result.push_back(clustSizeY_etaN3);  //clustSizeY_etaN3
  result.push_back(clustSizeY_etaN4);  //clustSizeY_etaN4
  result.push_back(clustSizeY_etaN5);  //clustSizeY_etaN5
  result.push_back(clustSizeY_etaN6);  //clustSizeY_etaN6

  int cluster_counter = clustSizeY_etaP5+clustSizeY_etaP4+clustSizeY_etaP3+clustSizeY_etaP2+clustSizeY_etaP1+clustSizeY_etaN1+clustSizeY_etaN2+clustSizeY_etaN3+clustSizeY_etaN4+clustSizeY_etaN5;
  result.push_back(cluster_counter);
  // cluster size -FINISHED-

  // fill the ntuple
  if(desLayer==1)
    multProp->Fill(&result[0]);
  if(desLayer==2)
    nd_multProp->Fill(&result[0]);
  if(desLayer==3)
    rd_multProp->Fill(&result[0]);

// LOOPER part starts here
// which are the looper hits?
  int looperHits_etaP6 = 0;
  int looperHits_etaP5 = 0;
  int looperHits_etaP4 = 0;
  int looperHits_etaP3 = 0;
  int looperHits_etaP2 = 0;
  int looperHits_etaP1 = 0;
  int looperHits_etaN1 = 0;
  int looperHits_etaN2 = 0;
  int looperHits_etaN3 = 0;
  int looperHits_etaN4 = 0;
  int looperHits_etaN5 = 0;
  int looperHits_etaN6 = 0;
  vector<float> looper_result;
  vector<TrackingParticle> loopers;  // it was inside the if below
  vector<TrackingParticle> geoPrims; 

//  if(vertices->size()==1) {
  if(1) {
    TrackerHitAssociator theHitAssociator(ev);
    // Get simulated
    edm::Handle<TrackingParticleCollection> simCollection;
//    ev.getByType(simCollection);
    ev.getByLabel("mergedtruth","MergedTrackTruth",simCollection);
    // Get pixel hits
    theHits = siPixelRecCollection.product();
    // result vector

    for(SiPixelRecHitCollection::const_iterator detunit_iter = theHits->begin();
                                             detunit_iter!= theHits->end(); detunit_iter++)
    {
      SiPixelRecHitCollection::DetSet range = *detunit_iter;
      unsigned int id = range.detId();
      const PixelGeomDetUnit* pixelDet =
        dynamic_cast<const PixelGeomDetUnit*> (theTracker->idToDet((id)));

      const RectangularPixelTopology* topology =
        dynamic_cast<const RectangularPixelTopology*>
          (&(pixelDet->specificTopology()));

      PXBDetId pid(id);

      // Take all hits
      if(pid.subdetId() == PixelSubdetector::PixelBarrel)
      { 
        // Look at a certain barrel only
        if(pid.layer() == (unsigned)desLayer)
        for(SiPixelRecHitCollection::DetSet::const_iterator recHit = range.begin();
                             recHit!= range.end(); recHit++)
        {
          GlobalPoint gpos = pixelDet->toGlobal(recHit->localPosition());
          // eta and eloss
          float x = fabs(gpos.x() - theBeamSpot->position().x());
          float y = fabs(gpos.y() - theBeamSpot->position().y());
          double R = TMath::Sqrt(x*x + y*y);
          float eta = -log(tan(atan2(R,(gpos.z()-rver_z))/2.));
          float eta_det = -log(tan(atan2(R,(gpos.z()-0.))/2.));

          float eloss = recHit->cluster()->charge();
          int clustSizeY = recHit->cluster()->sizeY();
          int clustSizeX = recHit->cluster()->sizeX();
          float phi = gpos.phi();
          int pixels = recHit->cluster()->size();
          double length = (recHit->localPosition()).mag()/fabsf((recHit->localPosition()).z())*pixelDet->surface().bounds().thickness();

          // associate 
          vector<PSimHit> simHits_ass = theHitAssociator.associateHit(*recHit);
          vector<PSimHit> ordered_ass = orderPSimHits(simHits_ass);
          const PSimHit * bestSimHit = 0;

          // background = 1, primary = 2, primary looper = 3
          int type = 1;
          for(vector<PSimHit>::const_iterator simHit = ordered_ass.begin();  //originally  simHits_ass.begin() and ...end()
                      simHit!= ordered_ass.end(); simHit++)                  // WARNING!!!
            if(simHit->processType() == 2)  //we expect one bestSimHit
            {
              bestSimHit = &(*simHit);
              type = 2;  
            }

          // Is it a looping hit?
          if(type == 2)
          for(TrackingParticleCollection::size_type i=0;
               i < simCollection.product()->size(); ++i)
          {
            const TrackingParticleRef simTrack(simCollection, i);

//            hPt->Fill(simTrack->pt());

            const PSimHit * firstSimHit = 0;
            float pmin = 100.;
            for(std::vector<PSimHit>::const_iterator
                          simHit = simTrack->pSimHit_begin();
                          simHit!= simTrack->pSimHit_end(); simHit++) {
              //WARNING: DIFFERENT FIRST DEFINITION!! (> pmax) -> (< pmin) !!

              const DetId simHitDetId = DetId(simHit->detUnitId());
              if(simHitDetId.subdetId() != int(PixelSubdetector::PixelBarrel))
                 continue;

              //for detector invalid units the layer is "5"
              PXBDetId BpdetId = PXBDetId(simHitDetId);
              int Blayer=BpdetId.layer();
              if(simHit->pabs() < pmin && Blayer==desLayer && simHit->processType() == 2)  //BEWARE
              { pmin = simHit->pabs(); firstSimHit = &(*simHit); }
            }

            if(firstSimHit != 0)
              if(bestSimHit->trackId() == firstSimHit->trackId())
              {
                if(!(bestSimHit->pabs() == firstSimHit->pabs())) {
                  if(abs(bestSimHit->timeOfFlight()-firstSimHit->timeOfFlight())<0.14) {  //hardcut on geos
                    // geo effect part
                    bool alreadY = false;
                    for(vector<TrackingParticle>::const_iterator tLemma = geoPrims.begin(); tLemma != geoPrims.end(); tLemma++) {
                      if(tLemma->pt() == simTrack->pt())
                        alreadY = true;
                    }
                    if(!alreadY)
                      geoPrims.push_back(*simTrack);
                    continue;
                  }
                  type = 3;
                  // remove multiple entries BEWARE
                  bool alreadY = false;
                  for(vector<TrackingParticle>::const_iterator tLemma = loopers.begin(); tLemma != loopers.end(); tLemma++) {
                    if(tLemma->pt() == simTrack->pt())
                      alreadY = true;
                  }
                  if(!alreadY)
                    loopers.push_back(*simTrack);
//                    hLooperPt->Fill(simTrack->pt());
                }
                if(type==2) {
//                  hNonLooperPt->Fill(simTrack->pt());
                }
  
                break;
              }
          }
          vector<float> result_looper;

          result_looper.push_back(centBin); //centBin
          result_looper.push_back(lowEdge); //lowEdge
          result_looper.push_back(bMean_mc); //B_mc
          result_looper.push_back(npartMean); //NPart
          result_looper.push_back(npartSigma);//NPartSigma
          result_looper.push_back(ncollMean); //NColl
          result_looper.push_back(ncollSigma);//NCollSigma
          result_looper.push_back(nhardMean); //NHard
          result_looper.push_back(nhardSigma);//NHardSigma
          result_looper.push_back(bMean);     //B
          result_looper.push_back(bSigma);    //BSigma

          result_looper.push_back(aboveTriggerThreshold_1(towers));
          result_looper.push_back(aboveTriggerThreshold_2(towers));
          result_looper.push_back(aboveTriggerThreshold_3(towers));

          result_looper.push_back(rver_z);
          result_looper.push_back(eta);
          result_looper.push_back(eta_det);
          result_looper.push_back(phi);
          result_looper.push_back(eloss);
          result_looper.push_back(type*(isAtEdge(topology,*recHit) ? -1 : 1));
//          result_looper.push_back(vertices->size());
          result_looper.push_back(1);
          result_looper.push_back(clustSizeY);
          result_looper.push_back(clustSizeX);
          result_looper.push_back(length);
          result_looper.push_back(pixels);
          result_looper.push_back(cluster_counter);

          result_looper.push_back(is_HLT_HIZeroBias);
          result_looper.push_back(is_HLT_HIZeroBiasPixel_SingleTrack);
          result_looper.push_back(is_HLT_HIMinBiasBSC);
          result_looper.push_back(is_HLT_HIMinBiasBSC_Core);
          result_looper.push_back(is_HLT_HIMinBiasHF);
          result_looper.push_back(is_HLT_HIMinBiasPixel_SingleTrack);
          result_looper.push_back(is_HLT_HIL1Tech_BSC_minBias);
          result_looper.push_back(is_HLT_HIL1Tech_BSC_minBias_OR);
          result_looper.push_back(is_HLT_HIL1Tech_BSC_HighMultiplicity);
          result_looper.push_back(is_HLT_HIL1Tech_HCAL_HF);
          result_looper.push_back(is_HLT_HIClusterVertexCompatibility);
          result_looper.push_back(is_HLT_HICentralityVeto);
          result_looper.push_back(is_HLT_HIL1ETT30);
          result_looper.push_back(is_HLT_HIL1ETT30_Core);
          result_looper.push_back(is_HLT_HIL1ETT60);
          result_looper.push_back(is_HLT_HIL1ETT60_Core);

          result_looper.push_back(is_bit0);
          result_looper.push_back(is_bit1);
          result_looper.push_back(is_bit2);
          result_looper.push_back(is_bit3);
          result_looper.push_back(is_bit4);
          result_looper.push_back(is_bit5);
          result_looper.push_back(is_bit6);
          result_looper.push_back(is_bit7);
          result_looper.push_back(is_bit8);
          result_looper.push_back(is_bit9);
          result_looper.push_back(is_bit10);
          result_looper.push_back(is_bit11);
          result_looper.push_back(is_bit12);
          result_looper.push_back(is_bit32);
          result_looper.push_back(is_bit33);
          result_looper.push_back(is_bit34);
          result_looper.push_back(is_bit35);
          result_looper.push_back(is_bit36);
          result_looper.push_back(is_bit37);
          result_looper.push_back(is_bit38);
          result_looper.push_back(is_bit39);
          result_looper.push_back(is_bit40);
          result_looper.push_back(is_bit41);
          result_looper.push_back(is_bit42);
          result_looper.push_back(is_bit43);
          result_looper.push_back(is_bit55);
          result_looper.push_back(is_bit60);
          result_looper.push_back(is_bit61);
          result_looper.push_back(is_bit62);
          result_looper.push_back(is_bit63);

          result_looper.push_back(is_L1_ZeroBias);
          result_looper.push_back(is_L1_BscMinBiasOR_BptxAND);
          result_looper.push_back(is_L1_BscMinBiasInnerThreshold1_BptxAND);
          result_looper.push_back(is_L1_BscMinBiasInnerThreshold2_BptxAND);
          result_looper.push_back(is_L1_BscMinBiasThreshold1_BptxAND);
          result_looper.push_back(is_L1_BscMinBiasThreshold2_BptxAND);
          result_looper.push_back(is_L1_DoubleHfBitCountsRing1_P1N1);
          result_looper.push_back(is_L1_DoubleHfBitCountsRing2_P1N1);
          result_looper.push_back(is_L1_DoubleHfRingEtSumsRing1_P4N4);
          result_looper.push_back(is_L1_DoubleHfRingEtSumsRing1_P200N200);
          result_looper.push_back(is_L1_DoubleHfRingEtSumsRing2_P4N4);
          result_looper.push_back(is_L1_DoubleHfRingEtSumsRing2_P200N200);
          result_looper.push_back(is_L1_ZdcScintTightVertex_BptxAND);
          result_looper.push_back(is_L1_ZdcScintLooseVertex_BptxAND);
          result_looper.push_back(is_L1_BscMinBiasThreshold1);
          result_looper.push_back(is_L1_ZdcCaloPlus);
          result_looper.push_back(is_L1_ZdcCaloMinus);
          result_looper.push_back(is_L1_ZdcCaloPlus_BptxAND);
          result_looper.push_back(is_L1_ZdcCaloMinus_BptxAND);
          result_looper.push_back(is_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND);
          result_looper.push_back(is_L1_HcalHfMmOrPpOrPm);
          result_looper.push_back(is_L1_HcalHfCoincidencePm);
          result_looper.push_back(is_L1_HcalHfMmpOrMpp);
          result_looper.push_back(is_L1_HcalHoTotalOR);
          result_looper.push_back(is_L1_ETT60);
          result_looper.push_back(is_L1_ETT60_BptxAND);
          result_looper.push_back(is_L1_ZdcCaloPlus_ZdcCaloMinus);
          result_looper.push_back(is_L1_BptxMinus);
          result_looper.push_back(is_L1_BptxPlus);
          result_looper.push_back(is_L1_BptxPlusORMinus);
          result_looper.push_back(is_L1_ETT30_BptxAND);
          result_looper.push_back(is_L1_ETT30);
          result_looper.push_back(is_L1_ZdcScintTightVertex);
          result_looper.push_back(is_L1_ZdcScintPlus);
          result_looper.push_back(is_L1_ZdcScintMinus);
          result_looper.push_back(is_L1_BscMinBiasInnerThreshold1);
          result_looper.push_back(is_L1_BptxPlusANDMinus);
          result_looper.push_back(is_L1_BscMinBiasOR_BptxPlusORMinus);

//          if(eloss/(135.*cosh(eta))<713. && eloss/(135.*cosh(eta))>712. && type==3)
//             std::cerr<<"Suspicious energy loss of a looper particle(2): "<< eloss/(135.*cosh(eta)) << std::endl;
//          if(type==3)
//             hProba->Fill(eloss/(135.*cosh(eta)));

          // Filling
          if(desLayer==1)
            multProp_looper->Fill(&result_looper[0]);
          if(desLayer==2)
            nd_multProp_looper->Fill(&result_looper[0]);
          if(desLayer==3)
            rd_multProp_looper->Fill(&result_looper[0]);

        }
      }
    }

//one would analyze the vector "loopers" here
    //loop over the looper particles
    for(vector<TrackingParticle>::const_iterator tPR = loopers.begin(); tPR != loopers.end(); tPR++) {
       //find their hits which are in the first pixel barrel layer
       vector<PSimHit> looper_hits;
       vector<PSimHit> final_looper_hits;
       vector<PSimHit> simHits_ass;
       for(std::vector<PSimHit>::const_iterator
           simHit = tPR->pSimHit_begin();
           simHit!= tPR->pSimHit_end(); simHit++)  {

          if(simHit->processType() != 2) //we looking for primary hits
             continue;

          const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit(simHit->detUnitId()));
          if((pgdu==0) || (pgdu->subDetector() != GeomDetEnumerators::PixelBarrel))
            continue;

          PXBDetId pdetId = PXBDetId(simHit->detUnitId());  //geographicalId());
          int layer=pdetId.layer();
          if(layer != desLayer)
             continue;

          looper_hits.push_back(*simHit);
          //get tof and pabs for every hit
          vector<float> pabstof;
          pabstof.push_back(simHit->pabs());
          pabstof.push_back(simHit->tof());
          if(desLayer == 1)
            hPabsTof->Fill(&pabstof[0]);
          if(desLayer == 2)
            nd_hPabsTof->Fill(&pabstof[0]);
          if(desLayer == 3)
            rd_hPabsTof->Fill(&pabstof[0]);
       }

       float pmax = 0.;
       float pmin = 9999.;
       const PSimHit * firstSimHit = 0;
       const PSimHit * lastSimHit = 0;
       // loop through the selected looper hits
       for(std::vector<PSimHit>::const_iterator
           simHit = looper_hits.begin();
           simHit!= looper_hits.end(); simHit++)  {
          // select the first hit
          if(simHit->pabs() > pmax)
            { pmax = simHit->pabs(); firstSimHit = &(*simHit); }
          // select the last hit
          if((simHit->pabs() < pmin) && !(firstSimHit->pabs()==simHit->pabs()))
            { pmin = simHit->pabs(); lastSimHit = &(*simHit); }
       }

       // get TOF
       if(!(lastSimHit == 0))
         hLastTOF->Fill(lastSimHit->timeOfFlight());

       // final looper hits
       for(std::vector<PSimHit>::const_iterator
           simHit = looper_hits.begin();
           simHit!= looper_hits.end(); simHit++)  {
          if(!(firstSimHit->pabs() == simHit->pabs()) && simHit->processType() == 2)   // BEWARE
            final_looper_hits.push_back(*simHit);
       }

       for(std::vector<PSimHit>::const_iterator lSimHit = final_looper_hits.begin();
                                                lSimHit != final_looper_hits.end(); lSimHit++)  {
          //we have to compare the final_looper_hits to associated simHits
          bool back = false;  // if we find the corresponding recHit, we should take the next element of final_looper_hit 
          for(SiPixelRecHitCollection::const_iterator detunit_iter = theHits->begin();
                                                   detunit_iter!= theHits->end(); detunit_iter++)
          {
            if(back)
              break;
            SiPixelRecHitCollection::DetSet range = *detunit_iter;
            unsigned int id = range.detId();
            const PixelGeomDetUnit* pixelDet =
              dynamic_cast<const PixelGeomDetUnit*> (theTracker->idToDet((id)));

            PXBDetId pid(id); 
            // Take all hits
            if(pid.subdetId() == PixelSubdetector::PixelBarrel && pid.layer()==(unsigned)desLayer)
              for(SiPixelRecHitCollection::DetSet::const_iterator recHit = range.begin();
                                                          recHit!= range.end(); recHit++)
              {
                if(back)
                  break;
                GlobalPoint gpos = pixelDet->toGlobal(recHit->localPosition());
                // eta and eloss
                float x = fabs(gpos.x() - theBeamSpot->position().x());
                float y = fabs(gpos.y() - theBeamSpot->position().y());
                double R = TMath::Sqrt(x*x + y*y);
                float eta = -log(tan(atan2(R,(gpos.z()-rver_z))/2.));
                float eloss = recHit->cluster()->charge();
                int clustSizeY = recHit->cluster()->sizeY();

//TEST -starts-
//           	//check if it is passed
//                bool HitPassed = false;
//                for(std::vector<const SiPixelRecHit*>::const_iterator passedrecHit = passedClusters.begin(); passedrecHit != passedClusters.end(); ++passedrecHit ) {
//                  if(compareRecHits((*passedrecHit),&(*recHit)))
//                  { HitPassed = true; break; }
//                }
//                if(!HitPassed)
//                  continue;
//TEST -ends-
                // associate 
                simHits_ass = theHitAssociator.associateHit(*recHit);
                // compare the simHits_ass and final_looper_hits
                for(std::vector<PSimHit>::const_iterator assSimHit = simHits_ass.begin();
                                                         assSimHit != simHits_ass.end(); assSimHit++)  {
                    if(comparePSimHits(&(*lSimHit),&(*assSimHit))) {
                      vector<float> input;

                      input.push_back(bMean_mc); //B_mc
                      input.push_back(npartMean); //NPart
                      input.push_back(npartSigma);//NPartSigma
                      input.push_back(ncollMean); //NColl
                      input.push_back(ncollSigma);//NCollSigma
                      input.push_back(nhardMean); //NHard
                      input.push_back(nhardSigma);//NHardSigma
                      input.push_back(bMean);     //B
                      input.push_back(bSigma);    //BSigma

                      input.push_back(rver_z);
                      input.push_back(eloss);
                      input.push_back(eta);
//                      input.push_back(vertices->size());
                      input.push_back(1);
                      input.push_back(clustSizeY);
                      input.push_back(cluster_counter);

                      // number of hits
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<3.0 && eta>2.5)
                        looperHits_etaP6++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<2.5 && eta>2.0)
                        looperHits_etaP5++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=2.0 && eta>1.5)
                        looperHits_etaP4++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=1.5 && eta>1.0)
                        looperHits_etaP3++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=1.0 && eta>0.5)
                        looperHits_etaP2++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=0.5 && eta>0.0)
                        looperHits_etaP1++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=0.0 && eta>-0.5)
                        looperHits_etaN1++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=-0.5 && eta>-1.0)
                        looperHits_etaN2++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=-1.0 && eta>-1.5)
                        looperHits_etaN3++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=-1.5 && eta>-2.0)
                        looperHits_etaN4++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=-2.0 && eta>-2.5)
                        looperHits_etaN5++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=-2.5 && eta>-3.0)
                        looperHits_etaN6++;

                      // Filling
                      if(desLayer==1)
                        hJustLooper->Fill(&input[0]);
                      if(desLayer==2)
                        nd_hJustLooper->Fill(&input[0]);
                      if(desLayer==3)
                        rd_hJustLooper->Fill(&input[0]);

                      back = true;
                      break;
                    }
                }
              }
          } //end of recHits
       }
    } //end of trackingParticles

  } // end of always if
//  } // end of 1vtx condition

  looper_result.push_back(looperHits_etaP6);
  looper_result.push_back(looperHits_etaP5);
  looper_result.push_back(looperHits_etaP4);
  looper_result.push_back(looperHits_etaP3);
  looper_result.push_back(looperHits_etaP2);
  looper_result.push_back(looperHits_etaP1);
  looper_result.push_back(looperHits_etaN1);
  looper_result.push_back(looperHits_etaN2);
  looper_result.push_back(looperHits_etaN3);
  looper_result.push_back(looperHits_etaN4);
  looper_result.push_back(looperHits_etaN5);
  looper_result.push_back(looperHits_etaN6);
  looper_result.push_back(cluster_counter);

  if(desLayer==1)  
    NLooper->Fill(&looper_result[0]);
  if(desLayer==2)  
    nd_NLooper->Fill(&looper_result[0]);
  if(desLayer==3)  
    rd_NLooper->Fill(&looper_result[0]);

//LOOPER part ends here
}

/*****************************************************************************/
bool HI_simple_sim::isAtEdge
  (const RectangularPixelTopology* topology, const SiPixelRecHit & recHit)
{
  return topology->isItEdgePixelInX(recHit.cluster()->minPixelCol()) ||
         topology->isItEdgePixelInX(recHit.cluster()->maxPixelCol()) ||
         topology->isItEdgePixelInY(recHit.cluster()->minPixelRow()) ||
         topology->isItEdgePixelInY(recHit.cluster()->maxPixelRow());
}

/*****************************************************************************/
vector<PSimHit> HI_simple_sim::orderPSimHits(vector<PSimHit> simHits)
{
  vector<PSimHit> ordered;
  PSimHit * earliest = 0;
  vector<PSimHit>::iterator lemma;
  float pmax = 0.;
  int i = 0;
  int boundary = simHits.size();
  for(i=0; i < boundary; i++) {
     for(vector<PSimHit>::iterator simHit = simHits.begin();
         simHit!= simHits.end(); simHit++) {
        if(simHit->pabs() > pmax)
          { earliest = &(*simHit); pmax=simHit->pabs(); lemma = simHit; }
     }
     pmax = 0.;
     simHits.erase(lemma);
     ordered.push_back(*earliest);
  }
  return ordered;
}

/*****************************************************************************/
void HI_simple_sim::analyze
  (const edm::Event& ev, const edm::EventSetup& es)
{
//  std::cerr<<"[HI_simple_sim] started" << std::endl;

  // Get HI MC
  Handle<HepMCProduct> mcp;
  ev.getByType(mcp);
  const HepMC::GenEvent * mc = mcp->GetEvent();
  const HepMC::HeavyIon * hi_mc = mc->heavy_ion();  

  // Get centrality
  centrality_ = new CentralityProvider(es);
  centrality_->newEvent(ev,es);

  // Get tracker geometry
  edm::ESHandle<TrackerGeometry> tracker;
  es.get<TrackerDigiGeometryRecord>().get(tracker);
  theTracker = tracker.product();

  // Beam spot
  edm::Handle<BeamSpot>      beamSpotHandle;
  ev.getByLabel("offlineBeamSpot", beamSpotHandle);
  theBeamSpot = beamSpotHandle.product();

  // Get simulated
  edm::Handle<vector<PSimHit> > simHits;
  ev.getByLabel("g4SimHits","TrackerHitsPixelBarrelLowTof", simHits);

  // Get reconstructed
    //tracks -only if triggers are simulated (track triggers, etc.)-
  edm::Handle<reco::TrackCollection>  recCollection;
  ev.getByLabel("hltPixelTracksForMinBias", recCollection);
//  ev.getByLabel(trackCollectionLabel, recCollection);

    //calorimeter
    //Richard
  Handle<HcalTrigPrimDigiCollection> tpg;
  ev.getByLabel("hcalDigis",tpg);

  edm::Handle<CaloTowerCollection> towers; 
  ev.getByLabel("towerMaker",towers);

  // Get siPixelRecHits
  edm::Handle<SiPixelRecHitCollection> siPixelRecCollection;
  ev.getByLabel(src_,siPixelRecCollection);

  //MC
  Handle<HepMCProduct> evt;
  ev.getByType(evt);
//  ev.getByLabel("source",evt); //give strange procID number: 1,4,5,6,7
//  ev.getByLabel("generator",evt); /give strange procID number: 1,4,5,6,7
  HepMC::GenEvent * myGenEvent = new  HepMC::GenEvent(*(evt->GetEvent()));

  // Analyze

//  FirstSimOnFirst(siPixelRecCollection, ev, es);

//  std::cerr<<"   [HI_simple_sim] collections loaded..." << std::endl;
//  std::cerr<<"   [HI_simple_sim] layer1 started" << std::endl;

  multiplicityProperties(ev, es, towers, siPixelRecCollection, myGenEvent, recCollection, tpg, centrality_, hi_mc, 1);
  multiplicityProperties(ev, es, towers, siPixelRecCollection, myGenEvent, recCollection, tpg, centrality_, hi_mc, 2);
  multiplicityProperties(ev, es, towers, siPixelRecCollection, myGenEvent, recCollection, tpg, centrality_, hi_mc, 3);

//  std::cerr<<"   [HI_simple_sim] layer3 finished" << std::endl;

//  clusterVertices(ev, es, siPixelRecCollection);
}
DEFINE_FWK_MODULE(HI_simple_sim);


