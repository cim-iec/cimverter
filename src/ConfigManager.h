///
/// ConfigManager.h
/// Manage the Config.cfg
///

#ifndef SRC_CONFIGMANAGER_H_
#define SRC_CONFIGMANAGER_H_

#include <libconfig.h++>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace libconfig;

/// ConnectionSettings in Template config.cfg

typedef  struct ConnectionSettings{
   std::string BusBarName;
   std::string ConnectivityNodeName;
   std::string SlackName;
   std::string PQLoadName;
   std::string ZLoadName;
   std::string PiLineName;
   std::string PiLineSuffix1;
   std::string PiLineSuffix2;
   std::string RxLineName;
   std::string TransformerName;
   std::string TransformerSuffix1;
   std::string TransformerSuffix2;
   std::string GenericGeneratorName;
   std::string WindGeneratorName;
   std::string SolarGeneratorName;
   std::string BatteryName;
   std::string HouseholdName;
   std::string PVNodeName;
   std::string BreakerName;
   std::string BreakerSuffix1;
   std::string BreakerSuffix2;
};

// use SV settings
typedef struct UseSVSettings{
    bool useSVforEnergyConsumer;
    bool useSVforGeneratingUnit;
    bool useSVforExternalNetworkInjection;
};

/// global settings in Config.cfg
typedef struct GlobalSettings{
  std::string source_tool_name;
  bool apply_Neplan_fix;
  bool create_distaix_format;

} GlobalSettings;

/// template settings in Config.cfg
typedef struct TemplateSettings {
  /// template tpl file path
  std::string directory_path;

} TemplateSettings;

/// files path settings in Config.cfg
typedef struct FilesSettings {
  std::string input_path;             /// input file path
  std::string output_path;            /// input file path

} FilesSettings;

/// Modelica system settings in Config.cfg
typedef struct SystemSettings {
  bool enable;                          /// enable system settings
  double topology_trans_parameter[4];   /// coordinate system transformer parameters in Modelica
  double coordinate[4];                 /// coordinate system range Parameters in Modelica
  std::string label_name;               /// set name of modelica label
  std::string label_simMode;            /// steady or transit
  std::string label_init;               /// initial mode
  double label_extent[4];               /// label size
  bool label_visible;                   /// label visible
  double annotation_extent[4];          /// system size
  bool use_TPNodes;                     /// Use TPNode or ConnectivityNodes
} SystemSettings;

/// base annotation settings in Config.cfg
typedef struct AnnotationSettings {
  bool visible;                     /// Icon visible
  double transformation_extent[4];  /// Icon size
} AnnotationSettings;

/// default unit settings in Config.cfg
typedef struct UnitSettings {
  bool enable;
  std::string voltage_unit;         /// Default unit of voltage
  std::string current_unit;         /// Default unit of current
  std::string active_power_unit;    /// Default unit of active power
  std::string reactive_power_unit;  /// Default unit of reactive power
} UnitSettings;

/// slack settings in Config.cfg
typedef struct SlackSettings {
  bool enable;                      /// enable slack settings
  AnnotationSettings annotation;    /// annotation settings
  UnitSettings unit;

} SlackSettings;

/// BusBar settings in Config.cfg
typedef struct BusBarSettings {
  bool enable;                      /// enable BusBar settings
  AnnotationSettings annotation;

} BusBarSettings;

/// Piline settings in Config.cfg
typedef struct PiLineSettings {
  bool enable;                      /// enable PiLine settings
  AnnotationSettings annotation;

} PiLineSettings;

/// Rxline settings in Config.cfg
typedef struct RxLineSettings {
  bool enable;                      /// enable Rxline settings
  AnnotationSettings annotation;

} RxLineSettings;

/// PQLoad settings in Config.cfg
typedef struct PQLoadSettings {
  bool enable;                      /// enable PQLoad settings
  int type;                         ///1:PQLoad, type 2:PQLoadProfile, 3:PQLoadNormProfile
  std::string profile_name;
  std::string profile_filename;
  AnnotationSettings annotation;

} PQLoadSettings;

/// ZLoad settings in Config.cfg
typedef struct ZLoadSettings {
  bool enable;                      /// enable ZLoad settings
  int type;
  std::string profile_name;
  std::string profile_filename;
  AnnotationSettings annotation;

} ZLoadSettings;

/// Transformer settings in Config.cfg
typedef struct TransformerSettings {
  bool enable;                      /// enable Transformer settings
  AnnotationSettings annotation;

} TransformerSettings;

/// WindGenerator settings in Config.cfg
typedef struct WindGeneratorSettings {
  bool enable;                      /// enable WindGenerator settings
  AnnotationSettings annotation;

} WindGeneratorSettings;

/// SolarGenerator settings in Config.cfg
typedef struct SolarGeneratorSettings {
  bool enable;                      /// enable SolarGenerator settings
  AnnotationSettings annotation;

} SolarGeneratorSettings;

/// Battery settings in Config.cfg
typedef struct BatterySettings {
  bool enable;                      /// enable Battery settings
  int type;                 /// Battery type: type0, type1
  AnnotationSettings annotation;

} BatterySettings;

/// Household settings in Config.cfg
typedef struct HouseholdSettings {
  bool enable;                      /// enable Household settings
  std::string type;                 /// Household type: type1, type2
  bool use_households;              /// use Household instead of PQLoad, SolarGenerator and Battery
  AnnotationSettings annotation;

} HouseholdSettings;

/// \brief Manage Settings from config.cfg
///
///
class ConfigManager {

 public:

  ConfigManager();

  virtual ~ConfigManager();
  int default_baseKV;
  UseSVSettings svSettings;
  ConnectionSettings cs;
  GlobalSettings  gs;
  UnitSettings us;
  TemplateSettings ts;
  FilesSettings fs;
  SystemSettings ss;
  SlackSettings slack_parameters;
  BusBarSettings busbar_parameters;
  PiLineSettings piline_parameters;
  RxLineSettings rxline_parameters;
  TransformerSettings trafo_parameters;
  PQLoadSettings pqload_parameters;
  ZLoadSettings zload_parameters;
  SolarGeneratorSettings solar_gen_parameters;
  WindGeneratorSettings wind_gen_parameters;
  BatterySettings battery_parameters;
  HouseholdSettings household_parameters;

 public:
  std::string template_folder;

  void getConnectionNames();

  void getConnectionConfigFiles();

  void getAllSettings();

  void getDefault_baseKV();

  void getSVSettings();

  void getGlobalSettings();

  void getConfigFiles();

  void getUnitSettings();

  void getFilesSettings();

  void getSystemSettings();

  void getSlackSettings();

  void getBusBarSettings();

  void getPiLineSettings();

  void getRxLineSettings();

  void getTransformerSettings();

  void getPQLoadSettings();

  void getZLoadSettings();

  void getWindGeneratorSettings();

  void getSolarGeneratorSettings();

  void getBatterySettings();

  void getHouseholdSettings();

 private:
  Config conCfg;
  Config cfg;

};

#endif /* SRC_CONFIGMANAGER_H_ */
