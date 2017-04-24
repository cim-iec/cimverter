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

/// global settings in Config.cfg
typedef struct GlobalSettings{
  std::string source_tool_name;
  bool apply_Neplan_fix;

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
} SystemSettings;

/// base annotation settings in Config.cfg
typedef struct AnnotationSettings {
  bool visible;                     /// Icon visible
  double transformation_extent[4];  /// Icon size
} AnnotationSettings;

/// slack settings in Config.cfg
typedef struct SlackSettings {
  bool enable;                      /// enable slack settings
  AnnotationSettings annotation;    /// annotation settings
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
  bool use_profiles;                /// use PQLoadProfile instead of PQLoad
  std::string profile_name;
  std::string profile_filename;
  AnnotationSettings annotation;

} PQLoadSettings;

/// ZLoad settings in Config.cfg
typedef struct ZLoadSettings {
  bool enable;                      /// enable ZLoad settings
  bool use_profiles;
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
  std::string type;                 /// Battery type: type0, type1
  AnnotationSettings annotation;

} BatterySettings;

/// Household settings in Config.cfg
typedef struct HouseholdSettings {
  bool enable;                      /// enable Household settings
  std::string type;                 /// Household type: type1, type2
  bool use_households;              /// use Household instead of PQLoad, SolarGenerator and Battery
  int load_type;                    /// Parameter Integer Load_Type: 1, 2, 3
  AnnotationSettings annotation;

} HouseholdSettings;

/// \brief Manage Settings from config.cfg
///
///
class ConfigManager {

 public:

  ConfigManager();

  virtual ~ConfigManager();

  GlobalSettings  gs;
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

  void getAllSettings();

  void getGlobalSettings();

  void getConfigFiles();

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
  Config cfg;

};

#endif /* SRC_CONFIGMANAGER_H_ */
