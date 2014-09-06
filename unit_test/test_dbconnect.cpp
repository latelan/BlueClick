/*************************************************************************
	> File Name: test_dbconnect.cpp
	> Author: latelan, coolboy1353@163.com
	> Created Time: 2014-09-01 22:32:06
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "dbconnect.h"

int main()
{
	struct resource_share res = {
		"喜欢你.mp3",
		"黄家驹，beyond，喜欢你",
		"5.6MB",
		"707C32C00B0BD7C60D0FB128D009E644",
		"00-1F-3C-17-00-E5",
		22
	};

	add_share_resource(&res);

	return 0;
}
