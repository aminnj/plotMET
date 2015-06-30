#include "CMS3.h"
CMS3 cms3;
namespace tas {
	TBits &hlt_bits() { return cms3.hlt_bits(); }
	vector<TString> &hlt_trigNames() { return cms3.hlt_trigNames(); }
	bool &hcalnoise_HasBadRBXTS4TS5() { return cms3.hcalnoise_HasBadRBXTS4TS5(); }
	bool &evt_cscTightHaloFilter() { return cms3.evt_cscTightHaloFilter(); }
	bool &evt_hbheFilter() { return cms3.evt_hbheFilter(); }
	bool &evt_hbheFilterRun1() { return cms3.evt_hbheFilterRun1(); }
	bool &evt_hbheFilterRun2Loose() { return cms3.evt_hbheFilterRun2Loose(); }
	bool &evt_hbheFilterRun2Tight() { return cms3.evt_hbheFilterRun2Tight(); }
	float &evt_bField() { return cms3.evt_bField(); }
	float &hcalnoise_GetRecHitEnergy() { return cms3.hcalnoise_GetRecHitEnergy(); }
	float &hcalnoise_GetRecHitEnergy15() { return cms3.hcalnoise_GetRecHitEnergy15(); }
	float &hcalnoise_GetTotalCalibCharge() { return cms3.hcalnoise_GetTotalCalibCharge(); }
	float &hcalnoise_TS4TS5NoiseSumE() { return cms3.hcalnoise_TS4TS5NoiseSumE(); }
	float &hcalnoise_TS4TS5NoiseSumEt() { return cms3.hcalnoise_TS4TS5NoiseSumEt(); }
	float &hcalnoise_eventChargeFraction() { return cms3.hcalnoise_eventChargeFraction(); }
	float &hcalnoise_eventEMEnergy() { return cms3.hcalnoise_eventEMEnergy(); }
	float &hcalnoise_eventEMFraction() { return cms3.hcalnoise_eventEMFraction(); }
	float &hcalnoise_eventHadEnergy() { return cms3.hcalnoise_eventHadEnergy(); }
	float &hcalnoise_eventTrackEnergy() { return cms3.hcalnoise_eventTrackEnergy(); }
	float &hcalnoise_flatNoiseSumE() { return cms3.hcalnoise_flatNoiseSumE(); }
	float &hcalnoise_flatNoiseSumEt() { return cms3.hcalnoise_flatNoiseSumEt(); }
	float &hcalnoise_isolatedNoiseSumE() { return cms3.hcalnoise_isolatedNoiseSumE(); }
	float &hcalnoise_isolatedNoiseSumEt() { return cms3.hcalnoise_isolatedNoiseSumEt(); }
	float &hcalnoise_max10GeVHitTime() { return cms3.hcalnoise_max10GeVHitTime(); }
	float &hcalnoise_max25GeVHitTime() { return cms3.hcalnoise_max25GeVHitTime(); }
	float &hcalnoise_maxE10TS() { return cms3.hcalnoise_maxE10TS(); }
	float &hcalnoise_maxE2Over10TS() { return cms3.hcalnoise_maxE2Over10TS(); }
	float &hcalnoise_maxE2TS() { return cms3.hcalnoise_maxE2TS(); }
	float &hcalnoise_min10GeVHitTime() { return cms3.hcalnoise_min10GeVHitTime(); }
	float &hcalnoise_min25GeVHitTime() { return cms3.hcalnoise_min25GeVHitTime(); }
	float &hcalnoise_minE10TS() { return cms3.hcalnoise_minE10TS(); }
	float &hcalnoise_minE2Over10TS() { return cms3.hcalnoise_minE2Over10TS(); }
	float &hcalnoise_minE2TS() { return cms3.hcalnoise_minE2TS(); }
	float &hcalnoise_minHPDEMF() { return cms3.hcalnoise_minHPDEMF(); }
	float &hcalnoise_minRBXEMF() { return cms3.hcalnoise_minRBXEMF(); }
	float &hcalnoise_rms10GeVHitTime() { return cms3.hcalnoise_rms10GeVHitTime(); }
	float &hcalnoise_rms25GeVHitTime() { return cms3.hcalnoise_rms25GeVHitTime(); }
	float &hcalnoise_spikeNoiseSumE() { return cms3.hcalnoise_spikeNoiseSumE(); }
	float &hcalnoise_spikeNoiseSumEt() { return cms3.hcalnoise_spikeNoiseSumEt(); }
	float &hcalnoise_triangleNoiseSumE() { return cms3.hcalnoise_triangleNoiseSumE(); }
	float &hcalnoise_triangleNoiseSumEt() { return cms3.hcalnoise_triangleNoiseSumEt(); }
	float &evt_ecalendcapm_met() { return cms3.evt_ecalendcapm_met(); }
	float &evt_ecalendcapm_metPhi() { return cms3.evt_ecalendcapm_metPhi(); }
	float &evt_ecalendcapp_met() { return cms3.evt_ecalendcapp_met(); }
	float &evt_ecalendcapp_metPhi() { return cms3.evt_ecalendcapp_metPhi(); }
	float &evt_ecalmet() { return cms3.evt_ecalmet(); }
	float &evt_ecalmetPhi() { return cms3.evt_ecalmetPhi(); }
	float &evt_endcapm_met() { return cms3.evt_endcapm_met(); }
	float &evt_endcapm_metPhi() { return cms3.evt_endcapm_metPhi(); }
	float &evt_endcapp_met() { return cms3.evt_endcapp_met(); }
	float &evt_endcapp_metPhi() { return cms3.evt_endcapp_metPhi(); }
	float &evt_hcalendcapm_met() { return cms3.evt_hcalendcapm_met(); }
	float &evt_hcalendcapm_metPhi() { return cms3.evt_hcalendcapm_metPhi(); }
	float &evt_hcalendcapp_met() { return cms3.evt_hcalendcapp_met(); }
	float &evt_hcalendcapp_metPhi() { return cms3.evt_hcalendcapp_metPhi(); }
	float &evt_hcalmet() { return cms3.evt_hcalmet(); }
	float &evt_hcalmetPhi() { return cms3.evt_hcalmetPhi(); }
	float &evt_met() { return cms3.evt_met(); }
	float &evt_met_EtGt3() { return cms3.evt_met_EtGt3(); }
	float &evt_metHO() { return cms3.evt_metHO(); }
	float &evt_metHOPhi() { return cms3.evt_metHOPhi(); }
	float &evt_metHOSig() { return cms3.evt_metHOSig(); }
	float &evt_metMuonCorr() { return cms3.evt_metMuonCorr(); }
	float &evt_metMuonCorrPhi() { return cms3.evt_metMuonCorrPhi(); }
	float &evt_metMuonCorrSig() { return cms3.evt_metMuonCorrSig(); }
	float &evt_metMuonJESCorr() { return cms3.evt_metMuonJESCorr(); }
	float &evt_metMuonJESCorrPhi() { return cms3.evt_metMuonJESCorrPhi(); }
	float &evt_metMuonJESCorrSig() { return cms3.evt_metMuonJESCorrSig(); }
	float &evt_metNoHF() { return cms3.evt_metNoHF(); }
	float &evt_metNoHFHO() { return cms3.evt_metNoHFHO(); }
	float &evt_metNoHFHOPhi() { return cms3.evt_metNoHFHOPhi(); }
	float &evt_metNoHFHOSig() { return cms3.evt_metNoHFHOSig(); }
	float &evt_metNoHFPhi() { return cms3.evt_metNoHFPhi(); }
	float &evt_metNoHFSig() { return cms3.evt_metNoHFSig(); }
	float &evt_metOpt() { return cms3.evt_metOpt(); }
	float &evt_metOptHO() { return cms3.evt_metOptHO(); }
	float &evt_metOptHOPhi() { return cms3.evt_metOptHOPhi(); }
	float &evt_metOptHOSig() { return cms3.evt_metOptHOSig(); }
	float &evt_metOptNoHF() { return cms3.evt_metOptNoHF(); }
	float &evt_metOptNoHFHO() { return cms3.evt_metOptNoHFHO(); }
	float &evt_metOptNoHFHOPhi() { return cms3.evt_metOptNoHFHOPhi(); }
	float &evt_metOptNoHFHOSig() { return cms3.evt_metOptNoHFHOSig(); }
	float &evt_metOptNoHFPhi() { return cms3.evt_metOptNoHFPhi(); }
	float &evt_metOptNoHFSig() { return cms3.evt_metOptNoHFSig(); }
	float &evt_metOptPhi() { return cms3.evt_metOptPhi(); }
	float &evt_metOptSig() { return cms3.evt_metOptSig(); }
	float &evt_metPhi() { return cms3.evt_metPhi(); }
	float &evt_metPhi_EtGt3() { return cms3.evt_metPhi_EtGt3(); }
	float &evt_metSig() { return cms3.evt_metSig(); }
	float &evt_sumet() { return cms3.evt_sumet(); }
	float &evt_sumet_EtGt3() { return cms3.evt_sumet_EtGt3(); }
	float &evt_sumetHO() { return cms3.evt_sumetHO(); }
	float &evt_sumetMuonCorr() { return cms3.evt_sumetMuonCorr(); }
	float &evt_sumetMuonJESCorr() { return cms3.evt_sumetMuonJESCorr(); }
	float &evt_sumetNoHF() { return cms3.evt_sumetNoHF(); }
	float &evt_sumetNoHFHO() { return cms3.evt_sumetNoHFHO(); }
	float &evt_sumetOpt() { return cms3.evt_sumetOpt(); }
	float &evt_sumetOptHO() { return cms3.evt_sumetOptHO(); }
	float &evt_sumetOptNoHF() { return cms3.evt_sumetOptNoHF(); }
	float &evt_sumetOptNoHFHO() { return cms3.evt_sumetOptNoHFHO(); }
	float &pfCaloMet_met() { return cms3.pfCaloMet_met(); }
	float &pfCaloMet_metPhi() { return cms3.pfCaloMet_metPhi(); }
	float &pfCaloMet_metPhi_type1cor() { return cms3.pfCaloMet_metPhi_type1cor(); }
	float &pfCaloMet_metSig() { return cms3.pfCaloMet_metSig(); }
	float &pfCaloMet_metSignificance() { return cms3.pfCaloMet_metSignificance(); }
	float &pfCaloMet_met_type1cor() { return cms3.pfCaloMet_met_type1cor(); }
	float &pfCaloMet_sumet() { return cms3.pfCaloMet_sumet(); }
	float &pfcluster_met() { return cms3.pfcluster_met(); }
	float &pfcluster_metphi() { return cms3.pfcluster_metphi(); }
	float &pfcluster_sumet() { return cms3.pfcluster_sumet(); }
	float &pfMet_met() { return cms3.pfMet_met(); }
	float &pfMet_metPhi() { return cms3.pfMet_metPhi(); }
	float &pfMet_metPhi_type1cor() { return cms3.pfMet_metPhi_type1cor(); }
	float &pfMet_metSig() { return cms3.pfMet_metSig(); }
	float &pfMet_metSignificance() { return cms3.pfMet_metSignificance(); }
	float &pfMet_met_type1cor() { return cms3.pfMet_met_type1cor(); }
	float &pfMet_sumet() { return cms3.pfMet_sumet(); }
	vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > &hlt_trigObjs_p4() { return cms3.hlt_trigObjs_p4(); }
	vector<float> &calojets_eta() { return cms3.calojets_eta(); }
	vector<float> &calojets_phi() { return cms3.calojets_phi(); }
	vector<float> &calojets_pt() { return cms3.calojets_pt(); }
	vector<float> &twrs_ecalTime() { return cms3.twrs_ecalTime(); }
	vector<float> &twrs_emEnergy() { return cms3.twrs_emEnergy(); }
	vector<float> &twrs_emEt() { return cms3.twrs_emEt(); }
	vector<float> &twrs_emEtcorr() { return cms3.twrs_emEtcorr(); }
	vector<float> &twrs_eta() { return cms3.twrs_eta(); }
	vector<float> &twrs_etacorr() { return cms3.twrs_etacorr(); }
	vector<float> &twrs_etcorr() { return cms3.twrs_etcorr(); }
	vector<float> &twrs_hadEnergy() { return cms3.twrs_hadEnergy(); }
	vector<float> &twrs_hadEt() { return cms3.twrs_hadEt(); }
	vector<float> &twrs_hadEtcorr() { return cms3.twrs_hadEtcorr(); }
	vector<float> &twrs_hcalTime() { return cms3.twrs_hcalTime(); }
	vector<float> &twrs_outerEnergy() { return cms3.twrs_outerEnergy(); }
	vector<float> &twrs_outerEt() { return cms3.twrs_outerEt(); }
	vector<float> &twrs_outerEtcorr() { return cms3.twrs_outerEtcorr(); }
	vector<float> &twrs_pcorr() { return cms3.twrs_pcorr(); }
	vector<float> &twrs_phi() { return cms3.twrs_phi(); }
	vector<float> &twrs_phicorr() { return cms3.twrs_phicorr(); }
	vector<float> &twrs_spikeEt() { return cms3.twrs_spikeEt(); }
	vector<float> &twrs_spikeR4() { return cms3.twrs_spikeR4(); }
	vector<float> &evt_ecalmet_etaslice() { return cms3.evt_ecalmet_etaslice(); }
	vector<float> &evt_ecalmet_etaslicePhi() { return cms3.evt_ecalmet_etaslicePhi(); }
	vector<float> &evt_hcalmet_etaslice() { return cms3.evt_hcalmet_etaslice(); }
	vector<float> &evt_hcalmet_etaslicePhi() { return cms3.evt_hcalmet_etaslicePhi(); }
	vector<float> &evt_towermet_etaslice() { return cms3.evt_towermet_etaslice(); }
	vector<float> &evt_towermet_etaslicePhi() { return cms3.evt_towermet_etaslicePhi(); }
	vector<float> &mus_met_deltax() { return cms3.mus_met_deltax(); }
	vector<float> &mus_met_deltay() { return cms3.mus_met_deltay(); }
	vector<float> &pfcluster_energy() { return cms3.pfcluster_energy(); }
	vector<float> &pfcluster_et() { return cms3.pfcluster_et(); }
	vector<float> &pfcluster_eta() { return cms3.pfcluster_eta(); }
	vector<float> &pfcluster_phi() { return cms3.pfcluster_phi(); }
	int &evt_bunchCrossing() { return cms3.evt_bunchCrossing(); }
	int &evt_experimentType() { return cms3.evt_experimentType(); }
	int &evt_isRealData() { return cms3.evt_isRealData(); }
	int &evt_orbitNumber() { return cms3.evt_orbitNumber(); }
	int &evt_storeNumber() { return cms3.evt_storeNumber(); }
	int &hcalnoise_GetRecHitCount() { return cms3.hcalnoise_GetRecHitCount(); }
	int &hcalnoise_GetRecHitCount15() { return cms3.hcalnoise_GetRecHitCount15(); }
	int &hcalnoise_maxHPDHits() { return cms3.hcalnoise_maxHPDHits(); }
	int &hcalnoise_maxHPDNoOtherHits() { return cms3.hcalnoise_maxHPDNoOtherHits(); }
	int &hcalnoise_maxRBXHits() { return cms3.hcalnoise_maxRBXHits(); }
	int &hcalnoise_maxZeros() { return cms3.hcalnoise_maxZeros(); }
	int &hcalnoise_noiseFilterStatus() { return cms3.hcalnoise_noiseFilterStatus(); }
	int &hcalnoise_noiseType() { return cms3.hcalnoise_noiseType(); }
	int &hcalnoise_num10GeVHits() { return cms3.hcalnoise_num10GeVHits(); }
	int &hcalnoise_num25GeVHits() { return cms3.hcalnoise_num25GeVHits(); }
	int &hcalnoise_numFlatNoiseChannels() { return cms3.hcalnoise_numFlatNoiseChannels(); }
	int &hcalnoise_numIsolatedNoiseChannels() { return cms3.hcalnoise_numIsolatedNoiseChannels(); }
	int &hcalnoise_numProblematicRBXs() { return cms3.hcalnoise_numProblematicRBXs(); }
	int &hcalnoise_numSpikeNoiseChannels() { return cms3.hcalnoise_numSpikeNoiseChannels(); }
	int &hcalnoise_numTS4TS5NoiseChannels() { return cms3.hcalnoise_numTS4TS5NoiseChannels(); }
	int &hcalnoise_numTriangleNoiseChannels() { return cms3.hcalnoise_numTriangleNoiseChannels(); }
	int &hcalnoise_passHighLevelNoiseFilter() { return cms3.hcalnoise_passHighLevelNoiseFilter(); }
	int &hcalnoise_passLooseNoiseFilter() { return cms3.hcalnoise_passLooseNoiseFilter(); }
	int &hcalnoise_passTightNoiseFilter() { return cms3.hcalnoise_passTightNoiseFilter(); }
	vector<int> &twrs_numCrystals() { return cms3.twrs_numCrystals(); }
	vector<int> &mus_met_flag() { return cms3.mus_met_flag(); }
	vector<int> &pfcluster_layer() { return cms3.pfcluster_layer(); }
	vector<vector<int> > &hlt_trigObjs_id() { return cms3.hlt_trigObjs_id(); }
	unsigned int &evt_ntwrs() { return cms3.evt_ntwrs(); }
	unsigned int &evt_detectorStatus() { return cms3.evt_detectorStatus(); }
	unsigned int &evt_event() { return cms3.evt_event(); }
	unsigned int &evt_lumiBlock() { return cms3.evt_lumiBlock(); }
	unsigned int &evt_run() { return cms3.evt_run(); }
	vector<unsigned int> &twrs_detid() { return cms3.twrs_detid(); }
	vector<unsigned int> &twrs_numBadEcalCells() { return cms3.twrs_numBadEcalCells(); }
	vector<unsigned int> &twrs_numBadHcalCells() { return cms3.twrs_numBadHcalCells(); }
	vector<unsigned int> &twrs_numProblematicEcalCells() { return cms3.twrs_numProblematicEcalCells(); }
	vector<unsigned int> &twrs_numProblematicHcalCells() { return cms3.twrs_numProblematicHcalCells(); }
	vector<unsigned int> &twrs_numRecoveredEcalCells() { return cms3.twrs_numRecoveredEcalCells(); }
	vector<unsigned int> &twrs_numRecoveredHcalCells() { return cms3.twrs_numRecoveredHcalCells(); }
	vector<unsigned int> &hlt_prescales() { return cms3.hlt_prescales(); }
	bool passHLTTrigger(TString trigName) { return cms3.passHLTTrigger(trigName); }
}
