#include <iostream>
#include <fstream>
#include <chrono>
#include "CIMParser.h"
#include "IEC61970.h"
#include "CIMObjectHandler.h"
#include <libconfig.h++>

//using namespace libconfig;

unsigned int filesize(const char* filename) {
  std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
  unsigned int size = in.tellg();
  in.close();
  return size;
}

std::string xml_filepath;
std::string modelica_filename("modelica_example.mo");

int main(int argc, const char **argv) {
//  Config cfg;
//
//  try {
//    cfg.readFile("src/config.cfg");
//  } catch (const FileIOException &fioex) {
//    std::cerr << "I/O error while reading file." << std::endl;
//    return (EXIT_FAILURE);
//  } catch (const ParseException &pex) {
//    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
//              << " - " << pex.getError() << std::endl;
//    return (EXIT_FAILURE);
//  }
//
//  // Get the store name.
//  try {
//    std::string version = cfg.lookup("version");
//    std::cout << "version: " << version << std::endl;
//  } catch (const SettingNotFoundException &nfex) {
//    std::cerr << "No 'name' setting in configuration file." << std::endl;
//  }

  // Check for arguments
  if (argc <= 1) {
    std::cerr << "Too few arguments:\nUsage: CIMParserGenerator <EACode_path>"
              << std::endl;
    exit(1);
  }

  xml_filepath = argv[1];

  if (argc > 1) {
    modelica_filename = argv[2];
  }

  std::cout << "CIM-XML file is in:" << xml_filepath << std::endl;

  CIMParser parser;
  unsigned long file_size = filesize(xml_filepath.c_str());
  unsigned long secs;

  // Timer start
  std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
  start = std::chrono::high_resolution_clock::now();

  parser.parse_file(xml_filepath.c_str());
  CIMObjectHandler ObjectHandler(std::move(parser.Objects));
  ObjectHandler.ModelicaCodeGenerator(modelica_filename);

  // Timer stop
  stop = std::chrono::high_resolution_clock::now();
  secs = std::chrono::duration_cast < std::chrono::microseconds
      > (stop - start).count();

  std::cout << 1000 * file_size / secs << "KByte/s" << std::endl;

}
