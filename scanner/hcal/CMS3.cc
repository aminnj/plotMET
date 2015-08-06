#include "CMS3.h"
CMS3 cms3;
namespace tas {
	const TBits &hlt_bits() { return cms3.hlt_bits(); }
	const vector<TString> &hlt_trigNames() { return cms3.hlt_trigNames(); }
	const vector<TString> &pfjets_bDiscriminatorNames() { return cms3.pfjets_bDiscriminatorNames(); }
	const bool &hcalnoise_HasBadRBXTS4TS5() { return cms3.hcalnoise_HasBadRBXTS4TS5(); }
	const bool &evt_EcalDeadCellBoundaryEnergyFilter() { return cms3.evt_EcalDeadCellBoundaryEnergyFilter(); }
	const bool &evt_EcalDeadCellTriggerPrimitiveFilter() { return cms3.evt_EcalDeadCellTriggerPrimitiveFilter(); }
	const bool &evt_cscTightHaloFilter() { return cms3.evt_cscTightHaloFilter(); }
	const bool &evt_eeBadScFilter() { return cms3.evt_eeBadScFilter(); }
	const bool &evt_eeNoiseFilter() { return cms3.evt_eeNoiseFilter(); }
	const bool &evt_goodVertices() { return cms3.evt_goodVertices(); }
	const bool &evt_hbheFilter() { return cms3.evt_hbheFilter(); }
	const bool &evt_hbheFilterRun1() { return cms3.evt_hbheFilterRun1(); }
	const bool &evt_hbheFilterRun2Loose() { return cms3.evt_hbheFilterRun2Loose(); }
	const bool &evt_hbheFilterRun2Tight() { return cms3.evt_hbheFilterRun2Tight(); }
	const bool &evt_trackingFailureFilter() { return cms3.evt_trackingFailureFilter(); }
	const float &evt_bField() { return cms3.evt_bField(); }
	const float &hcalnoise_GetRecHitEnergy() { return cms3.hcalnoise_GetRecHitEnergy(); }
	const float &hcalnoise_GetRecHitEnergy15() { return cms3.hcalnoise_GetRecHitEnergy15(); }
	const float &hcalnoise_GetTotalCalibCharge() { return cms3.hcalnoise_GetTotalCalibCharge(); }
	const float &hcalnoise_TS4TS5NoiseSumE() { return cms3.hcalnoise_TS4TS5NoiseSumE(); }
	const float &hcalnoise_TS4TS5NoiseSumEt() { return cms3.hcalnoise_TS4TS5NoiseSumEt(); }
	const float &hcalnoise_eventChargeFraction() { return cms3.hcalnoise_eventChargeFraction(); }
	const float &hcalnoise_eventEMEnergy() { return cms3.hcalnoise_eventEMEnergy(); }
	const float &hcalnoise_eventEMFraction() { return cms3.hcalnoise_eventEMFraction(); }
	const float &hcalnoise_eventHadEnergy() { return cms3.hcalnoise_eventHadEnergy(); }
	const float &hcalnoise_eventTrackEnergy() { return cms3.hcalnoise_eventTrackEnergy(); }
	const float &hcalnoise_flatNoiseSumE() { return cms3.hcalnoise_flatNoiseSumE(); }
	const float &hcalnoise_flatNoiseSumEt() { return cms3.hcalnoise_flatNoiseSumEt(); }
	const float &hcalnoise_isolatedNoiseSumE() { return cms3.hcalnoise_isolatedNoiseSumE(); }
	const float &hcalnoise_isolatedNoiseSumEt() { return cms3.hcalnoise_isolatedNoiseSumEt(); }
	const float &hcalnoise_max10GeVHitTime() { return cms3.hcalnoise_max10GeVHitTime(); }
	const float &hcalnoise_max25GeVHitTime() { return cms3.hcalnoise_max25GeVHitTime(); }
	const float &hcalnoise_maxE10TS() { return cms3.hcalnoise_maxE10TS(); }
	const float &hcalnoise_maxE2Over10TS() { return cms3.hcalnoise_maxE2Over10TS(); }
	const float &hcalnoise_maxE2TS() { return cms3.hcalnoise_maxE2TS(); }
	const float &hcalnoise_min10GeVHitTime() { return cms3.hcalnoise_min10GeVHitTime(); }
	const float &hcalnoise_min25GeVHitTime() { return cms3.hcalnoise_min25GeVHitTime(); }
	const float &hcalnoise_minE10TS() { return cms3.hcalnoise_minE10TS(); }
	const float &hcalnoise_minE2Over10TS() { return cms3.hcalnoise_minE2Over10TS(); }
	const float &hcalnoise_minE2TS() { return cms3.hcalnoise_minE2TS(); }
	const float &hcalnoise_minHPDEMF() { return cms3.hcalnoise_minHPDEMF(); }
	const float &hcalnoise_minRBXEMF() { return cms3.hcalnoise_minRBXEMF(); }
	const float &hcalnoise_rms10GeVHitTime() { return cms3.hcalnoise_rms10GeVHitTime(); }
	const float &hcalnoise_rms25GeVHitTime() { return cms3.hcalnoise_rms25GeVHitTime(); }
	const float &hcalnoise_spikeNoiseSumE() { return cms3.hcalnoise_spikeNoiseSumE(); }
	const float &hcalnoise_spikeNoiseSumEt() { return cms3.hcalnoise_spikeNoiseSumEt(); }
	const float &hcalnoise_triangleNoiseSumE() { return cms3.hcalnoise_triangleNoiseSumE(); }
	const float &hcalnoise_triangleNoiseSumEt() { return cms3.hcalnoise_triangleNoiseSumEt(); }
	const float &evt_ecalendcapm_met() { return cms3.evt_ecalendcapm_met(); }
	const float &evt_ecalendcapm_metPhi() { return cms3.evt_ecalendcapm_metPhi(); }
	const float &evt_ecalendcapp_met() { return cms3.evt_ecalendcapp_met(); }
	const float &evt_ecalendcapp_metPhi() { return cms3.evt_ecalendcapp_metPhi(); }
	const float &evt_ecalmet() { return cms3.evt_ecalmet(); }
	const float &evt_ecalmetPhi() { return cms3.evt_ecalmetPhi(); }
	const float &evt_endcapm_met() { return cms3.evt_endcapm_met(); }
	const float &evt_endcapm_metPhi() { return cms3.evt_endcapm_metPhi(); }
	const float &evt_endcapp_met() { return cms3.evt_endcapp_met(); }
	const float &evt_endcapp_metPhi() { return cms3.evt_endcapp_metPhi(); }
	const float &evt_hcalendcapm_met() { return cms3.evt_hcalendcapm_met(); }
	const float &evt_hcalendcapm_metPhi() { return cms3.evt_hcalendcapm_metPhi(); }
	const float &evt_hcalendcapp_met() { return cms3.evt_hcalendcapp_met(); }
	const float &evt_hcalendcapp_metPhi() { return cms3.evt_hcalendcapp_metPhi(); }
	const float &evt_hcalmet() { return cms3.evt_hcalmet(); }
	const float &evt_hcalmetPhi() { return cms3.evt_hcalmetPhi(); }
	const float &evt_met() { return cms3.evt_met(); }
	const float &evt_met_EtGt3() { return cms3.evt_met_EtGt3(); }
	const float &evt_metHO() { return cms3.evt_metHO(); }
	const float &evt_metHOPhi() { return cms3.evt_metHOPhi(); }
	const float &evt_metHOSig() { return cms3.evt_metHOSig(); }
	const float &evt_metMuonCorr() { return cms3.evt_metMuonCorr(); }
	const float &evt_metMuonCorrPhi() { return cms3.evt_metMuonCorrPhi(); }
	const float &evt_metMuonCorrSig() { return cms3.evt_metMuonCorrSig(); }
	const float &evt_metMuonJESCorr() { return cms3.evt_metMuonJESCorr(); }
	const float &evt_metMuonJESCorrPhi() { return cms3.evt_metMuonJESCorrPhi(); }
	const float &evt_metMuonJESCorrSig() { return cms3.evt_metMuonJESCorrSig(); }
	const float &evt_metNoHF() { return cms3.evt_metNoHF(); }
	const float &evt_metNoHFHO() { return cms3.evt_metNoHFHO(); }
	const float &evt_metNoHFHOPhi() { return cms3.evt_metNoHFHOPhi(); }
	const float &evt_metNoHFHOSig() { return cms3.evt_metNoHFHOSig(); }
	const float &evt_metNoHFPhi() { return cms3.evt_metNoHFPhi(); }
	const float &evt_metNoHFSig() { return cms3.evt_metNoHFSig(); }
	const float &evt_metOpt() { return cms3.evt_metOpt(); }
	const float &evt_metOptHO() { return cms3.evt_metOptHO(); }
	const float &evt_metOptHOPhi() { return cms3.evt_metOptHOPhi(); }
	const float &evt_metOptHOSig() { return cms3.evt_metOptHOSig(); }
	const float &evt_metOptNoHF() { return cms3.evt_metOptNoHF(); }
	const float &evt_metOptNoHFHO() { return cms3.evt_metOptNoHFHO(); }
	const float &evt_metOptNoHFHOPhi() { return cms3.evt_metOptNoHFHOPhi(); }
	const float &evt_metOptNoHFHOSig() { return cms3.evt_metOptNoHFHOSig(); }
	const float &evt_metOptNoHFPhi() { return cms3.evt_metOptNoHFPhi(); }
	const float &evt_metOptNoHFSig() { return cms3.evt_metOptNoHFSig(); }
	const float &evt_metOptPhi() { return cms3.evt_metOptPhi(); }
	const float &evt_metOptSig() { return cms3.evt_metOptSig(); }
	const float &evt_metPhi() { return cms3.evt_metPhi(); }
	const float &evt_metPhi_EtGt3() { return cms3.evt_metPhi_EtGt3(); }
	const float &evt_metSig() { return cms3.evt_metSig(); }
	const float &evt_sumet() { return cms3.evt_sumet(); }
	const float &evt_sumet_EtGt3() { return cms3.evt_sumet_EtGt3(); }
	const float &evt_sumetHO() { return cms3.evt_sumetHO(); }
	const float &evt_sumetMuonCorr() { return cms3.evt_sumetMuonCorr(); }
	const float &evt_sumetMuonJESCorr() { return cms3.evt_sumetMuonJESCorr(); }
	const float &evt_sumetNoHF() { return cms3.evt_sumetNoHF(); }
	const float &evt_sumetNoHFHO() { return cms3.evt_sumetNoHFHO(); }
	const float &evt_sumetOpt() { return cms3.evt_sumetOpt(); }
	const float &evt_sumetOptHO() { return cms3.evt_sumetOptHO(); }
	const float &evt_sumetOptNoHF() { return cms3.evt_sumetOptNoHF(); }
	const float &evt_sumetOptNoHFHO() { return cms3.evt_sumetOptNoHFHO(); }
	const float &pfCaloMet_met() { return cms3.pfCaloMet_met(); }
	const float &pfCaloMet_metPhi() { return cms3.pfCaloMet_metPhi(); }
	const float &pfCaloMet_metPhi_type1cor() { return cms3.pfCaloMet_metPhi_type1cor(); }
	const float &pfCaloMet_metSig() { return cms3.pfCaloMet_metSig(); }
	const float &pfCaloMet_metSignificance() { return cms3.pfCaloMet_metSignificance(); }
	const float &pfCaloMet_met_type1cor() { return cms3.pfCaloMet_met_type1cor(); }
	const float &pfCaloMet_sumet() { return cms3.pfCaloMet_sumet(); }
	const float &pfChMet_met() { return cms3.pfChMet_met(); }
	const float &pfChMet_metPhi() { return cms3.pfChMet_metPhi(); }
	const float &pfChMet_metPhi_type1cor() { return cms3.pfChMet_metPhi_type1cor(); }
	const float &pfChMet_metSig() { return cms3.pfChMet_metSig(); }
	const float &pfChMet_metSignificance() { return cms3.pfChMet_metSignificance(); }
	const float &pfChMet_met_type1cor() { return cms3.pfChMet_met_type1cor(); }
	const float &pfChMet_sumet() { return cms3.pfChMet_sumet(); }
	const float &pfcluster_met() { return cms3.pfcluster_met(); }
	const float &pfcluster_metphi() { return cms3.pfcluster_metphi(); }
	const float &pfcluster_sumet() { return cms3.pfcluster_sumet(); }
	const float &pfMet_met() { return cms3.pfMet_met(); }
	const float &pfMet_metPhi() { return cms3.pfMet_metPhi(); }
	const float &pfMet_metPhi_type1cor() { return cms3.pfMet_metPhi_type1cor(); }
	const float &pfMet_metSig() { return cms3.pfMet_metSig(); }
	const float &pfMet_metSignificance() { return cms3.pfMet_metSignificance(); }
	const float &pfMet_met_type1cor() { return cms3.pfMet_met_type1cor(); }
	const float &pfMet_sumet() { return cms3.pfMet_sumet(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &pfcands_p4() { return cms3.pfcands_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &pfjets_p4() { return cms3.pfjets_p4(); }
	const vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > &hlt_trigObjs_p4() { return cms3.hlt_trigObjs_p4(); }
	const vector<float> &calojets_eta() { return cms3.calojets_eta(); }
	const vector<float> &calojets_phi() { return cms3.calojets_phi(); }
	const vector<float> &calojets_pt() { return cms3.calojets_pt(); }
	const vector<float> &twrs_ecalTime() { return cms3.twrs_ecalTime(); }
	const vector<float> &twrs_emEnergy() { return cms3.twrs_emEnergy(); }
	const vector<float> &twrs_emEt() { return cms3.twrs_emEt(); }
	const vector<float> &twrs_emEtcorr() { return cms3.twrs_emEtcorr(); }
	const vector<float> &twrs_eta() { return cms3.twrs_eta(); }
	const vector<float> &twrs_etacorr() { return cms3.twrs_etacorr(); }
	const vector<float> &twrs_etcorr() { return cms3.twrs_etcorr(); }
	const vector<float> &twrs_hadEnergy() { return cms3.twrs_hadEnergy(); }
	const vector<float> &twrs_hadEt() { return cms3.twrs_hadEt(); }
	const vector<float> &twrs_hadEtcorr() { return cms3.twrs_hadEtcorr(); }
	const vector<float> &twrs_hcalTime() { return cms3.twrs_hcalTime(); }
	const vector<float> &twrs_outerEnergy() { return cms3.twrs_outerEnergy(); }
	const vector<float> &twrs_outerEt() { return cms3.twrs_outerEt(); }
	const vector<float> &twrs_outerEtcorr() { return cms3.twrs_outerEtcorr(); }
	const vector<float> &twrs_pcorr() { return cms3.twrs_pcorr(); }
	const vector<float> &twrs_phi() { return cms3.twrs_phi(); }
	const vector<float> &twrs_phicorr() { return cms3.twrs_phicorr(); }
	const vector<float> &twrs_spikeEt() { return cms3.twrs_spikeEt(); }
	const vector<float> &twrs_spikeR4() { return cms3.twrs_spikeR4(); }
	const vector<float> &evt_ecalmet_etaslice() { return cms3.evt_ecalmet_etaslice(); }
	const vector<float> &evt_ecalmet_etaslicePhi() { return cms3.evt_ecalmet_etaslicePhi(); }
	const vector<float> &evt_hcalmet_etaslice() { return cms3.evt_hcalmet_etaslice(); }
	const vector<float> &evt_hcalmet_etaslicePhi() { return cms3.evt_hcalmet_etaslicePhi(); }
	const vector<float> &evt_towermet_etaslice() { return cms3.evt_towermet_etaslice(); }
	const vector<float> &evt_towermet_etaslicePhi() { return cms3.evt_towermet_etaslicePhi(); }
	const vector<float> &mus_met_deltax() { return cms3.mus_met_deltax(); }
	const vector<float> &mus_met_deltay() { return cms3.mus_met_deltay(); }
	const vector<float> &pfcands_mass() { return cms3.pfcands_mass(); }
	const vector<float> &pfcluster_energy() { return cms3.pfcluster_energy(); }
	const vector<float> &pfcluster_et() { return cms3.pfcluster_et(); }
	const vector<float> &pfcluster_eta() { return cms3.pfcluster_eta(); }
	const vector<float> &pfcluster_phi() { return cms3.pfcluster_phi(); }
	const vector<float> &pfjets_area() { return cms3.pfjets_area(); }
	const vector<float> &pfjets_chargedEmE() { return cms3.pfjets_chargedEmE(); }
	const vector<float> &pfjets_chargedHadronE() { return cms3.pfjets_chargedHadronE(); }
	const vector<float> &pfjets_electronE() { return cms3.pfjets_electronE(); }
	const vector<float> &pfjets_hfEmE() { return cms3.pfjets_hfEmE(); }
	const vector<float> &pfjets_hfHadronE() { return cms3.pfjets_hfHadronE(); }
	const vector<float> &pfjets_mass() { return cms3.pfjets_mass(); }
	const vector<float> &pfjets_muonE() { return cms3.pfjets_muonE(); }
	const vector<float> &pfjets_neutralEmE() { return cms3.pfjets_neutralEmE(); }
	const vector<float> &pfjets_neutralHadronE() { return cms3.pfjets_neutralHadronE(); }
	const vector<float> &pfjets_photonE() { return cms3.pfjets_photonE(); }
	const vector<float> &pfjets_undoJEC() { return cms3.pfjets_undoJEC(); }
	const vector<vector<float> > &pfjets_bDiscriminators() { return cms3.pfjets_bDiscriminators(); }
	const int &evt_bunchCrossing() { return cms3.evt_bunchCrossing(); }
	const int &evt_experimentType() { return cms3.evt_experimentType(); }
	const int &evt_isRealData() { return cms3.evt_isRealData(); }
	const int &evt_ntracks() { return cms3.evt_ntracks(); }
	const int &evt_orbitNumber() { return cms3.evt_orbitNumber(); }
	const int &evt_storeNumber() { return cms3.evt_storeNumber(); }
	const int &hcalnoise_GetRecHitCount() { return cms3.hcalnoise_GetRecHitCount(); }
	const int &hcalnoise_GetRecHitCount15() { return cms3.hcalnoise_GetRecHitCount15(); }
	const int &hcalnoise_hbheIsoNoiseFilter() { return cms3.hcalnoise_hbheIsoNoiseFilter(); }
	const int &hcalnoise_maxHPDHits() { return cms3.hcalnoise_maxHPDHits(); }
	const int &hcalnoise_maxHPDNoOtherHits() { return cms3.hcalnoise_maxHPDNoOtherHits(); }
	const int &hcalnoise_maxRBXHits() { return cms3.hcalnoise_maxRBXHits(); }
	const int &hcalnoise_maxZeros() { return cms3.hcalnoise_maxZeros(); }
	const int &hcalnoise_noiseFilterStatus() { return cms3.hcalnoise_noiseFilterStatus(); }
	const int &hcalnoise_noiseType() { return cms3.hcalnoise_noiseType(); }
	const int &hcalnoise_num10GeVHits() { return cms3.hcalnoise_num10GeVHits(); }
	const int &hcalnoise_num25GeVHits() { return cms3.hcalnoise_num25GeVHits(); }
	const int &hcalnoise_numFlatNoiseChannels() { return cms3.hcalnoise_numFlatNoiseChannels(); }
	const int &hcalnoise_numIsolatedNoiseChannels() { return cms3.hcalnoise_numIsolatedNoiseChannels(); }
	const int &hcalnoise_numProblematicRBXs() { return cms3.hcalnoise_numProblematicRBXs(); }
	const int &hcalnoise_numSpikeNoiseChannels() { return cms3.hcalnoise_numSpikeNoiseChannels(); }
	const int &hcalnoise_numTS4TS5NoiseChannels() { return cms3.hcalnoise_numTS4TS5NoiseChannels(); }
	const int &hcalnoise_numTriangleNoiseChannels() { return cms3.hcalnoise_numTriangleNoiseChannels(); }
	const int &hcalnoise_passHighLevelNoiseFilter() { return cms3.hcalnoise_passHighLevelNoiseFilter(); }
	const int &hcalnoise_passLooseNoiseFilter() { return cms3.hcalnoise_passLooseNoiseFilter(); }
	const int &hcalnoise_passTightNoiseFilter() { return cms3.hcalnoise_passTightNoiseFilter(); }
	const vector<int> &twrs_ieta() { return cms3.twrs_ieta(); }
	const vector<int> &twrs_iphi() { return cms3.twrs_iphi(); }
	const vector<int> &twrs_numCrystals() { return cms3.twrs_numCrystals(); }
	const vector<int> &mus_met_flag() { return cms3.mus_met_flag(); }
	const vector<int> &pfcands_charge() { return cms3.pfcands_charge(); }
	const vector<int> &pfcands_particleId() { return cms3.pfcands_particleId(); }
	const vector<int> &pfcluster_layer() { return cms3.pfcluster_layer(); }
	const vector<int> &pfjets_chargedHadronMultiplicity() { return cms3.pfjets_chargedHadronMultiplicity(); }
	const vector<int> &pfjets_chargedMultiplicity() { return cms3.pfjets_chargedMultiplicity(); }
	const vector<int> &pfjets_electronMultiplicity() { return cms3.pfjets_electronMultiplicity(); }
	const vector<int> &pfjets_muonMultiplicity() { return cms3.pfjets_muonMultiplicity(); }
	const vector<int> &pfjets_neutralHadronMultiplicity() { return cms3.pfjets_neutralHadronMultiplicity(); }
	const vector<int> &pfjets_neutralMultiplicity() { return cms3.pfjets_neutralMultiplicity(); }
	const vector<int> &pfjets_photonMultiplicity() { return cms3.pfjets_photonMultiplicity(); }
	const vector<vector<int> > &hlt_trigObjs_id() { return cms3.hlt_trigObjs_id(); }
	const vector<vector<int> > &pfjets_pfcandIndicies() { return cms3.pfjets_pfcandIndicies(); }
	const unsigned int &evt_ntwrs() { return cms3.evt_ntwrs(); }
	const unsigned int &evt_detectorStatus() { return cms3.evt_detectorStatus(); }
	const unsigned int &evt_event() { return cms3.evt_event(); }
	const unsigned int &evt_lumiBlock() { return cms3.evt_lumiBlock(); }
	const unsigned int &evt_run() { return cms3.evt_run(); }
	const vector<unsigned int> &twrs_detid() { return cms3.twrs_detid(); }
	const vector<unsigned int> &twrs_numBadEcalCells() { return cms3.twrs_numBadEcalCells(); }
	const vector<unsigned int> &twrs_numBadHcalCells() { return cms3.twrs_numBadHcalCells(); }
	const vector<unsigned int> &twrs_numProblematicEcalCells() { return cms3.twrs_numProblematicEcalCells(); }
	const vector<unsigned int> &twrs_numProblematicHcalCells() { return cms3.twrs_numProblematicHcalCells(); }
	const vector<unsigned int> &twrs_numRecoveredEcalCells() { return cms3.twrs_numRecoveredEcalCells(); }
	const vector<unsigned int> &twrs_numRecoveredHcalCells() { return cms3.twrs_numRecoveredHcalCells(); }
	const vector<unsigned int> &hlt_prescales() { return cms3.hlt_prescales(); }
	bool passHLTTrigger(TString trigName) { return cms3.passHLTTrigger(trigName); }
	float getbtagvalue(TString bDiscriminatorName, unsigned int jetIndx) { return cms3.getbtagvalue( bDiscriminatorName, jetIndx); }
}
