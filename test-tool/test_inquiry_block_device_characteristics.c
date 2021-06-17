/* 
   Copyright (C) 2013 by Ronnie Sahlberg <ronniesahlberg@gmail.com>
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>

#include <CUnit/CUnit.h>

#include "iscsi.h"
#include "scsi-lowlevel.h"
#include "iscsi-support.h"
#include "iscsi-test-cu.h"

void test_inquiry_block_device_characteristics(void)
{
        int ret;

        logging(LOG_VERBOSE, LOG_BLANK_LINE);
        logging(LOG_VERBOSE, "Test INQUIRY block device characteristics");

        logging(LOG_VERBOSE, "Check if we can read the block device characteristics page");
        ret = inquiry(sd, &task,
                      1, SCSI_INQUIRY_PAGECODE_BLOCK_DEVICE_CHARACTERISTICS, 255,
                      EXPECT_STATUS_GOOD);
        CU_ASSERT_EQUAL(ret, 0);

        logging(LOG_VERBOSE, "Verify we can unmarshall the DATA-IN buffer");
        inq_bdc = scsi_datain_unmarshall(task);
        CU_ASSERT_NOT_EQUAL(inq_bdc, NULL);
        if (inq_bdc == NULL)
        {
                logging(LOG_NORMAL, "[FAILED] Failed to unmarshall DATA-IN "
                                    "buffer");
                return;
        }

        if (task != NULL)
        {
                scsi_free_scsi_task(task);
                task = NULL;
        }
}
