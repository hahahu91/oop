#include "pch.h"
#include "HtmlEncode\HtmlEncode.h"


TEST_CASE("HtmlEncode() encode text")
{
	CHECK(HtmlEncode("Cat <says> \"Meow\". M&M's") == "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
	CHECK(HtmlEncode("") == "");
	CHECK(HtmlEncode("M&M's") == "M&amp;M&apos;s");
	CHECK(HtmlEncode("M&M") == "M&amp;M");
	CHECK(HtmlEncode("most common text") == "most common text");
}