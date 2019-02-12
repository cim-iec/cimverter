#include <chrono>
#include "CIMObjectHandler.h"
#include <dirent.h>
#include <getopt.h>
#include <unistd.h>

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
inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
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
  std::cout << "Parse the separated files by option -f:" << std::endl;
  std::cout << "./CIMverter -f <file2.xml> <file2.xml>" << std::endl;
  std::cout << std::endl;
  std::cout << "Parse all files in a folder by option -a:" << std::endl;
  std::cout << "./CIMverter -a <xml_directory/>" << std::endl;
  std::cout << std::endl;
  std::cout << "Use verbose option for more information by using --verbose:" << std::endl;
  std::cout << "./CIMverter --verbose" << std::endl;
  std::cout << std::endl;
  std::cout << "Change Output File Name by using option -o:" << std::endl;
  std::cout << "./CIMverter -o [modelica_output_file_name]" << std::endl;
  std::cout << std::endl;
  std::cout << "Change Template Folder by using option -t:" << std::endl;
  std::cout << "./CIMverter -t [template_folder_name]" << std::endl;
  std::cout << std::endl;
  std::cout << "Complete example to parse all files in a directory using"
          " verbose for more information and using a custom output file name" << std::endl;
  std::cout << "./CIMverter -a <xml_directory/> --verbose -o [modelica_output_file_name]" << std::endl;
  exit(1);
}

int main(int argc, char *argv[]) {
    std::string output_file_name;// Arguments for the ObjectHandler
    std::string template_folder = "ModPowerSystems_templates";

    static int verbose_flag = 0;

    long file_size;// File size
    long secs;// Time in seconds

    // Check for arguments
    print_separator();

    CIMModel cimModel;
    if (argc <= 2) {
        std::cerr << "Too few arguments:" << std::endl;
        print_argument_help();
    }else{

        output_file_name = "default_output_name";// Push output modelica filename
        int c;


        while (1){
              static struct option long_options[] =
                    {
                            /* These options set a flag. */
                            {"verbose", no_argument,       &verbose_flag, 1},
                            {"all",     required_argument,       0, 'a'},
                            {"file",  required_argument,       0, 'f'},
                            {"output",  required_argument,       0, 'o'},
                            {"template",  required_argument,       0, 't'},
                            {0, 0, 0, 0}
                    };
            /* getopt_long stores the option index here. */
            int option_index = 0;

            //c = getopt (argc, argv, "abc");
            c = getopt_long(argc, argv, "o:a:f:t:",long_options, &option_index);

            std::vector<std::string> files;
            if (c == -1)
                break;
            switch (c)
            {
                // Read files with -f
                case 'f':
                    optind--;
                    for( ;optind < argc && *argv[optind] != '-'; optind++){
                        std::cout << "CIM-XML file is:" << ( argv[optind] ) << std::endl;
                        file_size += filesize(( argv[optind] ));
                        cimModel.addCIMFile(( argv[optind] ));
                    }
                    break;
                // Define the name of the output files with -o
                case 'o':
                    output_file_name = optarg;
                    break;
                // Read folders with -a
                case 'a':
                    if(!ends_with(optarg, "/")){
                        files = search_folder(strcat(optarg, "/"));
                    }
                    else{
                        files = search_folder(optarg);
                    }

                    for (auto f : files)
                    {
                        std::cout << "CIM-XML file is:" << f << std::endl;
                        file_size += filesize(f.c_str());
                        cimModel.addCIMFile(f);
                    }
                    break;
                case 't':
                    template_folder = optarg;
                    break;
                case '?':
                    std::cerr << "unknown argument " << c << "\n";
                    print_argument_help();
                    break;

            }
        }
    }
    // Print unused Arguments
    if (optind < argc)
    {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
    }
  // Check if verbose mode is used
  if(verbose_flag)
  {
      std::cout << "verbose activated \n";
  }


  // Timer start
  std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
  start = std::chrono::high_resolution_clock::now();

  //set off the Dependency check
  cimModel.setDependencyCheckOff();

  cimModel.parseFiles();// Parser begin!
  CIMObjectHandler ObjectHandler(std::move(cimModel.Objects));// r-value
  ObjectHandler.get_config(template_folder);// Get configuration files

  ObjectHandler.ModelicaCodeGenerator(output_file_name, verbose_flag);

  // Timer stop
  stop = std::chrono::high_resolution_clock::now();
  secs = std::chrono::duration_cast<std::chrono::microseconds
  >(stop - start).count();

  std::cout << file_size/1000 << "KByte" << std::endl;
  std::cout << secs << "us" << std::endl;

  std::cout << 1000*file_size/secs << "KByte/s" << std::endl;
  print_separator();
}
