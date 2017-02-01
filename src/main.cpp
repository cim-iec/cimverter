#include <chrono>
#include "CIMObjectHandler.h"
#include <dirent.h>

unsigned int filesize(const char* filename) {
  std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
  unsigned int size = in.tellg();
  in.close();
  return size;
}

std::vector<std::string> search_folder(const char *path) {

    struct dirent* ent = NULL;
    DIR *pDir;
    pDir = opendir(path);
    std::vector<std::string> files;

    while (NULL != (ent = readdir(pDir))) {

        std::string _path(path);
        std::string _dirName(ent->d_name);
        std::string file_path = _path + _dirName;
        files.push_back(file_path);
    }
    return files;

}

std::string modelica_filename("modelica_example");

int main(int argc, const char **argv) {

    unsigned long file_size;
    unsigned long secs;

  // Check for arguments
  if (argc <= 2) {
      if (strcmp(argv[1], "--help") == 0) {
          std::cout << "usage:" << std::endl;
          std::cout << "./CIM2Mod -f file2.xml file2.xml... modelica_output_file_name" << std::endl;
          std::cout << "./CIM2Mod -a xml_directory/ modelica_output_file_name" << std::endl;
          exit(1);
      } else {
          std::cerr << "Too few arguments:" << std::endl;
          std::cout << "usage:" << std::endl;
          std::cout << "./CIM2Mod -f file2.xml file2.xml... modelica_output_file_name" << std::endl;
          std::cout << "./CIM2Mod -a xml_directory/ modelica_output_file_name" << std::endl;
          exit(1);
      }
  }

    print_separator();

  CIMParser parser;

    if(argc > 2) {
        file_size = 0;
        if(strcmp(argv[1], "-f") == 0) {
            for(int i = 2; i < argc-1; i++)
            {
                std::cout << "CIM-XML file is:" << argv[i] << std::endl;
                file_size += filesize(argv[i]);
                parser.parse_file(argv[i]);
            }
            modelica_filename = argv[argc-1];

        } else if (strcmp(argv[1], "-a") == 0) {
            // Find all relevant files
            auto files = search_folder(argv[2]);

            for(auto f : files){
                std::cout << "CIM-XML file is:" << f << std::endl;
                file_size += filesize(f.c_str());
                parser.parse_file(f);
            }
            modelica_filename = argv[argc-1];
        } else {
            std::cout << "usage:" << std::endl;
            std::cout << "./CIM2Mod -f file2.xml file2.xml... modelica_output_file_name" << std::endl;
            std::cout << "./CIM2Mod -a xml_directory/ modelica_output_file_name" << std::endl;
            exit(1);
        }
    }

  // Timer start
  std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
  start = std::chrono::high_resolution_clock::now();

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
