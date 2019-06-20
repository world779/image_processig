#include <gd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int char_compare(const unsigned char *a, const unsigned char *b)
{
  if(*a < *b) return -1;
  else if(*a > *b) return 1;
  else return 0;
}

int median_value(int c[9]){
  int i,j,buf;

  for(j=0;j<8;j++){
    for(i=0;i<8;i++){
      if (c[i+1]<c[i]){
	buf=c[i+1];
	c[i+1]=c[i];
	c[i]=buf;
      }
    }
  }
  return c[4];
}




int main(const int argc,const char *argv[]){

  FILE *out,*in;
  gdImagePtr im,im_new;
  int width,height,i,j,color,r,g,b,pixel,k=0,l=0,m=0,x,y,z;
  int bufr[9],bufg[9],bufb[9];
  //unsigned char bufr[9];
  //double y;

  if(argv[1]==NULL||argv[2]==NULL||!strcmp(argv[1],argv[2])){
    printf("argument error\n");
    exit(-1);
  }

  //第一引数で指定されたファイルを読み出し用にオープン
  if((in=fopen(argv[1],"r"))==NULL){
    printf("file open error for %s\n",argv[1]);
    exit(-1);
  }
  //第二引数で指定されたファイルを書き出し用にオープン
  if((out=fopen(argv[2],"wb"))==NULL){
    printf("file open error for %s\n",argv[2]);
    exit(-1);
  }

  //im に画像を読み込み
  im = gdImageCreateFromJpeg(in);

  //入力画像のサイズを取得
  width=gdImageSX(im);
  height=gdImageSY(im);

  //新しい画像を用意
  im_new= gdImageCreateTrueColor(width,height);

  for(i=1;i<width-1;i++){
    for(j=1;j<height-1;j++){      
      //im の (i,j) におけるカラーインデックスの取得
      pixel=gdImageGetPixel(im,i-1,j-1); 
      //im の (i,j) における r,g,b の値を取得
      bufr[0]=gdImageRed(im,pixel);    
      bufg[0]=gdImageGreen(im,pixel);
      bufb[0]=gdImageBlue(im,pixel);
  
      pixel=gdImageGetPixel(im,i-1,j);
      bufr[1]=gdImageRed(im,pixel);    
      bufg[1]=gdImageGreen(im,pixel);
      bufb[1]=gdImageBlue(im,pixel);

      pixel=gdImageGetPixel(im,i-1,j+1);
      bufr[2]=gdImageRed(im,pixel);    
      bufg[2]=gdImageGreen(im,pixel);
      bufb[2]=gdImageBlue(im,pixel);

      pixel=gdImageGetPixel(im,i,j-1);
      bufr[3]=gdImageRed(im,pixel);    
      bufg[3]=gdImageGreen(im,pixel);
      bufb[3]=gdImageBlue(im,pixel);

      pixel=gdImageGetPixel(im,i,j);
      bufr[4]=gdImageRed(im,pixel);    
      bufg[4]=gdImageGreen(im,pixel);
      bufb[4]=gdImageBlue(im,pixel);

      pixel=gdImageGetPixel(im,i,j+1);
      bufr[5]=gdImageRed(im,pixel);    
      bufg[5]=gdImageGreen(im,pixel);
      bufb[5]=gdImageBlue(im,pixel);

      pixel=gdImageGetPixel(im,i+1,j-1);
      bufr[6]=gdImageRed(im,pixel);    
      bufg[6]=gdImageGreen(im,pixel);
      bufb[6]=gdImageBlue(im,pixel);

      pixel=gdImageGetPixel(im,i+1,j);
      bufr[7]=gdImageRed(im,pixel);    
      bufg[7]=gdImageGreen(im,pixel);
      bufb[7]=gdImageBlue(im,pixel);

      pixel=gdImageGetPixel(im,i+1,j+1);
      bufr[8]=gdImageRed(im,pixel);    
      bufg[8]=gdImageGreen(im,pixel);
      bufb[8]=gdImageBlue(im,pixel);

      
	
     
      x=median_value(bufr);
      y=median_value(bufg);
      z=median_value(bufb);
      
      color=gdImageColorExact(im_new,x,y,z);
      gdImageSetPixel(im_new,i,j,color);      
    }  
  }
  
  gdImageJpeg(im_new,out,-1);

  fclose(in);
  fclose(out);

  return 0;
  
}
