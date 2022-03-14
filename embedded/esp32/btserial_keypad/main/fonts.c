/**
 * @file fonts.c
 * @brief Fonts source
 * 
 * @addtogroup LCD
 * @{
 */

/**
 * LCD/OLED fonts library
 *
 * FIXME: License?
 *
 * @date: 8 dec. 2016
 *      Author: zaltora
 */
#include "fonts.h"

/**
 * @brief Include GLCD 5x7 font
 * 
 */
#define FONTS_GLCD_5X7

/**
 * @brief  Include BitOCRA 4x7 font
 * 
 */
#define FONTS_BITOCRA_4X7

/**
 * @brief  Include Terminus 6x12 font
 * 
 */
#define FONTS_TERMINUS_6X12_ISO8859_1

/**
 * @brief Include Terminus 8x14 font
 * 
 */
#define FONTS_TERMINUS_8X14_ISO8859_1

/**
 * @brief Include Terminus 10x18 font
 * 
 */
#define FONTS_TERMINUS_10X18_ISO8859_1

/**
 * @brief Include Terminus 12x24 font
 * 
 */
#define FONTS_TERMINUS_12X24_ISO8859_1

/**
 * @brief Include Terminus 8x14 (Bold) font
 * 
 */
#define FONTS_TERMINUS_BOLD_8X14_ISO8859_1

/**
 * @brief  Include Terminus 10x18 (Bold) font
 * 
 */
#define FONTS_TERMINUS_BOLD_10X18_ISO8859_1

/**
 * @brief  Include Terminus 12x24 (Bold) font
 * 
 */
#define FONTS_TERMINUS_BOLD_12X24_ISO8859_1

/////////////////////////////////////////////

#ifdef FONTS_GLCD_5X7
 #include "fonts/font_glcd_5x7.h"
#endif

#ifdef FONTS_BITOCRA_4X7
#include "fonts/font_bitocra_4x7_ascii.h"
#endif

#ifdef FONTS_TERMINUS_6X12_ISO8859_1
 #include "fonts/font_terminus_6x12_iso8859_1.h"
#endif

#ifdef FONTS_TERMINUS_8X14_ISO8859_1
 #include "fonts/font_terminus_8x14_iso8859_1.h"
#endif

#ifdef FONTS_TERMINUS_BOLD_8X14_ISO8859_1
 #include "fonts/font_terminus_bold_8x14_iso8859_1.h"
#endif

#ifdef FONTS_TERMINUS_10X18_ISO8859_1
 #include "fonts/font_terminus_10x18_iso8859_1.h"
#endif

#ifdef FONTS_TERMINUS_BOLD_10X18_ISO8859_1
 #include "fonts/font_terminus_bold_10x18_iso8859_1.h"
#endif

#ifdef FONTS_TERMINUS_12X24_ISO8859_1
 #include "fonts/font_terminus_12x24_iso8859_1.h"
#endif

#ifdef FONTS_TERMINUS_BOLD_12X24_ISO8859_1
 #include "fonts/font_terminus_bold_12x24_iso8859_1.h"
#endif

/////////////////////////////////////////////

// FIXME: this declaration is noisy

const font_info_t *font_builtin_fonts[] = {

#ifdef FONTS_GLCD_5X7
  [FONT_FACE_GLCD5x7] = &_fonts_glcd_5x7_info,
#else
  [FONT_FACE_GLCD5x7] = NULL,
#endif

#ifdef FONTS_BITOCRA_4X7
  [FONT_FACE_BITOCRA_4X7] = &_fonts_bitocra_4x7_ascii_info,
#else
  [FONT_FACE_BITOCRA_4X7] = NULL,
#endif

#ifdef FONTS_TERMINUS_6X12_ISO8859_1
  [FONT_FACE_TERMINUS_6X12_ISO8859_1] = &_fonts_terminus_6x12_iso8859_1_info,
#else
  [FONT_FACE_TERMINUS_6X12_ISO8859_1] = NULL,
#endif

#ifdef FONTS_TERMINUS_8X14_ISO8859_1
  [FONT_FACE_TERMINUS_8X14_ISO8859_1] = &_fonts_terminus_8x14_iso8859_1_info,
#else
  [FONT_FACE_TERMINUS_8X14_ISO8859_1] = NULL,
#endif

#ifdef FONTS_TERMINUS_BOLD_8X14_ISO8859_1
  [FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1] = &_fonts_terminus_bold_8x14_iso8859_1_info,
#else
  [FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1] = NULL,
#endif

#ifdef FONTS_TERMINUS_10X18_ISO8859_1
  [FONT_FACE_TERMINUS_10X18_ISO8859_1] = &_fonts_terminus_10x18_iso8859_1_info,
#else
  [FONT_FACE_TERMINUS_10X18_ISO8859_1] = NULL,
#endif

#ifdef FONTS_TERMINUS_BOLD_10X18_ISO8859_1
  [FONT_FACE_TERMINUS_BOLD_10X18_ISO8859_1] = &_fonts_terminus_bold_10x18_iso8859_1_info,
#else
  [FONT_FACE_TERMINUS_BOLD_10X18_ISO8859_1] = NULL,
#endif

#ifdef FONTS_TERMINUS_12X24_ISO8859_1
  [FONT_FACE_TERMINUS_12X24_ISO8859_1] = &_fonts_terminus_12x24_iso8859_1_info,
#else
  [FONT_FACE_TERMINUS_12X24_ISO8859_1] = NULL,
#endif

#ifdef FONTS_TERMINUS_BOLD_12X24_ISO8859_1
  [FONT_FACE_TERMINUS_BOLD_12X24_ISO8859_1] = &_fonts_terminus_bold_12x24_iso8859_1_info,
#else
  [FONT_FACE_TERMINUS_BOLD_12X24_ISO8859_1] = NULL,
#endif

};

/**
 * @brief Number of fonts
 * 
 */
const size_t font_builtin_fonts_count =
  (sizeof(font_builtin_fonts) / sizeof(font_info_t *));

/////////////////////////////////////////////

uint16_t font_measure_string(const font_info_t *fnt, const char *s) {
  if (!s || !fnt)
    return 0;

  uint16_t res = 0;
  while (*s) {
    const font_char_desc_t *d = font_get_char_desc(fnt, *s);
    if (d)
      res += d->width + fnt->c;
    s++;
  }

  return res > 0 ? res - fnt->c : 0;
}

/** @} */