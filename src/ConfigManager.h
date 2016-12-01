/*
 * ConfigManager.h
 * Manage the Config.cfg
 */

#ifndef SRC_CONFIGMANAGER_H_
#define SRC_CONFIGMANAGER_H_

#include <libconfig.h++>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace libconfig;

typedef struct TemplateSettings {
  std::string directory_path;

} TemplateSettings;

typedef struct FilesSettings {
  std::string input_path;
  std::string output_path;

} FilesSettings;

typedef struct SystemSettings {
  bool enable;
  double topology_trans_parameter[4];
  double coordinate[4];
  std::string label_name;  //Set name of modelica label
  std::string label_simMode;  //steady or transit
  std::string label_init;  //initial mode
  double label_extent[4];
  bool label_visible;
  double annotation_extent[4];
  bool annotation_visible;
} SystemSettings;

typedef struct AnnotationSettings {
  bool visible;
  double transformation_extent[4];
} AnnotationSettings;

typedef struct SlackSettings {
  bool enable;
  AnnotationSettings annotation;
} SlackSettings;

typedef struct BusBarSettings {
  bool enable;
  AnnotationSettings annotation;

} BusBarSettings;

typedef struct PiLineSettings {
  bool enable;
  AnnotationSettings annotation;

} PiLineSettings;

typedef struct RxLineSettings {
  bool enable;
  AnnotationSettings annotation;

} RxLineSettings;

typedef struct PQLoadSettings {
  bool enable;
  bool use_profiles;
  std::string profile_name;
  std::string profile_filename;
  AnnotationSettings annotation;

} PQLoadSettings;

typedef struct ZLoadSettings {
  bool enable;
  bool use_profiles;
  std::string profile_name;
  std::string profile_filename;
  AnnotationSettings annotation;

} ZLoadSettings;

typedef struct TransformerSettings {
  bool enable;
  AnnotationSettings annotation;

} TransformerSettings;

typedef struct WindGeneratorSettings {
  bool enable;
  AnnotationSettings annotation;

} WindGeneratorSettings;

typedef struct SolarGeneratorSettings {
  bool enable;
  AnnotationSettings annotation;

} SolarGeneratorSettings;

typedef struct HouseholdSettings {
  bool enable;
  bool use_households;
  AnnotationSettings annotation;

} HouseholdSettings;

/*
 * Manage Settings from config.cfg
 */
class ConfigManager {

 public:

  ConfigManager();
  virtual ~ConfigManager();

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
  HouseholdSettings household_parameters;

 public:

  void getAllSettings();
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
  void getHouseholdSettings();

 private:
  Config cfg;

};

#endif /* SRC_CONFIGMANAGER_H_ */
