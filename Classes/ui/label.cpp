#include "label.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>
#include "appbase.h"
#include "../log.h"

#pragma  warning(disable:4996)

NS_CROSSANY_BEGIN
NS_CROSSANY_UI_BEGIN

label::label():mmaxh(0){
	mwt = fixed;
	mht = fixed;
}

label::~label()
{
}
bool saveBmp(char *bmpName, unsigned char  *imgBuf,
	int width, int height,
	int gBiBitCount, RGBQUAD *gPColorTable)
{
	/// 如果位图数据指针为0，则没有数据传入，函数返回
	if (!imgBuf)
	{
		return 0;
	}

	/// 颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0
	int colorTablesize = 0;
	if (gBiBitCount == 8)
	{
		colorTablesize = 1024;
	}

	/// 待存储图像数据每行字节数为4的倍数
	int lineByte = (width * gBiBitCount / 8 + 3) / 4 * 4;

	/// 以二进制写的方式打开文件
	FILE *fp = fopen(bmpName, "wb");

	if (fp == 0)
	{
		return 0;
	}

	/// 申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42; ///<bmp类型

							  /// bfSize是图像文件4个组成部分之和
	fileHead.bfSize = sizeof(BITMAPFILEHEADER)
		+ sizeof(BITMAPINFOHEADER)
		+ colorTablesize + lineByte * height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;

	/// bfOffBits是图像文件前3个部分所需空间之和
	fileHead.bfOffBits = 54 + colorTablesize;

	/// 写文件头进文件
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);

	/// 申请位图信息头结构变量，填写信息头信息
	BITMAPINFOHEADER head;
	head.biBitCount = gBiBitCount;
	head.biClrImportant = 0;
	head.biClrUsed = 0;
	head.biCompression = 0;
	head.biHeight = height;
	head.biPlanes = 1;
	head.biSize = 40;
	head.biSizeImage = lineByte*height;
	head.biWidth = width;
	head.biXPelsPerMeter = 0;
	head.biYPelsPerMeter = 0;

	/// 写位图信息头进内存
	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	/// 如果灰度图像，有颜色表，写入文件 
	if (gBiBitCount == 8)
	{
		//fwrite(gPColorTable, sizeof(RGBQUAD), 256, fp);
		for (int i = 0; i < 256; i++) {
			RGBQUAD tmp;
			tmp.rgbBlue = i;
			tmp.rgbGreen = i;
			tmp.rgbRed = i;
			fwrite(&tmp, sizeof(tmp), 1, fp);
		}
	}

	///写位图数据进文件
	fwrite(imgBuf, height * lineByte, 1, fp);

	/// 关闭文件
	fclose(fp);

	return 1;
}


bool label::create(const wchar_t* _txt, const char* fontfile, const int32_t fontsize){
	FT_Library lib; FT_Face face; FT_Error err;  FT_ULong ch; int32_t i, count; int32_t x = 0, y = 0, totalw = 0, left = 0,wt,ht,len;
	FT_Glyph glyph;
	mmaxh = 0;
	if (FT_Init_FreeType(&lib) == 0){
		if ((err = FT_New_Face(lib, fontfile, 0, &face)) == 0){
			if (FT_Select_Charmap(face, FT_ENCODING_UNICODE) == 0){
				FT_Set_Pixel_Sizes(face, fontsize, 0);
				count = wcslen(_txt);
				for (i = 0; i < count; i++) {
					ch = _txt[i];
					if (FT_Load_Char(face, ch, /*FT_LOAD_RENDER|*/FT_LOAD_FORCE_AUTOHINT | (TRUE ? FT_LOAD_TARGET_NORMAL : FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO)) == 0) {
						if (FT_Get_Glyph(face->glyph, &glyph) == 0) { // 把字形图像从字形槽复制到新的FT_Glyph对象glyph中。这个函数返回一个错误码并且设置glyph。 
							FT_Render_Glyph(face->glyph, FT_RENDER_MODE_LCD);//FT_RENDER_MODE_NORMAL  ); //转化成位图
							FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
							FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
							FT_Bitmap& bitmap = bitmap_glyph->bitmap;	// 取道位图数据
							totalw += bitmap.width + bitmap_glyph->left;// +face->glyph->advance.x / 64.0f;;
							if (mmaxh < bitmap.rows) mmaxh = bitmap.rows;
							log::otprint("%C w:%d h:%d",ch,bitmap.width,bitmap.rows);
						}
					}
				}
				mtxtsize.setw(totalw);
				mtxtsize.seth(mmaxh); (fontsize);
				//totalw = (totalw + 3) / 4 * 4;
				wt = totalw;
				ht = mmaxh;//fontsize;
				mtex.mwr = wt;
				mtex.mhr = ht;
				mbmp.mwo = wt;
				mbmp.mho = ht;
				node::adj_w_h(wt, ht);
				len = wt * ht * 4;
				char* bmpbuf = new char[len];
				memset(bmpbuf, 0, len);
				int32_t height00 = -1;
				int32_t adj = 0;
				for (i = 0; i < count; i++){
					ch = _txt[i];
					if (FT_Load_Char(face, ch, /*FT_LOAD_RENDER|*/FT_LOAD_FORCE_AUTOHINT | (TRUE ? FT_LOAD_TARGET_NORMAL : FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO)) == 0){
						if (FT_Get_Glyph(face->glyph, &glyph) == 0){ // 把字形图像从字形槽复制到新的FT_Glyph对象glyph中。这个函数返回一个错误码并且设置glyph。 
							FT_Render_Glyph(face->glyph,  FT_RENDER_MODE_LCD);//FT_RENDER_MODE_NORMAL  ); //转化成位图
							FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
							FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
							FT_Bitmap& bitmap = bitmap_glyph->bitmap;	// 取道位图数据
							int32_t tmp =  (bitmap_glyph->top - bitmap.rows);
							if (tmp < 0) tmp = 0;
							if (height00 == -1) height00 = bitmap.rows;
							adj = height00 - bitmap.rows;
							log::otprint("[%C] rows:%d top:%d adj:%d maxh:%d",ch, bitmap.rows, bitmap_glyph->top, (height00 - bitmap.rows), mmaxh);
							for (int32_t j = 0; j < bitmap.rows; j++){
								int32_t lines = (j + tmp )* wt * 4;//(j + tmp ) * totalw * 4;//
								for (int32_t z = 0; z < bitmap.width; z++){
									unsigned char _vl = (z >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[z + bitmap.width*(bitmap.rows - j - 1 )];
									int32_t pos1 = lines + 4 * (z + left);
									bmpbuf[pos1 + 0] = 0xFF;
									bmpbuf[pos1 + 1] = 0xFF;
									bmpbuf[pos1 + 2] = 0xFF;
									bmpbuf[pos1 + 3] = _vl;
								}
							}
							left += bitmap.width + bitmap_glyph->left;// +face->glyph->advance.x / 64.0f;
						}
					}
				}

				//saveBmp("c:\\a111.bmp", (unsigned char*)bmpbuf, totalw, fontsize, 32, NULL);

				mtex.mw = wt;
				mtex.mh = ht;

				//glGenTextures(1, &mtex.texid);
				//glBindTexture(GL_TEXTURE_2D, mtex.texid);
				//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mtex.mw, mtex.mh, 0, GL_RGBA, GL_UNSIGNED_BYTE, bmpbuf);  //指定一个二维的纹理图片
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);							   //glTexParameteri():纹理过滤
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				//glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_KEEP);								//纹理进行混合
				mbmp.mw = wt;
				mbmp.mh = ht;
				glGenTextures(1, &mbmp.id);
				glBindTexture(GL_TEXTURE_2D, mbmp.id);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mbmp.mw, mbmp.mh, 0, GL_RGBA, GL_UNSIGNED_BYTE, bmpbuf);  //指定一个二维的纹理图片
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);							   //glTexParameteri():纹理过滤
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_KEEP);								//纹理进行混合

				delete[] bmpbuf;
			}
			FT_Done_Face(face);
		}
	}
	return true;
}

void label::customdraw(){
	
	int32_t sx = 0, height = 0;
	std::vector<txtchar>::iterator iter;
	sx = mrc.getpos().getx(); int32_t sy = mrc.getpos().gety() + mrc.geth();
	/*
	height = mtex.mh;
	glColor4f(mtxtclr.mr, mtxtclr.mg, mtxtclr.mb, mtxtclr.mt);
	glBindTexture(GL_TEXTURE_2D, mtex.texid);							//绑定到目标纹理
	glBegin(GL_QUADS);													 // 定义一个或一组原始的顶点
	// 左上角
	glTexCoord2f(0.5f, 1.0f); glVertex3f(sx, sy, 1.0f);
	// 右上角
	glTexCoord2f(1.0f, 1.0f); glVertex3f(sx + mtex.mw, sy, 1.0f);
	// 右下角
	glTexCoord2f(1.0f, 0.0f); glVertex3f(sx + mtex.mw, sy - mtex.mh, 1.0f);
	// 左下角
	glTexCoord2f(0.5f, 0.0f); glVertex3f(sx, sy - mtex.mh, 1.0f);
	glEnd();
	*/
	height = mbmp.mh;
	glColor4f(mtxtclr.mr, mtxtclr.mg, mtxtclr.mb, mtxtclr.mt);
	glBindTexture(GL_TEXTURE_2D, mbmp.id);							//绑定到目标纹理
	glBegin(GL_QUADS);													 // 定义一个或一组原始的顶点
	GLfloat ly = (GLfloat)mbmp.mho / (GLfloat)mbmp.mh + 0.01f;
	GLfloat rx = (GLfloat)mbmp.mwo / (GLfloat)mbmp.mw + 0.01f;
	GLfloat tt = (mrc.geth() - mbmp.mho) / 2.0f;
	GLfloat lt = (mrc.getw() - mbmp.mwo) / 2.0f;
	
	glTexCoord2f(0.0f, ly); glVertex3f(sx + lt, sy - tt, 1.0f); // 左上角
	glTexCoord2f(rx, 1.0f); glVertex3f(sx + lt + mbmp.mwo, sy - tt, 1.0f);// 右上角
	glTexCoord2f(rx, 0.0f); glVertex3f(sx + lt + mbmp.mwo, sy - mbmp.mho - tt, 1.0f);// 右下角
	glTexCoord2f(0.0f, 0.0f); glVertex3f(sx + lt, sy - mbmp.mho - tt, 1.0f);// 左下角
	glEnd();


	node::customdraw();
}

NS_CROSSANY_UI_END
NS_CROSSANY_END
