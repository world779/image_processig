#include <gd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(const int argc,const char *argv[]){
  FILE *out,*in;
  gdImagePtr im,im_new;
  int width,height,i,j,color,r,g,b,pixel;
  int buf[9];
  double y;

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

      pixel=gdImageGetPixel(im,i,j);
     
      r=gdImageRed(im,pixel);
      g=gdImageGreen(im,pixel);
      b=gdImageBlue(im,pixel);

      y=0.299*r+0.587*g+0.114*b;
      
      color=gdImageColorExact(im_new,y,y,y);
      gdImageSetPixel(im_new,i,j,color);
      
    }  
  }
  
  gdImageJpeg(im_new,out,-1);

  fclose(in);
  fclose(out);

  return 0;
  
}
