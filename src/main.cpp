#include <chrono>
#include "CIMObjectHandler.h"

unsigned int filesize(const char* filename) {
  std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
  unsigned int size = in.tellg();
  in.close();
  return size;
}

std::string xml_filepath;
std::string modelica_filename("modelica_example.mo");

int main(int argc, const char **argv) {

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
  print_separator();
  std::cout << "CIM-XML file is in:" << xml_filepath << std::endl;
  print_separator();

  CIMParser parser;
  unsigned long file_size = filesize(xml_filepath.c_str());
  unsigned long secs;

  // Timer start
  std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
  start = std::chrono::high_resolution_clock::now();

  parser.parse_file(xml_filepath.c_str());
  CIMObjectHandler ObjectHandler(std::move(parser.Objects));
  ObjectHandler.get_config();
  ObjectHandler.ModelicaCodeGenerator(modelica_filename);

  // Timer stop
  stop = std::chrono::high_resolution_clock::now();
  secs = std::chrono::duration_cast < std::chrono::microseconds
      > (stop - start).count();

  std::cout << 1000 * file_size / secs << "KByte/s" << std::endl;
  print_separator();
}
