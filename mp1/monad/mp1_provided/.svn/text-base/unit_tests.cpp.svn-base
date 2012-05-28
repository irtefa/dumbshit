/* University of Illinois at Urbana-Champaign (UIUC)
 * CS 225
 * MP1 Tests
 * Jack Toole
 */

#include "proxy.h"
#include "easypng.h"
#include "util.h"

using namespace util;

#define BASE_DIR "./"

#define MP1_TEST( imgid , points)                                        \
	UNIT_TEST(in_##imgid##_png, points, points, 1000)                    \
	{                                                                    \
		PNG in;                                                          \
		PNG expected_out;                                                \
		PNG actual_out;                                                  \
		exec("/bin/ln","-sf", BASE_DIR "in_" #imgid ".png", "./in.png"); \
		exec("./mp1");                                                   \
		actual_out.readFromFile(BASE_DIR "out.png");                     \
		expected_out.readFromFile(BASE_DIR "out_" #imgid ".png");        \
		if (actual_out != expected_out)                                  \
			FAIL("out.png != out_" #imgid ".png");                       \
		PASS;                                                            \
	}

MP1_TEST(01, 0)
MP1_TEST(02, 0)
MP1_TEST(03, 0)

