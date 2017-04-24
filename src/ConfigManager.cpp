/*
 * ConfigManager.cpp
 *
 */

#include "ConfigManager.h"

ConfigManager::ConfigManager() {
  this->getConfigFiles();
}

ConfigManager::~ConfigManager() {
  // TODO Auto-generated destructor stub
}

/// \brief get all settings
///
///
void ConfigManager::getAllSettings() {

  this->getGlobalSettings();
  this->getFilesSettings();
  this->getSystemSettings();
  this->getSlackSettings();
  this->getBusBarSettings();
  this->getPiLineSettings();
  this->getRxLineSettings();
  this->getTransformerSettings();
  this->getPQLoadSettings();
  this->getZLoadSettings();
  this->getWindGeneratorSettings();
  this->getSolarGeneratorSettings();
  this->getBatterySettings();
  this->getHouseholdSettings();
}


/// \brief find config file.
///
///
void ConfigManager::getConfigFiles() {
  try {
    this->cfg.readFile("config.cfg");         ///for release using CMake
    //this->cfg.readFile("build/bin/config.cfg"); ///for developing using makefile
  }
  catch (const FileIOException &fioex) {
    std::cerr << "I/O error while reading config file." << std::endl;
  }
  catch (const ParseException &pex) {
    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
  }
}

///
/// Get getGlobalSettings
///
void ConfigManager::getGlobalSettings(){
  try {
    this->gs.source_tool_name = this->cfg.lookup("source_tool_name").c_str();
    std::cout << "Source tool: " << this->gs.source_tool_name << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No source_tool_name in configuration file." << std::endl;
  }
  try {
    this->gs.apply_Neplan_fix = this->cfg.lookup("apply_Neplan_fix");
    if(this->gs.apply_Neplan_fix == true){
      std::cout << "Apply Neplan Fix: true" << std::endl;
    } else {
      std::cout << "Apply Neplan Fix: false" << std::endl;

    }
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No apply_Neplan_fix settings in configuration file." << std::endl;
  }
}

///
/// Get files' path from config.cfg
///
void ConfigManager::getFilesSettings() {
  std::cout << "----------------FilesSettings-------------------" << std::endl;
  try {
    this->fs.input_path = this->cfg.lookup("files.input_directory_path").c_str();
    std::cout << "input_directory_path: " << fs.input_path << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No input_directory_path settings in configuration file." << std::endl;
  }
  try {
    this->fs.output_path = this->cfg.lookup("files.output_directory_path").c_str();
    std::cout << "output_directory_path: " << fs.output_path << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No output_directory_path settings in configuration file." << std::endl;
  }
  try {
    this->ts.directory_path = this->cfg.lookup("files.template_directory_path").c_str();
    std::cout << "template_directory_path: " << ts.directory_path << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No template_directory_path settings in configuration file." << std::endl;
  }
}

///
/// Get Modelica SystemSettings from config.cfg
///
void ConfigManager::getSystemSettings() {
  std::cout << "----------------SystemSettings-------------------" << std::endl;
  try {
    this->ss.enable = this->cfg.lookup("system.enable");
    std::cout << "get systemSettings enable successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No system enable settings in configuration file." << std::endl;
  }
  try {
    this->ss.label_name = this->cfg.lookup("system.label.name").c_str();
    std::cout << "label_name: " << this->ss.label_name << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No label_name settings in configuration file." << std::endl;
  }
  try {
    this->ss.label_visible = this->cfg.lookup("system.label.annotation.visible");
    std::cout << "label_visible: " << this->ss.label_visible << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No label_visible settings in configuration file." << std::endl;
  }
  try {
    this->ss.label_simMode = this->cfg.lookup("system.label.simMode").c_str();
    std::cout << "label_simMode: " << this->ss.label_simMode << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No label_simMode settings in configuration file." << std::endl;
  }
  try {
    this->ss.label_init = this->cfg.lookup("system.label.init").c_str();
    std::cout << "label_init: " << this->ss.label_init << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No label_init settings in configuration file." << std::endl;
  }
  try {
    const Setting &trans_para = this->cfg.lookup("system.topology_trans_parameter");
    for (int i = 0; i < 4; i++) {
      this->ss.topology_trans_parameter[i] = trans_para[i];
    }
    std::cout << "get topology_trans_parameter successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No topology_trans_parameter settings in configuration file." << std::endl;
  }
  try {
    const Setting &coordinate = this->cfg.lookup("system.coordinate");
    for (int i = 0; i < 4; i++) {
      this->ss.coordinate[i] = coordinate[i];
    }
    std::cout << "get coordinate successfully!" << std::endl;

  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No coordinate settings in configuration file." << std::endl;
  }
  try {
    const Setting &label_extent = this->cfg.lookup("system.label.annotation.extent");
    for (int i = 0; i < 4; i++) {
      this->ss.label_extent[i] = label_extent[i];
    }
    std::cout << "get label_extent successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No label_extent settings in configuration file." << std::endl;
  }
  try {
    const Setting &annotation_extent = this->cfg.lookup("system.annotation.extent");
    for (int i = 0; i < 4; i++) {
      this->ss.annotation_extent[i] = annotation_extent[i];
    }
    std::cout << "get annotation_extent successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No annotation_extent settings in configuration file." << std::endl;
  }
}

///
/// Get Modelica Slack Settings from config.cfg
///
void ConfigManager::getSlackSettings() {
  std::cout << "----------------SlackSettings-------------------" << std::endl;
  try {
    this->slack_parameters.enable = this->cfg.lookup("single_phase.slack.enable");
    std::cout << "get enable successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No enable settings in configuration file." << std::endl;
  }
  try {
    this->slack_parameters.annotation.visible = this->cfg.lookup("single_phase.slack.annotation.visible");
    std::cout << "visible: " << this->slack_parameters.annotation.visible << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No visible settings in configuration file." << std::endl;
  }
  try {
    const Setting &transformation_extent = this->cfg.lookup("single_phase.slack.annotation.transformation.extent");
    for (int i = 0; i < 4; i++) {
      this->slack_parameters.annotation.transformation_extent[i] = transformation_extent[i];
    }
    std::cout << "get transformation_extent successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No transformation_extent settings in configuration file." << std::endl;
  }
}

///
/// Get Modelica BusBar Settings from config.cfg
///
void ConfigManager::getBusBarSettings() {
  std::cout << "----------------BusBarSettings-------------------" << std::endl;
  try {
    this->busbar_parameters.enable = this->cfg.lookup("single_phase.busbar.enable");
    std::cout << "get enable successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No enable settings in configuration file." << std::endl;
  }
  try {
    this->busbar_parameters.annotation.visible = this->cfg.lookup("single_phase.busbar.annotation.visible");
    std::cout << "visible: " << this->busbar_parameters.annotation.visible << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No visible settings in configuration file." << std::endl;
  }
  try {
    const Setting &transformation_extent = this->cfg.lookup("single_phase.busbar.annotation.transformation.extent");
    for (int i = 0; i < 4; i++) {
      this->busbar_parameters.annotation.transformation_extent[i] = transformation_extent[i];
    }
    std::cout << "get transformation_extent successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No transformation_extent settings in configuration file." << std::endl;
  }
}

///
/// Get Modelica Transformer Settings from config.cfg
///
void ConfigManager::getTransformerSettings() {
  std::cout << "-----------TransformerSettingsSettings-----------" << std::endl;
  try {
    this->trafo_parameters.enable = this->cfg.lookup("single_phase.transformer.enable");
    std::cout << "get enable successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No enable settings in configuration file." << std::endl;
  }
  try {
    this->trafo_parameters.annotation.visible = this->cfg.lookup("single_phase.transformer.annotation.visible");
    std::cout << "visible: " << this->trafo_parameters.annotation.visible << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No visible settings in configuration file." << std::endl;
  }
  try {
    const Setting &transformation_extent = this->cfg.lookup(
        "single_phase.transformer.annotation.transformation.extent");
    for (int i = 0; i < 4; i++) {
      this->trafo_parameters.annotation.transformation_extent[i] = transformation_extent[i];
    }
    std::cout << "get transformation_extent successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No transformation_extent settings in configuration file." << std::endl;
  }
}

///
/// Get Modelica PiLine Settings from config.cfg
///
void ConfigManager::getPiLineSettings() {
  std::cout << "----------------PiLineSettings-----------------" << std::endl;
  try {
    this->piline_parameters.enable = this->cfg.lookup("single_phase.piline.enable");
    std::cout << "get piline_parameters enable successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No enable settings in configuration file." << std::endl;
  }
  try {
    this->piline_parameters.annotation.visible = this->cfg.lookup("single_phase.piline.annotation.visible");
    std::cout << "visible: " << this->piline_parameters.annotation.visible << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No visible settings in configuration file." << std::endl;
  }
  try {
    const Setting &transformation_extent = this->cfg.lookup("single_phase.piline.annotation.transformation.extent");
    for (int i = 0; i < 4; i++) {
      this->piline_parameters.annotation.transformation_extent[i] = transformation_extent[i];
    }
    std::cout << "get transformation_extent successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No transformation_extent settings in configuration file." << std::endl;
  }
}

///
/// Get Modelica RxLine Settings from config.cfg
///
void ConfigManager::getRxLineSettings() {
  std::cout << "--------------RxLineSettings----------------" << std::endl;
  try {
    this->rxline_parameters.enable = this->cfg.lookup("single_phase.rxline.enable");
    std::cout << "get enable successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No enable settings in configuration file." << std::endl;
  }
  try {
    this->rxline_parameters.annotation.visible = this->cfg.lookup("single_phase.rxline.annotation.visible");
    std::cout << "visible: " << this->rxline_parameters.annotation.visible << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No visible settings in configuration file." << std::endl;
  }
  try {
    const Setting &transformation_extent = this->cfg.lookup("single_phase.rxline.annotation.transformation.extent");
    for (int i = 0; i < 4; i++) {
      this->rxline_parameters.annotation.transformation_extent[i] = transformation_extent[i];
    }
    std::cout << "get transformation_extent successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No transformation_extent settings in configuration file." << std::endl;
  }
}

/// \brief Get PQLoad Settings from config.cfg.
///
///
void ConfigManager::getPQLoadSettings() {
  std::cout << "----------------PQLoadSettings-----------------" << std::endl;
  try {
    this->pqload_parameters.enable = this->cfg.lookup("single_phase.pqload.enable");
    std::cout << "get enable successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No enable settings in configuration file." << std::endl;
  }
  try {
    this->pqload_parameters.annotation.visible = this->cfg.lookup("single_phase.pqload.annotation.visible");
    std::cout << "visible: " << this->pqload_parameters.annotation.visible << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No visible settings in configuration file." << std::endl;
  }
  try {
    this->pqload_parameters.profile_name = this->cfg.lookup("single_phase.pqload.profile_name").c_str();
    std::cout << "profile_name: " << pqload_parameters.profile_name << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No profile_name settings in configuration file." << std::endl;
  }
  try {
    this->pqload_parameters.profile_filename = this->cfg.lookup("single_phase.pqload.profile_filename").c_str();
    std::cout << "profile_filename: " << pqload_parameters.profile_filename << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No profile_filename settings in configuration file." << std::endl;
  }
  try {
    const Setting &transformation_extent = this->cfg.lookup("single_phase.pqload.annotation.transformation.extent");
    for (int i = 0; i < 4; i++) {
      this->pqload_parameters.annotation.transformation_extent[i] = transformation_extent[i];
    }
    std::cout << "get transformation_extent successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No transformation_extent settings in configuration file." << std::endl;
  }
  try {
    /// Get the UseProfiles.
    this->pqload_parameters.use_profiles = this->cfg.lookup("single_phase.pqload.use_profiles");
    if (this->pqload_parameters.use_profiles)
      std::cout << "Using UseProfiles" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "use_profiles setting mistake in configuration file." << std::endl;
  }
}

///
/// Get ZLoad Settings from config.cfg
///
void ConfigManager::getZLoadSettings() {
  std::cout << "----------------ZLoadSettings-----------------" << std::endl;
  try {
    this->zload_parameters.enable = this->cfg.lookup("single_phase.zload.enable");
    std::cout << "get enable successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No enable settings in configuration file." << std::endl;
  }
  try {
    this->zload_parameters.annotation.visible = this->cfg.lookup("single_phase.zload.annotation.visible");
    std::cout << "visible: " << this->zload_parameters.annotation.visible << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No visible settings in configuration file." << std::endl;
  }
  try {
    const Setting &transformation_extent = this->cfg.lookup("single_phase.zload.annotation.transformation.extent");
    for (int i = 0; i < 4; i++) {
      this->zload_parameters.annotation.transformation_extent[i] = transformation_extent[i];
    }
    std::cout << "get transformation_extent successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No transformation_extent settings in configuration file." << std::endl;
  }
  try {
    // Get the UseProfiles.
    this->zload_parameters.use_profiles = this->cfg.lookup("single_phase.zload.use_profiles");
    if (zload_parameters.use_profiles)
      std::cout << "Using UseProfiles" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "use_profiles setting mistake in configuration file." << std::endl;
  }
}

///
/// Get Modelica SolarGenerator Settings Settings from config.cfg
///
void ConfigManager::getSolarGeneratorSettings() {
  std::cout << "---------SolarGeneratorSettings---------------" << std::endl;
  try {
    this->solar_gen_parameters.enable = this->cfg.lookup("single_phase.solar_generator.enable");
    std::cout << "get enable successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No enable settings in configuration file." << std::endl;
  }
  try {
    this->solar_gen_parameters.annotation.visible = this->cfg.lookup(
        "single_phase.solar_generator.annotation.visible");
    std::cout << "visible: " << this->solar_gen_parameters.annotation.visible << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No visible settings in configuration file." << std::endl;
  }
  try {
    const Setting &transformation_extent = this->cfg.lookup(
        "single_phase.solar_generator.annotation.transformation.extent");
    for (int i = 0; i < 4; i++) {
      this->solar_gen_parameters.annotation.transformation_extent[i] = transformation_extent[i];
    }
    std::cout << "get transformation_extent successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No transformation_extent settings in configuration file." << std::endl;
  }
}

///
/// Get Modelica WindGenerator Settings Settings from config.cfg
///
void ConfigManager::getWindGeneratorSettings() {
  std::cout << "-----------WindGeneratorSettings-------------" << std::endl;
  try {
    this->wind_gen_parameters.enable = this->cfg.lookup("single_phase.wind_generator.enable");
    std::cout << "get enable successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No enable settings in configuration file." << std::endl;
  }
  try {
    this->wind_gen_parameters.annotation.visible = this->cfg.lookup(
        "single_phase.wind_generator.annotation.visible");
    std::cout << "visible: " << this->wind_gen_parameters.annotation.visible << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No visible settings in configuration file." << std::endl;
  }
  try {
    const Setting &transformation_extent = this->cfg.lookup(
        "single_phase.wind_generator.annotation.transformation.extent");
    for (int i = 0; i < 4; i++) {
      this->wind_gen_parameters.annotation.transformation_extent[i] = transformation_extent[i];
    }
    std::cout << "get transformation_extent successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No transformation_extent settings in configuration file." << std::endl;
  }
}

///
/// Get Battery Setting from config.cfg
///
void ConfigManager::getBatterySettings() {
  std::cout << "-------------BatterySettings-------------" << std::endl;
  try {
    this->battery_parameters.enable = this->cfg.lookup("single_phase.battery.enable");
    std::cout << "get enable successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No enable settings in configuration file." << std::endl;
  }
  try {
    this->battery_parameters.annotation.visible = this->cfg.lookup("single_phase.battery.annotation.visible");
    std::cout << "visible: " << this->battery_parameters.annotation.visible << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No visible settings in configuration file." << std::endl;
  }
  try {
    this->battery_parameters.type = this->cfg.lookup("single_phase.battery.type").c_str();
    std::cout << "type: " << battery_parameters.type << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No type settings in configuration file." << std::endl;
  }
  try {
    const Setting &transformation_extent = this->cfg.lookup(
        "single_phase.battery.annotation.transformation.extent");
    for (int i = 0; i < 4; i++) {
      this->battery_parameters.annotation.transformation_extent[i] = transformation_extent[i];
    }
    std::cout << "get transformation_extent successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No transformation_extent settings in configuration file." << std::endl;
  }
}

///
///Get Household Setting from config.cfg
///
void ConfigManager::getHouseholdSettings() {
  std::cout << "-------------HouseholdSettings-------------" << std::endl;
  try {
    this->household_parameters.enable = this->cfg.lookup("single_phase.household.enable");
    std::cout << "get enable successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No enable settings in configuration file." << std::endl;
  }
  try {
    this->household_parameters.annotation.visible = this->cfg.lookup("single_phase.household.annotation.visible");
    std::cout << "visible: " << this->household_parameters.annotation.visible << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No visible settings in configuration file." << std::endl;
  }
  try {
    const Setting &transformation_extent = this->cfg.lookup(
        "single_phase.household.annotation.transformation.extent");
    for (int i = 0; i < 4; i++) {
      this->household_parameters.annotation.transformation_extent[i] = transformation_extent[i];
    }
    std::cout << "get transformation_extent successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No transformation_extent settings in configuration file." << std::endl;
  }
  try {
    this->household_parameters.type = this->cfg.lookup("single_phase.household.type").c_str();
    std::cout << "type: " << household_parameters.type << std::endl;
    std::cout << "get household_parameters.type successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No type settings in configuration file." << std::endl;
  }
  try {
    // Get the UseHouseholds.
    this->household_parameters.use_households = this->cfg.lookup("single_phase.household.use_households");
    if (this->household_parameters.use_households)
      std::cout << "Using Households" << std::endl;
    std::cout << "get household_parameters.use_households successfully!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "UseHouseholds setting mistake in configuration file." << std::endl;
  }
  try {
    // Get the UseHouseholds.
    this->household_parameters.load_type = this->cfg.lookup("single_phase.household.load_type");
    if(this->household_parameters.load_type < 1 || this->household_parameters.load_type > 3){
      throw -1;
    }
      if (this->household_parameters.load_type){
      std::cout << "load_type:" << household_parameters.load_type << std::endl;
      std::cout << "get household_parameters.load_type successfully!" << std::endl;
      }

  }
    catch(int e)  {std::cerr << ">>>>>>>>>>>wrong load_type number:" << household_parameters.load_type << std::endl; exit(0);}
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "UseHouseholds setting mistake in configuration file." << std::endl;
  }
}

