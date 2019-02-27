/*
 * ConfigManager.cpp
 *
 */

#include <cstring>
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
  this->getUnitSettings();
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

void ConfigManager::getConnectionConfigFiles(){

    try {
        this->conCfg.readFile((ts.directory_path + "resource/" + template_folder + "/connectors.cfg").c_str());         ///for release using CMake
    }
    catch (const FileIOException &fioex) {
        std::cerr << "filepath: " << ts.directory_path + "resource/" + template_folder + "/connectors.cfg" << "\n";
        std::cerr << "I/O error while reading config file." << std::endl;
    }
    catch (const ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
    }
}

void ConfigManager::getConnectionNames(){
    try {
        this->cs.BusBarName = this->conCfg.lookup("connections.BusBar.name").c_str();

    }
    catch (const SettingNotFoundException &nfex) {
        std::cerr << "No system enable settings in configuration file." << std::endl;
    }
    try {
        this->cs.ConnectivityNodeName = this->conCfg.lookup("connections.ConnectivityNode.name").c_str();

    }
    catch (const SettingNotFoundException &nfex) {
        std::cerr << "No system enable settings in configuration file." << std::endl;
    }
    try {
        this->cs.SlackName = this->conCfg.lookup("connections.Slack.name").c_str();

    }
    catch (const SettingNotFoundException &nfex) {
        std::cerr << "No system enable settings in configuration file." << std::endl;
    }
    try {
        this->cs.PQLoadName = this->conCfg.lookup("connections.PQLoad.name").c_str();

    }
    catch (const SettingNotFoundException &nfex) {
        std::cerr << "No system enable settings in configuration file." << std::endl;
    }
    try {
        this->cs.HouseholdName = this->conCfg.lookup("connections.Household.name").c_str();

    }
    catch (const SettingNotFoundException &nfex) {
        std::cerr << "No system enable settings in configuration file." << std::endl;
    }
    try {
        this->cs.PiLineName = this->conCfg.lookup("connections.PiLine.name").c_str();

    }
    catch (const SettingNotFoundException &nfex) {
        std::cerr << "No system enable settings in configuration file." << std::endl;
    }
    try {
        this->cs.PiLineSuffix1 = this->conCfg.lookup("connections.PiLine.suffix1").c_str();

    }
    catch (const SettingNotFoundException &nfex) {
        std::cerr << "No system enable settings in configuration file." << std::endl;
    }
    try {
        this->cs.PiLineSuffix2 = this->conCfg.lookup("connections.PiLine.suffix2").c_str();

    }
    catch (const SettingNotFoundException &nfex) {
        std::cerr << "No system enable settings in configuration file." << std::endl;
    }
    try {
        this->cs.TransformerName = this->conCfg.lookup("connections.Transformer.name").c_str();

    }
    catch (const SettingNotFoundException &nfex) {
        std::cerr << "No system enable settings in configuration file." << std::endl;
    }
    try {
        this->cs.TransformerSuffix1 = this->conCfg.lookup("connections.Transformer.suffix1").c_str();

    }
    catch (const SettingNotFoundException &nfex) {
        std::cerr << "No system enable settings in configuration file." << std::endl;
    }
    try {
        this->cs.TransformerSuffix2 = this->conCfg.lookup("connections.Transformer.suffix2").c_str();

    }
    catch (const SettingNotFoundException &nfex) {
        std::cerr << "No system enable settings in configuration file." << std::endl;
    }
    try {
        this->cs.WindGeneratorName = this->conCfg.lookup("connections.WindGenerator.name").c_str();

    }
    catch (const SettingNotFoundException &nfex) {
        std::cerr << "No system enable settings in configuration file." << std::endl;
    }
    try {
        this->cs.SolarGeneratorName = this->conCfg.lookup("connections.SolarGenerator.name").c_str();

    }
    catch (const SettingNotFoundException &nfex) {
        std::cerr << "No system enable settings in configuration file." << std::endl;
    }
    try {
        this->cs.BatteryName = this->conCfg.lookup("connections.Battery.name").c_str();

    }
    catch (const SettingNotFoundException &nfex) {
        std::cerr << "No system enable settings in configuration file." << std::endl;
    }
}

void ConfigManager::getConfigFiles() {
  try {
      std::string cfgName = "config.cfg";
      if (std::getenv("CIMVERTER_HOME") != NULL){

          const char* CIMVERTER_HOME = std::getenv("CIMVERTER_HOME");
          std::cout << "cfg path"<< CIMVERTER_HOME + cfgName << std::endl;
          cfgName = CIMVERTER_HOME + cfgName;
          this->cfg.readFile(cfgName.c_str());         ///for release using CMake
      }
      this->cfg.readFile(cfgName.c_str());         ///for release using CMake
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
  // TODO: Remove if tested
  // try {
  //   this->gs.create_distaix_format = this->cfg.lookup("create_distaix_format");
  //   if(this->gs.create_distaix_format == true){
  //     std::cout << "Create distaix format: true" << std::endl;
  //   } else {
  //     std::cout << "Create distaix format: false" << std::endl;
  //   }
  // }
  // catch (const SettingNotFoundException &nfex) {
  //   std::cerr << "No create_distaix_format settings in configuration file." << std::endl;
  // }
}

void ConfigManager::getUnitSettings() {
  std::cout << "----------------Apply MEPLAN Unit fix-------------------" << std::endl;
  try {
    this->us.enable = this->cfg.lookup("apply_unit_fix.enable");
    std::cout << "Unit Enable!" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No unit settings in configuration file." << std::endl;
  }
  try {
    this->us.voltage_unit = this->cfg.lookup("apply_unit_fix.voltage_unit").c_str();
    std::cout << "voltage_unit:" << this->us.voltage_unit << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No voltage_unit settings in configuration file." << std::endl;
  }
  try {
    this->us.current_unit = this->cfg.lookup("apply_unit_fix.current_unit").c_str();
    std::cout << "current_unit:" << this->us.current_unit << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No current_unit settings in configuration file." << std::endl;
  }
  try {
    this->us.active_power_unit = this->cfg.lookup("apply_unit_fix.active_power_unit").c_str();
    std::cout << "active_power_unit:" << this->us.active_power_unit << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No active_power_unit settings in configuration file." << std::endl;
  }
  try {
    this->us.reactive_power_unit = this->cfg.lookup("apply_unit_fix.reactive_power_unit").c_str();
    std::cout << "reactive_power_unit:" << this->us.reactive_power_unit << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No reactive_power_unit settings in configuration file." << std::endl;
  }
}

///
/// Get files' path from config.cfg
///
void ConfigManager::getFilesSettings() {

    if (std::getenv("CIMVERTER_HOME") != NULL){
        const char* CIMVERTER_HOME = std::getenv("CIMVERTER_HOME");
        std::cout << "----------------FilesSettings-------------------" << std::endl;
        try {
            this->fs.input_path = this->cfg.lookup("files.input_directory_path").c_str();
            std::cout << "input_directory_path: " << fs.input_path << std::endl;
        }
        catch (const SettingNotFoundException &nfex) {
            std::cerr << "No input_directory_path settings in configuration file." << std::endl;
        }
        try {
            std::string outputPath = this->cfg.lookup("files.output_directory_path").c_str();
            this->fs.output_path = CIMVERTER_HOME + outputPath;
            std::cout << "output_directory_path: " << fs.output_path << std::endl;
        }
        catch (const SettingNotFoundException &nfex) {
            std::cerr << "No output_directory_path settings in configuration file." << std::endl;
        }
        try {
            std::string directoryPath = this->cfg.lookup("files.template_directory_path").c_str();
            this->ts.directory_path = CIMVERTER_HOME + directoryPath;
            std::cout << "template_directory_path: " << ts.directory_path << std::endl;
        }
        catch (const SettingNotFoundException &nfex) {
            std::cerr << "No template_directory_path settings in configuration file." << std::endl;
        }
    }else{
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
    /// Get the Profiles Type.
    this->pqload_parameters.type = this->cfg.lookup("single_phase.pqload.type");
    if (this->pqload_parameters.type)
      std::cout << "Using Profiles Type: " << this->pqload_parameters.type << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "Profile Type setting mistake in configuration file." << std::endl;
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
    /// Get the Profiles Type.
    this->zload_parameters.type = this->cfg.lookup("single_phase.zload.type");
    if (this->zload_parameters.type)
      std::cout << "Using Profiles Type: " << this->zload_parameters.type << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "Profile Type setting mistake in configuration file." << std::endl;
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
    this->battery_parameters.type = this->cfg.lookup("single_phase.battery.type");
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
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "No type settings in configuration file." << std::endl;
  }
  try {
    // Get the UseHouseholds.
    this->household_parameters.use_households = this->cfg.lookup("single_phase.household.use_households");
    if (this->household_parameters.use_households)
      std::cout << "Using Households" << std::endl;
  }
  catch (const SettingNotFoundException &nfex) {
    std::cerr << "UseHouseholds setting mistake in configuration file." << std::endl;
  }
}