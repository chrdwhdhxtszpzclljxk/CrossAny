#include "label.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>
#include "appbase.h"

NS_CROSSANY_BEGIN
NS_CROSSANY_UI_BEGIN

label::label()
{
	
}

label::~label()
{
}

bool label::create(const wchar_t* _txt, const char* fontfile, const int32_t fontsize){
	FT_Library lib; FT_Face face; FT_Error err;  FT_ULong ch; int32_t i, count; int32_t x = 0, y = 0;
	if (FT_Init_FreeType(&lib) == 0){
		if ((err = FT_New_Face(lib, fontfile, 0, &face)) == 0){
			if (FT_Select_Charmap(face, FT_ENCODING_UNICODE) == 0){
				FT_Set_Pixel_Sizes(face, fontsize, 0);
				count = wcslen(_txt);
				for (i = 0; i < count; i++){
					ch = _txt[i];
					if (FT_Load_Char(face, ch, /*FT_LOAD_RENDER|*/FT_LOAD_FORCE_AUTOHINT | (TRUE ? FT_LOAD_TARGET_NORMAL : FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO)) == 0){
						FT_Glyph glyph;	// 得到字模
						if (FT_Get_Glyph(face->glyph, &glyph) == 0){ // 把字形图像从字形槽复制到新的FT_Glyph对象glyph中。这个函数返回一个错误码并且设置glyph。 
							FT_Render_Glyph(face->glyph, FT_RENDER_MODE_LCD);// FT_RENDER_MODE_NORMAL  ); //转化成位图
							FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
							FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
							FT_Bitmap& bitmap = bitmap_glyph->bitmap;	// 取道位图数据
							int width = bitmap.width;	// 把位图数据拷贝自己定义的数据区里.这样旧可以画到需要的东西上面了。
							int height = bitmap.rows;
							face->size->metrics.y_ppem;			// 伸缩距离到设备空间
							face->glyph->metrics.horiAdvance;	// 水平文本排列
							txtchar tex;
							tex.m_Width = width;
							tex.m_Height = height;
							tex.m_adv_x = face->glyph->advance.x / 64.0f;		// 步进宽度
							tex.m_adv_y = face->size->metrics.y_ppem;			// m_FT_Face->glyph->metrics.horiBearingY / 64.0f;
							tex.m_delta_x = (float)bitmap_glyph->left;			// left:字形原点(0,0)到字形位图最左边象素的水平距离.它以整数象素的形式表示。 
							tex.m_delta_y = (float)bitmap_glyph->top - height;	// Top: 类似于字形槽的bitmap_top字段。
							glGenTextures(1, &tex.texid);
							glBindTexture(GL_TEXTURE_2D, tex.texid);
							char* pBuf = new char[width * height * 4];
							for (int j = 0; j < height; j++){
								for (int i = 0; i < width; i++){
									unsigned char _vl = (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width*j];
									pBuf[(4 * i + (height - j - 1) * width * 4) + 0] = 0xFF;
									pBuf[(4 * i + (height - j - 1) * width * 4) + 1] = 0xFF;
									pBuf[(4 * i + (height - j - 1) * width * 4) + 2] = 0xFF;
									pBuf[(4 * i + (height - j - 1) * width * 4) + 3] = _vl;//0xFF;
								}
							}

							glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuf);  //指定一个二维的纹理图片
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);							   //glTexParameteri():纹理过滤
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
							glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);								//纹理进行混合

							delete[] pBuf;
							mtex.push_back(tex);
						}

					}
				}
			}

			FT_Done_Face(face);
		}
	}
	return true;
}

void label::customdraw(){
	int32_t sx = 0, sy = 0, maxH = 0, height = 0;
	std::vector<txtchar>::iterator iter;
	size_t nLen = mtex.size();
	sx = mrc.getpos().getx(); sy = mrc.getpos().gety();
	if (nLen > 0){
		height = mtex.begin()->m_Height;
		for (iter = mtex.begin(); iter != mtex.end(); iter++){
			txtchar& tex = *iter;
			glBindTexture(GL_TEXTURE_2D, tex.texid);							//绑定到目标纹理
			int w = tex.m_Width;
			int h = tex.m_Height;

			int ch_x = sx + tex.m_delta_x;
			int ch_y = sy + height - h - tex.m_delta_y;

			if (maxH < h) maxH = h;
			glBegin(GL_QUADS);													 // 定义一个或一组原始的顶点
			{
				glTexCoord2f(0.0f, 1.0f); glVertex3f(ch_x, appbase::geth() - ch_y, 1.0f); // 左上角
				glTexCoord2f(1.0f, 1.0f); glVertex3f(ch_x + w, appbase::geth() - ch_y, 1.0f);//右上角
				glTexCoord2f(1.0f, 0.0f); glVertex3f(ch_x + w, appbase::geth() - (ch_y + h), 1.0f);//右下角
				glTexCoord2f(0.0f, 0.0f); glVertex3f(ch_x, appbase::geth() - (ch_y + h), 1.0f);//左下角
			}
			glEnd();
			sx += tex.m_adv_x;
			//if (sx > x + maxW)
			//{
			//	sx = x; sy += maxH + 12;
			//}
			//break;
		}
	}

}

NS_CROSSANY_UI_END
NS_CROSSANY_END
