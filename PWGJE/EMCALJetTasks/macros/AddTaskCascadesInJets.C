AliAnalysisTaskCascadesInJets* AddTaskCascadesInJets(
  TString tracksName = "usedefault",
  TString label = ""
)
{
  AliAnalysisManager* mgr = AliAnalysisManager::GetAnalysisManager();
  if(!mgr) {
    Error("AddTaskCascadesFinder", "No analysis manager found.");
    return 0;
  }
  
  TString outputFile = AliAnalysisManager::GetCommonFileName();
  outputFile += ":CascadesForJetAnalysis";

  TString taskName = "Cascade";
  TString containerName = "Cascade";

  if(label.Length()) {
    taskName += Form("_%s", label.Data());
    containerName += Form("_%s", label.Data());
  }
  
  AliAnalysisTaskCascadesInJets* mytask = new AliAnalysisTaskCascadesInJets(taskName.Data());
  
  AliParticleContainer* trackCont = mytask->AddTrackContainer(tracksName);
  
  // Add task
  mgr->AddTask(mytask);

  // Create containers for input/output
  AliAnalysisDataContainer* cinput0 = mgr->GetCommonInputContainer();
  AliAnalysisDataContainer* coutput1 = mgr->CreateContainer(Form("%s_%s", containerName.Data(), "Histograms"), TList::Class(), AliAnalysisManager::kOutputContainer, outputFile.Data());
  AliAnalysisDataContainer* coutput2 = mgr->CreateContainer(Form("%s_%s", containerName.Data(), "JetHistograms"), TList::Class(), AliAnalysisManager::kOutputContainer, outputFile.Data());
  AliAnalysisDataContainer* coutput3 = mgr->CreateContainer(Form("%s_%s", containerName.Data(), "MCHistograms"), TList::Class(), AliAnalysisManager::kOutputContainer, outputFile.Data());


  // Connect input/output
  mgr->ConnectInput(mytask, 0, cinput0);
  mgr->ConnectOutput(mytask, 1, coutput1);
  mgr->ConnectOutput(mytask, 2, coutput2);
  mgr->ConnectOutput(mytask, 3, coutput3);


  return mytask;
}
