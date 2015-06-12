#include "edit.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>
#include "appbase.h"
#include "label.h"
#include "log.h"

NS_CROSSANY_BEGIN
NS_CROSSANY_UI_BEGIN

edit::edit() {
}

edit::~edit(){
}

bool edit::create(const wchar_t* _placehoder, const char* fontfile, const int32_t& fontsize){
	mplaceholder = _placehoder;
	FT_Library lib; FT_Face face; FT_Error err;  FT_ULong ch; int32_t i, count; int32_t x = 0, y = 0;
	if (FT_Init_FreeType(&lib) == 0){
		if ((err = FT_New_Face(lib, fontfile, 0, &face)) == 0){
			if (FT_Select_Charmap(face, FT_ENCODING_UNICODE) == 0){
				FT_Set_Pixel_Sizes(face, fontsize, 0);
				count = wcslen(_placehoder);
				for (i = 0; i < count; i++){
					ch = _placehoder[i];
					if (FT_Load_Char(face, ch, /*FT_LOAD_RENDER|*/FT_LOAD_FORCE_AUTOHINT | (TRUE ? FT_LOAD_TARGET_NORMAL : FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO)) == 0){
						FT_Glyph glyph;	// �õ���ģ
						if (FT_Get_Glyph(face->glyph, &glyph) == 0){ // ������ͼ������β۸��Ƶ��µ�FT_Glyph����glyph�С������������һ�������벢������glyph�� 
							FT_Render_Glyph(face->glyph, FT_RENDER_MODE_LCD);// FT_RENDER_MODE_NORMAL  ); //ת����λͼ
							FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
							FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
							FT_Bitmap& bitmap = bitmap_glyph->bitmap;	// ȡ��λͼ����
							int width = bitmap.width;	// ��λͼ���ݿ����Լ��������������.�����ɿ��Ի�����Ҫ�Ķ��������ˡ�
							int height = bitmap.rows;
							face->size->metrics.y_ppem;			// �������뵽�豸�ռ�
							face->glyph->metrics.horiAdvance;	// ˮƽ�ı�����
							txtchar tex;
							tex.m_Width = width;
							tex.m_Height = height;
							tex.m_adv_x = face->glyph->advance.x / 64.0f;		// �������
							tex.m_adv_y = face->size->metrics.y_ppem;			// m_FT_Face->glyph->metrics.horiBearingY / 64.0f;
							tex.m_delta_x = (float)bitmap_glyph->left;			// left:����ԭ��(0,0)������λͼ��������ص�ˮƽ����.�����������ص���ʽ��ʾ�� 
							tex.m_delta_y = (float)bitmap_glyph->top - height;	// Top: ���������β۵�bitmap_top�ֶΡ�
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

							glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuf);  //ָ��һ����ά������ͼƬ
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);							   //glTexParameteri():�������
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
							glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);								//������л��

							delete[] pBuf;
							mtexplaceholder.push_back(tex);
						}

					}
				}
			}

			FT_Done_Face(face);
		}
	}
	return true;
}


void edit::customdraw(){
	int32_t sx = 0, sy = 0, maxH = 0, height = 0;
	std::vector<txtchar>::iterator iter;
	if (mfocus){ // get input focus

	} else{ // losted input focus
		if (mtxtval.empty()){
			size_t nLen = mtexplaceholder.size();
			sx = mrc.getpos().getx(); sy = mrc.getpos().gety();
			if (nLen > 0){
				height = mtexplaceholder.begin()->m_Height;
				for (iter = mtexplaceholder.begin(); iter != mtexplaceholder.end(); iter++){
					txtchar& tex = *iter;
					glBindTexture(GL_TEXTURE_2D, tex.texid);							//�󶨵�Ŀ������
					int w = tex.m_Width;
					int h = tex.m_Height;

					int ch_x = sx + tex.m_delta_x;
					int ch_y = sy + height - h - tex.m_delta_y;

					if (maxH < h) maxH = h;
					glBegin(GL_QUADS);													 // ����һ����һ��ԭʼ�Ķ���
					{
						glTexCoord2f(0.0f, 1.0f); glVertex3f(ch_x, appbase::geth() - ch_y, 1.0f); // ���Ͻ�
						glTexCoord2f(1.0f, 1.0f); glVertex3f(ch_x + w, appbase::geth() - ch_y, 1.0f);//���Ͻ�
						glTexCoord2f(1.0f, 0.0f); glVertex3f(ch_x + w, appbase::geth() - (ch_y + h), 1.0f);//���½�
						glTexCoord2f(0.0f, 0.0f); glVertex3f(ch_x, appbase::geth() - (ch_y + h), 1.0f);//���½�
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
	}
}

void edit::ontouchbegin(const msg*){
	mtouchbegin = true;
	if (appbase::mfocus != nullptr){
		if (appbase::mfocus != this){
			appbase::mfocus->mfocus = false;
			appbase::mfocus = this;
		}
	}
	mfocus = true;



}

void edit::ontouchend(const msg* m){
	if (mtouchbegin){
		//crossany::log("ok...");
		crossany::log::otprint("test");
	}
	mtouchbegin = false;
}


NS_CROSSANY_UI_END
NS_CROSSANY_END
