# Cutvalue-Optimization-recently-done-with-Mu2e-Flavor-Group

This repository includes some code sections and images from one of my recent projects at University of California, Berkeley and Lawrence Berkeley National Laboratory. All this work was done with valuable guidance from the members of the Mu2e Flavor Group at LBNL. I would like to convey special thanks to my daily supervisor, Dr. Richard Bonventre.

**OVERVIEW OF CONTENTS**

**(1)** **_Motivation : A look at the distributions of (a) total energies deposited (E), and (b) energies deposited per unit distance (dE/dx) by both protons and electrons passing through the straws of the Mu2e detector_**
_(**Images** : "Proton_electron_deposit_energy_histograms.png" and "Proton_electron_dEdx_histograms.png" created from Mu2e data stored in some Flavor Group TTrees)_

  > The straw hits allow us to reconstruct both total energy and dE/dx values. Bounds ("cuts") can be placed on these characteristic values to roughly distinguish between different particles and therefore these can be used to identify the particles that hit the straws. The electron hits constitute the desired "signal" for this experiment and the proton hits are considered to be undesired "background". Due to the overlap in the center between proton and electron distributions in both the above plots, it is not possible to choose a cut value that can segregate the electron and proton hits with 100% accuracy. 
Neither do we want to unwantedly ignore too many electron hits by keeping the cut value very low, nor do we want to incorrectly mistake protons for electrons by keeping the cut value too high. So the task at hand is to optimize the cut value so that the efficiency of signal detection is maximized while keeping the background rejection as efficient as possible.

  > Only an energy (E) cut value of about 3 keV was being used previously, but it was found through this project that a particular combination of both E and dE/dx cut values can be used simultaneously to further enhance background rejection without causing a drop in signal acceptance. 

**(2)** **_Optimization of the deposit energy cutvalue and the dE/dx cutvalue in the Mu2e straw detector's particle identification system to arrive at a suitable combination that simultaneously maximizes signal (electron) efficiency and background (proton) rejection_**

  > First done **manually**, using general ROOT code to iterate and compare efficiencies for both E and dE/dx on an interdependent basis. ROC curves were generated in the process and a comparison has been presented in the image. Notice that the red curve corresponding to the combined cut lies above the individual cut curves, indicating better performance. The exact cut-value combination can be viewed in the runtime output only, so they have been included as a comment in the code file below.
  _(**code file** : "Energy_cuts_by_hand.C") (**images** : Comparison of ROC curves in "ROC_curve_E_dEdx_both_comparison_by_hand.png") (The ROC curve if only an energy cut is used as before in "Deposit_energy_ROC.C" and "ROC_deposit_energy_cutvalues.png")_
  
  > Then used **machine learning algorithm** templates on TMVA | ROOT to develop training scripts that do the same optimization much faster. 
  _(**code file** : "Energy_cuts_TMVA_MLP.C") (**images**: The combined ROC curve on TMVA is "ROC_Bkg_vs_Sig_on_TMVA_GUI.png")
  (many other important plots also come along as part of the training, like this one "ROC_Bkg_vs_Sig_on_TMVA_GUI.png")
  
**(3)** **_The surprising lack of expected distinction between dE/dx data of electrons and muons obtained from a model Mu2e experiment_** 
This was further investigated by senior members of our group. (**image**: The significant overlap of the two distributions can be seen in "Electron_Muon_dEdx_overlap.png". The short code generating this image is in "electron_muon_overlap.C")
