/* profiles.c	definitions of stringprep profiles shipped with libstringprep
 * Copyright (C) 2002  Simon Josefsson
 *
 * This file is part of libstringprep.
 *
 * Libstringprep is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * Libstringprep is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with libstringprep; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "stringprep_generic.h"
#include "stringprep_nameprep.h"
#include "stringprep_kerberos5.h"

Stringprep_profile stringprep_generic[] = {
  /* 1) Map -- For each character in the input, check if it has a
        mapping and, if so, replace it with its mapping. This is
        described in section 3. */

  {STRINGPREP_MAP_TABLE, 0, stringprep_generic_B_1, "B.1"},
  {STRINGPREP_MAP_TABLE, ~STRINGPREP_NO_NFKC, stringprep_generic_B_2, "B.2"},
  {STRINGPREP_MAP_TABLE, STRINGPREP_NO_NFKC, stringprep_generic_B_3, "B.3"},

  /* 2) Normalize -- Possibly normalize the result of step 1 using
        Unicode normalization. This is described in section 4. */

  {STRINGPREP_NFKC, ~STRINGPREP_NO_NFKC, 0, "NFKC"},

  /* 3) Prohibit -- Check for any characters that are not allowed in
        the output. If any are found, return an error. This is
        described in section 5. */

  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_1_1, "C.1.1"},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_1_2, "C.1.2"},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_2_1, "C.2.1"},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_2_2, "C.2.2"},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_3, "C.3"},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_4, "C.4"},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_5, "C.5"},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_6, "C.6"},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_7, "C.7"},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_8, "C.8"},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_9, "C.9"},

  /* 4) Check bidi -- Possibly check for right-to-left characters, and
        if any are found, make sure that the whole string satisfies
        the requirements for bidirectional strings. If the string does
        not satisfy the requirements for bidirectional strings, return
        an error. This is described in section 6. */

  {STRINGPREP_BIDI, ~STRINGPREP_NO_BIDI, 0, "BIDI"},
  {STRINGPREP_BIDI_PROHIBIT_TABLE, ~STRINGPREP_NO_BIDI,
   stringprep_generic_C_9, "C.9"},
  {STRINGPREP_BIDI_RAL_TABLE, ~STRINGPREP_NO_BIDI, stringprep_generic_D_1,
   "D.1"},
  {STRINGPREP_BIDI_L_TABLE, ~STRINGPREP_NO_BIDI, stringprep_generic_D_2,
   "D.2"},

  /* 5) Check unassigned code points -- Possibly check the output for
        unassigned code points, according to the profile.  This is
        described in section 7. */

  {STRINGPREP_UNASSIGNED_TABLE, ~STRINGPREP_NO_UNASSIGNED,
  stringprep_generic_A_1, "A.1"},

  {0}
};

Stringprep_profile stringprep_nameprep[] = {
  {STRINGPREP_MAP_TABLE, 0, stringprep_generic_B_1, ""},
  {STRINGPREP_MAP_TABLE, 0, stringprep_generic_B_2, ""},
  {STRINGPREP_NFKC, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_1_2, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_2_2, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_3, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_4, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_5, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_6, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_7, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_8, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_9, ""},
  {STRINGPREP_BIDI, "BIDI"},
  {STRINGPREP_BIDI_PROHIBIT_TABLE, ~STRINGPREP_NO_BIDI,
   stringprep_generic_C_9, "C.9"},
  {STRINGPREP_BIDI_RAL_TABLE, 0, stringprep_generic_D_1, ""},
  {STRINGPREP_BIDI_L_TABLE, 0, stringprep_generic_D_2, ""},
  {STRINGPREP_UNASSIGNED_TABLE, ~STRINGPREP_NO_UNASSIGNED,
   stringprep_generic_A_1, ""},
  {0}
};

Stringprep_profile stringprep_kerberos5[] = {
  /* XXX this is likely to be wrong as the specification is
     a rough draft. */
  {STRINGPREP_MAP_TABLE, 0, stringprep_generic_B_1, ""},
  {STRINGPREP_MAP_TABLE, 0, stringprep_generic_B_3, ""},
  {STRINGPREP_NFKC, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_1_1, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_1_2, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_2_1, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_2_2, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_3, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_4, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_5, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_6, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_7, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_8, ""},
  {STRINGPREP_PROHIBIT_TABLE, 0, stringprep_generic_C_9, ""},
  {STRINGPREP_BIDI, "BIDI"},
  {STRINGPREP_BIDI_PROHIBIT_TABLE, ~STRINGPREP_NO_BIDI,
   stringprep_generic_C_9, "C.9"},
  {STRINGPREP_BIDI_RAL_TABLE, 0, stringprep_generic_D_1, ""},
  {STRINGPREP_BIDI_L_TABLE, 0, stringprep_generic_D_2, ""},
  {STRINGPREP_UNASSIGNED_TABLE, ~STRINGPREP_NO_UNASSIGNED,
   stringprep_generic_A_1, ""},
  {0}
};
