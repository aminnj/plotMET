// -*- C++ -*-
#ifndef CMS3_H
#define CMS3_H
#include "Math/LorentzVector.h"
#include "Math/Point3D.h"
#include "TMath.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"
#include "TBits.h"
#include <vector> 
#include <unistd.h> 
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std; 
class CMS3 {
private: 
protected: 
	unsigned int index;
	TBits hlt_bits_;
	TBranch *hlt_bits_branch;
	bool hlt_bits_isLoaded;
	vector<TString> hlt_trigNames_;
	TBranch *hlt_trigNames_branch;
	bool hlt_trigNames_isLoaded;
	vector<TString> pfjets_bDiscriminatorNames_;
	TBranch *pfjets_bDiscriminatorNames_branch;
	bool pfjets_bDiscriminatorNames_isLoaded;
	bool hcalnoise_HasBadRBXTS4TS5_;
	TBranch *hcalnoise_HasBadRBXTS4TS5_branch;
	bool hcalnoise_HasBadRBXTS4TS5_isLoaded;
	bool evt_EcalDeadCellBoundaryEnergyFilter_;
	TBranch *evt_EcalDeadCellBoundaryEnergyFilter_branch;
	bool evt_EcalDeadCellBoundaryEnergyFilter_isLoaded;
	bool evt_EcalDeadCellTriggerPrimitiveFilter_;
	TBranch *evt_EcalDeadCellTriggerPrimitiveFilter_branch;
	bool evt_EcalDeadCellTriggerPrimitiveFilter_isLoaded;
	bool evt_cscTightHaloFilter_;
	TBranch *evt_cscTightHaloFilter_branch;
	bool evt_cscTightHaloFilter_isLoaded;
	bool evt_eeBadScFilter_;
	TBranch *evt_eeBadScFilter_branch;
	bool evt_eeBadScFilter_isLoaded;
	bool evt_eeNoiseFilter_;
	TBranch *evt_eeNoiseFilter_branch;
	bool evt_eeNoiseFilter_isLoaded;
	bool evt_goodVertices_;
	TBranch *evt_goodVertices_branch;
	bool evt_goodVertices_isLoaded;
	bool evt_hbheFilter_;
	TBranch *evt_hbheFilter_branch;
	bool evt_hbheFilter_isLoaded;
	bool evt_hbheFilterRun1_;
	TBranch *evt_hbheFilterRun1_branch;
	bool evt_hbheFilterRun1_isLoaded;
	bool evt_hbheFilterRun2Loose_;
	TBranch *evt_hbheFilterRun2Loose_branch;
	bool evt_hbheFilterRun2Loose_isLoaded;
	bool evt_hbheFilterRun2Tight_;
	TBranch *evt_hbheFilterRun2Tight_branch;
	bool evt_hbheFilterRun2Tight_isLoaded;
	bool evt_trackingFailureFilter_;
	TBranch *evt_trackingFailureFilter_branch;
	bool evt_trackingFailureFilter_isLoaded;
	float evt_bField_;
	TBranch *evt_bField_branch;
	bool evt_bField_isLoaded;
	float hcalnoise_GetRecHitEnergy_;
	TBranch *hcalnoise_GetRecHitEnergy_branch;
	bool hcalnoise_GetRecHitEnergy_isLoaded;
	float hcalnoise_GetRecHitEnergy15_;
	TBranch *hcalnoise_GetRecHitEnergy15_branch;
	bool hcalnoise_GetRecHitEnergy15_isLoaded;
	float hcalnoise_GetTotalCalibCharge_;
	TBranch *hcalnoise_GetTotalCalibCharge_branch;
	bool hcalnoise_GetTotalCalibCharge_isLoaded;
	float hcalnoise_TS4TS5NoiseSumE_;
	TBranch *hcalnoise_TS4TS5NoiseSumE_branch;
	bool hcalnoise_TS4TS5NoiseSumE_isLoaded;
	float hcalnoise_TS4TS5NoiseSumEt_;
	TBranch *hcalnoise_TS4TS5NoiseSumEt_branch;
	bool hcalnoise_TS4TS5NoiseSumEt_isLoaded;
	float hcalnoise_eventChargeFraction_;
	TBranch *hcalnoise_eventChargeFraction_branch;
	bool hcalnoise_eventChargeFraction_isLoaded;
	float hcalnoise_eventEMEnergy_;
	TBranch *hcalnoise_eventEMEnergy_branch;
	bool hcalnoise_eventEMEnergy_isLoaded;
	float hcalnoise_eventEMFraction_;
	TBranch *hcalnoise_eventEMFraction_branch;
	bool hcalnoise_eventEMFraction_isLoaded;
	float hcalnoise_eventHadEnergy_;
	TBranch *hcalnoise_eventHadEnergy_branch;
	bool hcalnoise_eventHadEnergy_isLoaded;
	float hcalnoise_eventTrackEnergy_;
	TBranch *hcalnoise_eventTrackEnergy_branch;
	bool hcalnoise_eventTrackEnergy_isLoaded;
	float hcalnoise_flatNoiseSumE_;
	TBranch *hcalnoise_flatNoiseSumE_branch;
	bool hcalnoise_flatNoiseSumE_isLoaded;
	float hcalnoise_flatNoiseSumEt_;
	TBranch *hcalnoise_flatNoiseSumEt_branch;
	bool hcalnoise_flatNoiseSumEt_isLoaded;
	float hcalnoise_isolatedNoiseSumE_;
	TBranch *hcalnoise_isolatedNoiseSumE_branch;
	bool hcalnoise_isolatedNoiseSumE_isLoaded;
	float hcalnoise_isolatedNoiseSumEt_;
	TBranch *hcalnoise_isolatedNoiseSumEt_branch;
	bool hcalnoise_isolatedNoiseSumEt_isLoaded;
	float hcalnoise_max10GeVHitTime_;
	TBranch *hcalnoise_max10GeVHitTime_branch;
	bool hcalnoise_max10GeVHitTime_isLoaded;
	float hcalnoise_max25GeVHitTime_;
	TBranch *hcalnoise_max25GeVHitTime_branch;
	bool hcalnoise_max25GeVHitTime_isLoaded;
	float hcalnoise_maxE10TS_;
	TBranch *hcalnoise_maxE10TS_branch;
	bool hcalnoise_maxE10TS_isLoaded;
	float hcalnoise_maxE2Over10TS_;
	TBranch *hcalnoise_maxE2Over10TS_branch;
	bool hcalnoise_maxE2Over10TS_isLoaded;
	float hcalnoise_maxE2TS_;
	TBranch *hcalnoise_maxE2TS_branch;
	bool hcalnoise_maxE2TS_isLoaded;
	float hcalnoise_min10GeVHitTime_;
	TBranch *hcalnoise_min10GeVHitTime_branch;
	bool hcalnoise_min10GeVHitTime_isLoaded;
	float hcalnoise_min25GeVHitTime_;
	TBranch *hcalnoise_min25GeVHitTime_branch;
	bool hcalnoise_min25GeVHitTime_isLoaded;
	float hcalnoise_minE10TS_;
	TBranch *hcalnoise_minE10TS_branch;
	bool hcalnoise_minE10TS_isLoaded;
	float hcalnoise_minE2Over10TS_;
	TBranch *hcalnoise_minE2Over10TS_branch;
	bool hcalnoise_minE2Over10TS_isLoaded;
	float hcalnoise_minE2TS_;
	TBranch *hcalnoise_minE2TS_branch;
	bool hcalnoise_minE2TS_isLoaded;
	float hcalnoise_minHPDEMF_;
	TBranch *hcalnoise_minHPDEMF_branch;
	bool hcalnoise_minHPDEMF_isLoaded;
	float hcalnoise_minRBXEMF_;
	TBranch *hcalnoise_minRBXEMF_branch;
	bool hcalnoise_minRBXEMF_isLoaded;
	float hcalnoise_rms10GeVHitTime_;
	TBranch *hcalnoise_rms10GeVHitTime_branch;
	bool hcalnoise_rms10GeVHitTime_isLoaded;
	float hcalnoise_rms25GeVHitTime_;
	TBranch *hcalnoise_rms25GeVHitTime_branch;
	bool hcalnoise_rms25GeVHitTime_isLoaded;
	float hcalnoise_spikeNoiseSumE_;
	TBranch *hcalnoise_spikeNoiseSumE_branch;
	bool hcalnoise_spikeNoiseSumE_isLoaded;
	float hcalnoise_spikeNoiseSumEt_;
	TBranch *hcalnoise_spikeNoiseSumEt_branch;
	bool hcalnoise_spikeNoiseSumEt_isLoaded;
	float hcalnoise_triangleNoiseSumE_;
	TBranch *hcalnoise_triangleNoiseSumE_branch;
	bool hcalnoise_triangleNoiseSumE_isLoaded;
	float hcalnoise_triangleNoiseSumEt_;
	TBranch *hcalnoise_triangleNoiseSumEt_branch;
	bool hcalnoise_triangleNoiseSumEt_isLoaded;
	float evt_ecalendcapm_met_;
	TBranch *evt_ecalendcapm_met_branch;
	bool evt_ecalendcapm_met_isLoaded;
	float evt_ecalendcapm_metPhi_;
	TBranch *evt_ecalendcapm_metPhi_branch;
	bool evt_ecalendcapm_metPhi_isLoaded;
	float evt_ecalendcapp_met_;
	TBranch *evt_ecalendcapp_met_branch;
	bool evt_ecalendcapp_met_isLoaded;
	float evt_ecalendcapp_metPhi_;
	TBranch *evt_ecalendcapp_metPhi_branch;
	bool evt_ecalendcapp_metPhi_isLoaded;
	float evt_ecalmet_;
	TBranch *evt_ecalmet_branch;
	bool evt_ecalmet_isLoaded;
	float evt_ecalmetPhi_;
	TBranch *evt_ecalmetPhi_branch;
	bool evt_ecalmetPhi_isLoaded;
	float evt_endcapm_met_;
	TBranch *evt_endcapm_met_branch;
	bool evt_endcapm_met_isLoaded;
	float evt_endcapm_metPhi_;
	TBranch *evt_endcapm_metPhi_branch;
	bool evt_endcapm_metPhi_isLoaded;
	float evt_endcapp_met_;
	TBranch *evt_endcapp_met_branch;
	bool evt_endcapp_met_isLoaded;
	float evt_endcapp_metPhi_;
	TBranch *evt_endcapp_metPhi_branch;
	bool evt_endcapp_metPhi_isLoaded;
	float evt_hcalendcapm_met_;
	TBranch *evt_hcalendcapm_met_branch;
	bool evt_hcalendcapm_met_isLoaded;
	float evt_hcalendcapm_metPhi_;
	TBranch *evt_hcalendcapm_metPhi_branch;
	bool evt_hcalendcapm_metPhi_isLoaded;
	float evt_hcalendcapp_met_;
	TBranch *evt_hcalendcapp_met_branch;
	bool evt_hcalendcapp_met_isLoaded;
	float evt_hcalendcapp_metPhi_;
	TBranch *evt_hcalendcapp_metPhi_branch;
	bool evt_hcalendcapp_metPhi_isLoaded;
	float evt_hcalmet_;
	TBranch *evt_hcalmet_branch;
	bool evt_hcalmet_isLoaded;
	float evt_hcalmetPhi_;
	TBranch *evt_hcalmetPhi_branch;
	bool evt_hcalmetPhi_isLoaded;
	float evt_met_;
	TBranch *evt_met_branch;
	bool evt_met_isLoaded;
	float evt_met_EtGt3_;
	TBranch *evt_met_EtGt3_branch;
	bool evt_met_EtGt3_isLoaded;
	float evt_metHO_;
	TBranch *evt_metHO_branch;
	bool evt_metHO_isLoaded;
	float evt_metHOPhi_;
	TBranch *evt_metHOPhi_branch;
	bool evt_metHOPhi_isLoaded;
	float evt_metHOSig_;
	TBranch *evt_metHOSig_branch;
	bool evt_metHOSig_isLoaded;
	float evt_metMuonCorr_;
	TBranch *evt_metMuonCorr_branch;
	bool evt_metMuonCorr_isLoaded;
	float evt_metMuonCorrPhi_;
	TBranch *evt_metMuonCorrPhi_branch;
	bool evt_metMuonCorrPhi_isLoaded;
	float evt_metMuonCorrSig_;
	TBranch *evt_metMuonCorrSig_branch;
	bool evt_metMuonCorrSig_isLoaded;
	float evt_metMuonJESCorr_;
	TBranch *evt_metMuonJESCorr_branch;
	bool evt_metMuonJESCorr_isLoaded;
	float evt_metMuonJESCorrPhi_;
	TBranch *evt_metMuonJESCorrPhi_branch;
	bool evt_metMuonJESCorrPhi_isLoaded;
	float evt_metMuonJESCorrSig_;
	TBranch *evt_metMuonJESCorrSig_branch;
	bool evt_metMuonJESCorrSig_isLoaded;
	float evt_metNoHF_;
	TBranch *evt_metNoHF_branch;
	bool evt_metNoHF_isLoaded;
	float evt_metNoHFHO_;
	TBranch *evt_metNoHFHO_branch;
	bool evt_metNoHFHO_isLoaded;
	float evt_metNoHFHOPhi_;
	TBranch *evt_metNoHFHOPhi_branch;
	bool evt_metNoHFHOPhi_isLoaded;
	float evt_metNoHFHOSig_;
	TBranch *evt_metNoHFHOSig_branch;
	bool evt_metNoHFHOSig_isLoaded;
	float evt_metNoHFPhi_;
	TBranch *evt_metNoHFPhi_branch;
	bool evt_metNoHFPhi_isLoaded;
	float evt_metNoHFSig_;
	TBranch *evt_metNoHFSig_branch;
	bool evt_metNoHFSig_isLoaded;
	float evt_metOpt_;
	TBranch *evt_metOpt_branch;
	bool evt_metOpt_isLoaded;
	float evt_metOptHO_;
	TBranch *evt_metOptHO_branch;
	bool evt_metOptHO_isLoaded;
	float evt_metOptHOPhi_;
	TBranch *evt_metOptHOPhi_branch;
	bool evt_metOptHOPhi_isLoaded;
	float evt_metOptHOSig_;
	TBranch *evt_metOptHOSig_branch;
	bool evt_metOptHOSig_isLoaded;
	float evt_metOptNoHF_;
	TBranch *evt_metOptNoHF_branch;
	bool evt_metOptNoHF_isLoaded;
	float evt_metOptNoHFHO_;
	TBranch *evt_metOptNoHFHO_branch;
	bool evt_metOptNoHFHO_isLoaded;
	float evt_metOptNoHFHOPhi_;
	TBranch *evt_metOptNoHFHOPhi_branch;
	bool evt_metOptNoHFHOPhi_isLoaded;
	float evt_metOptNoHFHOSig_;
	TBranch *evt_metOptNoHFHOSig_branch;
	bool evt_metOptNoHFHOSig_isLoaded;
	float evt_metOptNoHFPhi_;
	TBranch *evt_metOptNoHFPhi_branch;
	bool evt_metOptNoHFPhi_isLoaded;
	float evt_metOptNoHFSig_;
	TBranch *evt_metOptNoHFSig_branch;
	bool evt_metOptNoHFSig_isLoaded;
	float evt_metOptPhi_;
	TBranch *evt_metOptPhi_branch;
	bool evt_metOptPhi_isLoaded;
	float evt_metOptSig_;
	TBranch *evt_metOptSig_branch;
	bool evt_metOptSig_isLoaded;
	float evt_metPhi_;
	TBranch *evt_metPhi_branch;
	bool evt_metPhi_isLoaded;
	float evt_metPhi_EtGt3_;
	TBranch *evt_metPhi_EtGt3_branch;
	bool evt_metPhi_EtGt3_isLoaded;
	float evt_metSig_;
	TBranch *evt_metSig_branch;
	bool evt_metSig_isLoaded;
	float evt_sumet_;
	TBranch *evt_sumet_branch;
	bool evt_sumet_isLoaded;
	float evt_sumet_EtGt3_;
	TBranch *evt_sumet_EtGt3_branch;
	bool evt_sumet_EtGt3_isLoaded;
	float evt_sumetHO_;
	TBranch *evt_sumetHO_branch;
	bool evt_sumetHO_isLoaded;
	float evt_sumetMuonCorr_;
	TBranch *evt_sumetMuonCorr_branch;
	bool evt_sumetMuonCorr_isLoaded;
	float evt_sumetMuonJESCorr_;
	TBranch *evt_sumetMuonJESCorr_branch;
	bool evt_sumetMuonJESCorr_isLoaded;
	float evt_sumetNoHF_;
	TBranch *evt_sumetNoHF_branch;
	bool evt_sumetNoHF_isLoaded;
	float evt_sumetNoHFHO_;
	TBranch *evt_sumetNoHFHO_branch;
	bool evt_sumetNoHFHO_isLoaded;
	float evt_sumetOpt_;
	TBranch *evt_sumetOpt_branch;
	bool evt_sumetOpt_isLoaded;
	float evt_sumetOptHO_;
	TBranch *evt_sumetOptHO_branch;
	bool evt_sumetOptHO_isLoaded;
	float evt_sumetOptNoHF_;
	TBranch *evt_sumetOptNoHF_branch;
	bool evt_sumetOptNoHF_isLoaded;
	float evt_sumetOptNoHFHO_;
	TBranch *evt_sumetOptNoHFHO_branch;
	bool evt_sumetOptNoHFHO_isLoaded;
	float pfCaloMet_met_;
	TBranch *pfCaloMet_met_branch;
	bool pfCaloMet_met_isLoaded;
	float pfCaloMet_metPhi_;
	TBranch *pfCaloMet_metPhi_branch;
	bool pfCaloMet_metPhi_isLoaded;
	float pfCaloMet_metPhi_type1cor_;
	TBranch *pfCaloMet_metPhi_type1cor_branch;
	bool pfCaloMet_metPhi_type1cor_isLoaded;
	float pfCaloMet_metSig_;
	TBranch *pfCaloMet_metSig_branch;
	bool pfCaloMet_metSig_isLoaded;
	float pfCaloMet_metSignificance_;
	TBranch *pfCaloMet_metSignificance_branch;
	bool pfCaloMet_metSignificance_isLoaded;
	float pfCaloMet_met_type1cor_;
	TBranch *pfCaloMet_met_type1cor_branch;
	bool pfCaloMet_met_type1cor_isLoaded;
	float pfCaloMet_sumet_;
	TBranch *pfCaloMet_sumet_branch;
	bool pfCaloMet_sumet_isLoaded;
	float pfChMet_met_;
	TBranch *pfChMet_met_branch;
	bool pfChMet_met_isLoaded;
	float pfChMet_metPhi_;
	TBranch *pfChMet_metPhi_branch;
	bool pfChMet_metPhi_isLoaded;
	float pfChMet_metPhi_type1cor_;
	TBranch *pfChMet_metPhi_type1cor_branch;
	bool pfChMet_metPhi_type1cor_isLoaded;
	float pfChMet_metSig_;
	TBranch *pfChMet_metSig_branch;
	bool pfChMet_metSig_isLoaded;
	float pfChMet_metSignificance_;
	TBranch *pfChMet_metSignificance_branch;
	bool pfChMet_metSignificance_isLoaded;
	float pfChMet_met_type1cor_;
	TBranch *pfChMet_met_type1cor_branch;
	bool pfChMet_met_type1cor_isLoaded;
	float pfChMet_sumet_;
	TBranch *pfChMet_sumet_branch;
	bool pfChMet_sumet_isLoaded;
	float pfcluster_met_;
	TBranch *pfcluster_met_branch;
	bool pfcluster_met_isLoaded;
	float pfcluster_metphi_;
	TBranch *pfcluster_metphi_branch;
	bool pfcluster_metphi_isLoaded;
	float pfcluster_sumet_;
	TBranch *pfcluster_sumet_branch;
	bool pfcluster_sumet_isLoaded;
	float pfMet_met_;
	TBranch *pfMet_met_branch;
	bool pfMet_met_isLoaded;
	float pfMet_metPhi_;
	TBranch *pfMet_metPhi_branch;
	bool pfMet_metPhi_isLoaded;
	float pfMet_metPhi_type1cor_;
	TBranch *pfMet_metPhi_type1cor_branch;
	bool pfMet_metPhi_type1cor_isLoaded;
	float pfMet_metSig_;
	TBranch *pfMet_metSig_branch;
	bool pfMet_metSig_isLoaded;
	float pfMet_metSignificance_;
	TBranch *pfMet_metSignificance_branch;
	bool pfMet_metSignificance_isLoaded;
	float pfMet_met_type1cor_;
	TBranch *pfMet_met_type1cor_branch;
	bool pfMet_met_type1cor_isLoaded;
	float pfMet_sumet_;
	TBranch *pfMet_sumet_branch;
	bool pfMet_sumet_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > pfcands_p4_;
	TBranch *pfcands_p4_branch;
	bool pfcands_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > pfjets_p4_;
	TBranch *pfjets_p4_branch;
	bool pfjets_p4_isLoaded;
	vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > hlt_trigObjs_p4_;
	TBranch *hlt_trigObjs_p4_branch;
	bool hlt_trigObjs_p4_isLoaded;
	vector<float> calojets_eta_;
	TBranch *calojets_eta_branch;
	bool calojets_eta_isLoaded;
	vector<float> calojets_phi_;
	TBranch *calojets_phi_branch;
	bool calojets_phi_isLoaded;
	vector<float> calojets_pt_;
	TBranch *calojets_pt_branch;
	bool calojets_pt_isLoaded;
	vector<float> twrs_ecalTime_;
	TBranch *twrs_ecalTime_branch;
	bool twrs_ecalTime_isLoaded;
	vector<float> twrs_emEnergy_;
	TBranch *twrs_emEnergy_branch;
	bool twrs_emEnergy_isLoaded;
	vector<float> twrs_emEt_;
	TBranch *twrs_emEt_branch;
	bool twrs_emEt_isLoaded;
	vector<float> twrs_emEtcorr_;
	TBranch *twrs_emEtcorr_branch;
	bool twrs_emEtcorr_isLoaded;
	vector<float> twrs_eta_;
	TBranch *twrs_eta_branch;
	bool twrs_eta_isLoaded;
	vector<float> twrs_etacorr_;
	TBranch *twrs_etacorr_branch;
	bool twrs_etacorr_isLoaded;
	vector<float> twrs_etcorr_;
	TBranch *twrs_etcorr_branch;
	bool twrs_etcorr_isLoaded;
	vector<float> twrs_hadEnergy_;
	TBranch *twrs_hadEnergy_branch;
	bool twrs_hadEnergy_isLoaded;
	vector<float> twrs_hadEt_;
	TBranch *twrs_hadEt_branch;
	bool twrs_hadEt_isLoaded;
	vector<float> twrs_hadEtcorr_;
	TBranch *twrs_hadEtcorr_branch;
	bool twrs_hadEtcorr_isLoaded;
	vector<float> twrs_hcalTime_;
	TBranch *twrs_hcalTime_branch;
	bool twrs_hcalTime_isLoaded;
	vector<float> twrs_outerEnergy_;
	TBranch *twrs_outerEnergy_branch;
	bool twrs_outerEnergy_isLoaded;
	vector<float> twrs_outerEt_;
	TBranch *twrs_outerEt_branch;
	bool twrs_outerEt_isLoaded;
	vector<float> twrs_outerEtcorr_;
	TBranch *twrs_outerEtcorr_branch;
	bool twrs_outerEtcorr_isLoaded;
	vector<float> twrs_pcorr_;
	TBranch *twrs_pcorr_branch;
	bool twrs_pcorr_isLoaded;
	vector<float> twrs_phi_;
	TBranch *twrs_phi_branch;
	bool twrs_phi_isLoaded;
	vector<float> twrs_phicorr_;
	TBranch *twrs_phicorr_branch;
	bool twrs_phicorr_isLoaded;
	vector<float> twrs_spikeEt_;
	TBranch *twrs_spikeEt_branch;
	bool twrs_spikeEt_isLoaded;
	vector<float> twrs_spikeR4_;
	TBranch *twrs_spikeR4_branch;
	bool twrs_spikeR4_isLoaded;
	vector<float> evt_ecalmet_etaslice_;
	TBranch *evt_ecalmet_etaslice_branch;
	bool evt_ecalmet_etaslice_isLoaded;
	vector<float> evt_ecalmet_etaslicePhi_;
	TBranch *evt_ecalmet_etaslicePhi_branch;
	bool evt_ecalmet_etaslicePhi_isLoaded;
	vector<float> evt_hcalmet_etaslice_;
	TBranch *evt_hcalmet_etaslice_branch;
	bool evt_hcalmet_etaslice_isLoaded;
	vector<float> evt_hcalmet_etaslicePhi_;
	TBranch *evt_hcalmet_etaslicePhi_branch;
	bool evt_hcalmet_etaslicePhi_isLoaded;
	vector<float> evt_towermet_etaslice_;
	TBranch *evt_towermet_etaslice_branch;
	bool evt_towermet_etaslice_isLoaded;
	vector<float> evt_towermet_etaslicePhi_;
	TBranch *evt_towermet_etaslicePhi_branch;
	bool evt_towermet_etaslicePhi_isLoaded;
	vector<float> mus_met_deltax_;
	TBranch *mus_met_deltax_branch;
	bool mus_met_deltax_isLoaded;
	vector<float> mus_met_deltay_;
	TBranch *mus_met_deltay_branch;
	bool mus_met_deltay_isLoaded;
	vector<float> pfcands_mass_;
	TBranch *pfcands_mass_branch;
	bool pfcands_mass_isLoaded;
	vector<float> pfcluster_energy_;
	TBranch *pfcluster_energy_branch;
	bool pfcluster_energy_isLoaded;
	vector<float> pfcluster_et_;
	TBranch *pfcluster_et_branch;
	bool pfcluster_et_isLoaded;
	vector<float> pfcluster_eta_;
	TBranch *pfcluster_eta_branch;
	bool pfcluster_eta_isLoaded;
	vector<float> pfcluster_phi_;
	TBranch *pfcluster_phi_branch;
	bool pfcluster_phi_isLoaded;
	vector<float> pfjets_area_;
	TBranch *pfjets_area_branch;
	bool pfjets_area_isLoaded;
	vector<float> pfjets_chargedEmE_;
	TBranch *pfjets_chargedEmE_branch;
	bool pfjets_chargedEmE_isLoaded;
	vector<float> pfjets_chargedHadronE_;
	TBranch *pfjets_chargedHadronE_branch;
	bool pfjets_chargedHadronE_isLoaded;
	vector<float> pfjets_electronE_;
	TBranch *pfjets_electronE_branch;
	bool pfjets_electronE_isLoaded;
	vector<float> pfjets_hfEmE_;
	TBranch *pfjets_hfEmE_branch;
	bool pfjets_hfEmE_isLoaded;
	vector<float> pfjets_hfHadronE_;
	TBranch *pfjets_hfHadronE_branch;
	bool pfjets_hfHadronE_isLoaded;
	vector<float> pfjets_mass_;
	TBranch *pfjets_mass_branch;
	bool pfjets_mass_isLoaded;
	vector<float> pfjets_muonE_;
	TBranch *pfjets_muonE_branch;
	bool pfjets_muonE_isLoaded;
	vector<float> pfjets_neutralEmE_;
	TBranch *pfjets_neutralEmE_branch;
	bool pfjets_neutralEmE_isLoaded;
	vector<float> pfjets_neutralHadronE_;
	TBranch *pfjets_neutralHadronE_branch;
	bool pfjets_neutralHadronE_isLoaded;
	vector<float> pfjets_photonE_;
	TBranch *pfjets_photonE_branch;
	bool pfjets_photonE_isLoaded;
	vector<float> pfjets_undoJEC_;
	TBranch *pfjets_undoJEC_branch;
	bool pfjets_undoJEC_isLoaded;
	vector<vector<float> > pfjets_bDiscriminators_;
	TBranch *pfjets_bDiscriminators_branch;
	bool pfjets_bDiscriminators_isLoaded;
	int evt_bunchCrossing_;
	TBranch *evt_bunchCrossing_branch;
	bool evt_bunchCrossing_isLoaded;
	int evt_experimentType_;
	TBranch *evt_experimentType_branch;
	bool evt_experimentType_isLoaded;
	int evt_isRealData_;
	TBranch *evt_isRealData_branch;
	bool evt_isRealData_isLoaded;
	int evt_ntracks_;
	TBranch *evt_ntracks_branch;
	bool evt_ntracks_isLoaded;
	int evt_orbitNumber_;
	TBranch *evt_orbitNumber_branch;
	bool evt_orbitNumber_isLoaded;
	int evt_storeNumber_;
	TBranch *evt_storeNumber_branch;
	bool evt_storeNumber_isLoaded;
	int hcalnoise_GetRecHitCount_;
	TBranch *hcalnoise_GetRecHitCount_branch;
	bool hcalnoise_GetRecHitCount_isLoaded;
	int hcalnoise_GetRecHitCount15_;
	TBranch *hcalnoise_GetRecHitCount15_branch;
	bool hcalnoise_GetRecHitCount15_isLoaded;
	int hcalnoise_hbheIsoNoiseFilter_;
	TBranch *hcalnoise_hbheIsoNoiseFilter_branch;
	bool hcalnoise_hbheIsoNoiseFilter_isLoaded;
	int hcalnoise_maxHPDHits_;
	TBranch *hcalnoise_maxHPDHits_branch;
	bool hcalnoise_maxHPDHits_isLoaded;
	int hcalnoise_maxHPDNoOtherHits_;
	TBranch *hcalnoise_maxHPDNoOtherHits_branch;
	bool hcalnoise_maxHPDNoOtherHits_isLoaded;
	int hcalnoise_maxRBXHits_;
	TBranch *hcalnoise_maxRBXHits_branch;
	bool hcalnoise_maxRBXHits_isLoaded;
	int hcalnoise_maxZeros_;
	TBranch *hcalnoise_maxZeros_branch;
	bool hcalnoise_maxZeros_isLoaded;
	int hcalnoise_noiseFilterStatus_;
	TBranch *hcalnoise_noiseFilterStatus_branch;
	bool hcalnoise_noiseFilterStatus_isLoaded;
	int hcalnoise_noiseType_;
	TBranch *hcalnoise_noiseType_branch;
	bool hcalnoise_noiseType_isLoaded;
	int hcalnoise_num10GeVHits_;
	TBranch *hcalnoise_num10GeVHits_branch;
	bool hcalnoise_num10GeVHits_isLoaded;
	int hcalnoise_num25GeVHits_;
	TBranch *hcalnoise_num25GeVHits_branch;
	bool hcalnoise_num25GeVHits_isLoaded;
	int hcalnoise_numFlatNoiseChannels_;
	TBranch *hcalnoise_numFlatNoiseChannels_branch;
	bool hcalnoise_numFlatNoiseChannels_isLoaded;
	int hcalnoise_numIsolatedNoiseChannels_;
	TBranch *hcalnoise_numIsolatedNoiseChannels_branch;
	bool hcalnoise_numIsolatedNoiseChannels_isLoaded;
	int hcalnoise_numProblematicRBXs_;
	TBranch *hcalnoise_numProblematicRBXs_branch;
	bool hcalnoise_numProblematicRBXs_isLoaded;
	int hcalnoise_numSpikeNoiseChannels_;
	TBranch *hcalnoise_numSpikeNoiseChannels_branch;
	bool hcalnoise_numSpikeNoiseChannels_isLoaded;
	int hcalnoise_numTS4TS5NoiseChannels_;
	TBranch *hcalnoise_numTS4TS5NoiseChannels_branch;
	bool hcalnoise_numTS4TS5NoiseChannels_isLoaded;
	int hcalnoise_numTriangleNoiseChannels_;
	TBranch *hcalnoise_numTriangleNoiseChannels_branch;
	bool hcalnoise_numTriangleNoiseChannels_isLoaded;
	int hcalnoise_passHighLevelNoiseFilter_;
	TBranch *hcalnoise_passHighLevelNoiseFilter_branch;
	bool hcalnoise_passHighLevelNoiseFilter_isLoaded;
	int hcalnoise_passLooseNoiseFilter_;
	TBranch *hcalnoise_passLooseNoiseFilter_branch;
	bool hcalnoise_passLooseNoiseFilter_isLoaded;
	int hcalnoise_passTightNoiseFilter_;
	TBranch *hcalnoise_passTightNoiseFilter_branch;
	bool hcalnoise_passTightNoiseFilter_isLoaded;
	vector<int> twrs_ieta_;
	TBranch *twrs_ieta_branch;
	bool twrs_ieta_isLoaded;
	vector<int> twrs_iphi_;
	TBranch *twrs_iphi_branch;
	bool twrs_iphi_isLoaded;
	vector<int> twrs_numCrystals_;
	TBranch *twrs_numCrystals_branch;
	bool twrs_numCrystals_isLoaded;
	vector<int> mus_met_flag_;
	TBranch *mus_met_flag_branch;
	bool mus_met_flag_isLoaded;
	vector<int> pfcands_charge_;
	TBranch *pfcands_charge_branch;
	bool pfcands_charge_isLoaded;
	vector<int> pfcands_particleId_;
	TBranch *pfcands_particleId_branch;
	bool pfcands_particleId_isLoaded;
	vector<int> pfcluster_layer_;
	TBranch *pfcluster_layer_branch;
	bool pfcluster_layer_isLoaded;
	vector<int> pfjets_chargedHadronMultiplicity_;
	TBranch *pfjets_chargedHadronMultiplicity_branch;
	bool pfjets_chargedHadronMultiplicity_isLoaded;
	vector<int> pfjets_chargedMultiplicity_;
	TBranch *pfjets_chargedMultiplicity_branch;
	bool pfjets_chargedMultiplicity_isLoaded;
	vector<int> pfjets_electronMultiplicity_;
	TBranch *pfjets_electronMultiplicity_branch;
	bool pfjets_electronMultiplicity_isLoaded;
	vector<int> pfjets_muonMultiplicity_;
	TBranch *pfjets_muonMultiplicity_branch;
	bool pfjets_muonMultiplicity_isLoaded;
	vector<int> pfjets_neutralHadronMultiplicity_;
	TBranch *pfjets_neutralHadronMultiplicity_branch;
	bool pfjets_neutralHadronMultiplicity_isLoaded;
	vector<int> pfjets_neutralMultiplicity_;
	TBranch *pfjets_neutralMultiplicity_branch;
	bool pfjets_neutralMultiplicity_isLoaded;
	vector<int> pfjets_photonMultiplicity_;
	TBranch *pfjets_photonMultiplicity_branch;
	bool pfjets_photonMultiplicity_isLoaded;
	vector<vector<int> > hlt_trigObjs_id_;
	TBranch *hlt_trigObjs_id_branch;
	bool hlt_trigObjs_id_isLoaded;
	vector<vector<int> > pfjets_pfcandIndicies_;
	TBranch *pfjets_pfcandIndicies_branch;
	bool pfjets_pfcandIndicies_isLoaded;
	unsigned int evt_ntwrs_;
	TBranch *evt_ntwrs_branch;
	bool evt_ntwrs_isLoaded;
	unsigned int evt_detectorStatus_;
	TBranch *evt_detectorStatus_branch;
	bool evt_detectorStatus_isLoaded;
	unsigned int evt_event_;
	TBranch *evt_event_branch;
	bool evt_event_isLoaded;
	unsigned int evt_lumiBlock_;
	TBranch *evt_lumiBlock_branch;
	bool evt_lumiBlock_isLoaded;
	unsigned int evt_run_;
	TBranch *evt_run_branch;
	bool evt_run_isLoaded;
	vector<unsigned int> twrs_detid_;
	TBranch *twrs_detid_branch;
	bool twrs_detid_isLoaded;
	vector<unsigned int> twrs_numBadEcalCells_;
	TBranch *twrs_numBadEcalCells_branch;
	bool twrs_numBadEcalCells_isLoaded;
	vector<unsigned int> twrs_numBadHcalCells_;
	TBranch *twrs_numBadHcalCells_branch;
	bool twrs_numBadHcalCells_isLoaded;
	vector<unsigned int> twrs_numProblematicEcalCells_;
	TBranch *twrs_numProblematicEcalCells_branch;
	bool twrs_numProblematicEcalCells_isLoaded;
	vector<unsigned int> twrs_numProblematicHcalCells_;
	TBranch *twrs_numProblematicHcalCells_branch;
	bool twrs_numProblematicHcalCells_isLoaded;
	vector<unsigned int> twrs_numRecoveredEcalCells_;
	TBranch *twrs_numRecoveredEcalCells_branch;
	bool twrs_numRecoveredEcalCells_isLoaded;
	vector<unsigned int> twrs_numRecoveredHcalCells_;
	TBranch *twrs_numRecoveredHcalCells_branch;
	bool twrs_numRecoveredHcalCells_isLoaded;
	vector<unsigned int> hlt_prescales_;
	TBranch *hlt_prescales_branch;
	bool hlt_prescales_isLoaded;
public: 
void Init(TTree *tree) {
	hlt_bits_branch = 0;
	if (tree->GetAlias("hlt_bits") != 0) {
		hlt_bits_branch = tree->GetBranch(tree->GetAlias("hlt_bits"));
		if (hlt_bits_branch) {hlt_bits_branch->SetAddress(&hlt_bits_);}
	}
	pfcands_p4_branch = 0;
	if (tree->GetAlias("pfcands_p4") != 0) {
		pfcands_p4_branch = tree->GetBranch(tree->GetAlias("pfcands_p4"));
		if (pfcands_p4_branch) {pfcands_p4_branch->SetAddress(&pfcands_p4_);}
	}
	pfjets_p4_branch = 0;
	if (tree->GetAlias("pfjets_p4") != 0) {
		pfjets_p4_branch = tree->GetBranch(tree->GetAlias("pfjets_p4"));
		if (pfjets_p4_branch) {pfjets_p4_branch->SetAddress(&pfjets_p4_);}
	}
  tree->SetMakeClass(1);
	hlt_trigNames_branch = 0;
	if (tree->GetAlias("hlt_trigNames") != 0) {
		hlt_trigNames_branch = tree->GetBranch(tree->GetAlias("hlt_trigNames"));
		if (hlt_trigNames_branch) {hlt_trigNames_branch->SetAddress(&hlt_trigNames_);}
	}
	pfjets_bDiscriminatorNames_branch = 0;
	if (tree->GetAlias("pfjets_bDiscriminatorNames") != 0) {
		pfjets_bDiscriminatorNames_branch = tree->GetBranch(tree->GetAlias("pfjets_bDiscriminatorNames"));
		if (pfjets_bDiscriminatorNames_branch) {pfjets_bDiscriminatorNames_branch->SetAddress(&pfjets_bDiscriminatorNames_);}
	}
	hcalnoise_HasBadRBXTS4TS5_branch = 0;
	if (tree->GetAlias("hcalnoise_HasBadRBXTS4TS5") != 0) {
		hcalnoise_HasBadRBXTS4TS5_branch = tree->GetBranch(tree->GetAlias("hcalnoise_HasBadRBXTS4TS5"));
		if (hcalnoise_HasBadRBXTS4TS5_branch) {hcalnoise_HasBadRBXTS4TS5_branch->SetAddress(&hcalnoise_HasBadRBXTS4TS5_);}
	}
	evt_EcalDeadCellBoundaryEnergyFilter_branch = 0;
	if (tree->GetAlias("evt_EcalDeadCellBoundaryEnergyFilter") != 0) {
		evt_EcalDeadCellBoundaryEnergyFilter_branch = tree->GetBranch(tree->GetAlias("evt_EcalDeadCellBoundaryEnergyFilter"));
		if (evt_EcalDeadCellBoundaryEnergyFilter_branch) {evt_EcalDeadCellBoundaryEnergyFilter_branch->SetAddress(&evt_EcalDeadCellBoundaryEnergyFilter_);}
	}
	evt_EcalDeadCellTriggerPrimitiveFilter_branch = 0;
	if (tree->GetAlias("evt_EcalDeadCellTriggerPrimitiveFilter") != 0) {
		evt_EcalDeadCellTriggerPrimitiveFilter_branch = tree->GetBranch(tree->GetAlias("evt_EcalDeadCellTriggerPrimitiveFilter"));
		if (evt_EcalDeadCellTriggerPrimitiveFilter_branch) {evt_EcalDeadCellTriggerPrimitiveFilter_branch->SetAddress(&evt_EcalDeadCellTriggerPrimitiveFilter_);}
	}
	evt_cscTightHaloFilter_branch = 0;
	if (tree->GetAlias("evt_cscTightHaloFilter") != 0) {
		evt_cscTightHaloFilter_branch = tree->GetBranch(tree->GetAlias("evt_cscTightHaloFilter"));
		if (evt_cscTightHaloFilter_branch) {evt_cscTightHaloFilter_branch->SetAddress(&evt_cscTightHaloFilter_);}
	}
	evt_eeBadScFilter_branch = 0;
	if (tree->GetAlias("evt_eeBadScFilter") != 0) {
		evt_eeBadScFilter_branch = tree->GetBranch(tree->GetAlias("evt_eeBadScFilter"));
		if (evt_eeBadScFilter_branch) {evt_eeBadScFilter_branch->SetAddress(&evt_eeBadScFilter_);}
	}
	evt_eeNoiseFilter_branch = 0;
	if (tree->GetAlias("evt_eeNoiseFilter") != 0) {
		evt_eeNoiseFilter_branch = tree->GetBranch(tree->GetAlias("evt_eeNoiseFilter"));
		if (evt_eeNoiseFilter_branch) {evt_eeNoiseFilter_branch->SetAddress(&evt_eeNoiseFilter_);}
	}
	evt_goodVertices_branch = 0;
	if (tree->GetAlias("evt_goodVertices") != 0) {
		evt_goodVertices_branch = tree->GetBranch(tree->GetAlias("evt_goodVertices"));
		if (evt_goodVertices_branch) {evt_goodVertices_branch->SetAddress(&evt_goodVertices_);}
	}
	evt_hbheFilter_branch = 0;
	if (tree->GetAlias("evt_hbheFilter") != 0) {
		evt_hbheFilter_branch = tree->GetBranch(tree->GetAlias("evt_hbheFilter"));
		if (evt_hbheFilter_branch) {evt_hbheFilter_branch->SetAddress(&evt_hbheFilter_);}
	}
	evt_hbheFilterRun1_branch = 0;
	if (tree->GetAlias("evt_hbheFilterRun1") != 0) {
		evt_hbheFilterRun1_branch = tree->GetBranch(tree->GetAlias("evt_hbheFilterRun1"));
		if (evt_hbheFilterRun1_branch) {evt_hbheFilterRun1_branch->SetAddress(&evt_hbheFilterRun1_);}
	}
	evt_hbheFilterRun2Loose_branch = 0;
	if (tree->GetAlias("evt_hbheFilterRun2Loose") != 0) {
		evt_hbheFilterRun2Loose_branch = tree->GetBranch(tree->GetAlias("evt_hbheFilterRun2Loose"));
		if (evt_hbheFilterRun2Loose_branch) {evt_hbheFilterRun2Loose_branch->SetAddress(&evt_hbheFilterRun2Loose_);}
	}
	evt_hbheFilterRun2Tight_branch = 0;
	if (tree->GetAlias("evt_hbheFilterRun2Tight") != 0) {
		evt_hbheFilterRun2Tight_branch = tree->GetBranch(tree->GetAlias("evt_hbheFilterRun2Tight"));
		if (evt_hbheFilterRun2Tight_branch) {evt_hbheFilterRun2Tight_branch->SetAddress(&evt_hbheFilterRun2Tight_);}
	}
	evt_trackingFailureFilter_branch = 0;
	if (tree->GetAlias("evt_trackingFailureFilter") != 0) {
		evt_trackingFailureFilter_branch = tree->GetBranch(tree->GetAlias("evt_trackingFailureFilter"));
		if (evt_trackingFailureFilter_branch) {evt_trackingFailureFilter_branch->SetAddress(&evt_trackingFailureFilter_);}
	}
	evt_bField_branch = 0;
	if (tree->GetAlias("evt_bField") != 0) {
		evt_bField_branch = tree->GetBranch(tree->GetAlias("evt_bField"));
		if (evt_bField_branch) {evt_bField_branch->SetAddress(&evt_bField_);}
	}
	hcalnoise_GetRecHitEnergy_branch = 0;
	if (tree->GetAlias("hcalnoise_GetRecHitEnergy") != 0) {
		hcalnoise_GetRecHitEnergy_branch = tree->GetBranch(tree->GetAlias("hcalnoise_GetRecHitEnergy"));
		if (hcalnoise_GetRecHitEnergy_branch) {hcalnoise_GetRecHitEnergy_branch->SetAddress(&hcalnoise_GetRecHitEnergy_);}
	}
	hcalnoise_GetRecHitEnergy15_branch = 0;
	if (tree->GetAlias("hcalnoise_GetRecHitEnergy15") != 0) {
		hcalnoise_GetRecHitEnergy15_branch = tree->GetBranch(tree->GetAlias("hcalnoise_GetRecHitEnergy15"));
		if (hcalnoise_GetRecHitEnergy15_branch) {hcalnoise_GetRecHitEnergy15_branch->SetAddress(&hcalnoise_GetRecHitEnergy15_);}
	}
	hcalnoise_GetTotalCalibCharge_branch = 0;
	if (tree->GetAlias("hcalnoise_GetTotalCalibCharge") != 0) {
		hcalnoise_GetTotalCalibCharge_branch = tree->GetBranch(tree->GetAlias("hcalnoise_GetTotalCalibCharge"));
		if (hcalnoise_GetTotalCalibCharge_branch) {hcalnoise_GetTotalCalibCharge_branch->SetAddress(&hcalnoise_GetTotalCalibCharge_);}
	}
	hcalnoise_TS4TS5NoiseSumE_branch = 0;
	if (tree->GetAlias("hcalnoise_TS4TS5NoiseSumE") != 0) {
		hcalnoise_TS4TS5NoiseSumE_branch = tree->GetBranch(tree->GetAlias("hcalnoise_TS4TS5NoiseSumE"));
		if (hcalnoise_TS4TS5NoiseSumE_branch) {hcalnoise_TS4TS5NoiseSumE_branch->SetAddress(&hcalnoise_TS4TS5NoiseSumE_);}
	}
	hcalnoise_TS4TS5NoiseSumEt_branch = 0;
	if (tree->GetAlias("hcalnoise_TS4TS5NoiseSumEt") != 0) {
		hcalnoise_TS4TS5NoiseSumEt_branch = tree->GetBranch(tree->GetAlias("hcalnoise_TS4TS5NoiseSumEt"));
		if (hcalnoise_TS4TS5NoiseSumEt_branch) {hcalnoise_TS4TS5NoiseSumEt_branch->SetAddress(&hcalnoise_TS4TS5NoiseSumEt_);}
	}
	hcalnoise_eventChargeFraction_branch = 0;
	if (tree->GetAlias("hcalnoise_eventChargeFraction") != 0) {
		hcalnoise_eventChargeFraction_branch = tree->GetBranch(tree->GetAlias("hcalnoise_eventChargeFraction"));
		if (hcalnoise_eventChargeFraction_branch) {hcalnoise_eventChargeFraction_branch->SetAddress(&hcalnoise_eventChargeFraction_);}
	}
	hcalnoise_eventEMEnergy_branch = 0;
	if (tree->GetAlias("hcalnoise_eventEMEnergy") != 0) {
		hcalnoise_eventEMEnergy_branch = tree->GetBranch(tree->GetAlias("hcalnoise_eventEMEnergy"));
		if (hcalnoise_eventEMEnergy_branch) {hcalnoise_eventEMEnergy_branch->SetAddress(&hcalnoise_eventEMEnergy_);}
	}
	hcalnoise_eventEMFraction_branch = 0;
	if (tree->GetAlias("hcalnoise_eventEMFraction") != 0) {
		hcalnoise_eventEMFraction_branch = tree->GetBranch(tree->GetAlias("hcalnoise_eventEMFraction"));
		if (hcalnoise_eventEMFraction_branch) {hcalnoise_eventEMFraction_branch->SetAddress(&hcalnoise_eventEMFraction_);}
	}
	hcalnoise_eventHadEnergy_branch = 0;
	if (tree->GetAlias("hcalnoise_eventHadEnergy") != 0) {
		hcalnoise_eventHadEnergy_branch = tree->GetBranch(tree->GetAlias("hcalnoise_eventHadEnergy"));
		if (hcalnoise_eventHadEnergy_branch) {hcalnoise_eventHadEnergy_branch->SetAddress(&hcalnoise_eventHadEnergy_);}
	}
	hcalnoise_eventTrackEnergy_branch = 0;
	if (tree->GetAlias("hcalnoise_eventTrackEnergy") != 0) {
		hcalnoise_eventTrackEnergy_branch = tree->GetBranch(tree->GetAlias("hcalnoise_eventTrackEnergy"));
		if (hcalnoise_eventTrackEnergy_branch) {hcalnoise_eventTrackEnergy_branch->SetAddress(&hcalnoise_eventTrackEnergy_);}
	}
	hcalnoise_flatNoiseSumE_branch = 0;
	if (tree->GetAlias("hcalnoise_flatNoiseSumE") != 0) {
		hcalnoise_flatNoiseSumE_branch = tree->GetBranch(tree->GetAlias("hcalnoise_flatNoiseSumE"));
		if (hcalnoise_flatNoiseSumE_branch) {hcalnoise_flatNoiseSumE_branch->SetAddress(&hcalnoise_flatNoiseSumE_);}
	}
	hcalnoise_flatNoiseSumEt_branch = 0;
	if (tree->GetAlias("hcalnoise_flatNoiseSumEt") != 0) {
		hcalnoise_flatNoiseSumEt_branch = tree->GetBranch(tree->GetAlias("hcalnoise_flatNoiseSumEt"));
		if (hcalnoise_flatNoiseSumEt_branch) {hcalnoise_flatNoiseSumEt_branch->SetAddress(&hcalnoise_flatNoiseSumEt_);}
	}
	hcalnoise_isolatedNoiseSumE_branch = 0;
	if (tree->GetAlias("hcalnoise_isolatedNoiseSumE") != 0) {
		hcalnoise_isolatedNoiseSumE_branch = tree->GetBranch(tree->GetAlias("hcalnoise_isolatedNoiseSumE"));
		if (hcalnoise_isolatedNoiseSumE_branch) {hcalnoise_isolatedNoiseSumE_branch->SetAddress(&hcalnoise_isolatedNoiseSumE_);}
	}
	hcalnoise_isolatedNoiseSumEt_branch = 0;
	if (tree->GetAlias("hcalnoise_isolatedNoiseSumEt") != 0) {
		hcalnoise_isolatedNoiseSumEt_branch = tree->GetBranch(tree->GetAlias("hcalnoise_isolatedNoiseSumEt"));
		if (hcalnoise_isolatedNoiseSumEt_branch) {hcalnoise_isolatedNoiseSumEt_branch->SetAddress(&hcalnoise_isolatedNoiseSumEt_);}
	}
	hcalnoise_max10GeVHitTime_branch = 0;
	if (tree->GetAlias("hcalnoise_max10GeVHitTime") != 0) {
		hcalnoise_max10GeVHitTime_branch = tree->GetBranch(tree->GetAlias("hcalnoise_max10GeVHitTime"));
		if (hcalnoise_max10GeVHitTime_branch) {hcalnoise_max10GeVHitTime_branch->SetAddress(&hcalnoise_max10GeVHitTime_);}
	}
	hcalnoise_max25GeVHitTime_branch = 0;
	if (tree->GetAlias("hcalnoise_max25GeVHitTime") != 0) {
		hcalnoise_max25GeVHitTime_branch = tree->GetBranch(tree->GetAlias("hcalnoise_max25GeVHitTime"));
		if (hcalnoise_max25GeVHitTime_branch) {hcalnoise_max25GeVHitTime_branch->SetAddress(&hcalnoise_max25GeVHitTime_);}
	}
	hcalnoise_maxE10TS_branch = 0;
	if (tree->GetAlias("hcalnoise_maxE10TS") != 0) {
		hcalnoise_maxE10TS_branch = tree->GetBranch(tree->GetAlias("hcalnoise_maxE10TS"));
		if (hcalnoise_maxE10TS_branch) {hcalnoise_maxE10TS_branch->SetAddress(&hcalnoise_maxE10TS_);}
	}
	hcalnoise_maxE2Over10TS_branch = 0;
	if (tree->GetAlias("hcalnoise_maxE2Over10TS") != 0) {
		hcalnoise_maxE2Over10TS_branch = tree->GetBranch(tree->GetAlias("hcalnoise_maxE2Over10TS"));
		if (hcalnoise_maxE2Over10TS_branch) {hcalnoise_maxE2Over10TS_branch->SetAddress(&hcalnoise_maxE2Over10TS_);}
	}
	hcalnoise_maxE2TS_branch = 0;
	if (tree->GetAlias("hcalnoise_maxE2TS") != 0) {
		hcalnoise_maxE2TS_branch = tree->GetBranch(tree->GetAlias("hcalnoise_maxE2TS"));
		if (hcalnoise_maxE2TS_branch) {hcalnoise_maxE2TS_branch->SetAddress(&hcalnoise_maxE2TS_);}
	}
	hcalnoise_min10GeVHitTime_branch = 0;
	if (tree->GetAlias("hcalnoise_min10GeVHitTime") != 0) {
		hcalnoise_min10GeVHitTime_branch = tree->GetBranch(tree->GetAlias("hcalnoise_min10GeVHitTime"));
		if (hcalnoise_min10GeVHitTime_branch) {hcalnoise_min10GeVHitTime_branch->SetAddress(&hcalnoise_min10GeVHitTime_);}
	}
	hcalnoise_min25GeVHitTime_branch = 0;
	if (tree->GetAlias("hcalnoise_min25GeVHitTime") != 0) {
		hcalnoise_min25GeVHitTime_branch = tree->GetBranch(tree->GetAlias("hcalnoise_min25GeVHitTime"));
		if (hcalnoise_min25GeVHitTime_branch) {hcalnoise_min25GeVHitTime_branch->SetAddress(&hcalnoise_min25GeVHitTime_);}
	}
	hcalnoise_minE10TS_branch = 0;
	if (tree->GetAlias("hcalnoise_minE10TS") != 0) {
		hcalnoise_minE10TS_branch = tree->GetBranch(tree->GetAlias("hcalnoise_minE10TS"));
		if (hcalnoise_minE10TS_branch) {hcalnoise_minE10TS_branch->SetAddress(&hcalnoise_minE10TS_);}
	}
	hcalnoise_minE2Over10TS_branch = 0;
	if (tree->GetAlias("hcalnoise_minE2Over10TS") != 0) {
		hcalnoise_minE2Over10TS_branch = tree->GetBranch(tree->GetAlias("hcalnoise_minE2Over10TS"));
		if (hcalnoise_minE2Over10TS_branch) {hcalnoise_minE2Over10TS_branch->SetAddress(&hcalnoise_minE2Over10TS_);}
	}
	hcalnoise_minE2TS_branch = 0;
	if (tree->GetAlias("hcalnoise_minE2TS") != 0) {
		hcalnoise_minE2TS_branch = tree->GetBranch(tree->GetAlias("hcalnoise_minE2TS"));
		if (hcalnoise_minE2TS_branch) {hcalnoise_minE2TS_branch->SetAddress(&hcalnoise_minE2TS_);}
	}
	hcalnoise_minHPDEMF_branch = 0;
	if (tree->GetAlias("hcalnoise_minHPDEMF") != 0) {
		hcalnoise_minHPDEMF_branch = tree->GetBranch(tree->GetAlias("hcalnoise_minHPDEMF"));
		if (hcalnoise_minHPDEMF_branch) {hcalnoise_minHPDEMF_branch->SetAddress(&hcalnoise_minHPDEMF_);}
	}
	hcalnoise_minRBXEMF_branch = 0;
	if (tree->GetAlias("hcalnoise_minRBXEMF") != 0) {
		hcalnoise_minRBXEMF_branch = tree->GetBranch(tree->GetAlias("hcalnoise_minRBXEMF"));
		if (hcalnoise_minRBXEMF_branch) {hcalnoise_minRBXEMF_branch->SetAddress(&hcalnoise_minRBXEMF_);}
	}
	hcalnoise_rms10GeVHitTime_branch = 0;
	if (tree->GetAlias("hcalnoise_rms10GeVHitTime") != 0) {
		hcalnoise_rms10GeVHitTime_branch = tree->GetBranch(tree->GetAlias("hcalnoise_rms10GeVHitTime"));
		if (hcalnoise_rms10GeVHitTime_branch) {hcalnoise_rms10GeVHitTime_branch->SetAddress(&hcalnoise_rms10GeVHitTime_);}
	}
	hcalnoise_rms25GeVHitTime_branch = 0;
	if (tree->GetAlias("hcalnoise_rms25GeVHitTime") != 0) {
		hcalnoise_rms25GeVHitTime_branch = tree->GetBranch(tree->GetAlias("hcalnoise_rms25GeVHitTime"));
		if (hcalnoise_rms25GeVHitTime_branch) {hcalnoise_rms25GeVHitTime_branch->SetAddress(&hcalnoise_rms25GeVHitTime_);}
	}
	hcalnoise_spikeNoiseSumE_branch = 0;
	if (tree->GetAlias("hcalnoise_spikeNoiseSumE") != 0) {
		hcalnoise_spikeNoiseSumE_branch = tree->GetBranch(tree->GetAlias("hcalnoise_spikeNoiseSumE"));
		if (hcalnoise_spikeNoiseSumE_branch) {hcalnoise_spikeNoiseSumE_branch->SetAddress(&hcalnoise_spikeNoiseSumE_);}
	}
	hcalnoise_spikeNoiseSumEt_branch = 0;
	if (tree->GetAlias("hcalnoise_spikeNoiseSumEt") != 0) {
		hcalnoise_spikeNoiseSumEt_branch = tree->GetBranch(tree->GetAlias("hcalnoise_spikeNoiseSumEt"));
		if (hcalnoise_spikeNoiseSumEt_branch) {hcalnoise_spikeNoiseSumEt_branch->SetAddress(&hcalnoise_spikeNoiseSumEt_);}
	}
	hcalnoise_triangleNoiseSumE_branch = 0;
	if (tree->GetAlias("hcalnoise_triangleNoiseSumE") != 0) {
		hcalnoise_triangleNoiseSumE_branch = tree->GetBranch(tree->GetAlias("hcalnoise_triangleNoiseSumE"));
		if (hcalnoise_triangleNoiseSumE_branch) {hcalnoise_triangleNoiseSumE_branch->SetAddress(&hcalnoise_triangleNoiseSumE_);}
	}
	hcalnoise_triangleNoiseSumEt_branch = 0;
	if (tree->GetAlias("hcalnoise_triangleNoiseSumEt") != 0) {
		hcalnoise_triangleNoiseSumEt_branch = tree->GetBranch(tree->GetAlias("hcalnoise_triangleNoiseSumEt"));
		if (hcalnoise_triangleNoiseSumEt_branch) {hcalnoise_triangleNoiseSumEt_branch->SetAddress(&hcalnoise_triangleNoiseSumEt_);}
	}
	evt_ecalendcapm_met_branch = 0;
	if (tree->GetAlias("evt_ecalendcapm_met") != 0) {
		evt_ecalendcapm_met_branch = tree->GetBranch(tree->GetAlias("evt_ecalendcapm_met"));
		if (evt_ecalendcapm_met_branch) {evt_ecalendcapm_met_branch->SetAddress(&evt_ecalendcapm_met_);}
	}
	evt_ecalendcapm_metPhi_branch = 0;
	if (tree->GetAlias("evt_ecalendcapm_metPhi") != 0) {
		evt_ecalendcapm_metPhi_branch = tree->GetBranch(tree->GetAlias("evt_ecalendcapm_metPhi"));
		if (evt_ecalendcapm_metPhi_branch) {evt_ecalendcapm_metPhi_branch->SetAddress(&evt_ecalendcapm_metPhi_);}
	}
	evt_ecalendcapp_met_branch = 0;
	if (tree->GetAlias("evt_ecalendcapp_met") != 0) {
		evt_ecalendcapp_met_branch = tree->GetBranch(tree->GetAlias("evt_ecalendcapp_met"));
		if (evt_ecalendcapp_met_branch) {evt_ecalendcapp_met_branch->SetAddress(&evt_ecalendcapp_met_);}
	}
	evt_ecalendcapp_metPhi_branch = 0;
	if (tree->GetAlias("evt_ecalendcapp_metPhi") != 0) {
		evt_ecalendcapp_metPhi_branch = tree->GetBranch(tree->GetAlias("evt_ecalendcapp_metPhi"));
		if (evt_ecalendcapp_metPhi_branch) {evt_ecalendcapp_metPhi_branch->SetAddress(&evt_ecalendcapp_metPhi_);}
	}
	evt_ecalmet_branch = 0;
	if (tree->GetAlias("evt_ecalmet") != 0) {
		evt_ecalmet_branch = tree->GetBranch(tree->GetAlias("evt_ecalmet"));
		if (evt_ecalmet_branch) {evt_ecalmet_branch->SetAddress(&evt_ecalmet_);}
	}
	evt_ecalmetPhi_branch = 0;
	if (tree->GetAlias("evt_ecalmetPhi") != 0) {
		evt_ecalmetPhi_branch = tree->GetBranch(tree->GetAlias("evt_ecalmetPhi"));
		if (evt_ecalmetPhi_branch) {evt_ecalmetPhi_branch->SetAddress(&evt_ecalmetPhi_);}
	}
	evt_endcapm_met_branch = 0;
	if (tree->GetAlias("evt_endcapm_met") != 0) {
		evt_endcapm_met_branch = tree->GetBranch(tree->GetAlias("evt_endcapm_met"));
		if (evt_endcapm_met_branch) {evt_endcapm_met_branch->SetAddress(&evt_endcapm_met_);}
	}
	evt_endcapm_metPhi_branch = 0;
	if (tree->GetAlias("evt_endcapm_metPhi") != 0) {
		evt_endcapm_metPhi_branch = tree->GetBranch(tree->GetAlias("evt_endcapm_metPhi"));
		if (evt_endcapm_metPhi_branch) {evt_endcapm_metPhi_branch->SetAddress(&evt_endcapm_metPhi_);}
	}
	evt_endcapp_met_branch = 0;
	if (tree->GetAlias("evt_endcapp_met") != 0) {
		evt_endcapp_met_branch = tree->GetBranch(tree->GetAlias("evt_endcapp_met"));
		if (evt_endcapp_met_branch) {evt_endcapp_met_branch->SetAddress(&evt_endcapp_met_);}
	}
	evt_endcapp_metPhi_branch = 0;
	if (tree->GetAlias("evt_endcapp_metPhi") != 0) {
		evt_endcapp_metPhi_branch = tree->GetBranch(tree->GetAlias("evt_endcapp_metPhi"));
		if (evt_endcapp_metPhi_branch) {evt_endcapp_metPhi_branch->SetAddress(&evt_endcapp_metPhi_);}
	}
	evt_hcalendcapm_met_branch = 0;
	if (tree->GetAlias("evt_hcalendcapm_met") != 0) {
		evt_hcalendcapm_met_branch = tree->GetBranch(tree->GetAlias("evt_hcalendcapm_met"));
		if (evt_hcalendcapm_met_branch) {evt_hcalendcapm_met_branch->SetAddress(&evt_hcalendcapm_met_);}
	}
	evt_hcalendcapm_metPhi_branch = 0;
	if (tree->GetAlias("evt_hcalendcapm_metPhi") != 0) {
		evt_hcalendcapm_metPhi_branch = tree->GetBranch(tree->GetAlias("evt_hcalendcapm_metPhi"));
		if (evt_hcalendcapm_metPhi_branch) {evt_hcalendcapm_metPhi_branch->SetAddress(&evt_hcalendcapm_metPhi_);}
	}
	evt_hcalendcapp_met_branch = 0;
	if (tree->GetAlias("evt_hcalendcapp_met") != 0) {
		evt_hcalendcapp_met_branch = tree->GetBranch(tree->GetAlias("evt_hcalendcapp_met"));
		if (evt_hcalendcapp_met_branch) {evt_hcalendcapp_met_branch->SetAddress(&evt_hcalendcapp_met_);}
	}
	evt_hcalendcapp_metPhi_branch = 0;
	if (tree->GetAlias("evt_hcalendcapp_metPhi") != 0) {
		evt_hcalendcapp_metPhi_branch = tree->GetBranch(tree->GetAlias("evt_hcalendcapp_metPhi"));
		if (evt_hcalendcapp_metPhi_branch) {evt_hcalendcapp_metPhi_branch->SetAddress(&evt_hcalendcapp_metPhi_);}
	}
	evt_hcalmet_branch = 0;
	if (tree->GetAlias("evt_hcalmet") != 0) {
		evt_hcalmet_branch = tree->GetBranch(tree->GetAlias("evt_hcalmet"));
		if (evt_hcalmet_branch) {evt_hcalmet_branch->SetAddress(&evt_hcalmet_);}
	}
	evt_hcalmetPhi_branch = 0;
	if (tree->GetAlias("evt_hcalmetPhi") != 0) {
		evt_hcalmetPhi_branch = tree->GetBranch(tree->GetAlias("evt_hcalmetPhi"));
		if (evt_hcalmetPhi_branch) {evt_hcalmetPhi_branch->SetAddress(&evt_hcalmetPhi_);}
	}
	evt_met_branch = 0;
	if (tree->GetAlias("evt_met") != 0) {
		evt_met_branch = tree->GetBranch(tree->GetAlias("evt_met"));
		if (evt_met_branch) {evt_met_branch->SetAddress(&evt_met_);}
	}
	evt_met_EtGt3_branch = 0;
	if (tree->GetAlias("evt_met_EtGt3") != 0) {
		evt_met_EtGt3_branch = tree->GetBranch(tree->GetAlias("evt_met_EtGt3"));
		if (evt_met_EtGt3_branch) {evt_met_EtGt3_branch->SetAddress(&evt_met_EtGt3_);}
	}
	evt_metHO_branch = 0;
	if (tree->GetAlias("evt_metHO") != 0) {
		evt_metHO_branch = tree->GetBranch(tree->GetAlias("evt_metHO"));
		if (evt_metHO_branch) {evt_metHO_branch->SetAddress(&evt_metHO_);}
	}
	evt_metHOPhi_branch = 0;
	if (tree->GetAlias("evt_metHOPhi") != 0) {
		evt_metHOPhi_branch = tree->GetBranch(tree->GetAlias("evt_metHOPhi"));
		if (evt_metHOPhi_branch) {evt_metHOPhi_branch->SetAddress(&evt_metHOPhi_);}
	}
	evt_metHOSig_branch = 0;
	if (tree->GetAlias("evt_metHOSig") != 0) {
		evt_metHOSig_branch = tree->GetBranch(tree->GetAlias("evt_metHOSig"));
		if (evt_metHOSig_branch) {evt_metHOSig_branch->SetAddress(&evt_metHOSig_);}
	}
	evt_metMuonCorr_branch = 0;
	if (tree->GetAlias("evt_metMuonCorr") != 0) {
		evt_metMuonCorr_branch = tree->GetBranch(tree->GetAlias("evt_metMuonCorr"));
		if (evt_metMuonCorr_branch) {evt_metMuonCorr_branch->SetAddress(&evt_metMuonCorr_);}
	}
	evt_metMuonCorrPhi_branch = 0;
	if (tree->GetAlias("evt_metMuonCorrPhi") != 0) {
		evt_metMuonCorrPhi_branch = tree->GetBranch(tree->GetAlias("evt_metMuonCorrPhi"));
		if (evt_metMuonCorrPhi_branch) {evt_metMuonCorrPhi_branch->SetAddress(&evt_metMuonCorrPhi_);}
	}
	evt_metMuonCorrSig_branch = 0;
	if (tree->GetAlias("evt_metMuonCorrSig") != 0) {
		evt_metMuonCorrSig_branch = tree->GetBranch(tree->GetAlias("evt_metMuonCorrSig"));
		if (evt_metMuonCorrSig_branch) {evt_metMuonCorrSig_branch->SetAddress(&evt_metMuonCorrSig_);}
	}
	evt_metMuonJESCorr_branch = 0;
	if (tree->GetAlias("evt_metMuonJESCorr") != 0) {
		evt_metMuonJESCorr_branch = tree->GetBranch(tree->GetAlias("evt_metMuonJESCorr"));
		if (evt_metMuonJESCorr_branch) {evt_metMuonJESCorr_branch->SetAddress(&evt_metMuonJESCorr_);}
	}
	evt_metMuonJESCorrPhi_branch = 0;
	if (tree->GetAlias("evt_metMuonJESCorrPhi") != 0) {
		evt_metMuonJESCorrPhi_branch = tree->GetBranch(tree->GetAlias("evt_metMuonJESCorrPhi"));
		if (evt_metMuonJESCorrPhi_branch) {evt_metMuonJESCorrPhi_branch->SetAddress(&evt_metMuonJESCorrPhi_);}
	}
	evt_metMuonJESCorrSig_branch = 0;
	if (tree->GetAlias("evt_metMuonJESCorrSig") != 0) {
		evt_metMuonJESCorrSig_branch = tree->GetBranch(tree->GetAlias("evt_metMuonJESCorrSig"));
		if (evt_metMuonJESCorrSig_branch) {evt_metMuonJESCorrSig_branch->SetAddress(&evt_metMuonJESCorrSig_);}
	}
	evt_metNoHF_branch = 0;
	if (tree->GetAlias("evt_metNoHF") != 0) {
		evt_metNoHF_branch = tree->GetBranch(tree->GetAlias("evt_metNoHF"));
		if (evt_metNoHF_branch) {evt_metNoHF_branch->SetAddress(&evt_metNoHF_);}
	}
	evt_metNoHFHO_branch = 0;
	if (tree->GetAlias("evt_metNoHFHO") != 0) {
		evt_metNoHFHO_branch = tree->GetBranch(tree->GetAlias("evt_metNoHFHO"));
		if (evt_metNoHFHO_branch) {evt_metNoHFHO_branch->SetAddress(&evt_metNoHFHO_);}
	}
	evt_metNoHFHOPhi_branch = 0;
	if (tree->GetAlias("evt_metNoHFHOPhi") != 0) {
		evt_metNoHFHOPhi_branch = tree->GetBranch(tree->GetAlias("evt_metNoHFHOPhi"));
		if (evt_metNoHFHOPhi_branch) {evt_metNoHFHOPhi_branch->SetAddress(&evt_metNoHFHOPhi_);}
	}
	evt_metNoHFHOSig_branch = 0;
	if (tree->GetAlias("evt_metNoHFHOSig") != 0) {
		evt_metNoHFHOSig_branch = tree->GetBranch(tree->GetAlias("evt_metNoHFHOSig"));
		if (evt_metNoHFHOSig_branch) {evt_metNoHFHOSig_branch->SetAddress(&evt_metNoHFHOSig_);}
	}
	evt_metNoHFPhi_branch = 0;
	if (tree->GetAlias("evt_metNoHFPhi") != 0) {
		evt_metNoHFPhi_branch = tree->GetBranch(tree->GetAlias("evt_metNoHFPhi"));
		if (evt_metNoHFPhi_branch) {evt_metNoHFPhi_branch->SetAddress(&evt_metNoHFPhi_);}
	}
	evt_metNoHFSig_branch = 0;
	if (tree->GetAlias("evt_metNoHFSig") != 0) {
		evt_metNoHFSig_branch = tree->GetBranch(tree->GetAlias("evt_metNoHFSig"));
		if (evt_metNoHFSig_branch) {evt_metNoHFSig_branch->SetAddress(&evt_metNoHFSig_);}
	}
	evt_metOpt_branch = 0;
	if (tree->GetAlias("evt_metOpt") != 0) {
		evt_metOpt_branch = tree->GetBranch(tree->GetAlias("evt_metOpt"));
		if (evt_metOpt_branch) {evt_metOpt_branch->SetAddress(&evt_metOpt_);}
	}
	evt_metOptHO_branch = 0;
	if (tree->GetAlias("evt_metOptHO") != 0) {
		evt_metOptHO_branch = tree->GetBranch(tree->GetAlias("evt_metOptHO"));
		if (evt_metOptHO_branch) {evt_metOptHO_branch->SetAddress(&evt_metOptHO_);}
	}
	evt_metOptHOPhi_branch = 0;
	if (tree->GetAlias("evt_metOptHOPhi") != 0) {
		evt_metOptHOPhi_branch = tree->GetBranch(tree->GetAlias("evt_metOptHOPhi"));
		if (evt_metOptHOPhi_branch) {evt_metOptHOPhi_branch->SetAddress(&evt_metOptHOPhi_);}
	}
	evt_metOptHOSig_branch = 0;
	if (tree->GetAlias("evt_metOptHOSig") != 0) {
		evt_metOptHOSig_branch = tree->GetBranch(tree->GetAlias("evt_metOptHOSig"));
		if (evt_metOptHOSig_branch) {evt_metOptHOSig_branch->SetAddress(&evt_metOptHOSig_);}
	}
	evt_metOptNoHF_branch = 0;
	if (tree->GetAlias("evt_metOptNoHF") != 0) {
		evt_metOptNoHF_branch = tree->GetBranch(tree->GetAlias("evt_metOptNoHF"));
		if (evt_metOptNoHF_branch) {evt_metOptNoHF_branch->SetAddress(&evt_metOptNoHF_);}
	}
	evt_metOptNoHFHO_branch = 0;
	if (tree->GetAlias("evt_metOptNoHFHO") != 0) {
		evt_metOptNoHFHO_branch = tree->GetBranch(tree->GetAlias("evt_metOptNoHFHO"));
		if (evt_metOptNoHFHO_branch) {evt_metOptNoHFHO_branch->SetAddress(&evt_metOptNoHFHO_);}
	}
	evt_metOptNoHFHOPhi_branch = 0;
	if (tree->GetAlias("evt_metOptNoHFHOPhi") != 0) {
		evt_metOptNoHFHOPhi_branch = tree->GetBranch(tree->GetAlias("evt_metOptNoHFHOPhi"));
		if (evt_metOptNoHFHOPhi_branch) {evt_metOptNoHFHOPhi_branch->SetAddress(&evt_metOptNoHFHOPhi_);}
	}
	evt_metOptNoHFHOSig_branch = 0;
	if (tree->GetAlias("evt_metOptNoHFHOSig") != 0) {
		evt_metOptNoHFHOSig_branch = tree->GetBranch(tree->GetAlias("evt_metOptNoHFHOSig"));
		if (evt_metOptNoHFHOSig_branch) {evt_metOptNoHFHOSig_branch->SetAddress(&evt_metOptNoHFHOSig_);}
	}
	evt_metOptNoHFPhi_branch = 0;
	if (tree->GetAlias("evt_metOptNoHFPhi") != 0) {
		evt_metOptNoHFPhi_branch = tree->GetBranch(tree->GetAlias("evt_metOptNoHFPhi"));
		if (evt_metOptNoHFPhi_branch) {evt_metOptNoHFPhi_branch->SetAddress(&evt_metOptNoHFPhi_);}
	}
	evt_metOptNoHFSig_branch = 0;
	if (tree->GetAlias("evt_metOptNoHFSig") != 0) {
		evt_metOptNoHFSig_branch = tree->GetBranch(tree->GetAlias("evt_metOptNoHFSig"));
		if (evt_metOptNoHFSig_branch) {evt_metOptNoHFSig_branch->SetAddress(&evt_metOptNoHFSig_);}
	}
	evt_metOptPhi_branch = 0;
	if (tree->GetAlias("evt_metOptPhi") != 0) {
		evt_metOptPhi_branch = tree->GetBranch(tree->GetAlias("evt_metOptPhi"));
		if (evt_metOptPhi_branch) {evt_metOptPhi_branch->SetAddress(&evt_metOptPhi_);}
	}
	evt_metOptSig_branch = 0;
	if (tree->GetAlias("evt_metOptSig") != 0) {
		evt_metOptSig_branch = tree->GetBranch(tree->GetAlias("evt_metOptSig"));
		if (evt_metOptSig_branch) {evt_metOptSig_branch->SetAddress(&evt_metOptSig_);}
	}
	evt_metPhi_branch = 0;
	if (tree->GetAlias("evt_metPhi") != 0) {
		evt_metPhi_branch = tree->GetBranch(tree->GetAlias("evt_metPhi"));
		if (evt_metPhi_branch) {evt_metPhi_branch->SetAddress(&evt_metPhi_);}
	}
	evt_metPhi_EtGt3_branch = 0;
	if (tree->GetAlias("evt_metPhi_EtGt3") != 0) {
		evt_metPhi_EtGt3_branch = tree->GetBranch(tree->GetAlias("evt_metPhi_EtGt3"));
		if (evt_metPhi_EtGt3_branch) {evt_metPhi_EtGt3_branch->SetAddress(&evt_metPhi_EtGt3_);}
	}
	evt_metSig_branch = 0;
	if (tree->GetAlias("evt_metSig") != 0) {
		evt_metSig_branch = tree->GetBranch(tree->GetAlias("evt_metSig"));
		if (evt_metSig_branch) {evt_metSig_branch->SetAddress(&evt_metSig_);}
	}
	evt_sumet_branch = 0;
	if (tree->GetAlias("evt_sumet") != 0) {
		evt_sumet_branch = tree->GetBranch(tree->GetAlias("evt_sumet"));
		if (evt_sumet_branch) {evt_sumet_branch->SetAddress(&evt_sumet_);}
	}
	evt_sumet_EtGt3_branch = 0;
	if (tree->GetAlias("evt_sumet_EtGt3") != 0) {
		evt_sumet_EtGt3_branch = tree->GetBranch(tree->GetAlias("evt_sumet_EtGt3"));
		if (evt_sumet_EtGt3_branch) {evt_sumet_EtGt3_branch->SetAddress(&evt_sumet_EtGt3_);}
	}
	evt_sumetHO_branch = 0;
	if (tree->GetAlias("evt_sumetHO") != 0) {
		evt_sumetHO_branch = tree->GetBranch(tree->GetAlias("evt_sumetHO"));
		if (evt_sumetHO_branch) {evt_sumetHO_branch->SetAddress(&evt_sumetHO_);}
	}
	evt_sumetMuonCorr_branch = 0;
	if (tree->GetAlias("evt_sumetMuonCorr") != 0) {
		evt_sumetMuonCorr_branch = tree->GetBranch(tree->GetAlias("evt_sumetMuonCorr"));
		if (evt_sumetMuonCorr_branch) {evt_sumetMuonCorr_branch->SetAddress(&evt_sumetMuonCorr_);}
	}
	evt_sumetMuonJESCorr_branch = 0;
	if (tree->GetAlias("evt_sumetMuonJESCorr") != 0) {
		evt_sumetMuonJESCorr_branch = tree->GetBranch(tree->GetAlias("evt_sumetMuonJESCorr"));
		if (evt_sumetMuonJESCorr_branch) {evt_sumetMuonJESCorr_branch->SetAddress(&evt_sumetMuonJESCorr_);}
	}
	evt_sumetNoHF_branch = 0;
	if (tree->GetAlias("evt_sumetNoHF") != 0) {
		evt_sumetNoHF_branch = tree->GetBranch(tree->GetAlias("evt_sumetNoHF"));
		if (evt_sumetNoHF_branch) {evt_sumetNoHF_branch->SetAddress(&evt_sumetNoHF_);}
	}
	evt_sumetNoHFHO_branch = 0;
	if (tree->GetAlias("evt_sumetNoHFHO") != 0) {
		evt_sumetNoHFHO_branch = tree->GetBranch(tree->GetAlias("evt_sumetNoHFHO"));
		if (evt_sumetNoHFHO_branch) {evt_sumetNoHFHO_branch->SetAddress(&evt_sumetNoHFHO_);}
	}
	evt_sumetOpt_branch = 0;
	if (tree->GetAlias("evt_sumetOpt") != 0) {
		evt_sumetOpt_branch = tree->GetBranch(tree->GetAlias("evt_sumetOpt"));
		if (evt_sumetOpt_branch) {evt_sumetOpt_branch->SetAddress(&evt_sumetOpt_);}
	}
	evt_sumetOptHO_branch = 0;
	if (tree->GetAlias("evt_sumetOptHO") != 0) {
		evt_sumetOptHO_branch = tree->GetBranch(tree->GetAlias("evt_sumetOptHO"));
		if (evt_sumetOptHO_branch) {evt_sumetOptHO_branch->SetAddress(&evt_sumetOptHO_);}
	}
	evt_sumetOptNoHF_branch = 0;
	if (tree->GetAlias("evt_sumetOptNoHF") != 0) {
		evt_sumetOptNoHF_branch = tree->GetBranch(tree->GetAlias("evt_sumetOptNoHF"));
		if (evt_sumetOptNoHF_branch) {evt_sumetOptNoHF_branch->SetAddress(&evt_sumetOptNoHF_);}
	}
	evt_sumetOptNoHFHO_branch = 0;
	if (tree->GetAlias("evt_sumetOptNoHFHO") != 0) {
		evt_sumetOptNoHFHO_branch = tree->GetBranch(tree->GetAlias("evt_sumetOptNoHFHO"));
		if (evt_sumetOptNoHFHO_branch) {evt_sumetOptNoHFHO_branch->SetAddress(&evt_sumetOptNoHFHO_);}
	}
	pfCaloMet_met_branch = 0;
	if (tree->GetAlias("pfCaloMet_met") != 0) {
		pfCaloMet_met_branch = tree->GetBranch(tree->GetAlias("pfCaloMet_met"));
		if (pfCaloMet_met_branch) {pfCaloMet_met_branch->SetAddress(&pfCaloMet_met_);}
	}
	pfCaloMet_metPhi_branch = 0;
	if (tree->GetAlias("pfCaloMet_metPhi") != 0) {
		pfCaloMet_metPhi_branch = tree->GetBranch(tree->GetAlias("pfCaloMet_metPhi"));
		if (pfCaloMet_metPhi_branch) {pfCaloMet_metPhi_branch->SetAddress(&pfCaloMet_metPhi_);}
	}
	pfCaloMet_metPhi_type1cor_branch = 0;
	if (tree->GetAlias("pfCaloMet_metPhi_type1cor") != 0) {
		pfCaloMet_metPhi_type1cor_branch = tree->GetBranch(tree->GetAlias("pfCaloMet_metPhi_type1cor"));
		if (pfCaloMet_metPhi_type1cor_branch) {pfCaloMet_metPhi_type1cor_branch->SetAddress(&pfCaloMet_metPhi_type1cor_);}
	}
	pfCaloMet_metSig_branch = 0;
	if (tree->GetAlias("pfCaloMet_metSig") != 0) {
		pfCaloMet_metSig_branch = tree->GetBranch(tree->GetAlias("pfCaloMet_metSig"));
		if (pfCaloMet_metSig_branch) {pfCaloMet_metSig_branch->SetAddress(&pfCaloMet_metSig_);}
	}
	pfCaloMet_metSignificance_branch = 0;
	if (tree->GetAlias("pfCaloMet_metSignificance") != 0) {
		pfCaloMet_metSignificance_branch = tree->GetBranch(tree->GetAlias("pfCaloMet_metSignificance"));
		if (pfCaloMet_metSignificance_branch) {pfCaloMet_metSignificance_branch->SetAddress(&pfCaloMet_metSignificance_);}
	}
	pfCaloMet_met_type1cor_branch = 0;
	if (tree->GetAlias("pfCaloMet_met_type1cor") != 0) {
		pfCaloMet_met_type1cor_branch = tree->GetBranch(tree->GetAlias("pfCaloMet_met_type1cor"));
		if (pfCaloMet_met_type1cor_branch) {pfCaloMet_met_type1cor_branch->SetAddress(&pfCaloMet_met_type1cor_);}
	}
	pfCaloMet_sumet_branch = 0;
	if (tree->GetAlias("pfCaloMet_sumet") != 0) {
		pfCaloMet_sumet_branch = tree->GetBranch(tree->GetAlias("pfCaloMet_sumet"));
		if (pfCaloMet_sumet_branch) {pfCaloMet_sumet_branch->SetAddress(&pfCaloMet_sumet_);}
	}
	pfChMet_met_branch = 0;
	if (tree->GetAlias("pfChMet_met") != 0) {
		pfChMet_met_branch = tree->GetBranch(tree->GetAlias("pfChMet_met"));
		if (pfChMet_met_branch) {pfChMet_met_branch->SetAddress(&pfChMet_met_);}
	}
	pfChMet_metPhi_branch = 0;
	if (tree->GetAlias("pfChMet_metPhi") != 0) {
		pfChMet_metPhi_branch = tree->GetBranch(tree->GetAlias("pfChMet_metPhi"));
		if (pfChMet_metPhi_branch) {pfChMet_metPhi_branch->SetAddress(&pfChMet_metPhi_);}
	}
	pfChMet_metPhi_type1cor_branch = 0;
	if (tree->GetAlias("pfChMet_metPhi_type1cor") != 0) {
		pfChMet_metPhi_type1cor_branch = tree->GetBranch(tree->GetAlias("pfChMet_metPhi_type1cor"));
		if (pfChMet_metPhi_type1cor_branch) {pfChMet_metPhi_type1cor_branch->SetAddress(&pfChMet_metPhi_type1cor_);}
	}
	pfChMet_metSig_branch = 0;
	if (tree->GetAlias("pfChMet_metSig") != 0) {
		pfChMet_metSig_branch = tree->GetBranch(tree->GetAlias("pfChMet_metSig"));
		if (pfChMet_metSig_branch) {pfChMet_metSig_branch->SetAddress(&pfChMet_metSig_);}
	}
	pfChMet_metSignificance_branch = 0;
	if (tree->GetAlias("pfChMet_metSignificance") != 0) {
		pfChMet_metSignificance_branch = tree->GetBranch(tree->GetAlias("pfChMet_metSignificance"));
		if (pfChMet_metSignificance_branch) {pfChMet_metSignificance_branch->SetAddress(&pfChMet_metSignificance_);}
	}
	pfChMet_met_type1cor_branch = 0;
	if (tree->GetAlias("pfChMet_met_type1cor") != 0) {
		pfChMet_met_type1cor_branch = tree->GetBranch(tree->GetAlias("pfChMet_met_type1cor"));
		if (pfChMet_met_type1cor_branch) {pfChMet_met_type1cor_branch->SetAddress(&pfChMet_met_type1cor_);}
	}
	pfChMet_sumet_branch = 0;
	if (tree->GetAlias("pfChMet_sumet") != 0) {
		pfChMet_sumet_branch = tree->GetBranch(tree->GetAlias("pfChMet_sumet"));
		if (pfChMet_sumet_branch) {pfChMet_sumet_branch->SetAddress(&pfChMet_sumet_);}
	}
	pfcluster_met_branch = 0;
	if (tree->GetAlias("pfcluster_met") != 0) {
		pfcluster_met_branch = tree->GetBranch(tree->GetAlias("pfcluster_met"));
		if (pfcluster_met_branch) {pfcluster_met_branch->SetAddress(&pfcluster_met_);}
	}
	pfcluster_metphi_branch = 0;
	if (tree->GetAlias("pfcluster_metphi") != 0) {
		pfcluster_metphi_branch = tree->GetBranch(tree->GetAlias("pfcluster_metphi"));
		if (pfcluster_metphi_branch) {pfcluster_metphi_branch->SetAddress(&pfcluster_metphi_);}
	}
	pfcluster_sumet_branch = 0;
	if (tree->GetAlias("pfcluster_sumet") != 0) {
		pfcluster_sumet_branch = tree->GetBranch(tree->GetAlias("pfcluster_sumet"));
		if (pfcluster_sumet_branch) {pfcluster_sumet_branch->SetAddress(&pfcluster_sumet_);}
	}
	pfMet_met_branch = 0;
	if (tree->GetAlias("pfMet_met") != 0) {
		pfMet_met_branch = tree->GetBranch(tree->GetAlias("pfMet_met"));
		if (pfMet_met_branch) {pfMet_met_branch->SetAddress(&pfMet_met_);}
	}
	pfMet_metPhi_branch = 0;
	if (tree->GetAlias("pfMet_metPhi") != 0) {
		pfMet_metPhi_branch = tree->GetBranch(tree->GetAlias("pfMet_metPhi"));
		if (pfMet_metPhi_branch) {pfMet_metPhi_branch->SetAddress(&pfMet_metPhi_);}
	}
	pfMet_metPhi_type1cor_branch = 0;
	if (tree->GetAlias("pfMet_metPhi_type1cor") != 0) {
		pfMet_metPhi_type1cor_branch = tree->GetBranch(tree->GetAlias("pfMet_metPhi_type1cor"));
		if (pfMet_metPhi_type1cor_branch) {pfMet_metPhi_type1cor_branch->SetAddress(&pfMet_metPhi_type1cor_);}
	}
	pfMet_metSig_branch = 0;
	if (tree->GetAlias("pfMet_metSig") != 0) {
		pfMet_metSig_branch = tree->GetBranch(tree->GetAlias("pfMet_metSig"));
		if (pfMet_metSig_branch) {pfMet_metSig_branch->SetAddress(&pfMet_metSig_);}
	}
	pfMet_metSignificance_branch = 0;
	if (tree->GetAlias("pfMet_metSignificance") != 0) {
		pfMet_metSignificance_branch = tree->GetBranch(tree->GetAlias("pfMet_metSignificance"));
		if (pfMet_metSignificance_branch) {pfMet_metSignificance_branch->SetAddress(&pfMet_metSignificance_);}
	}
	pfMet_met_type1cor_branch = 0;
	if (tree->GetAlias("pfMet_met_type1cor") != 0) {
		pfMet_met_type1cor_branch = tree->GetBranch(tree->GetAlias("pfMet_met_type1cor"));
		if (pfMet_met_type1cor_branch) {pfMet_met_type1cor_branch->SetAddress(&pfMet_met_type1cor_);}
	}
	pfMet_sumet_branch = 0;
	if (tree->GetAlias("pfMet_sumet") != 0) {
		pfMet_sumet_branch = tree->GetBranch(tree->GetAlias("pfMet_sumet"));
		if (pfMet_sumet_branch) {pfMet_sumet_branch->SetAddress(&pfMet_sumet_);}
	}
	hlt_trigObjs_p4_branch = 0;
	if (tree->GetAlias("hlt_trigObjs_p4") != 0) {
		hlt_trigObjs_p4_branch = tree->GetBranch(tree->GetAlias("hlt_trigObjs_p4"));
		if (hlt_trigObjs_p4_branch) {hlt_trigObjs_p4_branch->SetAddress(&hlt_trigObjs_p4_);}
	}
	calojets_eta_branch = 0;
	if (tree->GetAlias("calojets_eta") != 0) {
		calojets_eta_branch = tree->GetBranch(tree->GetAlias("calojets_eta"));
		if (calojets_eta_branch) {calojets_eta_branch->SetAddress(&calojets_eta_);}
	}
	calojets_phi_branch = 0;
	if (tree->GetAlias("calojets_phi") != 0) {
		calojets_phi_branch = tree->GetBranch(tree->GetAlias("calojets_phi"));
		if (calojets_phi_branch) {calojets_phi_branch->SetAddress(&calojets_phi_);}
	}
	calojets_pt_branch = 0;
	if (tree->GetAlias("calojets_pt") != 0) {
		calojets_pt_branch = tree->GetBranch(tree->GetAlias("calojets_pt"));
		if (calojets_pt_branch) {calojets_pt_branch->SetAddress(&calojets_pt_);}
	}
	twrs_ecalTime_branch = 0;
	if (tree->GetAlias("twrs_ecalTime") != 0) {
		twrs_ecalTime_branch = tree->GetBranch(tree->GetAlias("twrs_ecalTime"));
		if (twrs_ecalTime_branch) {twrs_ecalTime_branch->SetAddress(&twrs_ecalTime_);}
	}
	twrs_emEnergy_branch = 0;
	if (tree->GetAlias("twrs_emEnergy") != 0) {
		twrs_emEnergy_branch = tree->GetBranch(tree->GetAlias("twrs_emEnergy"));
		if (twrs_emEnergy_branch) {twrs_emEnergy_branch->SetAddress(&twrs_emEnergy_);}
	}
	twrs_emEt_branch = 0;
	if (tree->GetAlias("twrs_emEt") != 0) {
		twrs_emEt_branch = tree->GetBranch(tree->GetAlias("twrs_emEt"));
		if (twrs_emEt_branch) {twrs_emEt_branch->SetAddress(&twrs_emEt_);}
	}
	twrs_emEtcorr_branch = 0;
	if (tree->GetAlias("twrs_emEtcorr") != 0) {
		twrs_emEtcorr_branch = tree->GetBranch(tree->GetAlias("twrs_emEtcorr"));
		if (twrs_emEtcorr_branch) {twrs_emEtcorr_branch->SetAddress(&twrs_emEtcorr_);}
	}
	twrs_eta_branch = 0;
	if (tree->GetAlias("twrs_eta") != 0) {
		twrs_eta_branch = tree->GetBranch(tree->GetAlias("twrs_eta"));
		if (twrs_eta_branch) {twrs_eta_branch->SetAddress(&twrs_eta_);}
	}
	twrs_etacorr_branch = 0;
	if (tree->GetAlias("twrs_etacorr") != 0) {
		twrs_etacorr_branch = tree->GetBranch(tree->GetAlias("twrs_etacorr"));
		if (twrs_etacorr_branch) {twrs_etacorr_branch->SetAddress(&twrs_etacorr_);}
	}
	twrs_etcorr_branch = 0;
	if (tree->GetAlias("twrs_etcorr") != 0) {
		twrs_etcorr_branch = tree->GetBranch(tree->GetAlias("twrs_etcorr"));
		if (twrs_etcorr_branch) {twrs_etcorr_branch->SetAddress(&twrs_etcorr_);}
	}
	twrs_hadEnergy_branch = 0;
	if (tree->GetAlias("twrs_hadEnergy") != 0) {
		twrs_hadEnergy_branch = tree->GetBranch(tree->GetAlias("twrs_hadEnergy"));
		if (twrs_hadEnergy_branch) {twrs_hadEnergy_branch->SetAddress(&twrs_hadEnergy_);}
	}
	twrs_hadEt_branch = 0;
	if (tree->GetAlias("twrs_hadEt") != 0) {
		twrs_hadEt_branch = tree->GetBranch(tree->GetAlias("twrs_hadEt"));
		if (twrs_hadEt_branch) {twrs_hadEt_branch->SetAddress(&twrs_hadEt_);}
	}
	twrs_hadEtcorr_branch = 0;
	if (tree->GetAlias("twrs_hadEtcorr") != 0) {
		twrs_hadEtcorr_branch = tree->GetBranch(tree->GetAlias("twrs_hadEtcorr"));
		if (twrs_hadEtcorr_branch) {twrs_hadEtcorr_branch->SetAddress(&twrs_hadEtcorr_);}
	}
	twrs_hcalTime_branch = 0;
	if (tree->GetAlias("twrs_hcalTime") != 0) {
		twrs_hcalTime_branch = tree->GetBranch(tree->GetAlias("twrs_hcalTime"));
		if (twrs_hcalTime_branch) {twrs_hcalTime_branch->SetAddress(&twrs_hcalTime_);}
	}
	twrs_outerEnergy_branch = 0;
	if (tree->GetAlias("twrs_outerEnergy") != 0) {
		twrs_outerEnergy_branch = tree->GetBranch(tree->GetAlias("twrs_outerEnergy"));
		if (twrs_outerEnergy_branch) {twrs_outerEnergy_branch->SetAddress(&twrs_outerEnergy_);}
	}
	twrs_outerEt_branch = 0;
	if (tree->GetAlias("twrs_outerEt") != 0) {
		twrs_outerEt_branch = tree->GetBranch(tree->GetAlias("twrs_outerEt"));
		if (twrs_outerEt_branch) {twrs_outerEt_branch->SetAddress(&twrs_outerEt_);}
	}
	twrs_outerEtcorr_branch = 0;
	if (tree->GetAlias("twrs_outerEtcorr") != 0) {
		twrs_outerEtcorr_branch = tree->GetBranch(tree->GetAlias("twrs_outerEtcorr"));
		if (twrs_outerEtcorr_branch) {twrs_outerEtcorr_branch->SetAddress(&twrs_outerEtcorr_);}
	}
	twrs_pcorr_branch = 0;
	if (tree->GetAlias("twrs_pcorr") != 0) {
		twrs_pcorr_branch = tree->GetBranch(tree->GetAlias("twrs_pcorr"));
		if (twrs_pcorr_branch) {twrs_pcorr_branch->SetAddress(&twrs_pcorr_);}
	}
	twrs_phi_branch = 0;
	if (tree->GetAlias("twrs_phi") != 0) {
		twrs_phi_branch = tree->GetBranch(tree->GetAlias("twrs_phi"));
		if (twrs_phi_branch) {twrs_phi_branch->SetAddress(&twrs_phi_);}
	}
	twrs_phicorr_branch = 0;
	if (tree->GetAlias("twrs_phicorr") != 0) {
		twrs_phicorr_branch = tree->GetBranch(tree->GetAlias("twrs_phicorr"));
		if (twrs_phicorr_branch) {twrs_phicorr_branch->SetAddress(&twrs_phicorr_);}
	}
	twrs_spikeEt_branch = 0;
	if (tree->GetAlias("twrs_spikeEt") != 0) {
		twrs_spikeEt_branch = tree->GetBranch(tree->GetAlias("twrs_spikeEt"));
		if (twrs_spikeEt_branch) {twrs_spikeEt_branch->SetAddress(&twrs_spikeEt_);}
	}
	twrs_spikeR4_branch = 0;
	if (tree->GetAlias("twrs_spikeR4") != 0) {
		twrs_spikeR4_branch = tree->GetBranch(tree->GetAlias("twrs_spikeR4"));
		if (twrs_spikeR4_branch) {twrs_spikeR4_branch->SetAddress(&twrs_spikeR4_);}
	}
	evt_ecalmet_etaslice_branch = 0;
	if (tree->GetAlias("evt_ecalmet_etaslice") != 0) {
		evt_ecalmet_etaslice_branch = tree->GetBranch(tree->GetAlias("evt_ecalmet_etaslice"));
		if (evt_ecalmet_etaslice_branch) {evt_ecalmet_etaslice_branch->SetAddress(&evt_ecalmet_etaslice_);}
	}
	evt_ecalmet_etaslicePhi_branch = 0;
	if (tree->GetAlias("evt_ecalmet_etaslicePhi") != 0) {
		evt_ecalmet_etaslicePhi_branch = tree->GetBranch(tree->GetAlias("evt_ecalmet_etaslicePhi"));
		if (evt_ecalmet_etaslicePhi_branch) {evt_ecalmet_etaslicePhi_branch->SetAddress(&evt_ecalmet_etaslicePhi_);}
	}
	evt_hcalmet_etaslice_branch = 0;
	if (tree->GetAlias("evt_hcalmet_etaslice") != 0) {
		evt_hcalmet_etaslice_branch = tree->GetBranch(tree->GetAlias("evt_hcalmet_etaslice"));
		if (evt_hcalmet_etaslice_branch) {evt_hcalmet_etaslice_branch->SetAddress(&evt_hcalmet_etaslice_);}
	}
	evt_hcalmet_etaslicePhi_branch = 0;
	if (tree->GetAlias("evt_hcalmet_etaslicePhi") != 0) {
		evt_hcalmet_etaslicePhi_branch = tree->GetBranch(tree->GetAlias("evt_hcalmet_etaslicePhi"));
		if (evt_hcalmet_etaslicePhi_branch) {evt_hcalmet_etaslicePhi_branch->SetAddress(&evt_hcalmet_etaslicePhi_);}
	}
	evt_towermet_etaslice_branch = 0;
	if (tree->GetAlias("evt_towermet_etaslice") != 0) {
		evt_towermet_etaslice_branch = tree->GetBranch(tree->GetAlias("evt_towermet_etaslice"));
		if (evt_towermet_etaslice_branch) {evt_towermet_etaslice_branch->SetAddress(&evt_towermet_etaslice_);}
	}
	evt_towermet_etaslicePhi_branch = 0;
	if (tree->GetAlias("evt_towermet_etaslicePhi") != 0) {
		evt_towermet_etaslicePhi_branch = tree->GetBranch(tree->GetAlias("evt_towermet_etaslicePhi"));
		if (evt_towermet_etaslicePhi_branch) {evt_towermet_etaslicePhi_branch->SetAddress(&evt_towermet_etaslicePhi_);}
	}
	mus_met_deltax_branch = 0;
	if (tree->GetAlias("mus_met_deltax") != 0) {
		mus_met_deltax_branch = tree->GetBranch(tree->GetAlias("mus_met_deltax"));
		if (mus_met_deltax_branch) {mus_met_deltax_branch->SetAddress(&mus_met_deltax_);}
	}
	mus_met_deltay_branch = 0;
	if (tree->GetAlias("mus_met_deltay") != 0) {
		mus_met_deltay_branch = tree->GetBranch(tree->GetAlias("mus_met_deltay"));
		if (mus_met_deltay_branch) {mus_met_deltay_branch->SetAddress(&mus_met_deltay_);}
	}
	pfcands_mass_branch = 0;
	if (tree->GetAlias("pfcands_mass") != 0) {
		pfcands_mass_branch = tree->GetBranch(tree->GetAlias("pfcands_mass"));
		if (pfcands_mass_branch) {pfcands_mass_branch->SetAddress(&pfcands_mass_);}
	}
	pfcluster_energy_branch = 0;
	if (tree->GetAlias("pfcluster_energy") != 0) {
		pfcluster_energy_branch = tree->GetBranch(tree->GetAlias("pfcluster_energy"));
		if (pfcluster_energy_branch) {pfcluster_energy_branch->SetAddress(&pfcluster_energy_);}
	}
	pfcluster_et_branch = 0;
	if (tree->GetAlias("pfcluster_et") != 0) {
		pfcluster_et_branch = tree->GetBranch(tree->GetAlias("pfcluster_et"));
		if (pfcluster_et_branch) {pfcluster_et_branch->SetAddress(&pfcluster_et_);}
	}
	pfcluster_eta_branch = 0;
	if (tree->GetAlias("pfcluster_eta") != 0) {
		pfcluster_eta_branch = tree->GetBranch(tree->GetAlias("pfcluster_eta"));
		if (pfcluster_eta_branch) {pfcluster_eta_branch->SetAddress(&pfcluster_eta_);}
	}
	pfcluster_phi_branch = 0;
	if (tree->GetAlias("pfcluster_phi") != 0) {
		pfcluster_phi_branch = tree->GetBranch(tree->GetAlias("pfcluster_phi"));
		if (pfcluster_phi_branch) {pfcluster_phi_branch->SetAddress(&pfcluster_phi_);}
	}
	pfjets_area_branch = 0;
	if (tree->GetAlias("pfjets_area") != 0) {
		pfjets_area_branch = tree->GetBranch(tree->GetAlias("pfjets_area"));
		if (pfjets_area_branch) {pfjets_area_branch->SetAddress(&pfjets_area_);}
	}
	pfjets_chargedEmE_branch = 0;
	if (tree->GetAlias("pfjets_chargedEmE") != 0) {
		pfjets_chargedEmE_branch = tree->GetBranch(tree->GetAlias("pfjets_chargedEmE"));
		if (pfjets_chargedEmE_branch) {pfjets_chargedEmE_branch->SetAddress(&pfjets_chargedEmE_);}
	}
	pfjets_chargedHadronE_branch = 0;
	if (tree->GetAlias("pfjets_chargedHadronE") != 0) {
		pfjets_chargedHadronE_branch = tree->GetBranch(tree->GetAlias("pfjets_chargedHadronE"));
		if (pfjets_chargedHadronE_branch) {pfjets_chargedHadronE_branch->SetAddress(&pfjets_chargedHadronE_);}
	}
	pfjets_electronE_branch = 0;
	if (tree->GetAlias("pfjets_electronE") != 0) {
		pfjets_electronE_branch = tree->GetBranch(tree->GetAlias("pfjets_electronE"));
		if (pfjets_electronE_branch) {pfjets_electronE_branch->SetAddress(&pfjets_electronE_);}
	}
	pfjets_hfEmE_branch = 0;
	if (tree->GetAlias("pfjets_hfEmE") != 0) {
		pfjets_hfEmE_branch = tree->GetBranch(tree->GetAlias("pfjets_hfEmE"));
		if (pfjets_hfEmE_branch) {pfjets_hfEmE_branch->SetAddress(&pfjets_hfEmE_);}
	}
	pfjets_hfHadronE_branch = 0;
	if (tree->GetAlias("pfjets_hfHadronE") != 0) {
		pfjets_hfHadronE_branch = tree->GetBranch(tree->GetAlias("pfjets_hfHadronE"));
		if (pfjets_hfHadronE_branch) {pfjets_hfHadronE_branch->SetAddress(&pfjets_hfHadronE_);}
	}
	pfjets_mass_branch = 0;
	if (tree->GetAlias("pfjets_mass") != 0) {
		pfjets_mass_branch = tree->GetBranch(tree->GetAlias("pfjets_mass"));
		if (pfjets_mass_branch) {pfjets_mass_branch->SetAddress(&pfjets_mass_);}
	}
	pfjets_muonE_branch = 0;
	if (tree->GetAlias("pfjets_muonE") != 0) {
		pfjets_muonE_branch = tree->GetBranch(tree->GetAlias("pfjets_muonE"));
		if (pfjets_muonE_branch) {pfjets_muonE_branch->SetAddress(&pfjets_muonE_);}
	}
	pfjets_neutralEmE_branch = 0;
	if (tree->GetAlias("pfjets_neutralEmE") != 0) {
		pfjets_neutralEmE_branch = tree->GetBranch(tree->GetAlias("pfjets_neutralEmE"));
		if (pfjets_neutralEmE_branch) {pfjets_neutralEmE_branch->SetAddress(&pfjets_neutralEmE_);}
	}
	pfjets_neutralHadronE_branch = 0;
	if (tree->GetAlias("pfjets_neutralHadronE") != 0) {
		pfjets_neutralHadronE_branch = tree->GetBranch(tree->GetAlias("pfjets_neutralHadronE"));
		if (pfjets_neutralHadronE_branch) {pfjets_neutralHadronE_branch->SetAddress(&pfjets_neutralHadronE_);}
	}
	pfjets_photonE_branch = 0;
	if (tree->GetAlias("pfjets_photonE") != 0) {
		pfjets_photonE_branch = tree->GetBranch(tree->GetAlias("pfjets_photonE"));
		if (pfjets_photonE_branch) {pfjets_photonE_branch->SetAddress(&pfjets_photonE_);}
	}
	pfjets_undoJEC_branch = 0;
	if (tree->GetAlias("pfjets_undoJEC") != 0) {
		pfjets_undoJEC_branch = tree->GetBranch(tree->GetAlias("pfjets_undoJEC"));
		if (pfjets_undoJEC_branch) {pfjets_undoJEC_branch->SetAddress(&pfjets_undoJEC_);}
	}
	pfjets_bDiscriminators_branch = 0;
	if (tree->GetAlias("pfjets_bDiscriminators") != 0) {
		pfjets_bDiscriminators_branch = tree->GetBranch(tree->GetAlias("pfjets_bDiscriminators"));
		if (pfjets_bDiscriminators_branch) {pfjets_bDiscriminators_branch->SetAddress(&pfjets_bDiscriminators_);}
	}
	evt_bunchCrossing_branch = 0;
	if (tree->GetAlias("evt_bunchCrossing") != 0) {
		evt_bunchCrossing_branch = tree->GetBranch(tree->GetAlias("evt_bunchCrossing"));
		if (evt_bunchCrossing_branch) {evt_bunchCrossing_branch->SetAddress(&evt_bunchCrossing_);}
	}
	evt_experimentType_branch = 0;
	if (tree->GetAlias("evt_experimentType") != 0) {
		evt_experimentType_branch = tree->GetBranch(tree->GetAlias("evt_experimentType"));
		if (evt_experimentType_branch) {evt_experimentType_branch->SetAddress(&evt_experimentType_);}
	}
	evt_isRealData_branch = 0;
	if (tree->GetAlias("evt_isRealData") != 0) {
		evt_isRealData_branch = tree->GetBranch(tree->GetAlias("evt_isRealData"));
		if (evt_isRealData_branch) {evt_isRealData_branch->SetAddress(&evt_isRealData_);}
	}
	evt_ntracks_branch = 0;
	if (tree->GetAlias("evt_ntracks") != 0) {
		evt_ntracks_branch = tree->GetBranch(tree->GetAlias("evt_ntracks"));
		if (evt_ntracks_branch) {evt_ntracks_branch->SetAddress(&evt_ntracks_);}
	}
	evt_orbitNumber_branch = 0;
	if (tree->GetAlias("evt_orbitNumber") != 0) {
		evt_orbitNumber_branch = tree->GetBranch(tree->GetAlias("evt_orbitNumber"));
		if (evt_orbitNumber_branch) {evt_orbitNumber_branch->SetAddress(&evt_orbitNumber_);}
	}
	evt_storeNumber_branch = 0;
	if (tree->GetAlias("evt_storeNumber") != 0) {
		evt_storeNumber_branch = tree->GetBranch(tree->GetAlias("evt_storeNumber"));
		if (evt_storeNumber_branch) {evt_storeNumber_branch->SetAddress(&evt_storeNumber_);}
	}
	hcalnoise_GetRecHitCount_branch = 0;
	if (tree->GetAlias("hcalnoise_GetRecHitCount") != 0) {
		hcalnoise_GetRecHitCount_branch = tree->GetBranch(tree->GetAlias("hcalnoise_GetRecHitCount"));
		if (hcalnoise_GetRecHitCount_branch) {hcalnoise_GetRecHitCount_branch->SetAddress(&hcalnoise_GetRecHitCount_);}
	}
	hcalnoise_GetRecHitCount15_branch = 0;
	if (tree->GetAlias("hcalnoise_GetRecHitCount15") != 0) {
		hcalnoise_GetRecHitCount15_branch = tree->GetBranch(tree->GetAlias("hcalnoise_GetRecHitCount15"));
		if (hcalnoise_GetRecHitCount15_branch) {hcalnoise_GetRecHitCount15_branch->SetAddress(&hcalnoise_GetRecHitCount15_);}
	}
	hcalnoise_hbheIsoNoiseFilter_branch = 0;
	if (tree->GetAlias("hcalnoise_hbheIsoNoiseFilter") != 0) {
		hcalnoise_hbheIsoNoiseFilter_branch = tree->GetBranch(tree->GetAlias("hcalnoise_hbheIsoNoiseFilter"));
		if (hcalnoise_hbheIsoNoiseFilter_branch) {hcalnoise_hbheIsoNoiseFilter_branch->SetAddress(&hcalnoise_hbheIsoNoiseFilter_);}
	}
	hcalnoise_maxHPDHits_branch = 0;
	if (tree->GetAlias("hcalnoise_maxHPDHits") != 0) {
		hcalnoise_maxHPDHits_branch = tree->GetBranch(tree->GetAlias("hcalnoise_maxHPDHits"));
		if (hcalnoise_maxHPDHits_branch) {hcalnoise_maxHPDHits_branch->SetAddress(&hcalnoise_maxHPDHits_);}
	}
	hcalnoise_maxHPDNoOtherHits_branch = 0;
	if (tree->GetAlias("hcalnoise_maxHPDNoOtherHits") != 0) {
		hcalnoise_maxHPDNoOtherHits_branch = tree->GetBranch(tree->GetAlias("hcalnoise_maxHPDNoOtherHits"));
		if (hcalnoise_maxHPDNoOtherHits_branch) {hcalnoise_maxHPDNoOtherHits_branch->SetAddress(&hcalnoise_maxHPDNoOtherHits_);}
	}
	hcalnoise_maxRBXHits_branch = 0;
	if (tree->GetAlias("hcalnoise_maxRBXHits") != 0) {
		hcalnoise_maxRBXHits_branch = tree->GetBranch(tree->GetAlias("hcalnoise_maxRBXHits"));
		if (hcalnoise_maxRBXHits_branch) {hcalnoise_maxRBXHits_branch->SetAddress(&hcalnoise_maxRBXHits_);}
	}
	hcalnoise_maxZeros_branch = 0;
	if (tree->GetAlias("hcalnoise_maxZeros") != 0) {
		hcalnoise_maxZeros_branch = tree->GetBranch(tree->GetAlias("hcalnoise_maxZeros"));
		if (hcalnoise_maxZeros_branch) {hcalnoise_maxZeros_branch->SetAddress(&hcalnoise_maxZeros_);}
	}
	hcalnoise_noiseFilterStatus_branch = 0;
	if (tree->GetAlias("hcalnoise_noiseFilterStatus") != 0) {
		hcalnoise_noiseFilterStatus_branch = tree->GetBranch(tree->GetAlias("hcalnoise_noiseFilterStatus"));
		if (hcalnoise_noiseFilterStatus_branch) {hcalnoise_noiseFilterStatus_branch->SetAddress(&hcalnoise_noiseFilterStatus_);}
	}
	hcalnoise_noiseType_branch = 0;
	if (tree->GetAlias("hcalnoise_noiseType") != 0) {
		hcalnoise_noiseType_branch = tree->GetBranch(tree->GetAlias("hcalnoise_noiseType"));
		if (hcalnoise_noiseType_branch) {hcalnoise_noiseType_branch->SetAddress(&hcalnoise_noiseType_);}
	}
	hcalnoise_num10GeVHits_branch = 0;
	if (tree->GetAlias("hcalnoise_num10GeVHits") != 0) {
		hcalnoise_num10GeVHits_branch = tree->GetBranch(tree->GetAlias("hcalnoise_num10GeVHits"));
		if (hcalnoise_num10GeVHits_branch) {hcalnoise_num10GeVHits_branch->SetAddress(&hcalnoise_num10GeVHits_);}
	}
	hcalnoise_num25GeVHits_branch = 0;
	if (tree->GetAlias("hcalnoise_num25GeVHits") != 0) {
		hcalnoise_num25GeVHits_branch = tree->GetBranch(tree->GetAlias("hcalnoise_num25GeVHits"));
		if (hcalnoise_num25GeVHits_branch) {hcalnoise_num25GeVHits_branch->SetAddress(&hcalnoise_num25GeVHits_);}
	}
	hcalnoise_numFlatNoiseChannels_branch = 0;
	if (tree->GetAlias("hcalnoise_numFlatNoiseChannels") != 0) {
		hcalnoise_numFlatNoiseChannels_branch = tree->GetBranch(tree->GetAlias("hcalnoise_numFlatNoiseChannels"));
		if (hcalnoise_numFlatNoiseChannels_branch) {hcalnoise_numFlatNoiseChannels_branch->SetAddress(&hcalnoise_numFlatNoiseChannels_);}
	}
	hcalnoise_numIsolatedNoiseChannels_branch = 0;
	if (tree->GetAlias("hcalnoise_numIsolatedNoiseChannels") != 0) {
		hcalnoise_numIsolatedNoiseChannels_branch = tree->GetBranch(tree->GetAlias("hcalnoise_numIsolatedNoiseChannels"));
		if (hcalnoise_numIsolatedNoiseChannels_branch) {hcalnoise_numIsolatedNoiseChannels_branch->SetAddress(&hcalnoise_numIsolatedNoiseChannels_);}
	}
	hcalnoise_numProblematicRBXs_branch = 0;
	if (tree->GetAlias("hcalnoise_numProblematicRBXs") != 0) {
		hcalnoise_numProblematicRBXs_branch = tree->GetBranch(tree->GetAlias("hcalnoise_numProblematicRBXs"));
		if (hcalnoise_numProblematicRBXs_branch) {hcalnoise_numProblematicRBXs_branch->SetAddress(&hcalnoise_numProblematicRBXs_);}
	}
	hcalnoise_numSpikeNoiseChannels_branch = 0;
	if (tree->GetAlias("hcalnoise_numSpikeNoiseChannels") != 0) {
		hcalnoise_numSpikeNoiseChannels_branch = tree->GetBranch(tree->GetAlias("hcalnoise_numSpikeNoiseChannels"));
		if (hcalnoise_numSpikeNoiseChannels_branch) {hcalnoise_numSpikeNoiseChannels_branch->SetAddress(&hcalnoise_numSpikeNoiseChannels_);}
	}
	hcalnoise_numTS4TS5NoiseChannels_branch = 0;
	if (tree->GetAlias("hcalnoise_numTS4TS5NoiseChannels") != 0) {
		hcalnoise_numTS4TS5NoiseChannels_branch = tree->GetBranch(tree->GetAlias("hcalnoise_numTS4TS5NoiseChannels"));
		if (hcalnoise_numTS4TS5NoiseChannels_branch) {hcalnoise_numTS4TS5NoiseChannels_branch->SetAddress(&hcalnoise_numTS4TS5NoiseChannels_);}
	}
	hcalnoise_numTriangleNoiseChannels_branch = 0;
	if (tree->GetAlias("hcalnoise_numTriangleNoiseChannels") != 0) {
		hcalnoise_numTriangleNoiseChannels_branch = tree->GetBranch(tree->GetAlias("hcalnoise_numTriangleNoiseChannels"));
		if (hcalnoise_numTriangleNoiseChannels_branch) {hcalnoise_numTriangleNoiseChannels_branch->SetAddress(&hcalnoise_numTriangleNoiseChannels_);}
	}
	hcalnoise_passHighLevelNoiseFilter_branch = 0;
	if (tree->GetAlias("hcalnoise_passHighLevelNoiseFilter") != 0) {
		hcalnoise_passHighLevelNoiseFilter_branch = tree->GetBranch(tree->GetAlias("hcalnoise_passHighLevelNoiseFilter"));
		if (hcalnoise_passHighLevelNoiseFilter_branch) {hcalnoise_passHighLevelNoiseFilter_branch->SetAddress(&hcalnoise_passHighLevelNoiseFilter_);}
	}
	hcalnoise_passLooseNoiseFilter_branch = 0;
	if (tree->GetAlias("hcalnoise_passLooseNoiseFilter") != 0) {
		hcalnoise_passLooseNoiseFilter_branch = tree->GetBranch(tree->GetAlias("hcalnoise_passLooseNoiseFilter"));
		if (hcalnoise_passLooseNoiseFilter_branch) {hcalnoise_passLooseNoiseFilter_branch->SetAddress(&hcalnoise_passLooseNoiseFilter_);}
	}
	hcalnoise_passTightNoiseFilter_branch = 0;
	if (tree->GetAlias("hcalnoise_passTightNoiseFilter") != 0) {
		hcalnoise_passTightNoiseFilter_branch = tree->GetBranch(tree->GetAlias("hcalnoise_passTightNoiseFilter"));
		if (hcalnoise_passTightNoiseFilter_branch) {hcalnoise_passTightNoiseFilter_branch->SetAddress(&hcalnoise_passTightNoiseFilter_);}
	}
	twrs_ieta_branch = 0;
	if (tree->GetAlias("twrs_ieta") != 0) {
		twrs_ieta_branch = tree->GetBranch(tree->GetAlias("twrs_ieta"));
		if (twrs_ieta_branch) {twrs_ieta_branch->SetAddress(&twrs_ieta_);}
	}
	twrs_iphi_branch = 0;
	if (tree->GetAlias("twrs_iphi") != 0) {
		twrs_iphi_branch = tree->GetBranch(tree->GetAlias("twrs_iphi"));
		if (twrs_iphi_branch) {twrs_iphi_branch->SetAddress(&twrs_iphi_);}
	}
	twrs_numCrystals_branch = 0;
	if (tree->GetAlias("twrs_numCrystals") != 0) {
		twrs_numCrystals_branch = tree->GetBranch(tree->GetAlias("twrs_numCrystals"));
		if (twrs_numCrystals_branch) {twrs_numCrystals_branch->SetAddress(&twrs_numCrystals_);}
	}
	mus_met_flag_branch = 0;
	if (tree->GetAlias("mus_met_flag") != 0) {
		mus_met_flag_branch = tree->GetBranch(tree->GetAlias("mus_met_flag"));
		if (mus_met_flag_branch) {mus_met_flag_branch->SetAddress(&mus_met_flag_);}
	}
	pfcands_charge_branch = 0;
	if (tree->GetAlias("pfcands_charge") != 0) {
		pfcands_charge_branch = tree->GetBranch(tree->GetAlias("pfcands_charge"));
		if (pfcands_charge_branch) {pfcands_charge_branch->SetAddress(&pfcands_charge_);}
	}
	pfcands_particleId_branch = 0;
	if (tree->GetAlias("pfcands_particleId") != 0) {
		pfcands_particleId_branch = tree->GetBranch(tree->GetAlias("pfcands_particleId"));
		if (pfcands_particleId_branch) {pfcands_particleId_branch->SetAddress(&pfcands_particleId_);}
	}
	pfcluster_layer_branch = 0;
	if (tree->GetAlias("pfcluster_layer") != 0) {
		pfcluster_layer_branch = tree->GetBranch(tree->GetAlias("pfcluster_layer"));
		if (pfcluster_layer_branch) {pfcluster_layer_branch->SetAddress(&pfcluster_layer_);}
	}
	pfjets_chargedHadronMultiplicity_branch = 0;
	if (tree->GetAlias("pfjets_chargedHadronMultiplicity") != 0) {
		pfjets_chargedHadronMultiplicity_branch = tree->GetBranch(tree->GetAlias("pfjets_chargedHadronMultiplicity"));
		if (pfjets_chargedHadronMultiplicity_branch) {pfjets_chargedHadronMultiplicity_branch->SetAddress(&pfjets_chargedHadronMultiplicity_);}
	}
	pfjets_chargedMultiplicity_branch = 0;
	if (tree->GetAlias("pfjets_chargedMultiplicity") != 0) {
		pfjets_chargedMultiplicity_branch = tree->GetBranch(tree->GetAlias("pfjets_chargedMultiplicity"));
		if (pfjets_chargedMultiplicity_branch) {pfjets_chargedMultiplicity_branch->SetAddress(&pfjets_chargedMultiplicity_);}
	}
	pfjets_electronMultiplicity_branch = 0;
	if (tree->GetAlias("pfjets_electronMultiplicity") != 0) {
		pfjets_electronMultiplicity_branch = tree->GetBranch(tree->GetAlias("pfjets_electronMultiplicity"));
		if (pfjets_electronMultiplicity_branch) {pfjets_electronMultiplicity_branch->SetAddress(&pfjets_electronMultiplicity_);}
	}
	pfjets_muonMultiplicity_branch = 0;
	if (tree->GetAlias("pfjets_muonMultiplicity") != 0) {
		pfjets_muonMultiplicity_branch = tree->GetBranch(tree->GetAlias("pfjets_muonMultiplicity"));
		if (pfjets_muonMultiplicity_branch) {pfjets_muonMultiplicity_branch->SetAddress(&pfjets_muonMultiplicity_);}
	}
	pfjets_neutralHadronMultiplicity_branch = 0;
	if (tree->GetAlias("pfjets_neutralHadronMultiplicity") != 0) {
		pfjets_neutralHadronMultiplicity_branch = tree->GetBranch(tree->GetAlias("pfjets_neutralHadronMultiplicity"));
		if (pfjets_neutralHadronMultiplicity_branch) {pfjets_neutralHadronMultiplicity_branch->SetAddress(&pfjets_neutralHadronMultiplicity_);}
	}
	pfjets_neutralMultiplicity_branch = 0;
	if (tree->GetAlias("pfjets_neutralMultiplicity") != 0) {
		pfjets_neutralMultiplicity_branch = tree->GetBranch(tree->GetAlias("pfjets_neutralMultiplicity"));
		if (pfjets_neutralMultiplicity_branch) {pfjets_neutralMultiplicity_branch->SetAddress(&pfjets_neutralMultiplicity_);}
	}
	pfjets_photonMultiplicity_branch = 0;
	if (tree->GetAlias("pfjets_photonMultiplicity") != 0) {
		pfjets_photonMultiplicity_branch = tree->GetBranch(tree->GetAlias("pfjets_photonMultiplicity"));
		if (pfjets_photonMultiplicity_branch) {pfjets_photonMultiplicity_branch->SetAddress(&pfjets_photonMultiplicity_);}
	}
	hlt_trigObjs_id_branch = 0;
	if (tree->GetAlias("hlt_trigObjs_id") != 0) {
		hlt_trigObjs_id_branch = tree->GetBranch(tree->GetAlias("hlt_trigObjs_id"));
		if (hlt_trigObjs_id_branch) {hlt_trigObjs_id_branch->SetAddress(&hlt_trigObjs_id_);}
	}
	pfjets_pfcandIndicies_branch = 0;
	if (tree->GetAlias("pfjets_pfcandIndicies") != 0) {
		pfjets_pfcandIndicies_branch = tree->GetBranch(tree->GetAlias("pfjets_pfcandIndicies"));
		if (pfjets_pfcandIndicies_branch) {pfjets_pfcandIndicies_branch->SetAddress(&pfjets_pfcandIndicies_);}
	}
	evt_ntwrs_branch = 0;
	if (tree->GetAlias("evt_ntwrs") != 0) {
		evt_ntwrs_branch = tree->GetBranch(tree->GetAlias("evt_ntwrs"));
		if (evt_ntwrs_branch) {evt_ntwrs_branch->SetAddress(&evt_ntwrs_);}
	}
	evt_detectorStatus_branch = 0;
	if (tree->GetAlias("evt_detectorStatus") != 0) {
		evt_detectorStatus_branch = tree->GetBranch(tree->GetAlias("evt_detectorStatus"));
		if (evt_detectorStatus_branch) {evt_detectorStatus_branch->SetAddress(&evt_detectorStatus_);}
	}
	evt_event_branch = 0;
	if (tree->GetAlias("evt_event") != 0) {
		evt_event_branch = tree->GetBranch(tree->GetAlias("evt_event"));
		if (evt_event_branch) {evt_event_branch->SetAddress(&evt_event_);}
	}
	evt_lumiBlock_branch = 0;
	if (tree->GetAlias("evt_lumiBlock") != 0) {
		evt_lumiBlock_branch = tree->GetBranch(tree->GetAlias("evt_lumiBlock"));
		if (evt_lumiBlock_branch) {evt_lumiBlock_branch->SetAddress(&evt_lumiBlock_);}
	}
	evt_run_branch = 0;
	if (tree->GetAlias("evt_run") != 0) {
		evt_run_branch = tree->GetBranch(tree->GetAlias("evt_run"));
		if (evt_run_branch) {evt_run_branch->SetAddress(&evt_run_);}
	}
	twrs_detid_branch = 0;
	if (tree->GetAlias("twrs_detid") != 0) {
		twrs_detid_branch = tree->GetBranch(tree->GetAlias("twrs_detid"));
		if (twrs_detid_branch) {twrs_detid_branch->SetAddress(&twrs_detid_);}
	}
	twrs_numBadEcalCells_branch = 0;
	if (tree->GetAlias("twrs_numBadEcalCells") != 0) {
		twrs_numBadEcalCells_branch = tree->GetBranch(tree->GetAlias("twrs_numBadEcalCells"));
		if (twrs_numBadEcalCells_branch) {twrs_numBadEcalCells_branch->SetAddress(&twrs_numBadEcalCells_);}
	}
	twrs_numBadHcalCells_branch = 0;
	if (tree->GetAlias("twrs_numBadHcalCells") != 0) {
		twrs_numBadHcalCells_branch = tree->GetBranch(tree->GetAlias("twrs_numBadHcalCells"));
		if (twrs_numBadHcalCells_branch) {twrs_numBadHcalCells_branch->SetAddress(&twrs_numBadHcalCells_);}
	}
	twrs_numProblematicEcalCells_branch = 0;
	if (tree->GetAlias("twrs_numProblematicEcalCells") != 0) {
		twrs_numProblematicEcalCells_branch = tree->GetBranch(tree->GetAlias("twrs_numProblematicEcalCells"));
		if (twrs_numProblematicEcalCells_branch) {twrs_numProblematicEcalCells_branch->SetAddress(&twrs_numProblematicEcalCells_);}
	}
	twrs_numProblematicHcalCells_branch = 0;
	if (tree->GetAlias("twrs_numProblematicHcalCells") != 0) {
		twrs_numProblematicHcalCells_branch = tree->GetBranch(tree->GetAlias("twrs_numProblematicHcalCells"));
		if (twrs_numProblematicHcalCells_branch) {twrs_numProblematicHcalCells_branch->SetAddress(&twrs_numProblematicHcalCells_);}
	}
	twrs_numRecoveredEcalCells_branch = 0;
	if (tree->GetAlias("twrs_numRecoveredEcalCells") != 0) {
		twrs_numRecoveredEcalCells_branch = tree->GetBranch(tree->GetAlias("twrs_numRecoveredEcalCells"));
		if (twrs_numRecoveredEcalCells_branch) {twrs_numRecoveredEcalCells_branch->SetAddress(&twrs_numRecoveredEcalCells_);}
	}
	twrs_numRecoveredHcalCells_branch = 0;
	if (tree->GetAlias("twrs_numRecoveredHcalCells") != 0) {
		twrs_numRecoveredHcalCells_branch = tree->GetBranch(tree->GetAlias("twrs_numRecoveredHcalCells"));
		if (twrs_numRecoveredHcalCells_branch) {twrs_numRecoveredHcalCells_branch->SetAddress(&twrs_numRecoveredHcalCells_);}
	}
	hlt_prescales_branch = 0;
	if (tree->GetAlias("hlt_prescales") != 0) {
		hlt_prescales_branch = tree->GetBranch(tree->GetAlias("hlt_prescales"));
		if (hlt_prescales_branch) {hlt_prescales_branch->SetAddress(&hlt_prescales_);}
	}
  tree->SetMakeClass(0);
}
void GetEntry(unsigned int idx) 
	// this only marks branches as not loaded, saving a lot of time
	{
		index = idx;
		hlt_bits_isLoaded = false;
		hlt_trigNames_isLoaded = false;
		pfjets_bDiscriminatorNames_isLoaded = false;
		hcalnoise_HasBadRBXTS4TS5_isLoaded = false;
		evt_EcalDeadCellBoundaryEnergyFilter_isLoaded = false;
		evt_EcalDeadCellTriggerPrimitiveFilter_isLoaded = false;
		evt_cscTightHaloFilter_isLoaded = false;
		evt_eeBadScFilter_isLoaded = false;
		evt_eeNoiseFilter_isLoaded = false;
		evt_goodVertices_isLoaded = false;
		evt_hbheFilter_isLoaded = false;
		evt_hbheFilterRun1_isLoaded = false;
		evt_hbheFilterRun2Loose_isLoaded = false;
		evt_hbheFilterRun2Tight_isLoaded = false;
		evt_trackingFailureFilter_isLoaded = false;
		evt_bField_isLoaded = false;
		hcalnoise_GetRecHitEnergy_isLoaded = false;
		hcalnoise_GetRecHitEnergy15_isLoaded = false;
		hcalnoise_GetTotalCalibCharge_isLoaded = false;
		hcalnoise_TS4TS5NoiseSumE_isLoaded = false;
		hcalnoise_TS4TS5NoiseSumEt_isLoaded = false;
		hcalnoise_eventChargeFraction_isLoaded = false;
		hcalnoise_eventEMEnergy_isLoaded = false;
		hcalnoise_eventEMFraction_isLoaded = false;
		hcalnoise_eventHadEnergy_isLoaded = false;
		hcalnoise_eventTrackEnergy_isLoaded = false;
		hcalnoise_flatNoiseSumE_isLoaded = false;
		hcalnoise_flatNoiseSumEt_isLoaded = false;
		hcalnoise_isolatedNoiseSumE_isLoaded = false;
		hcalnoise_isolatedNoiseSumEt_isLoaded = false;
		hcalnoise_max10GeVHitTime_isLoaded = false;
		hcalnoise_max25GeVHitTime_isLoaded = false;
		hcalnoise_maxE10TS_isLoaded = false;
		hcalnoise_maxE2Over10TS_isLoaded = false;
		hcalnoise_maxE2TS_isLoaded = false;
		hcalnoise_min10GeVHitTime_isLoaded = false;
		hcalnoise_min25GeVHitTime_isLoaded = false;
		hcalnoise_minE10TS_isLoaded = false;
		hcalnoise_minE2Over10TS_isLoaded = false;
		hcalnoise_minE2TS_isLoaded = false;
		hcalnoise_minHPDEMF_isLoaded = false;
		hcalnoise_minRBXEMF_isLoaded = false;
		hcalnoise_rms10GeVHitTime_isLoaded = false;
		hcalnoise_rms25GeVHitTime_isLoaded = false;
		hcalnoise_spikeNoiseSumE_isLoaded = false;
		hcalnoise_spikeNoiseSumEt_isLoaded = false;
		hcalnoise_triangleNoiseSumE_isLoaded = false;
		hcalnoise_triangleNoiseSumEt_isLoaded = false;
		evt_ecalendcapm_met_isLoaded = false;
		evt_ecalendcapm_metPhi_isLoaded = false;
		evt_ecalendcapp_met_isLoaded = false;
		evt_ecalendcapp_metPhi_isLoaded = false;
		evt_ecalmet_isLoaded = false;
		evt_ecalmetPhi_isLoaded = false;
		evt_endcapm_met_isLoaded = false;
		evt_endcapm_metPhi_isLoaded = false;
		evt_endcapp_met_isLoaded = false;
		evt_endcapp_metPhi_isLoaded = false;
		evt_hcalendcapm_met_isLoaded = false;
		evt_hcalendcapm_metPhi_isLoaded = false;
		evt_hcalendcapp_met_isLoaded = false;
		evt_hcalendcapp_metPhi_isLoaded = false;
		evt_hcalmet_isLoaded = false;
		evt_hcalmetPhi_isLoaded = false;
		evt_met_isLoaded = false;
		evt_met_EtGt3_isLoaded = false;
		evt_metHO_isLoaded = false;
		evt_metHOPhi_isLoaded = false;
		evt_metHOSig_isLoaded = false;
		evt_metMuonCorr_isLoaded = false;
		evt_metMuonCorrPhi_isLoaded = false;
		evt_metMuonCorrSig_isLoaded = false;
		evt_metMuonJESCorr_isLoaded = false;
		evt_metMuonJESCorrPhi_isLoaded = false;
		evt_metMuonJESCorrSig_isLoaded = false;
		evt_metNoHF_isLoaded = false;
		evt_metNoHFHO_isLoaded = false;
		evt_metNoHFHOPhi_isLoaded = false;
		evt_metNoHFHOSig_isLoaded = false;
		evt_metNoHFPhi_isLoaded = false;
		evt_metNoHFSig_isLoaded = false;
		evt_metOpt_isLoaded = false;
		evt_metOptHO_isLoaded = false;
		evt_metOptHOPhi_isLoaded = false;
		evt_metOptHOSig_isLoaded = false;
		evt_metOptNoHF_isLoaded = false;
		evt_metOptNoHFHO_isLoaded = false;
		evt_metOptNoHFHOPhi_isLoaded = false;
		evt_metOptNoHFHOSig_isLoaded = false;
		evt_metOptNoHFPhi_isLoaded = false;
		evt_metOptNoHFSig_isLoaded = false;
		evt_metOptPhi_isLoaded = false;
		evt_metOptSig_isLoaded = false;
		evt_metPhi_isLoaded = false;
		evt_metPhi_EtGt3_isLoaded = false;
		evt_metSig_isLoaded = false;
		evt_sumet_isLoaded = false;
		evt_sumet_EtGt3_isLoaded = false;
		evt_sumetHO_isLoaded = false;
		evt_sumetMuonCorr_isLoaded = false;
		evt_sumetMuonJESCorr_isLoaded = false;
		evt_sumetNoHF_isLoaded = false;
		evt_sumetNoHFHO_isLoaded = false;
		evt_sumetOpt_isLoaded = false;
		evt_sumetOptHO_isLoaded = false;
		evt_sumetOptNoHF_isLoaded = false;
		evt_sumetOptNoHFHO_isLoaded = false;
		pfCaloMet_met_isLoaded = false;
		pfCaloMet_metPhi_isLoaded = false;
		pfCaloMet_metPhi_type1cor_isLoaded = false;
		pfCaloMet_metSig_isLoaded = false;
		pfCaloMet_metSignificance_isLoaded = false;
		pfCaloMet_met_type1cor_isLoaded = false;
		pfCaloMet_sumet_isLoaded = false;
		pfChMet_met_isLoaded = false;
		pfChMet_metPhi_isLoaded = false;
		pfChMet_metPhi_type1cor_isLoaded = false;
		pfChMet_metSig_isLoaded = false;
		pfChMet_metSignificance_isLoaded = false;
		pfChMet_met_type1cor_isLoaded = false;
		pfChMet_sumet_isLoaded = false;
		pfcluster_met_isLoaded = false;
		pfcluster_metphi_isLoaded = false;
		pfcluster_sumet_isLoaded = false;
		pfMet_met_isLoaded = false;
		pfMet_metPhi_isLoaded = false;
		pfMet_metPhi_type1cor_isLoaded = false;
		pfMet_metSig_isLoaded = false;
		pfMet_metSignificance_isLoaded = false;
		pfMet_met_type1cor_isLoaded = false;
		pfMet_sumet_isLoaded = false;
		pfcands_p4_isLoaded = false;
		pfjets_p4_isLoaded = false;
		hlt_trigObjs_p4_isLoaded = false;
		calojets_eta_isLoaded = false;
		calojets_phi_isLoaded = false;
		calojets_pt_isLoaded = false;
		twrs_ecalTime_isLoaded = false;
		twrs_emEnergy_isLoaded = false;
		twrs_emEt_isLoaded = false;
		twrs_emEtcorr_isLoaded = false;
		twrs_eta_isLoaded = false;
		twrs_etacorr_isLoaded = false;
		twrs_etcorr_isLoaded = false;
		twrs_hadEnergy_isLoaded = false;
		twrs_hadEt_isLoaded = false;
		twrs_hadEtcorr_isLoaded = false;
		twrs_hcalTime_isLoaded = false;
		twrs_outerEnergy_isLoaded = false;
		twrs_outerEt_isLoaded = false;
		twrs_outerEtcorr_isLoaded = false;
		twrs_pcorr_isLoaded = false;
		twrs_phi_isLoaded = false;
		twrs_phicorr_isLoaded = false;
		twrs_spikeEt_isLoaded = false;
		twrs_spikeR4_isLoaded = false;
		evt_ecalmet_etaslice_isLoaded = false;
		evt_ecalmet_etaslicePhi_isLoaded = false;
		evt_hcalmet_etaslice_isLoaded = false;
		evt_hcalmet_etaslicePhi_isLoaded = false;
		evt_towermet_etaslice_isLoaded = false;
		evt_towermet_etaslicePhi_isLoaded = false;
		mus_met_deltax_isLoaded = false;
		mus_met_deltay_isLoaded = false;
		pfcands_mass_isLoaded = false;
		pfcluster_energy_isLoaded = false;
		pfcluster_et_isLoaded = false;
		pfcluster_eta_isLoaded = false;
		pfcluster_phi_isLoaded = false;
		pfjets_area_isLoaded = false;
		pfjets_chargedEmE_isLoaded = false;
		pfjets_chargedHadronE_isLoaded = false;
		pfjets_electronE_isLoaded = false;
		pfjets_hfEmE_isLoaded = false;
		pfjets_hfHadronE_isLoaded = false;
		pfjets_mass_isLoaded = false;
		pfjets_muonE_isLoaded = false;
		pfjets_neutralEmE_isLoaded = false;
		pfjets_neutralHadronE_isLoaded = false;
		pfjets_photonE_isLoaded = false;
		pfjets_undoJEC_isLoaded = false;
		pfjets_bDiscriminators_isLoaded = false;
		evt_bunchCrossing_isLoaded = false;
		evt_experimentType_isLoaded = false;
		evt_isRealData_isLoaded = false;
		evt_ntracks_isLoaded = false;
		evt_orbitNumber_isLoaded = false;
		evt_storeNumber_isLoaded = false;
		hcalnoise_GetRecHitCount_isLoaded = false;
		hcalnoise_GetRecHitCount15_isLoaded = false;
		hcalnoise_hbheIsoNoiseFilter_isLoaded = false;
		hcalnoise_maxHPDHits_isLoaded = false;
		hcalnoise_maxHPDNoOtherHits_isLoaded = false;
		hcalnoise_maxRBXHits_isLoaded = false;
		hcalnoise_maxZeros_isLoaded = false;
		hcalnoise_noiseFilterStatus_isLoaded = false;
		hcalnoise_noiseType_isLoaded = false;
		hcalnoise_num10GeVHits_isLoaded = false;
		hcalnoise_num25GeVHits_isLoaded = false;
		hcalnoise_numFlatNoiseChannels_isLoaded = false;
		hcalnoise_numIsolatedNoiseChannels_isLoaded = false;
		hcalnoise_numProblematicRBXs_isLoaded = false;
		hcalnoise_numSpikeNoiseChannels_isLoaded = false;
		hcalnoise_numTS4TS5NoiseChannels_isLoaded = false;
		hcalnoise_numTriangleNoiseChannels_isLoaded = false;
		hcalnoise_passHighLevelNoiseFilter_isLoaded = false;
		hcalnoise_passLooseNoiseFilter_isLoaded = false;
		hcalnoise_passTightNoiseFilter_isLoaded = false;
		twrs_ieta_isLoaded = false;
		twrs_iphi_isLoaded = false;
		twrs_numCrystals_isLoaded = false;
		mus_met_flag_isLoaded = false;
		pfcands_charge_isLoaded = false;
		pfcands_particleId_isLoaded = false;
		pfcluster_layer_isLoaded = false;
		pfjets_chargedHadronMultiplicity_isLoaded = false;
		pfjets_chargedMultiplicity_isLoaded = false;
		pfjets_electronMultiplicity_isLoaded = false;
		pfjets_muonMultiplicity_isLoaded = false;
		pfjets_neutralHadronMultiplicity_isLoaded = false;
		pfjets_neutralMultiplicity_isLoaded = false;
		pfjets_photonMultiplicity_isLoaded = false;
		hlt_trigObjs_id_isLoaded = false;
		pfjets_pfcandIndicies_isLoaded = false;
		evt_ntwrs_isLoaded = false;
		evt_detectorStatus_isLoaded = false;
		evt_event_isLoaded = false;
		evt_lumiBlock_isLoaded = false;
		evt_run_isLoaded = false;
		twrs_detid_isLoaded = false;
		twrs_numBadEcalCells_isLoaded = false;
		twrs_numBadHcalCells_isLoaded = false;
		twrs_numProblematicEcalCells_isLoaded = false;
		twrs_numProblematicHcalCells_isLoaded = false;
		twrs_numRecoveredEcalCells_isLoaded = false;
		twrs_numRecoveredHcalCells_isLoaded = false;
		hlt_prescales_isLoaded = false;
	}

void LoadAllBranches() 
	// load all branches
{
	if (hlt_bits_branch != 0) hlt_bits();
	if (hlt_trigNames_branch != 0) hlt_trigNames();
	if (pfjets_bDiscriminatorNames_branch != 0) pfjets_bDiscriminatorNames();
	if (hcalnoise_HasBadRBXTS4TS5_branch != 0) hcalnoise_HasBadRBXTS4TS5();
	if (evt_EcalDeadCellBoundaryEnergyFilter_branch != 0) evt_EcalDeadCellBoundaryEnergyFilter();
	if (evt_EcalDeadCellTriggerPrimitiveFilter_branch != 0) evt_EcalDeadCellTriggerPrimitiveFilter();
	if (evt_cscTightHaloFilter_branch != 0) evt_cscTightHaloFilter();
	if (evt_eeBadScFilter_branch != 0) evt_eeBadScFilter();
	if (evt_eeNoiseFilter_branch != 0) evt_eeNoiseFilter();
	if (evt_goodVertices_branch != 0) evt_goodVertices();
	if (evt_hbheFilter_branch != 0) evt_hbheFilter();
	if (evt_hbheFilterRun1_branch != 0) evt_hbheFilterRun1();
	if (evt_hbheFilterRun2Loose_branch != 0) evt_hbheFilterRun2Loose();
	if (evt_hbheFilterRun2Tight_branch != 0) evt_hbheFilterRun2Tight();
	if (evt_trackingFailureFilter_branch != 0) evt_trackingFailureFilter();
	if (evt_bField_branch != 0) evt_bField();
	if (hcalnoise_GetRecHitEnergy_branch != 0) hcalnoise_GetRecHitEnergy();
	if (hcalnoise_GetRecHitEnergy15_branch != 0) hcalnoise_GetRecHitEnergy15();
	if (hcalnoise_GetTotalCalibCharge_branch != 0) hcalnoise_GetTotalCalibCharge();
	if (hcalnoise_TS4TS5NoiseSumE_branch != 0) hcalnoise_TS4TS5NoiseSumE();
	if (hcalnoise_TS4TS5NoiseSumEt_branch != 0) hcalnoise_TS4TS5NoiseSumEt();
	if (hcalnoise_eventChargeFraction_branch != 0) hcalnoise_eventChargeFraction();
	if (hcalnoise_eventEMEnergy_branch != 0) hcalnoise_eventEMEnergy();
	if (hcalnoise_eventEMFraction_branch != 0) hcalnoise_eventEMFraction();
	if (hcalnoise_eventHadEnergy_branch != 0) hcalnoise_eventHadEnergy();
	if (hcalnoise_eventTrackEnergy_branch != 0) hcalnoise_eventTrackEnergy();
	if (hcalnoise_flatNoiseSumE_branch != 0) hcalnoise_flatNoiseSumE();
	if (hcalnoise_flatNoiseSumEt_branch != 0) hcalnoise_flatNoiseSumEt();
	if (hcalnoise_isolatedNoiseSumE_branch != 0) hcalnoise_isolatedNoiseSumE();
	if (hcalnoise_isolatedNoiseSumEt_branch != 0) hcalnoise_isolatedNoiseSumEt();
	if (hcalnoise_max10GeVHitTime_branch != 0) hcalnoise_max10GeVHitTime();
	if (hcalnoise_max25GeVHitTime_branch != 0) hcalnoise_max25GeVHitTime();
	if (hcalnoise_maxE10TS_branch != 0) hcalnoise_maxE10TS();
	if (hcalnoise_maxE2Over10TS_branch != 0) hcalnoise_maxE2Over10TS();
	if (hcalnoise_maxE2TS_branch != 0) hcalnoise_maxE2TS();
	if (hcalnoise_min10GeVHitTime_branch != 0) hcalnoise_min10GeVHitTime();
	if (hcalnoise_min25GeVHitTime_branch != 0) hcalnoise_min25GeVHitTime();
	if (hcalnoise_minE10TS_branch != 0) hcalnoise_minE10TS();
	if (hcalnoise_minE2Over10TS_branch != 0) hcalnoise_minE2Over10TS();
	if (hcalnoise_minE2TS_branch != 0) hcalnoise_minE2TS();
	if (hcalnoise_minHPDEMF_branch != 0) hcalnoise_minHPDEMF();
	if (hcalnoise_minRBXEMF_branch != 0) hcalnoise_minRBXEMF();
	if (hcalnoise_rms10GeVHitTime_branch != 0) hcalnoise_rms10GeVHitTime();
	if (hcalnoise_rms25GeVHitTime_branch != 0) hcalnoise_rms25GeVHitTime();
	if (hcalnoise_spikeNoiseSumE_branch != 0) hcalnoise_spikeNoiseSumE();
	if (hcalnoise_spikeNoiseSumEt_branch != 0) hcalnoise_spikeNoiseSumEt();
	if (hcalnoise_triangleNoiseSumE_branch != 0) hcalnoise_triangleNoiseSumE();
	if (hcalnoise_triangleNoiseSumEt_branch != 0) hcalnoise_triangleNoiseSumEt();
	if (evt_ecalendcapm_met_branch != 0) evt_ecalendcapm_met();
	if (evt_ecalendcapm_metPhi_branch != 0) evt_ecalendcapm_metPhi();
	if (evt_ecalendcapp_met_branch != 0) evt_ecalendcapp_met();
	if (evt_ecalendcapp_metPhi_branch != 0) evt_ecalendcapp_metPhi();
	if (evt_ecalmet_branch != 0) evt_ecalmet();
	if (evt_ecalmetPhi_branch != 0) evt_ecalmetPhi();
	if (evt_endcapm_met_branch != 0) evt_endcapm_met();
	if (evt_endcapm_metPhi_branch != 0) evt_endcapm_metPhi();
	if (evt_endcapp_met_branch != 0) evt_endcapp_met();
	if (evt_endcapp_metPhi_branch != 0) evt_endcapp_metPhi();
	if (evt_hcalendcapm_met_branch != 0) evt_hcalendcapm_met();
	if (evt_hcalendcapm_metPhi_branch != 0) evt_hcalendcapm_metPhi();
	if (evt_hcalendcapp_met_branch != 0) evt_hcalendcapp_met();
	if (evt_hcalendcapp_metPhi_branch != 0) evt_hcalendcapp_metPhi();
	if (evt_hcalmet_branch != 0) evt_hcalmet();
	if (evt_hcalmetPhi_branch != 0) evt_hcalmetPhi();
	if (evt_met_branch != 0) evt_met();
	if (evt_met_EtGt3_branch != 0) evt_met_EtGt3();
	if (evt_metHO_branch != 0) evt_metHO();
	if (evt_metHOPhi_branch != 0) evt_metHOPhi();
	if (evt_metHOSig_branch != 0) evt_metHOSig();
	if (evt_metMuonCorr_branch != 0) evt_metMuonCorr();
	if (evt_metMuonCorrPhi_branch != 0) evt_metMuonCorrPhi();
	if (evt_metMuonCorrSig_branch != 0) evt_metMuonCorrSig();
	if (evt_metMuonJESCorr_branch != 0) evt_metMuonJESCorr();
	if (evt_metMuonJESCorrPhi_branch != 0) evt_metMuonJESCorrPhi();
	if (evt_metMuonJESCorrSig_branch != 0) evt_metMuonJESCorrSig();
	if (evt_metNoHF_branch != 0) evt_metNoHF();
	if (evt_metNoHFHO_branch != 0) evt_metNoHFHO();
	if (evt_metNoHFHOPhi_branch != 0) evt_metNoHFHOPhi();
	if (evt_metNoHFHOSig_branch != 0) evt_metNoHFHOSig();
	if (evt_metNoHFPhi_branch != 0) evt_metNoHFPhi();
	if (evt_metNoHFSig_branch != 0) evt_metNoHFSig();
	if (evt_metOpt_branch != 0) evt_metOpt();
	if (evt_metOptHO_branch != 0) evt_metOptHO();
	if (evt_metOptHOPhi_branch != 0) evt_metOptHOPhi();
	if (evt_metOptHOSig_branch != 0) evt_metOptHOSig();
	if (evt_metOptNoHF_branch != 0) evt_metOptNoHF();
	if (evt_metOptNoHFHO_branch != 0) evt_metOptNoHFHO();
	if (evt_metOptNoHFHOPhi_branch != 0) evt_metOptNoHFHOPhi();
	if (evt_metOptNoHFHOSig_branch != 0) evt_metOptNoHFHOSig();
	if (evt_metOptNoHFPhi_branch != 0) evt_metOptNoHFPhi();
	if (evt_metOptNoHFSig_branch != 0) evt_metOptNoHFSig();
	if (evt_metOptPhi_branch != 0) evt_metOptPhi();
	if (evt_metOptSig_branch != 0) evt_metOptSig();
	if (evt_metPhi_branch != 0) evt_metPhi();
	if (evt_metPhi_EtGt3_branch != 0) evt_metPhi_EtGt3();
	if (evt_metSig_branch != 0) evt_metSig();
	if (evt_sumet_branch != 0) evt_sumet();
	if (evt_sumet_EtGt3_branch != 0) evt_sumet_EtGt3();
	if (evt_sumetHO_branch != 0) evt_sumetHO();
	if (evt_sumetMuonCorr_branch != 0) evt_sumetMuonCorr();
	if (evt_sumetMuonJESCorr_branch != 0) evt_sumetMuonJESCorr();
	if (evt_sumetNoHF_branch != 0) evt_sumetNoHF();
	if (evt_sumetNoHFHO_branch != 0) evt_sumetNoHFHO();
	if (evt_sumetOpt_branch != 0) evt_sumetOpt();
	if (evt_sumetOptHO_branch != 0) evt_sumetOptHO();
	if (evt_sumetOptNoHF_branch != 0) evt_sumetOptNoHF();
	if (evt_sumetOptNoHFHO_branch != 0) evt_sumetOptNoHFHO();
	if (pfCaloMet_met_branch != 0) pfCaloMet_met();
	if (pfCaloMet_metPhi_branch != 0) pfCaloMet_metPhi();
	if (pfCaloMet_metPhi_type1cor_branch != 0) pfCaloMet_metPhi_type1cor();
	if (pfCaloMet_metSig_branch != 0) pfCaloMet_metSig();
	if (pfCaloMet_metSignificance_branch != 0) pfCaloMet_metSignificance();
	if (pfCaloMet_met_type1cor_branch != 0) pfCaloMet_met_type1cor();
	if (pfCaloMet_sumet_branch != 0) pfCaloMet_sumet();
	if (pfChMet_met_branch != 0) pfChMet_met();
	if (pfChMet_metPhi_branch != 0) pfChMet_metPhi();
	if (pfChMet_metPhi_type1cor_branch != 0) pfChMet_metPhi_type1cor();
	if (pfChMet_metSig_branch != 0) pfChMet_metSig();
	if (pfChMet_metSignificance_branch != 0) pfChMet_metSignificance();
	if (pfChMet_met_type1cor_branch != 0) pfChMet_met_type1cor();
	if (pfChMet_sumet_branch != 0) pfChMet_sumet();
	if (pfcluster_met_branch != 0) pfcluster_met();
	if (pfcluster_metphi_branch != 0) pfcluster_metphi();
	if (pfcluster_sumet_branch != 0) pfcluster_sumet();
	if (pfMet_met_branch != 0) pfMet_met();
	if (pfMet_metPhi_branch != 0) pfMet_metPhi();
	if (pfMet_metPhi_type1cor_branch != 0) pfMet_metPhi_type1cor();
	if (pfMet_metSig_branch != 0) pfMet_metSig();
	if (pfMet_metSignificance_branch != 0) pfMet_metSignificance();
	if (pfMet_met_type1cor_branch != 0) pfMet_met_type1cor();
	if (pfMet_sumet_branch != 0) pfMet_sumet();
	if (pfcands_p4_branch != 0) pfcands_p4();
	if (pfjets_p4_branch != 0) pfjets_p4();
	if (hlt_trigObjs_p4_branch != 0) hlt_trigObjs_p4();
	if (calojets_eta_branch != 0) calojets_eta();
	if (calojets_phi_branch != 0) calojets_phi();
	if (calojets_pt_branch != 0) calojets_pt();
	if (twrs_ecalTime_branch != 0) twrs_ecalTime();
	if (twrs_emEnergy_branch != 0) twrs_emEnergy();
	if (twrs_emEt_branch != 0) twrs_emEt();
	if (twrs_emEtcorr_branch != 0) twrs_emEtcorr();
	if (twrs_eta_branch != 0) twrs_eta();
	if (twrs_etacorr_branch != 0) twrs_etacorr();
	if (twrs_etcorr_branch != 0) twrs_etcorr();
	if (twrs_hadEnergy_branch != 0) twrs_hadEnergy();
	if (twrs_hadEt_branch != 0) twrs_hadEt();
	if (twrs_hadEtcorr_branch != 0) twrs_hadEtcorr();
	if (twrs_hcalTime_branch != 0) twrs_hcalTime();
	if (twrs_outerEnergy_branch != 0) twrs_outerEnergy();
	if (twrs_outerEt_branch != 0) twrs_outerEt();
	if (twrs_outerEtcorr_branch != 0) twrs_outerEtcorr();
	if (twrs_pcorr_branch != 0) twrs_pcorr();
	if (twrs_phi_branch != 0) twrs_phi();
	if (twrs_phicorr_branch != 0) twrs_phicorr();
	if (twrs_spikeEt_branch != 0) twrs_spikeEt();
	if (twrs_spikeR4_branch != 0) twrs_spikeR4();
	if (evt_ecalmet_etaslice_branch != 0) evt_ecalmet_etaslice();
	if (evt_ecalmet_etaslicePhi_branch != 0) evt_ecalmet_etaslicePhi();
	if (evt_hcalmet_etaslice_branch != 0) evt_hcalmet_etaslice();
	if (evt_hcalmet_etaslicePhi_branch != 0) evt_hcalmet_etaslicePhi();
	if (evt_towermet_etaslice_branch != 0) evt_towermet_etaslice();
	if (evt_towermet_etaslicePhi_branch != 0) evt_towermet_etaslicePhi();
	if (mus_met_deltax_branch != 0) mus_met_deltax();
	if (mus_met_deltay_branch != 0) mus_met_deltay();
	if (pfcands_mass_branch != 0) pfcands_mass();
	if (pfcluster_energy_branch != 0) pfcluster_energy();
	if (pfcluster_et_branch != 0) pfcluster_et();
	if (pfcluster_eta_branch != 0) pfcluster_eta();
	if (pfcluster_phi_branch != 0) pfcluster_phi();
	if (pfjets_area_branch != 0) pfjets_area();
	if (pfjets_chargedEmE_branch != 0) pfjets_chargedEmE();
	if (pfjets_chargedHadronE_branch != 0) pfjets_chargedHadronE();
	if (pfjets_electronE_branch != 0) pfjets_electronE();
	if (pfjets_hfEmE_branch != 0) pfjets_hfEmE();
	if (pfjets_hfHadronE_branch != 0) pfjets_hfHadronE();
	if (pfjets_mass_branch != 0) pfjets_mass();
	if (pfjets_muonE_branch != 0) pfjets_muonE();
	if (pfjets_neutralEmE_branch != 0) pfjets_neutralEmE();
	if (pfjets_neutralHadronE_branch != 0) pfjets_neutralHadronE();
	if (pfjets_photonE_branch != 0) pfjets_photonE();
	if (pfjets_undoJEC_branch != 0) pfjets_undoJEC();
	if (pfjets_bDiscriminators_branch != 0) pfjets_bDiscriminators();
	if (evt_bunchCrossing_branch != 0) evt_bunchCrossing();
	if (evt_experimentType_branch != 0) evt_experimentType();
	if (evt_isRealData_branch != 0) evt_isRealData();
	if (evt_ntracks_branch != 0) evt_ntracks();
	if (evt_orbitNumber_branch != 0) evt_orbitNumber();
	if (evt_storeNumber_branch != 0) evt_storeNumber();
	if (hcalnoise_GetRecHitCount_branch != 0) hcalnoise_GetRecHitCount();
	if (hcalnoise_GetRecHitCount15_branch != 0) hcalnoise_GetRecHitCount15();
	if (hcalnoise_hbheIsoNoiseFilter_branch != 0) hcalnoise_hbheIsoNoiseFilter();
	if (hcalnoise_maxHPDHits_branch != 0) hcalnoise_maxHPDHits();
	if (hcalnoise_maxHPDNoOtherHits_branch != 0) hcalnoise_maxHPDNoOtherHits();
	if (hcalnoise_maxRBXHits_branch != 0) hcalnoise_maxRBXHits();
	if (hcalnoise_maxZeros_branch != 0) hcalnoise_maxZeros();
	if (hcalnoise_noiseFilterStatus_branch != 0) hcalnoise_noiseFilterStatus();
	if (hcalnoise_noiseType_branch != 0) hcalnoise_noiseType();
	if (hcalnoise_num10GeVHits_branch != 0) hcalnoise_num10GeVHits();
	if (hcalnoise_num25GeVHits_branch != 0) hcalnoise_num25GeVHits();
	if (hcalnoise_numFlatNoiseChannels_branch != 0) hcalnoise_numFlatNoiseChannels();
	if (hcalnoise_numIsolatedNoiseChannels_branch != 0) hcalnoise_numIsolatedNoiseChannels();
	if (hcalnoise_numProblematicRBXs_branch != 0) hcalnoise_numProblematicRBXs();
	if (hcalnoise_numSpikeNoiseChannels_branch != 0) hcalnoise_numSpikeNoiseChannels();
	if (hcalnoise_numTS4TS5NoiseChannels_branch != 0) hcalnoise_numTS4TS5NoiseChannels();
	if (hcalnoise_numTriangleNoiseChannels_branch != 0) hcalnoise_numTriangleNoiseChannels();
	if (hcalnoise_passHighLevelNoiseFilter_branch != 0) hcalnoise_passHighLevelNoiseFilter();
	if (hcalnoise_passLooseNoiseFilter_branch != 0) hcalnoise_passLooseNoiseFilter();
	if (hcalnoise_passTightNoiseFilter_branch != 0) hcalnoise_passTightNoiseFilter();
	if (twrs_ieta_branch != 0) twrs_ieta();
	if (twrs_iphi_branch != 0) twrs_iphi();
	if (twrs_numCrystals_branch != 0) twrs_numCrystals();
	if (mus_met_flag_branch != 0) mus_met_flag();
	if (pfcands_charge_branch != 0) pfcands_charge();
	if (pfcands_particleId_branch != 0) pfcands_particleId();
	if (pfcluster_layer_branch != 0) pfcluster_layer();
	if (pfjets_chargedHadronMultiplicity_branch != 0) pfjets_chargedHadronMultiplicity();
	if (pfjets_chargedMultiplicity_branch != 0) pfjets_chargedMultiplicity();
	if (pfjets_electronMultiplicity_branch != 0) pfjets_electronMultiplicity();
	if (pfjets_muonMultiplicity_branch != 0) pfjets_muonMultiplicity();
	if (pfjets_neutralHadronMultiplicity_branch != 0) pfjets_neutralHadronMultiplicity();
	if (pfjets_neutralMultiplicity_branch != 0) pfjets_neutralMultiplicity();
	if (pfjets_photonMultiplicity_branch != 0) pfjets_photonMultiplicity();
	if (hlt_trigObjs_id_branch != 0) hlt_trigObjs_id();
	if (pfjets_pfcandIndicies_branch != 0) pfjets_pfcandIndicies();
	if (evt_ntwrs_branch != 0) evt_ntwrs();
	if (evt_detectorStatus_branch != 0) evt_detectorStatus();
	if (evt_event_branch != 0) evt_event();
	if (evt_lumiBlock_branch != 0) evt_lumiBlock();
	if (evt_run_branch != 0) evt_run();
	if (twrs_detid_branch != 0) twrs_detid();
	if (twrs_numBadEcalCells_branch != 0) twrs_numBadEcalCells();
	if (twrs_numBadHcalCells_branch != 0) twrs_numBadHcalCells();
	if (twrs_numProblematicEcalCells_branch != 0) twrs_numProblematicEcalCells();
	if (twrs_numProblematicHcalCells_branch != 0) twrs_numProblematicHcalCells();
	if (twrs_numRecoveredEcalCells_branch != 0) twrs_numRecoveredEcalCells();
	if (twrs_numRecoveredHcalCells_branch != 0) twrs_numRecoveredHcalCells();
	if (hlt_prescales_branch != 0) hlt_prescales();
}

	TBits &hlt_bits()
	{
		if (not hlt_bits_isLoaded) {
			if (hlt_bits_branch != 0) {
				hlt_bits_branch->GetEntry(index);
			} else { 
				printf("branch hlt_bits_branch does not exist!\n");
				exit(1);
			}
			hlt_bits_isLoaded = true;
		}
		return hlt_bits_;
	}
	const vector<TString> &hlt_trigNames()
	{
		if (not hlt_trigNames_isLoaded) {
			if (hlt_trigNames_branch != 0) {
				hlt_trigNames_branch->GetEntry(index);
			} else { 
				printf("branch hlt_trigNames_branch does not exist!\n");
				exit(1);
			}
			hlt_trigNames_isLoaded = true;
		}
		return hlt_trigNames_;
	}
	const vector<TString> &pfjets_bDiscriminatorNames()
	{
		if (not pfjets_bDiscriminatorNames_isLoaded) {
			if (pfjets_bDiscriminatorNames_branch != 0) {
				pfjets_bDiscriminatorNames_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_bDiscriminatorNames_branch does not exist!\n");
				exit(1);
			}
			pfjets_bDiscriminatorNames_isLoaded = true;
		}
		return pfjets_bDiscriminatorNames_;
	}
	bool &hcalnoise_HasBadRBXTS4TS5()
	{
		if (not hcalnoise_HasBadRBXTS4TS5_isLoaded) {
			if (hcalnoise_HasBadRBXTS4TS5_branch != 0) {
				hcalnoise_HasBadRBXTS4TS5_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_HasBadRBXTS4TS5_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_HasBadRBXTS4TS5_isLoaded = true;
		}
		return hcalnoise_HasBadRBXTS4TS5_;
	}
	bool &evt_EcalDeadCellBoundaryEnergyFilter()
	{
		if (not evt_EcalDeadCellBoundaryEnergyFilter_isLoaded) {
			if (evt_EcalDeadCellBoundaryEnergyFilter_branch != 0) {
				evt_EcalDeadCellBoundaryEnergyFilter_branch->GetEntry(index);
			} else { 
				printf("branch evt_EcalDeadCellBoundaryEnergyFilter_branch does not exist!\n");
				exit(1);
			}
			evt_EcalDeadCellBoundaryEnergyFilter_isLoaded = true;
		}
		return evt_EcalDeadCellBoundaryEnergyFilter_;
	}
	bool &evt_EcalDeadCellTriggerPrimitiveFilter()
	{
		if (not evt_EcalDeadCellTriggerPrimitiveFilter_isLoaded) {
			if (evt_EcalDeadCellTriggerPrimitiveFilter_branch != 0) {
				evt_EcalDeadCellTriggerPrimitiveFilter_branch->GetEntry(index);
			} else { 
				printf("branch evt_EcalDeadCellTriggerPrimitiveFilter_branch does not exist!\n");
				exit(1);
			}
			evt_EcalDeadCellTriggerPrimitiveFilter_isLoaded = true;
		}
		return evt_EcalDeadCellTriggerPrimitiveFilter_;
	}
	bool &evt_cscTightHaloFilter()
	{
		if (not evt_cscTightHaloFilter_isLoaded) {
			if (evt_cscTightHaloFilter_branch != 0) {
				evt_cscTightHaloFilter_branch->GetEntry(index);
			} else { 
				printf("branch evt_cscTightHaloFilter_branch does not exist!\n");
				exit(1);
			}
			evt_cscTightHaloFilter_isLoaded = true;
		}
		return evt_cscTightHaloFilter_;
	}
	bool &evt_eeBadScFilter()
	{
		if (not evt_eeBadScFilter_isLoaded) {
			if (evt_eeBadScFilter_branch != 0) {
				evt_eeBadScFilter_branch->GetEntry(index);
			} else { 
				printf("branch evt_eeBadScFilter_branch does not exist!\n");
				exit(1);
			}
			evt_eeBadScFilter_isLoaded = true;
		}
		return evt_eeBadScFilter_;
	}
	bool &evt_eeNoiseFilter()
	{
		if (not evt_eeNoiseFilter_isLoaded) {
			if (evt_eeNoiseFilter_branch != 0) {
				evt_eeNoiseFilter_branch->GetEntry(index);
			} else { 
				printf("branch evt_eeNoiseFilter_branch does not exist!\n");
				exit(1);
			}
			evt_eeNoiseFilter_isLoaded = true;
		}
		return evt_eeNoiseFilter_;
	}
	bool &evt_goodVertices()
	{
		if (not evt_goodVertices_isLoaded) {
			if (evt_goodVertices_branch != 0) {
				evt_goodVertices_branch->GetEntry(index);
			} else { 
				printf("branch evt_goodVertices_branch does not exist!\n");
				exit(1);
			}
			evt_goodVertices_isLoaded = true;
		}
		return evt_goodVertices_;
	}
	bool &evt_hbheFilter()
	{
		if (not evt_hbheFilter_isLoaded) {
			if (evt_hbheFilter_branch != 0) {
				evt_hbheFilter_branch->GetEntry(index);
			} else { 
				printf("branch evt_hbheFilter_branch does not exist!\n");
				exit(1);
			}
			evt_hbheFilter_isLoaded = true;
		}
		return evt_hbheFilter_;
	}
	bool &evt_hbheFilterRun1()
	{
		if (not evt_hbheFilterRun1_isLoaded) {
			if (evt_hbheFilterRun1_branch != 0) {
				evt_hbheFilterRun1_branch->GetEntry(index);
			} else { 
				printf("branch evt_hbheFilterRun1_branch does not exist!\n");
				exit(1);
			}
			evt_hbheFilterRun1_isLoaded = true;
		}
		return evt_hbheFilterRun1_;
	}
	bool &evt_hbheFilterRun2Loose()
	{
		if (not evt_hbheFilterRun2Loose_isLoaded) {
			if (evt_hbheFilterRun2Loose_branch != 0) {
				evt_hbheFilterRun2Loose_branch->GetEntry(index);
			} else { 
				printf("branch evt_hbheFilterRun2Loose_branch does not exist!\n");
				exit(1);
			}
			evt_hbheFilterRun2Loose_isLoaded = true;
		}
		return evt_hbheFilterRun2Loose_;
	}
	bool &evt_hbheFilterRun2Tight()
	{
		if (not evt_hbheFilterRun2Tight_isLoaded) {
			if (evt_hbheFilterRun2Tight_branch != 0) {
				evt_hbheFilterRun2Tight_branch->GetEntry(index);
			} else { 
				printf("branch evt_hbheFilterRun2Tight_branch does not exist!\n");
				exit(1);
			}
			evt_hbheFilterRun2Tight_isLoaded = true;
		}
		return evt_hbheFilterRun2Tight_;
	}
	bool &evt_trackingFailureFilter()
	{
		if (not evt_trackingFailureFilter_isLoaded) {
			if (evt_trackingFailureFilter_branch != 0) {
				evt_trackingFailureFilter_branch->GetEntry(index);
			} else { 
				printf("branch evt_trackingFailureFilter_branch does not exist!\n");
				exit(1);
			}
			evt_trackingFailureFilter_isLoaded = true;
		}
		return evt_trackingFailureFilter_;
	}
	float &evt_bField()
	{
		if (not evt_bField_isLoaded) {
			if (evt_bField_branch != 0) {
				evt_bField_branch->GetEntry(index);
			} else { 
				printf("branch evt_bField_branch does not exist!\n");
				exit(1);
			}
			evt_bField_isLoaded = true;
		}
		return evt_bField_;
	}
	float &hcalnoise_GetRecHitEnergy()
	{
		if (not hcalnoise_GetRecHitEnergy_isLoaded) {
			if (hcalnoise_GetRecHitEnergy_branch != 0) {
				hcalnoise_GetRecHitEnergy_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_GetRecHitEnergy_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_GetRecHitEnergy_isLoaded = true;
		}
		return hcalnoise_GetRecHitEnergy_;
	}
	float &hcalnoise_GetRecHitEnergy15()
	{
		if (not hcalnoise_GetRecHitEnergy15_isLoaded) {
			if (hcalnoise_GetRecHitEnergy15_branch != 0) {
				hcalnoise_GetRecHitEnergy15_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_GetRecHitEnergy15_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_GetRecHitEnergy15_isLoaded = true;
		}
		return hcalnoise_GetRecHitEnergy15_;
	}
	float &hcalnoise_GetTotalCalibCharge()
	{
		if (not hcalnoise_GetTotalCalibCharge_isLoaded) {
			if (hcalnoise_GetTotalCalibCharge_branch != 0) {
				hcalnoise_GetTotalCalibCharge_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_GetTotalCalibCharge_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_GetTotalCalibCharge_isLoaded = true;
		}
		return hcalnoise_GetTotalCalibCharge_;
	}
	float &hcalnoise_TS4TS5NoiseSumE()
	{
		if (not hcalnoise_TS4TS5NoiseSumE_isLoaded) {
			if (hcalnoise_TS4TS5NoiseSumE_branch != 0) {
				hcalnoise_TS4TS5NoiseSumE_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_TS4TS5NoiseSumE_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_TS4TS5NoiseSumE_isLoaded = true;
		}
		return hcalnoise_TS4TS5NoiseSumE_;
	}
	float &hcalnoise_TS4TS5NoiseSumEt()
	{
		if (not hcalnoise_TS4TS5NoiseSumEt_isLoaded) {
			if (hcalnoise_TS4TS5NoiseSumEt_branch != 0) {
				hcalnoise_TS4TS5NoiseSumEt_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_TS4TS5NoiseSumEt_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_TS4TS5NoiseSumEt_isLoaded = true;
		}
		return hcalnoise_TS4TS5NoiseSumEt_;
	}
	float &hcalnoise_eventChargeFraction()
	{
		if (not hcalnoise_eventChargeFraction_isLoaded) {
			if (hcalnoise_eventChargeFraction_branch != 0) {
				hcalnoise_eventChargeFraction_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_eventChargeFraction_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_eventChargeFraction_isLoaded = true;
		}
		return hcalnoise_eventChargeFraction_;
	}
	float &hcalnoise_eventEMEnergy()
	{
		if (not hcalnoise_eventEMEnergy_isLoaded) {
			if (hcalnoise_eventEMEnergy_branch != 0) {
				hcalnoise_eventEMEnergy_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_eventEMEnergy_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_eventEMEnergy_isLoaded = true;
		}
		return hcalnoise_eventEMEnergy_;
	}
	float &hcalnoise_eventEMFraction()
	{
		if (not hcalnoise_eventEMFraction_isLoaded) {
			if (hcalnoise_eventEMFraction_branch != 0) {
				hcalnoise_eventEMFraction_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_eventEMFraction_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_eventEMFraction_isLoaded = true;
		}
		return hcalnoise_eventEMFraction_;
	}
	float &hcalnoise_eventHadEnergy()
	{
		if (not hcalnoise_eventHadEnergy_isLoaded) {
			if (hcalnoise_eventHadEnergy_branch != 0) {
				hcalnoise_eventHadEnergy_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_eventHadEnergy_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_eventHadEnergy_isLoaded = true;
		}
		return hcalnoise_eventHadEnergy_;
	}
	float &hcalnoise_eventTrackEnergy()
	{
		if (not hcalnoise_eventTrackEnergy_isLoaded) {
			if (hcalnoise_eventTrackEnergy_branch != 0) {
				hcalnoise_eventTrackEnergy_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_eventTrackEnergy_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_eventTrackEnergy_isLoaded = true;
		}
		return hcalnoise_eventTrackEnergy_;
	}
	float &hcalnoise_flatNoiseSumE()
	{
		if (not hcalnoise_flatNoiseSumE_isLoaded) {
			if (hcalnoise_flatNoiseSumE_branch != 0) {
				hcalnoise_flatNoiseSumE_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_flatNoiseSumE_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_flatNoiseSumE_isLoaded = true;
		}
		return hcalnoise_flatNoiseSumE_;
	}
	float &hcalnoise_flatNoiseSumEt()
	{
		if (not hcalnoise_flatNoiseSumEt_isLoaded) {
			if (hcalnoise_flatNoiseSumEt_branch != 0) {
				hcalnoise_flatNoiseSumEt_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_flatNoiseSumEt_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_flatNoiseSumEt_isLoaded = true;
		}
		return hcalnoise_flatNoiseSumEt_;
	}
	float &hcalnoise_isolatedNoiseSumE()
	{
		if (not hcalnoise_isolatedNoiseSumE_isLoaded) {
			if (hcalnoise_isolatedNoiseSumE_branch != 0) {
				hcalnoise_isolatedNoiseSumE_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_isolatedNoiseSumE_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_isolatedNoiseSumE_isLoaded = true;
		}
		return hcalnoise_isolatedNoiseSumE_;
	}
	float &hcalnoise_isolatedNoiseSumEt()
	{
		if (not hcalnoise_isolatedNoiseSumEt_isLoaded) {
			if (hcalnoise_isolatedNoiseSumEt_branch != 0) {
				hcalnoise_isolatedNoiseSumEt_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_isolatedNoiseSumEt_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_isolatedNoiseSumEt_isLoaded = true;
		}
		return hcalnoise_isolatedNoiseSumEt_;
	}
	float &hcalnoise_max10GeVHitTime()
	{
		if (not hcalnoise_max10GeVHitTime_isLoaded) {
			if (hcalnoise_max10GeVHitTime_branch != 0) {
				hcalnoise_max10GeVHitTime_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_max10GeVHitTime_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_max10GeVHitTime_isLoaded = true;
		}
		return hcalnoise_max10GeVHitTime_;
	}
	float &hcalnoise_max25GeVHitTime()
	{
		if (not hcalnoise_max25GeVHitTime_isLoaded) {
			if (hcalnoise_max25GeVHitTime_branch != 0) {
				hcalnoise_max25GeVHitTime_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_max25GeVHitTime_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_max25GeVHitTime_isLoaded = true;
		}
		return hcalnoise_max25GeVHitTime_;
	}
	float &hcalnoise_maxE10TS()
	{
		if (not hcalnoise_maxE10TS_isLoaded) {
			if (hcalnoise_maxE10TS_branch != 0) {
				hcalnoise_maxE10TS_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_maxE10TS_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_maxE10TS_isLoaded = true;
		}
		return hcalnoise_maxE10TS_;
	}
	float &hcalnoise_maxE2Over10TS()
	{
		if (not hcalnoise_maxE2Over10TS_isLoaded) {
			if (hcalnoise_maxE2Over10TS_branch != 0) {
				hcalnoise_maxE2Over10TS_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_maxE2Over10TS_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_maxE2Over10TS_isLoaded = true;
		}
		return hcalnoise_maxE2Over10TS_;
	}
	float &hcalnoise_maxE2TS()
	{
		if (not hcalnoise_maxE2TS_isLoaded) {
			if (hcalnoise_maxE2TS_branch != 0) {
				hcalnoise_maxE2TS_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_maxE2TS_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_maxE2TS_isLoaded = true;
		}
		return hcalnoise_maxE2TS_;
	}
	float &hcalnoise_min10GeVHitTime()
	{
		if (not hcalnoise_min10GeVHitTime_isLoaded) {
			if (hcalnoise_min10GeVHitTime_branch != 0) {
				hcalnoise_min10GeVHitTime_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_min10GeVHitTime_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_min10GeVHitTime_isLoaded = true;
		}
		return hcalnoise_min10GeVHitTime_;
	}
	float &hcalnoise_min25GeVHitTime()
	{
		if (not hcalnoise_min25GeVHitTime_isLoaded) {
			if (hcalnoise_min25GeVHitTime_branch != 0) {
				hcalnoise_min25GeVHitTime_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_min25GeVHitTime_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_min25GeVHitTime_isLoaded = true;
		}
		return hcalnoise_min25GeVHitTime_;
	}
	float &hcalnoise_minE10TS()
	{
		if (not hcalnoise_minE10TS_isLoaded) {
			if (hcalnoise_minE10TS_branch != 0) {
				hcalnoise_minE10TS_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_minE10TS_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_minE10TS_isLoaded = true;
		}
		return hcalnoise_minE10TS_;
	}
	float &hcalnoise_minE2Over10TS()
	{
		if (not hcalnoise_minE2Over10TS_isLoaded) {
			if (hcalnoise_minE2Over10TS_branch != 0) {
				hcalnoise_minE2Over10TS_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_minE2Over10TS_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_minE2Over10TS_isLoaded = true;
		}
		return hcalnoise_minE2Over10TS_;
	}
	float &hcalnoise_minE2TS()
	{
		if (not hcalnoise_minE2TS_isLoaded) {
			if (hcalnoise_minE2TS_branch != 0) {
				hcalnoise_minE2TS_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_minE2TS_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_minE2TS_isLoaded = true;
		}
		return hcalnoise_minE2TS_;
	}
	float &hcalnoise_minHPDEMF()
	{
		if (not hcalnoise_minHPDEMF_isLoaded) {
			if (hcalnoise_minHPDEMF_branch != 0) {
				hcalnoise_minHPDEMF_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_minHPDEMF_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_minHPDEMF_isLoaded = true;
		}
		return hcalnoise_minHPDEMF_;
	}
	float &hcalnoise_minRBXEMF()
	{
		if (not hcalnoise_minRBXEMF_isLoaded) {
			if (hcalnoise_minRBXEMF_branch != 0) {
				hcalnoise_minRBXEMF_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_minRBXEMF_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_minRBXEMF_isLoaded = true;
		}
		return hcalnoise_minRBXEMF_;
	}
	float &hcalnoise_rms10GeVHitTime()
	{
		if (not hcalnoise_rms10GeVHitTime_isLoaded) {
			if (hcalnoise_rms10GeVHitTime_branch != 0) {
				hcalnoise_rms10GeVHitTime_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_rms10GeVHitTime_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_rms10GeVHitTime_isLoaded = true;
		}
		return hcalnoise_rms10GeVHitTime_;
	}
	float &hcalnoise_rms25GeVHitTime()
	{
		if (not hcalnoise_rms25GeVHitTime_isLoaded) {
			if (hcalnoise_rms25GeVHitTime_branch != 0) {
				hcalnoise_rms25GeVHitTime_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_rms25GeVHitTime_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_rms25GeVHitTime_isLoaded = true;
		}
		return hcalnoise_rms25GeVHitTime_;
	}
	float &hcalnoise_spikeNoiseSumE()
	{
		if (not hcalnoise_spikeNoiseSumE_isLoaded) {
			if (hcalnoise_spikeNoiseSumE_branch != 0) {
				hcalnoise_spikeNoiseSumE_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_spikeNoiseSumE_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_spikeNoiseSumE_isLoaded = true;
		}
		return hcalnoise_spikeNoiseSumE_;
	}
	float &hcalnoise_spikeNoiseSumEt()
	{
		if (not hcalnoise_spikeNoiseSumEt_isLoaded) {
			if (hcalnoise_spikeNoiseSumEt_branch != 0) {
				hcalnoise_spikeNoiseSumEt_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_spikeNoiseSumEt_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_spikeNoiseSumEt_isLoaded = true;
		}
		return hcalnoise_spikeNoiseSumEt_;
	}
	float &hcalnoise_triangleNoiseSumE()
	{
		if (not hcalnoise_triangleNoiseSumE_isLoaded) {
			if (hcalnoise_triangleNoiseSumE_branch != 0) {
				hcalnoise_triangleNoiseSumE_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_triangleNoiseSumE_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_triangleNoiseSumE_isLoaded = true;
		}
		return hcalnoise_triangleNoiseSumE_;
	}
	float &hcalnoise_triangleNoiseSumEt()
	{
		if (not hcalnoise_triangleNoiseSumEt_isLoaded) {
			if (hcalnoise_triangleNoiseSumEt_branch != 0) {
				hcalnoise_triangleNoiseSumEt_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_triangleNoiseSumEt_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_triangleNoiseSumEt_isLoaded = true;
		}
		return hcalnoise_triangleNoiseSumEt_;
	}
	float &evt_ecalendcapm_met()
	{
		if (not evt_ecalendcapm_met_isLoaded) {
			if (evt_ecalendcapm_met_branch != 0) {
				evt_ecalendcapm_met_branch->GetEntry(index);
			} else { 
				printf("branch evt_ecalendcapm_met_branch does not exist!\n");
				exit(1);
			}
			evt_ecalendcapm_met_isLoaded = true;
		}
		return evt_ecalendcapm_met_;
	}
	float &evt_ecalendcapm_metPhi()
	{
		if (not evt_ecalendcapm_metPhi_isLoaded) {
			if (evt_ecalendcapm_metPhi_branch != 0) {
				evt_ecalendcapm_metPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_ecalendcapm_metPhi_branch does not exist!\n");
				exit(1);
			}
			evt_ecalendcapm_metPhi_isLoaded = true;
		}
		return evt_ecalendcapm_metPhi_;
	}
	float &evt_ecalendcapp_met()
	{
		if (not evt_ecalendcapp_met_isLoaded) {
			if (evt_ecalendcapp_met_branch != 0) {
				evt_ecalendcapp_met_branch->GetEntry(index);
			} else { 
				printf("branch evt_ecalendcapp_met_branch does not exist!\n");
				exit(1);
			}
			evt_ecalendcapp_met_isLoaded = true;
		}
		return evt_ecalendcapp_met_;
	}
	float &evt_ecalendcapp_metPhi()
	{
		if (not evt_ecalendcapp_metPhi_isLoaded) {
			if (evt_ecalendcapp_metPhi_branch != 0) {
				evt_ecalendcapp_metPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_ecalendcapp_metPhi_branch does not exist!\n");
				exit(1);
			}
			evt_ecalendcapp_metPhi_isLoaded = true;
		}
		return evt_ecalendcapp_metPhi_;
	}
	float &evt_ecalmet()
	{
		if (not evt_ecalmet_isLoaded) {
			if (evt_ecalmet_branch != 0) {
				evt_ecalmet_branch->GetEntry(index);
			} else { 
				printf("branch evt_ecalmet_branch does not exist!\n");
				exit(1);
			}
			evt_ecalmet_isLoaded = true;
		}
		return evt_ecalmet_;
	}
	float &evt_ecalmetPhi()
	{
		if (not evt_ecalmetPhi_isLoaded) {
			if (evt_ecalmetPhi_branch != 0) {
				evt_ecalmetPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_ecalmetPhi_branch does not exist!\n");
				exit(1);
			}
			evt_ecalmetPhi_isLoaded = true;
		}
		return evt_ecalmetPhi_;
	}
	float &evt_endcapm_met()
	{
		if (not evt_endcapm_met_isLoaded) {
			if (evt_endcapm_met_branch != 0) {
				evt_endcapm_met_branch->GetEntry(index);
			} else { 
				printf("branch evt_endcapm_met_branch does not exist!\n");
				exit(1);
			}
			evt_endcapm_met_isLoaded = true;
		}
		return evt_endcapm_met_;
	}
	float &evt_endcapm_metPhi()
	{
		if (not evt_endcapm_metPhi_isLoaded) {
			if (evt_endcapm_metPhi_branch != 0) {
				evt_endcapm_metPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_endcapm_metPhi_branch does not exist!\n");
				exit(1);
			}
			evt_endcapm_metPhi_isLoaded = true;
		}
		return evt_endcapm_metPhi_;
	}
	float &evt_endcapp_met()
	{
		if (not evt_endcapp_met_isLoaded) {
			if (evt_endcapp_met_branch != 0) {
				evt_endcapp_met_branch->GetEntry(index);
			} else { 
				printf("branch evt_endcapp_met_branch does not exist!\n");
				exit(1);
			}
			evt_endcapp_met_isLoaded = true;
		}
		return evt_endcapp_met_;
	}
	float &evt_endcapp_metPhi()
	{
		if (not evt_endcapp_metPhi_isLoaded) {
			if (evt_endcapp_metPhi_branch != 0) {
				evt_endcapp_metPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_endcapp_metPhi_branch does not exist!\n");
				exit(1);
			}
			evt_endcapp_metPhi_isLoaded = true;
		}
		return evt_endcapp_metPhi_;
	}
	float &evt_hcalendcapm_met()
	{
		if (not evt_hcalendcapm_met_isLoaded) {
			if (evt_hcalendcapm_met_branch != 0) {
				evt_hcalendcapm_met_branch->GetEntry(index);
			} else { 
				printf("branch evt_hcalendcapm_met_branch does not exist!\n");
				exit(1);
			}
			evt_hcalendcapm_met_isLoaded = true;
		}
		return evt_hcalendcapm_met_;
	}
	float &evt_hcalendcapm_metPhi()
	{
		if (not evt_hcalendcapm_metPhi_isLoaded) {
			if (evt_hcalendcapm_metPhi_branch != 0) {
				evt_hcalendcapm_metPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_hcalendcapm_metPhi_branch does not exist!\n");
				exit(1);
			}
			evt_hcalendcapm_metPhi_isLoaded = true;
		}
		return evt_hcalendcapm_metPhi_;
	}
	float &evt_hcalendcapp_met()
	{
		if (not evt_hcalendcapp_met_isLoaded) {
			if (evt_hcalendcapp_met_branch != 0) {
				evt_hcalendcapp_met_branch->GetEntry(index);
			} else { 
				printf("branch evt_hcalendcapp_met_branch does not exist!\n");
				exit(1);
			}
			evt_hcalendcapp_met_isLoaded = true;
		}
		return evt_hcalendcapp_met_;
	}
	float &evt_hcalendcapp_metPhi()
	{
		if (not evt_hcalendcapp_metPhi_isLoaded) {
			if (evt_hcalendcapp_metPhi_branch != 0) {
				evt_hcalendcapp_metPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_hcalendcapp_metPhi_branch does not exist!\n");
				exit(1);
			}
			evt_hcalendcapp_metPhi_isLoaded = true;
		}
		return evt_hcalendcapp_metPhi_;
	}
	float &evt_hcalmet()
	{
		if (not evt_hcalmet_isLoaded) {
			if (evt_hcalmet_branch != 0) {
				evt_hcalmet_branch->GetEntry(index);
			} else { 
				printf("branch evt_hcalmet_branch does not exist!\n");
				exit(1);
			}
			evt_hcalmet_isLoaded = true;
		}
		return evt_hcalmet_;
	}
	float &evt_hcalmetPhi()
	{
		if (not evt_hcalmetPhi_isLoaded) {
			if (evt_hcalmetPhi_branch != 0) {
				evt_hcalmetPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_hcalmetPhi_branch does not exist!\n");
				exit(1);
			}
			evt_hcalmetPhi_isLoaded = true;
		}
		return evt_hcalmetPhi_;
	}
	float &evt_met()
	{
		if (not evt_met_isLoaded) {
			if (evt_met_branch != 0) {
				evt_met_branch->GetEntry(index);
			} else { 
				printf("branch evt_met_branch does not exist!\n");
				exit(1);
			}
			evt_met_isLoaded = true;
		}
		return evt_met_;
	}
	float &evt_met_EtGt3()
	{
		if (not evt_met_EtGt3_isLoaded) {
			if (evt_met_EtGt3_branch != 0) {
				evt_met_EtGt3_branch->GetEntry(index);
			} else { 
				printf("branch evt_met_EtGt3_branch does not exist!\n");
				exit(1);
			}
			evt_met_EtGt3_isLoaded = true;
		}
		return evt_met_EtGt3_;
	}
	float &evt_metHO()
	{
		if (not evt_metHO_isLoaded) {
			if (evt_metHO_branch != 0) {
				evt_metHO_branch->GetEntry(index);
			} else { 
				printf("branch evt_metHO_branch does not exist!\n");
				exit(1);
			}
			evt_metHO_isLoaded = true;
		}
		return evt_metHO_;
	}
	float &evt_metHOPhi()
	{
		if (not evt_metHOPhi_isLoaded) {
			if (evt_metHOPhi_branch != 0) {
				evt_metHOPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_metHOPhi_branch does not exist!\n");
				exit(1);
			}
			evt_metHOPhi_isLoaded = true;
		}
		return evt_metHOPhi_;
	}
	float &evt_metHOSig()
	{
		if (not evt_metHOSig_isLoaded) {
			if (evt_metHOSig_branch != 0) {
				evt_metHOSig_branch->GetEntry(index);
			} else { 
				printf("branch evt_metHOSig_branch does not exist!\n");
				exit(1);
			}
			evt_metHOSig_isLoaded = true;
		}
		return evt_metHOSig_;
	}
	float &evt_metMuonCorr()
	{
		if (not evt_metMuonCorr_isLoaded) {
			if (evt_metMuonCorr_branch != 0) {
				evt_metMuonCorr_branch->GetEntry(index);
			} else { 
				printf("branch evt_metMuonCorr_branch does not exist!\n");
				exit(1);
			}
			evt_metMuonCorr_isLoaded = true;
		}
		return evt_metMuonCorr_;
	}
	float &evt_metMuonCorrPhi()
	{
		if (not evt_metMuonCorrPhi_isLoaded) {
			if (evt_metMuonCorrPhi_branch != 0) {
				evt_metMuonCorrPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_metMuonCorrPhi_branch does not exist!\n");
				exit(1);
			}
			evt_metMuonCorrPhi_isLoaded = true;
		}
		return evt_metMuonCorrPhi_;
	}
	float &evt_metMuonCorrSig()
	{
		if (not evt_metMuonCorrSig_isLoaded) {
			if (evt_metMuonCorrSig_branch != 0) {
				evt_metMuonCorrSig_branch->GetEntry(index);
			} else { 
				printf("branch evt_metMuonCorrSig_branch does not exist!\n");
				exit(1);
			}
			evt_metMuonCorrSig_isLoaded = true;
		}
		return evt_metMuonCorrSig_;
	}
	float &evt_metMuonJESCorr()
	{
		if (not evt_metMuonJESCorr_isLoaded) {
			if (evt_metMuonJESCorr_branch != 0) {
				evt_metMuonJESCorr_branch->GetEntry(index);
			} else { 
				printf("branch evt_metMuonJESCorr_branch does not exist!\n");
				exit(1);
			}
			evt_metMuonJESCorr_isLoaded = true;
		}
		return evt_metMuonJESCorr_;
	}
	float &evt_metMuonJESCorrPhi()
	{
		if (not evt_metMuonJESCorrPhi_isLoaded) {
			if (evt_metMuonJESCorrPhi_branch != 0) {
				evt_metMuonJESCorrPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_metMuonJESCorrPhi_branch does not exist!\n");
				exit(1);
			}
			evt_metMuonJESCorrPhi_isLoaded = true;
		}
		return evt_metMuonJESCorrPhi_;
	}
	float &evt_metMuonJESCorrSig()
	{
		if (not evt_metMuonJESCorrSig_isLoaded) {
			if (evt_metMuonJESCorrSig_branch != 0) {
				evt_metMuonJESCorrSig_branch->GetEntry(index);
			} else { 
				printf("branch evt_metMuonJESCorrSig_branch does not exist!\n");
				exit(1);
			}
			evt_metMuonJESCorrSig_isLoaded = true;
		}
		return evt_metMuonJESCorrSig_;
	}
	float &evt_metNoHF()
	{
		if (not evt_metNoHF_isLoaded) {
			if (evt_metNoHF_branch != 0) {
				evt_metNoHF_branch->GetEntry(index);
			} else { 
				printf("branch evt_metNoHF_branch does not exist!\n");
				exit(1);
			}
			evt_metNoHF_isLoaded = true;
		}
		return evt_metNoHF_;
	}
	float &evt_metNoHFHO()
	{
		if (not evt_metNoHFHO_isLoaded) {
			if (evt_metNoHFHO_branch != 0) {
				evt_metNoHFHO_branch->GetEntry(index);
			} else { 
				printf("branch evt_metNoHFHO_branch does not exist!\n");
				exit(1);
			}
			evt_metNoHFHO_isLoaded = true;
		}
		return evt_metNoHFHO_;
	}
	float &evt_metNoHFHOPhi()
	{
		if (not evt_metNoHFHOPhi_isLoaded) {
			if (evt_metNoHFHOPhi_branch != 0) {
				evt_metNoHFHOPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_metNoHFHOPhi_branch does not exist!\n");
				exit(1);
			}
			evt_metNoHFHOPhi_isLoaded = true;
		}
		return evt_metNoHFHOPhi_;
	}
	float &evt_metNoHFHOSig()
	{
		if (not evt_metNoHFHOSig_isLoaded) {
			if (evt_metNoHFHOSig_branch != 0) {
				evt_metNoHFHOSig_branch->GetEntry(index);
			} else { 
				printf("branch evt_metNoHFHOSig_branch does not exist!\n");
				exit(1);
			}
			evt_metNoHFHOSig_isLoaded = true;
		}
		return evt_metNoHFHOSig_;
	}
	float &evt_metNoHFPhi()
	{
		if (not evt_metNoHFPhi_isLoaded) {
			if (evt_metNoHFPhi_branch != 0) {
				evt_metNoHFPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_metNoHFPhi_branch does not exist!\n");
				exit(1);
			}
			evt_metNoHFPhi_isLoaded = true;
		}
		return evt_metNoHFPhi_;
	}
	float &evt_metNoHFSig()
	{
		if (not evt_metNoHFSig_isLoaded) {
			if (evt_metNoHFSig_branch != 0) {
				evt_metNoHFSig_branch->GetEntry(index);
			} else { 
				printf("branch evt_metNoHFSig_branch does not exist!\n");
				exit(1);
			}
			evt_metNoHFSig_isLoaded = true;
		}
		return evt_metNoHFSig_;
	}
	float &evt_metOpt()
	{
		if (not evt_metOpt_isLoaded) {
			if (evt_metOpt_branch != 0) {
				evt_metOpt_branch->GetEntry(index);
			} else { 
				printf("branch evt_metOpt_branch does not exist!\n");
				exit(1);
			}
			evt_metOpt_isLoaded = true;
		}
		return evt_metOpt_;
	}
	float &evt_metOptHO()
	{
		if (not evt_metOptHO_isLoaded) {
			if (evt_metOptHO_branch != 0) {
				evt_metOptHO_branch->GetEntry(index);
			} else { 
				printf("branch evt_metOptHO_branch does not exist!\n");
				exit(1);
			}
			evt_metOptHO_isLoaded = true;
		}
		return evt_metOptHO_;
	}
	float &evt_metOptHOPhi()
	{
		if (not evt_metOptHOPhi_isLoaded) {
			if (evt_metOptHOPhi_branch != 0) {
				evt_metOptHOPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_metOptHOPhi_branch does not exist!\n");
				exit(1);
			}
			evt_metOptHOPhi_isLoaded = true;
		}
		return evt_metOptHOPhi_;
	}
	float &evt_metOptHOSig()
	{
		if (not evt_metOptHOSig_isLoaded) {
			if (evt_metOptHOSig_branch != 0) {
				evt_metOptHOSig_branch->GetEntry(index);
			} else { 
				printf("branch evt_metOptHOSig_branch does not exist!\n");
				exit(1);
			}
			evt_metOptHOSig_isLoaded = true;
		}
		return evt_metOptHOSig_;
	}
	float &evt_metOptNoHF()
	{
		if (not evt_metOptNoHF_isLoaded) {
			if (evt_metOptNoHF_branch != 0) {
				evt_metOptNoHF_branch->GetEntry(index);
			} else { 
				printf("branch evt_metOptNoHF_branch does not exist!\n");
				exit(1);
			}
			evt_metOptNoHF_isLoaded = true;
		}
		return evt_metOptNoHF_;
	}
	float &evt_metOptNoHFHO()
	{
		if (not evt_metOptNoHFHO_isLoaded) {
			if (evt_metOptNoHFHO_branch != 0) {
				evt_metOptNoHFHO_branch->GetEntry(index);
			} else { 
				printf("branch evt_metOptNoHFHO_branch does not exist!\n");
				exit(1);
			}
			evt_metOptNoHFHO_isLoaded = true;
		}
		return evt_metOptNoHFHO_;
	}
	float &evt_metOptNoHFHOPhi()
	{
		if (not evt_metOptNoHFHOPhi_isLoaded) {
			if (evt_metOptNoHFHOPhi_branch != 0) {
				evt_metOptNoHFHOPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_metOptNoHFHOPhi_branch does not exist!\n");
				exit(1);
			}
			evt_metOptNoHFHOPhi_isLoaded = true;
		}
		return evt_metOptNoHFHOPhi_;
	}
	float &evt_metOptNoHFHOSig()
	{
		if (not evt_metOptNoHFHOSig_isLoaded) {
			if (evt_metOptNoHFHOSig_branch != 0) {
				evt_metOptNoHFHOSig_branch->GetEntry(index);
			} else { 
				printf("branch evt_metOptNoHFHOSig_branch does not exist!\n");
				exit(1);
			}
			evt_metOptNoHFHOSig_isLoaded = true;
		}
		return evt_metOptNoHFHOSig_;
	}
	float &evt_metOptNoHFPhi()
	{
		if (not evt_metOptNoHFPhi_isLoaded) {
			if (evt_metOptNoHFPhi_branch != 0) {
				evt_metOptNoHFPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_metOptNoHFPhi_branch does not exist!\n");
				exit(1);
			}
			evt_metOptNoHFPhi_isLoaded = true;
		}
		return evt_metOptNoHFPhi_;
	}
	float &evt_metOptNoHFSig()
	{
		if (not evt_metOptNoHFSig_isLoaded) {
			if (evt_metOptNoHFSig_branch != 0) {
				evt_metOptNoHFSig_branch->GetEntry(index);
			} else { 
				printf("branch evt_metOptNoHFSig_branch does not exist!\n");
				exit(1);
			}
			evt_metOptNoHFSig_isLoaded = true;
		}
		return evt_metOptNoHFSig_;
	}
	float &evt_metOptPhi()
	{
		if (not evt_metOptPhi_isLoaded) {
			if (evt_metOptPhi_branch != 0) {
				evt_metOptPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_metOptPhi_branch does not exist!\n");
				exit(1);
			}
			evt_metOptPhi_isLoaded = true;
		}
		return evt_metOptPhi_;
	}
	float &evt_metOptSig()
	{
		if (not evt_metOptSig_isLoaded) {
			if (evt_metOptSig_branch != 0) {
				evt_metOptSig_branch->GetEntry(index);
			} else { 
				printf("branch evt_metOptSig_branch does not exist!\n");
				exit(1);
			}
			evt_metOptSig_isLoaded = true;
		}
		return evt_metOptSig_;
	}
	float &evt_metPhi()
	{
		if (not evt_metPhi_isLoaded) {
			if (evt_metPhi_branch != 0) {
				evt_metPhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_metPhi_branch does not exist!\n");
				exit(1);
			}
			evt_metPhi_isLoaded = true;
		}
		return evt_metPhi_;
	}
	float &evt_metPhi_EtGt3()
	{
		if (not evt_metPhi_EtGt3_isLoaded) {
			if (evt_metPhi_EtGt3_branch != 0) {
				evt_metPhi_EtGt3_branch->GetEntry(index);
			} else { 
				printf("branch evt_metPhi_EtGt3_branch does not exist!\n");
				exit(1);
			}
			evt_metPhi_EtGt3_isLoaded = true;
		}
		return evt_metPhi_EtGt3_;
	}
	float &evt_metSig()
	{
		if (not evt_metSig_isLoaded) {
			if (evt_metSig_branch != 0) {
				evt_metSig_branch->GetEntry(index);
			} else { 
				printf("branch evt_metSig_branch does not exist!\n");
				exit(1);
			}
			evt_metSig_isLoaded = true;
		}
		return evt_metSig_;
	}
	float &evt_sumet()
	{
		if (not evt_sumet_isLoaded) {
			if (evt_sumet_branch != 0) {
				evt_sumet_branch->GetEntry(index);
			} else { 
				printf("branch evt_sumet_branch does not exist!\n");
				exit(1);
			}
			evt_sumet_isLoaded = true;
		}
		return evt_sumet_;
	}
	float &evt_sumet_EtGt3()
	{
		if (not evt_sumet_EtGt3_isLoaded) {
			if (evt_sumet_EtGt3_branch != 0) {
				evt_sumet_EtGt3_branch->GetEntry(index);
			} else { 
				printf("branch evt_sumet_EtGt3_branch does not exist!\n");
				exit(1);
			}
			evt_sumet_EtGt3_isLoaded = true;
		}
		return evt_sumet_EtGt3_;
	}
	float &evt_sumetHO()
	{
		if (not evt_sumetHO_isLoaded) {
			if (evt_sumetHO_branch != 0) {
				evt_sumetHO_branch->GetEntry(index);
			} else { 
				printf("branch evt_sumetHO_branch does not exist!\n");
				exit(1);
			}
			evt_sumetHO_isLoaded = true;
		}
		return evt_sumetHO_;
	}
	float &evt_sumetMuonCorr()
	{
		if (not evt_sumetMuonCorr_isLoaded) {
			if (evt_sumetMuonCorr_branch != 0) {
				evt_sumetMuonCorr_branch->GetEntry(index);
			} else { 
				printf("branch evt_sumetMuonCorr_branch does not exist!\n");
				exit(1);
			}
			evt_sumetMuonCorr_isLoaded = true;
		}
		return evt_sumetMuonCorr_;
	}
	float &evt_sumetMuonJESCorr()
	{
		if (not evt_sumetMuonJESCorr_isLoaded) {
			if (evt_sumetMuonJESCorr_branch != 0) {
				evt_sumetMuonJESCorr_branch->GetEntry(index);
			} else { 
				printf("branch evt_sumetMuonJESCorr_branch does not exist!\n");
				exit(1);
			}
			evt_sumetMuonJESCorr_isLoaded = true;
		}
		return evt_sumetMuonJESCorr_;
	}
	float &evt_sumetNoHF()
	{
		if (not evt_sumetNoHF_isLoaded) {
			if (evt_sumetNoHF_branch != 0) {
				evt_sumetNoHF_branch->GetEntry(index);
			} else { 
				printf("branch evt_sumetNoHF_branch does not exist!\n");
				exit(1);
			}
			evt_sumetNoHF_isLoaded = true;
		}
		return evt_sumetNoHF_;
	}
	float &evt_sumetNoHFHO()
	{
		if (not evt_sumetNoHFHO_isLoaded) {
			if (evt_sumetNoHFHO_branch != 0) {
				evt_sumetNoHFHO_branch->GetEntry(index);
			} else { 
				printf("branch evt_sumetNoHFHO_branch does not exist!\n");
				exit(1);
			}
			evt_sumetNoHFHO_isLoaded = true;
		}
		return evt_sumetNoHFHO_;
	}
	float &evt_sumetOpt()
	{
		if (not evt_sumetOpt_isLoaded) {
			if (evt_sumetOpt_branch != 0) {
				evt_sumetOpt_branch->GetEntry(index);
			} else { 
				printf("branch evt_sumetOpt_branch does not exist!\n");
				exit(1);
			}
			evt_sumetOpt_isLoaded = true;
		}
		return evt_sumetOpt_;
	}
	float &evt_sumetOptHO()
	{
		if (not evt_sumetOptHO_isLoaded) {
			if (evt_sumetOptHO_branch != 0) {
				evt_sumetOptHO_branch->GetEntry(index);
			} else { 
				printf("branch evt_sumetOptHO_branch does not exist!\n");
				exit(1);
			}
			evt_sumetOptHO_isLoaded = true;
		}
		return evt_sumetOptHO_;
	}
	float &evt_sumetOptNoHF()
	{
		if (not evt_sumetOptNoHF_isLoaded) {
			if (evt_sumetOptNoHF_branch != 0) {
				evt_sumetOptNoHF_branch->GetEntry(index);
			} else { 
				printf("branch evt_sumetOptNoHF_branch does not exist!\n");
				exit(1);
			}
			evt_sumetOptNoHF_isLoaded = true;
		}
		return evt_sumetOptNoHF_;
	}
	float &evt_sumetOptNoHFHO()
	{
		if (not evt_sumetOptNoHFHO_isLoaded) {
			if (evt_sumetOptNoHFHO_branch != 0) {
				evt_sumetOptNoHFHO_branch->GetEntry(index);
			} else { 
				printf("branch evt_sumetOptNoHFHO_branch does not exist!\n");
				exit(1);
			}
			evt_sumetOptNoHFHO_isLoaded = true;
		}
		return evt_sumetOptNoHFHO_;
	}
	float &pfCaloMet_met()
	{
		if (not pfCaloMet_met_isLoaded) {
			if (pfCaloMet_met_branch != 0) {
				pfCaloMet_met_branch->GetEntry(index);
			} else { 
				printf("branch pfCaloMet_met_branch does not exist!\n");
				exit(1);
			}
			pfCaloMet_met_isLoaded = true;
		}
		return pfCaloMet_met_;
	}
	float &pfCaloMet_metPhi()
	{
		if (not pfCaloMet_metPhi_isLoaded) {
			if (pfCaloMet_metPhi_branch != 0) {
				pfCaloMet_metPhi_branch->GetEntry(index);
			} else { 
				printf("branch pfCaloMet_metPhi_branch does not exist!\n");
				exit(1);
			}
			pfCaloMet_metPhi_isLoaded = true;
		}
		return pfCaloMet_metPhi_;
	}
	float &pfCaloMet_metPhi_type1cor()
	{
		if (not pfCaloMet_metPhi_type1cor_isLoaded) {
			if (pfCaloMet_metPhi_type1cor_branch != 0) {
				pfCaloMet_metPhi_type1cor_branch->GetEntry(index);
			} else { 
				printf("branch pfCaloMet_metPhi_type1cor_branch does not exist!\n");
				exit(1);
			}
			pfCaloMet_metPhi_type1cor_isLoaded = true;
		}
		return pfCaloMet_metPhi_type1cor_;
	}
	float &pfCaloMet_metSig()
	{
		if (not pfCaloMet_metSig_isLoaded) {
			if (pfCaloMet_metSig_branch != 0) {
				pfCaloMet_metSig_branch->GetEntry(index);
			} else { 
				printf("branch pfCaloMet_metSig_branch does not exist!\n");
				exit(1);
			}
			pfCaloMet_metSig_isLoaded = true;
		}
		return pfCaloMet_metSig_;
	}
	float &pfCaloMet_metSignificance()
	{
		if (not pfCaloMet_metSignificance_isLoaded) {
			if (pfCaloMet_metSignificance_branch != 0) {
				pfCaloMet_metSignificance_branch->GetEntry(index);
			} else { 
				printf("branch pfCaloMet_metSignificance_branch does not exist!\n");
				exit(1);
			}
			pfCaloMet_metSignificance_isLoaded = true;
		}
		return pfCaloMet_metSignificance_;
	}
	float &pfCaloMet_met_type1cor()
	{
		if (not pfCaloMet_met_type1cor_isLoaded) {
			if (pfCaloMet_met_type1cor_branch != 0) {
				pfCaloMet_met_type1cor_branch->GetEntry(index);
			} else { 
				printf("branch pfCaloMet_met_type1cor_branch does not exist!\n");
				exit(1);
			}
			pfCaloMet_met_type1cor_isLoaded = true;
		}
		return pfCaloMet_met_type1cor_;
	}
	float &pfCaloMet_sumet()
	{
		if (not pfCaloMet_sumet_isLoaded) {
			if (pfCaloMet_sumet_branch != 0) {
				pfCaloMet_sumet_branch->GetEntry(index);
			} else { 
				printf("branch pfCaloMet_sumet_branch does not exist!\n");
				exit(1);
			}
			pfCaloMet_sumet_isLoaded = true;
		}
		return pfCaloMet_sumet_;
	}
	float &pfChMet_met()
	{
		if (not pfChMet_met_isLoaded) {
			if (pfChMet_met_branch != 0) {
				pfChMet_met_branch->GetEntry(index);
			} else { 
				printf("branch pfChMet_met_branch does not exist!\n");
				exit(1);
			}
			pfChMet_met_isLoaded = true;
		}
		return pfChMet_met_;
	}
	float &pfChMet_metPhi()
	{
		if (not pfChMet_metPhi_isLoaded) {
			if (pfChMet_metPhi_branch != 0) {
				pfChMet_metPhi_branch->GetEntry(index);
			} else { 
				printf("branch pfChMet_metPhi_branch does not exist!\n");
				exit(1);
			}
			pfChMet_metPhi_isLoaded = true;
		}
		return pfChMet_metPhi_;
	}
	float &pfChMet_metPhi_type1cor()
	{
		if (not pfChMet_metPhi_type1cor_isLoaded) {
			if (pfChMet_metPhi_type1cor_branch != 0) {
				pfChMet_metPhi_type1cor_branch->GetEntry(index);
			} else { 
				printf("branch pfChMet_metPhi_type1cor_branch does not exist!\n");
				exit(1);
			}
			pfChMet_metPhi_type1cor_isLoaded = true;
		}
		return pfChMet_metPhi_type1cor_;
	}
	float &pfChMet_metSig()
	{
		if (not pfChMet_metSig_isLoaded) {
			if (pfChMet_metSig_branch != 0) {
				pfChMet_metSig_branch->GetEntry(index);
			} else { 
				printf("branch pfChMet_metSig_branch does not exist!\n");
				exit(1);
			}
			pfChMet_metSig_isLoaded = true;
		}
		return pfChMet_metSig_;
	}
	float &pfChMet_metSignificance()
	{
		if (not pfChMet_metSignificance_isLoaded) {
			if (pfChMet_metSignificance_branch != 0) {
				pfChMet_metSignificance_branch->GetEntry(index);
			} else { 
				printf("branch pfChMet_metSignificance_branch does not exist!\n");
				exit(1);
			}
			pfChMet_metSignificance_isLoaded = true;
		}
		return pfChMet_metSignificance_;
	}
	float &pfChMet_met_type1cor()
	{
		if (not pfChMet_met_type1cor_isLoaded) {
			if (pfChMet_met_type1cor_branch != 0) {
				pfChMet_met_type1cor_branch->GetEntry(index);
			} else { 
				printf("branch pfChMet_met_type1cor_branch does not exist!\n");
				exit(1);
			}
			pfChMet_met_type1cor_isLoaded = true;
		}
		return pfChMet_met_type1cor_;
	}
	float &pfChMet_sumet()
	{
		if (not pfChMet_sumet_isLoaded) {
			if (pfChMet_sumet_branch != 0) {
				pfChMet_sumet_branch->GetEntry(index);
			} else { 
				printf("branch pfChMet_sumet_branch does not exist!\n");
				exit(1);
			}
			pfChMet_sumet_isLoaded = true;
		}
		return pfChMet_sumet_;
	}
	float &pfcluster_met()
	{
		if (not pfcluster_met_isLoaded) {
			if (pfcluster_met_branch != 0) {
				pfcluster_met_branch->GetEntry(index);
			} else { 
				printf("branch pfcluster_met_branch does not exist!\n");
				exit(1);
			}
			pfcluster_met_isLoaded = true;
		}
		return pfcluster_met_;
	}
	float &pfcluster_metphi()
	{
		if (not pfcluster_metphi_isLoaded) {
			if (pfcluster_metphi_branch != 0) {
				pfcluster_metphi_branch->GetEntry(index);
			} else { 
				printf("branch pfcluster_metphi_branch does not exist!\n");
				exit(1);
			}
			pfcluster_metphi_isLoaded = true;
		}
		return pfcluster_metphi_;
	}
	float &pfcluster_sumet()
	{
		if (not pfcluster_sumet_isLoaded) {
			if (pfcluster_sumet_branch != 0) {
				pfcluster_sumet_branch->GetEntry(index);
			} else { 
				printf("branch pfcluster_sumet_branch does not exist!\n");
				exit(1);
			}
			pfcluster_sumet_isLoaded = true;
		}
		return pfcluster_sumet_;
	}
	float &pfMet_met()
	{
		if (not pfMet_met_isLoaded) {
			if (pfMet_met_branch != 0) {
				pfMet_met_branch->GetEntry(index);
			} else { 
				printf("branch pfMet_met_branch does not exist!\n");
				exit(1);
			}
			pfMet_met_isLoaded = true;
		}
		return pfMet_met_;
	}
	float &pfMet_metPhi()
	{
		if (not pfMet_metPhi_isLoaded) {
			if (pfMet_metPhi_branch != 0) {
				pfMet_metPhi_branch->GetEntry(index);
			} else { 
				printf("branch pfMet_metPhi_branch does not exist!\n");
				exit(1);
			}
			pfMet_metPhi_isLoaded = true;
		}
		return pfMet_metPhi_;
	}
	float &pfMet_metPhi_type1cor()
	{
		if (not pfMet_metPhi_type1cor_isLoaded) {
			if (pfMet_metPhi_type1cor_branch != 0) {
				pfMet_metPhi_type1cor_branch->GetEntry(index);
			} else { 
				printf("branch pfMet_metPhi_type1cor_branch does not exist!\n");
				exit(1);
			}
			pfMet_metPhi_type1cor_isLoaded = true;
		}
		return pfMet_metPhi_type1cor_;
	}
	float &pfMet_metSig()
	{
		if (not pfMet_metSig_isLoaded) {
			if (pfMet_metSig_branch != 0) {
				pfMet_metSig_branch->GetEntry(index);
			} else { 
				printf("branch pfMet_metSig_branch does not exist!\n");
				exit(1);
			}
			pfMet_metSig_isLoaded = true;
		}
		return pfMet_metSig_;
	}
	float &pfMet_metSignificance()
	{
		if (not pfMet_metSignificance_isLoaded) {
			if (pfMet_metSignificance_branch != 0) {
				pfMet_metSignificance_branch->GetEntry(index);
			} else { 
				printf("branch pfMet_metSignificance_branch does not exist!\n");
				exit(1);
			}
			pfMet_metSignificance_isLoaded = true;
		}
		return pfMet_metSignificance_;
	}
	float &pfMet_met_type1cor()
	{
		if (not pfMet_met_type1cor_isLoaded) {
			if (pfMet_met_type1cor_branch != 0) {
				pfMet_met_type1cor_branch->GetEntry(index);
			} else { 
				printf("branch pfMet_met_type1cor_branch does not exist!\n");
				exit(1);
			}
			pfMet_met_type1cor_isLoaded = true;
		}
		return pfMet_met_type1cor_;
	}
	float &pfMet_sumet()
	{
		if (not pfMet_sumet_isLoaded) {
			if (pfMet_sumet_branch != 0) {
				pfMet_sumet_branch->GetEntry(index);
			} else { 
				printf("branch pfMet_sumet_branch does not exist!\n");
				exit(1);
			}
			pfMet_sumet_isLoaded = true;
		}
		return pfMet_sumet_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &pfcands_p4()
	{
		if (not pfcands_p4_isLoaded) {
			if (pfcands_p4_branch != 0) {
				pfcands_p4_branch->GetEntry(index);
			} else { 
				printf("branch pfcands_p4_branch does not exist!\n");
				exit(1);
			}
			pfcands_p4_isLoaded = true;
		}
		return pfcands_p4_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &pfjets_p4()
	{
		if (not pfjets_p4_isLoaded) {
			if (pfjets_p4_branch != 0) {
				pfjets_p4_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_p4_branch does not exist!\n");
				exit(1);
			}
			pfjets_p4_isLoaded = true;
		}
		return pfjets_p4_;
	}
	const vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > &hlt_trigObjs_p4()
	{
		if (not hlt_trigObjs_p4_isLoaded) {
			if (hlt_trigObjs_p4_branch != 0) {
				hlt_trigObjs_p4_branch->GetEntry(index);
			} else { 
				printf("branch hlt_trigObjs_p4_branch does not exist!\n");
				exit(1);
			}
			hlt_trigObjs_p4_isLoaded = true;
		}
		return hlt_trigObjs_p4_;
	}
	const vector<float> &calojets_eta()
	{
		if (not calojets_eta_isLoaded) {
			if (calojets_eta_branch != 0) {
				calojets_eta_branch->GetEntry(index);
			} else { 
				printf("branch calojets_eta_branch does not exist!\n");
				exit(1);
			}
			calojets_eta_isLoaded = true;
		}
		return calojets_eta_;
	}
	const vector<float> &calojets_phi()
	{
		if (not calojets_phi_isLoaded) {
			if (calojets_phi_branch != 0) {
				calojets_phi_branch->GetEntry(index);
			} else { 
				printf("branch calojets_phi_branch does not exist!\n");
				exit(1);
			}
			calojets_phi_isLoaded = true;
		}
		return calojets_phi_;
	}
	const vector<float> &calojets_pt()
	{
		if (not calojets_pt_isLoaded) {
			if (calojets_pt_branch != 0) {
				calojets_pt_branch->GetEntry(index);
			} else { 
				printf("branch calojets_pt_branch does not exist!\n");
				exit(1);
			}
			calojets_pt_isLoaded = true;
		}
		return calojets_pt_;
	}
	const vector<float> &twrs_ecalTime()
	{
		if (not twrs_ecalTime_isLoaded) {
			if (twrs_ecalTime_branch != 0) {
				twrs_ecalTime_branch->GetEntry(index);
			} else { 
				printf("branch twrs_ecalTime_branch does not exist!\n");
				exit(1);
			}
			twrs_ecalTime_isLoaded = true;
		}
		return twrs_ecalTime_;
	}
	const vector<float> &twrs_emEnergy()
	{
		if (not twrs_emEnergy_isLoaded) {
			if (twrs_emEnergy_branch != 0) {
				twrs_emEnergy_branch->GetEntry(index);
			} else { 
				printf("branch twrs_emEnergy_branch does not exist!\n");
				exit(1);
			}
			twrs_emEnergy_isLoaded = true;
		}
		return twrs_emEnergy_;
	}
	const vector<float> &twrs_emEt()
	{
		if (not twrs_emEt_isLoaded) {
			if (twrs_emEt_branch != 0) {
				twrs_emEt_branch->GetEntry(index);
			} else { 
				printf("branch twrs_emEt_branch does not exist!\n");
				exit(1);
			}
			twrs_emEt_isLoaded = true;
		}
		return twrs_emEt_;
	}
	const vector<float> &twrs_emEtcorr()
	{
		if (not twrs_emEtcorr_isLoaded) {
			if (twrs_emEtcorr_branch != 0) {
				twrs_emEtcorr_branch->GetEntry(index);
			} else { 
				printf("branch twrs_emEtcorr_branch does not exist!\n");
				exit(1);
			}
			twrs_emEtcorr_isLoaded = true;
		}
		return twrs_emEtcorr_;
	}
	const vector<float> &twrs_eta()
	{
		if (not twrs_eta_isLoaded) {
			if (twrs_eta_branch != 0) {
				twrs_eta_branch->GetEntry(index);
			} else { 
				printf("branch twrs_eta_branch does not exist!\n");
				exit(1);
			}
			twrs_eta_isLoaded = true;
		}
		return twrs_eta_;
	}
	const vector<float> &twrs_etacorr()
	{
		if (not twrs_etacorr_isLoaded) {
			if (twrs_etacorr_branch != 0) {
				twrs_etacorr_branch->GetEntry(index);
			} else { 
				printf("branch twrs_etacorr_branch does not exist!\n");
				exit(1);
			}
			twrs_etacorr_isLoaded = true;
		}
		return twrs_etacorr_;
	}
	const vector<float> &twrs_etcorr()
	{
		if (not twrs_etcorr_isLoaded) {
			if (twrs_etcorr_branch != 0) {
				twrs_etcorr_branch->GetEntry(index);
			} else { 
				printf("branch twrs_etcorr_branch does not exist!\n");
				exit(1);
			}
			twrs_etcorr_isLoaded = true;
		}
		return twrs_etcorr_;
	}
	const vector<float> &twrs_hadEnergy()
	{
		if (not twrs_hadEnergy_isLoaded) {
			if (twrs_hadEnergy_branch != 0) {
				twrs_hadEnergy_branch->GetEntry(index);
			} else { 
				printf("branch twrs_hadEnergy_branch does not exist!\n");
				exit(1);
			}
			twrs_hadEnergy_isLoaded = true;
		}
		return twrs_hadEnergy_;
	}
	const vector<float> &twrs_hadEt()
	{
		if (not twrs_hadEt_isLoaded) {
			if (twrs_hadEt_branch != 0) {
				twrs_hadEt_branch->GetEntry(index);
			} else { 
				printf("branch twrs_hadEt_branch does not exist!\n");
				exit(1);
			}
			twrs_hadEt_isLoaded = true;
		}
		return twrs_hadEt_;
	}
	const vector<float> &twrs_hadEtcorr()
	{
		if (not twrs_hadEtcorr_isLoaded) {
			if (twrs_hadEtcorr_branch != 0) {
				twrs_hadEtcorr_branch->GetEntry(index);
			} else { 
				printf("branch twrs_hadEtcorr_branch does not exist!\n");
				exit(1);
			}
			twrs_hadEtcorr_isLoaded = true;
		}
		return twrs_hadEtcorr_;
	}
	const vector<float> &twrs_hcalTime()
	{
		if (not twrs_hcalTime_isLoaded) {
			if (twrs_hcalTime_branch != 0) {
				twrs_hcalTime_branch->GetEntry(index);
			} else { 
				printf("branch twrs_hcalTime_branch does not exist!\n");
				exit(1);
			}
			twrs_hcalTime_isLoaded = true;
		}
		return twrs_hcalTime_;
	}
	const vector<float> &twrs_outerEnergy()
	{
		if (not twrs_outerEnergy_isLoaded) {
			if (twrs_outerEnergy_branch != 0) {
				twrs_outerEnergy_branch->GetEntry(index);
			} else { 
				printf("branch twrs_outerEnergy_branch does not exist!\n");
				exit(1);
			}
			twrs_outerEnergy_isLoaded = true;
		}
		return twrs_outerEnergy_;
	}
	const vector<float> &twrs_outerEt()
	{
		if (not twrs_outerEt_isLoaded) {
			if (twrs_outerEt_branch != 0) {
				twrs_outerEt_branch->GetEntry(index);
			} else { 
				printf("branch twrs_outerEt_branch does not exist!\n");
				exit(1);
			}
			twrs_outerEt_isLoaded = true;
		}
		return twrs_outerEt_;
	}
	const vector<float> &twrs_outerEtcorr()
	{
		if (not twrs_outerEtcorr_isLoaded) {
			if (twrs_outerEtcorr_branch != 0) {
				twrs_outerEtcorr_branch->GetEntry(index);
			} else { 
				printf("branch twrs_outerEtcorr_branch does not exist!\n");
				exit(1);
			}
			twrs_outerEtcorr_isLoaded = true;
		}
		return twrs_outerEtcorr_;
	}
	const vector<float> &twrs_pcorr()
	{
		if (not twrs_pcorr_isLoaded) {
			if (twrs_pcorr_branch != 0) {
				twrs_pcorr_branch->GetEntry(index);
			} else { 
				printf("branch twrs_pcorr_branch does not exist!\n");
				exit(1);
			}
			twrs_pcorr_isLoaded = true;
		}
		return twrs_pcorr_;
	}
	const vector<float> &twrs_phi()
	{
		if (not twrs_phi_isLoaded) {
			if (twrs_phi_branch != 0) {
				twrs_phi_branch->GetEntry(index);
			} else { 
				printf("branch twrs_phi_branch does not exist!\n");
				exit(1);
			}
			twrs_phi_isLoaded = true;
		}
		return twrs_phi_;
	}
	const vector<float> &twrs_phicorr()
	{
		if (not twrs_phicorr_isLoaded) {
			if (twrs_phicorr_branch != 0) {
				twrs_phicorr_branch->GetEntry(index);
			} else { 
				printf("branch twrs_phicorr_branch does not exist!\n");
				exit(1);
			}
			twrs_phicorr_isLoaded = true;
		}
		return twrs_phicorr_;
	}
	const vector<float> &twrs_spikeEt()
	{
		if (not twrs_spikeEt_isLoaded) {
			if (twrs_spikeEt_branch != 0) {
				twrs_spikeEt_branch->GetEntry(index);
			} else { 
				printf("branch twrs_spikeEt_branch does not exist!\n");
				exit(1);
			}
			twrs_spikeEt_isLoaded = true;
		}
		return twrs_spikeEt_;
	}
	const vector<float> &twrs_spikeR4()
	{
		if (not twrs_spikeR4_isLoaded) {
			if (twrs_spikeR4_branch != 0) {
				twrs_spikeR4_branch->GetEntry(index);
			} else { 
				printf("branch twrs_spikeR4_branch does not exist!\n");
				exit(1);
			}
			twrs_spikeR4_isLoaded = true;
		}
		return twrs_spikeR4_;
	}
	const vector<float> &evt_ecalmet_etaslice()
	{
		if (not evt_ecalmet_etaslice_isLoaded) {
			if (evt_ecalmet_etaslice_branch != 0) {
				evt_ecalmet_etaslice_branch->GetEntry(index);
			} else { 
				printf("branch evt_ecalmet_etaslice_branch does not exist!\n");
				exit(1);
			}
			evt_ecalmet_etaslice_isLoaded = true;
		}
		return evt_ecalmet_etaslice_;
	}
	const vector<float> &evt_ecalmet_etaslicePhi()
	{
		if (not evt_ecalmet_etaslicePhi_isLoaded) {
			if (evt_ecalmet_etaslicePhi_branch != 0) {
				evt_ecalmet_etaslicePhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_ecalmet_etaslicePhi_branch does not exist!\n");
				exit(1);
			}
			evt_ecalmet_etaslicePhi_isLoaded = true;
		}
		return evt_ecalmet_etaslicePhi_;
	}
	const vector<float> &evt_hcalmet_etaslice()
	{
		if (not evt_hcalmet_etaslice_isLoaded) {
			if (evt_hcalmet_etaslice_branch != 0) {
				evt_hcalmet_etaslice_branch->GetEntry(index);
			} else { 
				printf("branch evt_hcalmet_etaslice_branch does not exist!\n");
				exit(1);
			}
			evt_hcalmet_etaslice_isLoaded = true;
		}
		return evt_hcalmet_etaslice_;
	}
	const vector<float> &evt_hcalmet_etaslicePhi()
	{
		if (not evt_hcalmet_etaslicePhi_isLoaded) {
			if (evt_hcalmet_etaslicePhi_branch != 0) {
				evt_hcalmet_etaslicePhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_hcalmet_etaslicePhi_branch does not exist!\n");
				exit(1);
			}
			evt_hcalmet_etaslicePhi_isLoaded = true;
		}
		return evt_hcalmet_etaslicePhi_;
	}
	const vector<float> &evt_towermet_etaslice()
	{
		if (not evt_towermet_etaslice_isLoaded) {
			if (evt_towermet_etaslice_branch != 0) {
				evt_towermet_etaslice_branch->GetEntry(index);
			} else { 
				printf("branch evt_towermet_etaslice_branch does not exist!\n");
				exit(1);
			}
			evt_towermet_etaslice_isLoaded = true;
		}
		return evt_towermet_etaslice_;
	}
	const vector<float> &evt_towermet_etaslicePhi()
	{
		if (not evt_towermet_etaslicePhi_isLoaded) {
			if (evt_towermet_etaslicePhi_branch != 0) {
				evt_towermet_etaslicePhi_branch->GetEntry(index);
			} else { 
				printf("branch evt_towermet_etaslicePhi_branch does not exist!\n");
				exit(1);
			}
			evt_towermet_etaslicePhi_isLoaded = true;
		}
		return evt_towermet_etaslicePhi_;
	}
	const vector<float> &mus_met_deltax()
	{
		if (not mus_met_deltax_isLoaded) {
			if (mus_met_deltax_branch != 0) {
				mus_met_deltax_branch->GetEntry(index);
			} else { 
				printf("branch mus_met_deltax_branch does not exist!\n");
				exit(1);
			}
			mus_met_deltax_isLoaded = true;
		}
		return mus_met_deltax_;
	}
	const vector<float> &mus_met_deltay()
	{
		if (not mus_met_deltay_isLoaded) {
			if (mus_met_deltay_branch != 0) {
				mus_met_deltay_branch->GetEntry(index);
			} else { 
				printf("branch mus_met_deltay_branch does not exist!\n");
				exit(1);
			}
			mus_met_deltay_isLoaded = true;
		}
		return mus_met_deltay_;
	}
	const vector<float> &pfcands_mass()
	{
		if (not pfcands_mass_isLoaded) {
			if (pfcands_mass_branch != 0) {
				pfcands_mass_branch->GetEntry(index);
			} else { 
				printf("branch pfcands_mass_branch does not exist!\n");
				exit(1);
			}
			pfcands_mass_isLoaded = true;
		}
		return pfcands_mass_;
	}
	const vector<float> &pfcluster_energy()
	{
		if (not pfcluster_energy_isLoaded) {
			if (pfcluster_energy_branch != 0) {
				pfcluster_energy_branch->GetEntry(index);
			} else { 
				printf("branch pfcluster_energy_branch does not exist!\n");
				exit(1);
			}
			pfcluster_energy_isLoaded = true;
		}
		return pfcluster_energy_;
	}
	const vector<float> &pfcluster_et()
	{
		if (not pfcluster_et_isLoaded) {
			if (pfcluster_et_branch != 0) {
				pfcluster_et_branch->GetEntry(index);
			} else { 
				printf("branch pfcluster_et_branch does not exist!\n");
				exit(1);
			}
			pfcluster_et_isLoaded = true;
		}
		return pfcluster_et_;
	}
	const vector<float> &pfcluster_eta()
	{
		if (not pfcluster_eta_isLoaded) {
			if (pfcluster_eta_branch != 0) {
				pfcluster_eta_branch->GetEntry(index);
			} else { 
				printf("branch pfcluster_eta_branch does not exist!\n");
				exit(1);
			}
			pfcluster_eta_isLoaded = true;
		}
		return pfcluster_eta_;
	}
	const vector<float> &pfcluster_phi()
	{
		if (not pfcluster_phi_isLoaded) {
			if (pfcluster_phi_branch != 0) {
				pfcluster_phi_branch->GetEntry(index);
			} else { 
				printf("branch pfcluster_phi_branch does not exist!\n");
				exit(1);
			}
			pfcluster_phi_isLoaded = true;
		}
		return pfcluster_phi_;
	}
	const vector<float> &pfjets_area()
	{
		if (not pfjets_area_isLoaded) {
			if (pfjets_area_branch != 0) {
				pfjets_area_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_area_branch does not exist!\n");
				exit(1);
			}
			pfjets_area_isLoaded = true;
		}
		return pfjets_area_;
	}
	const vector<float> &pfjets_chargedEmE()
	{
		if (not pfjets_chargedEmE_isLoaded) {
			if (pfjets_chargedEmE_branch != 0) {
				pfjets_chargedEmE_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_chargedEmE_branch does not exist!\n");
				exit(1);
			}
			pfjets_chargedEmE_isLoaded = true;
		}
		return pfjets_chargedEmE_;
	}
	const vector<float> &pfjets_chargedHadronE()
	{
		if (not pfjets_chargedHadronE_isLoaded) {
			if (pfjets_chargedHadronE_branch != 0) {
				pfjets_chargedHadronE_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_chargedHadronE_branch does not exist!\n");
				exit(1);
			}
			pfjets_chargedHadronE_isLoaded = true;
		}
		return pfjets_chargedHadronE_;
	}
	const vector<float> &pfjets_electronE()
	{
		if (not pfjets_electronE_isLoaded) {
			if (pfjets_electronE_branch != 0) {
				pfjets_electronE_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_electronE_branch does not exist!\n");
				exit(1);
			}
			pfjets_electronE_isLoaded = true;
		}
		return pfjets_electronE_;
	}
	const vector<float> &pfjets_hfEmE()
	{
		if (not pfjets_hfEmE_isLoaded) {
			if (pfjets_hfEmE_branch != 0) {
				pfjets_hfEmE_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_hfEmE_branch does not exist!\n");
				exit(1);
			}
			pfjets_hfEmE_isLoaded = true;
		}
		return pfjets_hfEmE_;
	}
	const vector<float> &pfjets_hfHadronE()
	{
		if (not pfjets_hfHadronE_isLoaded) {
			if (pfjets_hfHadronE_branch != 0) {
				pfjets_hfHadronE_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_hfHadronE_branch does not exist!\n");
				exit(1);
			}
			pfjets_hfHadronE_isLoaded = true;
		}
		return pfjets_hfHadronE_;
	}
	const vector<float> &pfjets_mass()
	{
		if (not pfjets_mass_isLoaded) {
			if (pfjets_mass_branch != 0) {
				pfjets_mass_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_mass_branch does not exist!\n");
				exit(1);
			}
			pfjets_mass_isLoaded = true;
		}
		return pfjets_mass_;
	}
	const vector<float> &pfjets_muonE()
	{
		if (not pfjets_muonE_isLoaded) {
			if (pfjets_muonE_branch != 0) {
				pfjets_muonE_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_muonE_branch does not exist!\n");
				exit(1);
			}
			pfjets_muonE_isLoaded = true;
		}
		return pfjets_muonE_;
	}
	const vector<float> &pfjets_neutralEmE()
	{
		if (not pfjets_neutralEmE_isLoaded) {
			if (pfjets_neutralEmE_branch != 0) {
				pfjets_neutralEmE_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_neutralEmE_branch does not exist!\n");
				exit(1);
			}
			pfjets_neutralEmE_isLoaded = true;
		}
		return pfjets_neutralEmE_;
	}
	const vector<float> &pfjets_neutralHadronE()
	{
		if (not pfjets_neutralHadronE_isLoaded) {
			if (pfjets_neutralHadronE_branch != 0) {
				pfjets_neutralHadronE_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_neutralHadronE_branch does not exist!\n");
				exit(1);
			}
			pfjets_neutralHadronE_isLoaded = true;
		}
		return pfjets_neutralHadronE_;
	}
	const vector<float> &pfjets_photonE()
	{
		if (not pfjets_photonE_isLoaded) {
			if (pfjets_photonE_branch != 0) {
				pfjets_photonE_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_photonE_branch does not exist!\n");
				exit(1);
			}
			pfjets_photonE_isLoaded = true;
		}
		return pfjets_photonE_;
	}
	const vector<float> &pfjets_undoJEC()
	{
		if (not pfjets_undoJEC_isLoaded) {
			if (pfjets_undoJEC_branch != 0) {
				pfjets_undoJEC_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_undoJEC_branch does not exist!\n");
				exit(1);
			}
			pfjets_undoJEC_isLoaded = true;
		}
		return pfjets_undoJEC_;
	}
	const vector<vector<float> > &pfjets_bDiscriminators()
	{
		if (not pfjets_bDiscriminators_isLoaded) {
			if (pfjets_bDiscriminators_branch != 0) {
				pfjets_bDiscriminators_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_bDiscriminators_branch does not exist!\n");
				exit(1);
			}
			pfjets_bDiscriminators_isLoaded = true;
		}
		return pfjets_bDiscriminators_;
	}
	int &evt_bunchCrossing()
	{
		if (not evt_bunchCrossing_isLoaded) {
			if (evt_bunchCrossing_branch != 0) {
				evt_bunchCrossing_branch->GetEntry(index);
			} else { 
				printf("branch evt_bunchCrossing_branch does not exist!\n");
				exit(1);
			}
			evt_bunchCrossing_isLoaded = true;
		}
		return evt_bunchCrossing_;
	}
	int &evt_experimentType()
	{
		if (not evt_experimentType_isLoaded) {
			if (evt_experimentType_branch != 0) {
				evt_experimentType_branch->GetEntry(index);
			} else { 
				printf("branch evt_experimentType_branch does not exist!\n");
				exit(1);
			}
			evt_experimentType_isLoaded = true;
		}
		return evt_experimentType_;
	}
	int &evt_isRealData()
	{
		if (not evt_isRealData_isLoaded) {
			if (evt_isRealData_branch != 0) {
				evt_isRealData_branch->GetEntry(index);
			} else { 
				printf("branch evt_isRealData_branch does not exist!\n");
				exit(1);
			}
			evt_isRealData_isLoaded = true;
		}
		return evt_isRealData_;
	}
	int &evt_ntracks()
	{
		if (not evt_ntracks_isLoaded) {
			if (evt_ntracks_branch != 0) {
				evt_ntracks_branch->GetEntry(index);
			} else { 
				printf("branch evt_ntracks_branch does not exist!\n");
				exit(1);
			}
			evt_ntracks_isLoaded = true;
		}
		return evt_ntracks_;
	}
	int &evt_orbitNumber()
	{
		if (not evt_orbitNumber_isLoaded) {
			if (evt_orbitNumber_branch != 0) {
				evt_orbitNumber_branch->GetEntry(index);
			} else { 
				printf("branch evt_orbitNumber_branch does not exist!\n");
				exit(1);
			}
			evt_orbitNumber_isLoaded = true;
		}
		return evt_orbitNumber_;
	}
	int &evt_storeNumber()
	{
		if (not evt_storeNumber_isLoaded) {
			if (evt_storeNumber_branch != 0) {
				evt_storeNumber_branch->GetEntry(index);
			} else { 
				printf("branch evt_storeNumber_branch does not exist!\n");
				exit(1);
			}
			evt_storeNumber_isLoaded = true;
		}
		return evt_storeNumber_;
	}
	int &hcalnoise_GetRecHitCount()
	{
		if (not hcalnoise_GetRecHitCount_isLoaded) {
			if (hcalnoise_GetRecHitCount_branch != 0) {
				hcalnoise_GetRecHitCount_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_GetRecHitCount_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_GetRecHitCount_isLoaded = true;
		}
		return hcalnoise_GetRecHitCount_;
	}
	int &hcalnoise_GetRecHitCount15()
	{
		if (not hcalnoise_GetRecHitCount15_isLoaded) {
			if (hcalnoise_GetRecHitCount15_branch != 0) {
				hcalnoise_GetRecHitCount15_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_GetRecHitCount15_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_GetRecHitCount15_isLoaded = true;
		}
		return hcalnoise_GetRecHitCount15_;
	}
	int &hcalnoise_hbheIsoNoiseFilter()
	{
		if (not hcalnoise_hbheIsoNoiseFilter_isLoaded) {
			if (hcalnoise_hbheIsoNoiseFilter_branch != 0) {
				hcalnoise_hbheIsoNoiseFilter_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_hbheIsoNoiseFilter_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_hbheIsoNoiseFilter_isLoaded = true;
		}
		return hcalnoise_hbheIsoNoiseFilter_;
	}
	int &hcalnoise_maxHPDHits()
	{
		if (not hcalnoise_maxHPDHits_isLoaded) {
			if (hcalnoise_maxHPDHits_branch != 0) {
				hcalnoise_maxHPDHits_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_maxHPDHits_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_maxHPDHits_isLoaded = true;
		}
		return hcalnoise_maxHPDHits_;
	}
	int &hcalnoise_maxHPDNoOtherHits()
	{
		if (not hcalnoise_maxHPDNoOtherHits_isLoaded) {
			if (hcalnoise_maxHPDNoOtherHits_branch != 0) {
				hcalnoise_maxHPDNoOtherHits_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_maxHPDNoOtherHits_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_maxHPDNoOtherHits_isLoaded = true;
		}
		return hcalnoise_maxHPDNoOtherHits_;
	}
	int &hcalnoise_maxRBXHits()
	{
		if (not hcalnoise_maxRBXHits_isLoaded) {
			if (hcalnoise_maxRBXHits_branch != 0) {
				hcalnoise_maxRBXHits_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_maxRBXHits_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_maxRBXHits_isLoaded = true;
		}
		return hcalnoise_maxRBXHits_;
	}
	int &hcalnoise_maxZeros()
	{
		if (not hcalnoise_maxZeros_isLoaded) {
			if (hcalnoise_maxZeros_branch != 0) {
				hcalnoise_maxZeros_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_maxZeros_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_maxZeros_isLoaded = true;
		}
		return hcalnoise_maxZeros_;
	}
	int &hcalnoise_noiseFilterStatus()
	{
		if (not hcalnoise_noiseFilterStatus_isLoaded) {
			if (hcalnoise_noiseFilterStatus_branch != 0) {
				hcalnoise_noiseFilterStatus_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_noiseFilterStatus_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_noiseFilterStatus_isLoaded = true;
		}
		return hcalnoise_noiseFilterStatus_;
	}
	int &hcalnoise_noiseType()
	{
		if (not hcalnoise_noiseType_isLoaded) {
			if (hcalnoise_noiseType_branch != 0) {
				hcalnoise_noiseType_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_noiseType_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_noiseType_isLoaded = true;
		}
		return hcalnoise_noiseType_;
	}
	int &hcalnoise_num10GeVHits()
	{
		if (not hcalnoise_num10GeVHits_isLoaded) {
			if (hcalnoise_num10GeVHits_branch != 0) {
				hcalnoise_num10GeVHits_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_num10GeVHits_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_num10GeVHits_isLoaded = true;
		}
		return hcalnoise_num10GeVHits_;
	}
	int &hcalnoise_num25GeVHits()
	{
		if (not hcalnoise_num25GeVHits_isLoaded) {
			if (hcalnoise_num25GeVHits_branch != 0) {
				hcalnoise_num25GeVHits_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_num25GeVHits_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_num25GeVHits_isLoaded = true;
		}
		return hcalnoise_num25GeVHits_;
	}
	int &hcalnoise_numFlatNoiseChannels()
	{
		if (not hcalnoise_numFlatNoiseChannels_isLoaded) {
			if (hcalnoise_numFlatNoiseChannels_branch != 0) {
				hcalnoise_numFlatNoiseChannels_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_numFlatNoiseChannels_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_numFlatNoiseChannels_isLoaded = true;
		}
		return hcalnoise_numFlatNoiseChannels_;
	}
	int &hcalnoise_numIsolatedNoiseChannels()
	{
		if (not hcalnoise_numIsolatedNoiseChannels_isLoaded) {
			if (hcalnoise_numIsolatedNoiseChannels_branch != 0) {
				hcalnoise_numIsolatedNoiseChannels_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_numIsolatedNoiseChannels_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_numIsolatedNoiseChannels_isLoaded = true;
		}
		return hcalnoise_numIsolatedNoiseChannels_;
	}
	int &hcalnoise_numProblematicRBXs()
	{
		if (not hcalnoise_numProblematicRBXs_isLoaded) {
			if (hcalnoise_numProblematicRBXs_branch != 0) {
				hcalnoise_numProblematicRBXs_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_numProblematicRBXs_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_numProblematicRBXs_isLoaded = true;
		}
		return hcalnoise_numProblematicRBXs_;
	}
	int &hcalnoise_numSpikeNoiseChannels()
	{
		if (not hcalnoise_numSpikeNoiseChannels_isLoaded) {
			if (hcalnoise_numSpikeNoiseChannels_branch != 0) {
				hcalnoise_numSpikeNoiseChannels_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_numSpikeNoiseChannels_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_numSpikeNoiseChannels_isLoaded = true;
		}
		return hcalnoise_numSpikeNoiseChannels_;
	}
	int &hcalnoise_numTS4TS5NoiseChannels()
	{
		if (not hcalnoise_numTS4TS5NoiseChannels_isLoaded) {
			if (hcalnoise_numTS4TS5NoiseChannels_branch != 0) {
				hcalnoise_numTS4TS5NoiseChannels_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_numTS4TS5NoiseChannels_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_numTS4TS5NoiseChannels_isLoaded = true;
		}
		return hcalnoise_numTS4TS5NoiseChannels_;
	}
	int &hcalnoise_numTriangleNoiseChannels()
	{
		if (not hcalnoise_numTriangleNoiseChannels_isLoaded) {
			if (hcalnoise_numTriangleNoiseChannels_branch != 0) {
				hcalnoise_numTriangleNoiseChannels_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_numTriangleNoiseChannels_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_numTriangleNoiseChannels_isLoaded = true;
		}
		return hcalnoise_numTriangleNoiseChannels_;
	}
	int &hcalnoise_passHighLevelNoiseFilter()
	{
		if (not hcalnoise_passHighLevelNoiseFilter_isLoaded) {
			if (hcalnoise_passHighLevelNoiseFilter_branch != 0) {
				hcalnoise_passHighLevelNoiseFilter_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_passHighLevelNoiseFilter_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_passHighLevelNoiseFilter_isLoaded = true;
		}
		return hcalnoise_passHighLevelNoiseFilter_;
	}
	int &hcalnoise_passLooseNoiseFilter()
	{
		if (not hcalnoise_passLooseNoiseFilter_isLoaded) {
			if (hcalnoise_passLooseNoiseFilter_branch != 0) {
				hcalnoise_passLooseNoiseFilter_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_passLooseNoiseFilter_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_passLooseNoiseFilter_isLoaded = true;
		}
		return hcalnoise_passLooseNoiseFilter_;
	}
	int &hcalnoise_passTightNoiseFilter()
	{
		if (not hcalnoise_passTightNoiseFilter_isLoaded) {
			if (hcalnoise_passTightNoiseFilter_branch != 0) {
				hcalnoise_passTightNoiseFilter_branch->GetEntry(index);
			} else { 
				printf("branch hcalnoise_passTightNoiseFilter_branch does not exist!\n");
				exit(1);
			}
			hcalnoise_passTightNoiseFilter_isLoaded = true;
		}
		return hcalnoise_passTightNoiseFilter_;
	}
	const vector<int> &twrs_ieta()
	{
		if (not twrs_ieta_isLoaded) {
			if (twrs_ieta_branch != 0) {
				twrs_ieta_branch->GetEntry(index);
			} else { 
				printf("branch twrs_ieta_branch does not exist!\n");
				exit(1);
			}
			twrs_ieta_isLoaded = true;
		}
		return twrs_ieta_;
	}
	const vector<int> &twrs_iphi()
	{
		if (not twrs_iphi_isLoaded) {
			if (twrs_iphi_branch != 0) {
				twrs_iphi_branch->GetEntry(index);
			} else { 
				printf("branch twrs_iphi_branch does not exist!\n");
				exit(1);
			}
			twrs_iphi_isLoaded = true;
		}
		return twrs_iphi_;
	}
	const vector<int> &twrs_numCrystals()
	{
		if (not twrs_numCrystals_isLoaded) {
			if (twrs_numCrystals_branch != 0) {
				twrs_numCrystals_branch->GetEntry(index);
			} else { 
				printf("branch twrs_numCrystals_branch does not exist!\n");
				exit(1);
			}
			twrs_numCrystals_isLoaded = true;
		}
		return twrs_numCrystals_;
	}
	const vector<int> &mus_met_flag()
	{
		if (not mus_met_flag_isLoaded) {
			if (mus_met_flag_branch != 0) {
				mus_met_flag_branch->GetEntry(index);
			} else { 
				printf("branch mus_met_flag_branch does not exist!\n");
				exit(1);
			}
			mus_met_flag_isLoaded = true;
		}
		return mus_met_flag_;
	}
	const vector<int> &pfcands_charge()
	{
		if (not pfcands_charge_isLoaded) {
			if (pfcands_charge_branch != 0) {
				pfcands_charge_branch->GetEntry(index);
			} else { 
				printf("branch pfcands_charge_branch does not exist!\n");
				exit(1);
			}
			pfcands_charge_isLoaded = true;
		}
		return pfcands_charge_;
	}
	const vector<int> &pfcands_particleId()
	{
		if (not pfcands_particleId_isLoaded) {
			if (pfcands_particleId_branch != 0) {
				pfcands_particleId_branch->GetEntry(index);
			} else { 
				printf("branch pfcands_particleId_branch does not exist!\n");
				exit(1);
			}
			pfcands_particleId_isLoaded = true;
		}
		return pfcands_particleId_;
	}
	const vector<int> &pfcluster_layer()
	{
		if (not pfcluster_layer_isLoaded) {
			if (pfcluster_layer_branch != 0) {
				pfcluster_layer_branch->GetEntry(index);
			} else { 
				printf("branch pfcluster_layer_branch does not exist!\n");
				exit(1);
			}
			pfcluster_layer_isLoaded = true;
		}
		return pfcluster_layer_;
	}
	const vector<int> &pfjets_chargedHadronMultiplicity()
	{
		if (not pfjets_chargedHadronMultiplicity_isLoaded) {
			if (pfjets_chargedHadronMultiplicity_branch != 0) {
				pfjets_chargedHadronMultiplicity_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_chargedHadronMultiplicity_branch does not exist!\n");
				exit(1);
			}
			pfjets_chargedHadronMultiplicity_isLoaded = true;
		}
		return pfjets_chargedHadronMultiplicity_;
	}
	const vector<int> &pfjets_chargedMultiplicity()
	{
		if (not pfjets_chargedMultiplicity_isLoaded) {
			if (pfjets_chargedMultiplicity_branch != 0) {
				pfjets_chargedMultiplicity_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_chargedMultiplicity_branch does not exist!\n");
				exit(1);
			}
			pfjets_chargedMultiplicity_isLoaded = true;
		}
		return pfjets_chargedMultiplicity_;
	}
	const vector<int> &pfjets_electronMultiplicity()
	{
		if (not pfjets_electronMultiplicity_isLoaded) {
			if (pfjets_electronMultiplicity_branch != 0) {
				pfjets_electronMultiplicity_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_electronMultiplicity_branch does not exist!\n");
				exit(1);
			}
			pfjets_electronMultiplicity_isLoaded = true;
		}
		return pfjets_electronMultiplicity_;
	}
	const vector<int> &pfjets_muonMultiplicity()
	{
		if (not pfjets_muonMultiplicity_isLoaded) {
			if (pfjets_muonMultiplicity_branch != 0) {
				pfjets_muonMultiplicity_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_muonMultiplicity_branch does not exist!\n");
				exit(1);
			}
			pfjets_muonMultiplicity_isLoaded = true;
		}
		return pfjets_muonMultiplicity_;
	}
	const vector<int> &pfjets_neutralHadronMultiplicity()
	{
		if (not pfjets_neutralHadronMultiplicity_isLoaded) {
			if (pfjets_neutralHadronMultiplicity_branch != 0) {
				pfjets_neutralHadronMultiplicity_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_neutralHadronMultiplicity_branch does not exist!\n");
				exit(1);
			}
			pfjets_neutralHadronMultiplicity_isLoaded = true;
		}
		return pfjets_neutralHadronMultiplicity_;
	}
	const vector<int> &pfjets_neutralMultiplicity()
	{
		if (not pfjets_neutralMultiplicity_isLoaded) {
			if (pfjets_neutralMultiplicity_branch != 0) {
				pfjets_neutralMultiplicity_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_neutralMultiplicity_branch does not exist!\n");
				exit(1);
			}
			pfjets_neutralMultiplicity_isLoaded = true;
		}
		return pfjets_neutralMultiplicity_;
	}
	const vector<int> &pfjets_photonMultiplicity()
	{
		if (not pfjets_photonMultiplicity_isLoaded) {
			if (pfjets_photonMultiplicity_branch != 0) {
				pfjets_photonMultiplicity_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_photonMultiplicity_branch does not exist!\n");
				exit(1);
			}
			pfjets_photonMultiplicity_isLoaded = true;
		}
		return pfjets_photonMultiplicity_;
	}
	const vector<vector<int> > &hlt_trigObjs_id()
	{
		if (not hlt_trigObjs_id_isLoaded) {
			if (hlt_trigObjs_id_branch != 0) {
				hlt_trigObjs_id_branch->GetEntry(index);
			} else { 
				printf("branch hlt_trigObjs_id_branch does not exist!\n");
				exit(1);
			}
			hlt_trigObjs_id_isLoaded = true;
		}
		return hlt_trigObjs_id_;
	}
	const vector<vector<int> > &pfjets_pfcandIndicies()
	{
		if (not pfjets_pfcandIndicies_isLoaded) {
			if (pfjets_pfcandIndicies_branch != 0) {
				pfjets_pfcandIndicies_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_pfcandIndicies_branch does not exist!\n");
				exit(1);
			}
			pfjets_pfcandIndicies_isLoaded = true;
		}
		return pfjets_pfcandIndicies_;
	}
	unsigned int &evt_ntwrs()
	{
		if (not evt_ntwrs_isLoaded) {
			if (evt_ntwrs_branch != 0) {
				evt_ntwrs_branch->GetEntry(index);
			} else { 
				printf("branch evt_ntwrs_branch does not exist!\n");
				exit(1);
			}
			evt_ntwrs_isLoaded = true;
		}
		return evt_ntwrs_;
	}
	unsigned int &evt_detectorStatus()
	{
		if (not evt_detectorStatus_isLoaded) {
			if (evt_detectorStatus_branch != 0) {
				evt_detectorStatus_branch->GetEntry(index);
			} else { 
				printf("branch evt_detectorStatus_branch does not exist!\n");
				exit(1);
			}
			evt_detectorStatus_isLoaded = true;
		}
		return evt_detectorStatus_;
	}
	unsigned int &evt_event()
	{
		if (not evt_event_isLoaded) {
			if (evt_event_branch != 0) {
				evt_event_branch->GetEntry(index);
			} else { 
				printf("branch evt_event_branch does not exist!\n");
				exit(1);
			}
			evt_event_isLoaded = true;
		}
		return evt_event_;
	}
	unsigned int &evt_lumiBlock()
	{
		if (not evt_lumiBlock_isLoaded) {
			if (evt_lumiBlock_branch != 0) {
				evt_lumiBlock_branch->GetEntry(index);
			} else { 
				printf("branch evt_lumiBlock_branch does not exist!\n");
				exit(1);
			}
			evt_lumiBlock_isLoaded = true;
		}
		return evt_lumiBlock_;
	}
	unsigned int &evt_run()
	{
		if (not evt_run_isLoaded) {
			if (evt_run_branch != 0) {
				evt_run_branch->GetEntry(index);
			} else { 
				printf("branch evt_run_branch does not exist!\n");
				exit(1);
			}
			evt_run_isLoaded = true;
		}
		return evt_run_;
	}
	const vector<unsigned int> &twrs_detid()
	{
		if (not twrs_detid_isLoaded) {
			if (twrs_detid_branch != 0) {
				twrs_detid_branch->GetEntry(index);
			} else { 
				printf("branch twrs_detid_branch does not exist!\n");
				exit(1);
			}
			twrs_detid_isLoaded = true;
		}
		return twrs_detid_;
	}
	const vector<unsigned int> &twrs_numBadEcalCells()
	{
		if (not twrs_numBadEcalCells_isLoaded) {
			if (twrs_numBadEcalCells_branch != 0) {
				twrs_numBadEcalCells_branch->GetEntry(index);
			} else { 
				printf("branch twrs_numBadEcalCells_branch does not exist!\n");
				exit(1);
			}
			twrs_numBadEcalCells_isLoaded = true;
		}
		return twrs_numBadEcalCells_;
	}
	const vector<unsigned int> &twrs_numBadHcalCells()
	{
		if (not twrs_numBadHcalCells_isLoaded) {
			if (twrs_numBadHcalCells_branch != 0) {
				twrs_numBadHcalCells_branch->GetEntry(index);
			} else { 
				printf("branch twrs_numBadHcalCells_branch does not exist!\n");
				exit(1);
			}
			twrs_numBadHcalCells_isLoaded = true;
		}
		return twrs_numBadHcalCells_;
	}
	const vector<unsigned int> &twrs_numProblematicEcalCells()
	{
		if (not twrs_numProblematicEcalCells_isLoaded) {
			if (twrs_numProblematicEcalCells_branch != 0) {
				twrs_numProblematicEcalCells_branch->GetEntry(index);
			} else { 
				printf("branch twrs_numProblematicEcalCells_branch does not exist!\n");
				exit(1);
			}
			twrs_numProblematicEcalCells_isLoaded = true;
		}
		return twrs_numProblematicEcalCells_;
	}
	const vector<unsigned int> &twrs_numProblematicHcalCells()
	{
		if (not twrs_numProblematicHcalCells_isLoaded) {
			if (twrs_numProblematicHcalCells_branch != 0) {
				twrs_numProblematicHcalCells_branch->GetEntry(index);
			} else { 
				printf("branch twrs_numProblematicHcalCells_branch does not exist!\n");
				exit(1);
			}
			twrs_numProblematicHcalCells_isLoaded = true;
		}
		return twrs_numProblematicHcalCells_;
	}
	const vector<unsigned int> &twrs_numRecoveredEcalCells()
	{
		if (not twrs_numRecoveredEcalCells_isLoaded) {
			if (twrs_numRecoveredEcalCells_branch != 0) {
				twrs_numRecoveredEcalCells_branch->GetEntry(index);
			} else { 
				printf("branch twrs_numRecoveredEcalCells_branch does not exist!\n");
				exit(1);
			}
			twrs_numRecoveredEcalCells_isLoaded = true;
		}
		return twrs_numRecoveredEcalCells_;
	}
	const vector<unsigned int> &twrs_numRecoveredHcalCells()
	{
		if (not twrs_numRecoveredHcalCells_isLoaded) {
			if (twrs_numRecoveredHcalCells_branch != 0) {
				twrs_numRecoveredHcalCells_branch->GetEntry(index);
			} else { 
				printf("branch twrs_numRecoveredHcalCells_branch does not exist!\n");
				exit(1);
			}
			twrs_numRecoveredHcalCells_isLoaded = true;
		}
		return twrs_numRecoveredHcalCells_;
	}
	const vector<unsigned int> &hlt_prescales()
	{
		if (not hlt_prescales_isLoaded) {
			if (hlt_prescales_branch != 0) {
				hlt_prescales_branch->GetEntry(index);
			} else { 
				printf("branch hlt_prescales_branch does not exist!\n");
				exit(1);
			}
			hlt_prescales_isLoaded = true;
		}
		return hlt_prescales_;
	}
	bool passHLTTrigger(TString trigName) {
		int trigIndx;
		vector<TString>::const_iterator begin_it = hlt_trigNames().begin();
		vector<TString>::const_iterator end_it = hlt_trigNames().end();
		vector<TString>::const_iterator found_it = find(begin_it, end_it, trigName);
		if(found_it != end_it)
			trigIndx = found_it - begin_it;
		else {
			cout << "Cannot find Trigger " << trigName << endl; 
			return 0;
		}

	return hlt_bits().TestBitNumber(trigIndx);
	}
	float getbtagvalue(TString bDiscriminatorName, unsigned int jetIndx) {
		size_t bDiscriminatorIndx;
		vector<TString>::const_iterator begin_it = pfjets_bDiscriminatorNames().begin();
		vector<TString>::const_iterator end_it = pfjets_bDiscriminatorNames().end();
		vector<TString>::const_iterator found_it = find(begin_it, end_it, bDiscriminatorName);
		if(found_it != end_it)
			bDiscriminatorIndx = found_it - begin_it;
		else {
			cout << "Cannot find b discriminator " << bDiscriminatorName << endl; 
			return 0;
		}

		if (jetIndx < pfjets_bDiscriminators().size()) 
			return pfjets_bDiscriminators().at(jetIndx).at(bDiscriminatorIndx);
		else {
			cout << "Cannot find jet # "<< jetIndx << endl;
			return 0;
		}
	}

  static void progress( int nEventsTotal, int nEventsChain ){
    int period = 1000;
    if(nEventsTotal%1000 == 0) {
      // xterm magic from L. Vacavant and A. Cerri
      if (isatty(1)) {
        if( ( nEventsChain - nEventsTotal ) > period ){
          float frac = (float)nEventsTotal/(nEventsChain*0.01);
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
               "\033[0m\033[32m <---\033[0m\015", frac);
          fflush(stdout);
        }
        else {
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
                 "\033[0m\033[32m <---\033[0m\015", 100.);
          cout << endl;
        }
      }
    }
  }
  
};

#ifndef __CINT__
extern CMS3 cms3;
#endif

namespace tas {
	const TBits &hlt_bits();
	const vector<TString> &hlt_trigNames();
	const vector<TString> &pfjets_bDiscriminatorNames();
	const bool &hcalnoise_HasBadRBXTS4TS5();
	const bool &evt_EcalDeadCellBoundaryEnergyFilter();
	const bool &evt_EcalDeadCellTriggerPrimitiveFilter();
	const bool &evt_cscTightHaloFilter();
	const bool &evt_eeBadScFilter();
	const bool &evt_eeNoiseFilter();
	const bool &evt_goodVertices();
	const bool &evt_hbheFilter();
	const bool &evt_hbheFilterRun1();
	const bool &evt_hbheFilterRun2Loose();
	const bool &evt_hbheFilterRun2Tight();
	const bool &evt_trackingFailureFilter();
	const float &evt_bField();
	const float &hcalnoise_GetRecHitEnergy();
	const float &hcalnoise_GetRecHitEnergy15();
	const float &hcalnoise_GetTotalCalibCharge();
	const float &hcalnoise_TS4TS5NoiseSumE();
	const float &hcalnoise_TS4TS5NoiseSumEt();
	const float &hcalnoise_eventChargeFraction();
	const float &hcalnoise_eventEMEnergy();
	const float &hcalnoise_eventEMFraction();
	const float &hcalnoise_eventHadEnergy();
	const float &hcalnoise_eventTrackEnergy();
	const float &hcalnoise_flatNoiseSumE();
	const float &hcalnoise_flatNoiseSumEt();
	const float &hcalnoise_isolatedNoiseSumE();
	const float &hcalnoise_isolatedNoiseSumEt();
	const float &hcalnoise_max10GeVHitTime();
	const float &hcalnoise_max25GeVHitTime();
	const float &hcalnoise_maxE10TS();
	const float &hcalnoise_maxE2Over10TS();
	const float &hcalnoise_maxE2TS();
	const float &hcalnoise_min10GeVHitTime();
	const float &hcalnoise_min25GeVHitTime();
	const float &hcalnoise_minE10TS();
	const float &hcalnoise_minE2Over10TS();
	const float &hcalnoise_minE2TS();
	const float &hcalnoise_minHPDEMF();
	const float &hcalnoise_minRBXEMF();
	const float &hcalnoise_rms10GeVHitTime();
	const float &hcalnoise_rms25GeVHitTime();
	const float &hcalnoise_spikeNoiseSumE();
	const float &hcalnoise_spikeNoiseSumEt();
	const float &hcalnoise_triangleNoiseSumE();
	const float &hcalnoise_triangleNoiseSumEt();
	const float &evt_ecalendcapm_met();
	const float &evt_ecalendcapm_metPhi();
	const float &evt_ecalendcapp_met();
	const float &evt_ecalendcapp_metPhi();
	const float &evt_ecalmet();
	const float &evt_ecalmetPhi();
	const float &evt_endcapm_met();
	const float &evt_endcapm_metPhi();
	const float &evt_endcapp_met();
	const float &evt_endcapp_metPhi();
	const float &evt_hcalendcapm_met();
	const float &evt_hcalendcapm_metPhi();
	const float &evt_hcalendcapp_met();
	const float &evt_hcalendcapp_metPhi();
	const float &evt_hcalmet();
	const float &evt_hcalmetPhi();
	const float &evt_met();
	const float &evt_met_EtGt3();
	const float &evt_metHO();
	const float &evt_metHOPhi();
	const float &evt_metHOSig();
	const float &evt_metMuonCorr();
	const float &evt_metMuonCorrPhi();
	const float &evt_metMuonCorrSig();
	const float &evt_metMuonJESCorr();
	const float &evt_metMuonJESCorrPhi();
	const float &evt_metMuonJESCorrSig();
	const float &evt_metNoHF();
	const float &evt_metNoHFHO();
	const float &evt_metNoHFHOPhi();
	const float &evt_metNoHFHOSig();
	const float &evt_metNoHFPhi();
	const float &evt_metNoHFSig();
	const float &evt_metOpt();
	const float &evt_metOptHO();
	const float &evt_metOptHOPhi();
	const float &evt_metOptHOSig();
	const float &evt_metOptNoHF();
	const float &evt_metOptNoHFHO();
	const float &evt_metOptNoHFHOPhi();
	const float &evt_metOptNoHFHOSig();
	const float &evt_metOptNoHFPhi();
	const float &evt_metOptNoHFSig();
	const float &evt_metOptPhi();
	const float &evt_metOptSig();
	const float &evt_metPhi();
	const float &evt_metPhi_EtGt3();
	const float &evt_metSig();
	const float &evt_sumet();
	const float &evt_sumet_EtGt3();
	const float &evt_sumetHO();
	const float &evt_sumetMuonCorr();
	const float &evt_sumetMuonJESCorr();
	const float &evt_sumetNoHF();
	const float &evt_sumetNoHFHO();
	const float &evt_sumetOpt();
	const float &evt_sumetOptHO();
	const float &evt_sumetOptNoHF();
	const float &evt_sumetOptNoHFHO();
	const float &pfCaloMet_met();
	const float &pfCaloMet_metPhi();
	const float &pfCaloMet_metPhi_type1cor();
	const float &pfCaloMet_metSig();
	const float &pfCaloMet_metSignificance();
	const float &pfCaloMet_met_type1cor();
	const float &pfCaloMet_sumet();
	const float &pfChMet_met();
	const float &pfChMet_metPhi();
	const float &pfChMet_metPhi_type1cor();
	const float &pfChMet_metSig();
	const float &pfChMet_metSignificance();
	const float &pfChMet_met_type1cor();
	const float &pfChMet_sumet();
	const float &pfcluster_met();
	const float &pfcluster_metphi();
	const float &pfcluster_sumet();
	const float &pfMet_met();
	const float &pfMet_metPhi();
	const float &pfMet_metPhi_type1cor();
	const float &pfMet_metSig();
	const float &pfMet_metSignificance();
	const float &pfMet_met_type1cor();
	const float &pfMet_sumet();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &pfcands_p4();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &pfjets_p4();
	const vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > &hlt_trigObjs_p4();
	const vector<float> &calojets_eta();
	const vector<float> &calojets_phi();
	const vector<float> &calojets_pt();
	const vector<float> &twrs_ecalTime();
	const vector<float> &twrs_emEnergy();
	const vector<float> &twrs_emEt();
	const vector<float> &twrs_emEtcorr();
	const vector<float> &twrs_eta();
	const vector<float> &twrs_etacorr();
	const vector<float> &twrs_etcorr();
	const vector<float> &twrs_hadEnergy();
	const vector<float> &twrs_hadEt();
	const vector<float> &twrs_hadEtcorr();
	const vector<float> &twrs_hcalTime();
	const vector<float> &twrs_outerEnergy();
	const vector<float> &twrs_outerEt();
	const vector<float> &twrs_outerEtcorr();
	const vector<float> &twrs_pcorr();
	const vector<float> &twrs_phi();
	const vector<float> &twrs_phicorr();
	const vector<float> &twrs_spikeEt();
	const vector<float> &twrs_spikeR4();
	const vector<float> &evt_ecalmet_etaslice();
	const vector<float> &evt_ecalmet_etaslicePhi();
	const vector<float> &evt_hcalmet_etaslice();
	const vector<float> &evt_hcalmet_etaslicePhi();
	const vector<float> &evt_towermet_etaslice();
	const vector<float> &evt_towermet_etaslicePhi();
	const vector<float> &mus_met_deltax();
	const vector<float> &mus_met_deltay();
	const vector<float> &pfcands_mass();
	const vector<float> &pfcluster_energy();
	const vector<float> &pfcluster_et();
	const vector<float> &pfcluster_eta();
	const vector<float> &pfcluster_phi();
	const vector<float> &pfjets_area();
	const vector<float> &pfjets_chargedEmE();
	const vector<float> &pfjets_chargedHadronE();
	const vector<float> &pfjets_electronE();
	const vector<float> &pfjets_hfEmE();
	const vector<float> &pfjets_hfHadronE();
	const vector<float> &pfjets_mass();
	const vector<float> &pfjets_muonE();
	const vector<float> &pfjets_neutralEmE();
	const vector<float> &pfjets_neutralHadronE();
	const vector<float> &pfjets_photonE();
	const vector<float> &pfjets_undoJEC();
	const vector<vector<float> > &pfjets_bDiscriminators();
	const int &evt_bunchCrossing();
	const int &evt_experimentType();
	const int &evt_isRealData();
	const int &evt_ntracks();
	const int &evt_orbitNumber();
	const int &evt_storeNumber();
	const int &hcalnoise_GetRecHitCount();
	const int &hcalnoise_GetRecHitCount15();
	const int &hcalnoise_hbheIsoNoiseFilter();
	const int &hcalnoise_maxHPDHits();
	const int &hcalnoise_maxHPDNoOtherHits();
	const int &hcalnoise_maxRBXHits();
	const int &hcalnoise_maxZeros();
	const int &hcalnoise_noiseFilterStatus();
	const int &hcalnoise_noiseType();
	const int &hcalnoise_num10GeVHits();
	const int &hcalnoise_num25GeVHits();
	const int &hcalnoise_numFlatNoiseChannels();
	const int &hcalnoise_numIsolatedNoiseChannels();
	const int &hcalnoise_numProblematicRBXs();
	const int &hcalnoise_numSpikeNoiseChannels();
	const int &hcalnoise_numTS4TS5NoiseChannels();
	const int &hcalnoise_numTriangleNoiseChannels();
	const int &hcalnoise_passHighLevelNoiseFilter();
	const int &hcalnoise_passLooseNoiseFilter();
	const int &hcalnoise_passTightNoiseFilter();
	const vector<int> &twrs_ieta();
	const vector<int> &twrs_iphi();
	const vector<int> &twrs_numCrystals();
	const vector<int> &mus_met_flag();
	const vector<int> &pfcands_charge();
	const vector<int> &pfcands_particleId();
	const vector<int> &pfcluster_layer();
	const vector<int> &pfjets_chargedHadronMultiplicity();
	const vector<int> &pfjets_chargedMultiplicity();
	const vector<int> &pfjets_electronMultiplicity();
	const vector<int> &pfjets_muonMultiplicity();
	const vector<int> &pfjets_neutralHadronMultiplicity();
	const vector<int> &pfjets_neutralMultiplicity();
	const vector<int> &pfjets_photonMultiplicity();
	const vector<vector<int> > &hlt_trigObjs_id();
	const vector<vector<int> > &pfjets_pfcandIndicies();
	const unsigned int &evt_ntwrs();
	const unsigned int &evt_detectorStatus();
	const unsigned int &evt_event();
	const unsigned int &evt_lumiBlock();
	const unsigned int &evt_run();
	const vector<unsigned int> &twrs_detid();
	const vector<unsigned int> &twrs_numBadEcalCells();
	const vector<unsigned int> &twrs_numBadHcalCells();
	const vector<unsigned int> &twrs_numProblematicEcalCells();
	const vector<unsigned int> &twrs_numProblematicHcalCells();
	const vector<unsigned int> &twrs_numRecoveredEcalCells();
	const vector<unsigned int> &twrs_numRecoveredHcalCells();
	const vector<unsigned int> &hlt_prescales();
	bool passHLTTrigger(TString trigName);
	float getbtagvalue(TString bDiscriminatorName, unsigned int jetIndx);
}
#endif
