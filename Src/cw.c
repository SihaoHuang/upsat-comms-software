/*
 * upsat-comms-software: Communication Subsystem Software for UPSat satellite
 *
 *  Copyright (C) 2016, Libre Space Foundation <http://librespacefoundation.org/>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "cw.h"
#include <stdlib.h>
#include <string.h>

#define CW_DOT_DURATION_MS 200
#define CW_DASH_DURATION_MS (3*CW_DOT_DURATION_MS)
#define CW_SYMBOL_SPACE_MS CW_DOT_DURATION_MS
#define CW_CHAR_SPACE_MS (3*CW_DOT_DURATION_MS)

/*
 * NOTE: Normally the ITU word space is 7 dots long. However our encoder
 * applies a char character after each character. So at the end of a word
 * a space with duration of 4 more dots should be applied.
 */
#define CW_WORD_SPACE_MS (4*CW_DOT_DURATION_MS)

static cw_char_t cw_lut[256];

/**
 * Lookup table to easily retrieve the duration of each pulse and pause
 */
static const uint32_t cw_duration_lut[6] =
  {   CW_DOT_DURATION_MS, CW_DASH_DURATION_MS,
      CW_CHAR_SPACE_MS, CW_WORD_SPACE_MS,
      CW_SYMBOL_SPACE_MS, 0 };


/**
 * Converts the input characters into CW Morse symbols
 * @param out the output buffer with the CW symbols
 * @param in the input buffer
 * @param len the output buffer
 * @return CW_OK if the encoding was successful or CW_ERROR if an illegal
 * character was encountered.
 */
int32_t
cw_encode(cw_char_t *out, const uint8_t *in, size_t len)
{
  size_t i;
  for(i = 0; i < len; i++) {
    out[i] = cw_lut[in[i]];
    if(!out[i].is_valid){
      return CW_ERROR;
    }
  }
  return CW_OK;
}

/**
 * Initializes the internal structures for CW encoding.
 *
 * The CW code is based at the ITU international Morse code
 */
void
cw_init ()
{
  uint8_t i;
  memset(cw_lut, 0, 256 * sizeof(cw_char_t));

  /*Perform the CW mapping based on the ITU international code */
  i = 0;
  cw_lut['A'].is_valid = 1;
  cw_lut['A'].s[i++] = CW_DOT;
  cw_lut['A'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['A'].s[i++] = CW_DASH;
  cw_lut['A'].s[i++] = CW_CHAR_DELIM;
  cw_lut['A'].s_num = i;

  i = 0;
  cw_lut['B'].is_valid = 1;
  cw_lut['B'].s[i++] = CW_DASH;
  cw_lut['B'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['B'].s[i++] = CW_DOT;
  cw_lut['B'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['B'].s[i++] = CW_DOT;
  cw_lut['B'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['B'].s[i++] = CW_DOT;
  cw_lut['B'].s[i++] = CW_CHAR_DELIM;
  cw_lut['B'].s_num = i;

  i = 0;
  cw_lut['C'].is_valid = 1;
  cw_lut['C'].s[i++] = CW_DASH;
  cw_lut['C'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['C'].s[i++] = CW_DOT;
  cw_lut['C'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['C'].s[i++] = CW_DASH;
  cw_lut['C'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['C'].s[i++] = CW_DOT;
  cw_lut['C'].s[i++] = CW_CHAR_DELIM;
  cw_lut['C'].s_num = i;

  i = 0;
  cw_lut['D'].is_valid = 1;
  cw_lut['D'].s[i++] = CW_DASH;
  cw_lut['D'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['D'].s[i++] = CW_DOT;
  cw_lut['D'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['D'].s[i++] = CW_DOT;
  cw_lut['D'].s[i++] = CW_CHAR_DELIM;
  cw_lut['D'].s_num = i;

  i = 0;
  cw_lut['E'].is_valid = 1;
  cw_lut['E'].s[i++] = CW_DOT;
  cw_lut['E'].s[i++] = CW_CHAR_DELIM;
  cw_lut['E'].s_num = i;

  i = 0;
  cw_lut['F'].is_valid = 1;
  cw_lut['F'].s[i++] = CW_DOT;
  cw_lut['F'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['F'].s[i++] = CW_DOT;
  cw_lut['F'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['F'].s[i++] = CW_DASH;
  cw_lut['F'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['F'].s[i++] = CW_DOT;
  cw_lut['F'].s[i++] = CW_CHAR_DELIM;
  cw_lut['F'].s_num = i;

  i = 0;
  cw_lut['G'].is_valid = 1;
  cw_lut['G'].s[i++] = CW_DASH;
  cw_lut['G'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['G'].s[i++] = CW_DASH;
  cw_lut['G'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['G'].s[i++] = CW_DOT;
  cw_lut['G'].s[i++] = CW_CHAR_DELIM;
  cw_lut['G'].s_num = i;

  i = 0;
  cw_lut['H'].is_valid = 1;
  cw_lut['H'].s[i++] = CW_DOT;
  cw_lut['H'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['H'].s[i++] = CW_DOT;
  cw_lut['H'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['H'].s[i++] = CW_DOT;
  cw_lut['H'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['H'].s[i++] = CW_DOT;
  cw_lut['H'].s[i++] = CW_CHAR_DELIM;
  cw_lut['H'].s_num = i;

  i = 0;
  cw_lut['I'].is_valid = 1;
  cw_lut['I'].s[i++] = CW_DOT;
  cw_lut['I'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['I'].s[i++] = CW_DOT;
  cw_lut['I'].s[i++] = CW_CHAR_DELIM;
  cw_lut['I'].s_num = i;

  i = 0;
  cw_lut['J'].is_valid = 1;
  cw_lut['J'].s[i++] = CW_DOT;
  cw_lut['J'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['J'].s[i++] = CW_DASH;
  cw_lut['J'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['J'].s[i++] = CW_DASH;
  cw_lut['J'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['J'].s[i++] = CW_DASH;
  cw_lut['J'].s[i++] = CW_CHAR_DELIM;
  cw_lut['J'].s_num = i;

  i = 0;
  cw_lut['K'].is_valid = 1;
  cw_lut['K'].s[i++] = CW_DASH;
  cw_lut['K'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['K'].s[i++] = CW_DOT;
  cw_lut['K'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['K'].s[i++] = CW_DASH;
  cw_lut['K'].s[i++] = CW_CHAR_DELIM;
  cw_lut['K'].s_num = i;

  i = 0;
  cw_lut['L'].is_valid = 1;
  cw_lut['L'].s[i++] = CW_DOT;
  cw_lut['L'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['L'].s[i++] = CW_DASH;
  cw_lut['L'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['L'].s[i++] = CW_DOT;
  cw_lut['L'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['L'].s[i++] = CW_DOT;
  cw_lut['L'].s[i++] = CW_CHAR_DELIM;
  cw_lut['L'].s_num = i;

  i = 0;
  cw_lut['M'].is_valid = 1;
  cw_lut['M'].s[i++] = CW_DASH;
  cw_lut['M'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['M'].s[i++] = CW_DASH;
  cw_lut['M'].s[i++] = CW_CHAR_DELIM;
  cw_lut['M'].s_num = i;

  i = 0;
  cw_lut['N'].is_valid = 1;
  cw_lut['N'].s[i++] = CW_DASH;
  cw_lut['N'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['N'].s[i++] = CW_DOT;
  cw_lut['N'].s[i++] = CW_CHAR_DELIM;
  cw_lut['N'].s_num = i;

  i = 0;
  cw_lut['O'].is_valid = 1;
  cw_lut['O'].s[i++] = CW_DASH;
  cw_lut['O'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['O'].s[i++] = CW_DASH;
  cw_lut['O'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['O'].s[i++] = CW_DASH;
  cw_lut['O'].s[i++] = CW_CHAR_DELIM;
  cw_lut['O'].s_num = i;

  i = 0;
  cw_lut['P'].is_valid = 1;
  cw_lut['P'].s[i++] = CW_DOT;
  cw_lut['P'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['P'].s[i++] = CW_DASH;
  cw_lut['P'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['P'].s[i++] = CW_DASH;
  cw_lut['P'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['P'].s[i++] = CW_DOT;
  cw_lut['P'].s[i++] = CW_CHAR_DELIM;
  cw_lut['P'].s_num = i;

  i = 0;
  cw_lut['Q'].is_valid = 1;
  cw_lut['Q'].s[i++] = CW_DASH;
  cw_lut['Q'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['Q'].s[i++] = CW_DASH;
  cw_lut['Q'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['Q'].s[i++] = CW_DOT;
  cw_lut['Q'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['Q'].s[i++] = CW_DASH;
  cw_lut['Q'].s[i++] = CW_CHAR_DELIM;
  cw_lut['Q'].s_num = i;

  i = 0;
  cw_lut['R'].is_valid = 1;
  cw_lut['R'].s[i++] = CW_DOT;
  cw_lut['R'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['R'].s[i++] = CW_DASH;
  cw_lut['R'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['R'].s[i++] = CW_DOT;
  cw_lut['R'].s[i++] = CW_CHAR_DELIM;
  cw_lut['R'].s_num = i;

  i = 0;
  cw_lut['S'].is_valid = 1;
  cw_lut['S'].s[i++] = CW_DOT;
  cw_lut['S'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['S'].s[i++] = CW_DOT;
  cw_lut['S'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['S'].s[i++] = CW_DOT;
  cw_lut['S'].s[i++] = CW_CHAR_DELIM;
  cw_lut['S'].s_num = i;

  i = 0;
  cw_lut['T'].is_valid = 1;
  cw_lut['T'].s[i++] = CW_DASH;
  cw_lut['T'].s[i++] = CW_CHAR_DELIM;
  cw_lut['T'].s_num = i;

  i = 0;
  cw_lut['U'].is_valid = 1;
  cw_lut['U'].s[i++] = CW_DOT;
  cw_lut['U'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['U'].s[i++] = CW_DOT;
  cw_lut['U'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['U'].s[i++] = CW_DASH;
  cw_lut['U'].s[i++] = CW_CHAR_DELIM;
  cw_lut['U'].s_num = i;

  i = 0;
  cw_lut['V'].is_valid = 1;
  cw_lut['V'].s[i++] = CW_DOT;
  cw_lut['V'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['V'].s[i++] = CW_DOT;
  cw_lut['V'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['V'].s[i++] = CW_DOT;
  cw_lut['V'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['V'].s[i++] = CW_DASH;
  cw_lut['V'].s[i++] = CW_CHAR_DELIM;
  cw_lut['V'].s_num = i;

  i = 0;
  cw_lut['W'].is_valid = 1;
  cw_lut['W'].s[i++] = CW_DOT;
  cw_lut['W'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['W'].s[i++] = CW_DASH;
  cw_lut['W'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['W'].s[i++] = CW_DASH;
  cw_lut['W'].s[i++] = CW_CHAR_DELIM;
  cw_lut['W'].s_num = i;

  i = 0;
  cw_lut['Y'].is_valid = 1;
  cw_lut['Y'].s[i++] = CW_DASH;
  cw_lut['Y'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['Y'].s[i++] = CW_DOT;
  cw_lut['Y'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['Y'].s[i++] = CW_DASH;
  cw_lut['Y'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['Y'].s[i++] = CW_DASH;
  cw_lut['Y'].s[i++] = CW_CHAR_DELIM;
  cw_lut['Y'].s_num = i;

  i = 0;
  cw_lut['Z'].is_valid = 1;
  cw_lut['Z'].s[i++] = CW_DASH;
  cw_lut['Z'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['Z'].s[i++] = CW_DASH;
  cw_lut['Z'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['Z'].s[i++] = CW_DOT;
  cw_lut['Z'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['Z'].s[i++] = CW_DOT;
  cw_lut['Z'].s[i++] = CW_CHAR_DELIM;
  cw_lut['Z'].s_num = i;

  i = 0;
  cw_lut['1'].is_valid = 1;
  cw_lut['1'].s[i++] = CW_DOT;
  cw_lut['1'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['1'].s[i++] = CW_DASH;
  cw_lut['1'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['1'].s[i++] = CW_DASH;
  cw_lut['1'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['1'].s[i++] = CW_DASH;
  cw_lut['1'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['1'].s[i++] = CW_DASH;
  cw_lut['1'].s[i++] = CW_CHAR_DELIM;
  cw_lut['1'].s_num = i;

  i = 0;
  cw_lut['2'].is_valid = 1;
  cw_lut['2'].s[i++] = CW_DOT;
  cw_lut['2'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['2'].s[i++] = CW_DOT;
  cw_lut['2'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['2'].s[i++] = CW_DASH;
  cw_lut['2'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['2'].s[i++] = CW_DASH;
  cw_lut['2'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['2'].s[i++] = CW_DASH;
  cw_lut['2'].s[i++] = CW_CHAR_DELIM;
  cw_lut['2'].s_num = i;

  i = 0;
  cw_lut['3'].is_valid = 1;
  cw_lut['3'].s[i++] = CW_DOT;
  cw_lut['3'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['3'].s[i++] = CW_DOT;
  cw_lut['3'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['3'].s[i++] = CW_DOT;
  cw_lut['3'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['3'].s[i++] = CW_DASH;
  cw_lut['3'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['3'].s[i++] = CW_DASH;
  cw_lut['3'].s[i++] = CW_CHAR_DELIM;
  cw_lut['3'].s_num = i;

  i = 0;
  cw_lut['4'].is_valid = 1;
  cw_lut['4'].s[i++] = CW_DOT;
  cw_lut['4'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['4'].s[i++] = CW_DOT;
  cw_lut['4'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['4'].s[i++] = CW_DOT;
  cw_lut['4'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['4'].s[i++] = CW_DOT;
  cw_lut['4'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['4'].s[i++] = CW_DASH;
  cw_lut['4'].s[i++] = CW_CHAR_DELIM;
  cw_lut['4'].s_num = i;

  i = 0;
  cw_lut['5'].is_valid = 1;
  cw_lut['5'].s[i++] = CW_DOT;
  cw_lut['5'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['5'].s[i++] = CW_DOT;
  cw_lut['5'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['5'].s[i++] = CW_DOT;
  cw_lut['5'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['5'].s[i++] = CW_DOT;
  cw_lut['5'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['5'].s[i++] = CW_DOT;
  cw_lut['5'].s[i++] = CW_CHAR_DELIM;
  cw_lut['5'].s_num = i;

  i = 0;
  cw_lut['6'].is_valid = 1;
  cw_lut['6'].s[i++] = CW_DASH;
  cw_lut['6'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['6'].s[i++] = CW_DOT;
  cw_lut['6'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['6'].s[i++] = CW_DOT;
  cw_lut['6'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['6'].s[i++] = CW_DOT;
  cw_lut['6'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['6'].s[i++] = CW_DOT;
  cw_lut['6'].s[i++] = CW_CHAR_DELIM;
  cw_lut['6'].s_num = i;

  i = 0;
  cw_lut['7'].is_valid = 1;
  cw_lut['7'].s[i++] = CW_DASH;
  cw_lut['7'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['7'].s[i++] = CW_DASH;
  cw_lut['7'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['7'].s[i++] = CW_DOT;
  cw_lut['7'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['7'].s[i++] = CW_DOT;
  cw_lut['7'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['7'].s[i++] = CW_DOT;
  cw_lut['7'].s[i++] = CW_CHAR_DELIM;
  cw_lut['7'].s_num = i;

  i = 0;
  cw_lut['8'].is_valid = 1;
  cw_lut['8'].s[i++] = CW_DASH;
  cw_lut['8'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['8'].s[i++] = CW_DASH;
  cw_lut['8'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['8'].s[i++] = CW_DASH;
  cw_lut['8'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['8'].s[i++] = CW_DOT;
  cw_lut['8'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['8'].s[i++] = CW_DOT;
  cw_lut['8'].s[i++] = CW_CHAR_DELIM;
  cw_lut['8'].s_num = i;

  i = 0;
  cw_lut['9'].is_valid = 1;
  cw_lut['9'].s[i++] = CW_DASH;
  cw_lut['9'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['9'].s[i++] = CW_DASH;
  cw_lut['9'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['9'].s[i++] = CW_DASH;
  cw_lut['9'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['9'].s[i++] = CW_DASH;
  cw_lut['9'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['9'].s[i++] = CW_DOT;
  cw_lut['9'].s[i++] = CW_CHAR_DELIM;
  cw_lut['9'].s_num = i;

  i = 0;
  cw_lut['0'].is_valid = 1;
  cw_lut['0'].s[i++] = CW_DASH;
  cw_lut['0'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['0'].s[i++] = CW_DASH;
  cw_lut['0'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['0'].s[i++] = CW_DASH;
  cw_lut['0'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['0'].s[i++] = CW_DASH;
  cw_lut['0'].s[i++] = CW_SYMBOL_DELIM;
  cw_lut['0'].s[i++] = CW_DASH;
  cw_lut['0'].s[i++] = CW_CHAR_DELIM;
  cw_lut['0'].s_num = i;

  cw_lut[' '].is_valid = 1;
  cw_lut[' '].s[0] = CW_WORD_DELIM;
  cw_lut[' '].s_num = 1;
}
