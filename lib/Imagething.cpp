//ImageThing
#ifndef ImageThing_cpp
#define ImageThing_cpp

#include <cstdint>
#include <fstream>
#include "Matrix.cpp"
#include <string>


#pragma pack(push, 1)
struct BmpInfoHeader {
    uint32_t sizeofThisHeader = 40;
    int32_t width = 512;
    int32_t height = 512;
    uint16_t numberOfColorPlanes = 1;
    uint16_t colorDepth = 24;
    uint32_t compressionMethod = 0;
    uint32_t rawBitmapDataSize = 0; 
    int32_t horizontalResolution = 3780;
    int32_t VerticalResolution = 3780;
    uint32_t colorTableEntreis = 0;
    uint32_t importantColors = 0;
};

struct BmpHeader{
    char bitmapSignatureBytes[2] = {'B','M'};
    uint32_t sizeOfBitmapFile = 0; // DEFINE AS the size of BmpInfoHeader + size of BmpHeader + (height * widith * 3) for 24 bit color
    uint32_t reservedBytes = 0;
    uint32_t pixleDataOffset = 0; // sizeof(BmpInfoHdader) + sizeof(BmpHeader)

};

#pragma pack(pop)

struct PixleData{ // backward from RGB i guess
    MatrixRaw blue;
    MatrixRaw green;
    MatrixRaw red;
};
struct Pixle{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

Pixle PixleDataMatrixtoPixle(const PixleData& data,int x ,int y){
    Pixle temp;
    temp.blue = static_cast<uint8_t>(data.blue[x][y]);
    temp.green = static_cast<uint8_t>(data.green[x][y]);
    temp.red = static_cast<uint8_t>(data.red[x][y]);
    return temp;
}

PixleData TestImage(){
    int height = 512;
    int widith = 512;

    PixleData temp;
    vector<double> temprow;

    for(int h = 0; h < height; h++){
        for(int w = 0; w < widith; w++){
            temprow.push_back(((static_cast<double>(w))/512.0) * 255.0); 
        }
        temp.blue.push_back(temprow);
        temp.green.push_back(temprow);
        temp.red.push_back(temprow);
        temprow.clear();

    }
    return temp;
}

void WriteImage(PixleData data,string name){
    BmpInfoHeader InfoHeader;
   
    BmpHeader BmpHeader;

    InfoHeader.width = data.blue[0].size();
    InfoHeader.height = data.blue.size();
    InfoHeader.sizeofThisHeader = static_cast<uint32_t>(sizeof(InfoHeader));

    BmpHeader.pixleDataOffset = static_cast<uint32_t>( 14 + 40);

    

    uint32_t rowSize = (InfoHeader.width * 3 + 3) & ~3;
    InfoHeader.rawBitmapDataSize = rowSize * InfoHeader.height;

    BmpHeader.sizeOfBitmapFile = (14 + 40 + InfoHeader.rawBitmapDataSize);

    ofstream fout(name, ios::binary);

    fout.write((char *) &BmpHeader, 14);
    fout.write((char *) &InfoHeader, 40);

    for(int y = InfoHeader.height -1; y >= 0; y--){
        for(int x = 0; x < InfoHeader.width; x++){
            Pixle currentPixle = PixleDataMatrixtoPixle(data, y ,x);
            fout.write((char *) &currentPixle, 3);
        }
    }

    


}

#endif