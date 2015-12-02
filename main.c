#include <ft2build.h>
#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>
#include FT_FREETYPE_H

int main(int argc,char **argv)
{
    int ret;
    FT_Face face;
    FT_Library library; 
    FT_Glyph glyph;

    if(argc != 2) {
        fprintf(stderr,"Usage : %s <font file>\n",argv[0]);
        return -1;
    }

    FT_Init_FreeType(&library);
    ret = FT_New_Face(library,argv[1],0,&face);
    FT_Set_Pixel_Sizes(face,12,12);
    printf("unsigned short bitmap [] = {\n");
    for(int c = 0;c < 65535;c++) {
        FT_Load_Glyph(face, FT_Get_Char_Index(face,c), FT_LOAD_DEFAULT);  
        FT_Get_Glyph( face->glyph, &glyph);
        FT_Render_Glyph( face->glyph, FT_RENDER_MODE_NORMAL ); 
        FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
        FT_Bitmap *bitmap = &bitmap_glyph->bitmap;
        int rows = bitmap->rows;
        int cols = bitmap->width;
        for(int y = 0;y < rows;y++) {
            unsigned short t = 0;
            for(int x = 0;x < cols;x++) {
                if(bitmap->buffer[y * cols + x])
                    t |= 1 << x;
            }
            printf("0x%04x,",t);
        }

        for(int y = rows;y < 12;y++)
            printf("0x0000,");

        printf("\n");
    }
    printf("};\n");
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
}
