#include <cstdio>
#include <string>

using std::string;

int main(int argc, char *argv[]){
    string infilename;

    if(argc <= 1){
        printf("File name not provided, will use default of 'program.bin'\n");
        infilename = "program.bin";
    }else{
        infilename = string(argv[1]);
    }
    if(argc >= 3){
        printf("Too many arguments, at the momment this program only supports assembling 1 file at a time.\n");
    }

    FILE* infile = fopen64(infilename.c_str(), "rb");

    if(infile == NULL){
        printf("Failed to open input file %s\n", infilename.c_str());
        exit(-1);
    }

    string outfilename_msb = infilename.substr(0, infilename.find_last_of("."));
    outfilename_msb.append("_msb.hex");

    FILE* outfile_msb = fopen64(outfilename_msb.c_str(), "w+");

    if(outfile_msb == NULL){
        printf("Failed to open output MSB file %s\n", outfilename_msb.c_str());
        exit(-1);
    }
    
    string outfilename_lsb = infilename.substr(0, infilename.find_last_of("."));
    outfilename_lsb.append("_lsb.hex");

    FILE* outfile_lsb = fopen64(outfilename_lsb.c_str(), "w+");

    if(outfile_lsb == NULL){
        printf("Failed to open output LSB file %s\n", outfilename_lsb.c_str());
        exit(-1);
    }

    constexpr size_t numwords = 32768;
    size_t byte_count = 0;

    unsigned char access;

    while(byte_count<numwords && !(feof(infile))){
        if(fread(&access, sizeof(unsigned char), 1, infile) == 1){
            fprintf(outfile_msb, "%.2x ", access);
        }else{
            fprintf(outfile_msb, "00 ");
        }
        if(fread(&access, sizeof(unsigned char), 1, infile) == 1){
            fprintf(outfile_lsb, "%.2x ", access);
        }else{
            fprintf(outfile_lsb, "00 ");
        }
        byte_count++;
    }

    while(byte_count<numwords){
        fprintf(outfile_msb, "00 ");
        fprintf(outfile_lsb, "00 ");
        byte_count++;
    }

    fclose(infile);
    fclose(outfile_msb);
    fclose(outfile_lsb);

}