#define bsLen 16
#define hdSize 54

class BitmapStruct{

public:
	struct bs{
		char* field;
		uint8 bytes;
	};	

	bs bs[bsLen];	
	BitmapStruct(){	
		bs[0].field = "FileType";
		bs[0].bytes = 2;
		bs[1].field = "FileSize";
		bs[1].bytes = 4;
		bs[2].field = "Reserved";
		bs[2].bytes = 2;
		bs[3].field = "Reserved";
		bs[3].bytes = 2;
		bs[4].field = "PixelDataOffset";
		bs[4].bytes = 4;
		bs[5].field = "HeaderSize";
		bs[5].bytes = 4;
		bs[6].field = "ImageWidth";
		bs[6].bytes = 4;
		bs[7].field = "ImageHeight";
		bs[7].bytes = 4;
		bs[8].field = "Planes";
		bs[8].bytes = 2;
		bs[9].field = "BitsPerPixel";
		bs[9].bytes = 2;
		bs[10].field = "Compression";
		bs[10].bytes = 4;
		bs[11].field = "ImageSize";
		bs[11].bytes = 4;
		bs[12].field = "XpixelsPerMeter";
		bs[12].bytes = 4;
		bs[13].field = "YPixelsPerMeter";
		bs[13].bytes = 4;
		bs[14].field = "TotalColors";
		bs[14].bytes = 4;
		bs[15].field = "ImportantColors";
		bs[15].bytes = 4;
// 		bs[16].field = "Red";
// 		bs[16].bytes = 1;
// 		bs[17].field = "Green";
// 		bs[17].bytes = 1;
// 		bs[18].field = "Blue";
// 		bs[18].bytes = 1;
// 		bs[19].field = "Reserved";
// 		bs[19].bytes = 1;
	}
};