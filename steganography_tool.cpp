#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "lodepng/lodepng.h"

using namespace std;


//read the png file using lodepng
void read_png_file(const char* filename,vector<unsigned char>&image,unsigned &width,unsigned &height){
    unsigned error=lodepng::decode(image,width,height,filename);
    if(error){
        cerr<<"Decoder error "<<error<<": "<<lodepng_error_text(error)<<"\n";
        exit(1);
    }
}


//write the png file using lodepng

void write_png_file(const char* filename,const vector<unsigned char>&image,unsigned width,unsigned height){
    unsigned error=lodepng::encode(filename,image,width,height);
    if(error){
        cerr<<"Encoder error "<<error<<": "<<lodepng_error_text(error)<<"\n";
        exit(1);
    }
}

//function to embed the message into the image

void embed_message(vector<unsigned char>&image,const string &message){
    //convert message to binary string
    string binary_message;
    for(char c:message){
        for(int i=7;i>=0;i--){
            binary_message+=((c>>i)&1)?'1':'0';
        }
    }
    //add a null terminator to indicate the end of the message

    binary_message+="00000000";

    size_t max_bits=image.size();

    if(binary_message.size()>max_bits){
        cerr<<"Message is too large to be hidden in this image.\n";
        exit(1);
    }

    //embed the message into the image

    for(size_t i=0;i<binary_message.size();i++){
        image[i]&=0xFE;//set LSB to zero
        image[i]|=(binary_message[i]=='1')?'1':'0';
    }
}

string extract_message(const vector<unsigned char>&image){
    string message;
    char current_char=0;
    int bit_count=0;
    for(size_t i=0;i<image.size();i++){
        current_char=(current_char<<1)|(image[i]&1);
        bit_count++;
        //since each character can have a maximum 8 bits
        if(bit_count==8){
            if(current_char=='\0'){
                return message;
            }
            message+=current_char;
            bit_count=0;
            current_char=0;
        }
    }
    return message;
}

int main(int argc,char *argv[]){
    if(argc<4){
        cout<<"Usage:\n";
        cout<<" To embed:  "<<argv[0]<<"--embed <input_png> <output_png> <message_file>\n";
        cout<<" To extract:  "<<argv[0]<<"--extract <input_png> <output_text_file>\n";
        return 1;
    }
    string mode=argv[1];
    if(mode=="--embed"){
        if(argc!=5){
            cout<<"Invalid arguments for embedding.\n";
            return 1;
        }
        const char *input_png=argv[2];
        const char *output_png=argv[3];
        const char *message_file=argv[4];

        //read message from file
        ifstream msg_file(message_file,ios::binary);

        if(!msg_file.is_open()){
            cerr<<"Could not open message file: "<<message_file<<"\n";
            return 1;
        }
        string message((istreambuf_iterator<char>(msg_file)),istreambuf_iterator<char>());
        msg_file.close();

        //read the input png file

        vector<unsigned char>image;
        unsigned width,height;
        read_png_file(input_png,image,width,height);

        //embed the message

        embed_message(image,message);

        //write the output png file

        write_png_file(output_png,image,width,height);
        
        cout<<"Message embedded successfullly into "<<output_png<<"\n";
    }
    else if(mode=="--extract"){
        if (argc != 4){
            cout << "Invalid arguments for extraction.\n";
            return 1;
        }

        const char *input_png = argv[2];
        const char *output_text_file = argv[3];

        // Read the input PNG file
        vector<unsigned char> image;
        unsigned width, height;
        read_png_file(input_png, image, width, height);

        // Extract the message
        string message = extract_message(image);

        // Write the message to output file
        ofstream out_file(output_text_file, ios::binary);
        if (!out_file.is_open()){
            cerr<<"Could not open output text file: "<<output_text_file<<"\n";
            return 1;
        }
        out_file<<message;
        out_file.close();

        cout<<"Message extracted successfully to "<<output_text_file<< "\n";
    }
    else{
        cout<<"Invalid mode. Use --embed or --extract.\n";
        return 1;
    }
    return 0;
}