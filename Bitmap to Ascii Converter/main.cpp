#include <MyLibs\bitmap.h>
#include <map>
#include <fstream>
#include<iostream>
#include<string>
using namespace std;

typedef char BYTE;

void main(){

	//unsigned color = getpixel();

	const BYTE patch_dim = 8;
	unsigned iNum = 0;

	unsigned data[patch_dim][patch_dim];

	//unsigned data[MAX_SPRITES][patch_dim][patch_dim];

	cout<<"Filename: ";
	string filename;
	cin>>filename;

	raw_bmp* bitty = new raw_bmp(filename);
	map<unsigned, unsigned> index;

	unsigned max_columns = (bitty->width)/patch_dim; //columns of sprites, same as rows
//everyother is blank so we get 2x-1
	
	fstream filestr ("test.txt", fstream::out);

	for(int ir(0); ir < (bitty->height); ir += patch_dim){
		for(int ic(0); ic < (bitty->width); ic += patch_dim){	
			for(int ary_i(0), i(ic); i < (patch_dim +ic); ++ary_i, ++i){
				for(int ary_j(0), j(ir); j < (patch_dim +ir); ++ary_j, ++j){//relative			
					BYTE blue = bitty->pixel_elem(i, j, 0);//returns the start of pixel dat
					//   -> {[B], [G], [R]}
					//
					//there bytes!
					BYTE green	= bitty->pixel_elem(i, j, 1);
					BYTE red	= bitty->pixel_elem(i, j, 2);
					
					unsigned clr(0);

					clr = 0x00FFFFFF & ( ( ( (unsigned) red )& 0x000000FF) << 16) 
						| ( ( ( (unsigned) green) & 0x000000FF) << 8) | ((unsigned) blue & 0x000000FF);

					pair<map<unsigned,unsigned>::iterator, bool> pr;

					pr = index.insert(pair<unsigned, unsigned>(clr, iNum));

					//data[(patch_dim - ary_j) -1][ary_i] = (index.insert(pair<BYTE, unsigned>(clr, iNum))).second? (index.insert(pair<BYTE, unsigned>(clr, iNum))).first->second : (index.insert(pair<BYTE, unsigned>(clr, iNum++))).first->second;

					if(pr.second)	//index was not found
						++iNum;
					//patch_dim-i
					//cout<<iNum<<" "<< (((unsigned short)pr.first->first ) &0x00FF) <<" "<<pr.first->second<<" "<<pr.second<<endl;
					data[(patch_dim - ary_j) -1][ary_i] = pr.first->second;
					
					
				}
				
			}
			filestr<<"ary[patch_dim][patch_dim] = {"<<endl;
			for(int y =0; y<patch_dim; ++y){


				filestr<<"\t\t\t\t{";

				for(int x =0; x <patch_dim; ++x){
					filestr<<data[y][x];
					if(x < patch_dim-1) filestr<<", ";
				}

				if(y < patch_dim-1) filestr<<"},"<<endl;
				else				filestr<<"}"<<endl;
			}
			filestr<<"\t\t\t     };"<<endl;
			filestr<<endl;
		}
	}

	filestr.close();

	map<unsigned,unsigned>::iterator pr = index.begin();;
	
	cout<<"\n\n"<<flush;
	while(pr != index.end()){
		cout<<"Value: "<<hex<<((unsigned short)pr->first )<<"\t Index Value: "<<pr->second<<endl;

		++pr;
	}
	
}