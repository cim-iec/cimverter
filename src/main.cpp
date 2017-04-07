#include <chrono>
#include "CIMObjectHandler.h"
#include <dirent.h>

/**
 * Get File size
 * @param filename
 * @return
 */
unsigned int filesize(const char *filename) {
  std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
  long size = in.tellg();
  in.close();
  return size;
}
/**
 * Find all files in the folder
 * @param path
 * @return files
 */
std::vector<std::string> search_folder(const char *path) {

  struct dirent *ent = NULL;
  DIR *pDir;
  pDir = opendir(path);
  std::vector<std::string> files;
  
  while (NULL != (ent = readdir(pDir))) {

    std::string _path(path);
    std::string _dirName(ent->d_name);
    if(strcmp(ent->d_name,".") == 0 || strcmp(ent->d_name,"..") == 0 )
      continue;
    std::string file_path = _path + _dirName;
    files.push_back(file_path);
  }

  return files;
}

/**
 * Show the help information
 *
 */
void print_argument_help(){
  std::cout << "usage:" << std::endl;
  std::cout << "Parse the separated files:" << std::endl;
  std::cout << "./CIM2Mod -f <file2.xml> <file2.xml>... [modelica_output_file_name]" << std::endl;
  std::cout << std::endl;
  std::cout << "Parse the separated files using verbose option:" << std::endl;
  std::cout << "./CIM2Mod -f --verbose <file2.xml> <file2.xml>... [modelica_output_file_name]" << std::endl;
  std::cout << std::endl;
  std::cout << "Parse all files in a folder:" << std::endl;
  std::cout << "./CIM2Mod -a <xml_directory/> [modelica_output_file_name]" << std::endl;
  std::cout << std::endl;
  std::cout << "Parse all files in a folder using verbose option" << std::endl;
  std::cout << "./CIM2Mod -a --verbose <xml_directory/> [modelica_output_file_name]" << std::endl;
  exit(1);
}

int main(int argc, const char **argv) {
  std::vector<std::string> args;// Arguments for the ObjectHandler

  long file_size;// File size
  long secs;// Time in seconds

  // Check for arguments
  if (argc <= 2) {
    if(argc == 1){
      std::cerr << "Too few arguments:" << std::endl;
      print_argument_help();
    } else if (strcmp(argv[1], "--help") == 0) {
      print_argument_help();
    } else {
      std::cerr << "Too few arguments:" << std::endl;
      print_argument_help();
    }
  }

  print_separator();

  CIMModel cimModel;

  if (argc > 2) {

    args.push_back(std::string(argv[argc - 1]));// Push output modelica filesname

    file_size = 0;
    if (strcmp(argv[1], "-f") == 0) {

      if(strcmp(argv[2], "--verbose") == 0){
        args.push_back("--verbose");
        for (int i = 3; i < argc - 1; i++) {
          std::cout << "CIM-XML file is:" << argv[i] << std::endl;
          file_size += filesize(argv[i]);
          cimModel.addCIMFile(argv[i]);
        }
      } else {
        for (int i = 2; i < argc - 1; i++) {
          std::cout << "CIM-XML file is:" << argv[i] << std::endl;
          file_size += filesize(argv[i]);
          cimModel.addCIMFile(argv[i]);
        }
      }
    } else if (strcmp(argv[1], "-a") == 0) {
        std::vector<std::string> files;
        if(strcmp(argv[2], "--verbose") == 0) {
          files = search_folder(argv[3]);// Find all relevant files
          args.push_back("--verbose");
        } else {
          files = search_folder(argv[2]);
        }

        for (auto f : files) {
          std::cout << "CIM-XML file is:" << f << std::endl;
          file_size += filesize(f.c_str());
          cimModel.addCIMFile(f);
        }
      } else {
        std::cerr << "Wrong arguments:" << std::endl;
        print_argument_help();
      }
    } else {
      std::cerr << "Wrong arguments:" << std::endl;
      print_argument_help();
    }

  // Timer start
  std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
  start = std::chrono::high_resolution_clock::now();

  //set off the Dependency check
  cimModel.setDependencyCheckOff();

  cimModel.parseFiles();// Parser begin!
  CIMObjectHandler ObjectHandler(std::move(cimModel.Objects));// r-value
  ObjectHandler.get_config();// Get configuration files

//  std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
//  start = std::chrono::high_resolution_clock::now();
  ObjectHandler.ModelicaCodeGenerator(args);

  // Timer stop
  stop = std::chrono::high_resolution_clock::now();
  secs = std::chrono::duration_cast<std::chrono::microseconds
  >(stop - start).count();

  std::cout << file_size/1000 << "KByte" << std::endl;
  std::cout << secs << "us" << std::endl;

  std::cout << 1000*file_size/secs << "KByte/s" << std::endl;
  print_separator();
}
